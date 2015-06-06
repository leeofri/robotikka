#pragma once
#include "ConfigurationManager.h"
#include <iostream>
#include <string>
#include "../lib/config.h"
#include "../Consts.h"
using namespace std;
using namespace Consts;

namespace Managers {
ConfigurationManager * ConfigurationManager::m_ConfigurationManagerInstance = NULL;
ConfigurationManager::ConfigurationManager(){};
void ConfigurationManager::LoadFromFile(std::string filePath) {
		// create the first singleton instance

		Config configParser = Config(filePath);

		ConfigurationManager::m_ConfigurationManagerInstance = new ConfigurationManager();
		m_PngMapPath = configParser.pString(CFG_PATH_TO_PNG);
		m_StartLocation.m_X = configParser.pDouble(CFG_START_LOCATION_X);
		m_StartLocation.m_Y = configParser.pDouble(CFG_START_LOCATION_Y);
		m_StartLocation.m_Yaw = configParser.pDouble(CFG_START_LOCATION_YAW);
		m_EndLocation.m_X = configParser.pDouble(CFG_END_LOCATION_X);
		m_EndLocation.m_Y = configParser.pDouble(CFG_END_LOCATION_Y);
		m_PpCM = configParser.pDouble(CFG_PPCM_KEY_KEY);
		m_PngGridResolution = configParser.pDouble(CFG_PNG_GRID_RESOLUTION);
		m_RobotSize.m_Width = configParser.pDouble(CFG_ROBOT_SIZE_WIDTH);
		m_RobotSize.m_Height = configParser.pDouble(CFG_ROBOT_SIZE_HEIGHT);

	}

ConfigurationManager::~ConfigurationManager() {
	}


ConfigurationManager* ConfigurationManager::GetInstance() {
	if (ConfigurationManager::m_ConfigurationManagerInstance == NULL)
	{
		throw new std::string("Object ConfigurationManager Never Loaded");
	}
	else
	{
		return ConfigurationManager::m_ConfigurationManagerInstance;
	}
	return NULL;
	}


	string ConfigurationManager::getPngMapPath() {
		return m_PngMapPath;
	}

	Location ConfigurationManager::getStartLocation() {
		return m_StartLocation;
	}

	Location ConfigurationManager::getEndLocation() {
		return m_EndLocation;
	}

	float ConfigurationManager::getPixelPerCm() {
		return m_PpCM;
	}

	float ConfigurationManager::getPngGridResolution() {
		return m_PngGridResolution;
	}

	Size ConfigurationManager::getRobotSize() {
		return m_RobotSize;
	}

}
