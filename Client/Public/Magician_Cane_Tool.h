#pragma once

#include "Magician_Cane.h"

BEGIN(Client)

class CMagician_Cane_Tool final : public CMagician_Cane
{
protected:
	CMagician_Cane_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Cane_Tool(const CMagician_Cane_Tool& rhs);
	virtual ~CMagician_Cane_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CMagician_Cane_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END
