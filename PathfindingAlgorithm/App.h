#pragma once

#include "imgui.h"
#include "imgui-sfml.h"
#include <SFML/Graphics.hpp>

#include "Grid.h"

#include <memory>
#include <string>

constexpr std::string_view APP_NAME = "PATHFINDER";
constexpr size_t MAX_MEMORY = 640;

class App
{
public:
	App();
	~App();
	void MainLoop();

private:
	std::unique_ptr<sf::RenderWindow> window;
	Grid grid;
	sf::Clock deltaClock;
	sf::View view;

};

