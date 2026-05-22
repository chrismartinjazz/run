#include "InputReceiver.h"

void InputReceiver::addEvent(Event event)
{
    m_Events.push_back(event);
}

std::vector<Event>& InputReceiver::getEvents()
{
    return m_Events;
}

void InputReceiver::clearEvents()
{
    m_Events.clear();
}