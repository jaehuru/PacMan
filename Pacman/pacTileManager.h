#pragma once

#include "Common/CommonInclude.h"

namespace huru::graphics
{
    class Texture;
}

namespace pac
{
    class Tile;

    class TileManager
    {
    public:
        void        LoadMapFile(const wstring& filePath, graphics::Texture* texture);
        void        Clear();
        int         CountTotalDots();

        Tile*                   GetTile(int x, int y);
        const vector<Tile*>&    GetTileMap()            const { return mTileMap; }
        const vector<Tile*>&    GetPortalTiles()        const { return mPortalTiles; }
        int                     GetMapWidth()           const { return mMapWidth; }
        int                     GetMapHeight()          const { return mMapHeight; }
        
    private:
        vector<Tile*>       mTileMap;
        vector<Tile*>       mPortalTiles;

        int                 mMapWidth = 0;
        int                 mMapHeight = 0;
    };
}
