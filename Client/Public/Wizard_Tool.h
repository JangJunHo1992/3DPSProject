#pragma once

#include "Wizard.h"

BEGIN(Client)

class CWizard_Tool final : public CWizard
{
private:
	CWizard_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWizard_Tool(const CWizard_Tool& rhs);
	virtual ~CWizard_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CWizard_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CWizard_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END