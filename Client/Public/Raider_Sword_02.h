#pragma once

#include "Raider_Weapon.h"

BEGIN(Client)

class CRaider_Sword_02 abstract : public CRaider_Weapon
{
protected:
	CRaider_Sword_02(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CRaider_Sword_02(const CRaider_Sword_02& rhs);
	virtual ~CRaider_Sword_02() = default;

protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;

};

END