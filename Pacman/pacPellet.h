#pragma once

#include "GameObject/huruGameObject.h"

namespace huru
{
	class SpriteRenderer;
}

namespace pac
{
	class Pellet : public GameObject
	{
	public:
		Pellet();

		void		Initialize()	override;
		void		Update()		override;
		void		LateUpdate()	override;
		void		Render(HDC hdc) override;

		void		SetBlinkInterval(float interval) { mBlinkInterval = interval; }

	private:
		SpriteRenderer*		mRenderer;
		float				mBlinkTimer;
		float				mBlinkInterval;

	};
}

