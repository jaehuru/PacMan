#pragma once

#include "UI/huruUIHUD.h"


namespace pac
{
	class HUD : public UIHUD
	{
	public:
		HUD();
		~HUD();

		void	OnInit()			override;
		void	OnRender(HDC hdc)	override;

	private:
		vector<graphics::Texture*> mLifeIcons;
	};
}
