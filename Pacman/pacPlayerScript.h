#pragma once

#include "Component/Script/huruScript.h"

namespace huru
{
	class Collider;
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

		void		OnCollisionEnter(Collider* other) override;
		void		OnCollisionStay(Collider* other) override;
		void		OnCollisionExit(Collider* other) override;

	private:
		void		HandleInput();

		bool		CanMove(Vector2 from, Vector2 dir);
		void		Dead();

		void		ProcessTileNavigation();
		Vector2		SnapToTileCenter(Vector2 tilePos);

		bool		IsOnPortalTile();
		void		TeleportToOtherPortal();

		void		UpdateAnimation();

		void		CollectedItem();
		void		CollectedDot();
		void		CollectedPellet();

	private:
		Animator*		mAnimator;
		eState			mState;
		Transform*		mTransform;
		TileManager*	mTileManager;

		const			Vector2 DIR_UP = Vector2(0, -1);
		const			Vector2 DIR_DOWN = Vector2(0, 1);
		const			Vector2 DIR_LEFT = Vector2(-1, 0);
		const			Vector2 DIR_RIGHT = Vector2(1, 0);

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