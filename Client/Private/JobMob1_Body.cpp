#include "JobMob1_Body.h"
#include "Transform.h"

CJobMob1_Body::CJobMob1_Body(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CBody_Client(pDevice, pContext)
{
}

CJobMob1_Body::CJobMob1_Body(const CJobMob1_Body& rhs)
	: CBody_Client(rhs)
{
}

HRESULT CJobMob1_Body::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1_Body::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CJobMob1_Body::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CJobMob1_Body::Tick(_float fTimeDelta)
{
	
	__super::Tick(fTimeDelta);
	if (true == Get_CheckAnimDead())
	{
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) - 2.5 * m_pTransformCom->Get_State(CTransform::STATE_UP));
		Set_CheckAnimDead(false);
	}
}

void CJobMob1_Body::Late_Tick(_float fTimeDelta)
{
	
	__super::Late_Tick(fTimeDelta);
}

HRESULT CJobMob1_Body::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1_Body::Ready_Components_Origin(LEVEL eLevel)
{
	if (FAILED(__super::Ready_Components_Origin(eLevel)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_JobMob1"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1_Body::Bind_ShaderResources()
{
	if (FAILED(__super::Bind_ShaderResources()))
		return E_FAIL;
}


void CJobMob1_Body::Free()
{
	__super::Free();
}
