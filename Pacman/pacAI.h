#pragma once

#include "Common/CommonInclude.h"

namespace pac
{
    class TileManager;

    class AI
    {
    public:
        static vector<int> BFS_FindPath(TileManager* tileManager, int width, int height, int startIndex, int goalIndex);
    };
}

