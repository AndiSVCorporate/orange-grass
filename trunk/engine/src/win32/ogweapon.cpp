/*
 *  ogweapon.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogweapon.h"
#include "IOGMath.h"


COGWeapon::COGWeapon()
{
}


COGWeapon::~COGWeapon()
{
    std::list<COGActorPlasmaMissile*>::iterator iter = m_MissileList.begin();
    for (; iter != m_MissileList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_MissileList.clear();
}


// Create weapon.
bool COGWeapon::Create (IOGActor* _pOwner)
{
    m_pOwner = _pOwner;
    Vec3 vStart = _pOwner->GetPhysicalObject()->GetPosition();
    for (int i = 0; i < 10; ++i)
    {
        IOGActor* pMissile = GetActorManager()->CreateActor(
            std::string("plasma_01"), 
            Vec3(0,0,0),
            Vec3(0,0,0),
            Vec3(1,1,1));
        GetActorManager()->AddActor(pMissile);
        m_MissileList.push_back((COGActorPlasmaMissile*)pMissile);
    }
    return true;
}


// Fire missile.
void COGWeapon::Fire (const Vec3& _vTarget)
{
    std::list<COGActorPlasmaMissile*>::iterator iter = m_MissileList.begin();
    for (; iter != m_MissileList.end(); ++iter)
    {
        COGActorPlasmaMissile* pMissile = *iter;
        if (!pMissile->IsActive())
        {
            pMissile->SetOwner(m_pOwner, Vec3(-3,0,-7));
            pMissile->Fire(_vTarget);
            return;
        }
    }
}