// Pacman 
#include "pacPlayScene.h"
#include "pacGameManager.h"
#include "pacToolScene.h"
#include "pacPlayer.h"
#include "pacPlayerScript.h"
// Engine 
#include "../JaehuruEngine/Engine/public/Component/Camera/huruCamera.h"
#include "../JaehuruEngine/Engine/public/GameObject/huruGameObject.h"
#include "../JaehuruEngine/Engine/public/Component/huruComponent.h"
#include "../JaehuruEngine/Engine/public/Object/huruObject.h"
#include "../JaehuruEngine/Engine/public/Renderer/huruRenderer.h"
#include "../JaehuruEngine/Engine/public/Resource/huruTexture.h"


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
		GameManager::GetInstance().LoadResources();
		GameManager::GetInstance().LoadMap();

		// Player
		Vector2 startTilePos = Vector2(46, 21);
		Vector2 startPos = Vector2(
			startTilePos.x * Tile::Size.x + Tile::Size.x * 0.5f,
			startTilePos.y * Tile::Size.y + Tile::Size.y * 0.5f);

		GameObject* player = object::Instantiate<Player>(ToEngineLayerType(ePacLayerType::Player),
															(Vector2(startPos.x, startPos.y)));

		Scene::Initialize();
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
