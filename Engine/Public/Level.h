#pragma once

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CLevel abstract : public CBase
{
protected:
	CLevel(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize() ;
	virtual void Tick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	_uint					m_iNextLevel = -1;
protected:
	ID3D11Device*			m_pDevice = { nullptr };
	ID3D11DeviceContext*	m_pContext = { nullptr };

protected:
	class CGameInstance*	m_pGameInstance = { nullptr };
	LIGHT_DESC				PlayerLightDesc{};
	class CCharacter*		pPlayer = { nullptr };
public:
	virtual void Free() override;
};

END