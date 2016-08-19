//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// FunctionsGL.h: Defines the FuntionsGL class to contain loaded GL functions

#ifndef LIBANGLE_RENDERER_GL_FUNCTIONSGL_H_
#define LIBANGLE_RENDERER_GL_FUNCTIONSGL_H_

#include "common/debug.h"
#include "libANGLE/Version.h"
#include "libANGLE/renderer/gl/functionsgl_enums.h"
#include "libANGLE/renderer/gl/functionsgl_typedefs.h"

namespace rx
{

enum StandardGL
{
    STANDARD_GL_DESKTOP,
    STANDARD_GL_ES,
};

class FunctionsGL
{
  public:
    FunctionsGL();
    virtual ~FunctionsGL();

    void initialize();

    // Version information
    gl::Version version;
    StandardGL standard;
    GLint profile;
    bool isAtLeastGL(const gl::Version &glVersion) const;
    bool isAtLeastGLES(const gl::Version &glesVersion) const;

    // Extensions
    std::vector<std::string> extensions;
    bool hasExtension(const std::string &ext) const;
    bool hasGLExtension(const std::string &ext) const;
    bool hasGLESExtension(const std::string &ext) const;

    // Entry Points
    // 1.0
    PFNGLBLENDFUNCPROC blendFunc;
    PFNGLCLEARPROC clear;
    PFNGLCLEARCOLORPROC clearColor;
    PFNGLCLEARDEPTHPROC clearDepth;
    PFNGLCLEARSTENCILPROC clearStencil;
    PFNGLCOLORMASKPROC colorMask;
    PFNGLCULLFACEPROC cullFace;
    PFNGLDEPTHFUNCPROC depthFunc;
    PFNGLDEPTHMASKPROC depthMask;
    PFNGLDEPTHRANGEPROC depthRange;
    PFNGLDISABLEPROC disable;
    PFNGLDRAWBUFFERPROC drawBuffer;
    PFNGLENABLEPROC enable;
    PFNGLFINISHPROC finish;
    PFNGLFLUSHPROC flush;
    PFNGLFRONTFACEPROC frontFace;
    PFNGLGETBOOLEANVPROC getBooleanv;
    PFNGLGETDOUBLEVPROC getDoublev;
    PFNGLGETERRORPROC getError;
    PFNGLGETFLOATVPROC getFloatv;
    PFNGLGETINTEGERVPROC getIntegerv;
    PFNGLGETSTRINGPROC getString;
    PFNGLGETTEXIMAGEPROC getTexImage;
    PFNGLGETTEXLEVELPARAMETERFVPROC getTexLevelParameterfv;
    PFNGLGETTEXLEVELPARAMETERIVPROC getTexLevelParameteriv;
    PFNGLGETTEXPARAMETERFVPROC getTexParameterfv;
    PFNGLGETTEXPARAMETERIVPROC getTexParameteriv;
    PFNGLHINTPROC hint;
    PFNGLISENABLEDPROC isEnabled;
    PFNGLLINEWIDTHPROC lineWidth;
    PFNGLLOGICOPPROC logicOp;
    PFNGLPIXELSTOREFPROC pixelStoref;
    PFNGLPIXELSTOREIPROC pixelStorei;
    PFNGLPOINTSIZEPROC pointSize;
    PFNGLPOLYGONMODEPROC polygonMode;
    PFNGLREADBUFFERPROC readBuffer;
    PFNGLREADPIXELSPROC readPixels;
    PFNGLSCISSORPROC scissor;
    PFNGLSTENCILFUNCPROC stencilFunc;
    PFNGLSTENCILMASKPROC stencilMask;
    PFNGLSTENCILOPPROC stencilOp;
    PFNGLTEXIMAGE1DPROC texImage1D;
    PFNGLTEXIMAGE2DPROC texImage2D;
    PFNGLTEXPARAMETERFPROC texParameterf;
    PFNGLTEXPARAMETERFVPROC texParameterfv;
    PFNGLTEXPARAMETERIPROC texParameteri;
    PFNGLTEXPARAMETERIVPROC texParameteriv;
    PFNGLVIEWPORTPROC viewport;

    // 1.1
    PFNGLBINDTEXTUREPROC bindTexture;
    PFNGLCOPYTEXIMAGE1DPROC copyTexImage1D;
    PFNGLCOPYTEXIMAGE2DPROC copyTexImage2D;
    PFNGLCOPYTEXSUBIMAGE1DPROC copyTexSubImage1D;
    PFNGLCOPYTEXSUBIMAGE2DPROC copyTexSubImage2D;
    PFNGLDELETETEXTURESPROC deleteTextures;
    PFNGLDRAWARRAYSPROC drawArrays;
    PFNGLDRAWELEMENTSPROC drawElements;
    PFNGLGENTEXTURESPROC genTextures;
    PFNGLISTEXTUREPROC isTexture;
    PFNGLPOLYGONOFFSETPROC polygonOffset;
    PFNGLTEXSUBIMAGE1DPROC texSubImage1D;
    PFNGLTEXSUBIMAGE2DPROC texSubImage2D;

    // 1.2
    PFNGLBLENDCOLORPROC blendColor;
    PFNGLBLENDEQUATIONPROC blendEquation;
    PFNGLCOPYTEXSUBIMAGE3DPROC copyTexSubImage3D;
    PFNGLDRAWRANGEELEMENTSPROC drawRangeElements;
    PFNGLTEXIMAGE3DPROC texImage3D;
    PFNGLTEXSUBIMAGE3DPROC texSubImage3D;

    // 1.2 Extensions
    PFNGLDELETEFENCESNVPROC deleteFencesNV;
    PFNGLGENFENCESNVPROC genFencesNV;
    PFNGLISFENCENVPROC isFenceNV;
    PFNGLTESTFENCENVPROC testFenceNV;
    PFNGLGETFENCEIVNVPROC getFenceivNV;
    PFNGLFINISHFENCENVPROC finishFenceNV;
    PFNGLSETFENCENVPROC setFenceNV;

    // 1.3
    PFNGLACTIVETEXTUREPROC activeTexture;
    PFNGLCOMPRESSEDTEXIMAGE1DPROC compressedTexImage1D;
    PFNGLCOMPRESSEDTEXIMAGE2DPROC compressedTexImage2D;
    PFNGLCOMPRESSEDTEXIMAGE3DPROC compressedTexImage3D;
    PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC compressedTexSubImage1D;
    PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC compressedTexSubImage2D;
    PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC compressedTexSubImage3D;
    PFNGLGETCOMPRESSEDTEXIMAGEPROC getCompressedTexImage;
    PFNGLSAMPLECOVERAGEPROC sampleCoverage;

    // 1.4
    PFNGLBLENDFUNCSEPARATEPROC blendFuncSeparate;
    PFNGLMULTIDRAWARRAYSPROC multiDrawArrays;
    PFNGLMULTIDRAWELEMENTSPROC multiDrawElements;
    PFNGLPOINTPARAMETERFPROC pointParameterf;
    PFNGLPOINTPARAMETERFVPROC pointParameterfv;
    PFNGLPOINTPARAMETERIPROC pointParameteri;
    PFNGLPOINTPARAMETERIVPROC pointParameteriv;

    // 1.5
    PFNGLBEGINQUERYPROC beginQuery;
    PFNGLBINDBUFFERPROC bindBuffer;
    PFNGLBUFFERDATAPROC bufferData;
    PFNGLBUFFERSUBDATAPROC bufferSubData;
    PFNGLDELETEBUFFERSPROC deleteBuffers;
    PFNGLDELETEQUERIESPROC deleteQueries;
    PFNGLENDQUERYPROC endQuery;
    PFNGLGENBUFFERSPROC genBuffers;
    PFNGLGENQUERIESPROC genQueries;
    PFNGLGETBUFFERPARAMETERIVPROC getBufferParameteriv;
    PFNGLGETBUFFERPOINTERVPROC getBufferPointerv;
    PFNGLGETBUFFERSUBDATAPROC getBufferSubData;
    PFNGLGETQUERYOBJECTIVPROC getQueryObjectiv;
    PFNGLGETQUERYOBJECTUIVPROC getQueryObjectuiv;
    PFNGLGETQUERYIVPROC getQueryiv;
    PFNGLISBUFFERPROC isBuffer;
    PFNGLISQUERYPROC isQuery;
    PFNGLMAPBUFFERPROC mapBuffer;
    PFNGLUNMAPBUFFERPROC unmapBuffer;

    // 2.0
    PFNGLATTACHSHADERPROC attachShader;
    PFNGLBINDATTRIBLOCATIONPROC bindAttribLocation;
    PFNGLBLENDEQUATIONSEPARATEPROC blendEquationSeparate;
    PFNGLCOMPILESHADERPROC compileShader;
    PFNGLCREATEPROGRAMPROC createProgram;
    PFNGLCREATESHADERPROC createShader;
    PFNGLDELETEPROGRAMPROC deleteProgram;
    PFNGLDELETESHADERPROC deleteShader;
    PFNGLDETACHSHADERPROC detachShader;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC disableVertexAttribArray;
    PFNGLDRAWBUFFERSPROC drawBuffers;
    PFNGLENABLEVERTEXATTRIBARRAYPROC enableVertexAttribArray;
    PFNGLGETACTIVEATTRIBPROC getActiveAttrib;
    PFNGLGETACTIVEUNIFORMPROC getActiveUniform;
    PFNGLGETATTACHEDSHADERSPROC getAttachedShaders;
    PFNGLGETATTRIBLOCATIONPROC getAttribLocation;
    PFNGLGETPROGRAMINFOLOGPROC getProgramInfoLog;
    PFNGLGETPROGRAMIVPROC getProgramiv;
    PFNGLGETSHADERINFOLOGPROC getShaderInfoLog;
    PFNGLGETSHADERSOURCEPROC getShaderSource;
    PFNGLGETSHADERIVPROC getShaderiv;
    PFNGLGETUNIFORMLOCATIONPROC getUniformLocation;
    PFNGLGETUNIFORMFVPROC getUniformfv;
    PFNGLGETUNIFORMIVPROC getUniformiv;
    PFNGLGETVERTEXATTRIBPOINTERVPROC getVertexAttribPointerv;
    PFNGLGETVERTEXATTRIBDVPROC getVertexAttribdv;
    PFNGLGETVERTEXATTRIBFVPROC getVertexAttribfv;
    PFNGLGETVERTEXATTRIBIVPROC getVertexAttribiv;
    PFNGLISPROGRAMPROC isProgram;
    PFNGLISSHADERPROC isShader;
    PFNGLLINKPROGRAMPROC linkProgram;
    PFNGLSHADERSOURCEPROC shaderSource;
    PFNGLSTENCILFUNCSEPARATEPROC stencilFuncSeparate;
    PFNGLSTENCILMASKSEPARATEPROC stencilMaskSeparate;
    PFNGLSTENCILOPSEPARATEPROC stencilOpSeparate;
    PFNGLUNIFORM1FPROC uniform1f;
    PFNGLUNIFORM1FVPROC uniform1fv;
    PFNGLUNIFORM1IPROC uniform1i;
    PFNGLUNIFORM1IVPROC uniform1iv;
    PFNGLUNIFORM2FPROC uniform2f;
    PFNGLUNIFORM2FVPROC uniform2fv;
    PFNGLUNIFORM2IPROC uniform2i;
    PFNGLUNIFORM2IVPROC uniform2iv;
    PFNGLUNIFORM3FPROC uniform3f;
    PFNGLUNIFORM3FVPROC uniform3fv;
    PFNGLUNIFORM3IPROC uniform3i;
    PFNGLUNIFORM3IVPROC uniform3iv;
    PFNGLUNIFORM4FPROC uniform4f;
    PFNGLUNIFORM4FVPROC uniform4fv;
    PFNGLUNIFORM4IPROC uniform4i;
    PFNGLUNIFORM4IVPROC uniform4iv;
    PFNGLUNIFORMMATRIX2FVPROC uniformMatrix2fv;
    PFNGLUNIFORMMATRIX3FVPROC uniformMatrix3fv;
    PFNGLUNIFORMMATRIX4FVPROC uniformMatrix4fv;
    PFNGLUSEPROGRAMPROC useProgram;
    PFNGLVALIDATEPROGRAMPROC validateProgram;
    PFNGLVERTEXATTRIB1DPROC vertexAttrib1d;
    PFNGLVERTEXATTRIB1DVPROC vertexAttrib1dv;
    PFNGLVERTEXATTRIB1FPROC vertexAttrib1f;
    PFNGLVERTEXATTRIB1FVPROC vertexAttrib1fv;
    PFNGLVERTEXATTRIB1SPROC vertexAttrib1s;
    PFNGLVERTEXATTRIB1SVPROC vertexAttrib1sv;
    PFNGLVERTEXATTRIB2DPROC vertexAttrib2d;
    PFNGLVERTEXATTRIB2DVPROC vertexAttrib2dv;
    PFNGLVERTEXATTRIB2FPROC vertexAttrib2f;
    PFNGLVERTEXATTRIB2FVPROC vertexAttrib2fv;
    PFNGLVERTEXATTRIB2SPROC vertexAttrib2s;
    PFNGLVERTEXATTRIB2SVPROC vertexAttrib2sv;
    PFNGLVERTEXATTRIB3DPROC vertexAttrib3d;
    PFNGLVERTEXATTRIB3DVPROC vertexAttrib3dv;
    PFNGLVERTEXATTRIB3FPROC vertexAttrib3f;
    PFNGLVERTEXATTRIB3FVPROC vertexAttrib3fv;
    PFNGLVERTEXATTRIB3SPROC vertexAttrib3s;
    PFNGLVERTEXATTRIB3SVPROC vertexAttrib3sv;
    PFNGLVERTEXATTRIB4NBVPROC vertexAttrib4Nbv;
    PFNGLVERTEXATTRIB4NIVPROC vertexAttrib4Niv;
    PFNGLVERTEXATTRIB4NSVPROC vertexAttrib4Nsv;
    PFNGLVERTEXATTRIB4NUBPROC vertexAttrib4Nub;
    PFNGLVERTEXATTRIB4NUBVPROC vertexAttrib4Nubv;
    PFNGLVERTEXATTRIB4NUIVPROC vertexAttrib4Nuiv;
    PFNGLVERTEXATTRIB4NUSVPROC vertexAttrib4Nusv;
    PFNGLVERTEXATTRIB4BVPROC vertexAttrib4bv;
    PFNGLVERTEXATTRIB4DPROC vertexAttrib4d;
    PFNGLVERTEXATTRIB4DVPROC vertexAttrib4dv;
    PFNGLVERTEXATTRIB4FPROC vertexAttrib4f;
    PFNGLVERTEXATTRIB4FVPROC vertexAttrib4fv;
    PFNGLVERTEXATTRIB4IVPROC vertexAttrib4iv;
    PFNGLVERTEXATTRIB4SPROC vertexAttrib4s;
    PFNGLVERTEXATTRIB4SVPROC vertexAttrib4sv;
    PFNGLVERTEXATTRIB4UBVPROC vertexAttrib4ubv;
    PFNGLVERTEXATTRIB4UIVPROC vertexAttrib4uiv;
    PFNGLVERTEXATTRIB4USVPROC vertexAttrib4usv;
    PFNGLVERTEXATTRIBPOINTERPROC vertexAttribPointer;

    // 2.1
    PFNGLUNIFORMMATRIX2X3FVPROC uniformMatrix2x3fv;
    PFNGLUNIFORMMATRIX2X4FVPROC uniformMatrix2x4fv;
    PFNGLUNIFORMMATRIX3X2FVPROC uniformMatrix3x2fv;
    PFNGLUNIFORMMATRIX3X4FVPROC uniformMatrix3x4fv;
    PFNGLUNIFORMMATRIX4X2FVPROC uniformMatrix4x2fv;
    PFNGLUNIFORMMATRIX4X3FVPROC uniformMatrix4x3fv;

    // 3.0
    PFNGLBEGINCONDITIONALRENDERPROC beginConditionalRender;
    PFNGLBEGINTRANSFORMFEEDBACKPROC beginTransformFeedback;
    PFNGLBINDBUFFERBASEPROC bindBufferBase;
    PFNGLBINDBUFFERRANGEPROC bindBufferRange;
    PFNGLBINDFRAGDATALOCATIONPROC bindFragDataLocation;
    PFNGLBINDFRAMEBUFFERPROC bindFramebuffer;
    PFNGLBINDRENDERBUFFERPROC bindRenderbuffer;
    PFNGLBINDVERTEXARRAYPROC bindVertexArray;
    PFNGLBLITFRAMEBUFFERPROC blitFramebuffer;
    PFNGLCHECKFRAMEBUFFERSTATUSPROC checkFramebufferStatus;
    PFNGLCLAMPCOLORPROC clampColor;
    PFNGLCLEARBUFFERFIPROC clearBufferfi;
    PFNGLCLEARBUFFERFVPROC clearBufferfv;
    PFNGLCLEARBUFFERIVPROC clearBufferiv;
    PFNGLCLEARBUFFERUIVPROC clearBufferuiv;
    PFNGLCOLORMASKIPROC colorMaski;
    PFNGLDELETEFRAMEBUFFERSPROC deleteFramebuffers;
    PFNGLDELETERENDERBUFFERSPROC deleteRenderbuffers;
    PFNGLDELETEVERTEXARRAYSPROC deleteVertexArrays;
    PFNGLDISABLEIPROC disablei;
    PFNGLENABLEIPROC enablei;
    PFNGLENDCONDITIONALRENDERPROC endConditionalRender;
    PFNGLENDTRANSFORMFEEDBACKPROC endTransformFeedback;
    PFNGLFLUSHMAPPEDBUFFERRANGEPROC flushMappedBufferRange;
    PFNGLFRAMEBUFFERRENDERBUFFERPROC framebufferRenderbuffer;
    PFNGLFRAMEBUFFERTEXTURE1DPROC framebufferTexture1D;
    PFNGLFRAMEBUFFERTEXTURE2DPROC framebufferTexture2D;
    PFNGLFRAMEBUFFERTEXTURE3DPROC framebufferTexture3D;
    PFNGLFRAMEBUFFERTEXTURELAYERPROC framebufferTextureLayer;
    PFNGLGENFRAMEBUFFERSPROC genFramebuffers;
    PFNGLGENRENDERBUFFERSPROC genRenderbuffers;
    PFNGLGENVERTEXARRAYSPROC genVertexArrays;
    PFNGLGENERATEMIPMAPPROC generateMipmap;
    PFNGLGETBOOLEANI_VPROC getBooleani_v;
    PFNGLGETFRAGDATALOCATIONPROC getFragDataLocation;
    PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC getFramebufferAttachmentParameteriv;
    PFNGLGETINTEGERI_VPROC getIntegeri_v;
    PFNGLGETRENDERBUFFERPARAMETERIVPROC getRenderbufferParameteriv;
    PFNGLGETSTRINGIPROC getStringi;
    PFNGLGETTEXPARAMETERIIVPROC getTexParameterIiv;
    PFNGLGETTEXPARAMETERIUIVPROC getTexParameterIuiv;
    PFNGLGETTRANSFORMFEEDBACKVARYINGPROC getTransformFeedbackVarying;
    PFNGLGETUNIFORMUIVPROC getUniformuiv;
    PFNGLGETVERTEXATTRIBIIVPROC getVertexAttribIiv;
    PFNGLGETVERTEXATTRIBIUIVPROC getVertexAttribIuiv;
    PFNGLISENABLEDIPROC isEnabledi;
    PFNGLISFRAMEBUFFERPROC isFramebuffer;
    PFNGLISRENDERBUFFERPROC isRenderbuffer;
    PFNGLISVERTEXARRAYPROC isVertexArray;
    PFNGLMAPBUFFERRANGEPROC mapBufferRange;
    PFNGLRENDERBUFFERSTORAGEPROC renderbufferStorage;
    PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC renderbufferStorageMultisample;
    PFNGLTEXPARAMETERIIVPROC texParameterIiv;
    PFNGLTEXPARAMETERIUIVPROC texParameterIuiv;
    PFNGLTRANSFORMFEEDBACKVARYINGSPROC transformFeedbackVaryings;
    PFNGLUNIFORM1UIPROC uniform1ui;
    PFNGLUNIFORM1UIVPROC uniform1uiv;
    PFNGLUNIFORM2UIPROC uniform2ui;
    PFNGLUNIFORM2UIVPROC uniform2uiv;
    PFNGLUNIFORM3UIPROC uniform3ui;
    PFNGLUNIFORM3UIVPROC uniform3uiv;
    PFNGLUNIFORM4UIPROC uniform4ui;
    PFNGLUNIFORM4UIVPROC uniform4uiv;
    PFNGLVERTEXATTRIBI1IPROC vertexAttribI1i;
    PFNGLVERTEXATTRIBI1IVPROC vertexAttribI1iv;
    PFNGLVERTEXATTRIBI1UIPROC vertexAttribI1ui;
    PFNGLVERTEXATTRIBI1UIVPROC vertexAttribI1uiv;
    PFNGLVERTEXATTRIBI2IPROC vertexAttribI2i;
    PFNGLVERTEXATTRIBI2IVPROC vertexAttribI2iv;
    PFNGLVERTEXATTRIBI2UIPROC vertexAttribI2ui;
    PFNGLVERTEXATTRIBI2UIVPROC vertexAttribI2uiv;
    PFNGLVERTEXATTRIBI3IPROC vertexAttribI3i;
    PFNGLVERTEXATTRIBI3IVPROC vertexAttribI3iv;
    PFNGLVERTEXATTRIBI3UIPROC vertexAttribI3ui;
    PFNGLVERTEXATTRIBI3UIVPROC vertexAttribI3uiv;
    PFNGLVERTEXATTRIBI4BVPROC vertexAttribI4bv;
    PFNGLVERTEXATTRIBI4IPROC vertexAttribI4i;
    PFNGLVERTEXATTRIBI4IVPROC vertexAttribI4iv;
    PFNGLVERTEXATTRIBI4SVPROC vertexAttribI4sv;
    PFNGLVERTEXATTRIBI4UBVPROC vertexAttribI4ubv;
    PFNGLVERTEXATTRIBI4UIPROC vertexAttribI4ui;
    PFNGLVERTEXATTRIBI4UIVPROC vertexAttribI4uiv;
    PFNGLVERTEXATTRIBI4USVPROC vertexAttribI4usv;
    PFNGLVERTEXATTRIBIPOINTERPROC vertexAttribIPointer;

    // 3.1
    PFNGLCOPYBUFFERSUBDATAPROC copyBufferSubData;
    PFNGLDRAWARRAYSINSTANCEDPROC drawArraysInstanced;
    PFNGLDRAWELEMENTSINSTANCEDPROC drawElementsInstanced;
    PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC getActiveUniformBlockName;
    PFNGLGETACTIVEUNIFORMBLOCKIVPROC getActiveUniformBlockiv;
    PFNGLGETACTIVEUNIFORMNAMEPROC getActiveUniformName;
    PFNGLGETACTIVEUNIFORMSIVPROC getActiveUniformsiv;
    PFNGLGETUNIFORMBLOCKINDEXPROC getUniformBlockIndex;
    PFNGLGETUNIFORMINDICESPROC getUniformIndices;
    PFNGLPRIMITIVERESTARTINDEXPROC primitiveRestartIndex;
    PFNGLTEXBUFFERPROC texBuffer;
    PFNGLUNIFORMBLOCKBINDINGPROC uniformBlockBinding;

    // 3.2
    PFNGLCLIENTWAITSYNCPROC clientWaitSync;
    PFNGLDELETESYNCPROC deleteSync;
    PFNGLDRAWELEMENTSBASEVERTEXPROC drawElementsBaseVertex;
    PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC drawElementsInstancedBaseVertex;
    PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC drawRangeElementsBaseVertex;
    PFNGLFENCESYNCPROC fenceSync;
    PFNGLFRAMEBUFFERTEXTUREPROC framebufferTexture;
    PFNGLGETBUFFERPARAMETERI64VPROC getBufferParameteri64v;
    PFNGLGETINTEGER64I_VPROC getInteger64i_v;
    PFNGLGETINTEGER64VPROC getInteger64v;
    PFNGLGETMULTISAMPLEFVPROC getMultisamplefv;
    PFNGLGETSYNCIVPROC getSynciv;
    PFNGLISSYNCPROC isSync;
    PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC multiDrawElementsBaseVertex;
    PFNGLPROVOKINGVERTEXPROC provokingVertex;
    PFNGLSAMPLEMASKIPROC sampleMaski;
    PFNGLTEXIMAGE2DMULTISAMPLEPROC texImage2DMultisample;
    PFNGLTEXIMAGE3DMULTISAMPLEPROC texImage3DMultisample;
    PFNGLWAITSYNCPROC waitSync;

    // NV_path_rendering (originally written against 3.2 compatibility profile)
    PFNGLMATRIXLOADFEXTPROC matrixLoadEXT;
    PFNGLGENPATHSNVPROC genPathsNV;
    PFNGLDELETEPATHSNVPROC delPathsNV;
    PFNGLPATHCOMMANDSNVPROC pathCommandsNV;
    PFNGLISPATHNVPROC isPathNV;
    PFNGLPATHPARAMETERFNVPROC setPathParameterfNV;
    PFNGLPATHPARAMETERINVPROC setPathParameteriNV;
    PFNGLGETPATHPARAMETERFVNVPROC getPathParameterfNV;
    PFNGLGETPATHPARAMETERIVNVPROC getPathParameteriNV;
    PFNGLPATHSTENCILFUNCNVPROC pathStencilFuncNV;
    PFNGLSTENCILFILLPATHNVPROC stencilFillPathNV;
    PFNGLSTENCILSTROKEPATHNVPROC stencilStrokePathNV;
    PFNGLCOVERFILLPATHNVPROC coverFillPathNV;
    PFNGLCOVERSTROKEPATHNVPROC coverStrokePathNV;
    PFNGLSTENCILTHENCOVERFILLPATHNVPROC stencilThenCoverFillPathNV;
    PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC stencilThenCoverStrokePathNV;
    PFNGLCOVERFILLPATHINSTANCEDNVPROC coverFillPathInstancedNV;
    PFNGLCOVERSTROKEPATHINSTANCEDNVPROC coverStrokePathInstancedNV;
    PFNGLSTENCILFILLPATHINSTANCEDNVPROC stencilFillPathInstancedNV;
    PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC stencilStrokePathInstancedNV;
    PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC stencilThenCoverFillPathInstancedNV;
    PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC stencilThenCoverStrokePathInstancedNV;
    PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC programPathFragmentInputGenNV;

    // 3.3
    PFNGLBINDFRAGDATALOCATIONINDEXEDPROC bindFragDataLocationIndexed;
    PFNGLBINDSAMPLERPROC bindSampler;
    PFNGLDELETESAMPLERSPROC deleteSamplers;
    PFNGLGENSAMPLERSPROC genSamplers;
    PFNGLGETFRAGDATAINDEXPROC getFragDataIndex;
    PFNGLGETQUERYOBJECTI64VPROC getQueryObjecti64v;
    PFNGLGETQUERYOBJECTUI64VPROC getQueryObjectui64v;
    PFNGLGETSAMPLERPARAMETERIIVPROC getSamplerParameterIiv;
    PFNGLGETSAMPLERPARAMETERIUIVPROC getSamplerParameterIuiv;
    PFNGLGETSAMPLERPARAMETERFVPROC getSamplerParameterfv;
    PFNGLGETSAMPLERPARAMETERIVPROC getSamplerParameteriv;
    PFNGLISSAMPLERPROC isSampler;
    PFNGLQUERYCOUNTERPROC queryCounter;
    PFNGLSAMPLERPARAMETERIIVPROC samplerParameterIiv;
    PFNGLSAMPLERPARAMETERIUIVPROC samplerParameterIuiv;
    PFNGLSAMPLERPARAMETERFPROC samplerParameterf;
    PFNGLSAMPLERPARAMETERFVPROC samplerParameterfv;
    PFNGLSAMPLERPARAMETERIPROC samplerParameteri;
    PFNGLSAMPLERPARAMETERIVPROC samplerParameteriv;
    PFNGLVERTEXATTRIBDIVISORPROC vertexAttribDivisor;
    PFNGLVERTEXATTRIBP1UIPROC vertexAttribP1ui;
    PFNGLVERTEXATTRIBP1UIVPROC vertexAttribP1uiv;
    PFNGLVERTEXATTRIBP2UIPROC vertexAttribP2ui;
    PFNGLVERTEXATTRIBP2UIVPROC vertexAttribP2uiv;
    PFNGLVERTEXATTRIBP3UIPROC vertexAttribP3ui;
    PFNGLVERTEXATTRIBP3UIVPROC vertexAttribP3uiv;
    PFNGLVERTEXATTRIBP4UIPROC vertexAttribP4ui;
    PFNGLVERTEXATTRIBP4UIVPROC vertexAttribP4uiv;

    // 4.0
    PFNGLBEGINQUERYINDEXEDPROC beginQueryIndexed;
    PFNGLBINDTRANSFORMFEEDBACKPROC bindTransformFeedback;
    PFNGLBLENDEQUATIONSEPARATEIPROC blendEquationSeparatei;
    PFNGLBLENDEQUATIONIPROC blendEquationi;
    PFNGLBLENDFUNCSEPARATEIPROC blendFuncSeparatei;
    PFNGLBLENDFUNCIPROC blendFunci;
    PFNGLDELETETRANSFORMFEEDBACKSPROC deleteTransformFeedbacks;
    PFNGLDRAWARRAYSINDIRECTPROC drawArraysIndirect;
    PFNGLDRAWELEMENTSINDIRECTPROC drawElementsIndirect;
    PFNGLDRAWTRANSFORMFEEDBACKPROC drawTransformFeedback;
    PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC drawTransformFeedbackStream;
    PFNGLENDQUERYINDEXEDPROC endQueryIndexed;
    PFNGLGENTRANSFORMFEEDBACKSPROC genTransformFeedbacks;
    PFNGLGETACTIVESUBROUTINENAMEPROC getActiveSubroutineName;
    PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC getActiveSubroutineUniformName;
    PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC getActiveSubroutineUniformiv;
    PFNGLGETPROGRAMSTAGEIVPROC getProgramStageiv;
    PFNGLGETQUERYINDEXEDIVPROC getQueryIndexediv;
    PFNGLGETSUBROUTINEINDEXPROC getSubroutineIndex;
    PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC getSubroutineUniformLocation;
    PFNGLGETUNIFORMSUBROUTINEUIVPROC getUniformSubroutineuiv;
    PFNGLGETUNIFORMDVPROC getUniformdv;
    PFNGLISTRANSFORMFEEDBACKPROC isTransformFeedback;
    PFNGLMINSAMPLESHADINGPROC minSampleShading;
    PFNGLPATCHPARAMETERFVPROC patchParameterfv;
    PFNGLPATCHPARAMETERIPROC patchParameteri;
    PFNGLPAUSETRANSFORMFEEDBACKPROC pauseTransformFeedback;
    PFNGLRESUMETRANSFORMFEEDBACKPROC resumeTransformFeedback;
    PFNGLUNIFORM1DPROC uniform1d;
    PFNGLUNIFORM1DVPROC uniform1dv;
    PFNGLUNIFORM2DPROC uniform2d;
    PFNGLUNIFORM2DVPROC uniform2dv;
    PFNGLUNIFORM3DPROC uniform3d;
    PFNGLUNIFORM3DVPROC uniform3dv;
    PFNGLUNIFORM4DPROC uniform4d;
    PFNGLUNIFORM4DVPROC uniform4dv;
    PFNGLUNIFORMMATRIX2DVPROC uniformMatrix2dv;
    PFNGLUNIFORMMATRIX2X3DVPROC uniformMatrix2x3dv;
    PFNGLUNIFORMMATRIX2X4DVPROC uniformMatrix2x4dv;
    PFNGLUNIFORMMATRIX3DVPROC uniformMatrix3dv;
    PFNGLUNIFORMMATRIX3X2DVPROC uniformMatrix3x2dv;
    PFNGLUNIFORMMATRIX3X4DVPROC uniformMatrix3x4dv;
    PFNGLUNIFORMMATRIX4DVPROC uniformMatrix4dv;
    PFNGLUNIFORMMATRIX4X2DVPROC uniformMatrix4x2dv;
    PFNGLUNIFORMMATRIX4X3DVPROC uniformMatrix4x3dv;
    PFNGLUNIFORMSUBROUTINESUIVPROC uniformSubroutinesuiv;

    // 4.1
    PFNGLACTIVESHADERPROGRAMPROC activeShaderProgram;
    PFNGLBINDPROGRAMPIPELINEPROC bindProgramPipeline;
    PFNGLCLEARDEPTHFPROC clearDepthf;
    PFNGLCREATESHADERPROGRAMVPROC createShaderProgramv;
    PFNGLDELETEPROGRAMPIPELINESPROC deleteProgramPipelines;
    PFNGLDEPTHRANGEARRAYVPROC depthRangeArrayv;
    PFNGLDEPTHRANGEINDEXEDPROC depthRangeIndexed;
    PFNGLDEPTHRANGEFPROC depthRangef;
    PFNGLGENPROGRAMPIPELINESPROC genProgramPipelines;
    PFNGLGETDOUBLEI_VPROC getDoublei_v;
    PFNGLGETFLOATI_VPROC getFloati_v;
    PFNGLGETPROGRAMBINARYPROC getProgramBinary;
    PFNGLGETPROGRAMPIPELINEINFOLOGPROC getProgramPipelineInfoLog;
    PFNGLGETPROGRAMPIPELINEIVPROC getProgramPipelineiv;
    PFNGLGETSHADERPRECISIONFORMATPROC getShaderPrecisionFormat;
    PFNGLGETVERTEXATTRIBLDVPROC getVertexAttribLdv;
    PFNGLISPROGRAMPIPELINEPROC isProgramPipeline;
    PFNGLPROGRAMBINARYPROC programBinary;
    PFNGLPROGRAMPARAMETERIPROC programParameteri;
    PFNGLPROGRAMUNIFORM1DPROC programUniform1d;
    PFNGLPROGRAMUNIFORM1DVPROC programUniform1dv;
    PFNGLPROGRAMUNIFORM1FPROC programUniform1f;
    PFNGLPROGRAMUNIFORM1FVPROC programUniform1fv;
    PFNGLPROGRAMUNIFORM1IPROC programUniform1i;
    PFNGLPROGRAMUNIFORM1IVPROC programUniform1iv;
    PFNGLPROGRAMUNIFORM1UIPROC programUniform1ui;
    PFNGLPROGRAMUNIFORM1UIVPROC programUniform1uiv;
    PFNGLPROGRAMUNIFORM2DPROC programUniform2d;
    PFNGLPROGRAMUNIFORM2DVPROC programUniform2dv;
    PFNGLPROGRAMUNIFORM2FPROC programUniform2f;
    PFNGLPROGRAMUNIFORM2FVPROC programUniform2fv;
    PFNGLPROGRAMUNIFORM2IPROC programUniform2i;
    PFNGLPROGRAMUNIFORM2IVPROC programUniform2iv;
    PFNGLPROGRAMUNIFORM2UIPROC programUniform2ui;
    PFNGLPROGRAMUNIFORM2UIVPROC programUniform2uiv;
    PFNGLPROGRAMUNIFORM3DPROC programUniform3d;
    PFNGLPROGRAMUNIFORM3DVPROC programUniform3dv;
    PFNGLPROGRAMUNIFORM3FPROC programUniform3f;
    PFNGLPROGRAMUNIFORM3FVPROC programUniform3fv;
    PFNGLPROGRAMUNIFORM3IPROC programUniform3i;
    PFNGLPROGRAMUNIFORM3IVPROC programUniform3iv;
    PFNGLPROGRAMUNIFORM3UIPROC programUniform3ui;
    PFNGLPROGRAMUNIFORM3UIVPROC programUniform3uiv;
    PFNGLPROGRAMUNIFORM4DPROC programUniform4d;
    PFNGLPROGRAMUNIFORM4DVPROC programUniform4dv;
    PFNGLPROGRAMUNIFORM4FPROC programUniform4f;
    PFNGLPROGRAMUNIFORM4FVPROC programUniform4fv;
    PFNGLPROGRAMUNIFORM4IPROC programUniform4i;
    PFNGLPROGRAMUNIFORM4IVPROC programUniform4iv;
    PFNGLPROGRAMUNIFORM4UIPROC programUniform4ui;
    PFNGLPROGRAMUNIFORM4UIVPROC programUniform4uiv;
    PFNGLPROGRAMUNIFORMMATRIX2DVPROC programUniformMatrix2dv;
    PFNGLPROGRAMUNIFORMMATRIX2FVPROC programUniformMatrix2fv;
    PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC programUniformMatrix2x3dv;
    PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC programUniformMatrix2x3fv;
    PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC programUniformMatrix2x4dv;
    PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC programUniformMatrix2x4fv;
    PFNGLPROGRAMUNIFORMMATRIX3DVPROC programUniformMatrix3dv;
    PFNGLPROGRAMUNIFORMMATRIX3FVPROC programUniformMatrix3fv;
    PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC programUniformMatrix3x2dv;
    PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC programUniformMatrix3x2fv;
    PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC programUniformMatrix3x4dv;
    PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC programUniformMatrix3x4fv;
    PFNGLPROGRAMUNIFORMMATRIX4DVPROC programUniformMatrix4dv;
    PFNGLPROGRAMUNIFORMMATRIX4FVPROC programUniformMatrix4fv;
    PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC programUniformMatrix4x2dv;
    PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC programUniformMatrix4x2fv;
    PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC programUniformMatrix4x3dv;
    PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC programUniformMatrix4x3fv;
    PFNGLRELEASESHADERCOMPILERPROC releaseShaderCompiler;
    PFNGLSCISSORARRAYVPROC scissorArrayv;
    PFNGLSCISSORINDEXEDPROC scissorIndexed;
    PFNGLSCISSORINDEXEDVPROC scissorIndexedv;
    PFNGLSHADERBINARYPROC shaderBinary;
    PFNGLUSEPROGRAMSTAGESPROC useProgramStages;
    PFNGLVALIDATEPROGRAMPIPELINEPROC validateProgramPipeline;
    PFNGLVERTEXATTRIBL1DPROC vertexAttribL1d;
    PFNGLVERTEXATTRIBL1DVPROC vertexAttribL1dv;
    PFNGLVERTEXATTRIBL2DPROC vertexAttribL2d;
    PFNGLVERTEXATTRIBL2DVPROC vertexAttribL2dv;
    PFNGLVERTEXATTRIBL3DPROC vertexAttribL3d;
    PFNGLVERTEXATTRIBL3DVPROC vertexAttribL3dv;
    PFNGLVERTEXATTRIBL4DPROC vertexAttribL4d;
    PFNGLVERTEXATTRIBL4DVPROC vertexAttribL4dv;
    PFNGLVERTEXATTRIBLPOINTERPROC vertexAttribLPointer;
    PFNGLVIEWPORTARRAYVPROC viewportArrayv;
    PFNGLVIEWPORTINDEXEDFPROC viewportIndexedf;
    PFNGLVIEWPORTINDEXEDFVPROC viewportIndexedfv;

    // 4.2
    PFNGLBINDIMAGETEXTUREPROC bindImageTexture;
    PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC drawArraysInstancedBaseInstance;
    PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC drawElementsInstancedBaseInstance;
    PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC drawElementsInstancedBaseVertexBaseInstance;
    PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC drawTransformFeedbackInstanced;
    PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC drawTransformFeedbackStreamInstanced;
    PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC getActiveAtomicCounterBufferiv;
    PFNGLGETINTERNALFORMATIVPROC getInternalformativ;
    PFNGLMEMORYBARRIERPROC memoryBarrier;
    PFNGLTEXSTORAGE1DPROC texStorage1D;
    PFNGLTEXSTORAGE2DPROC texStorage2D;
    PFNGLTEXSTORAGE3DPROC texStorage3D;

    // 4.3
    PFNGLBINDVERTEXBUFFERPROC bindVertexBuffer;
    PFNGLCLEARBUFFERDATAPROC clearBufferData;
    PFNGLCLEARBUFFERSUBDATAPROC clearBufferSubData;
    PFNGLCOPYIMAGESUBDATAPROC copyImageSubData;
    PFNGLDEBUGMESSAGECALLBACKPROC debugMessageCallback;
    PFNGLDEBUGMESSAGECONTROLPROC debugMessageControl;
    PFNGLDEBUGMESSAGEINSERTPROC debugMessageInsert;
    PFNGLDISPATCHCOMPUTEPROC dispatchCompute;
    PFNGLDISPATCHCOMPUTEINDIRECTPROC dispatchComputeIndirect;
    PFNGLFRAMEBUFFERPARAMETERIPROC framebufferParameteri;
    PFNGLGETDEBUGMESSAGELOGPROC getDebugMessageLog;
    PFNGLGETFRAMEBUFFERPARAMETERIVPROC getFramebufferParameteriv;
    PFNGLGETINTERNALFORMATI64VPROC getInternalformati64v;
    PFNGLGETPOINTERVPROC getPointerv;
    PFNGLGETOBJECTLABELPROC getObjectLabel;
    PFNGLGETOBJECTPTRLABELPROC getObjectPtrLabel;
    PFNGLGETPROGRAMINTERFACEIVPROC getProgramInterfaceiv;
    PFNGLGETPROGRAMRESOURCEINDEXPROC getProgramResourceIndex;
    PFNGLGETPROGRAMRESOURCELOCATIONPROC getProgramResourceLocation;
    PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC getProgramResourceLocationIndex;
    PFNGLGETPROGRAMRESOURCENAMEPROC getProgramResourceName;
    PFNGLGETPROGRAMRESOURCEIVPROC getProgramResourceiv;
    PFNGLINVALIDATEBUFFERDATAPROC invalidateBufferData;
    PFNGLINVALIDATEBUFFERSUBDATAPROC invalidateBufferSubData;
    PFNGLINVALIDATEFRAMEBUFFERPROC invalidateFramebuffer;
    PFNGLINVALIDATESUBFRAMEBUFFERPROC invalidateSubFramebuffer;
    PFNGLINVALIDATETEXIMAGEPROC invalidateTexImage;
    PFNGLINVALIDATETEXSUBIMAGEPROC invalidateTexSubImage;
    PFNGLMULTIDRAWARRAYSINDIRECTPROC multiDrawArraysIndirect;
    PFNGLMULTIDRAWELEMENTSINDIRECTPROC multiDrawElementsIndirect;
    PFNGLOBJECTLABELPROC objectLabel;
    PFNGLOBJECTPTRLABELPROC objectPtrLabel;
    PFNGLPOPDEBUGGROUPPROC popDebugGroup;
    PFNGLPUSHDEBUGGROUPPROC pushDebugGroup;
    PFNGLSHADERSTORAGEBLOCKBINDINGPROC shaderStorageBlockBinding;
    PFNGLTEXBUFFERRANGEPROC texBufferRange;
    PFNGLTEXSTORAGE2DMULTISAMPLEPROC texStorage2DMultisample;
    PFNGLTEXSTORAGE3DMULTISAMPLEPROC texStorage3DMultisample;
    PFNGLTEXTUREVIEWPROC textureView;
    PFNGLVERTEXATTRIBBINDINGPROC vertexAttribBinding;
    PFNGLVERTEXATTRIBFORMATPROC vertexAttribFormat;
    PFNGLVERTEXATTRIBIFORMATPROC vertexAttribIFormat;
    PFNGLVERTEXATTRIBLFORMATPROC vertexAttribLFormat;
    PFNGLVERTEXBINDINGDIVISORPROC vertexBindingDivisor;
    PFNGLCOVERAGEMODULATIONNVPROC coverageModulationNV;

    // 4.4
    PFNGLBINDBUFFERSBASEPROC bindBuffersBase;
    PFNGLBINDBUFFERSRANGEPROC bindBuffersRange;
    PFNGLBINDIMAGETEXTURESPROC bindImageTextures;
    PFNGLBINDSAMPLERSPROC bindSamplers;
    PFNGLBINDTEXTURESPROC bindTextures;
    PFNGLBINDVERTEXBUFFERSPROC bindVertexBuffers;
    PFNGLBUFFERSTORAGEPROC bufferStorage;
    PFNGLCLEARTEXIMAGEPROC clearTexImage;
    PFNGLCLEARTEXSUBIMAGEPROC clearTexSubImage;

    // 4.5
    PFNGLBINDTEXTUREUNITPROC bindTextureUnit;
    PFNGLBLITNAMEDFRAMEBUFFERPROC blitNamedFramebuffer;
    PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC checkNamedFramebufferStatus;
    PFNGLCLEARNAMEDBUFFERDATAPROC clearNamedBufferData;
    PFNGLCLEARNAMEDBUFFERSUBDATAPROC clearNamedBufferSubData;
    PFNGLCLEARNAMEDFRAMEBUFFERFIPROC clearNamedFramebufferfi;
    PFNGLCLEARNAMEDFRAMEBUFFERFVPROC clearNamedFramebufferfv;
    PFNGLCLEARNAMEDFRAMEBUFFERIVPROC clearNamedFramebufferiv;
    PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC clearNamedFramebufferuiv;
    PFNGLCLIPCONTROLPROC clipControl;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC compressedTextureSubImage1D;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC compressedTextureSubImage2D;
    PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC compressedTextureSubImage3D;
    PFNGLCOPYNAMEDBUFFERSUBDATAPROC copyNamedBufferSubData;
    PFNGLCOPYTEXTURESUBIMAGE1DPROC copyTextureSubImage1D;
    PFNGLCOPYTEXTURESUBIMAGE2DPROC copyTextureSubImage2D;
    PFNGLCOPYTEXTURESUBIMAGE3DPROC copyTextureSubImage3D;
    PFNGLCREATEBUFFERSPROC createBuffers;
    PFNGLCREATEFRAMEBUFFERSPROC createFramebuffers;
    PFNGLCREATEPROGRAMPIPELINESPROC createProgramPipelines;
    PFNGLCREATEQUERIESPROC createQueries;
    PFNGLCREATERENDERBUFFERSPROC createRenderbuffers;
    PFNGLCREATESAMPLERSPROC createSamplers;
    PFNGLCREATETEXTURESPROC createTextures;
    PFNGLCREATETRANSFORMFEEDBACKSPROC createTransformFeedbacks;
    PFNGLCREATEVERTEXARRAYSPROC createVertexArrays;
    PFNGLDISABLEVERTEXARRAYATTRIBPROC disableVertexArrayAttrib;
    PFNGLENABLEVERTEXARRAYATTRIBPROC enableVertexArrayAttrib;
    PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC flushMappedNamedBufferRange;
    PFNGLGENERATETEXTUREMIPMAPPROC generateTextureMipmap;
    PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC getCompressedTextureImage;
    PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC getCompressedTextureSubImage;
    PFNGLGETGRAPHICSRESETSTATUSPROC getGraphicsResetStatus;
    PFNGLGETNAMEDBUFFERPARAMETERI64VPROC getNamedBufferParameteri64v;
    PFNGLGETNAMEDBUFFERPARAMETERIVPROC getNamedBufferParameteriv;
    PFNGLGETNAMEDBUFFERPOINTERVPROC getNamedBufferPointerv;
    PFNGLGETNAMEDBUFFERSUBDATAPROC getNamedBufferSubData;
    PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC getNamedFramebufferAttachmentParameteriv;
    PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC getNamedFramebufferParameteriv;
    PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC getNamedRenderbufferParameteriv;
    PFNGLGETQUERYBUFFEROBJECTI64VPROC getQueryBufferObjecti64v;
    PFNGLGETQUERYBUFFEROBJECTIVPROC getQueryBufferObjectiv;
    PFNGLGETQUERYBUFFEROBJECTUI64VPROC getQueryBufferObjectui64v;
    PFNGLGETQUERYBUFFEROBJECTUIVPROC getQueryBufferObjectuiv;
    PFNGLGETTEXTUREIMAGEPROC getTextureImage;
    PFNGLGETTEXTURELEVELPARAMETERFVPROC getTextureLevelParameterfv;
    PFNGLGETTEXTURELEVELPARAMETERIVPROC getTextureLevelParameteriv;
    PFNGLGETTEXTUREPARAMETERIIVPROC getTextureParameterIiv;
    PFNGLGETTEXTUREPARAMETERIUIVPROC getTextureParameterIuiv;
    PFNGLGETTEXTUREPARAMETERFVPROC getTextureParameterfv;
    PFNGLGETTEXTUREPARAMETERIVPROC getTextureParameteriv;
    PFNGLGETTEXTURESUBIMAGEPROC getTextureSubImage;
    PFNGLGETTRANSFORMFEEDBACKI64_VPROC getTransformFeedbacki64_v;
    PFNGLGETTRANSFORMFEEDBACKI_VPROC getTransformFeedbacki_v;
    PFNGLGETTRANSFORMFEEDBACKIVPROC getTransformFeedbackiv;
    PFNGLGETVERTEXARRAYINDEXED64IVPROC getVertexArrayIndexed64iv;
    PFNGLGETVERTEXARRAYINDEXEDIVPROC getVertexArrayIndexediv;
    PFNGLGETVERTEXARRAYIVPROC getVertexArrayiv;
    PFNGLGETNCOMPRESSEDTEXIMAGEPROC getnCompressedTexImage;
    PFNGLGETNTEXIMAGEPROC getnTexImage;
    PFNGLGETNUNIFORMDVPROC getnUniformdv;
    PFNGLGETNUNIFORMFVPROC getnUniformfv;
    PFNGLGETNUNIFORMIVPROC getnUniformiv;
    PFNGLGETNUNIFORMUIVPROC getnUniformuiv;
    PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC invalidateNamedFramebufferData;
    PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC invalidateNamedFramebufferSubData;
    PFNGLMAPNAMEDBUFFERPROC mapNamedBuffer;
    PFNGLMAPNAMEDBUFFERRANGEPROC mapNamedBufferRange;
    PFNGLMEMORYBARRIERBYREGIONPROC memoryBarrierByRegion;
    PFNGLNAMEDBUFFERDATAPROC namedBufferData;
    PFNGLNAMEDBUFFERSTORAGEPROC namedBufferStorage;
    PFNGLNAMEDBUFFERSUBDATAPROC namedBufferSubData;
    PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC namedFramebufferDrawBuffer;
    PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC namedFramebufferDrawBuffers;
    PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC namedFramebufferParameteri;
    PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC namedFramebufferReadBuffer;
    PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC namedFramebufferRenderbuffer;
    PFNGLNAMEDFRAMEBUFFERTEXTUREPROC namedFramebufferTexture;
    PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC namedFramebufferTextureLayer;
    PFNGLNAMEDRENDERBUFFERSTORAGEPROC namedRenderbufferStorage;
    PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC namedRenderbufferStorageMultisample;
    PFNGLREADNPIXELSPROC readnPixels;
    PFNGLTEXTUREBARRIERPROC textureBarrier;
    PFNGLTEXTUREBUFFERPROC textureBuffer;
    PFNGLTEXTUREBUFFERRANGEPROC textureBufferRange;
    PFNGLTEXTUREPARAMETERIIVPROC textureParameterIiv;
    PFNGLTEXTUREPARAMETERIUIVPROC textureParameterIuiv;
    PFNGLTEXTUREPARAMETERFPROC textureParameterf;
    PFNGLTEXTUREPARAMETERFVPROC textureParameterfv;
    PFNGLTEXTUREPARAMETERIPROC textureParameteri;
    PFNGLTEXTUREPARAMETERIVPROC textureParameteriv;
    PFNGLTEXTURESTORAGE1DPROC textureStorage1D;
    PFNGLTEXTURESTORAGE2DPROC textureStorage2D;
    PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC textureStorage2DMultisample;
    PFNGLTEXTURESTORAGE3DPROC textureStorage3D;
    PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC textureStorage3DMultisample;
    PFNGLTEXTURESUBIMAGE1DPROC textureSubImage1D;
    PFNGLTEXTURESUBIMAGE2DPROC textureSubImage2D;
    PFNGLTEXTURESUBIMAGE3DPROC textureSubImage3D;
    PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC transformFeedbackBufferBase;
    PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC transformFeedbackBufferRange;
    PFNGLUNMAPNAMEDBUFFERPROC unmapNamedBuffer;
    PFNGLVERTEXARRAYATTRIBBINDINGPROC vertexArrayAttribBinding;
    PFNGLVERTEXARRAYATTRIBFORMATPROC vertexArrayAttribFormat;
    PFNGLVERTEXARRAYATTRIBIFORMATPROC vertexArrayAttribIFormat;
    PFNGLVERTEXARRAYATTRIBLFORMATPROC vertexArrayAttribLFormat;
    PFNGLVERTEXARRAYBINDINGDIVISORPROC vertexArrayBindingDivisor;
    PFNGLVERTEXARRAYELEMENTBUFFERPROC vertexArrayElementBuffer;
    PFNGLVERTEXARRAYVERTEXBUFFERPROC vertexArrayVertexBuffer;
    PFNGLVERTEXARRAYVERTEXBUFFERSPROC vertexArrayVertexBuffers;

    // ES 3.2
    PFNGLBLENDBARRIERPROC blendBarrier;
    PFNGLPRIMITIVEBOUNDINGBOXPROC primitiveBoundingBox;

    // ES extensions
    PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC eglImageTargetRenderbufferStorageOES;
    PFNGLEGLIMAGETARGETTEXTURE2DOESPROC eglImageTargetTexture2DOES;

  private:
    void initializeProcsDesktopGL();
    void initializeProcsGLES();

    virtual void *loadProcAddress(const std::string &function) = 0;
};

}

#endif // LIBANGLE_RENDERER_GL_FUNCTIONSGL_H_
