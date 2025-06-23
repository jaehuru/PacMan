#pragma once

#include "UI/huruUIBase.h"


namespace pac
{
	class GameOverUI : public UIBase
	{
	public:
		GameOverUI();
		~GameOverUI() = default;

		void OnRender(HDC hdc) override;
	};
}

