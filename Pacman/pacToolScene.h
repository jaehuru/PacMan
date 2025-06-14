#pragma once

#include "Scene/huruScene.h"

namespace huru::graphics { class Texture; }

namespace pac
{
	class Tile;

	class ToolScene : public Scene
	{
	public:
		ToolScene();
		~ToolScene();

		void	Initialize() override;
		void	Update() override;
		void	LateUpdate() override;
		void	Render(HDC hdc) override;

		void	OnEnter() override;
		void	OnExit() override;

		void	Save();
		void	Load();

	private:
		void	HandleInput();
		void	DrawTileGrid(HDC hdc);

	private:
		vector<Tile*> mTiles;
	};
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
