#include<iostream>
#include"SystemControllHandler.h"
#include"Window.h"

using crustgames::SystemControllHandler;
using crustgames::Window;

SystemControllHandler::SystemControllHandler() {

}

SystemControllHandler::~SystemControllHandler() {

}

void SystemControllHandler::WindowClosed(sf::Event& event) {
	Window::Instance().Get().close();
}

void SystemControllHandler::KeyPressed(sf::Event& event) {
	//std::cout << "key press" << std::endl;
}

void SystemControllHandler::Resized(sf::Event& event) {
	// ������Ϸ��ͼ�Ĵ�С����Ӧ�µĴ��ڴ�С
	Window::Instance().setView(sf::Vector2f(event.size.width, event.size.height));
}