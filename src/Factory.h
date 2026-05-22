#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class InputDispatcher;
class Factory
{
  private:
    RenderWindow* m_Window;

  public:
    Factory(RenderWindow* window);
    void loadLevel(
        std::vector<GameObject>& gameObjects,
        VertexArray& canvas,
        InputDispatcher& inputDispatcher
    );
    Texture* m_Texture;
};