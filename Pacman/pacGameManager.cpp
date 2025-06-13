//Pacman
#include "pacGameManager.h"
#include "pacPlayScene.h"
#include "pacToolScene.h"
#include "pacTile.h"
//Engine
#include "Resource/huruResources.h" 
#include "Scene/huruSceneManager.h"
#include "Resource/huruTexture.h"
#include <Component/TileMapRenderer/huruTileMapRenderer.h>
#include <Object/huruObject.h>

namespace pac
{
	void GameManager::Initialize()
	{
		LoadResources();
		LoadScenes();
	}

	void GameManager::LoadResources()
	{
		mSpriteTexture = ::huru::Resources::Load<huru::graphics::Texture>(L"Sprite", L"..\\Resources\\PacmanSprite.bmp");
	}

	void GameManager::LoadScenes()
	{
		::huru::SceneManager::CreateScene<PlayScene>(L"PlayScene");
		::huru::SceneManager::CreateScene<ToolScene>(L"ToolScene");

		::huru::SceneManager::LoadScene(L"PlayScene");
		// 씬 등록 및 초기화 코드
	}

	void GameManager::LoadMap()
	{
		LoadMapFile(L"..\\Resources\\PacmanMap.tile", mSpriteTexture);
	}

	void GameManager::LoadMapFile(const std::wstring& filePath, ::huru::graphics::Texture* texture)
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, filePath.c_str(), L"rb");

		if (!pFile)
		{
			std::wstring msg = L"Failed to open file: " + filePath;
			MessageBox(nullptr, msg.c_str(), L"Error", MB_OK);
			return;
		}

		while (true)
		{
			int idxX = 0, idxY = 0;
			int posX = 0, posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&idxY, sizeof(int), 1, pFile) != 1) break;
			if (fread(&posX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&posY, sizeof(int), 1, pFile) != 1) break;

			Tile* tile = ::huru::object::Instantiate<Tile>(::huru::enums::eLayerType::Tile, ::huru::math::Vector2(posX, posY));
			::huru::TileMapRenderer* tmr = tile->AddComponent<::huru::TileMapRenderer>();
			tmr->SetTexture(texture);
			tmr->SetIndex(::huru::math::Vector2(idxX, idxY));
		}

		fclose(pFile);
	}
}