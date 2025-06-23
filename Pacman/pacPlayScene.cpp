// Pacman 
#include "pacPlayScene.h"
#include "pacGameManager.h"
#include "pacPlayer.h"
#include "pacGhost.h"
#include "pacBlinkyScript.h"
#include "pacClydeScript.h"
#include "pacInkyScript.h"
#include "pacPinkyScript.h"
// Engine 
#include "Object/huruObject.h"
#include "UI/huruUIManager.h"


namespace pac
{
	void PlayScene::Initialize()
	{
		GameManager::GetInstance().LoadMap();

		// Player
		Player* player = object::Instantiate<Player>(ToEngineLayerType(ePacLayerType::Player), (Vector2(558.f, 258.f)));

		//Ghost
		Ghost* blinky = object::Instantiate<Ghost>(ToEngineLayerType(ePacLayerType::Ghost), (Vector2(558.f, 210.f)));
		blinky->AddComponent<BlinkyScript>();
		Ghost* clyde = object::Instantiate<Ghost>(ToEngineLayerType(ePacLayerType::Ghost), (Vector2(546.f, 234.f)));
		clyde->AddComponent<ClydeScript>();
		Ghost* inky = object::Instantiate<Ghost>(ToEngineLayerType(ePacLayerType::Ghost), (Vector2(570.f, 234.f)));
		inky->AddComponent<InkyScript>();
		Ghost* pinky = object::Instantiate<Ghost>(ToEngineLayerType(ePacLayerType::Ghost), (Vector2(558.f, 234.f)));
		pinky->AddComponent<PinkyScript>();


		//HUD
		UIManager::Push(eUIType::HUD);

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		mLife = GameManager::GetInstance().GetLife();
		if (mLife <= 0)
		{
			UIManager::Push(ToEngineUIType(ePacUItype::GameOver));
			return;
		}

		if (GameManager::GetInstance().GetRemainingDotCount() == 0)
		{
			SceneManager::GetActiveScene()->Destroy();
			UIManager::Pop(eUIType::HUD);
			SceneManager::LoadScene(L"VictoryScene");
		}

		Scene::Update();
	}
}
