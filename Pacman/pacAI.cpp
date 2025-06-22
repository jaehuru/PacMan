#include "pacAI.h"
#include "pacTileManager.h"
#include "pacTile.h"

namespace pac
{
    vector<int> AI::BFS_FindPath(TileManager* tileManager, int width, int height, int startIndex, int goalIndex)
	{
        vector<int> directions = { 1, -1, width, -width };  // ©Л, аб, го, ╩С
        queue<int> q;
        unordered_map<int, int> cameFrom;

        q.push(startIndex);
        cameFrom[startIndex] = startIndex;

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            if (current == goalIndex)
                break;

            for (int dir : directions)
            {
                int next = current + dir;
                int x = next % width;
                int y = next / width;

                if (x < 0 || x >= width || y < 0 || y >= height)
                    continue;

                Tile* tile = tileManager->GetTile(x, y);
                if (!tile || tile->GetTileType() == Tile::eTileType::Wall)
                    continue;

                if (cameFrom.find(next) == cameFrom.end())
                {
                    q.push(next);
                    cameFrom[next] = current;
                }
            }
        }

        vector<int> path;
        if (cameFrom.find(goalIndex) == cameFrom.end())
            return path;

        int current = goalIndex;
        while (current != startIndex)
        {
            path.push_back(current);
            current = cameFrom[current];
        }
        path.push_back(startIndex);

        std::reverse(path.begin(), path.end());
        return path;
	}
}