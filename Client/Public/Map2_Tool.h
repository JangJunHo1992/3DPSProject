#pragma once

#include "Map2.h"

BEGIN(Client)

class CMap2_Tool final : public CMap2
{
private:
	CMap2_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMap2_Tool(const CMap2_Tool& rhs);
	virtual ~CMap2_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	HRESULT Ready_Components();





public:
	/* ������ü�� �����Ѵ�. */
	static CMap2_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CMap2_Tool* Clone(void* pArg) override;

	virtual void Free() override;
};

END
