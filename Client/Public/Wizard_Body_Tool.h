#pragma once

#include "Wizard_Body.h"

BEGIN(Client)

class CWizard_Body_Tool final : public CWizard_Body
{
private:
	CWizard_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWizard_Body_Tool(const CWizard_Body_Tool& rhs);
	virtual ~CWizard_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CWizard_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END