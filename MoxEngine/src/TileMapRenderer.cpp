#include "pch.h"
#include "TileMapRenderer.h"
#include "ImGUI.h"
#include "ImGuiFileDialog.h"

void TileMapRenderer::setTilemap(std::unique_ptr<TileMap> newMap, const std::string& layerName) {

    _tileMap = std::move(newMap);    
    _layerName = layerName;
}


void TileMapRenderer::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    if (!_tileMap) {
        std::cerr << " Null tilemap\n";
        return;
    }

    if (_layerName.empty()) {
        std::cerr << "Layer name was empty\n";
        return;
    }
    try {
        
       
        const auto& layer = _tileMap->getLayer(_layerName);
        target.draw(layer, states);
        std::cout << "drawing\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing layer '" << _layerName << "': " << e.what() << "\n";
    }
}


#if IN_EDITOR
void TileMapRenderer::getImGuiParams(nlohmann::json& data) {
    data["layer"] = _layerName;
}


void TileMapRenderer::getInspectorParams() {
    ImGui::SeparatorText("Tilemap Renderer");

    char buf[256];
    strcpy_s(buf, _layerName.c_str());

    if (ImGui::InputText("Layer to draw", buf, sizeof(buf))) {
        _layerName = buf;
    }
}

#endif