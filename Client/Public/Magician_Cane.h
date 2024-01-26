#pragma once

#include "Magician_Weapon.h"

BEGIN(Client)

class CMagician_Cane abstract : public CMagician_Weapon
{
protected:
	CMagician_Cane(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Cane(const CMagician_Cane& rhs);
	virtual ~CMagician_Cane() = default;

public:
	virtual HRESULT Ready_Components_Origin(LEVEL eLevel) override;
};

END
