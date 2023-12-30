#pragma once

#include "Raider_Weapon.h"

BEGIN(Client)

class CRaider_Sword_01 abstract : public CRaider_Weapon
{
protected:
	CRaider_Sword_01(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Sword_01(const CRaider_Sword_01& rhs);
	virtual ~CRaider_Sword_01() = default;

protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;

};

END