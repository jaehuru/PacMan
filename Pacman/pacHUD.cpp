//Pacman
#include "pacHUD.h"
#include "pacGameManager.h"
//Engine
#include "Resource/huruResources.h"
#include "Resource/huruTexture.h"

namespace pac
{
	void HUD::OnInit()
	{
		mLifeIcons.push_back(Resources::Find<graphics::Texture>(L"Life0"));
		mLifeIcons.push_back(Resources::Find<graphics::Texture>(L"Life1"));
		mLifeIcons.push_back(Resources::Find<graphics::Texture>(L"Life2"));
		mLifeIcons.push_back(Resources::Find<graphics::Texture>(L"Life3"));
	}

	void HUD::OnRender(HDC hdc)
	{
        int life = GameManager::GetInstance().GetLife();

		graphics::Texture* lifeTexture = nullptr;
		if (life >= 0 && life < (int)mLifeIcons.size())
		{
			lifeTexture = mLifeIcons[life];
		}

        if (lifeTexture)
        {
            int renderWidth = static_cast<int>(lifeTexture->GetWidth() * 0.19f);
            int renderHeight = static_cast<int>(lifeTexture->GetHeight() * 0.19f);
  
            Gdiplus::Graphics graphics(hdc);
            graphics.DrawImage(
                lifeTexture->GetImage(),
                230, 350, renderWidth, renderHeight);   
        }
	}
}