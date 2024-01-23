#pragma once

#include "Covus_Weapon.h"

BEGIN(Client)

class CCovus_Weapon_Saber abstract : public CCovus_Weapon
{
protected:
	CCovus_Weapon_Saber(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_Weapon_Saber(const CCovus_Weapon_Saber& rhs);
	virtual ~CCovus_Weapon_Saber() = default;

public:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
};

END
