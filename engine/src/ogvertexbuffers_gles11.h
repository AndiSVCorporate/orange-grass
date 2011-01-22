/*
 *  ogvertexbuffers_gles11.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGVERTEXBUFFERS_GLES11_H_
#define OGVERTEXBUFFERS_GLES11_H_

#include "Geometry.h"
#include "IOGStatistics.h"
#include "IOGVertexBuffers.h"


class COGVertexBuffers_GLES11 : public IOGVertexBuffers
{
	COGVertexBuffers_GLES11();

public:
	COGVertexBuffers_GLES11 (const SPODMesh* _pMesh);
	virtual ~COGVertexBuffers_GLES11 ();

	// apply buffers.
	virtual void Apply () const;

	// render buffer geometry.
	virtual void Render () const;

	// is indexed
	virtual bool IsIndexed() const {return (m_pMesh->sFaces.pData != 0);}
	
private:

	const SPODMesh*	m_pMesh;
	unsigned int	m_VBO;
	unsigned int	m_IBO;
	unsigned int	m_NumVertices;
	IOGStatistics*	m_pStats;
};

#endif