#include "LevelUpdate.h"
#include "PlayerUpdate.h"
#include "SoundEngine.h"
#include <memory>
#include <random>

void LevelUpdate::assemble(
    std::shared_ptr<LevelUpdate> levelUpdate,
    std::shared_ptr<PlayerUpdate> playerUpdate
)
{
    m_PlayerPosition = playerUpdate->getPositionPointer();
}

void LevelUpdate::connectToCameraTime(float* cameraTime)
{
    m_CameraTime = cameraTime;
}

void LevelUpdate::addPlatformPosition(FloatRect* newPosition)
{
    m_PlatformPositions.push_back(newPosition);
    ++m_NumberOfPlatforms;
}

bool* LevelUpdate::getIsPausedPointer()
{
    return &m_IsPaused;
}

void LevelUpdate::positionLevelAtStart()
{
    float startOffset { m_PlatformPositions[0]->left };
    for (int i { 0 }; i < m_NumberOfPlatforms; ++i)
    {
        m_PlatformPositions[i]->left = i * 100 + startOffset;
        m_PlatformPositions[i]->top = 0;
        m_PlatformPositions[i]->width = 100;
        m_PlatformPositions[i]->height = 20;
    }
    // TODO fix magic numbers + 2 and - 22
    m_PlayerPosition->left =
        m_PlatformPositions[m_NumberOfPlatforms / 2]->left + 2;
    m_PlayerPosition->top =
        m_PlatformPositions[m_NumberOfPlatforms / 2]->top - 22;
    m_MoveRelativeToPlatform = m_NumberOfPlatforms - 1;
    m_NextPlatformToMove = 0;
}

int LevelUpdate::getRandomNumber(int minHeight, int maxHeight)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minHeight, maxHeight);
    int randomHeight { distribution(gen) };
    return randomHeight;
}

void LevelUpdate::update(float timeSinceLastUpdate)
{
    if (!m_IsPaused)
    {
        // If the game is over, reset and start a new game
        if (m_GameOver)
        {
            m_GameOver = false;
            *m_CameraTime = 0;
            m_TimeSinceLastPlatform = 0;
            int platformToPlacePlayerOn {};
            positionLevelAtStart();
        }

        // Increment the timer
        *m_CameraTime += timeSinceLastUpdate;
        m_TimeSinceLastPlatform += timeSinceLastUpdate;

        // Create (move to the front) a new platform if it is time to do so
        if (m_TimeSinceLastPlatform > m_PlatformCreationInterval)
        {
            // Set the height of the next platform randomly
            m_PlatformPositions[m_NextPlatformToMove]->top =
                m_PlatformPositions[m_MoveRelativeToPlatform]->top +
                getRandomNumber(-40, 40);

            // How far away to create the next platform
            // Bigger gap if lower than previous
            if (m_PlatformPositions[m_MoveRelativeToPlatform]->top <
                m_PlatformPositions[m_NextPlatformToMove]->top)
            {
                m_PlatformPositions[m_NextPlatformToMove]->left =
                    m_PlatformPositions[m_MoveRelativeToPlatform]->left +
                    m_PlatformPositions[m_MoveRelativeToPlatform]->width +
                    getRandomNumber(20, 40);
            }
            else
            {
                m_PlatformPositions[m_NextPlatformToMove]->left =
                    m_PlatformPositions[m_MoveRelativeToPlatform]->left +
                    m_PlatformPositions[m_MoveRelativeToPlatform]->width +
                    getRandomNumber(0, 20);
            }

            // Set the width and height of the next platform randomly
            m_PlatformPositions[m_NextPlatformToMove]->width =
                getRandomNumber(20, 200);
            m_PlatformPositions[m_NextPlatformToMove]->height =
                getRandomNumber(10, 20);

            // Base the time to create the next platform on the width of the one
            // just created
            m_PlatformCreationInterval =
                m_PlatformPositions[m_NextPlatformToMove]->width / 90;
            m_MoveRelativeToPlatform = m_NextPlatformToMove;

            // Prepare to move the next platform in the sequence, handling if we
            // are at the final platform, and reset the platform creation timer
            ++m_NextPlatformToMove;
            if (m_NextPlatformToMove == m_NumberOfPlatforms)
            {
                m_NextPlatformToMove = 0;
            }
            m_TimeSinceLastPlatform = 0;
        }

        // Has the player lagged behind the furthest back platform?
        bool laggingBehind { true };
        for (auto platformPosition : m_PlatformPositions)
        {
            if (platformPosition->left < m_PlayerPosition->left)
            {
                laggingBehind = false;
                break; // At least one platform is behind the player
            }
            else
            {
                laggingBehind = true;
            }
        }

        // If the player is lagging behind, the game is over
        if (laggingBehind)
        {
            m_IsPaused = true;
            m_GameOver = true;
            SoundEngine::pauseMusic();
        }
    }
}