#include "stdafx.h"
#include "..\Public\Particle_Custom_EffectTool.h"

#include "GameInstance.h"

#include "VIBuffer_Particle_Point.h"

CParticle_Custom_EffectTool::CParticle_Custom_EffectTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CParticle_Custom(pDevice, pContext)
{

}

CParticle_Custom_EffectTool::CParticle_Custom_EffectTool(const CParticle_Custom_EffectTool& rhs)
	: CParticle_Custom(rhs)
{
}

HRESULT CParticle_Custom_EffectTool::Ready_Components()
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Shader_Particle_Point"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;


	if (FAILED(__super::Add_Component(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_VIBuffer_Particle_Point"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom), &m_ParticleDesc)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_EFFECT_TOOL, TEXT("Prototype_Component_Texture_Snow"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	return S_OK;
}

CParticle_Custom_EffectTool* CParticle_Custom_EffectTool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CParticle_Custom_EffectTool* pInstance = new CParticle_Custom_EffectTool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CParticle_Custom_EffectTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CParticle_Custom_EffectTool::Clone(void* pArg)
{
	CParticle_Custom_EffectTool* pInstance = new CParticle_Custom_EffectTool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CParticle_Custom_EffectTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CParticle_Custom_EffectTool::Free()
{
	__super::Free();
}

