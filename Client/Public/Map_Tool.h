#pragma once

#include "Map.h"

BEGIN(Client)

class CMap_Tool final : public CMap
{
private:
	CMap_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMap_Tool(const CMap_Tool& rhs);
	virtual ~CMap_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	HRESULT Ready_Components();





public:
	/* 원형객체를 생성한다. */
	static CMap_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CMap_Tool* Clone(void* pArg) override;

	virtual void Free() override;
};

END