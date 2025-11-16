#pragma once
#include "SFML/Graphics/Color.hpp"
#include "json.hpp"


namespace nlohmann {
	template<> struct adl_serializer<sf::Color> {
		static void to_json(json& j, const sf::Color& c) {
		// Store as an array of 4 uint8s
			j = json::array({ c.r, c.g, c.b, c.a });
		}


		static void from_json(const json& j, sf::Color& c) {
		// Expect exactly 4 entries
			c.r = j.at(0).get<uint8_t>();
			c.g = j.at(1).get<uint8_t>();
			c.b = j.at(2).get<uint8_t>();
			c.a = j.at(3).get<uint8_t>();
		}
	};


	template<> struct adl_serializer<sf::IntRect> {
		static void to_json(json& j, const sf::IntRect& ir) {
			j = json::array({
				ir.position.x, 
				ir.position.y,
				ir.size.x, 
				ir.size.y });
		}

		static void from_json(const json& j, sf::IntRect& ir) {
			ir.position.x = j.at(0).get<int>();
			ir.position.y = j.at(1).get<int>();
			ir.size.x = j.at(2).get<int>();
			ir.size.y = j.at(3).get<int>();
			
		}
	};

}