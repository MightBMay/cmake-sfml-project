#pragma once
#include "Component.h"
#include "json.hpp"

using ComponentCreateFunction = std::unique_ptr<Component>(*)(const nlohmann::json&);

class ComponentFactory {

private:
	std::unordered_map<std::string, ComponentCreateFunction> registry;
	std::vector<std::string> registeredTypes;

public:
	static ComponentFactory& instance() {
		static ComponentFactory inst;
		return inst;
	}
	const std::vector<std::string> GetTypes() {
		return registeredTypes;
	}

	void Register(const std::string& type, ComponentCreateFunction function) {
		registry[type] = function;
		registeredTypes.emplace_back(type);
	}

	std::unique_ptr<Component> Create(const std::string& type, const nlohmann::json& data) {
		auto it = registry.find(type);
		if (it != registry.end())
			return it->second(data);
		throw std::runtime_error("Component type not found in registry:" + type);
	}		


};
