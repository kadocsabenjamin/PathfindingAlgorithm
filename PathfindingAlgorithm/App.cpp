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
    bool placeStart{ false };
    bool placeEnd{ false };

    Dijkstra d(grid);
    d.Reset();

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
        window->clear(sf::Color::Blue);

        grid.Draw(window);

        // imgui
        {
            ImGui::Begin("controls");

            if (ImGui::Button("Start")) 
            {
                placeStart = true;
            }
            else if (ImGui::Button("End"))
            {
                placeEnd = true;
            }

            ImGui::End();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if (placeStart)
            {
                grid.DeleteStartPos();
                placeStart = false;
            }
            else if (placeEnd)
            {
                grid.DeleteEndPos();
                placeEnd = false;
            }
            
            grid.Update(GetMousePos(), GridItemState::Black);
            
        }
        //d.Update();

        ImGui::SFML::Render(*window);
        
        window->display();
    }
}

sf::Vector2f App::GetMousePos()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);
    return worldPos;
}
