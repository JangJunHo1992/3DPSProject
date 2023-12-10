#pragma once

#include "ImGui_Window.h"

BEGIN(Engine)
class CGameObject;
class GameInstance;
END

BEGIN(Client)
class CTerrain_MapTool;

class CMap_Window final : public CImGui_Window
{
	DECLARE_SINGLETON(CMap_Window)
public:
	CMap_Window();
	virtual ~CMap_Window() = default;
public:
	virtual HRESULT	Initialize();
	virtual void	Start();
	virtual void	Tick(_float fTimeDelta);
	virtual HRESULT	Render(ID3D11DeviceContext* pContext) override;

public:
	class CTerrain_Tool*		m_pTerrain = nullptr;
	class CGameInstance* m_pGameInstance = { nullptr };
public:
	_float*						m_fBrushRange = { nullptr };
	_float*						m_fBrushHeight = { nullptr };
	_int*						m_iMode = { nullptr };

	_float3						m_Picking = { 0.f,0.f, 0.f };
	_float						m_TerrainSizeX = { 0 };
	_float						m_TerrainSizeZ = { 0 };

	string						m_strName;
	json						m_MapJson;
public:
	virtual void Free() override;
};

END