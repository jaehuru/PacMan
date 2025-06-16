// Pacman
#include "pacToolScene.h"
#include "pacGameManager.h"
#include "pacCameraScript.h"
// Engine
#include "HighLevelInterface/huruApplication.h"
#include "Component/TileMapRenderer/huruTileMapRenderer.h"
#include "Resource/huruResources.h"
#include "Component/Camera/huruCamera.h"
#include "Renderer/huruRenderer.h"
#include "Object/huruObject.h"
#include "Helpers/huruInput.h"
#include "Component/Transform/huruTransform.h"

extern Application application;


namespace pac
{

	ToolScene::ToolScene()
	{

	}

	ToolScene::~ToolScene()
	{

	}

	void ToolScene::Initialize()
	{
		GameObject* camera = object::Instantiate<GameObject>(ToEngineLayerType(ePacLayerType::Particle), Vector2(580.0f, 258.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		renderer::mainCamera = cameraComp;
		camera->AddComponent<CameraScript>();

		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}

	void ToolScene::LateUpdate()
	{
		HandleInput();

		Scene::LateUpdate();
	}

	void ToolScene::Render(HDC hdc)
	{
		DrawTileGrid(hdc);
		TileTypeTextOut(hdc);
		Scene::Render(hdc);
	}

	void ToolScene::OnEnter()
	{

	}

	void ToolScene::OnExit()
	{

	}

	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");

		for (Tile* tile : mTileMap)
		{
			if (tile == nullptr)
				continue;

			TileMapRenderer* tmr = tile->GetComponent<TileMapRenderer>();
			Transform* tr = tile->GetComponent<Transform>();

			Vector2 sourceIndex = tmr->GetIndex();
			Vector2 position = tr->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x, sizeof(int), 1, pFile);
			int y = sourceIndex.y;
			fwrite(&y, sizeof(int), 1, pFile);

			x = position.x;
			fwrite(&x, sizeof(int), 1, pFile);
			y = position.y;
			fwrite(&y, sizeof(int), 1, pFile);

			int tileType = static_cast<int>(tile->GetTileType());
			fwrite(&tileType, sizeof(int), 1, pFile);
		}

		fclose(pFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		if (!pFile)
			return;

		// ±‚¡∏ ≈∏¿œ √ ±‚»≠
		for (Tile* tile : mTileMap)
			object::Destroy(tile);
		mTileMap.clear();

		mTileMap.resize(define::MaxMapWidth * define::MaxMapHeight, nullptr);

		while (true)
		{
			int tool_idxX = 0;
			int tool_idxY = 0;

			int tool_posX = 0;
			int tool_posY = 0;

			if (fread(&tool_idxX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_idxY, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_posX, sizeof(int), 1, pFile) != 1) break;
			if (fread(&tool_posY, sizeof(int), 1, pFile) != 1) break;

			Tile* tile = object::Instantiate<Tile>(ToEngineLayerType(ePacLayerType::Tile), Vector2(tool_posX, tool_posY));
			int tileTypeInt = 0;
			if (fread(&tileTypeInt, sizeof(int), 1, pFile) != 1) break;
			tile->SetTileType(static_cast<Tile::eTileType>(tileTypeInt));

			int tile_idxX = tool_posX / Tile::Size.x;
			int tile_idxY = tool_posY / Tile::Size.y;

			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(GameManager::GetInstance().GetSpriteTexture());
			tmr->SetSize(Tile::Size);
			tmr->SetScale(Tile::Scale);
			tmr->SetIndex(Vector2(tool_idxX, tool_idxY));

			tile->SetIndexPosition(tile_idxX, tile_idxY);

			int linearIndex = define::GetLinearIndex(tile_idxX, tile_idxY);
			if (linearIndex >= 0 && linearIndex < (int)mTileMap.size())
			{
				mTileMap[linearIndex] = tile;
			}
		}
		fclose(pFile);
	}

	void ToolScene::HandleInput()
	{
		if (Input::GetKeyDown(eKeyCode::LButton))
		{
			Vector2 pos = Input::GetMousePosition();
			pos = renderer::mainCamera->CalcuateTilePosition(pos);
			mTileMap.resize(define::MaxMapWidth * define::MaxMapHeight, nullptr);

			if (pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / Tile::Size.x;
				int idxY = pos.y / Tile::Size.y;
				int linearIndex = define::GetLinearIndex(idxX, idxY);
				if (linearIndex < 0 || linearIndex >= (int)mTileMap.size())
					return;

				if (mTileMap[linearIndex] != nullptr)
					object::Destroy(mTileMap[linearIndex]);

				Tile* tile = object::Instantiate<Tile>(ToEngineLayerType(ePacLayerType::Tile));
				tile->SetIndexPosition(idxX, idxY);

				Transform* tr = tile->GetComponent<Transform>();
				tr->SetPosition(
					{
						idxX * Tile::Size.x,
						idxY * Tile::Size.y
					});

				TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
				tmr->SetTexture(GameManager::GetInstance().GetSpriteTexture());
				tmr->SetSize(Tile::Size);
				tmr->SetScale(Tile::Scale);
				tmr->SetIndex(TileMapRenderer::SelectedIndex);

				tile->SetTileType(mSelectedTileType);

				mTileMap[linearIndex] = tile;
			}
		}

		if (Input::GetKeyDown(eKeyCode::RButton))
		{
			Vector2 mousePos = Input::GetMousePosition();
			Vector2 tilePos = renderer::mainCamera->CalcuateTilePosition(mousePos);

			if (tilePos.x >= 0.0f && tilePos.y >= 0.0f)
			{
				int idxX = static_cast<int>(tilePos.x / Tile::Size.x);
				int idxY = static_cast<int>(tilePos.y / Tile::Size.y);
				int linearIndex = define::GetLinearIndex(idxX, idxY);

				if (linearIndex >= 0 && linearIndex < (int)mTileMap.size() && mTileMap[linearIndex] != nullptr)
				{
					object::Destroy(mTileMap[linearIndex]);
					mTileMap[linearIndex] = nullptr;
				}
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
			Save();

		if (Input::GetKeyDown(eKeyCode::L))
			Load();

		if (Input::GetKeyDown(eKeyCode::Q))
			mSelectedTileType = Tile::eTileType::Path;
		else if (Input::GetKeyDown(eKeyCode::W))
			mSelectedTileType = Tile::eTileType::Wall;
		else if (Input::GetKeyDown(eKeyCode::E))
			mSelectedTileType = Tile::eTileType::Jail;
		else if (Input::GetKeyDown(eKeyCode::R))
			mSelectedTileType = Tile::eTileType::Potal;
	}

	void ToolScene::DrawTileGrid(HDC hdc)
	{
		// »Úªˆ ∆Ê ª˝º∫ π◊ º±≈√
		HPEN hWhitePen = CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hWhitePen);

		for (size_t i = 0; i < 100; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition
			(
				Vector2(Tile::Size.x * i, 0.0f)
			);

			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 1000);
		}

		for (size_t i = 0; i < 100; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition
			(
				Vector2(0.0f, Tile::Size.y * i)
			);

			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 1000, pos.y);
		}

		// ø¯∑° ∆Ê ∫πø¯ π◊ »Úªˆ ∆Ê ªË¡¶
		SelectObject(hdc, hOldPen);
		DeleteObject(hWhitePen);
	}

	void ToolScene::TileTypeTextOut(HDC hdc)
	{
		wstring typeStr;

		switch (mSelectedTileType)
		{
		case Tile::eTileType::Wall:  typeStr = L"Selected: Wall"; break;
		case Tile::eTileType::Path:  typeStr = L"Selected: Path"; break;
		case Tile::eTileType::Jail:  typeStr = L"Selected: Jail"; break;
		case Tile::eTileType::Potal: typeStr = L"Selected: Potal"; break;
		}

		TextOut(hdc, 10, 10, typeStr.c_str(), (int)typeStr.length());
	}
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT mousePos = { };
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);

		Vector2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;

		int idxX = mousePosition.x / pac::Tile::Size.x;
		int idxY = mousePosition.y / pac::Tile::Size.y;

		TileMapRenderer::SelectedIndex = Vector2(idxX, idxY);
	}

	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		graphics::Texture* texture
			= pac::GameManager::GetInstance().GetSpriteTexture();

		TransparentBlt(hdc
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, texture->GetHdc()
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, RGB(255, 0, 255));

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}