#pragma once
#include "SFML/Graphics.hpp"
#include "TileMap.h"
#include "Renderer.h"
#include "TextureManager.h"
#define missing "../assets/sprites/missingTexture.png"
class TileMapRenderer : public Renderer {
private:
	std::unique_ptr<TileMap> _tileMap = nullptr;
    std::string _layerName = ""; // actual layer from ldtk to draw

public:

	static std::unique_ptr<Renderer> Create(const nlohmann::json& data) {
        std::unique_ptr<TileMapRenderer> r = std::make_unique<TileMapRenderer>();

        if (data.contains("layer"))
            r->_layerName = data["layer"];

        return r;
	}


	TileMapRenderer() = default;

    void setTilemap(std::unique_ptr<TileMap> map, const std::string& layerName);

    virtual sf::FloatRect GetGlobalBounds() const override { return {}; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) override;



#if IN_EDITOR
    virtual void getImGuiParams(nlohmann::json& data)override;
    virtual void getInspectorParams()override;

    virtual nlohmann::json SaveToJSON() const override {
        nlohmann::json data;
        data["type"] = "tilemap";
        data["layer"] = _layerName;
        return data;
    }
#endif

private:
    inline static bool registered = [] {
        RendererFactory::instance().Register("tilemap", &TileMapRenderer::Create);
        return true;
        }();

};