/*
 *  ogeffect.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffect.h"
#include "OrangeGrass.h"


COGEffect::COGEffect()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_pRenderer = GetRenderer();
}


COGEffect::~COGEffect()
{
}


// Set billboard basis vectors.
void COGEffect::SetBillboardVectors (const Vec3& _vUp, const Vec3& _vRight)
{
	m_vCameraUp = _vUp;
	m_vCameraRight = _vRight;
}


// Set direction.
void COGEffect::SetDirection (const Vec3& _vDir)
{
	m_Direction = _vDir;
}


// Render.
void COGEffect::Render (const MATRIX& _mWorld, unsigned int _Part)
{
    Render(_mWorld);
}


// Start.
void COGEffect::Start ()
{
}


// Stop.
void COGEffect::Stop ()
{
}