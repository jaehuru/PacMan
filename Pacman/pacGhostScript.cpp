//Pacman
#include "pacGhostScript.h"
#include "pacGhost.h"
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
		FlashInterval(0.2f)
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
		// 개별적으로 처리 virtual 함수
	}

	void GhostScript::HandleDeadState()
	{
		// 스프라이트 이동 방향에 따라 상하좌우 이미지 렌더 처리
	}
}

