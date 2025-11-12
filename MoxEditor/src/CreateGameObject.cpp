#include "CreateGameObject.h"
#include "imgui.h"
#include "imgui-SFML.h"



void GUI_CreateGameObject::draw(Scene& scene) {
    ImGui::Begin("Create GameObject");
    
   
    ImGui::InputText("Name", name, 64);
    ImGui::SeparatorText("Transform");
    ImGui::InputFloat2("Position", pos);
    ImGui::InputFloat2("Scale", scale);
    ImGui::InputFloat("Rotation", &rot);
#pragma region  Renderer



    ImGui::SeparatorText("Renderer");

    // Renderer dropdown
    const std::vector<std::string> rendererTypes = RendererFactory::instance().GetTypes();
    std::vector<const char*> rendererOptions;
    rendererOptions.reserve(rendererTypes.size());
    for (auto& s : rendererTypes) rendererOptions.push_back(s.c_str());

    if (!rendererOptions.empty()) {
        if (ImGui::Combo("Renderer Type", &selectedRendererIndex, rendererOptions.data(), (int)rendererOptions.size())) {
            if (selectedRendererIndex != previousRendererIndex) {
                rendererData = nlohmann::json::object();
                previousRendererIndex = selectedRendererIndex;
            }
        }
    }

    // Renderer-specific input fields
    if (!rendererOptions.empty()) {
        std::string selectedRenderer = rendererOptions[selectedRendererIndex];
        try {
            auto tempRenderer = RendererFactory::instance().Create(selectedRenderer, rendererData);
            tempRenderer->getImGuiParams(rendererData);
        }
        catch (const std::exception& e) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Error creating renderer: %s", e.what());
        }
    }
#pragma endregion

#pragma region  Component
    ImGui::SeparatorText("Components");

    // Get all registered component types
    const std::vector<std::string> componentTypes = ComponentFactory::instance().GetTypes();
    std::vector<const char*> componentOptions;
    componentOptions.reserve(componentTypes.size());
    for (auto& s : componentTypes) componentOptions.push_back(s.c_str());

    if (!componentOptions.empty()) {
        if (ImGui::Combo("Component Type", &selectedComponentIndex, componentOptions.data(), (int)componentOptions.size())) {
            componentData = nlohmann::json::object();
            previousComponentIndex = selectedComponentIndex;
        }

        std::string selectedComponent = componentOptions[selectedComponentIndex];

        // Show ImGui fields for this component
        try {
            auto tempComponent = ComponentFactory::instance().Create(selectedComponent, componentData);
            tempComponent->getImGuiParams(componentData);
        }
        catch (const std::exception& e) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Error with component UI: %s", e.what());
        }

        // --- Add Component button ---
        if (ImGui::Button("Add Component")) {
            // Store current component selection and its data
            componentsToAdd.push_back({ selectedComponent, componentData });
            componentData = nlohmann::json::object(); // clear data for next component
        }

        // --- List all queued components ---
        if (!componentsToAdd.empty()) {
            ImGui::SeparatorText("Queued Components");
            for (int i = 0; i < componentsToAdd.size(); ++i) {
                ImGui::Text("%d. %s", i + 1, componentsToAdd[i].type.c_str());
            }
        }
    }

#pragma endregion


    





    // Create button
    if (ImGui::Button("Create")) {
        auto obj = std::make_unique<GameObject>();
        obj->SetName(std::string(name));
        obj->_transform->SetTransform({ pos[0], pos[1] }, { scale[0], scale[1] }, rot);

        auto rendererType = rendererOptions[selectedRendererIndex];
        auto renderer = RendererFactory::instance().Create(rendererType, rendererData);
        renderer->SetTransform(obj->_transform.get());
        obj->setRenderer(std::move(renderer));

        GameObject* objPtr = obj.get();

        for (auto& component : componentsToAdd) {
            std::cout << "component type: " << component.type << ", component data: " << component.data << "\n";
            auto c = ComponentFactory::instance().Create(component.type, component.data);
            c->SetParent(objPtr);
            obj->addComponent(std::move(c));
            
        }


        scene.addObject(std::move(obj));
        componentsToAdd.clear();
    }

    ImGui::End();
}