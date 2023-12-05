#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "Actor.h"


BEGIN(Client)

class CLevel_MapTool final : public CLevel
{
private:
	CLevel_MapTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CLevel_MapTool() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Update_MousePos();

public:
	void Terrain_Pick();
	void Create_Object(const wstring& strLayerTag, const wstring& strPrototypeTag);
	void Create_Raider();


private:
	HRESULT Ready_Layer_Camera(const wstring& strLayerTag);
	HRESULT Ready_Layer_Raider(const wstring& strLayerTag);
	HRESULT Ready_Layer_BackGround(const wstring& strLayerTag);


private:
	class CImgui_Manager* m_pImguiManager = { nullptr };
	class CTerrain_MapTool*		m_pTerrain = { nullptr };
	//list<class CGameObject*>	m_pPickableObjects;

	class CTerrain_MapTool*		m_pTerrain_MapTool = { nullptr };

public:
	void	Set_BrushRange(_float _fBrushRange);
	
public:
	static CLevel_MapTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;

private:
	CActor<CLevel_MapTool>* m_pActor = { nullptr };
};

END