/*
 *  ogsprite.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "ogsprite.h"
#include "OrangeGrass.h"


static const float g_fHalfScrWidth = SCR_WIDTH / 2.0f;
static const float g_fHalfScrHeight = SCR_HEIGHT / 2.0f;


COGSprite::COGSprite() : m_pTexture(NULL)
{
}


COGSprite::~COGSprite()
{
	m_pTexture = NULL;
}


// Initialize sprite.
void COGSprite::SetMapping (const Vec2& _vPos, const Vec2& _vSize)
{
	m_Pos = _vPos;
	m_Size = _vSize;
}


// Load resource.
bool COGSprite::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;    
	}

	m_pTexture = GetResourceMgr()->GetTexture(m_ResourceFile);
	if (m_pTexture)
	{
		m_T0 = Vec2(m_Pos.x / m_pTexture->GetWidth(), (m_pTexture->GetHeight() - m_Pos.y - m_Size.y) / m_pTexture->GetHeight());
		m_T1 = Vec2(
			(m_Pos.x + m_Size.x) / m_pTexture->GetWidth(), 
			(m_pTexture->GetHeight() - m_Pos.y) / m_pTexture->GetHeight() );
	}
	else
	{
		return false;
	}

	m_LoadState = OG_RESSTATE_LOADED;
    return true;
}


// Unload resource.
void COGSprite::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	m_pTexture = NULL;

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render sprite.
void COGSprite::Render (const Vec2& _vPos, const Vec2& _vSize)
{
	float fLeft = -g_fHalfScrWidth+_vPos.x;
	float fRight = -g_fHalfScrWidth+_vSize.x+_vPos.x;
	float fTop = g_fHalfScrHeight-_vSize.y-_vPos.y;
	float fBottom = g_fHalfScrHeight-_vPos.y;

	m_Vertices[0].p	= Vec2(fRight, fTop);	
	m_Vertices[0].t = Vec2(m_T1.x, m_T0.y); 
	m_Vertices[1].p	= Vec2(fLeft, fTop);	
	m_Vertices[1].t = Vec2(m_T0.x, m_T0.y); 
	m_Vertices[2].p	= Vec2(fRight, fBottom);	
	m_Vertices[2].t = Vec2(m_T1.x, m_T1.y); 
	m_Vertices[3].p	= Vec2(fLeft, fBottom);	
	m_Vertices[3].t = Vec2(m_T0.x, m_T1.y); 

	GetRenderer()->SetTexture(m_pTexture);
	glVertexPointer(2, GL_FLOAT, 16, m_Vertices);
	glTexCoordPointer(2, GL_FLOAT, 16, (void*)((char *)m_Vertices + 8));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
