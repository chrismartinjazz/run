#pragma once
#include "Graphics.h"
using namespace sf;

// class Animator;
class PlayerUpdate;
class PlayerGraphics : public Graphics
{
  private:
    FloatRect* m_Position { nullptr };
    int m_VertexStartIndex = -999;
    // Animator* m_Animator;
    IntRect* m_SectionToDraw { new IntRect };
    IntRect* m_StandingStillSectionToDraw { new IntRect };
    std::shared_ptr<PlayerUpdate> m_PlayerUpdate {};
    const int BOOST_TEX_LEFT { 536 };
    const int BOOST_TEX_TOP { 0 };
    const int BOOST_TEX_WIDTH { 69 };
    const int BOOST_TEX_HEIGHT { 100 };
    bool m_LastFacingRight { true };

  public:
    // From Component : Graphics
    void assemble(
        VertexArray& canvas,
        std::shared_ptr<Update> genericUpdate,
        IntRect texCoords
    ) override;
    void draw(VertexArray& canvas) override;
};