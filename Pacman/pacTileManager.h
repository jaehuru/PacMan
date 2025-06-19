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

        const vector<Tile*>&    GetTileMap()        const { return mTileMap; }
        const vector<Tile*>&    GetPortalTiles()    const { return mPortalTiles; }

        Tile* GetTile(int x, int y);
        
    private:
        vector<Tile*>       mTileMap;
        vector<Tile*>       mPortalTiles;
    };
}
