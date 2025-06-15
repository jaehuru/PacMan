#pragma once

#include "Common/CommonInclude.h"
#include "GameObject/huruGameObject.h"

namespace huru 
{ 
	class Transform;
	class Animator;
}

namespace pac
{
	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		Transform* mTransform;
		Animator* mAnimator;
	};
}

