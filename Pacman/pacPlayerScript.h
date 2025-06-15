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

	private:
		Animator*	mAnimator;
		eState		mState;

		Vector2		mCurrentTile;     // 현재 타일 좌표
		Vector2		mTargetTile;      // 이동하려는 목표 타일
		Vector2		mCurrentDir;      // 현재 이동 방향 
		Vector2		mNextDir;         // 입력 받은 다음 방향
		float		mSpeed;
	};
}