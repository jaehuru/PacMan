#pragma once

#include "pacGhostScript.h"

namespace pac
{
	class BlinkyScript : public GhostScript
	{
	public:
		BlinkyScript();
		virtual ~BlinkyScript();

		void				Initialize() override;
		void				Update() override;
		void				LateUpdate() override;
		void				Render(HDC hdc) override;

		void				OnCollisionEnter(Collider* other) override;
		void				OnCollisionStay(Collider* other) override;
		void				OnCollisionExit(Collider* other) override;

		Vector2				CalculateTargetPosition() override;

	protected:
		void				PlayAnimByDir(const Vector2& direction) override;

	};
}

