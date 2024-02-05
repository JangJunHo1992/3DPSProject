#include "stdafx.h"
#include "JobMob1.h"
#include "GameInstance.h"

#include "JobMob1_Body.h"
#include "JobMob1_Weapon.h"

CJobMob1::CJobMob1(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCharacter_Client(pDevice, pContext)
{

}

CJobMob1::CJobMob1(const CJobMob1& rhs)
	: CCharacter_Client(rhs)
{
}

HRESULT CJobMob1::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob1::Initialize(void* pArg)
{
	m_sName = "JobMob1";
	m_sLayerTag = "Layer_Monster";

	
	JobMob1Status.m_iAttack = 10;
	JobMob1Status.m_iHP = 100;

	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 10.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(-30.f, 0.f, 0.f, 1.f));

	return S_OK;
}

void CJobMob1::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CJobMob1::Tick(_float fTimeDelta)
{
	if (m_iCurrentLevelIn == 2)
		Collision_Chcek(LEVEL_GAMEPLAY);
	else if (m_iCurrentLevelIn == 6)
		Collision_Chcek(LEVEL_BOSS1);
	else if (m_iCurrentLevelIn == 7)
		Collision_Chcek(LEVEL_BOSS2);
	__super::Tick(fTimeDelta);
}

void CJobMob1::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
	if (Get_HasBeenHit() == true)
		++m_iCheckHitTime;

	if (Get_HasBeenHit() == true && m_iCheckHitTime >5.f)
	{
		Set_HasBeenHit(false);
		m_iCheckHitTime = 0;
	}
}

HRESULT CJobMob1::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

_bool CJobMob1::Collision_Chcek(LEVEL eLevel)//_uint eLevel
{
	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;
	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(eLevel, TEXT("Layer_Player"));
	for (CGameObject* pGameObject : _Targets)
	{
		CCharacter* pTarget = dynamic_cast<CCharacter*>(pGameObject);
		if (pTarget)
		{
			CCollider* pTargetCollider = pTarget->Get_Collider();
			if (nullptr == pTargetCollider && pTargetCollider != m_pColliderCom)
				continue;

			_bool isCollision = m_pColliderCom->Collision(pTargetCollider);
			if (isCollision)
			{

				_vector vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				pTarget->Pushed(vPos);
				bIsCollision = true;
			}

		}
	}


	return bIsCollision;
}

void CJobMob1::Set_Hitted()
{
	if (m_bCheckDead == false && Get_HasBeenHit() == false)
	{
		Set_IsAttack(false);
		CJobMob1::JobMob1State eHitted = CJobMob1::JobMob1State::HurtS_FL;
		Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
		JobMob1Status.m_iHP -= 10;
// 		if (m_iCurrentLevelIn == 2)
// 		{
// 			Create_Attack_Particle(LEVEL_GAMEPLAY, m_pColliderCom->GetCenterPos());
// 		}
// 		else if (m_iCurrentLevelIn == 6)
// 		{
// 			Create_Attack_Particle(LEVEL_BOSS1, m_pColliderCom->GetCenterPos());
// 		}
// 		else if (m_iCurrentLevelIn == 7)
// 		{
// 			Create_Attack_Particle(LEVEL_BOSS2, m_pColliderCom->GetCenterPos());
// 		}
	}
	
}
void CJobMob1::Create_Attack_Particle(LEVEL eLevel, _float3 vLocalPos)
{
	{
		//CParticle_Hit::PARTICLE_DESC Desc = Get_Particle_Hitblood_Desc();
		//
		//_float3 vPos;
		//XMStoreFloat3(&vPos, XMVector3Transform(XMLoadFloat3(&vLocalPos), m_pTransformCom->Get_WorldMatrix()));
		//
		//Desc.parentMatrix = m_pTransformCom->Get_WorldMatrix();
		//Desc.vPos = vPos;
		//
		//m_pGameInstance->Add_CloneObject(eLevel, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Particle_Hit"), &Desc);
	}
}
void CJobMob1::Set_Dead()
{
	//CJobMob1::JobMob1State eHitted = CJobMob1::JobMob1State::Dead;
	//Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
	//m_pTransformCom->Set_State(CTransform::STATE_POSITION, m_pTransformCom->Get_State(CTransform::STATE_POSITION) - 3*m_pTransformCom->Get_State(CTransform::STATE_UP));

}

void CJobMob1::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	Out_Json["LayerTag"] = m_sLayerTag;
	__super::Write_Json(Out_Json);
}

HRESULT CJobMob1::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Navigation */
	CNavigation::NAVI_DESC		NaviDesc = {};
	NaviDesc.iCurrentIndex = 0;

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Navigation"),
		TEXT("Com_Navigation"), reinterpret_cast<CComponent**>(&m_pNavigationCom), &NaviDesc)))
		return E_FAIL;

	/* For.Com_Collider */
	CBounding_Sphere::BOUNDING_SPHERE_DESC  BoundingDesc = {};

	// 	BoundingDesc.vExtents = _float3(0.5f, 0.7f, 0.5f);
	// 	BoundingDesc.vCenter = _float3(0.f, BoundingDesc.vExtents.y, 0.f);
	// 	BoundingDesc.vRotation = _float3(0.f, XMConvertToRadians(45.0f), 0.f);
	BoundingDesc.fRadius = _float(1.f);
	BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius, 0.f);

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
		TEXT("Com_Collider"), reinterpret_cast<CComponent**>(&m_pColliderCom), &BoundingDesc)))
		return E_FAIL;



	return S_OK;
}

HRESULT CJobMob1::Ready_PartObjects()
{
	CJobMob1_Body::BODY_DESC		BodyDesc = {};
	if (FAILED(Add_Body(TEXT("Prototype_GameObject_JobMob1_Body"), BodyDesc)))
		return E_FAIL;


	// 	{
	//  		CJobMob1_Weapon::WEAPON_DESC	WeaponDesc = {};
	//  		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_JobMob1_Weapon"), "ik_hand_l", WeaponDesc, TEXT("Weapon_L"))))
	//  			return E_FAIL;
	// 	}

	{
		CJobMob1_Weapon::WEAPON_DESC	WeaponDesc = {};
		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_JobMob1_Weapon"), "weapon_r", WeaponDesc, TEXT("Weapon_R"))))
			return E_FAIL;
	}

	//CWeapon* m_pWeapon_L = Get_Weapon(TEXT("Weapon_L"));

	CWeapon* m_pWeapon_R = Get_Weapon(TEXT("Weapon_R"));
	m_pWeapon_R->Get_TransformComp()->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180.0f));

	//m_pWeapon_L->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.1f, 0.f, 0.f, 1.f));
	m_pWeapon_R->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(-1.f, 0.f, 0.f, 1.f));



	return S_OK;
}

void CJobMob1::Free()
{
	__super::Free();
}