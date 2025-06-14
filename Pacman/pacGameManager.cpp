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
			int idxX = 0, idxY = 0;
			int posX = 0, posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&idxY, sizeof(int), 1, pFile) != 1) break;
			if (fread(&posX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&posY, sizeof(int), 1, pFile) != 1) break;

			Tile* tile = object::Instantiate<Tile>(ToEngineLayerType(ePacLayerType::Tile), Vector2(posX, posY));
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(texture);
			tmr->SetIndex(Vector2(idxX, idxY));
		}

		fclose(pFile);
	}
}