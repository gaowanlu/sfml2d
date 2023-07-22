#include"ControllHandler.h"
#include"ControllHandlerMgr.h"

using crustgames::ControllHandler;
using crustgames::ControllHandlerMgr;

ControllHandler::ControllHandler():m_lifeState(NORMAL) {
    ControllHandlerMgr::Instance().Reg(this);
}

ControllHandler::~ControllHandler() {
    m_lifeState = DONE;
}

void ControllHandler::WindowInitBefore() {

}

void ControllHandler::WindowInitAfter() {

}

void ControllHandler::EventNotifyBefore() {
    
}

void ControllHandler::EventNotifyAfter() {

}

void ControllHandler::WindowClosed(sf::Event& event){

}

void ControllHandler::KeyPressed(sf::Event& event){

}

void ControllHandler::Resized(sf::Event& event){

}

void ControllHandler::LostFocus(sf::Event& event){

}

void ControllHandler::GainedFocus(sf::Event& evnet){

}

void ControllHandler::TextEntered(sf::Event& evnet){

}

void ControllHandler::MouseWheelScrolled(sf::Event& evnet){

}

void ControllHandler::MouseButtonPressed(sf::Event& evnet){

}

void ControllHandler::MouseMoved(sf::Event& evnet){

}

void ControllHandler::MouseEntered(sf::Event& evnet){

}

void ControllHandler::MouseLeft(sf::Event& evnet){

}

void ControllHandler::JoystickButtonPressed(sf::Event& evnet){

}

void ControllHandler::JoystickMoved(sf::Event& evnet){

}

void ControllHandler::JoystickConnected(sf::Event& evnet){

}

void ControllHandler::JoystickDisconnected(sf::Event& evnet){

}

void ControllHandler::Render() {

}

void ControllHandler::ToDone() {
    m_lifeState = WILLDONE;
}

ControllHandler::LifeState ControllHandler::GetLifeState() {
    return m_lifeState;
}