#include "Varg_Body.h"

CVarg_Body::CVarg_Body(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CBody_Client(pDevice, pContext)
{
}

CVarg_Body::CVarg_Body(const CVarg_Body& rhs)
	: CBody_Client(rhs)
{
}

HRESULT CVarg_Body::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_Body::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CVarg_Body::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CVarg_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CVarg_Body::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CVarg_Body::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_Body::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Varg"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg_Body::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;
}


void CVarg_Body::Free()
{
	__super::Free();
}
