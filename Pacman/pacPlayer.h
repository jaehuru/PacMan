#pragma once

#include "Common/CommonInclude.h"
#include "GameObject/huruGameObject.h"

namespace huru 
{ 
	class Transform;
	class SpriteRenderer;
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

		float GetSpeed() const { return mSpeed; }

	private:
		Transform* mTransform;
		SpriteRenderer* mSpriteRenderer;

		Vector2 mDirection;
		float mSpeed;
	};
}

