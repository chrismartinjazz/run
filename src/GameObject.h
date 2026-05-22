#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
using namespace sf;

class GameObject
{
  private:
    std::vector<std::shared_ptr<Component>> m_Components {};

  public:
    void addComponent(std::shared_ptr<Component> newComponent);
    void update(float elapsedTime);
    void draw(VertexArray& canvas);
};