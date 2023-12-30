#pragma once

#include "Wizard_Body.h"

BEGIN(Client)

class CWizard_Body_GamePlay final : public CWizard_Body
{
private:
	CWizard_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWizard_Body_GamePlay(const CWizard_Body_GamePlay& rhs);
	virtual ~CWizard_Body_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CWizard_Body_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END