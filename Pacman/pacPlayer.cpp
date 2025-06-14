//Pacman
#include "pacPlayer.h"
#include "pacPlayerScript.h"
#include "pacGameManager.h"
//Engine
#include "Component/Transform/huruTransform.h"
#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "Component/Collider/huruBoxCollider2D.h"
#include "Component/Rigidbody/huruRigidbody.h"

namespace pac
{
	Player::Player() :
		mTransform(nullptr),
		mSpriteRenderer(nullptr),
		mDirection(0,0),
		mSpeed(60.f)
	{
		mTransform = AddComponent<Transform>();
		mTransform->SetScale(Vector2(1.55f, 1.55f));
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetTexture(GameManager::GetInstance().GetPacmanTexture());

	
		BoxCollider2D* collider = AddComponent<BoxCollider2D>();
		collider->SetSize(Vector2(24.f, 24.f));  // 월드 단위 크기 (픽셀 크기라 생각해도 무방)
		collider->SetOffset(Vector2(11.f, 12.f));

		SetLayerType(ToEngineLayerType(ePacLayerType::Player));
		AddComponent<PlayerScript>();
	}

	Player::~Player()
	{

	}

	void Player::Initialize()
	{
		mSpriteRenderer->SetTexture(GameManager::GetInstance().GetPacmanTexture());

		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Player::Render(HDC hdc)
	{
		mSpriteRenderer->Render(hdc);
		GameObject::Render(hdc);
	}
}