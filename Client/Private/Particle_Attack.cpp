#include "stdafx.h"
#include "Particle_Attack.h"

#include "GameInstance.h"

#include "VIBuffer_Particle_Point.h"

CParticle_Attack::CParticle_Attack(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CParticle_Attack::CParticle_Attack(const CParticle_Attack& rhs)
	: CGameObject(rhs)
{
	//m_pVIBufferCom
}

HRESULT CParticle_Attack::Initialize_Prototype()
{
	/* ������ü�� �ʱ�ȭ������ �����Ѵ�. */
	/* 1.�����κ��� ���� �޾ƿͼ� �ʱ�ȭ�Ѵ� .*/
	/* 2.����������� ���� ���� �޾ƿ´�.*/
	//int*		pData_int = new int(3);

	//void**		pData = (void**)&pData_int;

	return S_OK;
}

HRESULT CParticle_Attack::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	PARTICLE_DESC* Desc = (PARTICLE_DESC*)pArg;
	CVIBuffer_Particle_Point::PARTICLE_POINT_DESC ParticleDesc = Desc->ParticleDesc;

	//m_pTransformCom->Set_WorldMatrix(Desc->parentMatrix);



	_float4 vPos = Desc->vPos;
	vPos.w = 1;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMLoadFloat4(&vPos));
	m_pTransformCom->Rotation(Desc->parentMatrix);

	m_ParticleDesc = ParticleDesc;

	if (m_pGameInstance->Get_NextLevel() == 2)
	{
		if (FAILED(Ready_Components(LEVEL_GAMEPLAY)))
			return E_FAIL;
	}
	else if (m_pGameInstance->Get_NextLevel() == 6)
	{
		if (FAILED(Ready_Components(LEVEL_BOSS1)))
			return E_FAIL;
	}
	else if (m_pGameInstance->Get_NextLevel() == 7)
	{
		if (FAILED(Ready_Components(LEVEL_BOSS2)))
			return E_FAIL;
	}


	return S_OK;
}

void CParticle_Attack::Priority_Tick(_float fTimeDelta)
{

}

void CParticle_Attack::Tick(_float fTimeDelta)
{
	m_pVIBufferCom->Update(fTimeDelta);
	m_fTimeAcc += fTimeDelta;

	if (m_fTimeAcc >= m_ParticleDesc.vLifeTime.y)
		m_bisdead = true;

}

void CParticle_Attack::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONLIGHT, this)))
		return;

}

HRESULT CParticle_Attack::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* �� �Τ��̴��� 0��° �н��� �׸�����. */
	m_pShaderCom->Begin(0);

	/* ���� �׸������ϴ� ����, �ΉK�������۸� ��ġ�� ���ε���. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* ���ε��� ����, �ε����� �׷�. */
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CParticle_Attack::Ready_Components(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_Particle_Point"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;


	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_VIBuffer_Particle_Point"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom), &m_ParticleDesc)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Texture_Snow"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CParticle_Attack::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;


	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->Bind_ShaderResource(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
		return E_FAIL;

	return S_OK;
}

CParticle_Attack* CParticle_Attack::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CParticle_Attack* pInstance = new CParticle_Attack(pDevice, pContext);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CParticle_Attack");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CParticle_Attack::Clone(void* pArg)
{
	CParticle_Attack* pInstance = new CParticle_Attack(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CParticle_Attack");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CParticle_Attack::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
}

