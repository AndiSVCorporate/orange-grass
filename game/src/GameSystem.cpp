/*
 *  GameSystem.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "GameSystem.h"
#include "OrangeGrass.h"
#include "LoadScreenController.h"
#include "GameScreenController.h"


///	@brief Constructor.
CGameSystem::CGameSystem () :   m_pLoadScreen(NULL),
                                m_pGameScreen(NULL),
                                m_pCurScreen(NULL)
{
    m_State = SYSSTATE_ACTIVE;
    m_pLoadScreen = new CLoadScreenController();
    m_pGameScreen = new CGameScreenController();

    m_pCurScreen = m_pLoadScreen;
    m_pLoadScreen->Init();
    m_pLoadScreen->Activate();
}


///	@brief Destructor.
CGameSystem::~CGameSystem ()
{
    OG_SAFE_DELETE(m_pLoadScreen);
    OG_SAFE_DELETE(m_pGameScreen);
    m_pCurScreen = NULL;
}


///	@brief Exit from the program.
void CGameSystem::Exit ()
{
    m_State = SYSSTATE_EXIT;
}


///	@brief Change screen model.
/// @param _Model screen model id.
/// @param _Param screen model parameter #1.
/// @param _Param2 screen model parameter #2.
void CGameSystem::ChangeModel ( int _Model, int _Param, int _Param2 )
{
    if (m_pCurScreen == NULL)
        return;

    switch(m_pCurScreen->GetType())
    {
    case SCRTYPE_LOAD:
        m_pCurScreen = m_pGameScreen;
        m_pGameScreen->Init();
        m_pGameScreen->Activate();
        break;

    case SCRTYPE_GAME:
        Exit();
        break;
            
    case SCRTYPE_NONE:
        break;
    }
}


///	@brief Update screen model.
/// @param _ElapsedTime frame elapsed time in msec.
void CGameSystem::Update ( unsigned long _ElapsedTime )
{
    if (!m_pCurScreen)
        return;

    m_pCurScreen->Update (_ElapsedTime);
    ControllerState state = m_pCurScreen->GetState();
    if (state == CSTATE_INACTIVE)
    {
        ChangeModel(1, 0, 0);
    }
}


///	@brief Draw screen model.
void CGameSystem::Draw ()
{
    if (!m_pCurScreen)
        return;

    m_pCurScreen->RenderScene();
}


///	@brief Get state of the game controller.
/// @return return code.
SystemState CGameSystem::GetControllerState () const
{
    return m_State;
}


///	@brief Key press handler.
/// @param _KeyCode key code.
void CGameSystem::OnKeyDown ( int _KeyCode )
{
}


///	@brief Key release handler.
/// @param _KeyCode key code.
void CGameSystem::OnKeyUp ( int _KeyCode )
{
}


///	@brief Pointing device press handler.
/// @param _X x coordinate.
/// @param _Y y coordinate.
void CGameSystem::OnPointerDown ( int _X, int _Y )
{
    Exit();
}


///	@brief Pointing device release handler.
/// @param _X x coordinate.
/// @param _Y y coordinate.
void CGameSystem::OnPointerUp ( int _X, int _Y )
{
}


///	@brief Pointing device move handler.
/// @param _X x coordinate.
/// @param _Y y coordinate.
void CGameSystem::OnPointerMove ( int _X, int _Y )
{
}


///	@brief Resetting game state.
void CGameSystem::ResetGameState ()
{
}


///	@brief Saving game state.
void CGameSystem::SaveGameState ()
{
}


///	@brief Loading game state.
void CGameSystem::LoadGameState ()
{
}