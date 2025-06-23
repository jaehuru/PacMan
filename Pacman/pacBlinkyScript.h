#pragma once

#include "pacGhostScript.h"

namespace pac
{
	class BlinkyScript : public GhostScript
	{
	public:
		BlinkyScript();
		~BlinkyScript() = default;

		void	Initialize() override;

	protected:
		void	PlayAnimByDir(const Vector2& direction) override;
	};
}

