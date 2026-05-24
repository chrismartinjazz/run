#include "Factory.h"
#include "InputDispatcher.h"
#include "LevelUpdate.h"
#include "PlayerGraphics.h"
#include "PlayerUpdate.h"
#include <iostream>
#include <memory>
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
    InputDispatcher& inputDispatcher
)
{
    // Build a level game object
    GameObject level {};
    std::shared_ptr<LevelUpdate> levelUpdate = std::make_shared<LevelUpdate>();
    level.addComponent(levelUpdate);
    gameObjects.push_back(level);

    // Build a player object
    GameObject player;
    // Create and register playerUpdate
    std::shared_ptr<PlayerUpdate> playerUpdate =
        std::make_shared<PlayerUpdate>();
    playerUpdate->assemble(levelUpdate, nullptr);
    player.addComponent(playerUpdate);
    inputDispatcher.registerNewInputReceiver(playerUpdate->getInputReceiver());

    // Create and register playerGraphics
    std::shared_ptr<PlayerGraphics> playerGraphics =
        std::make_shared<PlayerGraphics>();
    playerGraphics->assemble(
        canvas,
        playerUpdate,
        IntRect(
            PLAYER_TEX_LEFT, PLAYER_TEX_TOP, PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT
        )
    );
    player.addComponent(playerGraphics);

    // The player object is ready, add it to gameObjects
    gameObjects.push_back(player);
    // Make the LevelUpdate aware of the player
    levelUpdate->assemble(nullptr, playerUpdate);
}
