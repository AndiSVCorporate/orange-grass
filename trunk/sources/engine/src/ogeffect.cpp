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
}


COGEffect::~COGEffect()
{
}


// Initialize effect.
void COGEffect::Init(OGEffectType _Type, const std::string& _File)
{
    m_Type = _Type;

    IOGSettingsReader* pReader = GetSettingsReader();
    IOGEffectsManager* pEffectsMgr = GetEffectsManager();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath(_File));
    if (!pSource)
        return;

    IOGGroupNode* pEffectNode = pReader->OpenGroupNode(pSource, NULL, "Effect");
    if (pEffectNode)
    {
        IOGGroupNode* pEmitterNode = pReader->OpenGroupNode(pSource, pEffectNode, "Emitter");
        while (pEmitterNode)
        {
            IOGEmitter* pEmitter = NULL;

            std::string type_str = pReader->ReadStringParam(pEmitterNode, "type");
            int master = pReader->ReadIntParam(pEmitterNode, "master");

            pEmitter = pEffectsMgr->CreateEmitter(type_str);
            if (pEmitter)
            {
                pEmitter->Init(pEmitterNode);
                m_Emitters.push_back(pEmitter);
                if (master == 1)
                {
                    m_pMasterEmitter = pEmitter;
                }
            }
            pEmitterNode = pReader->ReadNextNode(pEmitterNode);
        }
    }
    pReader->CloseSource(pSource);

    m_AABB.SetMinMax(OGVec3(-1,-1,-1), OGVec3(1,1,1));
}


// Update.
void COGEffect::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Update(_ElapsedTime);
    }
    m_Status = m_pMasterEmitter->GetStatus();
}


// Render.
void COGEffect::Render (const OGMatrix& _mWorld, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight, _Pass);
    }
}


// Set billboard basis vectors.
void COGEffect::SetBillboardVectors (const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight)
{
    m_vCameraLook = _vLook;
    m_vCameraUp = _vUp;
    m_vCameraRight = _vRight;
}


// Set direction.
void COGEffect::SetDirection (const OGVec3& _vDir)
{
    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->SetDirection(_vDir);
    }
}


// Update position.
void COGEffect::UpdatePosition (const OGVec3& _vPosition)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->UpdatePosition(_vPosition);
    }
}


// Start.
void COGEffect::Start ()
{
    m_Status = OG_EFFECTSTATUS_STARTED;
    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Start();
    }
}


// Stop.
void COGEffect::Stop ()
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    m_Status = OG_EFFECTSTATUS_STOPPED;

    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Stop();
    }
}


// Set start and finish positions.
void COGEffect::SetStartFinishPositions (const OGVec3& _vStartPos, const OGVec3& _vFinishPos)
{
    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->SetStartFinishPositions(_vStartPos, _vFinishPos);
    }
}


// Is dynamic.
bool COGEffect::IsDynamic () const 
{
    if (m_pMasterEmitter)
        return m_pMasterEmitter->IsDynamic();
    return false;
}