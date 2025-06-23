//Pacman
#include "pacBlinkyScript.h"
#include "pacGhost.h"
#include "pacPlayer.h"
#include "pacPlayerScript.h"
#include "pacGameManager.h"
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
		mSpawnPos = Vector2(558.f, 210.f);
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

	void BlinkyScript::PlayAnimByDir(const Vector2& direction)
	{
		GhostScript::PlayAnimByDir(direction);

		const wstring newAnim = (fabs(direction.x) > fabs(direction.y))
			? ((direction.x > 0) ? L"Blinky_Right" : L"Blinky_Left") 
			: ((direction.y > 0) ? L"Blinky_Down" : L"Blinky_Up");

		UpdateAnimation(newAnim);
	}
}