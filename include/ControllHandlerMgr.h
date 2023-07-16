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
		ControllHandlerMgr()=default;
	private:
		static ControllHandlerMgr* ptr_;
		std::list<ControllHandler*>list_;
	public:
		void reg(ControllHandler* item);
		void remove(ControllHandler*item);
		void notify(sf::Event&event);
	};
}