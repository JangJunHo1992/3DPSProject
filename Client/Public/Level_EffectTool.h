#pragma once

#include "Client_Defines.h"
#include "Level.h"
#include "Particle_Custom.h"

BEGIN(Client)

class CLevel_EffectTool final : public CLevel
{
private:
	CLevel_EffectTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CLevel_EffectTool() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_LightDesc();
	HRESULT Ready_Layer_Camera(const wstring& strLayerTag);
	HRESULT Ready_Layer_Effect(const wstring& strLayerTag);

public:
	HRESULT Load_Objects_With_Json(string filePath);

public:
	CParticle_Custom::PARTICLE_DESC* Get_Desc() {
		return &m_Desc;
	}

	void Set_CamPos(_float fMaxRange);
	void Set_MaxDelay(_float _fMaxDelay) {
		m_fMaxDelay = _fMaxDelay;
	}

	void Save_Desc();
	void Load_Desc();


private:
	_float m_fDelay = { 1.f };
	_float m_fMaxDelay = { 1.f };

	CParticle_Custom::PARTICLE_DESC m_Desc;

	class CImgui_Manager* m_pImguiManager = { nullptr };
	class CEffect_Window* m_pEffectWin = { nullptr };
	class CCamera_Dynamic* m_pCamera = { nullptr };
	CGameObject* m_pWaepon = { nullptr };

public:
	static CLevel_EffectTool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual void Free() override;

};

END