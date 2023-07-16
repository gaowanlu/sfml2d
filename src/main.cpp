#include <iostream>
#include <SFML/Graphics.hpp>
#include "Conf.h"
#include "Window.h"
#include "ControllHandlerMgr.h"
#include "App.h"
#include "SystemControllHandler.h"

using crustgames::Window;
using crustgames::ControllHandlerMgr;
using crustgames::App;
using crustgames::SystemControllHandler;

int main()
{
    App app;
    SystemControllHandler systemControllHandler;
    app.WindowInitBefore();
    Window::Instance();
    app.WindowInitAfter();
    while (Window::Instance().Get().isOpen())//窗口是否打开
    {
        app.EventNotifyBefore();
        sf::Event event;//窗口事件
        while (Window::Instance().Get().pollEvent(event))
        {
            ControllHandlerMgr::Instance().notify(event);
        }
        app.EventNotifyAfter();
    }
    return 0;
}