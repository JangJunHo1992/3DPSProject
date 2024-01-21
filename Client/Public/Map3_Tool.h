#pragma once

#include "Map3.h"

BEGIN(Client)

class CMap3_Tool final : public CMap3
{
private:
	CMap3_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMap3_Tool(const CMap3_Tool& rhs);
	virtual ~CMap3_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	HRESULT Ready_Components();





public:
	/* 원형객체를 생성한다. */
	static CMap3_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CMap3_Tool* Clone(void* pArg) override;

	virtual void Free() override;
};

END