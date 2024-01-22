#pragma once

#include "Covus_Weapon.h"

BEGIN(Client)

class CCovus_Weapon_Dagger abstract : public CCovus_Weapon
{
protected:
	CCovus_Weapon_Dagger(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_Weapon_Dagger(const CCovus_Weapon_Dagger& rhs);
	virtual ~CCovus_Weapon_Dagger() = default;

public:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
};

END