//Pacman
#include "pacGameManager.h"
#include "pacPlayScene.h"
#include "pacToolScene.h"
#include "pacVictoryScene.h"
#include "pacTileManager.h"
#include "pacGhostScript.h"
#include "pacGhost.h"
#include "pacHUD.h"
#include "pacGameOverUI.h"
//Engine
#include "Resource/huruResources.h" 
#include "Scene/huruSceneManager.h"
#include "Resource/huruTexture.h"
#include "UI/huruUIManager.h"

namespace pac
{
	void GameManager::Initialize()
	{
		mTileManager = new TileManager();
		LoadResources();
		LoadScenes();

		UIManager::RegisterUIFactory(eUIType::HUD, []() { return new HUD(); });
		UIManager::RegisterUIFactory(ToEngineUIType(ePacUItype::GameOver), []() { return new GameOverUI(); });

		mTotalDotCount = mTileManager->CountTotalDots();
		mRemainingDotCount = mTotalDotCount;
	}

	void GameManager::Release()
	{
		delete mTileManager;
		mTileManager = nullptr;
	}

	void GameManager::LoadResources()
	{
		// SheetSprite
		mSpriteTexture = Resources::Load<graphics::Texture>(L"Sprite", L"../Resources/PacmanSprite.bmp");

		// Dot & Pellet
		mDotTexture = Resources::Load<graphics::Texture>(L"Dot", L"../Resources/img/item/dot.png");
		mPelletTexture = Resources::Load<graphics::Texture>(L"Pellet", L"../Resources/img/item/pellet.png");

		//LifeIcon
		Resources::Load<graphics::Texture>(L"Life0", L"../Resources/img/lives_0.png");
		Resources::Load<graphics::Texture>(L"Life1", L"../Resources/img/lives_1.png");
		Resources::Load<graphics::Texture>(L"Life2", L"../Resources/img/lives_2.png");
		Resources::Load<graphics::Texture>(L"Life3", L"../Resources/img/lives_3.png");
	}

	void GameManager::LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");
		SceneManager::CreateScene<VictoryScene>(L"VictoryScene");

		SceneManager::LoadScene(L"PlayScene");
		// 씬 등록 및 초기화 코드
	}

	void GameManager::LoadMap()
	{
		mTileManager->LoadMapFile(L"../Resources/PacmanMap.tile", mSpriteTexture);
	}

	void GameManager::RegisterGhost(Ghost* ghost)
	{
		mGhosts.push_back(ghost);
	}

	void GameManager::OnPlayerDead()
	{
		mLife--;
		if (mLife <= 0)
		{
			// 게임 오버 처리 (나중에)
		}
	}

	void GameManager::ResetGhosts()
	{
		for (Ghost* ghost : mGhosts)
		{
			GhostScript* ghostScript = ghost->GetComponent<GhostScript>();
			ghostScript->Respawn();
		}
	}

	void GameManager::DecreaseDotCount()
	{
		mRemainingDotCount--;
	}

	Ghost* GameManager::GetGhostByType(ePacGhostType type)
	{
		for (Ghost* ghost : mGhosts)
		{
			GhostScript* ghostScript = ghost->GetComponent<GhostScript>();
			if (ghostScript && ghostScript->GetGhostType() == type)
				return ghost;
		}
		return nullptr;
	}
}