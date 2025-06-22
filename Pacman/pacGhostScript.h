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

		void				BeginNerf();

	protected:
		virtual	Vector2		CalculateTargetPosition() = 0;

		virtual void		PlayAnimByDir(const Vector2& direction) = 0;
		void				UpdateAnimation(const wstring& newAnim);

	private:
		void				HandleNormalState();
		void				HandleNerfState();
		void				HandleDeadState();

		void				EndNerf();

		Vector2Int			ConvertToTileIndex(const Vector2& worldPos);
		Vector2				TileIndexToWorldPosition(const Vector2Int& tileIndex);

		void				MoveTowards(const Vector2& targetPosition, float deltaTime);


	protected:
		Animator*			mAnimator;

	private:
		eState				mState;
		Transform*			mTransform;
		SpriteRenderer*		mSpriteRenderer;

		float				mFrightenedTimer;
		bool				mIsFlashing;
		float				mFlashTimer;

		const float			FrightenedDuration;
		const float			FlashStartTime;   
		const float			FlashInterval;

		float				mSpeed;

		wstring				mCurrentAnimName;
	};
}

