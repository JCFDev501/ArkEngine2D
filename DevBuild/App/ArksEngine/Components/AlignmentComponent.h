#pragma once
#include "Component.h"

namespace ArksEngine
{
	class Core;
}

enum Alignment
{
    CENTER,             // Center of the screen
    TOP,                // Top-center of the screen
    BOTTOM,             // Bottom-center of the screen
    LEFT,               // Left-center of the screen
    RIGHT,              // Right-center of the screen

    TOP_LEFT,           // Top-left corner
    TOP_RIGHT,          // Top-right corner
    BOTTOM_LEFT,        // Bottom-left corner
    BOTTOM_RIGHT,       // Bottom-right corner

    CENTER_LEFT,        // Center-left (middle left)
    CENTER_RIGHT,       // Center-right (middle right)
    CENTER_TOP,         // Center-top (top-center)
    CENTER_BOTTOM       // Center-bottom (bottom-center)
};


namespace ArksEngineComponents
{
    class TransformComponent;

    class AlignmentComponent : public Component
    {
        ArksEngine::Core* m_pOwner = nullptr;
        ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;
        Alignment m_pAligment = LEFT;
        int m_ScreenWidth = 0;
        int m_ScreenHeight = 0;
        int m_OffsetX = 0; // Offset in X-axis
        int m_OffsetY = 0; // Offset in Y-axis

    public:
        AlignmentComponent(ArksEngine::Core* pOwner);

        void Init() override;

        void Update(double deltaTime) override;

        // Setters for alignment and offset
        void SetAlignment(Alignment alignment);
        void SetOffset(int offsetX, int offsetY);
    };
}


