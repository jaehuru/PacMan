//Pacman
#include "pacBlinkyScript.h"
#include "pacGhost.h"
//Engine
#include "Component/Transform/huruTransform.h"
#include "Component/Animator/huruAnimator.h"
#include "Component/SpriteRenderer/huruSpriteRenderer.h"

namespace pac
{
	BlinkyScript::BlinkyScript()
	{

	}

	BlinkyScript::~BlinkyScript()
	{

	}

	void BlinkyScript::Initialize()
	{
		GhostScript::Initialize();

		if (mAnimator)
		{
			mAnimator->CreateAnimationByFolder(L"Blinky_Left", L"../Resources/img/ghost/blinky/left", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Blinky_Right", L"../Resources/img/ghost/blinky/right", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Blinky_Up", L"../Resources/img/ghost/blinky/up", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Blinky_Down", L"../Resources/img/ghost/blinky/down", Vector2::Zero, 0.1f);

			mAnimator->PlayAnimation(L"Blinky_Left", true);
		}
	}

	void BlinkyScript::Update()
	{
		GhostScript::Update();
	}

	void BlinkyScript::LateUpdate()
	{
		GhostScript::LateUpdate();
	}

	void BlinkyScript::Render(HDC hdc)
	{
		GhostScript::Render(hdc);
	}

	void BlinkyScript::OnCollisionEnter(Collider* other)
	{
		GhostScript::OnCollisionEnter(other);
	}

	void BlinkyScript::OnCollisionStay(Collider* other)
	{
		GhostScript::OnCollisionStay(other);
	}

	void BlinkyScript::OnCollisionExit(Collider* other)
	{
		GhostScript::OnCollisionExit(other);
	}

	Vector2 BlinkyScript::CalculateTargetPosition()
	{
		return Vector2();
	}

	void BlinkyScript::EndNerf()
	{
		GhostScript::EndNerf();

		if (mAnimator)
		{
			// 현재 이동 방향에 따라 알맞은 애니메이션 재생
			mAnimator->PlayAnimation(L"Blinky_Left", true);
		}
	}

	void BlinkyScript::HandleNormalState()
	{
		// 개별적으로 처리 virtual 함수
	}

}