//Pacman
#include "pacGameOverUI.h"
#include "pacGameManager.h"
//Engine


namespace pac
{
	GameOverUI::GameOverUI() :
		UIBase(ToEngineUIType(ePacUItype::GameOver))
	{

	}

	void GameOverUI::OnRender(HDC hdc)
	{
		const wstring text = L"GAME OVER";

		SetTextColor(hdc, RGB(255, 0, 0));
		SetBkMode(hdc, TRANSPARENT);

		RECT rect = { 350, 200, 750, 300 };
		DrawText(hdc, text.c_str(), (int)text.size(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}