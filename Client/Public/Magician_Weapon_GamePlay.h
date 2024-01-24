#pragma once

#include "Magician_Weapon.h"

BEGIN(Client)

class CMagician_Weapon_GamePlay final : public CMagician_Weapon
{
protected:
	CMagician_Weapon_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Weapon_GamePlay(const CMagician_Weapon_GamePlay& rhs);
	virtual ~CMagician_Weapon_GamePlay() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CMagician_Weapon_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END