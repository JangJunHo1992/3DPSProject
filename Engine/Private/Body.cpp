#include "..\Public\Body.h"
#include "GameInstance.h"


CBody::CBody(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CBody::CBody(const CBody& rhs)
	: CGameObject(rhs)
{
}

CBone* CBody::Get_BonePtr(const _char* pBoneName)
{
	return m_pModelCom->Get_BonePtr(pBoneName);
}

HRESULT CBody::Initialize_Prototype()
{
	__super::Initialize_Prototype();
	return S_OK;
}

HRESULT CBody::Initialize(void* pArg)
{
	m_pParentTransform = (reinterpret_cast<BODY_DESC*>(pArg))->m_pParentTransform;
	if (nullptr == m_pParentTransform)
		return E_FAIL;
	Safe_AddRef(m_pParentTransform);

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CBody::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CBody::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_vMovePos = { 0.f, 0.f, 0.f };

	m_pModelCom->Play_Animation(fTimeDelta, m_vMovePos);

	//m_pColliderCom->Update(m_WorldMatrix);
}

void CBody::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	XMStoreFloat4x4(&m_WorldMatrix, m_pTransformCom->Get_WorldMatrix() * m_pParentTransform->Get_WorldMatrix());

	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return;
}

HRESULT CBody::Render()
{
	__super::Render();

	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	_uint		iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (size_t i = 0; i < iNumMeshes; i++)
	{
		m_pModelCom->Bind_BoneMatrices(m_pShaderCom, "g_BoneMatrices", i);

		m_pModelCom->Bind_ShaderResource(m_pShaderCom, "g_DiffuseTexture", i, aiTextureType_DIFFUSE);

		m_pShaderCom->Begin(0);

		m_pModelCom->Render(i);
	}

	return S_OK;
}

void CBody::Set_Animation(_uint _iNextAnimation, CModel::ANIM_STATE _eAnimState, _bool _bIsTransition, _bool _bUseAnimationPos, _uint iTargetKeyFrameIndex)
{
	m_pModelCom->Set_Animation(_iNextAnimation, _eAnimState, _bIsTransition, m_pModelCom->Get_TickPerSecond() / 10.f, iTargetKeyFrameIndex);
	m_pModelCom->Set_UseAnimationPos(_bUseAnimationPos);
}

_bool CBody::Is_Animation_End()
{
	return m_pModelCom->Is_AnimEnd();
}

_bool CBody::Is_Inputable_Front(_uint _iIndexFront)
{
	return m_pModelCom->Is_Inputable_Front(_iIndexFront);
}

_bool CBody::Is_Inputable_Back(_uint _iIndexBack)
{
	return m_pModelCom->Is_Inputable_Back(_iIndexBack);
}


HRESULT CBody::Bind_ShaderResources()
{
	/*if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;*/

	if (FAILED(m_pShaderCom->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
 	if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
 		return E_FAIL;

	return S_OK;
}


void CBody::Free()
{
	__super::Free();
	//Safe_Release(m_pColliderCom);
	Safe_Release(m_pParentTransform);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
}

