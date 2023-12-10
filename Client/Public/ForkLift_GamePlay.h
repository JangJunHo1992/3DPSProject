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
	/* 원형객체를 생성한다. */
	static CForkLift_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CForkLift_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;
};

END