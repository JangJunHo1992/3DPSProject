#include "stdafx.h"
#include "..\Public\Magician_Card_Bullet.h"

#include "Character.h"
#include "GameInstance.h"


CMagician_Card_Bullet::CMagician_Card_Bullet(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CMagician_Card_Bullet::CMagician_Card_Bullet(const CMagician_Card_Bullet& rhs)
	: CGameObject(rhs)
{
}

HRESULT CMagician_Card_Bullet::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CMagician_Card_Bullet::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;


	

	return S_OK;
}

void CMagician_Card_Bullet::Priority_Tick(_float fTimeDelta)
{

}

void CMagician_Card_Bullet::Tick(_float fTimeDelta)
{
	m_pColliderCom->Update(m_pTransformCom->Get_WorldMatrix());

	Collision_Chcek();
}

void CMagician_Card_Bullet::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return;
#ifdef _DEBUG
	//m_pNavigationCom->Render();
	m_pGameInstance->Add_DebugRender(m_pColliderCom);
	/*m_pColliderCom->Render();*/
#endif
}

HRESULT CMagician_Card_Bullet::Render()
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


_bool CMagician_Card_Bullet::Collision_Chcek()
{
	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;

	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));
	for (CGameObject* pGameObject : _Targets)
	{

		CCharacter* pTarget = dynamic_cast<CCharacter*>(pGameObject);
		if (pTarget)
		{
			CCollider* pTargetCollider = pTarget->Get_Collider();
			if (nullptr == pTargetCollider)
				continue;

		
			_bool isCollision =m_pColliderCom->Collision(pTargetCollider);
			if (isCollision)
			{
				if (pTarget->Get_Parry() == false)
				{
					pTarget->Set_Hitted();
				}
				pAlreadyHittedCharacter = pTarget;
				bIsCollision = true;
				Set_isdead(true);
				break;
			}
		
		}
	}


	return bIsCollision;
}

HRESULT CMagician_Card_Bullet::Ready_Components_Origin(LEVEL eLEVEL)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLEVEL, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};


	BoundingDesc.fRadius = 0.8f;
	BoundingDesc.vCenter = m_pTransformCom->Get_State(CTransform::STATE_POSITION);


	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_Collider_Sphere"),
		TEXT("Com_Collider"), reinterpret_cast<CComponent**>(&m_pColliderCom), &BoundingDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMagician_Card_Bullet::Bind_ShaderResources()
{
// 	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
// 		return E_FAIL;
// 	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
// 		return E_FAIL;
// 	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
// 		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

// 	if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
// 		return E_FAIL;

	//if (FAILED(m_pShaderCom->Bind_RawValue("g_vCamPosition", &m_pGameInstance->Get_CamPosition(), sizeof(_float4))))
	//	return E_FAIL;
	return S_OK;
}

void CMagician_Card_Bullet::Free()
{
	__super::Free();

	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
}

