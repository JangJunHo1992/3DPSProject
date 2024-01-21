#include "stdafx.h"
#include "..\Public\Map2.h"

#include "GameInstance.h"


CMap2::CMap2(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CMap2::CMap2(const CMap2& rhs)
	: CGameObject(rhs)
{
}

HRESULT CMap2::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMap2::Initialize(void* pArg)
{
	m_sName = "Map2";
	m_sLayerTag = "Layer_BackGround";

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(rand() % 20, 0.f, rand() % 20, 1.f));

	return S_OK;
}

void CMap2::Priority_Tick(_float fTimeDelta)
{

	m_pNavigationCom->Update(m_pTransformCom->Get_WorldMatrix(), fTimeDelta);

}

void CMap2::Tick(_float fTimeDelta)
{

}

void CMap2::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return;
}

HRESULT CMap2::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	_uint		iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (size_t i = 0; i < iNumMeshes; i++)
	{
		m_pModelCom->Bind_ShaderResource(m_pShaderCom, "g_DiffuseTexture", i, aiTextureType_DIFFUSE);

		m_pShaderCom->Begin(0);

		m_pModelCom->Render(i);
	}

#ifdef _DEBUG
	m_pNavigationCom->Render();
#endif

	return S_OK;
}

void CMap2::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	Out_Json["LayerTag"] = m_sLayerTag;
	__super::Write_Json(Out_Json);
}

HRESULT CMap2::Ready_Components_Origin(LEVEL eLEVEL)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;


	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Navigation"),
		TEXT("Com_Navigation"), reinterpret_cast<CComponent**>(&m_pNavigationCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CMap2::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
		return E_FAIL;

	return S_OK;
}



void CMap2::Free()
{
	__super::Free();

	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pNavigationCom);
}

