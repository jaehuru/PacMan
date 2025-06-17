#pragma once

#include "Common/CommonInclude.h"
#include "pacEnum.h"
#include "pacDefine.h"

namespace huru::graphics { class Texture; }
namespace huru { class Animator; }

namespace pac
{
    class Tile;

    class GameManager
    {
    public:
        static GameManager& GetInstance()
        {
            static GameManager instance;
            return instance;
        }

        void        Initialize(); // 리소스 로딩
  
        void        LoadResources();
        void        LoadScenes();
        void        LoadMap();
        void        LoadMapFile(const wstring& filePath, graphics::Texture* texture);

        graphics::Texture*      GetSpriteTexture()  const { return mSpriteTexture; }
        const vector<Tile*>&    GetTileMap()        const { return mTileMap; }
        const vector<Tile*>&    GetPortalTiles()    const { return mPortalTiles; }

    private:
        GameManager() = default;
        ~GameManager() = default;

        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;

    private:
        Animator* mAnimator;

        graphics::Texture* mSpriteTexture = nullptr;

       vector<Tile*> mTileMap;
       vector<Tile*> mPortalTiles;
    };
}
