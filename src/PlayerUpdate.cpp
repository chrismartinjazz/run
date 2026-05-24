#include "PlayerUpdate.h"
#include "LevelUpdate.h"
#include "SoundEngine.h"

FloatRect* PlayerUpdate::getPositionPointer()
{
    return &m_Position;
}

bool* PlayerUpdate::getGroundedPointer()
{
    return &m_IsGrounded;
}

InputReceiver* PlayerUpdate::getInputReceiver()
{
    return &m_InputReceiver;
}

void PlayerUpdate::assemble(
    std::shared_ptr<LevelUpdate> levelUpdate,
    std::shared_ptr<PlayerUpdate> playerUpdate
)
{
    SoundEngine(); // was SoundEngine::SoundEngine() with error 'fully qualified
                   // constructor call is not allowed'
    m_Position.width = PLAYER_WIDTH;
    m_Position.height = PLAYER_HEIGHT;
    m_IsPaused = levelUpdate->getIsPausedPointer();
}

void PlayerUpdate::handleInput()
{
    m_InputReceiver.clearEvents();
}

void PlayerUpdate::update(float timeTakenThisFrame)
{
    handleInput();
}