/*
 *  OGActorMissile.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORMISSILE_H_
#define OGACTORMISSILE_H_

#include "ogactorbullet.h"
#include "ogmissileflightworker.h"


class COGActorMissile : public COGActorBullet
{
public:
	COGActorMissile();
	virtual ~COGActorMissile();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Set active state
	virtual void Activate (bool _bActive);

	// Fire to target.
	virtual void Fire (const Vec3& _vTarget);

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

protected:

    IOGEffect*				m_pHeadEffect;
	COGMissileFlightWorker	m_FlightWorker;
};


#endif