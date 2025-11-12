#pragma once
#pragma once
#include "Scene.h"
#include "GameObject.h"
#include <memory>

class GUI_SceneHierarchy {
private:
    GameObject* selectedObject = nullptr; // currently selected object
    bool _isVisible = false;
public:

    static GUI_SceneHierarchy& instance() {
        static GUI_SceneHierarchy inst;
        return inst;
    }

    void SetVisible(bool visible) { _isVisible = visible; }
    bool IsVisible() const { return _isVisible; }

    void Open() { _isVisible = true; }
    void Close() { _isVisible = false; }


    // Get the currently selected object (nullptr if none)
    GameObject* getSelectedObject() const {
        return selectedObject;
    }

    void ClearSelectedObject() {
        selectedObject = nullptr;
    }

    void Draw(Scene& scene) {
        if (!_isVisible) return;
        ImGui::Begin("Scene Hierarchy");

        ImGui::SeparatorText("Scene");

         // Create a child box to contain the selectable objects
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(.15f, .15f, .15f, .50f));
        ImGui::BeginChild("HierarchyBox", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        ImGui::PopStyleColor();
        const auto& objects = scene.getObjects();

        for (size_t i = 0; i < objects.size(); ++i) {
            GameObject* obj = objects[i].get();

            bool isSelected = (obj == selectedObject);

            // 
            std::string label = obj->GetName() + "##" + std::to_string(reinterpret_cast<uintptr_t>(obj));
            if (ImGui::Selectable(label.c_str(), isSelected, ImGuiSelectableFlags_SpanAllColumns)) {
                selectedObject = obj;
            }

        }
        ImGui::EndChild();
        ImGui::End();
    }
};
