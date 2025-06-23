//Pacman
#include "pacInkyScript.h"
#include "pacPlayer.h"
#include "pacPlayerScript.h"
#include "pacGameManager.h"
#include "pacTile.h"
#include "pacGhost.h"
#include "pacBlinkyScript.h"
//Engine
#include "Component/Animator/huruAnimator.h"
#include "Component/Transform/huruTransform.h"



namespace pac
{
	InkyScript::InkyScript() :
		GhostScript(ePacGhostType::Inky)
	{

	}

	void InkyScript::Initialize()
	{
		mSpawnPos = Vector2(570.f, 234.f);
		GhostScript::Initialize();

		if (mAnimator)
		{
			mAnimator->CreateAnimationByFolder(L"Inky_Left", L"../Resources/img/ghost/inky/left", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Inky_Right", L"../Resources/img/ghost/inky/right", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Inky_Up", L"../Resources/img/ghost/inky/up", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Inky_Down", L"../Resources/img/ghost/inky/down", Vector2::Zero, 0.1f);

			mAnimator->PlayAnimation(L"Inky_Left", true);
		}
	}

	void InkyScript::PlayAnimByDir(const Vector2& direction)
	{
		GhostScript::PlayAnimByDir(direction);

		const wstring newAnim = (fabs(direction.x) > fabs(direction.y))
			? ((direction.x > 0) ? L"Inky_Right" : L"Inky_Left")
			: ((direction.y > 0) ? L"Inky_Down" : L"Inky_Up");

		UpdateAnimation(newAnim);
	}

	Vector2	InkyScript::GetTargetPosition(const Vector2& playerPos)
	{
		Player* player = GameManager::GetInstance().GetPlayer();
		Vector2 playerDir = player->GetComponent<PlayerScript>()->GetCurrentDirection();
		Vector2 playerAhead = playerPos + playerDir * Tile::Size * 2;

		Ghost* blinky = GameManager::GetInstance().GetGhostByType(ePacGhostType::Blinky);
		Vector2 blinkyPos = blinky->GetComponent<Transform>()->GetPosition();

		Vector2 diff = playerAhead - blinkyPos;
		Vector2 target = blinkyPos + diff * 2;
		return target;
	}
}