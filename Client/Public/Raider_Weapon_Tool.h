#pragma once

#include "Raider_Weapon.h"

BEGIN(Client)

class CRaider_Weapon_Tool final : public CRaider_Weapon
{
protected:
	CRaider_Weapon_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Weapon_Tool(const CRaider_Weapon_Tool& rhs);
	virtual ~CRaider_Weapon_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CRaider_Weapon_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END