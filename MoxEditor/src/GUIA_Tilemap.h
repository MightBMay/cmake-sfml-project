#pragma once
#include "GUI_Action.h"
#include "TileMapRenderer.h"
struct GUIA_TileMapSettingsChange : public GUI_Action{

private:
	TileMapRenderer* renderer;
	std::string projectPath;
	std::string layerName;
	std::string levelName;

	std::string oldProjectPath;
	std::string oldLayerName;
	std::string oldLevelName;

public:
	GUIA_TileMapSettingsChange(TileMapRenderer* renderer, std::string projectPath, std::string layerName, std::string levelName): 
		renderer(renderer), projectPath(projectPath), layerName(layerName), levelName(levelName){}

	void Execute() override {
		if (!renderer) return;
		oldProjectPath = renderer->GetProjectPath();
		oldLayerName = renderer->GetLayerName();
		oldLevelName = renderer->GetLevelName();

		renderer->SetPathAndName(projectPath, layerName, levelName);

		if(projectPath != oldProjectPath) renderer->ReloadTileMap();

	}

	void Undo() override {
		if (!renderer) return;
		renderer->SetPathAndName(oldProjectPath, oldLayerName, oldLevelName);
		if(projectPath != oldProjectPath) renderer->ReloadTileMap();

	}

};