#pragma once
#include"ControllHandler.h"

namespace crustgames {
	struct MenuItem {
		std::string text;
		sf::Text sfText;
		sf::RectangleShape sfRect;
	};
	class UI :public ControllHandler {
	public:
		enum RenderState {
			SHOW = 0,
			HIDEN
		};
	public:
		UI();
		virtual ~UI();
		virtual void Render();
		virtual void MouseWheelScrolled(sf::Event& evnet);
		RenderState renderState{ HIDEN };
		float scrollOffset = 0.0f;
		float scrollSpeed = 10.0f;
		std::vector<MenuItem> menuItems;
	};
}