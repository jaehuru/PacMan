//Pacman
#include "pacPlayer.h"
#include "pacPlayerScript.h"
#include "pacGameManager.h"
//Engine
#include "Component/Transform/huruTransform.h"
#include "Component/Animator/huruAnimator.h"

namespace pac
{
	Player::Player() :
		mTransform(nullptr),
		mAnimator(nullptr)
	{
		mTransform = AddComponent<Transform>();
		mTransform->SetScale(Vector2(1.f, 1.f));
		mAnimator = AddComponent<Animator>();

		SetLayerType(ToEngineLayerType(ePacLayerType::Player));
		AddComponent<PlayerScript>();
	}

	Player::~Player()
	{

	}

	void Player::Initialize()
	{
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
		GameObject::Render(hdc);
	}
}