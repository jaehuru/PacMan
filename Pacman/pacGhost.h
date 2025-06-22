#pragma once

#include "GameObject/huruGameObject.h"

namespace huru
{
	class Animator;
	class SpriteRenderer;
}

namespace pac
{
	class Ghost : public GameObject
	{
	public:
		Ghost();
		virtual ~Ghost();

		void			Initialize() override;
		void			Update() override;
		void			LateUpdate() override;
		void			Render(HDC hdc) override;

		Animator*		GetAnimator()	const { return mAnimator; }

	private:
		Animator*			mAnimator;
	};
}