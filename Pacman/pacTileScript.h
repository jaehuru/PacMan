#pragma once

#include "Component/Script/huruScript.h"
#include "Resource/huruTexture.h"

namespace huru
{
	class Collider;
}

namespace pac
{
	class TileScript : public Script
	{
	public:
		TileScript();
		~TileScript();

		void		Initialize() override;
		void		Update() override;
		void		LateUpdate() override;
		void		Render(HDC hdc) override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:

	};
}