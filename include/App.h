#pragma once

#include"FPS.h"

namespace crustgames {
	class App {
	public:
		void WindowInitBefore();
		void WindowInitAfter();
		void EventNotifyBefore();
		void EventNotifyAfter();
	private:
		FPS fps;
	};
}