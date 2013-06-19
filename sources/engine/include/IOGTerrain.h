/*
 *  IOGTerrain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGTERRAIN_H_
#define IOGTERRAIN_H_

#include "IOGRenderable.h"
#include "IOGTexture.h"


class IOGTerrain
{
public:
	virtual ~IOGTerrain() {}

	// Save params
	virtual bool SaveParams () = 0;

	// Render terrain.
	virtual void Render (const OGMatrix& _mWorld) = 0;

	// Render all.
	virtual void RenderAll (const OGMatrix& _mWorld) = 0;

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos) = 0;

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;

	// Get all submesh AABBs
    virtual void GetAllAABBs (std::vector<IOGAabb*>& _aabbs) = 0;
};


#endif