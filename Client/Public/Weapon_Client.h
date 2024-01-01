#pragma once

#include "Weapon.h"
#include "Client_Defines.h"

BEGIN(Client)

class CWeapon_Client abstract : public CWeapon
{
protected:
	CWeapon_Client(ID3D11Device* pDevice, ID3D11DeviceContext* pContext) 
		: CWeapon (pDevice, pContext)
	{
	};
	CWeapon_Client(const CWeapon_Client& rhs) 
		: CWeapon(rhs)
	{
	};
	virtual ~CWeapon_Client() = default;

protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) PURE;

};

END