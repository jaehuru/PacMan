// Pacman 
#include "pacPlayScene.h"
#include "pacGameManager.h"
#include "pacPlayer.h"
#include "pacGhost.h"
#include "pacBlinkyScript.h"
// Engine 
#include "Object/huruObject.h"
#include "UI/huruUIManager.h"


namespace pac
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		GameManager::GetInstance().LoadMap();

		// Player
		Player* player = object::Instantiate<Player>(ToEngineLayerType(ePacLayerType::Player), (Vector2(558.f, 258.f)));

		//Ghost
		Ghost* blinky = object::Instantiate<Ghost>(ToEngineLayerType(ePacLayerType::Ghost), (Vector2(558.f, 210.f)));
		blinky->AddComponent<BlinkyScript>();

		//HUD
		UIManager::Push(eUIType::HUD);
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}
