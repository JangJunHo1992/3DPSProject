#include "Covus_Weapon_Saber_EffectTool.h"


CCovus_Weapon_Saber_EffectTool::CCovus_Weapon_Saber_EffectTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CCovus_Weapon_Saber_EffectTool::CCovus_Weapon_Saber_EffectTool(const CCovus_Weapon_Saber_EffectTool& rhs)
	: CGameObject(rhs)
{
}

HRESULT CCovus_Weapon_Saber_EffectTool::Ready_Components()
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_Model */
	//if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Model_Raider_Weapon_DoubleSword"),
	if (FAILED(__super::Add_Component(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Model_Covus_Weapon_Saber"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_Weapon_Saber_EffectTool::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus_Weapon_Saber_EffectTool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;


	return S_OK;
}

void CCovus_Weapon_Saber_EffectTool::Priority_Tick(_float fTimeDelta)
{
}

void CCovus_Weapon_Saber_EffectTool::Tick(_float fTimeDelta)
{
}

void CCovus_Weapon_Saber_EffectTool::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return;
}

HRESULT CCovus_Weapon_Saber_EffectTool::Render()
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

	return S_OK;
}


HRESULT CCovus_Weapon_Saber_EffectTool::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
	return S_OK;
}

CCovus_Weapon_Saber_EffectTool* CCovus_Weapon_Saber_EffectTool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CCovus_Weapon_Saber_EffectTool* pInstance = new CCovus_Weapon_Saber_EffectTool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CCovus_Weapon_Saber_EffectTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCovus_Weapon_Saber_EffectTool::Clone(void* pArg)
{
	CCovus_Weapon_Saber_EffectTool* pInstance = new CCovus_Weapon_Saber_EffectTool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CCovus_Weapon_Saber_EffectTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCovus_Weapon_Saber_EffectTool::Free()
{
	__super::Free();
}
