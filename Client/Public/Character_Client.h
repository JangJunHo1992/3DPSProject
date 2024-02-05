#pragma once

#include "Character.h"
#include "Client_Defines.h"
#include "Particle_Hit.h"

BEGIN(Client)

class CCharacter_Client abstract : public CCharacter
{
	
protected:
	CCharacter_Client(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
		: CCharacter(pDevice, pContext)
	{
	};
	CCharacter_Client(const CCharacter_Client& rhs)
		: CCharacter(rhs)
	{
	};
	virtual ~CCharacter_Client() = default;

protected:
	CParticle_Hit::PARTICLE_DESC Get_Particle_Hitblood_Desc();

	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) PURE;

};

END