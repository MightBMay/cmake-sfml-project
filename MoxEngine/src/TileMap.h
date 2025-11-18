#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
struct TileMap {
	std::string texturePath;
	const sf::Texture* tileset;

	sf::Vector2u tileSize;
	unsigned width;
	unsigned height;
	std::vector<int> tileData;

	TileMap() : tileset(nullptr), width(0), height(0) {}


	void SaveToJSON(nlohmann::json& data) {

		data["spritePath"] = texturePath;
		data["tileSize"] = { tileSize.x, tileSize.y };
		data["width"] = width;
		data["height"] = height;
		data["tileData"] = tileData;
	}

	void Resize(unsigned newW, unsigned newH) {
		unsigned oldW = width;
		unsigned oldH = height;
		std::vector<int> newData(newW * newH, 0);
		unsigned copyW = std::min(oldW, newW);
		unsigned copyH = std::min(oldH, newH);


		for (unsigned y = 0; y < copyH; ++y)
			for (unsigned x = 0; x < copyW; ++x)
				newData[x + y * newW] = tileData[x + y * oldW];

		tileData = std::move(newData);
		width = newW;
		height = newH;

			

	}


	void EditTile(unsigned x, unsigned y, int newValue) {
		tileData[x + y * width] = newValue;
		// tile rules can go here prob.
	}


};

