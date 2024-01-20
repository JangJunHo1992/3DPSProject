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
	/* ������ü�� �����Ѵ�. */
	static CRaider_Weapon_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END