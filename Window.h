#pragma once
#include<SFML/Graphics.hpp>
#include"Conf.h"

namespace crustgames {
	class Window {
	public:
		static Window& Instance();
	private:
		static Window* ptr_;
	public:
		~Window();
		sf::RenderWindow& Get();
		void setView(sf::Vector2f vec2f);
	private:
		sf::RenderWindow window_;
		sf::View view_;
		Window();
	};
}