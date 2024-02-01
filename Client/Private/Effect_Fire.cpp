#include "stdafx.h"
#include "Effect_Fire.h"

#include "GameInstance.h"


CEffect_Fire::CEffect_Fire(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CAlphaObject(pDevice, pContext)
{

}

CEffect_Fire::CEffect_Fire(const CEffect_Fire& rhs)
	: CAlphaObject(rhs)
{
}

HRESULT CEffect_Fire::Initialize_Prototype()
{
	
	/* 원형객체의 초기화과정을 수행한다. */
	/* 1.서버로부터 값을 받아와서 초기화한다 .*/
	/* 2.파일입출력을 통해 값을 받아온다.*/
	//int*		pData_int = new int(3);

	//void**		pData = (void**)&pData_int;

	return S_OK;
}

HRESULT CEffect_Fire::Initialize(void* pArg)
{
	m_sName = "Fire";
	m_sLayerTag = "Layer_Effect";

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	// void* pArg : 복제하여 객체를 생성할때 원형에서 채우지 못한 데이터를 추가적으로 더 초기화해주기위해서. 
	
	if (FAILED(Ready_Components(LEVEL_GAMEPLAY)))
		return E_FAIL;
// 	}
// 	else if (m_pGameInstance->Get_CurrentLevel() == 3)
// 	{
// 		if (FAILED(Ready_Components(LEVEL_TOOL)))
// 			return E_FAIL;
// 	}
// 	else if (m_pGameInstance->Get_CurrentLevel() == 6)
// 	{
// 		if (FAILED(Ready_Components(LEVEL_BOSS1)))
// 			return E_FAIL;
// 	}
// 	else if (m_pGameInstance->Get_CurrentLevel() == 7)
// 	{
// 		if (FAILED(Ready_Components(LEVEL_BOSS2)))
// 			return E_FAIL;
// 	}

	

	

	return S_OK;
}

void CEffect_Fire::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
	
}

void CEffect_Fire::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_fFrame += 36.f * fTimeDelta;

	if (m_fFrame >= 36.0f)
		m_fFrame = 0.f;
}
	
void CEffect_Fire::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	Compute_CamDistance();

	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_BLEND, this)))
		return;
}

HRESULT CEffect_Fire::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* 이 셰ㅒ이더에 0번째 패스로 그릴꺼야. */
	m_pShaderCom->Begin(1);

	/* 내가 그릴려고하는 정점, 인덷ㄱ스버퍼를 장치에 바인딩해. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* 바인딩된 정점, 인덱스를 그려. */
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CEffect_Fire::Ready_Components(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxPosTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Texture_Fire"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CEffect_Fire::Bind_ShaderResources()
{

	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->Bind_ShaderResource(m_pShaderCom, "g_DiffuseTexture", _uint(m_fFrame))))
		return E_FAIL;

// 	if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
// 		return E_FAIL;

	if (FAILED(m_pGameInstance->Bind_RenderTarget_ShaderResource(TEXT("Target_Depth"), m_pShaderCom, "g_DepthTexture")))
		return E_FAIL;

	return S_OK;
}

void CEffect_Fire::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	Out_Json["LayerTag"] = m_sLayerTag;
	__super::Write_Json(Out_Json);
}

CEffect_Fire* CEffect_Fire::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CEffect_Fire* pInstance = new CEffect_Fire(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CEffect_Fire");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CEffect_Fire::Clone(void* pArg)
{
	CEffect_Fire* pInstance = new CEffect_Fire(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CEffect_Fire");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEffect_Fire::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
}

