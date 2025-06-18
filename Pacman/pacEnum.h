#pragma once

#include "Common/huruEnums.h"

namespace pac
{
    enum class ePacLayerType : int
    {
        None = (int)::huru::enums::eLayerType::None,
        Background,
        Tile,
        Item,
        Enemy,
        Player,
        Particle,
        Max = (int)::huru::enums::eLayerType::Max
    };
}
