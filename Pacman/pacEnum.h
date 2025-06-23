#pragma once

#include "Common/huruEnums.h"

namespace pac
{
    enum class ePacLayerType
    {
        None = huru::enums::eLayerType::None,
        Background,
        Item,
        Ghost,
        Player,
        Tile,
        Particle,
        Max = huru::enums::eLayerType::Max
    };

    enum class ePacUItype
    {
        Button = huru::enums::eUIType::Button,
        HUD = huru::enums::eUIType::HUD,
        GameOver,
        End = huru::enums::eUIType::End,
    };

    enum class ePacGhostType
    {
        Blinky,
        Clyde,
        Inky,
        Pinky,
        None
    };
}
