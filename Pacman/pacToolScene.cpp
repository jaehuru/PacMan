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
		::huru::GameObject* camera = ::huru::object::Instantiate<::huru::GameObject>(::huru::enums::eLayerType::Particle, ::huru::math::Vector2(580.0f, 258.0f));
		::huru::Camera* cameraComp = camera->AddComponent<::huru::Camera>();
		::huru::renderer::mainCamera = cameraComp;
		camera->AddComponent<CameraScript>();

		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}

	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (::huru::Input::GetKeyDown(::huru::eKeyCode::LButton))
		{
			::huru::math::Vector2 pos = ::huru::Input::GetMousePosition();
			pos = ::huru::renderer::mainCamera->CalcuateTilePosition(pos);

			if (pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / ::huru::TileMapRenderer::TileSize.x;
				int idxY = pos.y / ::huru::TileMapRenderer::TileSize.y;

				Tile* tile = ::huru::object::Instantiate<Tile>(::huru::enums::eLayerType::Tile);
				tile->SetIndexPosition(idxX, idxY);

				::huru::Transform* tr = tile->GetComponent<::huru::Transform>();
				tr->SetPosition(
					{
						idxX * ::huru::TileMapRenderer::TileSize.x,
						idxY * ::huru::TileMapRenderer::TileSize.y
					});

				::huru::TileMapRenderer* tmr = tile->AddComponent<::huru::TileMapRenderer>();
				tmr->SetTexture(GameManager::GetInstance().GetSpriteTexture());
				tmr->SetSize(Tile::Size);
				tmr->SetScale(Tile::Scale);
				tmr->UpdateTileSize();
				tmr->SetIndex(::huru::TileMapRenderer::SelectedIndex);

				mTiles.push_back(tile);
			}
			else
			{
				//
			}
		}

		if (::huru::Input::GetKeyDown(::huru::eKeyCode::RButton))
		{
			::huru::math::Vector2 pos = ::huru::Input::GetMousePosition();
			pos = ::huru::renderer::mainCamera->CalcuateTilePosition(pos);

			if (pos.x >= 0.0f && pos.y >= 0.0f)
			{
				int idxX = pos.x / ::huru::TileMapRenderer::TileSize.x;
				int idxY = pos.y / ::huru::TileMapRenderer::TileSize.y;

				for (auto it = mTiles.begin(); it != mTiles.end(); ++it)
				{
					Tile* tile = *it;
					if (tile->GetIndexX() == idxX && tile->GetIndexY() == idxY)
					{
						::huru::object::Destroy(tile);  // �������� ����
						mTiles.erase(it);              // ����Ʈ���� ����
						break;					}
				}
			}
		}

		if (::huru::Input::GetKeyDown(::huru::eKeyCode::S))
		{
			Save();
		}

		if (::huru::Input::GetKeyDown(::huru::eKeyCode::L))
		{
			Load();
		}
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
			::huru::TileMapRenderer* tmr = tile->GetComponent<::huru::TileMapRenderer>();
			::huru::Transform* tr = tile->GetComponent<::huru::Transform>();

			::huru::math::Vector2 sourceIndex = tmr->GetIndex();
			::huru::math::Vector2 position = tr->GetPosition();

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

		// ���� Ÿ�� �ʱ�ȭ
		for (Tile* tile : mTiles)
			::huru::object::Destroy(tile);  // ���¸� Dead�� �ٲ�
		// Dead ������ Ÿ�� ���� �� ���� ����
		ClearDeadTiles();

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

			Tile* tile = ::huru::object::Instantiate<Tile>(::huru::enums::eLayerType::Tile);

			::huru::Transform* tr = tile->GetComponent<::huru::Transform>();
			tr->SetPosition(::huru::math::Vector2(posX, posY));

			int tile_idxX = posX / Tile::Size.x;
			int tile_idxY = posY / Tile::Size.y;

			::huru::TileMapRenderer* tmr = tile->AddComponent<::huru::TileMapRenderer>();
			tmr->SetTexture(GameManager::GetInstance().GetSpriteTexture());
			tmr->SetSize(Tile::Size);
			tmr->SetScale(Tile::Scale);
			tmr->UpdateTileSize();
			tmr->SetIndex(::huru::math::Vector2(idxX, idxY));

			tile->SetIndexPosition(tile_idxX, tile_idxY);

			mTiles.push_back(tile);
		}
		fclose(pFile);
	}

	void ToolScene::DrawTileGrid(HDC hdc)
	{
		// ��� �� ���� �� ����
		HPEN hWhitePen = CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hWhitePen);

		for (size_t i = 0; i < 100; i++)
		{
			::huru::math::Vector2 pos = ::huru::renderer::mainCamera->CalculatePosition
			(
				::huru::math::Vector2(::huru::TileMapRenderer::TileSize.x * i, 0.0f)
			);

			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 1000);
		}

		for (size_t i = 0; i < 100; i++)
		{
			::huru::math::Vector2 pos = ::huru::renderer::mainCamera->CalculatePosition
			(
				::huru::math::Vector2(0.0f, ::huru::TileMapRenderer::TileSize.y * i)
			);

			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 1000, pos.y);
		}

		// ���� �� ���� �� ��� �� ����
		SelectObject(hdc, hOldPen);
		DeleteObject(hWhitePen);
	}

	void ToolScene::ClearDeadTiles()
	{
		std::vector<Tile*> deadTiles;

		// ���� Ÿ�� ������
		for (Tile* tile : mTiles)
		{
			if (tile->IsDead())
				deadTiles.push_back(tile);
		}

		// 1. ���Ϳ��� ���� Ÿ�� ����
		std::erase_if(mTiles, [](Tile* tile) { return tile->IsDead(); });

		// 2. ���� ���̾���� ����
		huru::Layer* tileLayer = GetLayer(huru::enums::eLayerType::Tile); // Ȥ�� ������ ������ ���

		for (Tile* tile : deadTiles)
		{
			tileLayer->EraseGameObject(tile);  // Layer�� mGameObjects������ ����
			delete tile; // ��¥ �޸� ����
		}
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

		huru::math::Vector2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;

		int idxX = mousePosition.x / huru::TileMapRenderer::OriginTileSize.x;
		int idxY = mousePosition.y / huru::TileMapRenderer::OriginTileSize.y;

		huru::TileMapRenderer::SelectedIndex = huru::math::Vector2(idxX, idxY);
	}

	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		huru::graphics::Texture* texture
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