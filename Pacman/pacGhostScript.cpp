//Pacman
#include "pacGhostScript.h"
#include "pacGhost.h"
#include "pacTile.h"
#include "pacGameManager.h"
#include "pacTileManager.h"
#include "pacPlayerScript.h"
#include "pacPlayer.h"
//Engine
#include "Component/Transform/huruTransform.h"
#include "Component/Animator/huruAnimator.h"
#include "Component/SpriteRenderer/huruSpriteRenderer.h"
#include "Helpers/huruTime.h"



namespace pac
{
	GhostScript::GhostScript() :
		mState(eState::Normal),
		mTransform(nullptr),
		mAnimator(nullptr),
		mSpriteRenderer(nullptr),
		mFrightenedTimer(0.f),
		mIsFlashing(false),
		mFlashTimer(0.f),
		FrightenedDuration(8.f),
		FlashStartTime(3.f),
		FlashInterval(0.2f),
		mSpeed(46.f),
		mCurrentAnimName(L""),
		mCurrentDirection(Vector2::Zero),
		mTargetTileCenter(Vector2::Zero),
		DIR_UP(Vector2(0, -1)),
		DIR_DOWN(Vector2(0, 1)),
		DIR_LEFT(Vector2(-1, 0)),
		DIR_RIGHT(Vector2(1, 0))
	{

	}

	GhostScript::~GhostScript()
	{

	}

	void GhostScript::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
		mAnimator = GetOwner()->GetComponent<Animator>();
		mSpriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();
		if (mAnimator)
		{
			mAnimator->CreateAnimationByFolder(L"Nerf_Blue", L"../Resources/img/ghost/nerf/blue", Vector2::Zero, 0.1f);
			mAnimator->CreateAnimationByFolder(L"Nerf_White", L"../Resources/img/ghost/nerf/white", Vector2::Zero, 0.1f);
		}

		mCurrentDirection = DIR_UP;

		Vector2 pos = mTransform->GetPosition();
		int idxX = static_cast<int>(pos.x / Tile::Size.x);
		int idxY = static_cast<int>(pos.y / Tile::Size.y);
		mTargetTileCenter = Vector2((idxX + 0.5f) * Tile::Size.x, (idxY + 0.5f) * Tile::Size.y);
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
			break;
		case eState::Dead:
			HandleDeadState();
			break;
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

	void GhostScript::OnCollisionEnter(Collider* other)
	{
		Script::OnCollisionEnter(other);
	}

	void GhostScript::OnCollisionStay(Collider* other)
	{
		Script::OnCollisionStay(other);
	}

	void GhostScript::OnCollisionExit(Collider* other)
	{
		Script::OnCollisionExit(other);
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
		// 스프라이트 이동 방향에 따라 상하좌우 이미지 렌더 처리
	}

	void GhostScript::BeginNerf()
	{
		if (mState == eState::Dead)
			return;

		mState = eState::Nerf;
		mFrightenedTimer = FrightenedDuration;
		mIsFlashing = false;
		mSpeed = 30.f;

		
		mAnimator->PlayAnimation(L"Nerf_Blue", true);
	}

	void GhostScript::EndNerf()
	{
		mState = eState::Normal;
		mIsFlashing = false;
		mSpeed = 48.f;

		PlayAnimByDir(mCurrentDirection);
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

	void GhostScript::UpdateMovement(bool isEscaping)
	{
		Vector2 pos = mTransform->GetPosition();
		int idxX = static_cast<int>(pos.x / Tile::Size.x);
		int idxY = static_cast<int>(pos.y / Tile::Size.y);
		Vector2 currentTile = Vector2((float)idxX, (float)idxY);
		Vector2 center = Vector2((idxX + 0.5f) * Tile::Size.x, (idxY + 0.5f) * Tile::Size.y);

		if ((center - pos).length() < 0.1f)
		{
			mTransform->SetPosition(center);
			Vector2 prevDir = mCurrentDirection;
			UpdateDirection(isEscaping);

			if (mCurrentDirection != prevDir && mState == eState::Normal)
				PlayAnimByDir(mCurrentDirection);

			int nextX = idxX + static_cast<int>(mCurrentDirection.x);
			int nextY = idxY + static_cast<int>(mCurrentDirection.y);
			mTargetTileCenter = Vector2((nextX + 0.5f) * Tile::Size.x, (nextY + 0.5f) * Tile::Size.y);
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
		Vector2 playerPos = GetPlayerPosition();
		Vector2 currentTileCenter = mTargetTileCenter;
		int idxX = static_cast<int>(currentTileCenter.x / Tile::Size.x);
		int idxY = static_cast<int>(currentTileCenter.y / Tile::Size.y);

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
			float score = (tileCenter - playerPos).length();

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
			bestDir = -mCurrentDirection; // 막다른길이면 뒤로라도

		mCurrentDirection = bestDir;
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
				if (mAnimator->GetActiveAnimationName() == L"Nerf_White")
					mAnimator->PlayAnimation(L"Nerf_Blue", true);
				else
					mAnimator->PlayAnimation(L"Nerf_White", true);

				mFlashTimer = FlashInterval;
			}
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
	
}

