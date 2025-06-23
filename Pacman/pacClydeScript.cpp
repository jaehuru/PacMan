//Pacman
#include "pacClydeScript.h"
#include "pacTile.h"
#include "pacTileManager.h"
#include "pacGameManager.h"
#include "pacUtility.h"
//Engine
#include "Component/Animator/huruAnimator.h"
#include "Component/Transform/huruTransform.h"



namespace pac
{
	ClydeScript::ClydeScript() :
		GhostScript(ePacGhostType::Clyde)
	{
	}

	void ClydeScript::Initialize()
	{
		mSpawnPos = Vector2(546.f, 234.f);
		GhostScript::Initialize();

		if (mAnimator)
		{
			mAnimator->CreateAnimationByFolder(L"Clyde_Left", L"../Resources/img/ghost/clyde/left", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Clyde_Right", L"../Resources/img/ghost/clyde/right", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Clyde_Up", L"../Resources/img/ghost/clyde/up", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Clyde_Down", L"../Resources/img/ghost/clyde/down", Vector2::Zero, 0.1f);

			mAnimator->PlayAnimation(L"Clyde_Left", true);
		}
	}

	void ClydeScript::PlayAnimByDir(const Vector2& direction)
	{
		GhostScript::PlayAnimByDir(direction);

		const wstring newAnim = (fabs(direction.x) > fabs(direction.y))
			? ((direction.x > 0) ? L"Clyde_Right" : L"Clyde_Left")
			: ((direction.y > 0) ? L"Clyde_Down" : L"Clyde_Up");

		UpdateAnimation(newAnim);
	}

	Vector2	ClydeScript::GetTargetPosition(const Vector2& playerPos)
	{
		Vector2 clydePos = util::WorldToTile(mTransform->GetPosition());
		float distance = (clydePos - playerPos).length();
		float mapHeight = GameManager::GetInstance().GetTileManager()->GetMapHeight();
		if (distance > Tile::Size.x * 8) 
			return playerPos;
		else
			return Vector2(0, mapHeight * Tile::Size.y);
	}
}