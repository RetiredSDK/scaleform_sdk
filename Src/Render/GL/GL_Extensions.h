/**********************************************************************

Filename    :   GL_Extensions.h
Content     :   GL  extension header.
Created     :   Automatically generated.
Authors     :   Extensions.pl

Copyright   :   (c) 2001-2011 Scaleform Corp. All Rights Reserved.

Licensees may use this file in accordance with the valid Scaleform
Commercial License Agreement provided with the software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING 
THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR ANY PURPOSE.

***********************************************************************/

#ifndef INC_SF_Render_GL_Extensions_H
#define INC_SF_Render_GL_Extensions_H

#include "Kernel/SF_Debug.h"
#include "Render/GL/GL_Common.h"

namespace Scaleform { namespace Render { namespace GL {

class Extensions
{
    PFNGLISRENDERBUFFEREXTPROC                      p_glIsRenderbufferEXT;
    PFNGLGENERATEMIPMAPEXTPROC                      p_glGenerateMipmapEXT;
    PFNGLCREATESHADERPROC                           p_glCreateShader;
    PFNGLCOMPRESSEDTEXIMAGE2DPROC                   p_glCompressedTexImage2D;
    #if defined(GL_ARB_get_program_binary)
    PFNGLPROGRAMBINARYPROC                          p_glProgramBinary;
    #endif
    PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC              p_glCheckFramebufferStatusEXT;
    PFNGLBLENDEQUATIONPROC                          p_glBlendEquation;
    PFNGLBINDATTRIBLOCATIONPROC                     p_glBindAttribLocation;
    PFNGLCOMPILESHADERPROC                          p_glCompileShader;
    PFNGLATTACHSHADERPROC                           p_glAttachShader;
    PFNGLGETATTRIBLOCATIONPROC                      p_glGetAttribLocation;
    PFNGLBLENDFUNCSEPARATEPROC                      p_glBlendFuncSeparate;
    PFNGLGETSHADERIVPROC                            p_glGetShaderiv;
    #if defined(GL_EXT_gpu_shader4)
    PFNGLBINDFRAGDATALOCATIONPROC                   p_glBindFragDataLocation;
    #endif
    #if defined(GL_GREMEDY_string_marker)
    PFNGLSTRINGMARKERGREMEDYPROC                    p_glStringMarkerGREMEDY;
    #endif
    PFNGLDELETEFRAMEBUFFERSEXTPROC                  p_glDeleteFramebuffersEXT;
    PFNGLCREATEPROGRAMPROC                          p_glCreateProgram;
    PFNGLUNIFORM1FPROC                              p_glUniform1f;
    PFNGLBINDRENDERBUFFEREXTPROC                    p_glBindRenderbufferEXT;
    PFNGLGENRENDERBUFFERSEXTPROC                    p_glGenRenderbuffersEXT;
    PFNGLRENDERBUFFERSTORAGEEXTPROC                 p_glRenderbufferStorageEXT;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC p_glGetFramebufferAttachmentParameterivEXT;
    #if defined(GL_ARB_vertex_array_object)
    PFNGLGENVERTEXARRAYSPROC                        p_glGenVertexArrays;
    #endif
    PFNGLUNIFORM4FVPROC                             p_glUniform4fv;
    PFNGLUNMAPBUFFERPROC                            p_glUnmapBuffer;
    PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC             p_glFramebufferRenderbufferEXT;
    PFNGLISFRAMEBUFFEREXTPROC                       p_glIsFramebufferEXT;
    PFNGLUNIFORM2FVPROC                             p_glUniform2fv;
    PFNGLFRAMEBUFFERTEXTURE2DEXTPROC                p_glFramebufferTexture2DEXT;
    PFNGLMAPBUFFERPROC                              p_glMapBuffer;
    #if defined(GL_ARB_draw_instanced)
    PFNGLDRAWELEMENTSINSTANCEDPROC                  p_glDrawElementsInstanced;
    #endif
    PFNGLGENBUFFERSPROC                             p_glGenBuffers;
    PFNGLBUFFERDATAPROC                             p_glBufferData;
    PFNGLLINKPROGRAMPROC                            p_glLinkProgram;
    PFNGLACTIVETEXTUREPROC                          p_glActiveTexture;
    PFNGLGETPROGRAMIVPROC                           p_glGetProgramiv;
    PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC          p_glGetRenderbufferParameterivEXT;
    PFNGLUNIFORM1FVPROC                             p_glUniform1fv;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC               p_glDisableVertexAttribArray;
    PFNGLUNIFORM1IVPROC                             p_glUniform1iv;
    #if defined(GL_EXT_gpu_shader4)
    PFNGLGETFRAGDATALOCATIONPROC                    p_glGetFragDataLocation;
    #endif
    PFNGLGENFRAMEBUFFERSEXTPROC                     p_glGenFramebuffersEXT;
    #if defined(GL_ARB_get_program_binary)
    PFNGLGETPROGRAMBINARYPROC                       p_glGetProgramBinary;
    #endif
    #if defined(GL_ARB_get_program_binary)
    PFNGLPROGRAMPARAMETERIPROC                      p_glProgramParameteri;
    #endif
    PFNGLUNIFORM1IPROC                              p_glUniform1i;
    PFNGLDELETERENDERBUFFERSEXTPROC                 p_glDeleteRenderbuffersEXT;
    #if defined(GL_ARB_vertex_array_object)
    PFNGLDELETEVERTEXARRAYSPROC                     p_glDeleteVertexArrays;
    #endif
    PFNGLBUFFERSUBDATAPROC                          p_glBufferSubData;
    PFNGLDELETEPROGRAMPROC                          p_glDeleteProgram;
    #if defined(GL_VERSION_3_0)
    PFNGLGETSTRINGIPROC                             p_glGetStringi;
    #endif
    PFNGLUSEPROGRAMPROC                             p_glUseProgram;
    PFNGLBINDFRAMEBUFFEREXTPROC                     p_glBindFramebufferEXT;
    PFNGLGETPROGRAMINFOLOGPROC                      p_glGetProgramInfoLog;
    PFNGLDELETESHADERPROC                           p_glDeleteShader;
    PFNGLDELETEBUFFERSPROC                          p_glDeleteBuffers;
    PFNGLSHADERSOURCEPROC                           p_glShaderSource;
    PFNGLBINDBUFFERPROC                             p_glBindBuffer;
    PFNGLGETSHADERINFOLOGPROC                       p_glGetShaderInfoLog;
    PFNGLUNIFORMMATRIX4FVPROC                       p_glUniformMatrix4fv;
    PFNGLENABLEVERTEXATTRIBARRAYPROC                p_glEnableVertexAttribArray;
    PFNGLVERTEXATTRIBPOINTERPROC                    p_glVertexAttribPointer;
    PFNGLUNIFORM2FPROC                              p_glUniform2f;
    PFNGLGETUNIFORMLOCATIONPROC                     p_glGetUniformLocation;
    PFNGLUNIFORM3FVPROC                             p_glUniform3fv;
    #if defined(GL_ARB_vertex_array_object)
    PFNGLBINDVERTEXARRAYPROC                        p_glBindVertexArray;
    #endif
public:
    bool Init();
    
    class ScopedGLErrorCheck
    {
    public:
        ScopedGLErrorCheck(const char* func) : FuncName(func)
        {
        #ifdef SF_BUILD_DEBUG
            GLenum error = glGetError(); SF_UNUSED(error);
            SF_DEBUG_ASSERT2(!error, "GL error before function %s (error code = %d)\n", FuncName, error );
        #endif
        }
        ~ScopedGLErrorCheck()
        {
        #ifdef SF_BUILD_DEBUG
            GLenum error = glGetError(); SF_UNUSED(error);
            SF_DEBUG_ASSERT2(!error, "GL error after function %s (error code = %d)\n", FuncName, error );
        #endif
        }
    private:
        const char * FuncName;
    };
    GLboolean glIsRenderbufferEXT(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glIsRenderbufferEXT(a0);
    }

    void glGenerateMipmapEXT(GLenum a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGenerateMipmapEXT(a0);
    }

    GLuint glCreateShader(GLenum a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glCreateShader(a0);
    }

    void glCompressedTexImage2D(GLenum a0, GLint a1, GLenum a2, GLsizei a3, GLsizei a4, GLint a5, GLsizei a6, const GLvoid * a7)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glCompressedTexImage2D(a0, a1, a2, a3, a4, a5, a6, a7);
    }

    void glProgramBinary(GLuint a0, GLenum a1, const GLvoid * a2, GLsizei a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_ARB_get_program_binary)
        p_glProgramBinary(a0, a1, a2, a3);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glProgramBinary extension function (#if defined(GL_ARB_get_program_binary))");
        #endif
    }

    #if defined(GL_ARB_get_program_binary)
    bool Has_glProgramBinary() const { return p_glProgramBinary != 0; }

    #else
    bool Has_glProgramBinary() const { return false; }
    #endif

    GLenum glCheckFramebufferStatusEXT(GLenum a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glCheckFramebufferStatusEXT(a0);
    }

    void glBlendEquation(GLenum a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBlendEquation(a0);
    }

    void glBindAttribLocation(GLuint a0, GLuint a1, const GLchar * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBindAttribLocation(a0, a1, a2);
    }

    void glCompileShader(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glCompileShader(a0);
    }

    void glAttachShader(GLuint a0, GLuint a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glAttachShader(a0, a1);
    }

    GLint glGetAttribLocation(GLuint a0, const GLchar * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glGetAttribLocation(a0, a1);
    }

    void glBlendFuncSeparate(GLenum a0, GLenum a1, GLenum a2, GLenum a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBlendFuncSeparate(a0, a1, a2, a3);
    }

    void glGetShaderiv(GLuint a0, GLenum a1, GLint * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGetShaderiv(a0, a1, a2);
    }

    void glBindFragDataLocation(GLuint a0, GLuint a1, const GLchar * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_EXT_gpu_shader4)
        p_glBindFragDataLocation(a0, a1, a2);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glBindFragDataLocation extension function (#if defined(GL_EXT_gpu_shader4))");
        #endif
    }

    #if defined(GL_EXT_gpu_shader4)
    bool Has_glBindFragDataLocation() const { return p_glBindFragDataLocation != 0; }

    #else
    bool Has_glBindFragDataLocation() const { return false; }
    #endif

    void glStringMarkerGREMEDY(GLsizei a0, const GLvoid * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_GREMEDY_string_marker)
        p_glStringMarkerGREMEDY(a0, a1);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glStringMarkerGREMEDY extension function (#if defined(GL_GREMEDY_string_marker))");
        #endif
    }

    #if defined(GL_GREMEDY_string_marker)
    bool Has_glStringMarkerGREMEDY() const { return p_glStringMarkerGREMEDY != 0; }

    #else
    bool Has_glStringMarkerGREMEDY() const { return false; }
    #endif

    void glDeleteFramebuffersEXT(GLsizei a0, const GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glDeleteFramebuffersEXT(a0, a1);
    }

    GLuint glCreateProgram()
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glCreateProgram();
    }

    void glUniform1f(GLint a0, GLfloat a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform1f(a0, a1);
    }

    void glBindRenderbufferEXT(GLenum a0, GLuint a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBindRenderbufferEXT(a0, a1);
    }

    void glGenRenderbuffersEXT(GLsizei a0, GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGenRenderbuffersEXT(a0, a1);
    }

    void glRenderbufferStorageEXT(GLenum a0, GLenum a1, GLsizei a2, GLsizei a3)
    {
        p_glRenderbufferStorageEXT(a0, a1, a2, a3);
    }

    void glGetFramebufferAttachmentParameterivEXT(GLenum a0, GLenum a1, GLenum a2, GLint * a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGetFramebufferAttachmentParameterivEXT(a0, a1, a2, a3);
    }

    void glGenVertexArrays(GLsizei a0, GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_ARB_vertex_array_object)
        p_glGenVertexArrays(a0, a1);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glGenVertexArrays extension function (#if defined(GL_ARB_vertex_array_object))");
        #endif
    }

    #if defined(GL_ARB_vertex_array_object)
    bool Has_glGenVertexArrays() const { return p_glGenVertexArrays != 0; }

    #else
    bool Has_glGenVertexArrays() const { return false; }
    #endif

    void glUniform4fv(GLint a0, GLsizei a1, const GLfloat * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform4fv(a0, a1, a2);
    }

    GLboolean glUnmapBuffer(GLenum a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glUnmapBuffer(a0);
    }

    void glFramebufferRenderbufferEXT(GLenum a0, GLenum a1, GLenum a2, GLuint a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glFramebufferRenderbufferEXT(a0, a1, a2, a3);
    }

    GLboolean glIsFramebufferEXT(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glIsFramebufferEXT(a0);
    }

    void glUniform2fv(GLint a0, GLsizei a1, const GLfloat * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform2fv(a0, a1, a2);
    }

    void glFramebufferTexture2DEXT(GLenum a0, GLenum a1, GLenum a2, GLuint a3, GLint a4)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glFramebufferTexture2DEXT(a0, a1, a2, a3, a4);
    }

    GLvoid* glMapBuffer(GLenum a0, GLenum a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glMapBuffer(a0, a1);
    }

    void glDrawElementsInstanced(GLenum a0, GLsizei a1, GLenum a2, const GLvoid * a3, GLsizei a4)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_ARB_draw_instanced)
        p_glDrawElementsInstanced(a0, a1, a2, a3, a4);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glDrawElementsInstanced extension function (#if defined(GL_ARB_draw_instanced))");
        #endif
    }

    #if defined(GL_ARB_draw_instanced)
    bool Has_glDrawElementsInstanced() const { return p_glDrawElementsInstanced != 0; }

    #else
    bool Has_glDrawElementsInstanced() const { return false; }
    #endif

    void glGenBuffers(GLsizei a0, GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGenBuffers(a0, a1);
    }

    void glBufferData(GLenum a0, GLsizeiptr a1, const GLvoid * a2, GLenum a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBufferData(a0, a1, a2, a3);
    }

    void glLinkProgram(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glLinkProgram(a0);
    }

    void glActiveTexture(GLenum a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glActiveTexture(a0);
    }

    void glGetProgramiv(GLuint a0, GLenum a1, GLint * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGetProgramiv(a0, a1, a2);
    }

    void glGetRenderbufferParameterivEXT(GLenum a0, GLenum a1, GLint * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGetRenderbufferParameterivEXT(a0, a1, a2);
    }

    void glUniform1fv(GLint a0, GLsizei a1, const GLfloat * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform1fv(a0, a1, a2);
    }

    void glDisableVertexAttribArray(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glDisableVertexAttribArray(a0);
    }

    void glUniform1iv(GLint a0, GLsizei a1, const GLint * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform1iv(a0, a1, a2);
    }

    GLint glGetFragDataLocation(GLuint a0, const GLchar * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_EXT_gpu_shader4)
        return p_glGetFragDataLocation(a0, a1);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glGetFragDataLocation extension function (#if defined(GL_EXT_gpu_shader4))");
        return GLint(0);
        #endif
    }

    #if defined(GL_EXT_gpu_shader4)
    bool Has_glGetFragDataLocation() const { return p_glGetFragDataLocation != 0; }

    #else
    bool Has_glGetFragDataLocation() const { return false; }
    #endif

    void glGenFramebuffersEXT(GLsizei a0, GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGenFramebuffersEXT(a0, a1);
    }

    void glGetProgramBinary(GLuint a0, GLsizei a1, GLsizei * a2, GLenum * a3, GLvoid * a4)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_ARB_get_program_binary)
        p_glGetProgramBinary(a0, a1, a2, a3, a4);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glGetProgramBinary extension function (#if defined(GL_ARB_get_program_binary))");
        #endif
    }

    #if defined(GL_ARB_get_program_binary)
    bool Has_glGetProgramBinary() const { return p_glGetProgramBinary != 0; }

    #else
    bool Has_glGetProgramBinary() const { return false; }
    #endif

    void glProgramParameteri(GLuint a0, GLenum a1, GLint a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_ARB_get_program_binary)
        p_glProgramParameteri(a0, a1, a2);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glProgramParameteri extension function (#if defined(GL_ARB_get_program_binary))");
        #endif
    }

    #if defined(GL_ARB_get_program_binary)
    bool Has_glProgramParameteri() const { return p_glProgramParameteri != 0; }

    #else
    bool Has_glProgramParameteri() const { return false; }
    #endif

    void glUniform1i(GLint a0, GLint a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform1i(a0, a1);
    }

    void glDeleteRenderbuffersEXT(GLsizei a0, const GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glDeleteRenderbuffersEXT(a0, a1);
    }

    void glDeleteVertexArrays(GLsizei a0, const GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_ARB_vertex_array_object)
        p_glDeleteVertexArrays(a0, a1);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glDeleteVertexArrays extension function (#if defined(GL_ARB_vertex_array_object))");
        #endif
    }

    #if defined(GL_ARB_vertex_array_object)
    bool Has_glDeleteVertexArrays() const { return p_glDeleteVertexArrays != 0; }

    #else
    bool Has_glDeleteVertexArrays() const { return false; }
    #endif

    void glBufferSubData(GLenum a0, GLintptr a1, GLsizeiptr a2, const GLvoid * a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBufferSubData(a0, a1, a2, a3);
    }

    void glDeleteProgram(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glDeleteProgram(a0);
    }

    const GLubyte * glGetStringi(GLenum a0, GLuint a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_VERSION_3_0)
        return p_glGetStringi(a0, a1);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glGetStringi extension function (#if defined(GL_VERSION_3_0))");
        return const GLubyte *(0);
        #endif
    }

    #if defined(GL_VERSION_3_0)
    bool Has_glGetStringi() const { return p_glGetStringi != 0; }

    #else
    bool Has_glGetStringi() const { return false; }
    #endif

    void glUseProgram(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUseProgram(a0);
    }

    void glBindFramebufferEXT(GLenum a0, GLuint a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBindFramebufferEXT(a0, a1);
    }

    void glGetProgramInfoLog(GLuint a0, GLsizei a1, GLsizei * a2, GLchar * a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGetProgramInfoLog(a0, a1, a2, a3);
    }

    void glDeleteShader(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glDeleteShader(a0);
    }

    void glDeleteBuffers(GLsizei a0, const GLuint * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glDeleteBuffers(a0, a1);
    }

    void glShaderSource(GLuint a0, GLsizei a1, const GLchar* * a2, const GLint * a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glShaderSource(a0, a1, a2, a3);
    }

    void glBindBuffer(GLenum a0, GLuint a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glBindBuffer(a0, a1);
    }

    void glGetShaderInfoLog(GLuint a0, GLsizei a1, GLsizei * a2, GLchar * a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glGetShaderInfoLog(a0, a1, a2, a3);
    }

    void glUniformMatrix4fv(GLint a0, GLsizei a1, GLboolean a2, const GLfloat * a3)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniformMatrix4fv(a0, a1, a2, a3);
    }

    void glEnableVertexAttribArray(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glEnableVertexAttribArray(a0);
    }

    void glVertexAttribPointer(GLuint a0, GLint a1, GLenum a2, GLboolean a3, GLsizei a4, const GLvoid * a5)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glVertexAttribPointer(a0, a1, a2, a3, a4, a5);
    }

    void glUniform2f(GLint a0, GLfloat a1, GLfloat a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform2f(a0, a1, a2);
    }

    GLint glGetUniformLocation(GLuint a0, const GLchar * a1)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        return p_glGetUniformLocation(a0, a1);
    }

    void glUniform3fv(GLint a0, GLsizei a1, const GLfloat * a2)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        p_glUniform3fv(a0, a1, a2);
    }

    void glBindVertexArray(GLuint a0)
    {
        ScopedGLErrorCheck check(__FUNCTION__);
        #if defined(GL_ARB_vertex_array_object)
        p_glBindVertexArray(a0);
        #else
        SF_DEBUG_ASSERT(1, "glext.h did not contain required preprocessor defines to "
                           "use the glBindVertexArray extension function (#if defined(GL_ARB_vertex_array_object))");
        #endif
    }

    #if defined(GL_ARB_vertex_array_object)
    bool Has_glBindVertexArray() const { return p_glBindVertexArray != 0; }

    #else
    bool Has_glBindVertexArray() const { return false; }
    #endif

};

}}}
#endif
