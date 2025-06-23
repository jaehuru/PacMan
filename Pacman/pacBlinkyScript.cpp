//Pacman
#include "pacBlinkyScript.h"
#include "pacEnum.h"
//Engine
#include "Component/Animator/huruAnimator.h"


namespace pac
{
	BlinkyScript::BlinkyScript() :
		GhostScript(ePacGhostType::Blinky)
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

	void BlinkyScript::PlayAnimByDir(const Vector2& direction)
	{
		GhostScript::PlayAnimByDir(direction);

		const wstring newAnim = (fabs(direction.x) > fabs(direction.y))
			? ((direction.x > 0) ? L"Blinky_Right" : L"Blinky_Left") 
			: ((direction.y > 0) ? L"Blinky_Down" : L"Blinky_Up");

		UpdateAnimation(newAnim);
	}
}