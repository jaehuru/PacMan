// Pacman 
#include "pacPlayScene.h"
#include "pacGameManager.h"
#include "pacToolScene.h"
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
		//MapLoad
		GameManager::GetInstance().LoadMap();

		//Camera
		::huru::GameObject* camera = ::huru::object::Instantiate<huru::GameObject>(::huru::enums::eLayerType::Particle, ::huru::math::Vector2(344.0f, 442.0f));
		::huru::Camera* cameraComp = camera->AddComponent<::huru::Camera>();
		::huru::renderer::mainCamera = cameraComp;



		// Player



		// Sound
		//AudioClip* ac = Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\Sound\\...");


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
