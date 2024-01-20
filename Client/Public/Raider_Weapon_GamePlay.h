#pragma once

#include "Raider_Weapon.h"

BEGIN(Client)

class CRaider_Weapon_GamePlay final : public CRaider_Weapon
{
protected:
	CRaider_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Weapon_GamePlay(const CRaider_Weapon_GamePlay& rhs);
	virtual ~CRaider_Weapon_GamePlay() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CRaider_Weapon_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END