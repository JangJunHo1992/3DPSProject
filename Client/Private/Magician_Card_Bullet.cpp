#include "stdafx.h"
#include "..\Public\Magician_Card_Bullet.h"

#include "Character.h"
#include "GameInstance.h"
#include "Particle_Custom.h"

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

CParticle_Custom::PARTICLE_DESC CMagician_Card_Bullet::Get_Particle_Blood_Desc()
{
	CParticle_Custom::PARTICLE_DESC Desc;

	Desc.ParticleDesc.vRange = _float2(0.5f, 1.0f);
	Desc.ParticleDesc.vSpeed = _float2(0.9f, 3.f);
	Desc.ParticleDesc.vCenter.x = _float(1.f);
	Desc.ParticleDesc.vCenter.y = _float(0.f);
	Desc.ParticleDesc.vCenter.z = _float(1.f);
	Desc.ParticleDesc.fAcceleration = -3.f;
	Desc.ParticleDesc.vRotationX = _float2(0.f, 360.f);
	Desc.ParticleDesc.vRotationY = _float2(0.f, 360.f);
	Desc.ParticleDesc.vRotationZ = _float2(0.f, 360.f);
	Desc.ParticleDesc.vLifeTime = _float2(0.1f, 1.5f);
	Desc.ParticleDesc.vScaleX = _float2(0.10000000149011612f, 0.30000001192092896f);
	Desc.ParticleDesc.vScaleY = _float2(0.10000000149011612f, 0.30000001192092896f);

	return Desc;
}



CParticle_Custom::PARTICLE_DESC CMagician_Card_Bullet::Get_Particle_HalfMoon_Desc()
{
	CParticle_Custom::PARTICLE_DESC Desc;

	Desc.ParticleDesc.vRange = _float2(0.6f, 0.6f);
	Desc.ParticleDesc.vSpeed = _float2(5.f, 5.f);
	Desc.ParticleDesc.vCenter.x = _float(0.4f);
	Desc.ParticleDesc.vCenter.y = _float(0.f);
	Desc.ParticleDesc.vCenter.z = _float(0.f);
	Desc.ParticleDesc.fAcceleration = -29.f;
	Desc.ParticleDesc.vRotationX = _float2(270.f, 270.f);
	Desc.ParticleDesc.vRotationY = _float2(180.f, 360.f);
	Desc.ParticleDesc.vRotationZ = _float2(360.f, 360.f);
	Desc.ParticleDesc.vLifeTime = _float2(0.9f, 0.9f);
	Desc.ParticleDesc.vScaleX = _float2(0.2f, 0.2f);
	Desc.ParticleDesc.vScaleY = _float2(0.2f, 0.2f);

	return Desc;
}

HRESULT CMagician_Card_Bullet::Initialize(void* pArg)
{
	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 13.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	

	list<CGameObject*>* _pMTargets = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Monster"));

	if (nullptr == _pMTargets)
		return E_FAIL;
	
	for (CGameObject* pGameObject : *_pMTargets)
	{
		
		CCharacter* m_pMonster = dynamic_cast<CCharacter*>(pGameObject);
		m_vMonsterPos = m_pMonster->Get_TransformComp()->Get_State(CTransform::STATE_POSITION)+ 2*m_pMonster->Get_TransformComp()->Get_State(CTransform::STATE_UP);
		m_pTransformCom->Set_WorldMatrix(m_pMonster->Get_TransformComp()->Get_WorldMatrix());
	}

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_vMonsterPos);

	list<CGameObject*>* _pTargets = m_pGameInstance->Get_GameObjects(LEVEL_BOSS2, TEXT("Layer_Player"));

	if (nullptr == _pTargets)
		return E_FAIL;

	for (CGameObject* pGameObject : *_pTargets)
	{
		CCharacter* m_pPlayer = dynamic_cast<CCharacter*>(pGameObject);
		m_vPlayerPos = m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_POSITION)+ 2 * m_pPlayer->Get_TransformComp()->Get_State(CTransform::STATE_UP);
	}

	m_pTransformCom->Look_At(m_vPlayerPos);


	

	return S_OK;
}

void CMagician_Card_Bullet::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CMagician_Card_Bullet::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	m_WorldMatrix = m_pTransformCom->Get_WorldMatrix();

	if (m_iCardDeadTime < 0)
	{
		m_bisdead = true;
	}
	else
	{
		--m_iCardDeadTime;
	}

	m_pTransformCom->Go_Straight(fTimeDelta);

	m_pColliderCom->Update(m_pTransformCom->Get_WorldMatrix());
	
	Collision_Chcek();

}

void CMagician_Card_Bullet::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

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
	__super::Render();

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
				Create_Attack_Particle(LEVEL_BOSS2, m_pColliderCom->GetCenterPos());
				pAlreadyHittedCharacter = pTarget;
				bIsCollision = true;
				Set_isdead(true);
				break;
			}
		
		}
	}


	return bIsCollision;
}

void CMagician_Card_Bullet::Create_Attack_Particle(LEVEL eLevel, _float3 vLocalPos)
{
	_uint iRandom = rand() % 3;

	{
		CParticle_Custom::PARTICLE_DESC Desc = Get_Particle_HalfMoon_Desc();
		switch (iRandom)
		{
		case 0:
			m_pGameInstance->Play_Sound(L"ENEMY_HIT", L"BodyHit_01.ogg", SOUND_Monster, 1.f);
			break;
		case 1:
			m_pGameInstance->Play_Sound(L"ENEMY_HIT", L"BodyHit_02.ogg", SOUND_Monster, 1.f);
			break;
		case 2:
			m_pGameInstance->Play_Sound(L"ENEMY_HIT", L"BodyHit_03.ogg", SOUND_Monster, 1.f);
			break;
		}
		_float3 vPos;
		XMStoreFloat3(&vPos, XMVector3Transform(XMLoadFloat3(&vLocalPos), m_WorldMatrix));

		Desc.parentMatrix = m_WorldMatrix;
		Desc.vPos = vPos;

		m_pGameInstance->Add_CloneObject(eLevel, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Particle_Custom"), &Desc);
	}
	if (iRandom == 2)
	{
		CParticle_Custom::PARTICLE_DESC Desc = Get_Particle_Blood_Desc();
		switch (iRandom)
		{
		case 0:
			m_pGameInstance->Play_Sound(L"PLAYER_HIT", L"CriticalHit_01.ogg", SOUND_PLAYER, 1.f);
			break;
		case 1:
			m_pGameInstance->Play_Sound(L"PLAYER_HIT", L"CriticalHit_02.ogg", SOUND_PLAYER, 1.f);
			break;
		case 2:
			m_pGameInstance->Play_Sound(L"PLAYER_HIT", L"CriticalHit_03.ogg", SOUND_PLAYER, 1.f);
			break;
		}

		_float3 vPos;
		XMStoreFloat3(&vPos, XMVector3Transform(XMLoadFloat3(&vLocalPos), m_WorldMatrix));

		Desc.parentMatrix = m_WorldMatrix;
		Desc.vPos = vPos;

		m_pGameInstance->Add_CloneObject(eLevel, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Particle_Custom"), &Desc);
	}
}

HRESULT CMagician_Card_Bullet::Ready_Components_Origin(LEVEL eLEVEL)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_Shader_Model"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	CBounding_Sphere::BOUNDING_SPHERE_DESC BoundingDesc = {};


	BoundingDesc.fRadius = 0.2f;
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
	if (FAILED(m_pShaderCom->Bind_Matrix("g_WorldMatrix", &m_WorldMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;


	return S_OK;
}

void CMagician_Card_Bullet::Free()
{
	__super::Free();

	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pColliderCom);
}

