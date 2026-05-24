#pragma once
#include "Update.h"
#include <memory>
using namespace sf;

class LevelUpdate : public Update
{
  private:
    bool m_IsPaused { true };
    std::vector<FloatRect*> m_PlatformPositions {};
    float* m_CameraTime { new float };
    FloatRect* m_PlayerPosition {};
    float m_PlatformCreationInterval { 0 };
    float m_TimeSinceLastPlatform { 0 };
    int m_NextPlatformToMove { 0 };
    int m_NumberOfPlatforms { 0 };
    int m_MoveRelativeToPlatform { 0 };
    bool m_GameOver { true };
    void positionLevelAtStart();

  public:
    void addPlatformPosition(FloatRect* newPosition);
    void connectToCameraTime(float* cameraTime);
    bool* getIsPausedPointer();
    int getRandomNumber(int minHeight, int maxHeight);
    // From Update : Component
    void update(float fps) override;
    void assemble(
        std::shared_ptr<LevelUpdate> levelUpdate,
        std::shared_ptr<PlayerUpdate> playerUpdate
    ) override;
};
