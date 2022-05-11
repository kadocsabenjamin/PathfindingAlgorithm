#include "App.h"
#include <Windows.h>

App::App() :
    window(std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), APP_NAME.data()))
{
    ImGui::SFML::Init(*window);

	MainLoop();
}

App::~App()
{
	ImGui::SFML::Shutdown();
}

void App::MainLoop()
{
    

    while (window->isOpen())
    {
        ImGui::SFML::Update(*window, deltaClock.restart());

        sf::Event event;
        ImGui::SFML::ProcessEvent(event);

        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        window->clear();

        grid.Draw(window);

        // imgui
        {
            ImGui::Begin("controls");


            ImGui::End();
        }

        grid.Update(GetMousePos(), GridItemState::Black); //TODO nem csak ez a state van

        ImGui::SFML::Render(*window);
        window->display();
        //Sleep(20);
    }
}

sf::Vector2f App::GetMousePos()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
    return worldPos;
}
