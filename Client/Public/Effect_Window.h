#pragma once

#include "ImGui_Window.h"
#include "Particle_Custom.h"

BEGIN(Engine)
class GameInstance;
END

BEGIN(Client)
class CLevel_EffectTool;
class CParticle_Custom;

class CEffect_Window final :public CImGui_Window
{
	DECLARE_SINGLETON(CEffect_Window)

public:
	CEffect_Window();
	virtual ~CEffect_Window() = default;
public:
	virtual HRESULT	Initialize();
	virtual void	Start();
	virtual void	Tick(_float fTimeDelta);
	virtual HRESULT	Render(ID3D11DeviceContext* pContext) override;

public:
	void Set_Level(CLevel_EffectTool* pLevel);


private:
	CGameInstance* m_pGameInstance = { nullptr };
	CLevel_EffectTool* m_pEffectTool = { nullptr };
	CParticle_Custom::PARTICLE_DESC* m_Desc = { nullptr };
	_float m_fDistance = { 5.f };

public:
	virtual void Free() override;

};

END
