#include"ControllHandlerMgr.h"
using crustgames::ControllHandlerMgr;

ControllHandlerMgr ControllHandlerMgr::controllHandlerInstance;

ControllHandlerMgr& ControllHandlerMgr::Instance() {
	return controllHandlerInstance;
}

ControllHandlerMgr::~ControllHandlerMgr() {
	for (auto ptr : list_) {
		delete ptr;
	}
}

void ControllHandlerMgr::Reg(ControllHandler* item) {
	for (auto ptr : list_) {
		if (ptr == item) { return; }
	}
	list_.push_back(item);
}

void ControllHandlerMgr::Remove(ControllHandler* item) {
	for (auto iter = list_.begin(); iter != list_.end(); ++iter) {
		if (*iter == item) {
			delete item;
			list_.erase(iter);
			return;
		}
	}
}

void ControllHandlerMgr::Notify(sf::Event& event) {
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

void ControllHandlerMgr::WindowInitBefore() {
	for (auto ptr : list_) {
		ptr->WindowInitBefore();
	}
}

void ControllHandlerMgr::WindowInitAfter() {
	for (auto ptr : list_) {
		ptr->WindowInitAfter();
	}
}

void ControllHandlerMgr::EventNotifyBefore() {
	//À¬»ø»ØÊÕ
	for (auto iter = list_.begin(); iter != list_.end(); ) {
		if (ControllHandler::WILLDONE == (*iter)->GetLifeState()) {
			delete (*iter);
			iter = list_.erase(iter);
		}
		else {
			++iter;
		}
	}
	for (auto ptr : list_) {
		ptr->EventNotifyBefore();
	}
}

void ControllHandlerMgr::EventNotifyAfter() {
	for (auto ptr : list_) {
		ptr->EventNotifyAfter();
	}
}

void ControllHandlerMgr::Render() {
	for (auto ptr : list_) {
		ptr->Render();
	}
}