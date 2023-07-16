#include"ControllHandlerMgr.h"
using crustgames::ControllHandlerMgr;

ControllHandlerMgr* ControllHandlerMgr::ptr_=nullptr;

ControllHandlerMgr& ControllHandlerMgr::Instance() {
	if (ptr_ == nullptr) {
		ptr_ = new ControllHandlerMgr;
	}
	return *ptr_;
}

ControllHandlerMgr::~ControllHandlerMgr() {
	for (auto ptr : list_) {
		delete ptr;
	}
}

void ControllHandlerMgr::reg(ControllHandler* item) {
	for (auto ptr : list_) {
		if (ptr == item) { return; }
	}
	list_.push_back(item);
}

void ControllHandlerMgr::remove(ControllHandler* item) {
	for (auto iter = list_.begin(); iter != list_.end();++iter) {
		if (*iter == item) {
			list_.erase(iter);
			return;
		}
	}
}

void ControllHandlerMgr::notify(sf::Event& event) {
	switch (event.type)
	{
	case sf::Event::Closed:
		for (auto ptr : list_) {
			ptr->WindowClosed(event);
		}
		break;
	case sf::Event::KeyPressed:		
		for (auto ptr : list_) {
			ptr->KeyPressed(event);
		}
		break;
	case sf::Event::Resized:
		for (auto ptr : list_) {
			ptr->Resized(event);
		}
		break;
	case sf::Event::LostFocus:
		for (auto ptr : list_) {
			ptr->LostFocus(event);
		}
		break;
	case sf::Event::GainedFocus:
		for (auto ptr : list_) {
			ptr->GainedFocus(event);
		}
		break;
	case sf::Event::TextEntered:
		for (auto ptr : list_) {
			ptr->TextEntered(event);
		}
		break;
	case sf::Event::MouseWheelScrolled:
		for (auto ptr : list_) {
			ptr->MouseWheelScrolled(event);
		}
		break;
	case sf::Event::MouseButtonPressed:
		for (auto ptr : list_) {
			ptr->MouseButtonPressed(event);
		}
		break;
	case sf::Event::MouseMoved:
		for (auto ptr : list_) {
			ptr->MouseMoved(event);
		}
		break;
	case sf::Event::MouseEntered:
		for (auto ptr : list_) {
			ptr->MouseEntered(event);
		}
		break;
	case sf::Event::MouseLeft:
		for (auto ptr : list_) {
			ptr->MouseLeft(event);
		}
		break;
	case sf::Event::JoystickButtonPressed:
		for (auto ptr : list_) {
			ptr->JoystickButtonPressed(event);
		}
		break;
	case sf::Event::JoystickMoved:
		for (auto ptr : list_) {
			ptr->JoystickMoved(event);
		}
		break;
	case sf::Event::JoystickConnected:
		for (auto ptr : list_) {
			ptr->JoystickConnected(event);
		}
		break;
	case sf::Event::JoystickDisconnected:
		for (auto ptr : list_) {
			ptr->JoystickDisconnected(event);
		}
		break;
	default:
		break;
	}
}