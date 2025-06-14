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

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		void		move();
		void		Dead();

	private:
		Animator* mAnimator;
		eState mState;

		Vector2 mPrevPosition;
	};
}