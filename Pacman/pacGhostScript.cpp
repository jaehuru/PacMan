//Pacman
#include "pacGhostScript.h"
#include "pacGhost.h"
#include "pacTile.h"
#include "pacGameManager.h"
#include "pacTileManager.h"
#include "pacPlayerScript.h"
#include "pacPlayer.h"
#include "pacPlayerScript.h"
#include "pacUtility.h"
//Engine
#include "Component/Transform/huruTransform.h"
#include "Component/Animator/huruAnimator.h"
#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "Helpers/huruTime.h"



namespace pac
{
	GhostScript::GhostScript(ePacGhostType type) :
		mAnimator(nullptr),
		mSpawnPos(Vector2::Zero),
		mState(eState::Normal),
		mTransform(nullptr),
		mFrightenedTimer(0.f),
		mIsFlashing(false),
		mFlashTimer(0.f),
		FrightenedDuration(8.f),
		FlashStartTime(3.f),
		FlashInterval(0.2f),
		mSpeed(46.f),
		mNormalSpeed(46.f),
		mNerfSpeed(30.f),
		mDeadSpeed(100.f),
		mCurrentAnimName(L""),
		mCurrentDirection(Vector2::Zero),
		mTargetTileCenter(Vector2::Zero),
		DIR_UP(Vector2(0, -1)),
		DIR_DOWN(Vector2(0, 1)),
		DIR_LEFT(Vector2(-1, 0)),
		DIR_RIGHT(Vector2(1, 0)),
		mJailPos(Vector2(558.f, 236.f)),
		mDeadWaitTimer(0.f),
		mPortalCoolTime(0.f),
		mType(type)
	{

	}


	void GhostScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();
		mPortals = GameManager::GetInstance().GetTileManager()->GetPortalTiles();
		
		mAnimator->CreateAnimationByFolder(L"Nerf_Blue", L"../Resources/img/ghost/nerf/blue", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimationByFolder(L"Nerf_White", L"../Resources/img/ghost/nerf/white", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimationByFolder(L"Dead_UP", L"../Resources/img/ghost/dead/up", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimationByFolder(L"Dead_Down", L"../Resources/img/ghost/dead/down", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimationByFolder(L"Dead_Left", L"../Resources/img/ghost/dead/left", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimationByFolder(L"Dead_Right", L"../Resources/img/ghost/dead/right", Vector2::Zero, 0.1f);

		mCurrentDirection = DIR_UP;

		Vector2 tilePos = util::WorldToTile(mTransform->GetPosition());
		mTargetTileCenter = util::SnapToTileCenter(tilePos);
	}

	void GhostScript::Update()
	{
		switch (mState)
		{
		case eState::Normal:
			HandleNormalState();
			break;
		case eState::Nerf:
			HandleNerfState();
			ConnectedPlayerInNerf();
			break;
		case eState::Dead:
			HandleDeadState();
			break;
		case eState::Wait:
			HandleWaitState();
		}
	}

	void GhostScript::LateUpdate()
	{
		Script::LateUpdate();
	}

	void GhostScript::Render(HDC hdc)
	{
		Script::Render(hdc);
	}

	void GhostScript::HandleNerfState()
	{
		UpdateMovement(true);

		// 기존 nerf 타이머, 깜빡임 로직 유지
		UpdateNerfTimers();
	}

	void GhostScript::HandleNormalState()
	{
		UpdateMovement(false);
	}

	void GhostScript::HandleDeadState()
	{
		int jailTileX = static_cast<int>(mJailPos.x / Tile::Size.x);
		int jailTileY = static_cast<int>(mJailPos.y / Tile::Size.y);

		UpdateDeadMovement(jailTileX, jailTileY);
	}

	void GhostScript::HandleWaitState()
	{
		mDeadWaitTimer -= Time::DeltaTime();
		if (mDeadWaitTimer <= 0.f)
		{
			mState = eState::Normal;
			mSpeed = mNormalSpeed;

			mCurrentDirection = DIR_UP;

			Vector2 jailTile = util::WorldToTile(mJailPos);
			mTargetTileCenter = util::SnapToTileCenter(jailTile);

			PlayAnimByDir(mCurrentDirection);
		}
	}

	void GhostScript::BeginNerf()
	{
		if (mState == eState::Dead)
			return;

		mState = eState::Nerf;
		mFrightenedTimer = FrightenedDuration;
		mIsFlashing = false;
		mSpeed = mNerfSpeed;

		
		mAnimator->PlayAnimation(L"Nerf_Blue", true);
	}

	void GhostScript::EndNerf()
	{
		mState = eState::Normal;
		mIsFlashing = false;
		mSpeed = mNormalSpeed;

		PlayAnimByDir(mCurrentDirection);
	}

	void GhostScript::UpdateMovement(bool isEscaping)
	{
		Vector2 pos = mTransform->GetPosition();
		Vector2 tilePos = util::WorldToTile(pos);
		Vector2 center = util::SnapToTileCenter(tilePos);

		if ((center - pos).length() < 0.1f)
		{
			mTransform->SetPosition(center);

			if (mPortalCoolTime <= 0.0f)
			{
				if (util::IsOnPortalTile(tilePos, mPortals))
				{
					util::TeleportToOtherPortal(tilePos, mTransform, mPortals);
					mPortalCoolTime = 0.08f;
					return;
				}
			}
			else
			{
				mPortalCoolTime -= Time::DeltaTime();
			}

			Vector2 prevDir = mCurrentDirection;
			UpdateDirection(isEscaping);

			if (mCurrentDirection != prevDir && mState == eState::Normal)
				PlayAnimByDir(mCurrentDirection);

			Vector2 nextTile = tilePos + mCurrentDirection;
			mTargetTileCenter = util::SnapToTileCenter(nextTile);
		}

		if (mCurrentDirection == Vector2::Zero)
			return;

		Vector2 move = mCurrentDirection * mSpeed * Time::DeltaTime();
		Vector2 nextPos = mTransform->GetPosition() + move;
		Vector2 toCenter = mTargetTileCenter - nextPos;

		mTransform->SetPosition
		(
			((mCurrentDirection.x != 0 && fabs(toCenter.x) < fabs(move.x)) ||
				(mCurrentDirection.y != 0 && fabs(toCenter.y) < fabs(move.y)))
			? mTargetTileCenter : nextPos
		);
	}

	void GhostScript::UpdateDirection(bool isEscaping)
	{
		Player* player = GameManager::GetInstance().GetPlayer();
		Vector2 playerPos = player->GetComponent<PlayerScript>()->GetCurrentPosition();
		Vector2 targetPos = GetTargetPosition(playerPos);

		Vector2 tilePos = util::WorldToTile(mTargetTileCenter);
		int idxX = static_cast<int>(tilePos.x);
		int idxY = static_cast<int>(tilePos.y);

		Vector2 bestDir = mCurrentDirection;
		float bestScore = isEscaping ? -FLT_MAX : FLT_MAX;
		bool hasValid = false;

		for (const auto& dir : directions)
		{
			if (dir == -mCurrentDirection)
				continue;

			int nx = idxX + static_cast<int>(dir.x);
			int ny = idxY + static_cast<int>(dir.y);

			if (IsWall(nx, ny))
				continue;

			hasValid = true;

			Vector2 tileCenter = Vector2((nx + 0.5f) * Tile::Size.x, (ny + 0.5f) * Tile::Size.y);
			float score = (tileCenter - targetPos).length();

			if (isEscaping)
			{
				if (score > bestScore) { bestScore = score; bestDir = dir; }
			}
			else
			{
				if (score < bestScore) { bestScore = score; bestDir = dir; }
			}
		}

		if (!hasValid)
			bestDir = -mCurrentDirection;

		mCurrentDirection = bestDir;
	}

	Vector2 GhostScript::GetPlayerPosition()
	{
		Player* pacman = GameManager::GetInstance().GetPlayer();
		PlayerScript* script = pacman->GetComponent<PlayerScript>();
		return script->GetOwner()->GetComponent<Transform>()->GetPosition();
	}

	bool GhostScript::IsWall(int tileX, int tileY)
	{
		Tile* tile = GameManager::GetInstance().GetTileManager()->GetTile(tileX, tileY);
		return (!tile || tile->GetTileType() == Tile::eTileType::Wall);
	}

	void GhostScript::PlayAnimByDir(const Vector2& direction)
	{
		if (direction == Vector2::Zero)
		{
			mAnimator->Stop();
			mCurrentAnimName = L"";
			return;
		}
	}

	void GhostScript::UpdateAnimation(const wstring& newAnim)
	{
		if (!newAnim.empty() && newAnim != mCurrentAnimName && mAnimator)
		{
			mAnimator->PlayAnimation(newAnim, true);
			mCurrentAnimName = newAnim;
		}
	}

	void GhostScript::UpdateNerfTimers()
	{
		mFrightenedTimer -= Time::DeltaTime();

		if (mFrightenedTimer <= 0.f)
		{
			EndNerf();
			return;
		}

		if (mFrightenedTimer <= FlashStartTime && !mIsFlashing)
		{
			mIsFlashing = true;
			mAnimator->PlayAnimation(L"Nerf_White", true);
			mFlashTimer = FlashInterval;
		}

		if (mIsFlashing)
		{
			mFlashTimer -= Time::DeltaTime();
			if (mFlashTimer <= 0.f)
			{
				mAnimator->PlayAnimation
				(
					(mAnimator->GetActiveAnimationName() == L"Nerf_White") ?
					L"Nerf_Blue" : L"Nerf_White", true
				);

				mFlashTimer = FlashInterval;
			}
		}
	}

	void GhostScript::ConnectedPlayerInNerf()
	{
		Vector2 playerPos = GetPlayerPosition();
		Vector2 ghostPos = mTransform->GetPosition();

		Vector2 pTile = util::WorldToTile(playerPos);
		Vector2 gTile = util::WorldToTile(ghostPos);

		if (pTile == gTile)
		{
			mState = eState::Dead;
			mSpeed = mDeadSpeed;
			DeadByDirection(mCurrentDirection);
		}
	}

	void GhostScript::DeadByDirection(const Vector2& direction)
	{
		const wstring anim = (fabs(direction.x) > fabs(direction.y))
			? (direction.x > 0 ? L"Dead_Right" : L"Dead_Left")
			: (direction.y > 0 ? L"Dead_Down" : L"Dead_UP");

		mAnimator->PlayAnimation(anim, true);
	}

	void GhostScript::UpdateDeadMovement(int targetTileX, int targetTileY)
	{
		Vector2 pos = mTransform->GetPosition();
		Vector2 tilePos = util::WorldToTile(pos);
		Vector2 center = util::SnapToTileCenter(tilePos);

		if ((center - pos).length() < 0.1f)
		{
			mTransform->SetPosition(center);

			if (tilePos.x == targetTileX && tilePos.y == targetTileY)
			{
				mTransform->SetPosition(mJailPos);
				mState = eState::Wait;
				mDeadWaitTimer = 1.0f;  // 1초 대기
				mSpeed = 0.f;
				PlayAnimByDir(Vector2::Zero);
				return;
			}

			UpdateDeadDirection(targetTileX, targetTileY);

			Vector2 nextTile = tilePos + mCurrentDirection;
			mTargetTileCenter = util::SnapToTileCenter(nextTile);
		}

		if (mCurrentDirection != Vector2::Zero)
		{
			Vector2 move = mCurrentDirection * mSpeed * Time::DeltaTime();
			Vector2 nextPos = pos + move;
			Vector2 toCenter = mTargetTileCenter - nextPos;

			mTransform->SetPosition(
				((mCurrentDirection.x != 0 && fabs(toCenter.x) < fabs(move.x)) ||
					(mCurrentDirection.y != 0 && fabs(toCenter.y) < fabs(move.y)))
				? mTargetTileCenter : nextPos
			);

			DeadByDirection(mCurrentDirection);
		}
	}

	void GhostScript::UpdateDeadDirection(int targetTileX, int targetTileY)
	{
		Vector2 tilePos = util::WorldToTile(mTargetTileCenter);
		int idxX = static_cast<int>(tilePos.x);
		int idxY = static_cast<int>(tilePos.y);

		Vector2 bestDir = mCurrentDirection;
		float bestScore = FLT_MAX;
		bool  hasValid = false;

		Vector2 jailCenter = Vector2((targetTileX + 0.5f) * Tile::Size.x, (targetTileY + 0.5f) * Tile::Size.y);

		for (auto& dir : directions)
		{
			if (dir == -mCurrentDirection)
				continue;

			int nx = idxX + static_cast<int>(dir.x);
			int ny = idxY + static_cast<int>(dir.y);
			if (IsWall(nx, ny))
				continue;

			hasValid = true;
			Vector2 tileCtr = Vector2((nx + 0.5f) * Tile::Size.x, (ny + 0.5f) * Tile::Size.y);
			float score = (tileCtr - jailCenter).length();

			if (score < bestScore)
			{
				bestScore = score;
				bestDir = dir;
			}
		}

		if (!hasValid)
			bestDir = -mCurrentDirection;

		mCurrentDirection = bestDir;
	}

	void GhostScript::Respawn()
	{
		mTransform->SetPosition(mSpawnPos);
		mState = eState::Normal;
		mSpeed = mNormalSpeed;
		mCurrentDirection = DIR_UP;
		mTargetTileCenter = util::SnapToTileCenter(util::WorldToTile(mTransform->GetPosition()));
		PlayAnimByDir(mCurrentDirection);
	}
}

