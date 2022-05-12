#pragma once

#include "imgui.h"
#include "imgui-sfml.h"
#include <SFML/Graphics.hpp>

#include "Dijkstra.h"
#include "Grid.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <tuple>

constexpr std::string_view APP_NAME = "PATHFINDER";
constexpr size_t MAX_MEMORY = 640;

class App
{
public:
	App();
	~App();
	void MainLoop();

private:
	sf::Vector2f GetMousePos();

	std::unique_ptr<sf::RenderWindow> window;
	Grid grid;
	sf::Clock deltaClock;
};

