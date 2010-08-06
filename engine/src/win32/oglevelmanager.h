/*
 *  OGLevelManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLEVELMANAGER_H_
#define OGLEVELMANAGER_H_

#include "IOGLevelManager.h"
#include "oglevel.h"
#include <string>
#include <map>


class COGLevelManager : public IOGLevelManager
{
public:
	COGLevelManager ();
	virtual ~COGLevelManager ();

	// load from config file.
	virtual bool Init ();
	
	// load level.
	virtual IOGLevel* LoadLevel (const std::string& _Alias);

	// unload level.
	virtual void UnloadLevel (IOGLevel* _pLevel);
	
	// save level.
	virtual bool SaveLevel (IOGLevel* _pLevel);

	// get level list (for editor).
	virtual void GetLevelList (std::vector<std::string>& _LevelList) const;

	// get version.
    virtual unsigned int GetVersion () const { return LEVEL_VERSION; }

private:

	struct Cfg
	{
		struct LevelCfg
		{
			std::string level_alias;
			std::string level_file;
		};

		std::vector<LevelCfg> level_cfg_list;
	};

	// Load level manager configuration
	bool LoadConfig (COGLevelManager::Cfg& _cfg);

private:

    std::map<std::string, COGLevel*>	m_LevelList;
};


#endif
