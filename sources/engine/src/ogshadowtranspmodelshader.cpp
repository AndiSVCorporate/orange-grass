/*
*  OGShadowModelShader.cpp
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 11.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogshadowtranspmodelshader.h"
#include "ogshader.h"


COGShadowTransparentModelShader::COGShadowTransparentModelShader ()
{
}


COGShadowTransparentModelShader::~COGShadowTransparentModelShader ()
{
}


// load shaders.
bool COGShadowTransparentModelShader::Load (OGShaderID _Id, const std::string& _VertShader, const std::string& _FragmentShader)
{
    if(ShaderLoadFromFile(_FragmentShader.c_str(), GL_FRAGMENT_SHADER, &m_uiFragShader) == 0)
        return false;
    if(ShaderLoadFromFile(_VertShader.c_str(), GL_VERTEX_SHADER, &m_uiVertShader) == 0)
        return false;

    const char* pszAttribs[] = { "inVertex", "inNormal", "inTexCoord" };
    if (CreateProgram(&m_uiId, m_uiVertShader, m_uiFragShader, pszAttribs, 3) == 0)
        return false;

    m_uiMVPMatrixLoc = glGetUniformLocation(m_uiId, "MVPMatrix");
    m_uiTextureLoc = glGetUniformLocation(m_uiId, "sTexture");
    m_uiAlphaReference = glGetUniformLocation(m_uiId, "AlphaReference");

    m_Id = _Id;
    m_fAlphaRef = 0.5f;

    return true;
}


// unload shaders.
void COGShadowTransparentModelShader::Unload ()
{
    glDeleteProgram(m_uiId);
    glDeleteShader(m_uiVertShader);
    glDeleteShader(m_uiFragShader);
}


// apply the shader.
void COGShadowTransparentModelShader::Apply ()
{
    MatrixMultiply(m_mMV, m_mModel, m_mView);
    MatrixMultiply(m_mMVP, m_mMV, m_mProjection);
    glUniformMatrix4fv(m_uiMVPMatrixLoc, 1, GL_FALSE, m_mMVP.f);
}


// setup the shader.
void COGShadowTransparentModelShader::Setup ()
{
    glUseProgram(m_uiId);
    glUniform1i(m_uiTextureLoc, 0);
    glUniform1f(m_uiAlphaReference, m_fAlphaRef);
}


// set model matrix
void COGShadowTransparentModelShader::SetModelMatrix (const OGMatrix& _mModel)
{
    m_mModel = _mModel;
}


// set view matrix
void COGShadowTransparentModelShader::SetViewMatrix (const OGMatrix& _mView)
{
    m_mView = _mView;
}


// set projection matrix
void COGShadowTransparentModelShader::SetProjectionMatrix (const OGMatrix& _mProj)
{
    m_mProjection = _mProj;
}