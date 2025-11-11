// MOXEngineGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "pch.h"
#include "PlayerMovement.h"
#include "Event.h"
#include "SceneLoader.h"
#include "Scene.h"

sf::RenderWindow window;
sf::View playerView;



using json = nlohmann::json;



int main()
{
    Input::Initialize();
    Input::ResetToDefaultBinds();
    playerView = sf::View({ 0,0 }, { 1920,1080 });

    window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project");
    window.setView(playerView);
    window.setFramerateLimit(144);
 

    std::ifstream file("../assets/prefabs/testScene.json");
    if (!file.is_open()) {
        std::cerr << "failed to open scene \n";
        return 1;
    }

    json data;
    try {
        file >> data;
    }
    catch (const json::parse_error& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return 1;
    }

    std::unique_ptr<Scene> curScene = LoadScene(data);

    /*
    new GameObject({ 0, 0});
    test->setRenderer<CircleRenderer>(test->_transform.get(), 64, 5);
    test->addComponent<PlayerMovement>();
    test->addComponent<Button>();*/

    sf::Clock dtClock;

    while (window.isOpen())
    {
        Input::Update();

        sf::Time dt = dtClock.restart();
        float deltaTime = dt.asSeconds();

        window.clear();

        while (const std::optional event = window.pollEvent())
        {
            Input::HandleEvent(event);
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
        }


        curScene->Update(deltaTime);
        curScene->Draw();

        window.display();

    }

    Input::SaveInputToFile();

}
