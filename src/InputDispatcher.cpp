#include "InputDispatcher.h"
using namespace sf;

InputDispatcher::InputDispatcher(RenderWindow* window)
    : m_Window { window }
{
}

void InputDispatcher::dispatchInputEvents()
{
    Event event;
    while (m_Window->pollEvent(event))
    {
        // TODO: remove this statement once event handling closes window
        if (event.type == Event::KeyPressed &&
            event.key.code == Keyboard::Escape)
        {
            m_Window->close();
        }
        // end TODO
        for (const auto& ir : m_InputReceivers)
        {
            ir->addEvent(event);
        }
    }
}

void InputDispatcher::registerNewInputReceiver(InputReceiver* ir)
{
    m_InputReceivers.push_back(ir);
}