#pragma once

#include "Common/CommonInclude.h"

namespace huru::graphics
{
    class Texture;
}

namespace pac
{
    class Tile;
    class Dot;
    class Pellet;

    class TileManager
    {
    public:
        void        LoadMapFile(const wstring& filePath, graphics::Texture* texture);
        Tile*       GetTile(int x, int y);
        void        Clear();

        const vector<Tile*>&    GetTileMap()        const { return mTileMap; }
        const vector<Tile*>&    GetPortalTiles()    const { return mPortalTiles; }
        const vector<Dot*>&     GetDots()           const { return mDots; }
        const vector<Pellet*>&  GetPellets()        const { return mPellets; }


    private:
        vector<Tile*>       mTileMap;
        vector<Tile*>       mPortalTiles;
        vector<Dot*>        mDots;
        vector<Pellet*>     mPellets;
    };
}
