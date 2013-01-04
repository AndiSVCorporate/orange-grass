/*
 *  IOGSgNode.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSGNODE_H_
#define IOGSGNODE_H_

#include "Mathematics.h"
#include "IOGPhysicalObject.h"
#include "IOGRenderable.h"


class IOGSgNode
{
public:
	// destructor
	virtual ~IOGSgNode () {}

	// update transform.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// render.
	virtual void Render () = 0;

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const = 0;

	// Get OBB
	virtual const IOGObb& GetOBB () const = 0;

	// Get transformed OBBs list
	virtual const std::vector<IOGObb>& GetTransformedOBBs () const = 0;

	// get physics.
	virtual IOGPhysicalObject* GetPhysics () = 0;

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const = 0;

	// start animation.
    virtual void StartAnimation (const std::string& _Alias) = 0;

	// Get active point
    virtual bool GetActivePoint (Vec3& _point, const std::string& _Alias) = 0;

	// Get active state
	virtual bool IsActive () const = 0;

	// Set active state
	virtual void Activate (bool _bActive) = 0;
};

#endif