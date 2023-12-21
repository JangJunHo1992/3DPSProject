#include "stdafx.h"
#include "Raider.h"

#include "GameInstance.h"


CRaider::CRaider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCharacter(pDevice, pContext)
{

}

CRaider::CRaider(const CRaider& rhs)
	: CCharacter(rhs)
{
}

HRESULT CRaider::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CRaider::Initialize(void* pArg)
{
	m_sName = "Raider";
	m_sLayerTag = "Layer_Monster";

	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 10.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;
	m_pModelCom->Set_Animation(rand() % 20, CModel::ANIM_STATE_LOOP, false);
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(rand() % 20, 0.f, rand() % 20, 1.f));
	return S_OK;
}

void CRaider::Priority_Tick(_float fTimeDelta)
{



}

void CRaider::Tick(_float fTimeDelta)
{
	_float3 vPos = { 0.f, 0.f, 0.f };
	m_pModelCom->Play_Animation(fTimeDelta, vPos);
	m_pTransformCom->Add_Position(vPos);
}

void CRaider::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return;
}

HRESULT CRaider::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	_uint		iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (size_t i = 0; i < iNumMeshes; i++)
	{
		m_pModelCom->Bind_BoneMatrices(m_pShaderCom, "g_BoneMatrices", i);

		m_pModelCom->Bind_ShaderResource(m_pShaderCom, "g_DiffuseTexture", i, Type_DIFFUSE);

		m_pShaderCom->Begin(0);

		m_pModelCom->Render(i);
	}

	return S_OK;
}

void CRaider::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	Out_Json["LayerTag"] = m_sLayerTag;
	__super::Write_Json(Out_Json);
}

HRESULT CRaider::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_AnimModel"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Model */
	//if (FAILED(__super::Add_Component(LEVEL_TOOL, TEXT("Prototype_Component_Model_Raider"),
	//	TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
	//	return E_FAIL;

	return S_OK;
}

HRESULT CRaider::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
		return E_FAIL;

	//if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
	//	return E_FAIL;
	return S_OK;
}



void CRaider::Free()
{
	__super::Free();

	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
}

