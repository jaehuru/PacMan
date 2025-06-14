// Pacman
#include "pacToolScene.h"
#include "pacGameManager.h"
#include "pacCameraScript.h"
#include "pacTile.h"
// Engine
#include "HighLevelInterface/huruApplication.h"
#include "Component/TileMapRenderer/huruTileMapRenderer.h"
#include "Resource/huruResources.h"
#include "Component/Camera/huruCamera.h"
#include "Renderer/huruRenderer.h"
#include "Object/huruObject.h"
#include "Helpers/huruInput.h"
#include "Component/Transform/huruTransform.h"

extern huru::Application application;

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
		Scene::Render(hdc);

		DrawTileGrid(hdc);
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

		for (Tile* tile : mTiles)
		{
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

		// 기존 타일 초기화
		for (Tile* tile : mTiles)
			object::Destroy(tile);
		mTiles.clear();

		while (true)
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&idxY, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&posX, sizeof(int), 1, pFile) != 1)
				break;
			if (fread(&posY, sizeof(int), 1, pFile) != 1)
				break;

			Tile* tile = object::Instantiate<Tile>(ToEngineLayerType(ePacLayerType::Tile));

			Transform* tr = tile->GetComponent<Transform>();
			tr->SetPosition(Vector2(posX, posY));

			int tile_idxX = posX / Tile::Size.x;
			int tile_idxY = posY / Tile::Size.y;

			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(GameManager::GetInstance().GetSpriteTexture());
			tmr->SetSize(Tile::Size);
			tmr->SetScale(Tile::Scale);
			tmr->SetIndex(Vector2(idxX, idxY));

			tile->SetIndexPosition(tile_idxX, tile_idxY);

			mTiles.push_back(tile);
		}
		fclose(pFile);
	}

	void ToolScene::HandleInput()
	{
		if (Input::GetKeyDown(eKeyCode::LButton))
		{
			Vector2 pos = Input::GetMousePosition();
			pos = renderer::mainCamera->CalcuateTilePosition(pos);

			if (pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / Tile::Size.x;
				int idxY = pos.y / Tile::Size.y;

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

				mTiles.push_back(tile);
			}
		}

		if (Input::GetKeyDown(eKeyCode::RButton))
		{
			Vector2 pos = Input::GetMousePosition();
			pos = renderer::mainCamera->CalcuateTilePosition(pos);

			if (pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / Tile::Size.x;
				int idxY = pos.y / Tile::Size.y;

				for (auto it = mTiles.begin(); it != mTiles.end(); ++it)
				{
					Tile* tile = *it;
					if (tile->GetIndexX() == idxX && tile->GetIndexY() == idxY)
					{
						object::Destroy(tile);  // 엔진에서 제거
						mTiles.erase(it);              // 리스트에서 제거
						break;
					}
				}
			}
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}

		if (Input::GetKeyDown(eKeyCode::L))
		{
			Load();
		}
	}

	void ToolScene::DrawTileGrid(HDC hdc)
	{
		// 흰색 펜 생성 및 선택
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

		// 원래 펜 복원 및 흰색 펜 삭제
		SelectObject(hdc, hOldPen);
		DeleteObject(hWhitePen);
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