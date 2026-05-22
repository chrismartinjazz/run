#include "Factory.h"
#include <iostream>
#include <vector>
using namespace sf;

Factory::Factory(RenderWindow* window)
    : m_Window { window }
    , m_Texture { new Texture() }
{
    if (!m_Texture->loadFromFile("graphics/texture.png"))
    {
        std::cerr << "Texture not loaded";
        return;
    }
}

void Factory::loadLevel(
    std::vector<GameObject>& gameObjects,
    VertexArray& canvas,
    InputDispatcher& InputDispatcher
)
{
}