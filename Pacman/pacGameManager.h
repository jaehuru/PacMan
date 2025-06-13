#pragma once

#include "Common/CommonInclude.h"

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

        void        LoadMapFile(const std::wstring& filePath, ::huru::graphics::Texture* texture);

        ::huru::graphics::Texture* GetSpriteTexture() const { return mSpriteTexture; }

    private:
        GameManager() = default;
        ~GameManager() = default;

        GameManager(const GameManager&) = delete;
        GameManager& operator=(const GameManager&) = delete;

    private:
        ::huru::graphics::Texture* mSpriteTexture = nullptr;
    };
}
