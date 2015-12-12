#pragma once

#include <SFML/Graphics.hpp>

struct BasicConfig {
	sf::ContextSettings settings = sf::ContextSettings(0U, 0U, 2U, 1U, 1U, 0U);
	sf::VideoMode video_mode = sf::VideoMode(1280, 720);
	std::string window_title = "Ludum Dare 35";
	std::size_t window_style = sf::Style::Default;

	// @Todo(Nyrox || Lapinozz) Implement config loading and saving
};
