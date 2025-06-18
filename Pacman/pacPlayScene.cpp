// Pacman 
#include "pacPlayScene.h"
#include "pacGameManager.h"
#include "pacToolScene.h"
#include "pacPlayer.h"
#include "pacPlayerScript.h"
// Engine 
#include "Component/Camera/huruCamera.h"
#include "GameObject/huruGameObject.h"
#include "Component/huruComponent.h"
#include "Object/huruObject.h"
#include "Renderer/huruRenderer.h"
#include "Resource/huruTexture.h"


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
		GameObject* player = object::Instantiate<Player>(ToEngineLayerType(ePacLayerType::Player),
															(Vector2(558.f, 258.f)));
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
