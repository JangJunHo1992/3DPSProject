#include "stdafx.h"
#include "Terrain.h"
#include "VIBuffer_Dynamic_Terrain_Origin.h"
#include "VIBuffer_Dynamic_Plane.h"
#include "GameInstance.h"


CTerrain::CTerrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CTerrain::CTerrain(const CTerrain & rhs)
	: CGameObject(rhs)
	, m_bIsPlane(rhs.m_bIsPlane)
{
}

HRESULT CTerrain::Initialize_Prototype(_bool bIsPlane)
{	
	m_bIsPlane = bIsPlane;
	return S_OK;
}



HRESULT CTerrain::Initialize(void* pArg)
{	
	m_sName = "Terrain";
	m_sLayerTag = "Layer_BackGround";

	if (FAILED(__super::Initialize(&GAMEOBJECT_DESC(0.0f, XMConvertToRadians(20.0f)))))
		return E_FAIL;	

	//if (m_bIsPlane) 
	//{
	//	
	//}
	//else 
	//{
	//	if (FAILED(Ready_Components()))
	//		return E_FAIL;
	//}

	if (FAILED(Ready_Components()))
		return E_FAIL;



	return S_OK;
}

void CTerrain::Priority_Tick(_float fTimeDelta)
{
	m_pNavigationCom->Update(m_pTransformCom->Get_WorldMatrix(), fTimeDelta);
}

void CTerrain::Tick(_float fTimeDelta)
{

}

void CTerrain::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return ;
}

HRESULT CTerrain::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* �� �Τ��̴��� 0��° �н��� �׸�����. */
	m_pShaderCom->Begin(0);

	/* ���� �׸������ϴ� ����, �ΉK�������۸� ��ġ�� ���ε���. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* ���ε��� ����, �ε����� �׷�. */
	m_pVIBufferCom->Render();

#ifdef _DEBUG
	m_pNavigationCom->Render();
#endif

	return S_OK;
}

void CTerrain::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	Out_Json["LayerTag"] = m_sLayerTag;
	__super::Write_Json(Out_Json);
}

HRESULT CTerrain::Ready_Components_Origin(LEVEL eLEVEL)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Navigation"),
		TEXT("Com_Navigation"), reinterpret_cast<CComponent**>(&m_pNavigationCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Shader_VtxNorTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_VIBuffer */

	if (LEVEL_TOOL == eLEVEL) 
	{
		if (m_bIsPlane) 
		{
			if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_VIBuffer_Plane_Tool"),
				TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
				return E_FAIL;
		}
		else 
		{
			if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain_Tool"),
				TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
				return E_FAIL;
		}
	}
	else 
	{
		if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_VIBuffer_Terrain_GamePlay"),
			TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
			return E_FAIL;
	}

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Texture_Terrain"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom[TYPE_DIFFUSE]))))
		return E_FAIL;

	/* For.Com_Mask */
	if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Mask"),
		TEXT("Com_Mask"), reinterpret_cast<CComponent**>(&m_pTextureCom[TYPE_MASK]))))
		return E_FAIL;

	///* For.Com_Brush */
	//if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Texture_Terrain_Brush"),
	//	TEXT("Com_Brush"), reinterpret_cast<CComponent**>(&m_pTextureCom[TYPE_BRUSH]))))
	//	return E_FAIL;


	return S_OK;
}



HRESULT CTerrain::Bind_ShaderResources_Origin()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
	if (FAILED(m_pTextureCom[TYPE_DIFFUSE]->Bind_ShaderResources(m_pShaderCom, "g_DiffuseTexture")))
		return E_FAIL;
	if (FAILED(m_pTextureCom[TYPE_MASK]->Bind_ShaderResource(m_pShaderCom, "g_MaskTexture", 0)))
		return E_FAIL;



	if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
		return E_FAIL;


	return S_OK;
}



//CTerrain * CTerrain::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
//{
//	CTerrain*		pInstance = new CTerrain(pDevice, pContext);
//
//	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
//	if (FAILED(pInstance->Initialize_Prototype()))
//	{
//		MSG_BOX("Failed to Created : CTerrain");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}
//
//CGameObject * CTerrain::Clone(void* pArg)
//{
//	CTerrain*		pInstance = new CTerrain(*this);
//
//	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
//	if (FAILED(pInstance->Initialize(pArg)))
//	{
//		MSG_BOX("Failed to Cloned : CTerrain");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}

void CTerrain::Free()
{
	__super::Free();

	Safe_Release(m_pNavigationCom);

	Safe_Release(m_pVIBufferCom);

	for (size_t i = 0; i < TYPE_END; i++)
	{
		Safe_Release(m_pTextureCom[i]);
	}

	Safe_Release(m_pShaderCom);
}

//CGameObject* CTerrain::Clone(void* pArg)
//{
//	return nullptr;
//}

