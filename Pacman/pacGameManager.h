#pragma once

#include "Common/CommonInclude.h"
#include "pacEnum.h"
#include "pacDefine.h"

namespace huru::graphics { class Texture; }
namespace huru { class Animator; }

namespace pac
{
    class TileManager;

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

        graphics::Texture*      GetSpriteTexture()  const { return mSpriteTexture; }
        TileManager*            GetTileManager()    { return mTileManager; }
        graphics::Texture* GetDotTexture() { return mDotTexture; }
        graphics::Texture* GetPelletTexture() { return mPelletTexture; }

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
    };
}
