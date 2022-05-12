#include "App.h"
#include <Windows.h>

App::App() :
    reset(true),
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

            if (reset)
            {
                if (ImGui::Button("Dijkstra"))
                {
                    reset = false;
                    Dijkstra();
                }
            }

            if (ImGui::Button("Reset"))
            {
                ResetToDefault();
                reset = true;
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

void App::ResetToDefault()
{
    grid.ResetToDefault();
}

void App::Dijkstra()
{
    grid.Reset();

    while (grid.CheckForNotVisited())
    {
        std::tuple<int, int> u = grid.GetItemPosWithSmallestDistance();



        auto currentMinimum = grid.GetSingleItem(std::get<0>(u), std::get<1>(u));
        currentMinimum->SetVisited(true);

        for (size_t x = 0; x < currentMinimum->neighbors.size(); x++)
        {
            std::pair<int, int> neighborPos = currentMinimum->neighbors[x];

            if (neighborPos.first == std::get<0>(grid.GetEndPos()) && neighborPos.second == std::get<1>(grid.GetEndPos())) // todo
            {
                std::vector<std::pair<int, int>> path;
                bool done{ false };
                while (!done)
                {
                    currentMinimum->SetState(GridItemState::Magenta);
                    
                    if (currentMinimum->prevPos.first == std::get<0>(grid.GetStartPos()) && currentMinimum->prevPos.second == std::get<1>(grid.GetStartPos()))
                    {
                        done = true;
                    }
                    else
                    {
                        currentMinimum = grid.GetSingleItem(currentMinimum->prevPos.first, currentMinimum->prevPos.second);
                    }
                }

                return;
            }

            auto neighbor = grid.GetSingleItem(neighborPos.first, neighborPos.second);

            int dist = currentMinimum->GetDistance();
            if (dist < neighbor->GetDistance() && neighbor->GetDistance() != INT_MAX)
            {
                neighbor->SetDistance(dist + 1);
                neighbor->prevPos.first = std::get<0>(u);
                neighbor->prevPos.second = std::get<1>(u);
            }
        }
    }
}
