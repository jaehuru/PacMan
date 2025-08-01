#pragma once

#include "Component/Script/huruScript.h"

namespace huru
{
	class Animator;
	class Transform;
}

namespace pac
{
	class Tile;
	class TileManager;

	class PlayerScript : public Script
	{
	public:
		enum class eState
		{
			Alive,
			Dead,
			End,
		};

		PlayerScript();
		~PlayerScript();

		void		Initialize() override;
		void		Update() override;
		void		LateUpdate() override;
		void		Render(HDC hdc) override;

		Vector2		GetCurrentPosition() const;
		Vector2		GetCurrentDirection() const		{ return mCurrentDir; }

	private:
		void		HandleInput();

		bool		CanMove(Vector2 from, Vector2 dir);
		void		Dead();

		void		ProcessTileNavigation();

		void		UpdateAnimation();

		void		CollectedItem();
		void		CollectedDot();
		void		CollectedPellet();

		void		ConnetedGhost();
		void		Respawn();

	private:
		Animator*		mAnimator;
		eState			mState;
		Transform*		mTransform;
		TileManager*	mTileManager;

		const Vector2	DIR_UP;
		const Vector2	DIR_DOWN;
		const Vector2	DIR_LEFT;
		const Vector2	DIR_RIGHT;

		Vector2			mCurrentTile;
		Vector2			mTargetTile;
		Vector2			mCurrentDir;
		Vector2			mNextDir;
		float			mSpeed;

		wstring			mCurrentAnimName;
		float			mPortalCoolTime;
		vector<Tile*>	mPortals;
	};
}