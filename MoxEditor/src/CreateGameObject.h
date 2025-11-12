#pragma once
#include "Scene.h"
#include "RendererFactory.h"



class GUI_CreateGameObject {
private:
    // Persistent GUI state
    char name[64] = "NewObject";
    float pos[2] = { 0.f, 0.f };
    float scale[2] = { 1.f, 1.f };
    float rot = 0.f;

    static inline int selectedRendererIndex = 0;
    static inline int previousRendererIndex = -1;
    static inline nlohmann::json rendererData = nlohmann::json::object();

    static inline int selectedComponentIndex = 0;
    static inline int previousComponentIndex = -1;
    static inline nlohmann::json componentData = nlohmann::json::object();

    struct QueuedComponent
    {
        std::string type;
        nlohmann::json data;
    };

    std::vector<QueuedComponent> componentsToAdd;


public:
    void draw(Scene& scene);
};
