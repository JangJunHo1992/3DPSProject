#include "stdafx.h"
#include "Effect_Monster_Trail.h"
#include "GameInstance.h"
#include "VIBuffer_Trail.h"


#include "Texture.h"
#include "Bone.h"
#include "Shader.h"

CEffect_Monster_Trail::CEffect_Monster_Trail(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CAlphaObject(pDevice, pContext)
{
}

CEffect_Monster_Trail::CEffect_Monster_Trail(const CEffect_Monster_Trail& rhs)
	: CAlphaObject(rhs)
{
}

HRESULT CEffect_Monster_Trail::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CEffect_Monster_Trail::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	TRAIL_DESC TrailDesc = *(TRAIL_DESC*)pArg;

	// 	/* For.Com_Trail */
	// 	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Trail"),
	// 		TEXT("Com_Trail"), reinterpret_cast<CComponent**>(&m_pVIBuffer), &TrailDesc)))
	// 		return E_FAIL;

		//if (3 == TrailDesc.iPass)
		//	m_iPass = 3;
	if (m_pGameInstance->Get_NextLevel() == 2)
	{
		if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_VIBuffer_Monster_Trail"),
			TEXT("Com_Trail"), reinterpret_cast<CComponent**>(&m_pVIBuffer), &TrailDesc)))
			return E_FAIL;

		if (FAILED(Ready_Components(LEVEL_GAMEPLAY)))
			return E_FAIL;
	}
	else if (m_pGameInstance->Get_NextLevel() == 6)
	{
		if (FAILED(__super::Add_Component(LEVEL_BOSS1, TEXT("Prototype_Component_VIBuffer_Monster_Trail"),
			TEXT("Com_Trail"), reinterpret_cast<CComponent**>(&m_pVIBuffer), &TrailDesc)))
			return E_FAIL;

		if (FAILED(Ready_Components(LEVEL_BOSS1)))
			return E_FAIL;
	}
	else if (m_pGameInstance->Get_NextLevel() == 7)
	{
		if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_VIBuffer_Monster_Trail"),
			TEXT("Com_Trail"), reinterpret_cast<CComponent**>(&m_pVIBuffer), &TrailDesc)))
			return E_FAIL;

		if (FAILED(Ready_Components(LEVEL_BOSS2)))
			return E_FAIL;
	}


	return S_OK;
}

void CEffect_Monster_Trail::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CEffect_Monster_Trail::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	Compute_CamDistance();

	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_BLEND, this)))
		return;
}

HRESULT CEffect_Monster_Trail::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	m_pShader->Begin(2);

	m_pVIBuffer->Bind_VIBuffers();

	m_pVIBuffer->Render();

	return S_OK;
}

void CEffect_Monster_Trail::Update(_float fTimeDelta, _matrix _ParentMatrix)
{

	if (false == m_bIsUse)
	{
		m_pVIBuffer->Reset_Points(_ParentMatrix);
		return;
	}


	m_pVIBuffer->Update(fTimeDelta, _ParentMatrix);
}

void CEffect_Monster_Trail::Set_OwnerDesc(_matrix _ParentMatrix)
{
	XMStoreFloat4x4(&m_pParentMatrix, _ParentMatrix);
}

HRESULT CEffect_Monster_Trail::Ready_Components(LEVEL eLevel)
{
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxPosTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShader))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Texture_Trail"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Texture_UVMask"),
		TEXT("Com_MaskTexture"), reinterpret_cast<CComponent**>(&m_pMaskTextureCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Texture_UVNoise"),
		TEXT("Com_NoiseTexture"), reinterpret_cast<CComponent**>(&m_pNoiseTextureCom))))
		return E_FAIL;


	//if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_EffectMesh"),
	//	TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShader))))
	//	return E_FAIL;



	return S_OK;
}

HRESULT CEffect_Monster_Trail::Bind_ShaderResources()
{


	//if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
	//	return E_FAIL;
	//if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
	//	return E_FAIL;

	//if (FAILED(m_pTextureCom->Bind_ShaderResource(m_pShader, "g_DiffuseTexture", m_iDiffuseIndex)))
	//	return E_FAIL;
	//if (FAILED(m_pNoiseTextureCom->Bind_ShaderResource(m_pShader, "g_NoiseTexture", m_iNoiseIndex)))
	//	return E_FAIL;
	//if (FAILED(m_pMaskTextureCom->Bind_ShaderResource(m_pShader, "g_MaskTexture", m_iMaskIndex)))
	//	return E_FAIL;



	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShader, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShader->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	if (FAILED(m_pTextureCom->Bind_ShaderResource(m_pShader, "g_DiffuseTexture")))
		return E_FAIL;
	m_iMaskIndex = 628;
	if (FAILED(m_pMaskTextureCom->Bind_ShaderResource(m_pShader, "g_MaskTexture", m_iMaskIndex)))
		return E_FAIL;
	m_iNoiseIndex = 36;
	if (FAILED(m_pNoiseTextureCom->Bind_ShaderResource(m_pShader, "g_DistortionTexture", m_iNoiseIndex)))
		return E_FAIL;
	if (FAILED(m_pGameInstance->Bind_RenderTarget_ShaderResource(TEXT("Target_Depth"), m_pShader, "g_DepthTexture")))
		return E_FAIL;

	return S_OK;
}


CEffect_Monster_Trail* CEffect_Monster_Trail::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CEffect_Monster_Trail* pInstance = new CEffect_Monster_Trail(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CEffect_Monster_Trail");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CEffect_Monster_Trail::Clone(void* pArg)
{
	CEffect_Monster_Trail* pInstance = new CEffect_Monster_Trail(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CEffect_Monster_Trail");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEffect_Monster_Trail::Free()
{
	__super::Free();

	Safe_Release(m_pShader);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pMaskTextureCom);
	Safe_Release(m_pNoiseTextureCom);
	Safe_Release(m_pVIBuffer);


}
