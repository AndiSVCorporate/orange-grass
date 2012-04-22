/*
 *  ogshadersmanager.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogshadermanager.h"
#include "ogshader.h"
#include "ogmodelshader.h"
#include "ogspriteshader.h"
#include "ogcoloreffectshader.h"
#include "ogtextshader.h"
#include "ogshadowmodelshader.h"
#include "ogshadowedsceneshader.h"
#include "OrangeGrass.h"
#include <algorithm>


COGShaderManager::COGShaderManager ()
{
}


COGShaderManager::~COGShaderManager ()
{
}


// initialize shaders.
bool COGShaderManager::Init ()
{
    IOGResourceMgr* pResMgr = GetResourceMgr();
	std::string ShaderPath = std::string("Shaders/gles/");
#ifdef WIN32
	ShaderPath = std::string("Shaders/gl/");
#endif

    m_ShaderStorage[OG_SHADER_NO] = NULL;

    IOGShader* pColorEffectShader = new COGColorEffectShader();
    if (!pColorEffectShader->Load(pResMgr->GetFullPath(ShaderPath + std::string("ColorEffect.vsh")), pResMgr->GetFullPath(ShaderPath + std::string("ColorEffect.fsh"))))
        return false;
    m_ShaderStorage[OG_SHADER_COLOREFFECT] = pColorEffectShader;

    IOGShader* pModelShader = new COGModelShader();
	if (!pModelShader->Load(pResMgr->GetFullPath(ShaderPath + std::string("Model.vsh")), pResMgr->GetFullPath(ShaderPath + std::string("Model.fsh"))))
        return false;
    m_ShaderStorage[OG_SHADER_MODEL] = pModelShader;

    IOGShader* pShadowedSceneShader = new COGShadowedSceneShader();
    if (!pShadowedSceneShader->Load(pResMgr->GetFullPath(ShaderPath + std::string("ShadowedScene.vsh")), pResMgr->GetFullPath(ShaderPath + std::string("ShadowedScene.fsh"))))
        return false;
    m_ShaderStorage[OG_SHADER_SHADOWEDSCENE] = pShadowedSceneShader;

    IOGShader* pShadowModelShader = new COGShadowModelShader();
    if (!pShadowModelShader->Load(pResMgr->GetFullPath(ShaderPath + std::string("ShadowModel.vsh")), pResMgr->GetFullPath(ShaderPath + std::string("ShadowModel.fsh"))))
        return false;
    m_ShaderStorage[OG_SHADER_SHADOWMODEL] = pShadowModelShader;

    IOGShader* pSpriteShader = new COGSpriteShader();
    if (!pSpriteShader->Load(pResMgr->GetFullPath(ShaderPath + std::string("Sprite.vsh")), pResMgr->GetFullPath(ShaderPath + std::string("Sprite.fsh"))))
        return false;
    m_ShaderStorage[OG_SHADER_SPRITE] = pSpriteShader;

    IOGShader* pTextShader = new COGTextShader();
    if (!pTextShader->Load(pResMgr->GetFullPath(ShaderPath + std::string("Text.vsh")), pResMgr->GetFullPath(ShaderPath + std::string("Text.fsh"))))
        return false;
    m_ShaderStorage[OG_SHADER_TEXT] = pTextShader;

    return true;
}


// destroy shaders.
void COGShaderManager::Destroy ()
{
    for (int i = 0; i < OG_SHADERS_MAX; ++i)
    {
        IOGShader* pCur = m_ShaderStorage[i];
        if (pCur)
        {
            pCur->Unload();
            OG_SAFE_DELETE(pCur);
        }
    }
}


// get shader.
IOGShader* COGShaderManager::GetShader (OGShaderID _ShaderId)
{
    if (_ShaderId <= OG_SHADER_NO || _ShaderId >= OG_SHADERS_MAX)
        return NULL;

    return m_ShaderStorage[_ShaderId];
}


// get shader.
IOGShader* COGShaderManager::GetShader (const std::string& _ShaderAlias)
{
    return GetShader(ParseShaderId(_ShaderAlias));
}
