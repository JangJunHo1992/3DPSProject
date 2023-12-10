#pragma once

#include "ForkLift.h"

BEGIN(Client)

class CForkLift_Tool final : public CForkLift
{
private:
	CForkLift_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CForkLift_Tool(const CForkLift_Tool& rhs);
	virtual ~CForkLift_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	HRESULT Ready_Components();





public:
	/* ������ü�� �����Ѵ�. */
	static CForkLift_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CForkLift_Tool* Clone(void* pArg) override;

	virtual void Free() override;
};

END