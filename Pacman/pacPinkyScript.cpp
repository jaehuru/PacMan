//Pacman
#include "pacPinkyScript.h"
#include "pacPlayer.h"
#include "pacPlayerScript.h"
#include "pacGameManager.h"
#include "pacTile.h"
//Engine
#include "Component/Animator/huruAnimator.h"


namespace pac
{
	PinkyScript::PinkyScript() :
		GhostScript(ePacGhostType::Pinky)
	{

	}

	void PinkyScript::Initialize()
	{
		mSpawnPos = Vector2(558.f, 234.f);
		GhostScript::Initialize();

		if (mAnimator)
		{
			mAnimator->CreateAnimationByFolder(L"Pinky_Left", L"../Resources/img/ghost/pinky/left", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Pinky_Right", L"../Resources/img/ghost/pinky/right", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Pinky_Up", L"../Resources/img/ghost/pinky/up", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Pinky_Down", L"../Resources/img/ghost/pinky/down", Vector2::Zero, 0.1f);

			mAnimator->PlayAnimation(L"Pinky_Left", true);
		}
	}

	void PinkyScript::PlayAnimByDir(const Vector2& direction)
	{
		GhostScript::PlayAnimByDir(direction);

		const wstring newAnim = (fabs(direction.x) > fabs(direction.y))
			? ((direction.x > 0) ? L"Pinky_Right" : L"Pinky_Left")
			: ((direction.y > 0) ? L"Pinky_Down" : L"Pinky_Up");

		UpdateAnimation(newAnim);
	}

	Vector2	PinkyScript::GetTargetPosition(const Vector2& playerPos)
	{
		Player* player = GameManager::GetInstance().GetPlayer();
		Vector2 playerDir = player->GetComponent<PlayerScript>()->GetCurrentDirection();
		Vector2 target = playerPos + playerDir * Tile::Size * 4;
		return target;
	}
}