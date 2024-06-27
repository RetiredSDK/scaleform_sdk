/**********************************************************************

Filename    :   GL_ExtensionMacros.h
Content     :   GL  extension macros header.
Created     :   Automatically generated.
Authors     :   Extensions.pl

Copyright   :   (c) 2001-2011 Scaleform Corp. All Rights Reserved.

Licensees may use this file in accordance with the valid Scaleform
Commercial License Agreement provided with the software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING 
THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR ANY PURPOSE.

***********************************************************************/

#ifndef INC_SF_Render_GL_ExtensionMacros_H
#define INC_SF_Render_GL_ExtensionMacros_H
#include "Render/GL/GL_HAL.h"

#ifdef SF_GL_RUNTIME_LINK

    #define glIsRenderbufferEXT GetHAL()->glIsRenderbufferEXT
    #define glGenerateMipmapEXT GetHAL()->glGenerateMipmapEXT
    #define glCreateShader GetHAL()->glCreateShader
    #define glCompressedTexImage2D GetHAL()->glCompressedTexImage2D
    #define glProgramBinary GetHAL()->glProgramBinary
    #define Has_glProgramBinary GetHAL()->Has_glProgramBinary
    #define glCheckFramebufferStatusEXT GetHAL()->glCheckFramebufferStatusEXT
    #define glBlendEquation GetHAL()->glBlendEquation
    #define glBindAttribLocation GetHAL()->glBindAttribLocation
    #define glCompileShader GetHAL()->glCompileShader
    #define glAttachShader GetHAL()->glAttachShader
    #define glGetAttribLocation GetHAL()->glGetAttribLocation
    #define glBlendFuncSeparate GetHAL()->glBlendFuncSeparate
    #define glGetShaderiv GetHAL()->glGetShaderiv
    #define glBindFragDataLocation GetHAL()->glBindFragDataLocation
    #define Has_glBindFragDataLocation GetHAL()->Has_glBindFragDataLocation
    #define glStringMarkerGREMEDY GetHAL()->glStringMarkerGREMEDY
    #define Has_glStringMarkerGREMEDY GetHAL()->Has_glStringMarkerGREMEDY
    #define glDeleteFramebuffersEXT GetHAL()->glDeleteFramebuffersEXT
    #define glCreateProgram GetHAL()->glCreateProgram
    #define glUniform1f GetHAL()->glUniform1f
    #define glBindRenderbufferEXT GetHAL()->glBindRenderbufferEXT
    #define glGenRenderbuffersEXT GetHAL()->glGenRenderbuffersEXT
    #define glRenderbufferStorageEXT GetHAL()->glRenderbufferStorageEXT
    #define glGetFramebufferAttachmentParameterivEXT GetHAL()->glGetFramebufferAttachmentParameterivEXT
    #define glGenVertexArrays GetHAL()->glGenVertexArrays
    #define Has_glGenVertexArrays GetHAL()->Has_glGenVertexArrays
    #define glUniform4fv GetHAL()->glUniform4fv
    #define glUnmapBuffer GetHAL()->glUnmapBuffer
    #define glFramebufferRenderbufferEXT GetHAL()->glFramebufferRenderbufferEXT
    #define glIsFramebufferEXT GetHAL()->glIsFramebufferEXT
    #define glUniform2fv GetHAL()->glUniform2fv
    #define glFramebufferTexture2DEXT GetHAL()->glFramebufferTexture2DEXT
    #define glMapBuffer GetHAL()->glMapBuffer
    #define glDrawElementsInstanced GetHAL()->glDrawElementsInstanced
    #define Has_glDrawElementsInstanced GetHAL()->Has_glDrawElementsInstanced
    #define glGenBuffers GetHAL()->glGenBuffers
    #define glBufferData GetHAL()->glBufferData
    #define glLinkProgram GetHAL()->glLinkProgram
    #define glActiveTexture GetHAL()->glActiveTexture
    #define glGetProgramiv GetHAL()->glGetProgramiv
    #define glGetRenderbufferParameterivEXT GetHAL()->glGetRenderbufferParameterivEXT
    #define glUniform1fv GetHAL()->glUniform1fv
    #define glDisableVertexAttribArray GetHAL()->glDisableVertexAttribArray
    #define glUniform1iv GetHAL()->glUniform1iv
    #define glGetFragDataLocation GetHAL()->glGetFragDataLocation
    #define Has_glGetFragDataLocation GetHAL()->Has_glGetFragDataLocation
    #define glGenFramebuffersEXT GetHAL()->glGenFramebuffersEXT
    #define glGetProgramBinary GetHAL()->glGetProgramBinary
    #define Has_glGetProgramBinary GetHAL()->Has_glGetProgramBinary
    #define glProgramParameteri GetHAL()->glProgramParameteri
    #define Has_glProgramParameteri GetHAL()->Has_glProgramParameteri
    #define glUniform1i GetHAL()->glUniform1i
    #define glDeleteRenderbuffersEXT GetHAL()->glDeleteRenderbuffersEXT
    #define glDeleteVertexArrays GetHAL()->glDeleteVertexArrays
    #define Has_glDeleteVertexArrays GetHAL()->Has_glDeleteVertexArrays
    #define glBufferSubData GetHAL()->glBufferSubData
    #define glDeleteProgram GetHAL()->glDeleteProgram
    #define glGetStringi GetHAL()->glGetStringi
    #define Has_glGetStringi GetHAL()->Has_glGetStringi
    #define glUseProgram GetHAL()->glUseProgram
    #define glBindFramebufferEXT GetHAL()->glBindFramebufferEXT
    #define glGetProgramInfoLog GetHAL()->glGetProgramInfoLog
    #define glDeleteShader GetHAL()->glDeleteShader
    #define glDeleteBuffers GetHAL()->glDeleteBuffers
    #define glShaderSource GetHAL()->glShaderSource
    #define glBindBuffer GetHAL()->glBindBuffer
    #define glGetShaderInfoLog GetHAL()->glGetShaderInfoLog
    #define glUniformMatrix4fv GetHAL()->glUniformMatrix4fv
    #define glEnableVertexAttribArray GetHAL()->glEnableVertexAttribArray
    #define glVertexAttribPointer GetHAL()->glVertexAttribPointer
    #define glUniform2f GetHAL()->glUniform2f
    #define glGetUniformLocation GetHAL()->glGetUniformLocation
    #define glUniform3fv GetHAL()->glUniform3fv
    #define glBindVertexArray GetHAL()->glBindVertexArray
    #define Has_glBindVertexArray GetHAL()->Has_glBindVertexArray

#else
    inline bool Has_glProgramBinary() { return true; }
    inline bool Has_glBindFragDataLocation() { return true; }
    inline bool Has_glStringMarkerGREMEDY() { return true; }
    inline bool Has_glGenVertexArrays() { return true; }
    inline bool Has_glDrawElementsInstanced() { return true; }
    inline bool Has_glGetFragDataLocation() { return true; }
    inline bool Has_glGetProgramBinary() { return true; }
    inline bool Has_glProgramParameteri() { return true; }
    inline bool Has_glDeleteVertexArrays() { return true; }
    inline bool Has_glGetStringi() { return true; }
    inline bool Has_glBindVertexArray() { return true; }

#endif
#endif
