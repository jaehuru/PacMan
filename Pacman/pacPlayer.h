#pragma once

#include "GameObject/huruGameObject.h"

namespace huru 
{ 
	class Animator;
}

namespace pac
{
	class Player : public GameObject
	{
	public:
		Player();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		Animator* mAnimator;
	};
}

