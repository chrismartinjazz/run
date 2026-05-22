#pragma once
#include "InputReceiver.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class InputDispatcher
{
  private:
    RenderWindow* m_Window;
    std::vector<InputReceiver*> m_InputReceivers;

  public:
    InputDispatcher(RenderWindow* window);
    void dispatchInputEvents();
    void registerNewInputReceiver(InputReceiver* ir);
};