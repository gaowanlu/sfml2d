#include"UI.h"
#include"Window.h"
#include<iostream>
#include<string>
#include<vector>
#include<SFML/Graphics/RectangleShape.hpp>

using crustgames::UI;
using crustgames::Window;

UI::UI() :ControllHandler() {

}

UI::~UI() {
	std::cout << "UI �ڴ����" << std::endl;
}

void UI::Render() {
	if (renderState != SHOW) {
		return;
	}
	menuItems.clear();
	//��ȡ���ڴ�С
	const int windowWidth = Window::Instance().Get().getSize().x;
	const int windowHeight = Window::Instance().Get().getSize().y;
	//ȡ���ڵ����ĵ�
	const int windowCenterX = windowWidth / 2;
	const int windowCenterY = windowHeight / 2;
	//�������ڴ�С
	const int alertWidth = 400;
	const int alertHeight = 300;
	//�ҳ����ڵ����Ͻǵ�
	const int alertLeftTopX = windowCenterX - alertWidth / 2;
	const int alertLeftTopY = windowCenterY - alertHeight / 2;
	//��������
	sf::RectangleShape rect;
	rect.setPosition(alertLeftTopX, alertLeftTopY);
	rect.setSize(sf::Vector2f(alertWidth,alertHeight));
	rect.setFillColor(sf::Color(255,255,255,200));
	//�����б�
	rect.setOutlineColor(sf::Color::White);
	//����
	sf::Font font;
	if (!font.loadFromFile("asset/waltographUI.ttf")) {
		std::cout << "load ttf error" << std::endl;
		return;
	}
	for (int i = 0; i < 20; ++i) {
		MenuItem item;
		item.text = std::string("ITEM [")+std::to_string(i)+"]";
		item.sfText.setFont(font);
		item.sfText.setString(item.text);
		item.sfText.setCharacterSize(30);
		item.sfText.setFillColor(sf::Color::Black);
		item.sfText.setPosition(alertLeftTopX, alertLeftTopY + i * 40);
		item.sfRect.setSize(sf::Vector2f(item.sfText.getGlobalBounds().width, item.sfText.getGlobalBounds().height));
		item.sfRect.setPosition(item.sfText.getPosition());
		item.sfRect.setFillColor(sf::Color::Transparent);
		menuItems.push_back(item);
	}
	Window::Instance().Get().draw(rect);
	for (int i = 0; i < menuItems.size(); i++) {
		if (menuItems[i].sfText.getPosition().y + scrollOffset >= 100 && menuItems[i].sfText.getPosition().y + scrollOffset <= 400) {
			menuItems[i].sfText.setPosition(alertLeftTopX, alertLeftTopY + i * 40 + scrollOffset);
			menuItems[i].sfRect.setPosition(menuItems[i].sfText.getPosition());
			Window::Instance().Get().draw(menuItems[i].sfRect);
			Window::Instance().Get().draw(menuItems[i].sfText);
		}
		Window::Instance().Get().draw(menuItems[i].sfText);
	}
	std::cout << "UI::Render" << std::endl;
}

void UI::MouseWheelScrolled(sf::Event & event) {
	scrollOffset += event.mouseWheelScroll.delta * scrollSpeed;
	scrollOffset += event.mouseWheelScroll.delta * scrollSpeed;
	if (scrollOffset > 0)
		scrollOffset = 0;
	else if (scrollOffset < -((int)menuItems.size() - 5) * 40)
		scrollOffset = -((int)menuItems.size() - 5) * 40;
	std::cout << "���� scrollOffset="<<scrollOffset<<" scrollSpeed="<<scrollSpeed << std::endl;
}