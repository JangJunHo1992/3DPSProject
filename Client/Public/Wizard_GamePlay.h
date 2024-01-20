#pragma once

#include "Wizard.h"

BEGIN(Client)

class CWizard_GamePlay final : public CWizard
{
private:
	CWizard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWizard_GamePlay(const CWizard_GamePlay& rhs);
	virtual ~CWizard_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* 원형객체를 생성한다. */
	static CWizard_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CWizard_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END