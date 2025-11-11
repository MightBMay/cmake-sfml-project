#pragma once
#include "Component.h"
#include "json.hpp"

using ComponentCreateFunction = std::unique_ptr<Component>(*)(const nlohmann::json&);

class ComponentFactory {

private:
	std::unordered_map<std::string, ComponentCreateFunction> registry;

public:
	static ComponentFactory& instance() {
		static ComponentFactory inst;
		return inst;
	}


	void Register(
		const std::string& type, 
		ComponentCreateFunction function) {
		registry[type] = function;
	}

	std::unique_ptr<Component> Create(const std::string& type, const nlohmann::json& data) {
		auto it = registry.find(type);
		if (it != registry.end())
			return it->second(data);
		throw std::runtime_error("Component type not found in registry:" + type);
	}		


};
