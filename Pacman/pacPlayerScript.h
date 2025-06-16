#pragma once

#include "Component/Script/huruScript.h"
#include "Resource/huruTexture.h"

namespace huru
{
	class Collider;
	class Animator;
}

namespace pac
{

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

		Vector2		SnapToTileCenter(Vector2 tilePos);
	private:
		Animator*	mAnimator;
		eState		mState;

		const		Vector2 DIR_UP = Vector2(0, -1);
		const		Vector2 DIR_DOWN = Vector2(0, 1);
		const		Vector2 DIR_LEFT = Vector2(-1, 0);
		const		Vector2 DIR_RIGHT = Vector2(1, 0);

		Vector2		mCurrentTile;    
		Vector2		mTargetTile;     
		Vector2		mCurrentDir;      
		Vector2		mNextDir;        
		float		mSpeed;

		wstring		mCurrentAnimName;
	};
}