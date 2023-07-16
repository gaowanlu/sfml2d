#include<iostream>
#include"SystemControllHandler.h"
#include"Window.h"

using crustgames::SystemControllHandler;
using crustgames::Window;
using crustgames::ControllHandlerMgr;

SystemControllHandler::SystemControllHandler() {
	ControllHandlerMgr::Instance().reg(this);
}

SystemControllHandler::~SystemControllHandler() {

}

void SystemControllHandler::WindowClosed(sf::Event& event) {
	Window::Instance().Get().close();
}

void SystemControllHandler::KeyPressed(sf::Event& event) {
	std::cout << "key press" << std::endl;
}