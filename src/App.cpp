#include<iostream>
#include"App.h"
#include"Window.h"

using crustgames::App;

App::~App() {

}

void App::WindowInitBefore() {

}

void App::WindowInitAfter() {

}

void App::EventNotifyBefore() {
	
}

void App::EventNotifyAfter() {
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	Window::Instance().Get().clear();
	Window::Instance().Get().draw(shape);
	Window::Instance().Get().display();
	fps.Show();
	std::cout << "fps: "<<fps.Get() << std::endl;
}