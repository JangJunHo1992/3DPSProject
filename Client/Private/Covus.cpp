#include "stdafx.h"
#include "Covus.h"

#include "GameInstance.h"

#include "Covus_Body.h"
#include "Covus_Weapon.h"



CCovus::CCovus(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCharacter_Client(pDevice, pContext)
{

}

CCovus::CCovus(const CCovus& rhs)
	: CCharacter_Client(rhs)
{

}

HRESULT CCovus::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCovus::Initialize(void* pArg)
{
	m_sName = "Covus";
	m_sLayerTag = "Layer_Player";

	
	PlayerStatus.m_iHP = 150;
	PlayerStatus.m_iAttack = 10;


	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 8.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;
	if(m_iCurrentLevelIn==2)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(90.f, -3.5f, 0.f, 1.f));
	else if (m_iCurrentLevelIn == 6)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(10.f, 0.f, 0.f, 1.f));
	else if (m_iCurrentLevelIn == 7)
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));
	return S_OK;
}

void CCovus::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CCovus::Tick(_float fTimeDelta)
{
	Collision_Chcek();
	__super::Tick(fTimeDelta);
}

void CCovus::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CCovus::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}


_bool CCovus::Collision_Chcek()//_uint eLevel
{
	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;
	_uint eLevel = m_pGameInstance->Get_NextLevel();
	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(LEVEL_GAMEPLAY, TEXT("Layer_Monster"));
	for (CGameObject* pGameObject : _Targets)
	{
		CCharacter* pTarget = dynamic_cast<CCharacter*>(pGameObject);
		if (pTarget)
		{
			CCollider* pTargetCollider = pTarget->Get_Collider();
			if (nullptr == pTargetCollider)
				continue;

			_bool isCollision = m_pColliderCom->Collision(pTargetCollider);
			if (isCollision)
			{
				_float3 position = m_pTransformCom->Get_Position();
				_float3 otherposition = pTarget->Get_TransformComp()->Get_Position();
// 				_vector overlap = XMLoadFloat3(&position) - XMLoadFloat3(&otherposition);
// 				_vector minOverlap = XMVectorMin(overlap, XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
//  				_float3 minOverlapValues;
// 				XMStoreFloat3(&minOverlapValues, minOverlap);
				XMVECTOR overlap = XMLoadFloat3(&position) - XMLoadFloat3(&otherposition);

				// 각 성분별 최솟값 계산
				XMVECTOR minOverlap = XMVectorMin(overlap, XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));

				XMFLOAT3 minOverlapValues;
				XMStoreFloat3(&minOverlapValues, minOverlap);

				// 수동으로 변수 정의
				float minX = minOverlapValues.x;
				float minY = minOverlapValues.y;
				float minZ = minOverlapValues.z;

				float minOverlapValue = min(min( minX, minY), minZ );

				if (minOverlapValue > 0) {
					// 겹친 부분이 있는 경우
					if (minOverlapValue == minX) {
						position.x += minOverlapValue / 2.0f;
						otherposition.x -= minOverlapValue / 2.0f;
					}
					else if (minOverlapValue == minY) {
						position.y += minOverlapValue / 2.0f;
						otherposition.y -= minOverlapValue / 2.0f;
					}
					else {
						position.z += minOverlapValue / 2.0f;
						otherposition.z -= minOverlapValue / 2.0f;
					}
				}
				break;
			}
			
		}
	}


	return bIsCollision;
}


void CCovus::Set_Hitted()
{
	CCovus::PlayerState eHitted = CCovus::PlayerState::HurtMFL;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

void CCovus::Set_Dead()
{
}

void CCovus::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	Out_Json["LayerTag"] = m_sLayerTag;
	__super::Write_Json(Out_Json);
}

HRESULT CCovus::Ready_Components_Origin(LEVEL eLevel)
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
	BoundingDesc.fRadius = _float(0.7f);
	BoundingDesc.vCenter = _float3(0.f, BoundingDesc.fRadius, 0.f);

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_Sphere"),
		TEXT("Com_Collider"), reinterpret_cast<CComponent**>(&m_pColliderCom), &BoundingDesc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CCovus::Ready_PartObjects()
{
	CCovus_Body::BODY_DESC		BodyDesc = {};
	if (FAILED(Add_Body(TEXT("Prototype_GameObject_Covus_Body"), BodyDesc)))
		return E_FAIL;


	{
		CCovus_Weapon::WEAPON_DESC	WeaponDesc = {};
		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_Covus_Weapon_Dagger"), "ik_hand_l", WeaponDesc, TEXT("Weapon_L"))))
			return E_FAIL;
	}
	
	{
		CCovus_Weapon::WEAPON_DESC	WeaponDesc = {};
		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_Covus_Weapon_Saber"), "ik_hand_r", WeaponDesc, TEXT("Weapon_R"))))
			return E_FAIL;
	}

	CWeapon* m_pWeapon_L = Get_Weapon(TEXT("Weapon_L"));

	CWeapon* m_pWeapon_R = Get_Weapon(TEXT("Weapon_R"));
	//m_pWeapon_R->Get_TransformComp()->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180.0f));

	m_pWeapon_L->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.1f, 0.f, 0.f, 1.f));
	m_pWeapon_R->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(-0.1f, 0.f, 0.f, 1.f));



	return S_OK;
}

void CCovus::Free()
{
	__super::Free();
}

