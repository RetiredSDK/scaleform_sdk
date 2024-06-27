/**************************************************************************

Filename    :   GL_Shader.cpp
Content     :   
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#if !defined(SF_USE_GLES)   // Do not compile under GLES 1.1

#include "Render/GL/GL_Shader.h"
#include "Render/GL/GL_HAL.h"
#include "Kernel/SF_Debug.h"

#if defined(GL_ES_VERSION_2_0)
#include "Render/GL/GLES_ExtensionMacros.h"
#include "Render/GL/GLES_ShaderDescs.h"
#else
#include "Render/GL/GL_ExtensionMacros.h"
#include "Render/GL/GL_ShaderDescs.h"
#endif

#include "Render/Render_FiltersLE.h"
#include "Kernel/SF_MsgFormat.h"

#include "Kernel/SF_SysFile.h"

#if defined(GL_ARB_get_program_binary) || defined(GL_OES_get_program_binary)
    #define SF_GL_BINARY_SHADER
    #define SF_GL_BINARY_SHADER_DEBUG 0 // 0 == no optional binary shader output, 1 == most optional output, 2 == all optional output.
#endif

#if defined(SF_GL_BINARY_SHADER_DEBUG) && SF_GL_BINARY_SHADER_DEBUG
    #define SF_BINARYSHADER_DEBUG_MESSAGE(...)  SF_DEBUG_MESSAGE(__VA_ARGS__)
    #define SF_BINARYSHADER_DEBUG_MESSAGE1(...) SF_DEBUG_MESSAGE1(__VA_ARGS__)
    #define SF_BINARYSHADER_DEBUG_MESSAGE2(...) SF_DEBUG_MESSAGE2(__VA_ARGS__)
    #define SF_BINARYSHADER_DEBUG_MESSAGE3(...) SF_DEBUG_MESSAGE3(__VA_ARGS__)
    #define SF_BINARYSHADER_DEBUG_MESSAGE4(...) SF_DEBUG_MESSAGE4(__VA_ARGS__)
#else
    #define SF_BINARYSHADER_DEBUG_MESSAGE(...)
    #define SF_BINARYSHADER_DEBUG_MESSAGE1(...)
    #define SF_BINARYSHADER_DEBUG_MESSAGE2(...)
    #define SF_BINARYSHADER_DEBUG_MESSAGE3(...)
    #define SF_BINARYSHADER_DEBUG_MESSAGE4(...)
#endif

namespace Scaleform { namespace Render { namespace GL {

extern const char* ShaderUniformNames[Uniform::SU_Count];
unsigned ShaderInterface::MaxRowsPerInstance = 0;
static const unsigned MaxShaderCodeSize = 4096; // Assume all shaders have a buffer smaller than this.

// Replaces the array size of a shader variable with the new count. This method assumes that 
// psrcPtr is a buffer with at least MaxShaderCodeSize bytes, and arrayString is the name of
// an shader variable which is an array.
void overwriteArrayCount(char* psrcPtr, const char* arrayString, unsigned newCount)
{
    char tempBuffer[MaxShaderCodeSize];
    if ( !psrcPtr )
        return;

    char * matFind = strstr(psrcPtr, arrayString);
    if (!matFind)
        return;
    
    SF_DEBUG_ASSERT(newCount > 0, "Can't have an array of size zero.");
    char tempNumber[16];
    SFsprintf(tempNumber, 16, "[%d]", newCount);
    UPInt size = (matFind - psrcPtr) + SFstrlen(arrayString);
    SFstrncpy(tempBuffer, MaxShaderCodeSize, psrcPtr, size);
    tempBuffer[size] = 0;
    SFstrcat(tempBuffer, MaxShaderCodeSize, tempNumber);

    char* endPtr = SFstrchr(matFind, ']');
    SF_DEBUG_ASSERT1(endPtr != 0, "Expected shader variable to be an array %s, but closing bracket not found.", arrayString );
    if (!endPtr)
        return;
    SFstrcat(tempBuffer, MaxShaderCodeSize, endPtr+1);

    // Overwrite the original buffer with the modified code.
    SFstrcpy(psrcPtr, MaxShaderCodeSize, tempBuffer);
}

bool ShaderObject::Init(HAL* phal, ShaderDesc::ShaderType shader, bool testCompilation)
{
    SF_UNUSED(testCompilation);
    pHal = phal;
    if (Prog)
    {
        glDeleteProgram(Prog);
        Prog = 0;
    }
    
    pVDesc = VertexShaderDesc::GetDesc(shader, phal->SManager.GLSLVersion);
    pFDesc = FragShaderDesc::GetDesc(shader, phal->SManager.GLSLVersion);

    if ( !pVDesc || !pFDesc )
        return false;

    GLint result;
    GLuint vp = 0;

    // Note: although we may actually modify the vertex shader source, we use the hash on the original
    // string pointer, so that we will find duplicate shaders. This assumes that all vertex shaders will
    // be modified in a consistent manner.
    if (!pHal->SManager.CompiledShaderHash.Get((void*)pVDesc->pSource, &vp))
    {
        // By default, the batch shaders are compiled with a batch count of 30. However, depending
        // on the maximum number of uniforms supported, this may not be possible, and the shader source
        // will not compile. Thus, we need to modify the incoming source, so it can compile.
        const char * vdescpSource = (const char*)pVDesc->pSource;
        char modifiedShaderSource[MaxShaderCodeSize];
        if ( pVDesc->Flags & Shader_Batch )
        {
            unsigned maxUniforms = (phal->Caps & Cap_MaxUniforms) >> Cap_MaxUniforms_Shift;
            unsigned maxInstances = Alg::Min<unsigned>(SF_RENDER_MAX_BATCHES, 
                                                       maxUniforms / ShaderInterface::GetMaximumRowsPerInstance());

            if ( maxInstances < SF_RENDER_MAX_BATCHES)
            {
			    SF_DEBUG_WARNONCE4(1, "For the default batch count of %d, %d uniforms are required."
						      "System only supports %d uniforms, batch count will be reduced to %d\n",
						      SF_RENDER_MAX_BATCHES, SF_RENDER_MAX_BATCHES *
						      ShaderInterface::GetMaximumRowsPerInstance(), maxUniforms,
						      maxInstances);
    							  
                vdescpSource = modifiedShaderSource;
                UPInt originalLength = SFstrlen(pVDesc->pSource);
                SF_ASSERT(originalLength < MaxShaderCodeSize);
                SFstrncpy(modifiedShaderSource, MaxShaderCodeSize, pVDesc->pSource, originalLength);
                modifiedShaderSource[originalLength] = 0;
                overwriteArrayCount(modifiedShaderSource, "vfmuniforms", 
                    ShaderInterface::GetCountPerInstance(pVDesc, Uniform::SU_vfmuniforms) * maxInstances);
                overwriteArrayCount(modifiedShaderSource, "vfuniforms", 
                    ShaderInterface::GetCountPerInstance(pVDesc, Uniform::SU_vfuniforms) * maxInstances);
            }
        }

        vp = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vp, 1, const_cast<const char**>(&vdescpSource), 0);
        glCompileShader(vp);
        glGetShaderiv(vp, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            GLchar msg[512];
            glGetShaderInfoLog(vp, sizeof(msg), 0, msg);
            SF_DEBUG_ERROR2(!testCompilation, "%s: %s\n", vdescpSource, msg);
            glDeleteShader(vp);
            return 0;
        }
        pHal->SManager.CompiledShaderHash.Set((void*)pVDesc->pSource, vp);
    }

    GLuint fp = 0;
    if (!pHal->SManager.CompiledShaderHash.Get((void*)pFDesc->pSource, &fp))
    {
        fp = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fp, 1, const_cast<const char**>(&pFDesc->pSource), 0);
        glCompileShader(fp);
        glGetShaderiv(fp, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            GLchar msg[1512];
            glGetShaderInfoLog(fp, sizeof(msg), 0, msg);
            SF_DEBUG_ERROR2(!testCompilation, "%s: %s\n", pFDesc->pSource, msg);
            glDeleteShader(fp);
            return 0;
        }
        pHal->SManager.CompiledShaderHash.Set((void*)pFDesc->pSource, fp);
    }

    Prog = glCreateProgram();
    glAttachShader(Prog, vp);
    glAttachShader(Prog, fp);
    
    for (int i = 0; i < pVDesc->NumAttribs; i++)
        glBindAttribLocation(Prog, i, pVDesc->Attributes[i].Name);

#if !defined(SF_USE_GLES_ANY) && defined(GL_VERSION_3_0)
    // In GLSL 1.5, we need to explicitly bind the output variable to a color output.
    if (pHal->SManager.GLSLVersion == ShaderDesc::ShaderVersion_GLSL150)
    {
        SF_DEBUG_ASSERT(Has_glBindFragDataLocation(), "Must have glBindFragDataLocation if using GLSL 1.5.");
        glBindFragDataLocation(Prog, 0, "fcolor");
    }
#endif   
    
#if !defined(SF_USE_GLES_ANY) && defined(SF_GL_BINARY_SHADER)
    // In OpenGL, we must set the retrievable hint, otherwise, it won't generate a binary format we can save.
    if (pHal->Caps & Cap_BinaryShaders)
        glProgramParameteri(Prog, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
#endif

    glLinkProgram(Prog);

#if !defined(SF_USE_GLES_ANY) && defined(GL_VERSION_3_0)
    // In GLSL 1.5, we need to explicitly bind the output variable to a color output.
    if (pHal->SManager.GLSLVersion == ShaderDesc::ShaderVersion_GLSL150)
    {
        SF_DEBUG_ASSERT(Has_glGetFragDataLocation(), "Must have glGetFragDataLocation if using GLSL 1.5.");
        SF_DEBUG_ASSERT(glGetFragDataLocation(Prog, "fcolor") != -1, "fcolor not bound to an output stage.");            
    }
#endif
    
    // The shaders will not actually be deleted until the program is destroyed.
    // We check the status of deletion, because some platforms (iOS) generate 
    // errors for deleting shaders multiple times.
    GLint fstatus, vstatus;
    glGetShaderiv(fp, GL_DELETE_STATUS, &fstatus);
    glGetShaderiv(vp, GL_DELETE_STATUS, &vstatus);
    if (fstatus == GL_FALSE)
        glDeleteShader(fp);
    if (vstatus == GL_FALSE)
        glDeleteShader(vp);
    
    if (!InitUniforms())
    {
        glDeleteProgram(Prog);
        Prog = 0;
        return false;
    }
    
    return true;
}

bool ShaderObject::InitUniforms()
{
    GLint result;
    glGetProgramiv(Prog, GL_LINK_STATUS, &result);
    if (!result)
    {
        GLchar msg[512];
        glGetProgramInfoLog(Prog, sizeof(msg), 0, msg);
        SF_DEBUG_ERROR1(1, "link: %s\n", msg);
        return false;
    }

    for (unsigned i = 0; i < Uniform::SU_Count; i++)
    {
        if (pFDesc->Uniforms[i].Location >= 0 || pVDesc->Uniforms[i].Location >= 0)
        {
            Uniforms[i] = glGetUniformLocation(Prog, ShaderUniformNames[i]);

            // It seems that the binary shaders could store uniform names with '[0]' appended on them
            // So, if we fail to find the uniform with the original name, search for that.
            if (Uniforms[i] < 0)
            {
                char arrayname[128];
                SFstrcpy(arrayname, 128, ShaderUniformNames[i]);
                SFstrcat(arrayname, 128, "[0]");
                Uniforms[i] = glGetUniformLocation(Prog, arrayname);
            }

            // Couldn't find the uniform at all.
            if (Uniforms[i] < 0 )
            {
                SF_DEBUG_ERROR1(1, "Failed to find uniform %s (program uniforms):", ShaderUniformNames[i]);
                dumpUniforms();
                return false;
            }

            if (pFDesc->Uniforms[i].Location >= 0)
            {
                SF_ASSERT(pVDesc->Uniforms[i].Location < 0);
                AllUniforms[i] = pFDesc->Uniforms[i];
            }
            else
                AllUniforms[i] = pVDesc->Uniforms[i];
        }
        else
            Uniforms[i] = -1;
    }
    return result != 0;
}

void ShaderObject::Shutdown( )
{
    if (Prog)
        glDeleteProgram(Prog);
    
    Prog   = 0;
    pVDesc = 0;
    pFDesc = 0;
    pHal   = 0;
}

ShaderObject::~ShaderObject()
{
    Shutdown();
}

bool ShaderObject::InitBinary(HAL* phal, ShaderDesc::ShaderVersion ver, unsigned comboIndex, File* pfile, void*& buffer, GLsizei& bufferSize)
{
#if defined(SF_GL_BINARY_SHADER)
    pHal = phal;
    if (Prog)
    {
        glDeleteProgram(Prog);
        Prog = 0;
    }

    VertexShaderDesc::ShaderIndex vidx = VertexShaderDesc::GetShaderIndexForComboIndex(comboIndex, ver);
    FragShaderDesc::ShaderIndex fidx = FragShaderDesc::GetShaderIndexForComboIndex(comboIndex, ver);
    pVDesc = VertexShaderDesc::Descs[vidx];
    pFDesc = FragShaderDesc::Descs[fidx];

    if (!pVDesc || !pFDesc)
        return false;


    SF_BINARYSHADER_DEBUG_MESSAGE4(1, "Shader indices (v=%d - type=%d, f=%d - type = %d)", vidx, pVDesc->Type, fidx, pFDesc->Type);
    Prog = glCreateProgram();

    GLenum format = pfile->ReadSInt32();
    GLsizei size = pfile->ReadSInt32();

    SF_BINARYSHADER_DEBUG_MESSAGE2(1, "Loading binary shader (size=%d, format=%d)", size, format);
    if (bufferSize < size)
    {
        bufferSize = (size + 1023) & ~1023;
        SF_BINARYSHADER_DEBUG_MESSAGE1(1, "Allocating shader buffer, size %d", bufferSize );
        buffer = buffer == 0 ? SF_ALLOC(bufferSize, Stat_Default_Mem) : SF_REALLOC(buffer, bufferSize, Stat_Default_Mem);
    }
    if (pfile->Read((UByte*)buffer, size) < size)
    {
        SF_DEBUG_WARNING(1, "Error reading from binary shader file (insufficient space remaining).");
        glDeleteProgram(Prog);
        Prog = 0;
        return false;
    }

    glProgramBinary(Prog, format, buffer, size);

    if (!InitUniforms())
    {
        glDeleteProgram(Prog);
        Prog = 0;
        return false;
    }

    // Save the size of the loaded binary.
    glGetProgramiv(Prog, GL_PROGRAM_BINARY_LENGTH, &BinarySize);

    //dumpUniforms();
    return true;

#else // SF_GL_BINARY_SHADER
    return false;
#endif
}

bool ShaderObject::SaveBinary(File* pfile, void*& buffer, GLsizei& bufferSize, GLsizei& totalSize)
{
#if defined(SF_GL_BINARY_SHADER)

    GLsizei size;
    glGetProgramiv(Prog, GL_PROGRAM_BINARY_LENGTH, &size);
    SF_DEBUG_MESSAGE(size < 0, "glGetProgramiv returned GL_PROGRAM_BINARY_LENGTH == 0");

    if (bufferSize < size)
    {
        bufferSize = (size + 1023) & ~1023;
        buffer = buffer == 0 ? SF_ALLOC(bufferSize, Stat_Default_Mem) : SF_REALLOC(buffer, bufferSize, Stat_Default_Mem);
    }

    GLenum format;
    memset(buffer, 0, bufferSize);
    glGetProgramBinary(Prog, bufferSize, 0, &format, buffer);
    if (size > 0)
    {
        pfile->WriteSInt32(format);
        pfile->WriteSInt32(size);
        SF_BINARYSHADER_DEBUG_MESSAGE2(1, "Saving binary shader (size=%d, format=%d) - uniforms:", size, format);
        dumpUniforms();

        if (pfile->Write((UByte*)buffer, size) < size)
        {
            SF_DEBUG_MESSAGE(1, "Failed writing to binary shader file.");
            return false;
        }
        totalSize += size;

        return true;
    }
#else
    SF_DEBUG_MESSAGE(1, "Cannot save binary shaders, SF_GL_BINARY_SHADER is not defined.");
#endif

    return false;
}

void ShaderObject::dumpUniforms()
{
#if defined(SF_GL_BINARY_SHADER_DEBUG) && SF_GL_BINARY_SHADER_DEBUG >= 2
    GLint uniformCount;
    glGetProgramiv(Prog, GL_ACTIVE_UNIFORMS, &uniformCount);
    SF_DEBUG_MESSAGE1(1, "Shader has %d uniforms:", uniformCount);
    for ( int uniform = 0; uniform < uniformCount; ++uniform)
    {
        char uniformName[128];
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveUniform(Prog, uniform, 128, &length, &size, &type, uniformName);
        SF_DEBUG_MESSAGE3(1,"\t%16s (size=%d, type=%d)", uniformName, size, type);
    }
#endif
}


bool ShaderInterface::SetStaticShader(ShaderDesc::ShaderType shader, const VertexFormat*)
{
    CurShader.pShaderObj = pHal->GetStaticShader(shader);
    if ( !CurShader.pShaderObj || !CurShader.pShaderObj->Prog )
    {
        CurShader.pVDesc = 0;
        CurShader.pFDesc = 0;
        glUseProgram(0);
        SF_ASSERT(0);
        return false;
    }
    CurShader.pVDesc = CurShader.pShaderObj->pVDesc;
    CurShader.pFDesc = CurShader.pShaderObj->pFDesc;
    glUseProgram(CurShader.pShaderObj->Prog);
    
    return true;
}

void ShaderInterface::SetTexture(Shader sd, unsigned var, Render::Texture* ptex, ImageFillMode fm, unsigned index)
{
    GL::Texture* ptexture = (GL::Texture*)ptex;

    SF_ASSERT(CurShader.pShaderObj->Uniforms[var] >= 0 ); // Expected texture uniform does not exist in this shader.
    int *textureStages = 0;
    int *stageCount = 0;
    int baseLocation = sd->pFDesc->Uniforms[var].Location;

    // Find our texture uniform index.
    int tu;
    for ( tu = 0; tu < FragShaderDesc::MaxTextureSamplers; ++tu)
    {
        if ( TextureUniforms[tu].UniformVar < 0 || TextureUniforms[tu].UniformVar == (int)var )
        {
            TextureUniforms[tu].UniformVar = var;
            textureStages = TextureUniforms[tu].SamplerStages;
            stageCount = &TextureUniforms[tu].StagesUsed;
            break;
        }
    }
    SF_DEBUG_ASSERT(tu < FragShaderDesc::MaxTextureSamplers, "Unexpected number of texture uniforms used.");

    for (unsigned plane = 0; plane < ptexture->GetTextureStageCount() ; plane++)
    {
        int stageIndex = baseLocation + index + plane;
        textureStages[plane + index] = stageIndex;
        *stageCount = Alg::Max<int>(*stageCount, index+plane+1);
    }

    ptex->ApplyTexture(baseLocation + index, fm);
}

void ShaderInterface::Finish(unsigned batchCount)
{
    SF_ASSERT(CurShader.pShaderObj->Prog);

    const ShaderObject* pCurShader = CurShader.pShaderObj;
    for (int var = 0; var < Uniform::SU_Count; var++)
    {
        if (UniformSet[var])
        {
            unsigned size;
            if (pCurShader->AllUniforms[var].BatchSize > 0)
                size = batchCount * pCurShader->AllUniforms[var].BatchSize;
            else if (pCurShader->AllUniforms[var].ElementSize)
                size = pCurShader->AllUniforms[var].Size / pCurShader->AllUniforms[var].ElementSize;
            else
                continue;

            switch (pCurShader->AllUniforms[var].ElementCount)
            {
                case 16:
                    glUniformMatrix4fv(pCurShader->Uniforms[var], size, false /* transpose */,
                        UniformData + pCurShader->AllUniforms[var].ShadowOffset);
                    break;
                case 4:
                    glUniform4fv(pCurShader->Uniforms[var], size,
                        UniformData + pCurShader->AllUniforms[var].ShadowOffset);
                    break;
                case 3:
                    glUniform3fv(pCurShader->Uniforms[var], size,
                        UniformData + pCurShader->AllUniforms[var].ShadowOffset);
                    break;
                case 2:
                    glUniform2fv(pCurShader->Uniforms[var], size,
                        UniformData + pCurShader->AllUniforms[var].ShadowOffset);
                    break;
                case 1:
                    glUniform1fv(pCurShader->Uniforms[var], size,
                        UniformData + pCurShader->AllUniforms[var].ShadowOffset);
                    break;

                default:
                    SF_ASSERT(0);
            }
        }
    }

    // Set sampler stage uniforms.
    for (int tu = 0; tu < FragShaderDesc::MaxTextureSamplers; ++tu)
    {
        if ( TextureUniforms[tu].UniformVar < 0 )
            break;

        glUniform1iv( pCurShader->Uniforms[TextureUniforms[tu].UniformVar], 
            TextureUniforms[tu].StagesUsed, TextureUniforms[tu].SamplerStages );
    }

    memset(UniformSet, 0, Uniform::SU_Count);
    memset(TextureUniforms, -1, sizeof(TextureUniforms));
}

unsigned ShaderInterface::GetMaximumRowsPerInstance()
{
    // Check for cached value. This should not change between runs. TBD: precalculate.
    if ( MaxRowsPerInstance == 0 )
    {
        // Note: this assumes that batch variables are stored in shader descs.
        MaxRowsPerInstance = 0;
        for ( unsigned desc = 0; desc < VertexShaderDesc::VSI_Count; ++desc )
        {
            const VertexShaderDesc* pvdesc = VertexShaderDesc::Descs[desc];
            MaxRowsPerInstance = Alg::Max(MaxRowsPerInstance, GetRowsPerInstance(pvdesc));
        }
    }
    return MaxRowsPerInstance;
}

bool ShaderInterface::GetDynamicLoopSupport()
{
    // Check cached value. -1 indicates not calculated yet.
    if ( DynamicLoops < 0 )
    {
        // Just try to compile a shader we know has dynamic loops, and see if it fails.
        for ( int i = 0; i < FragShaderDesc::FSI_Count; ++i )
        {
            if ( FragShaderDesc::Descs[i] && FragShaderDesc::Descs[i]->Flags & Shader_DynamicLoop )
            {
                DynamicLoops = pHal->SManager.StaticShaders[i].Init(pHal, FragShaderDesc::Descs[i]->Type, true ) ? 1 : 0;            
                break;
            }
        }
    }
    return DynamicLoops ? true : false;
}

unsigned ShaderInterface::GetRowsPerInstance( const VertexShaderDesc* pvdesc )
{
    // Desc doesn't exist, or isn't batched, don't consider it.
    if ( !pvdesc || (pvdesc->Flags & Shader_Batch) == 0 )
        return 0;

    unsigned currentUniforms = 0;
    for ( unsigned uniform = 0; uniform < Uniform::SU_Count; ++uniform )
    {
        if ( pvdesc->BatchUniforms[uniform].Size > 0 )
        {
            currentUniforms += pvdesc->BatchUniforms[uniform].Size *
                (pvdesc->BatchUniforms[uniform].Array == Uniform::SU_vfmuniforms ? 4 : 1);
        }
    }
    return currentUniforms;
}

// Returns the number of entries per instance of the given uniform type.
unsigned ShaderInterface::GetCountPerInstance(const VertexShaderDesc* pvdesc, Uniform::UniformType arrayType)
{
    // Desc doesn't exist, or isn't batched, don't consider it.
    if ( !pvdesc || (pvdesc->Flags & Shader_Batch) == 0 )
        return 0;

    unsigned currentUniforms = 0;
    for ( unsigned uniform = 0; uniform < Uniform::SU_Count; ++uniform )
    {
        if ( pvdesc->BatchUniforms[uniform].Size > 0 )
        {
            if ( pvdesc->BatchUniforms[uniform].Array == arrayType )
                currentUniforms += pvdesc->BatchUniforms[uniform].Size;
        }
    }
    return currentUniforms;
}

ShaderManager::ShaderManager(ProfileViews* prof) :
    StaticShaderManagerType(prof), 
    Caps(0),
    GLSLVersion(ShaderDesc::ShaderVersion_Default),
    ShouldUseBinaryShaders(false)
{
    memset(StaticShaders, 0, sizeof(StaticShaders));
}

static const char* ShaderHeaderString = "GFxShaders";
static const unsigned ShaderHeaderSize = 10;

bool ShaderManager::Initialize(HAL* phal, unsigned vmcFlags)
{
    pHal = phal;

    // On GL (Mac/PC), if the driver is GL 3.2+, it does not support GLSL 1.1/1.2.
    // However, if the driver is GL3.1-, it might not support GLSL 1.5, so we need to
    // support both.
#if !defined(SF_USE_GLES_ANY)
    const GLubyte* glVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
   	if (glVersion == 0 || glGetError() != 0)
    {
        if (!ShaderDesc::IsShaderVersionSupported(GLSLVersion))
        {
            SF_DEBUG_MESSAGE(1, "GL_VERSION return NULL, or produced error, but GLSL v1.10 support is not present. Failing.");
            return false;
        }
        else
        {
            SF_DEBUG_WARNING(1, "GL_VERSION returned NULL, or produced error. Assuming GLSL v1.10.\n");
            return true;
        }
    }
    
    // Parse the verison string.
    unsigned majorVersion, minorVersion;
    SFsscanf(reinterpret_cast<const char*>(glVersion), "%d.%d", &majorVersion, &minorVersion);
    
    // Per the spec, minorVersion should always be two digits.
    if (majorVersion > 1 || minorVersion >= 50)
    {
        GLSLVersion = ShaderDesc::ShaderVersion_GLSL150;
        if (!ShaderDesc::IsShaderVersionSupported(GLSLVersion))
        {
            SF_DEBUG_WARNING1(1, "GLSL version reported %s, however GLSL v1.50 support is unavailable. Failing.", glVersion);
            return false;
        }
    }
    else if (majorVersion > 1 || minorVersion >= 20)
    {
        Caps &= ~Cap_Instancing; // can't support instancing in GLSL 1.20
        GLSLVersion = ShaderDesc::ShaderVersion_GLSL120;
        if (!ShaderDesc::IsShaderVersionSupported(GLSLVersion))
        {
            SF_DEBUG_WARNING1(1, "GLSL version reported %s, however GLSL v1.20 support is unavailable. Failing.", glVersion);
            return false;
        }
    }
    else
    {
        Caps &= ~Cap_Instancing; // can't support instancing in GLSL 1.10
        GLSLVersion = ShaderDesc::ShaderVersion_GLSL110;
        if (!ShaderDesc::IsShaderVersionSupported(GLSLVersion))
        {
            SF_DEBUG_WARNING1(1, "GLSL version reported %s, however GLSL v1.10 support is unavailable. Failing.", glVersion);
            return false;
        }
    }
    
#endif

    ShouldUseBinaryShaders = (vmcFlags & HALConfig_DisableBinaryShaders) == 0 && (Caps & Cap_BinaryShaders);

    // Attempt to load binary shaders. If successful (all loaded), just finish now.
    if (ShouldUseBinaryShaders && loadBinaryShaders(phal))
            return true;

    // If it was not requested to compile shaders dynamically, then compile all of them now. Note that if binary
    // shader support is on, this is overridden, and all shaders are compiled anyhow, because they will be saved
    // immediately.
    SF_DEBUG_WARNING((vmcFlags & HALConfig_DynamicShaderCompile) && ShouldUseBinaryShaders,
        "Dynamic shader compilation was requested, but this is incompatible with using binary shaders, "
        "which this system supports. Dynamic compilation flag will be ignored.\n");

    if ( ShouldUseBinaryShaders || (vmcFlags & HALConfig_DynamicShaderCompile) == 0)
    {
        for (unsigned i = 0; i < UniqueShaderCombinations; i++)
        {
            // If the InitBinary succeeded, skip recompilation.
            if ( StaticShaders[i].Prog )
                continue;

            ShaderType shaderType = ShaderDesc::GetShaderTypeForComboIndex(i, GLSLVersion);
            if (shaderType == ShaderDesc::ST_None)
                continue;
            
            const FragShaderDesc* fdesc = FragShaderDesc::GetDesc(shaderType, GLSLVersion);
            const VertexShaderDesc* vdesc = VertexShaderDesc::GetDesc(shaderType, GLSLVersion);

            if (!fdesc || !vdesc )
                continue;

            // If the platform does not support dynamic loops, do not initialize shaders that use them.
            if ((fdesc->Flags & Shader_DynamicLoop) && (Caps & Cap_NoDynamicLoops))
                continue;

            // If the platform doesn't support instancing, do not initialize shaders that use it.
            if ( (fdesc->Flags & Shader_Instanced) && !HasInstancingSupport() )
                continue;

            if ( !StaticShaders[i].Init(phal, shaderType))
                return false;
        }
    }

    // Now that all shaders have been compiled, save them to disk.
    if (ShouldUseBinaryShaders)
        saveBinaryShaders();

    return true;
}

unsigned ShaderManager::SetupFilter(const Filter* filter, unsigned fillFlags, unsigned* passes, BlurFilterState& leBlur) const
{
    // If we don't support dynamic loops only allow color matrix filters (which don't have dynamic loops).
    if ( (Caps & Cap_NoDynamicLoops) == 0 || filter->GetFilterType() == Filter_ColorMatrix )
    {
        leBlur.Passes = 0;
        return StaticShaderManagerType::GetFilterPasses(filter, fillFlags, passes);
    }

    if (leBlur.Setup(filter))
        return leBlur.Passes;

    return 0;
}

bool ShaderManager::HasInstancingSupport() const
{
    // Caps generated on InitHAL.
    return (Caps & Cap_Instancing) != 0;
}

void ShaderManager::Reset()
{
#if !defined(SF_USE_GLES_ANY)
    // Save binary shaders. In OpenGL, additional optimization may be done after a shader is actually used.
    // Thus, saving the binaries at this point, may yield additional benefits when reloading them. 
    if (ShouldUseBinaryShaders)
        saveBinaryShaders();
#endif

    // Destroy the shader programs as well.
    CompiledShaderHash.Clear();
    for (unsigned i = 0; i < UniqueShaderCombinations; i++)
        StaticShaders[i].Shutdown();
}

void ShaderManager::saveBinaryShaders()
{
#if defined(SF_GL_BINARY_SHADER)

    SF_BINARYSHADER_DEBUG_MESSAGE(1,"Saving Binary Shaders...");

    // If we support binary shaders, save them now.
    if (Caps & Cap_BinaryShaders)
    {
        // Before we do anything, run through all our shaders, and see if their binary sizes have changed. If not,
        // assume no further optimizations were done, and thus, do not actually re-save the file on shutdown.
        bool needsResave = false;
        for (unsigned shader =0; shader < UniqueShaderCombinations; ++shader)
        {
            if (StaticShaders[shader].Prog == 0)
                continue;

            GLint newBinarySize;
            glGetProgramiv(StaticShaders[shader].Prog, GL_PROGRAM_BINARY_LENGTH, &newBinarySize);
            if (StaticShaders[shader].BinarySize != newBinarySize)
            {
                SF_BINARYSHADER_DEBUG_MESSAGE4(1, "Shader binary is different size (old=%d, new=%d, comboIndex=%d, prog=%d)", 
                    StaticShaders[shader].BinarySize, newBinarySize, shader, StaticShaders[shader].Prog);
                needsResave = true;
                break;
            }
        }
        // If we don't need to resave, then just quit now.
        if (!needsResave)
            return;

        String shpath = BinaryShaderPath + "GFxShaders.cache";
        Ptr<File>  pfile = *SF_NEW SysFile(shpath, File::Open_Write|File::Open_Create|File::Open_Truncate);

        if (pfile->IsValid())
        {
            GLsizei totalSize = 0;
            GLsizei bufferSize = 0;
            void* buffer = 0;

            pfile->Write((const UByte*) ShaderHeaderString, 10);
            pfile->WriteSInt64(SF_GFXSHADERMAKER_TIMESTAMP);
            totalSize += ShaderHeaderSize + sizeof(SInt64);

            SInt32 count = 0;
            for (unsigned i = 0; i < UniqueShaderCombinations; i++)
            {
                if (StaticShaders[i].Prog)
                    count++;
            }

            pfile->WriteSInt32(count);
            totalSize += 4;

            for (unsigned i = 0; i < UniqueShaderCombinations; i++)
            {
                if (StaticShaders[i].Prog)
                {
                    pfile->WriteSInt32(i);
                    totalSize += sizeof(SInt32);
                    SF_BINARYSHADER_DEBUG_MESSAGE1(1, "Saving binary shader (comboIndex=%d)", i);
                    if (!StaticShaders[i].SaveBinary(pfile, buffer, bufferSize, totalSize))
                    {
                        SF_DEBUG_WARNING1(1, "Error saving shader (comboIndex=%d)", i);
                        pfile->Close();
                        // Delete the contents of the file.
                        pfile = SF_NEW SysFile(shpath.ToCStr(), File::Open_Write|File::Open_Truncate);
                        pfile->Close();
                        break;
                    }
                }
            }

            if (buffer)
                SF_FREE(buffer);

            SF_BINARYSHADER_DEBUG_MESSAGE1(1, "Total bytes written to shader cache file: %d", totalSize);
            pfile->Close();
        }
        else
            SF_DEBUG_WARNING2(1, "Error creating binary shader cache %s: %d", shpath.ToCStr(), pfile->GetErrorCode());
    }
#endif // SF_GL_BINARY_SHADER
}

bool ShaderManager::loadBinaryShaders( HAL* phal )
{
#if defined(SF_GL_BINARY_SHADER)

    if (Caps & Cap_BinaryShaders)
    {
        String shpath = BinaryShaderPath + "GFxShaders.cache";
        Ptr<File>  pfile = *SF_NEW SysFile(shpath);

        SF_BINARYSHADER_DEBUG_MESSAGE1(1, "Shader binary file is %d bytes", pfile->GetLength());
        if (pfile)
        {
            char header[ShaderHeaderSize];
            SInt64 version = 0;
            SInt32 count = 0;

            if (pfile->Read((UByte*)header, ShaderHeaderSize) < (int)ShaderHeaderSize || strncmp(header, ShaderHeaderString, ShaderHeaderSize))
            {
                SF_DEBUG_WARNING1(1, "Binary shader file does not contain the required header (%s).", ShaderHeaderString);
            }
            else
            {
                version = pfile->ReadSInt64();
                count = pfile->ReadSInt32();
                if ( version != SF_GFXSHADERMAKER_TIMESTAMP )
                {
                    SF_DEBUG_WARNING2(version != SF_GFXSHADERMAKER_TIMESTAMP, "Binary shaders timestamps do not match executable. "
                        "Using source shaders (bin=%lld, exe=%lld)", version, SF_GFXSHADERMAKER_TIMESTAMP);
                    count = 0; // Will skip reading of shaders.
                }
            }

            GLsizei bufferSize = 0;
            void* buffer = 0;
            bool initSuccess = true;
            for (int i = 0; i < count; i++)
            {
                SInt32 comboIndex = pfile->ReadSInt32();
                SF_BINARYSHADER_DEBUG_MESSAGE1(1, "Loading binary shader (comboIndex=%d)", comboIndex);

                // Find the shader type that goes with this combination.
                if (!StaticShaders[comboIndex].InitBinary(phal, GLSLVersion, comboIndex, pfile, buffer, bufferSize))
                {
                    SF_DEBUG_WARNING(1, "Error loading some binary shaders. Using source.");

                    // Kill all previously loaded binary shaders, they are likely bogus.
                    for ( unsigned ci = 0; ci < UniqueShaderCombinations; ++ci)
                        StaticShaders[ci].Shutdown();

                    initSuccess = false;
                    break;
                }                    
            }

            if (buffer)
                SF_FREE(buffer);

            // If we initialized all shaders successfully, stop now.
            if (count > 0 && initSuccess)
                return true;
        }
    }
#endif // SF_GL_BINARY_SHADER

    // We did not load all binary shaders.
    return false;
}


//*** ShaderInterface
void ShaderInterface::ResetContext()
{
    for (BlurShadersHash::Iterator It = BlurShaders.Begin(); It != BlurShaders.End(); ++It)
        delete It->Second;

    BlurShaders.Clear();
}

const BlurFilterShader* ShaderInterface::GetBlurShader(const BlurFilterShaderKey& params)
{
    const BlurFilterShader*const* psh = BlurShaders.Get(params);
    if (psh)
        return *psh;

    StringBuffer vsrc, fsrc;

    fsrc.AppendString(
#if defined(GL_ES_VERSION_2_0)
        "precision mediump float;\n"
#endif
        "uniform sampler2D tex;\n"
        "uniform vec2 texscale;\n"
        "uniform vec4 cxmul;\n"
        "uniform vec4 cxadd;\n"
        "uniform float samples;\n");

    vsrc.AppendString("uniform vec4 mvp[2];\nuniform vec2 texscale;\n");
    for (int i = 0; i < params.TotalTCs; i++)
    {
        SPrintF(vsrc, "attribute vec2 intc%d;\n", i);
        SPrintF(vsrc, "varying   vec2 tc%d;\n", i);
        SPrintF(fsrc, "varying   vec2 tc%d;\n", i);
    }

    if (params.Mode & Filter_Shadow)
    {
        vsrc.AppendString("uniform vec2 srctexscale;\n");

        fsrc.AppendString("uniform vec4 scolor;\n"
                          "uniform sampler2D srctex;\n");

        if (params.Mode & BlurFilterParams::Mode_Highlight)
        {
            fsrc.AppendString("uniform vec4 scolor2;\n");
        }
    }

    vsrc.AppendString("attribute vec4 pos;\n"
                      "void main(void)\n{\n"
                      "  vec4 opos = pos;\n"
                      "  opos.x = dot(pos, mvp[0]);\n"
                      "  opos.y = dot(pos, mvp[1]);\n"
                      "  gl_Position = opos;\n");
    for (int i = 0; i < params.TotalTCs-params.BaseTCs; i++)
        SPrintF(vsrc, "  tc%d = intc%d * texscale;\n", i, i);
    for (int i = params.TotalTCs-params.BaseTCs; i < params.TotalTCs; i++)
        SPrintF(vsrc, "  tc%d = intc%d * srctexscale;\n", i, i);

    vsrc.AppendString("\n}");

    fsrc.AppendString("void main(void)\n{\n"
        "  vec4 color = vec4(0);\n");

    if (params.Mode & Filter_Shadow)
    {
        const char *color;
        if (params.Mode & BlurFilterParams::Mode_Highlight)
        {
            for (int i = 0; i < params.BoxTCs; i++)
            {
                SPrintF(fsrc, "  color.a += texture2D(tex, tc%d).a;\n", i*2);
                SPrintF(fsrc, "  color.r += texture2D(tex, tc%d).a;\n", i*2+1);
            }
            color = "(scolor * color.a + scolor2 * color.r)";
        }
        else
        {
            for (int i = 0; i < params.BoxTCs; i++)
                SPrintF(fsrc, "  color += texture2D(tex, tc%d);\n", i);
            color = "(scolor * color.a)";
        }

        SPrintF(fsrc,   "  color *= samples;\n");

        if (params.Mode & BlurFilterParams::Mode_HideObject)
            SPrintF(fsrc, "  gl_FragColor = %s;}\n", color);
        else
        {
            SPrintF(fsrc,   "  vec4 base = texture2D(srctex, tc%d);\n", params.TotalTCs-1);

            if (params.Mode & BlurFilterParams::Mode_Inner)
            {
                if (params.Mode & BlurFilterParams::Mode_Highlight)
                {
                    fsrc.AppendString("  color.ar = clamp((1.0 - color.ar) - (1.0 - color.ra) * 0.5, 0.0,1.0);\n");
                    fsrc.AppendString("  color = (scolor * (color.a) + scolor2 * (color.r)\n"
                        "           + base * (1.0 - color.a - color.r)) * base.a;\n");
                }
                else if (params.Mode & BlurFilterParams::Mode_Knockout)
                {
                    fsrc.AppendString("  color = scolor * (1-color.a) * base.a;\n");
                }
                else
                    fsrc.AppendString("  color = mix(scolor, base, color.a) * base.a;\n");

                fsrc.AppendString("  gl_FragColor = color * cxmul + cxadd * color.a;\n}");
            }
            else
            {
                SPrintF  (fsrc, "  color = %s * (1.0-base.a) + base;\n", color);

                if (params.Mode & BlurFilterParams::Mode_Knockout)
                {
                    fsrc.AppendString("  color *= (1.0 - base.a);\n"
                        "  gl_FragColor = color * cxmul + cxadd * color.a;\n}");
                }
                else
                    fsrc.AppendString("  gl_FragColor = color * cxmul + cxadd * color.a;\n}");
            }
        }
    }
    else
    {
        for (int i = 0; i < params.BoxTCs; i++)
            SPrintF(fsrc, "  color += texture2D(tex, tc%d);\n", i);
        SPrintF(fsrc,       "  color = color * samples;\n");
        fsrc.AppendString(    "  gl_FragColor = color * cxmul + cxadd * color.a;\n}\n");
    }

    const GLchar* pvsource = (const GLchar*)(vsrc.ToCStr());
    const GLchar* pfsource = (const GLchar*)(fsrc.ToCStr());

    //SF_DEBUG_MESSAGE2(1, "Blur shader\n%s\n\n%s\n\n", pvsource, pfsource);

    GLuint vp = glCreateShader(GL_VERTEX_SHADER);
    GLint result;
    glShaderSource(vp, 1, &pvsource, 0);
    glCompileShader(vp);
    glGetShaderiv(vp, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        GLchar msg[512];
        glGetShaderInfoLog(vp, sizeof(msg), 0, msg);
        SF_DEBUG_ERROR2(1, "%s: %s\n", pvsource, msg);
        glDeleteShader(vp);
        return 0;
    }
    GLint prog = glCreateProgram();
    glAttachShader(prog, vp);
    GLuint fp = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fp, 1, &pfsource, 0);
    glCompileShader(fp);
    glGetShaderiv(fp, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        GLchar msg[1512];
        glGetShaderInfoLog(fp, sizeof(msg), 0, msg);
        SF_DEBUG_ERROR2(1, "%s: %s\n", pfsource, msg);
        glDeleteShader(fp);
        glDeleteProgram(prog);
        prog = 0;
        return 0;
    }
    glAttachShader(prog, fp);

    glBindAttribLocation(prog, 0, "pos");
    for (int i = 0; i < params.TotalTCs; i++)
    {
        char tc[16];
        SPrintF(tc, "intc%d", i);
        glBindAttribLocation(prog, 1+i, tc);
    }

    glLinkProgram(prog);
    GLint fstatus, vstatus;
    glGetShaderiv(fp, GL_DELETE_STATUS, &fstatus);
    glGetShaderiv(vp, GL_DELETE_STATUS, &vstatus);
    if (fstatus == GL_FALSE)
        glDeleteShader(fp);
    if (vstatus == GL_FALSE)
        glDeleteShader(vp);
    glGetProgramiv(prog, GL_LINK_STATUS, &result);
    if (!result)
    {
        GLchar msg[512];
        glGetProgramInfoLog(prog, sizeof(msg), 0, msg);
        SF_DEBUG_ERROR3(1, "link:\n%s\n%s %s\n", pvsource, pfsource, msg);
        glDeleteProgram(prog);
        return 0;
    }

    BlurFilterShader* pfs = new BlurFilterShader;
    pfs->Shader = prog;

    pfs->mvp = glGetUniformLocation(prog, "mvp");
    pfs->cxmul = glGetUniformLocation(prog, "cxmul");
    pfs->cxadd = glGetUniformLocation(prog, "cxadd");
    pfs->tex[0] = glGetUniformLocation(prog, "tex");
    pfs->tex[1] = glGetUniformLocation(prog, "srctex");
    pfs->texscale[0] = glGetUniformLocation(prog, "texscale");
    pfs->texscale[1] = glGetUniformLocation(prog, "srctexscale");
    pfs->samples = glGetUniformLocation(prog, "samples");

    pfs->scolor[0] = glGetUniformLocation(prog, "scolor");
    pfs->scolor[1] = glGetUniformLocation(prog, "scolor2");

    BlurShaders.Add(params, pfs);
    return pfs;
}

}}}

#endif // !defined(SF_USE_GLES)
