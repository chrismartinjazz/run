#include "GameObject.h"
#include "Graphics.h"
#include "Update.h"
#include <SFML/Graphics.hpp>
#include <iostream> // Why??
#include <memory>
using namespace sf;

void GameObject::addComponent(std::shared_ptr<Component> newComponent)
{
    m_Components.push_back(newComponent);
}

void GameObject::update(float elapsedTime)
{
    for (auto component : m_Components)
    {
        if (component->m_IsUpdate)
        {
            std::static_pointer_cast<Update>(component)->update(elapsedTime);
        }
    }
}

void GameObject::draw(VertexArray& canvas)
{
    for (auto component : m_Components)
    {
        if (component->m_IsGraphics)
        {
            std::static_pointer_cast<Graphics>(component)->draw(canvas);
        }
    }
}