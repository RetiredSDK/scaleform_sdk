/**************************************************************************

Filename    :   GL_Common.h
Content     :   
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_Render_GL_Common_H
#define INC_SF_Render_GL_Common_H

#include "Kernel/SF_Types.h"

#if defined(SF_OS_IPHONE)
    #ifdef SF_USE_GLES
        #include <OpenGLES/ES1/gl.h>
        #include <OpenGLES/ES1/glext.h>
    #else
        #ifndef SF_USE_GLES2
            #define SF_USE_GLES2
        #endif
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
    #endif
#elif defined(SF_USE_GLES)
    #include <GLES/gl.h>
    #if defined(SF_USE_EGL)
      #include <EGL/egl.h>
      #define SF_GL_RUNTIME_LINK(x) eglGetProcAddress(x)
    #else
      #define GL_GLEXT_PROTOTYPES
    #endif
    #include <GLES/glext.h>
#elif defined(SF_USE_GLES2)
    #include <GLES2/gl2.h>
    #if defined(SF_USE_EGL)
      #include <EGL/egl.h>
      #define SF_GL_RUNTIME_LINK(x) eglGetProcAddress(x)
    #else
      #define GL_GLEXT_PROTOTYPES
    #endif
    #include <GLES2/gl2ext.h>
#elif defined(SF_OS_WIN32)
    #include <windows.h>
    #include <gl/gl.h>
    #include "glext.h"
    #define SF_GL_RUNTIME_LINK(x) wglGetProcAddress(x)
#elif defined(SF_OS_MAC)
    #include <OpenGL/OpenGL.h>
    #define GL_GLEXT_PROTOTYPES
    #if defined(MAC_OS_X_VERSION_10_7) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7)
        #include <OpenGL/gl3.h>
        #include <OpenGL/gl3ext.h>
    #else
        #include <OpenGL/gl.h>
        #include <OpenGL/glext.h>
    #endif
#else

    // Use GLX to link gl extensions at runtime; comment out if not using GLX
    #define SF_GLX_RUNTIME_LINK

    #ifdef SF_GLX_RUNTIME_LINK
        #include <GL/glx.h>
        #include <GL/glxext.h>
        #define SF_GL_RUNTIME_LINK(x) glXGetProcAddressARB((const GLubyte*) (x))
    #else
        #define GL_GLEXT_PROTOTYPES
    #endif
    #include <GL/gl.h>
    #include <GL/glext.h>
#endif

// Helper macro for any GLES (vs. OpenGL).
#if defined(SF_USE_GLES) || defined(SF_USE_GLES2)
    #define SF_USE_GLES_ANY
#endif

#ifdef SF_GL_RUNTIME_LINK
    #if defined(SF_USE_GLES)
        #include "Render/GL/GLES11_Extensions.h"
    #elif defined(SF_USE_GLES2)
        #include "Render/GL/GLES_Extensions.h"
    #else
        #include "Render/GL/GL_Extensions.h"
    #endif
    #define GLEXT GetHAL()->
#else
  #define GLEXT
#endif

#if defined(GL_ES_VERSION_2_0) || defined(GL_VERSION_3_0)

    // ES 2.0 specific
    #if defined(GL_ES_VERSION_2_0)
        // Unsupported features
        #define GL_MIN                                  GL_FUNC_ADD
        #define GL_MAX                                  GL_FUNC_ADD

        // Built-in in GL2.x, extensions in ES2.0
        #define GL_WRITE_ONLY                           GL_WRITE_ONLY_OES
        #define glMapBuffer                             glMapBufferOES
        #define glUnmapBuffer                           glUnmapBufferOES


	    #define glProgramBinary                 glProgramBinaryOES
	    #define GL_PROGRAM_BINARY_LENGTH        GL_PROGRAM_BINARY_LENGTH_OES
	    #define glGetProgramBinary              glGetProgramBinaryOES
    #endif

    // GL 3.0+ specific
    #if !defined(GL_TEXTURE_COMPONENTS)
        #define GL_TEXTURE_COMPONENTS                   GL_TEXTURE_INTERNAL_FORMAT
    #endif

    #if !defined(GL_EXT_framebuffer_object)
        // Convert extension enums to standard ones
        #define GL_FRAMEBUFFER_EXT                          GL_FRAMEBUFFER
        #define GL_FRAMEBUFFER_BINDING_EXT                  GL_FRAMEBUFFER_BINDING
        #define GL_FRAMEBUFFER_COMPLETE_EXT                 GL_FRAMEBUFFER_COMPLETE
        #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT   GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE
        #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT   GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME
        #define GL_FRAMEBUFFER_COMPLETE_EXT                 GL_FRAMEBUFFER_COMPLETE
        #define GL_RENDERBUFFER_EXT                         GL_RENDERBUFFER
        #define GL_RENDERBUFFER_BINDING_EXT                 GL_RENDERBUFFER_BINDING
        #define GL_RENDERBUFFER_WIDTH_EXT                   GL_RENDERBUFFER_WIDTH
        #define GL_RENDERBUFFER_HEIGHT_EXT                  GL_RENDERBUFFER_HEIGHT
        #define GL_COLOR_ATTACHMENT0_EXT                    GL_COLOR_ATTACHMENT0
        #define GL_DEPTH_ATTACHMENT_EXT                     GL_DEPTH_ATTACHMENT
        #define GL_STENCIL_ATTACHMENT_EXT                   GL_STENCIL_ATTACHMENT

        #define glGenRenderbuffersEXT                       glGenRenderbuffers
        #define glBindRenderbufferEXT                       glBindRenderbuffer
        #define glRenderbufferStorageEXT                    glRenderbufferStorage
        #define glGenFramebuffersEXT                        glGenFramebuffers
        #define glBindFramebufferEXT                        glBindFramebuffer
        #define glFramebufferTexture2DEXT                   glFramebufferTexture2D
        #define glIsFramebufferEXT                          glIsFramebuffer
        #define glGetFramebufferAttachmentParameterivEXT    glGetFramebufferAttachmentParameteriv
        #define glDeleteRenderbuffersEXT                    glDeleteRenderbuffers
        #define glIsRenderbufferEXT                         glIsRenderbuffer
        #define glGetRenderbufferParameterivEXT             glGetRenderbufferParameteriv
        #define glFramebufferRenderbufferEXT                glFramebufferRenderbuffer
        #define glDeleteFramebuffersEXT                     glDeleteFramebuffers
        #define glCheckFramebufferStatusEXT                 glCheckFramebufferStatus
        #define glGenerateMipmapEXT                         glGenerateMipmap
    #endif // GL_EXT_framebuffer_object

    #if !defined(GL_BGRA) && defined(GL_BGRA_EXT)
        #define GL_BGRA GL_BGRA_EXT
    #endif
    #if !defined(GL_BGRA_EXT) && defined(GL_BGRA)
        #define GL_BGRA_EXT GL_BGRA
    #endif

    typedef char GLchar;

    // Some GLES 2.0 devices do support S3TC texture compression, however, the extensions aren't included 
    // in the glext.h on these platforms. Specifically, Tegra2 devices on Android. So, define the values 
    // here, if they are undefined, and check the extension at runtime to determine compatability.
    #ifndef GL_EXT_texture_compression_s3tc
        #define GL_EXT_texture_compression_s3tc                1
        #define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                   0x83F0
        #define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                  0x83F1
    #endif
    #ifndef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
        #define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT                  0x83F2
    #endif
    #ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
        #define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT                  0x83F3
    #endif

#elif defined(SF_USE_GLES)

    // Unsupported features
    #define GL_MIN                   0
    #define GL_MAX                   0
    #define GL_FUNC_ADD              GL_ADD
    #define GL_FUNC_REVERSE_SUBTRACT 0

    // Convert extension enums to standard ones
    #define GL_WRITE_ONLY GL_WRITE_ONLY_OES
    #define glMapBuffer glMapBufferOES
    #define glUnmapBuffer glUnmapBufferOES
    #define glGenerateMipmapEXT glGenerateMipmapOES

#else // SF_USE_GLES

    // Statically linking, with possible extensions.
    #if !defined SF_GL_RUNTIME_LINK
        #if defined(GL_APPLE_vertex_array_object) && GL_APPLE_vertex_array_object
            #define glBindVertexArray                           glBindVertexArrayAPPLE
            #define glGenVertexArrays                           glGenVertexArraysAPPLE
            #define glDeleteVertexArrays                        glDeleteVertexArraysAPPLE
        #endif

        #if defined(GL_ARB_instanced_arrays) && GL_ARB_instanced_arrays
            #define glDrawElementsInstanced                     glDrawElementsInstancedARB
        #endif
    #endif

#endif

#endif
