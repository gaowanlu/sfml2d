#pragma once
#include<list>
#include<SFML/Graphics.hpp>

#include"ControllHandler.h"

namespace crustgames {
	class ControllHandlerMgr {
	public:
		static ControllHandlerMgr& Instance();
		~ControllHandlerMgr();
	private:
		ControllHandlerMgr() = default;
	private:
		static ControllHandlerMgr controllHandlerInstance;
		std::list<ControllHandler*>list_;
	public:
		void Reg(ControllHandler* item);
		void Remove(ControllHandler* item);
		void Notify(sf::Event& event);
		void WindowInitBefore();
		void WindowInitAfter();
		void EventNotifyBefore();
		void EventNotifyAfter();
		void Render();

	};
}