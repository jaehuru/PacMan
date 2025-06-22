#pragma once

#include "Common/CommonInclude.h"
#include "pacEnum.h"
#include "pacDefine.h"

namespace huru 
{
    namespace graphics
    {
        class Texture;
    }
    class Animator; 
}

namespace pac
{
    class TileManager;
    class Ghost;
    class Player;

    class GameManager
    {
    public:
        static GameManager& GetInstance()
        {
            static GameManager instance;
            return instance;
        }

        void        Initialize(); // 리소스 로딩
        void        Release();
  
        void        LoadResources();
        void        LoadScenes();
        void        LoadMap();
        void        RegisterGhost(Ghost* ghost);

        graphics::Texture*      GetSpriteTexture() const    { return mSpriteTexture; }
        TileManager*            GetTileManager() const      { return mTileManager; }
        graphics::Texture*      GetDotTexture() const       { return mDotTexture; }
        graphics::Texture*      GetPelletTexture() const    { return mPelletTexture; }
        const vector<Ghost*>&   GetGhosts() const           { return mGhosts; }
        void                    SetPlayer(Player* player)   { mPlayer = player; }
        Player*                 GetPlayer() const           { return mPlayer; }

    private:
        GameManager() = default;
        ~GameManager() = default;

        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;

    private:
        graphics::Texture*      mSpriteTexture = nullptr;
        TileManager*            mTileManager = nullptr;
        graphics::Texture*      mDotTexture = nullptr;
        graphics::Texture*      mPelletTexture = nullptr;
        Player*                 mPlayer = nullptr;
        vector<Ghost*>          mGhosts;
    };
}
