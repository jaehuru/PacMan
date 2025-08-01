# PacMan Clone – 2D Game Project

# Project Description

[자체 제작한 Win32 기반 2D 게임 엔진](https://github.com/jaehuru/JaehuruEngine_Core)을 활용하여 클래식 게임 **팩맨(Pac-Man)** 을 구현합니다.  
게임 구조 설계, AI 상태머신 구현, 타일 기반 맵 로직, 간단한 UI 시스템을 통합하는 것을 목표로 합니다.

## Development Environment
- 'Window OS'
- 'Visual Studio 2022'

---

## Game Design

### 타일맵 시스템
- 고정된 타일 기반 맵 사용 (벽, 길, 포탈, 감옥으로 구분)
- 충돌 처리는 **벽 기준**으로만 수행
- 타일 단위 이동이므로 FSM 기반 AI 설계가 용이

### 플레이어 컨트롤
- 방향키 입력에 따라 진행 방향 결정
- 방향 전환 시, 다음 타일의 유효성 검사 후 이동 결정

### 유령 AI (FSM 기반)
- 유령은 다음과 같은 상태를 가짐:
  - `Normal`: 플레이어 방향 추적
  - `Nerf`: 플레이어가 Pellet을 먹으면 Nerf 상태가 되어 플레이어한테 잡아먹힘
  - `Dead`: 사망 시 Jail로 돌아감
  - `Wait`: 사망 후 Jail 안에서 잠시 대기
- 유령 마다 다른 움직임 패턴

### UI 시스템
- Lives UI
- 게임 승리 / 오버 화면 및 텍스트

### 게임 조건 처리
- Dot을 모두 먹으면 -> 게임 승리
- 유령에게 잡히면 사망 → 게임 오버

---

# Implementation Overview

## Singleton 패턴

### GameManager  

- 팩맨 게임의 전체적인 게임 진행을 총괄하는 관리자 클래스
- Singleton 패턴으로 전역에서 접근 가능
- 리소스 로딩, 맵 로딩, 씬 등록, 게임 상태 관리, 고스트 및 플레이어 관리

## Map 관련 클래스

### TileManager 클래스

- 맵 파일 로딩 및 타일 데이터 관리
- 타일 리스트 및 포탈 타일 관리
- 전체 도트 개수 계산 기능 제공

### ToolScene 클래스

- 맵 제작을 위한 타일 에디터 씬
- 타일을 배치/삭제하고 맵 데이터를 파일로 저장 및 로드
- 타일 타입 선택 기능 제공

### Tile 클래스

- 타일을 객체 단위로 관리하며 인덱스를 통해 맵 데이터와 연동
- 타일 타입(Path, Wall, Jail, Portal, Pellet) 관리
- 도트(Dot) 보유 여부 및 렌더링 관리

## 충돌 및 이동 관련 클래스

### PlayerScript 클래스
- 플레이어의 이동, 입력 처리, 애니메이션, 타일 네비게이션을 담당
- 아이템(도트, 펠렛) 수집 및 고스트와의 충돌 판정 관리
- 포탈 이동 처리 및 사망 시 리스폰 로직 담당
- 임 매니저 및 타일 매니저와 상호작용하여 게임 진행을 제어

### GhostScript 클래스
- 고스트 이동과 상태(노멀, 널프, 데드, 대기) 관리  
- 플레이어 위치에 따라 타겟 방향 결정 (가상 함수로 고스트별 타겟 다름)  
- 널프 상태 타이머 및 깜빡임 효과 처리  
- 데드 상태일 때 감옥으로 이동 후 대기 및 리스폰  
- 포탈 이동 처리와 애니메이션 갱신  
- 플레이어와 충돌 시 상태 변화 처리

## 기타 객체와 UI, 유틸 클래스

### Pellet 클래스
- 펠렛(파워업 아이템) 렌더링 및 깜빡임 효과 처리
- 일정 시간 간격으로 가시성 토글하여 깜빡임 구현

### Utility 클래스
- 타일 좌표와 월드 좌표 간 변환 함수 제공  
- 타일 중심 위치 계산 (SnapToTileCenter)  
- 월드 좌표를 타일 인덱스로 변환 (WorldToTile)  
- 현재 타일이 포탈 타일인지 검사 (IsOnPortalTile)  
- 포탈 타일 간 위치 이동 처리 (TeleportToOtherPortal)

###
HUD, GameOverUI, Define, Enum, Scene 클래스 등등..
---

# About Development

- **Pacman 개발 이슈 및 버그 기록**  
  [🐞 Debug Notes & Issues](https://github.com/jaehuru/Pacman/issues)

---

# Reflections
Win32 API 기반의 게임 엔진을 만들어 처음으로 게임을 개발하면서 정말 많은 것을 느꼈다. GDI+ 렌더링의 한계, 즉 CPU만으로 화면을 출력하는 방식이 얼마나 비효율적인지 체감할 수 있었고, 부족한 실력이지만 최적화를 고민하면서 옛날 게임 개발자들이 겪었을 최적화의 어려움을 조금이나마 이해할 수 있었다.

게임을 만들어가면서 필요에 따라 엔진을 수정하고 다양한 버그를 직면하며 시행착오를 겪었지만, 그 과정 속에서 게임 엔진이 무엇인지에 대한 이해도가 많이 높아졌다. 상용 엔진으로 게임을 만드는 것이 얼마나 편리한지도 새삼 느끼게 되었고, 시각적인 툴 없이 대부분 코드를 통해 작업하다 보니 문제가 발생했을 때 디버깅 의존도가 높아졌고 덕분에 디버깅 실력도 많이 성장한 것 같다.

이번 경험을 통해 앞으로 상용 엔진을 사용할 때도 조금 더 깊이 이해하고 활용할 수 있을 것 같아 값진 경험이 되었다.
