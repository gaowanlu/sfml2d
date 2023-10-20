#pragma once
#include"ControllHandler.h"
#include"ControllHandlerMgr.h"

namespace crustgames {
	class SystemControllHandler :public ControllHandler {
	public:
		SystemControllHandler();
		virtual ~SystemControllHandler();
		virtual void WindowClosed(sf::Event& event);
		//KeyPressed
		virtual void KeyPressed(sf::Event& event);
		virtual void Resized(sf::Event& event);
	};
}