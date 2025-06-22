//Pacman
#include "pacGhostScript.h"
#include "pacGhost.h"
#include "pacAI.h"
#include "pacTile.h"
#include "pacGameManager.h"
#include "pacTileManager.h"
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
		mSpeed(48.f)
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

	void GhostScript::BeginNerf()
	{
		if (mState == eState::Dead)
			return;

		mState = eState::Nerf;
		mFrightenedTimer = FrightenedDuration;
		mIsFlashing = false;

		if (mAnimator)
		{
			mAnimator->PlayAnimation(L"Nerf_Blue", true);
		}
	}

	void GhostScript::EndNerf()
	{
		mState = eState::Normal;
		mIsFlashing = false;
	}

	void GhostScript::HandleNerfState()
	{
		mFrightenedTimer -= Time::DeltaTime();

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
				// 파란색/흰색 전환
				if (mAnimator && mAnimator->GetActiveAnimationName() == L"Nerf_White")
					mAnimator->PlayAnimation(L"Nerf_Blue", true);
				else
					mAnimator->PlayAnimation(L"Nerf_White", true);

				mFlashTimer = FlashInterval;
			}
		}

		if (mFrightenedTimer <= 0.f)
		{
			EndNerf();
		}
	}

	void GhostScript::HandleNormalState()
	{
		TileManager* tileManager = GameManager::GetInstance().GetTileManager();

		// 현재 위치, 목표 위치 타일 인덱스로 변환
		Vector2Int currentTile = ConvertToTileIndex(mTransform->GetPosition());
		Vector2 targetPos = CalculateTargetPosition();
		Vector2Int targetTile = ConvertToTileIndex(targetPos);

		int mapWidth = tileManager->GetMapWidth();
		int mapHeight = tileManager->GetMapHeight();

		int currentIndex = currentTile.y * mapWidth + currentTile.x;
		int targetIndex = targetTile.y * mapWidth + targetTile.x;

		// BFS 경로 찾기
		vector<int> path = AI::BFS_FindPath(tileManager, mapWidth, mapHeight, currentIndex, targetIndex);

		if (path.size() > 1)
		{
			int nextIndex = path[1];
			Vector2Int nextTile{ nextIndex % mapWidth, nextIndex / mapWidth };
			Vector2 nextPos = TileIndexToWorldPosition(nextTile);

			Vector2 currentPos = mTransform->GetPosition();
			Vector2 dir = nextPos - currentPos;

			MoveTowards(nextPos, Time::DeltaTime());

			if ((nextPos - mTransform->GetPosition()).length() > 0.001f)
				PlayAnimByDir(nextPos - mTransform->GetPosition());
		}
		else
		{
			// 경로가 없거나 이미 목표 도착: 정지 혹은 대기 상태 처리
			// 예: StopMoving() 같은 함수 호출 가능
		}
	}

	void GhostScript::HandleDeadState()
	{
		// 스프라이트 이동 방향에 따라 상하좌우 이미지 렌더 처리
	}

	Vector2Int GhostScript::ConvertToTileIndex(const Vector2& worldPos)
	{
		return Vector2Int(
			static_cast<int>(worldPos.x / Tile::Size.x),
			static_cast<int>(worldPos.y / Tile::Size.y)
		);
	}

	Vector2 GhostScript::TileIndexToWorldPosition(const Vector2Int& tileIndex)
	{
		return Vector2(
			(tileIndex.x + 0.5f) * Tile::Size.x,
			(tileIndex.y + 0.5f) * Tile::Size.y
		);
	}

	void GhostScript::MoveTowards(const Vector2& targetPosition, float deltaTime)
	{
		Vector2 currentPosition = mTransform->GetPosition();
		Vector2 direction = targetPosition - currentPosition;
		float distance = direction.length();

		if (distance < 0.01f)
		{
			// 거의 도착한 경우, 정확히 위치 맞추기
			mTransform->SetPosition(targetPosition);
			return;
		}

		direction = direction.normalize();

		float moveDistance = mSpeed * deltaTime;
		if (moveDistance > distance)
			moveDistance = distance;

		Vector2 newPos = currentPosition + direction * moveDistance;
		mTransform->SetPosition(newPos);

		if ((targetPosition - newPos).length() < 0.05f)
		{
			mTransform->SetPosition(targetPosition);
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

