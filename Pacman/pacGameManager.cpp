//Pacman
#include "pacGameManager.h"
#include "pacPlayScene.h"
#include "pacToolScene.h"
#include "pacTileManager.h"
//Engine
#include "Resource/huruResources.h" 
#include "Scene/huruSceneManager.h"
#include "Resource/huruTexture.h"

namespace pac
{
	void GameManager::Initialize()
	{
		mTileManager = new TileManager();
		LoadResources();
		LoadScenes();
	}

	void GameManager::Release()
	{
		delete mTileManager;
		mTileManager = nullptr;
	}

	void GameManager::LoadResources()
	{
		mSpriteTexture = Resources::Load<graphics::Texture>(L"Sprite", L"../Resources/PacmanSprite.bmp");

		mDotTexture = Resources::Load<graphics::Texture>(L"Dot", L"../Resources/img/item/dot.png");
		mPelletTexture = Resources::Load<graphics::Texture>(L"Pellet", L"../Resources/img/item/pellet.png");
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
		mTileManager->LoadMapFile(L"../Resources/PacmanMap.tile", mSpriteTexture);
	}
}