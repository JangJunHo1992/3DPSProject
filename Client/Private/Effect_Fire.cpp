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
	
	/* ������ü�� �ʱ�ȭ������ �����Ѵ�. */
	/* 1.�����κ��� ���� �޾ƿͼ� �ʱ�ȭ�Ѵ� .*/
	/* 2.����������� ���� ���� �޾ƿ´�.*/
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

	// void* pArg : �����Ͽ� ��ü�� �����Ҷ� �������� ä���� ���� �����͸� �߰������� �� �ʱ�ȭ���ֱ����ؼ�. 
	if (FAILED(Ready_Components()))
		return E_FAIL;

	LIGHT_DESC		m_LightDesc{};

	m_LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	m_LightDesc.vPosition = m_pTransformCom->Get_Position();
	m_LightDesc.fRange = 10.f;
	m_LightDesc.vDiffuse = _float4(0.6f, 0.8f, 1.0f, 1.0f);
	m_LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	m_LightDesc.vSpecular = m_LightDesc.vDiffuse;

	if (FAILED(m_pGameInstance->Add_Light(m_LightDesc)))
		return E_FAIL;

	return S_OK;
}

void CEffect_Fire::Priority_Tick(_float fTimeDelta)
{
	
}

void CEffect_Fire::Tick(_float fTimeDelta)
{
	m_fFrame += 36.f * fTimeDelta;

	if (m_fFrame >= 36.0f)
		m_fFrame = 0.f;
}

void CEffect_Fire::Late_Tick(_float fTimeDelta)
{
	Compute_CamDistance();

	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_BLEND, this)))
		return;
}

HRESULT CEffect_Fire::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* �� �Τ��̴��� 0��° �н��� �׸�����. */
	m_pShaderCom->Begin(1);

	/* ���� �׸������ϴ� ����, �ΉK�������۸� ��ġ�� ���ε���. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* ���ε��� ����, �ε����� �׷�. */
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CEffect_Fire::Ready_Components()
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
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Texture_Fire"),
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

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
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

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
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

