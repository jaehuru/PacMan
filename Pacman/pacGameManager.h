#pragma once

#include "Common/CommonInclude.h"
#include "pacEnum.h"

namespace huru::graphics { class Texture; }

namespace pac
{
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

        graphics::Texture* GetSpriteTexture() const { return mSpriteTexture; }
        graphics::Texture* GetPacmanTexture() const { return mPacmanTexture; }

    private:
        GameManager() = default;
        ~GameManager() = default;

        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;

    private:
        graphics::Texture* mSpriteTexture = nullptr;
        graphics::Texture* mPacmanTexture = nullptr;
    };
}
