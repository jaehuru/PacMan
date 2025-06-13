#pragma once

#include "Scene/huruScene.h"

namespace huru::graphics { class Texture; }

namespace pac
{
	class Tile;

	class ToolScene : public ::huru::Scene
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
		void	DrawTileGrid(HDC hdc);
		void	ClearDeadTiles();

	private:
		std::vector<Tile*> mTiles;
	};
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
