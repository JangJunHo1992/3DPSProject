#pragma once

#include "ForkLift.h"

BEGIN(Client)

class CForkLift_GamePlay final : public CForkLift
{
private:
	CForkLift_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CForkLift_GamePlay(const CForkLift_GamePlay& rhs);
	virtual ~CForkLift_GamePlay() = default;

private:
	HRESULT Ready_Components();


public:
	/* ������ü�� �����Ѵ�. */
	static CForkLift_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CForkLift_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;
};

END