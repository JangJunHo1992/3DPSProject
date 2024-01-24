#pragma once

#include "Varg_Body.h"

BEGIN(Client)

class CVarg_Body_GamePlay final : public CVarg_Body
{
private:
	CVarg_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVarg_Body_GamePlay(const CVarg_Body_GamePlay& rhs);
	virtual ~CVarg_Body_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CVarg_Body_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END