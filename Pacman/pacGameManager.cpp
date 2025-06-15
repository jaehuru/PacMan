//Pacman
#include "pacGameManager.h"
#include "pacPlayScene.h"
#include "pacToolScene.h"
#include "pacTile.h"
//Engine
#include "Resource/huruResources.h" 
#include "Scene/huruSceneManager.h"
#include "Resource/huruTexture.h"
#include "Component/TileMapRenderer/huruTileMapRenderer.h"
#include "Object/huruObject.h"
#include "Collision/huruCollisionManager.h"

namespace pac
{
	void GameManager::Initialize()
	{
		LoadResources();

		CollisionManager::CollisionLayerCheck(
			ToEngineLayerType(ePacLayerType::Player),
			ToEngineLayerType(ePacLayerType::Tile),
			true
		);

		LoadScenes();
	}

	void GameManager::LoadResources()
	{
		mSpriteTexture = Resources::Load<graphics::Texture>(L"Sprite", L"..\\Resources\\PacmanSprite.bmp");
		mPacmanTexture = Resources::Load<graphics::Texture>(L"Pacman", L"..\\Resources\\img\\pacman\\1.png");
	}

	void GameManager::LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");

		SceneManager::LoadScene(L"PlayScene");
		// 씬 등록 및 초기화 코드
	}

	void GameManager::LoadMap()
	{
		LoadMapFile(L"..\\Resources\\PacmanMap.tile", mSpriteTexture);
	}

	void GameManager::LoadMapFile(const wstring& filePath, graphics::Texture* texture)
	{
		// 기존 타일 초기화
		for (Tile* tile : mTileMap)
			object::Destroy(tile);
		mTileMap.clear();
		mTileMap.resize(define::MaxMapWidth * define::MaxMapHeight, nullptr);

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, filePath.c_str(), L"rb");

		if (!pFile)
		{
			wstring msg = L"Failed to open file: " + filePath;
			MessageBox(nullptr, msg.c_str(), L"Error", MB_OK);
			return;
		}

		while (true)
		{
			int tool_idxX = 0, tool_idxY = 0;
			int tool_posX = 0, tool_posY = 0;

			if (fread(&tool_idxX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_idxY, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_posX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_posY, sizeof(int), 1, pFile) != 1) break;

			Tile* tile = object::Instantiate<Tile>(ToEngineLayerType(ePacLayerType::Tile), Vector2(tool_posX, tool_posY));
			int tileTypeInt = 0;
			if (fread(&tileTypeInt, sizeof(int), 1, pFile) != 1) break;
			tile->SetTileType(static_cast<Tile::eTileType>(tileTypeInt));

			int tileIdxX = tool_posX / Tile::Size.x;
			int tileIdxY = tool_posY / Tile::Size.y;
			int linearIndex = define::GetLinearIndex(tileIdxX, tileIdxY);

			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(texture);
			tmr->SetSize(Tile::Size);
			tmr->SetScale(Tile::Scale);
			tmr->SetIndex(Vector2(tool_idxX, tool_idxY));

			tile->SetIndexPosition(tileIdxX, tileIdxY);

			if (linearIndex >= 0 && linearIndex < static_cast<int>(mTileMap.size()))
			{
				mTileMap[linearIndex] = tile;
			}
		}

		fclose(pFile);
	}
}