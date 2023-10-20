#include <iostream>
#include <SFML/Graphics.hpp>
#include "Conf.h"
#include "Window.h"
#include "ControllHandlerMgr.h"
#include "My2DShape.h"
#include "SystemControllHandler.h"
#include "ControllHandler.h"
#include "Physics.h"

using crustgames::Window;
using crustgames::ControllHandlerMgr;
using crustgames::ControllHandler;
using crustgames::My2DShape;
using crustgames::SystemControllHandler;
using crustgames::Physics;

int main()
{
	Physics::Instance();//物理引擎
	ControllHandlerMgr::Instance();
	new My2DShape();
	new SystemControllHandler();
	ControllHandlerMgr::Instance().WindowInitBefore();
	Window::Instance();
	ControllHandlerMgr::Instance().WindowInitAfter();
	while (Window::Instance().Get().isOpen())//窗口是否打开
	{
		//更新Box2d世界
		Physics::Instance().world_.Step(1.0f / 60.f, 6, 2);
		ControllHandlerMgr::Instance().EventNotifyBefore();
		sf::Event event;//窗口事件
		while (Window::Instance().Get().pollEvent(event))
		{
			ControllHandlerMgr::Instance().Notify(event);
		}
		ControllHandlerMgr::Instance().EventNotifyAfter();
		//Render
		Window::Instance().Get().clear();
		ControllHandlerMgr::Instance().Render();
		Window::Instance().Get().display();
	}
	return 0;
}
