//Pacman
#include "pacPlayer.h"
#include "pacPlayerScript.h"
#include "pacGameManager.h"
//Engine
#include "Component/Animator/huruAnimator.h"

namespace pac
{
	Player::Player() :
		mAnimator(nullptr)
	{
		mAnimator = AddComponent<Animator>();
		SetLayerType(ToEngineLayerType(ePacLayerType::Player));
		AddComponent<PlayerScript>();
		GameManager::GetInstance().SetPlayer(this);
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