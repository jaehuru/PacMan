#pragma once

#include "Component/Script/huruScript.h"
#include "pacEnum.h"

namespace huru
{
	class Collider;
	class Animator;
	class Transform;
	class SpriteRenderer;
}

namespace pac
{
	class Tile;

	class GhostScript : public Script
	{
	public:
		enum class eState
		{
			Normal,
			Nerf, // ÆÄ¿öÆç¸´ ¸ÔÀº »óÅÂ
			Dead,
			Wait
		};

		GhostScript(ePacGhostType type);
		virtual ~GhostScript() = default;

		void				Initialize() override;
		void				Update() override;
		void				LateUpdate() override;
		void				Render(HDC hdc) override;

		void				BeginNerf();

		void				Respawn();

		void				SetState(eState state)	{ mState = state; }
		eState				GetState() const		{ return mState; }
		ePacGhostType		GetGhostType() const	{ return mType; }

	protected:
		virtual void		PlayAnimByDir(const Vector2& direction);
		void				UpdateAnimation(const wstring& newAnim);

		virtual Vector2		GetTargetPosition(const Vector2& playerPos) { return playerPos; }

	private:
		void				HandleNormalState();
		void				HandleNerfState();
		void				HandleDeadState();
		void				HandleWaitState();

		void				EndNerf();

		void				UpdateMovement(bool isEscaping);
		void				UpdateDirection(bool isEscaping);

		Vector2				GetPlayerPosition();
		bool				IsWall(int tileX, int tileY);

		void				UpdateNerfTimers();

		void				ConnectedPlayerInNerf();

		void				DeadByDirection(const Vector2& direction);

		void				UpdateDeadMovement(int targetTileX, int targetTileY);
		void				UpdateDeadDirection(int targetTileX, int targetTileY);

	protected:
		Animator*			mAnimator;
		Transform*			mTransform;

		Vector2				mSpawnPos;

	private:
		eState				mState;

		float				mFrightenedTimer;
		bool				mIsFlashing;
		float				mFlashTimer;

		const float			FrightenedDuration;
		const float			FlashStartTime;   
		const float			FlashInterval;

		float				mSpeed;
		float				mNormalSpeed;
		float				mNerfSpeed;
		float				mDeadSpeed;

		wstring				mCurrentAnimName;

		Vector2				mCurrentDirection;
		Vector2				mTargetTileCenter;

		const Vector2		DIR_UP;
		const Vector2		DIR_DOWN;
		const Vector2		DIR_LEFT;
		const Vector2		DIR_RIGHT;
		const Vector2		directions[4] = { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };

		Vector2             mJailPos;
		float				mDeadWaitTimer;

		vector<Tile*>		mPortals;
		float				mPortalCoolTime;

		ePacGhostType		mType;
	};
}
