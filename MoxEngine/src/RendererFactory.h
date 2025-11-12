#pragma once
#include "Renderer.h"
#include "json.hpp"

using RendererCreateFunction = std::unique_ptr<Renderer>(*)(const nlohmann::json&);

class RendererFactory {
private:
	std::unordered_map<std::string, RendererCreateFunction> registry;
	std::vector<std::string> registeredTypes;

public:
	static RendererFactory& instance() {
		static RendererFactory inst;
		return inst;
	}

	const std::vector<std::string> GetTypes() {
		return registeredTypes;
	}

	void Register(const std::string& type, RendererCreateFunction function) {
		registry[type] = function;
		registeredTypes.emplace_back(type);
	}

	std::unique_ptr<Renderer> Create(const std::string& type, const nlohmann::json& data) {
		auto it = registry.find(type);
		if (it != registry.end())
			return it->second(data);
		throw std::runtime_error("Renderer type not found ion registry:" + type);
	}

};