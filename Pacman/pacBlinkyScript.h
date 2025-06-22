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

	protected:
		void				PlayAnimByDir(const Vector2& direction) override;

	};
}

