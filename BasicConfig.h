#pragma once

#include <SFML/Graphics.hpp>

struct BasicConfig {
	sf::ContextSettings settings = sf::ContextSettings(0U, 0U, 2U, 1U, 1U);
	sf::VideoMode video_mode = sf::VideoMode(1280-100, 720-50);
//	sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();

	std::string window_title = "War...";
	std::size_t window_style = sf::Style::Default xor sf::Style::Resize;

	// @Todo(Nyrox || Lapinozz) Implement config loading and saving
};
