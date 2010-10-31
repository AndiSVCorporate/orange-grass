/*
 *  ogrenderer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogrenderer.h"
#include "oglight.h"
#include "ogcamera.h"
#include "ogfog.h"
#include "ogsprite.h"
#include "oggrutility.h"


COGRenderer::COGRenderer () :   m_pCurTexture(NULL),
                                m_pCurMaterial(NULL),
                                m_pCurMesh(NULL),
								m_pFog(NULL),
								m_pLight(NULL),
								m_pCamera(NULL),
								m_pText(NULL)
{
	m_pStats = GetStatistics();
}


COGRenderer::~COGRenderer ()
{
    OG_SAFE_DELETE(m_pText);
    OG_SAFE_DELETE(m_pFog);
    OG_SAFE_DELETE(m_pLight);
    OG_SAFE_DELETE(m_pCamera);
}


// initialize renderer.
bool COGRenderer::Init ()
{
    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);

    glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Reset();
	m_pLight = new COGLight ();
	m_pCamera = new COGCamera ();
	m_pFog = new COGFog ();

	return true;
}


// set viewport.
void COGRenderer::SetViewport (
							   unsigned int _Width, 
							   unsigned int _Height,
							   float _fZNear,
							   float _fZFar,
							   float _fFOV )
{
	m_Width = _Width;
	m_Height = _Height;
	m_fFOV = _fFOV;
	m_fZNear = _fZNear;
	m_fZFar = _fZFar;

    for(int i=0; i<16; i++){m_mTextProj.f[i]=0;}
    m_mTextProj.f[10] = 1.0f; m_mTextProj.f[12] = -1.0f;
    m_mTextProj.f[13] = 1.0f; m_mTextProj.f[15] = 1.0f;

#ifdef WIN32
	MatrixOrthoRH(m_mOrthoProj, (float)m_Width, (float)m_Height, -1, 1, false);
    MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Width)/float(m_Height), m_fZNear, m_fZFar, false);
 	m_pText->SetTextures(_Width, _Height, false);
    m_mTextProj.f[0] = 2.0f/(m_Width);
    m_mTextProj.f[5] = -2.0f/(m_Height);
#else
	MatrixOrthoRH(m_mOrthoProj, (float)m_Height, (float)m_Width, -1, 1, true);
    MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Height)/float(m_Width), m_fZNear, m_fZFar, true);
 	m_pText->SetTextures(_Width, _Height, true);
    //m_mTextProj.f[0] = 2.0f/(m_Width);
    //m_mTextProj.f[5] = -2.0f/(m_Height);
    m_mTextProj.f[0] = 2.0f/(m_Height);
    m_mTextProj.f[5] = -2.0f/(m_Width);
#endif
}


// add rendering command.
void COGRenderer::SetTexture (IOGTexture* _pTexture)
{
    if (_pTexture != m_pCurTexture)
    {
		m_pStats->AddTextureSwitch();
        m_pCurTexture = _pTexture;
        m_pCurTexture->Apply();
    }
}


// add rendering command.
void COGRenderer::SetMaterial (IOGMaterial* _pMaterial)
{
	if (m_Mode == OG_RENDERMODE_SHADOWMAP)
		return;

    if (_pMaterial != m_pCurMaterial)
    {
        m_pCurMaterial = _pMaterial;
        m_pCurMaterial->Apply();
    }
}


// add rendering command.
void COGRenderer::RenderMesh (void* _pMesh)
{
	if ((IOGVertexBuffers*)_pMesh != m_pCurMesh)
    {
        m_pCurMesh = (IOGVertexBuffers*)_pMesh;
        m_pCurMesh->Apply();
    }
    m_pCurMesh->Render();
}


// clear frame buffer with the given color
void COGRenderer::ClearFrame (const Vec4& _vClearColor)
{
	glClearColor(_vClearColor.x, _vClearColor.y, _vClearColor.z, _vClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// Get scene light.
IOGLight* COGRenderer::GetLight ()
{
	return m_pLight;
}


// Get main camera.
IOGCamera* COGRenderer::GetCamera ()
{
	return m_pCamera;
}


// Get fog.
IOGFog* COGRenderer::GetFog ()
{
	return m_pFog;
}


// reset renderer pipeline.
void COGRenderer::Reset ()
{
    m_pCurTexture = NULL;
    m_pCurMaterial = NULL;
    m_pCurMesh = NULL;
}


// Unproject screen coords.
Vec3 COGRenderer::UnprojectCoords (int _X, int _Y)
{
    float* pMV = m_mView.f;
    float* pP = m_mProjection.f;
	float x0, y0, z0;
#ifdef WIN32
	UnProject((float)_X, (float)(m_Height - _Y), 0.0f, pMV, pP, m_Width, m_Height, &x0, &y0, &z0);
#else
	UnProject((float)_Y, (float)_X, 0.0f, pMV, pP, m_Height, m_Width, &x0, &y0, &z0);
#endif    
    return Vec3(x0, y0, z0);
}


// Display string.
void COGRenderer::DisplayString (const Vec2& _vPos, 
								 float _fScale, 
								 unsigned int Colour, 
								 const char * const pszFormat, ...)
{
	va_list	args;
	static char	Text[5120+1];
	va_start(args, pszFormat);
	vsprintf(Text, pszFormat, args);
	va_end(args);

    m_pText->DisplayText(_vPos.x,_vPos.y,_fScale, Colour, Text);
}