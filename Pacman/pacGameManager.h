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

    class GameManager
    {
    public:
        static GameManager& GetInstance()
        {
            static GameManager instance;
            return instance;
        }

        void        Initialize(); // ���ҽ� �ε�
        void        Release();
  
        void        LoadResources();
        void        LoadScenes();
        void        LoadMap();
        void        RegisterGhost(Ghost* ghost);

        graphics::Texture*      GetSpriteTexture()  const { return mSpriteTexture; }
        TileManager*            GetTileManager()    { return mTileManager; }
        graphics::Texture* GetDotTexture() { return mDotTexture; }
        graphics::Texture* GetPelletTexture() { return mPelletTexture; }
        const vector<Ghost*>& GetGhosts() const { return mGhosts; }

    private:
        GameManager() = default;
        ~GameManager() = default;

        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;

    private:
        graphics::Texture* mSpriteTexture = nullptr;
        TileManager* mTileManager = nullptr;
        graphics::Texture* mDotTexture = nullptr;
        graphics::Texture* mPelletTexture = nullptr;
        vector<Ghost*> mGhosts;
    };
}
