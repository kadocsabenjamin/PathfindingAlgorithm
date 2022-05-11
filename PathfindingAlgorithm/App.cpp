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
        ImGui::SFML::Update(*window, deltaClock.restart());

        // imgui
        {
            ImGui::Begin("controls");


            ImGui::End();
        }



        ImGui::SFML::Render(*window);
        window->display();
        Sleep(20);
    }
}
