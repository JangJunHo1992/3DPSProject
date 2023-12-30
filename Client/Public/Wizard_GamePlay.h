#pragma once

#include "Wizard.h"
#include "Actor.h"

BEGIN(Client)

class CWizard_GamePlay final : public CWizard
{
private:
	CWizard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CWizard_GamePlay(const CWizard_GamePlay& rhs);
	virtual ~CWizard_GamePlay() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Set_Hitted() override;

private:
	virtual HRESULT Ready_Components() override;

private:
	CActor<CWizard_GamePlay>* m_pActor = { nullptr };

public:
	/* ������ü�� �����Ѵ�. */
	static CWizard_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CWizard_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END