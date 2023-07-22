#pragma once
#include<SFML/Graphics.hpp>

namespace crustgames {
    class ControllHandler {
    public:
        enum LifeState {
            NORMAL=0,
            WILLDONE,
            DONE
        };
    public:
        ControllHandler();
        virtual ~ControllHandler();
        virtual void WindowInitBefore();
        virtual void WindowInitAfter();
        virtual void EventNotifyBefore();
        virtual void EventNotifyAfter();
        virtual void Render();
        virtual void WindowClosed(sf::Event& event);
        virtual void KeyPressed(sf::Event& event);
        virtual void Resized(sf::Event& event);
        virtual void LostFocus(sf::Event& event);
        virtual void GainedFocus(sf::Event& evnet);
        virtual void TextEntered(sf::Event& evnet);
        virtual void MouseWheelScrolled(sf::Event& evnet);
        virtual void MouseButtonPressed(sf::Event& evnet);
        virtual void MouseMoved(sf::Event& evnet);
        virtual void MouseEntered(sf::Event& evnet);
        virtual void MouseLeft(sf::Event& evnet);
        virtual void JoystickButtonPressed(sf::Event& evnet);
        virtual void JoystickMoved(sf::Event& evnet);
        virtual void JoystickConnected(sf::Event& evnet);
        virtual void JoystickDisconnected(sf::Event& evnet);
        virtual void ToDone();
        LifeState GetLifeState();
    private:
        LifeState m_lifeState;
    };
}