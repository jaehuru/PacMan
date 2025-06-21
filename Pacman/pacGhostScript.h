#pragma once

#include "Component/Script/huruScript.h"

namespace huru
{
	class Collider;
	class Animator;
	class Transform;
	class SpriteRenderer;
}

namespace pac
{
	class GhostScript : public Script
	{
	public:
		enum class eState
		{
			Normal,
			Nerf, // ÆÄ¿öÆç¸´ ¸ÔÀº »óÅÂ
			Dead,
		};

		GhostScript();
		virtual ~GhostScript();

		void				Initialize() override;
		void				Update() override;
		void				LateUpdate() override;
		void				Render(HDC hdc) override;

		void				OnCollisionEnter(Collider* other) override;
		void				OnCollisionStay(Collider* other) override;
		void				OnCollisionExit(Collider* other) override;

		void				SetState(eState state)	{ mState = state; }
		eState				GetState() const		{ return mState; }

		virtual	Vector2		CalculateTargetPosition() = 0;

		void				BeginNerf();
		virtual void		EndNerf();

	protected:
		virtual void		HandleNormalState();
		void				HandleNerfState();
		void				HandleDeadState();

	protected:
		eState				mState;
		Transform*			mTransform;
		Animator*			mAnimator;
		SpriteRenderer*		mSpriteRenderer;

		float				mFrightenedTimer;
		bool				mIsFlashing;
		float				mFlashTimer;

		const float			FrightenedDuration;
		const float			FlashStartTime;   
		const float			FlashInterval;
	};
}

