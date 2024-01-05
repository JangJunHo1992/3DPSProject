#pragma once

#include "Body.h"
#include "Client_Defines.h"

BEGIN(Client)

class CBody_Client abstract : public CBody
{
protected:
	CBody_Client(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
		: CBody(pDevice, pContext)
	{
	};
	CBody_Client(const CBody_Client& rhs)
		: CBody(rhs)
	{
	};
	virtual ~CBody_Client() = default;

protected:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel);

};

END