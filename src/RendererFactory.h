#pragma once
#include "Renderer.h"
#include "json.hpp"

using RendererCreateFunction = std::unique_ptr<Renderer>(*)(const nlohmann::json&);

class RendererFactory {
private:
	std::unordered_map<std::string, RendererCreateFunction> registry;

public:
	static RendererFactory& instance() {
		static RendererFactory inst;
		return inst;
	}

	void Register(const std::string& type, RendererCreateFunction function) {
		registry[type] = function;
	}

	std::unique_ptr<Renderer> Create(const std::string& type, const nlohmann::json& data) {
		auto it = registry.find(type);
		if (it != registry.end())
			return it->second(data);
		throw std::runtime_error("Renderer type not found ion registry:" + type);
	}

};