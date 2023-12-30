#include "..\Public\KnightGuard_Body.h"

CKnightGuard_Body::CKnightGuard_Body(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CBody_Client(pDevice, pContext)
{
}

CKnightGuard_Body::CKnightGuard_Body(const CKnightGuard_Body& rhs)
	: CBody_Client(rhs)
{
}

HRESULT CKnightGuard_Body::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKnightGuard_Body::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CKnightGuard_Body::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CKnightGuard_Body::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CKnightGuard_Body::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CKnightGuard_Body::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKnightGuard_Body::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_KnightGuard"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CKnightGuard_Body::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;
}


void CKnightGuard_Body::Free()
{
	__super::Free();
}
