/*
 *  IOGActorManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGACTORMANAGER_H_
#define IOGACTORMANAGER_H_

#include "IOGActor.h"
#include <vector>


class IOGActorManager
{
public:
	// destructor
	virtual ~IOGActorManager () {}

	// Create actor
	virtual IOGActor* CreateActor (
		OGActorType _Type,
		const char* _pModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale) = 0;

	// Add actor to the list.
	virtual void AddActor (IOGActor* _pActor) = 0;

	// Destroy actor and remove from list.
	virtual void DestroyActor (IOGActor* _pActor) = 0;

	// Update actors.
	virtual void Update (int _ElapsedTime) = 0;

	// Get actors list.
    virtual const std::vector<IOGActor*>& GetActorsList () const = 0;

	// Get nearest intersected actor.
	virtual IOGActor* GetNearestIntersectedActor (
        const Vec3& _RayStart, 
        const Vec3& _RayDir ) = 0;
};

#endif
