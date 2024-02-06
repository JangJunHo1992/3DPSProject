#include "stdafx.h"
#include "Covus.h"

#include "GameInstance.h"

#include "Covus_Body.h"
#include "Covus_Weapon.h"
#include "Light.h"
#include "Player_HPBarBase.h"

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
	
	ZeroMemory(&m_LightDesc, sizeof m_LightDesc);

	m_LightDesc.eType = LIGHT_DESC::TYPE_POINT;
	XMStoreFloat4(&m_LightDesc.vPosition, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + _float4(0.f, 1.f, 0.f, 1.f));
	m_LightDesc.fRange = 20.f;
	m_LightDesc.vDiffuse = _float4(0.6f, 0.8f, 1.0f, 1.0f);
	m_LightDesc.vAmbient = _float4(0.2f, 0.2f, 0.2f, 1.f);
	m_LightDesc.vSpecular = m_LightDesc.vDiffuse;

	if (FAILED(m_pGameInstance->Add_Light(m_LightDesc)))
		return E_FAIL;
	m_pLight = m_pGameInstance->Get_Light_Back();

	{
		CPlayer_HPBarBase::Player_HPBarBase_DESC		BackGroundDesc = {};

		BackGroundDesc.fX = 180;
		BackGroundDesc.fY = 650;
		BackGroundDesc.fSizeX = 300;
		BackGroundDesc.fSizeY = 20;
		BackGroundDesc.fRotationPerSec = XMConvertToRadians(90.f);
		BackGroundDesc.fSpeedPerSec = 10.f;
		if (FAILED(m_pGameInstance->Add_CloneObject(m_pGameInstance->Get_NextLevel(), TEXT("Layer_UI"), TEXT("Prototype_GameObject_TexUI_Player_HPBarBase"), &BackGroundDesc)))
			return E_FAIL;
	}

	return S_OK;
}

void CCovus::Priority_Tick(_float fTimeDelta)
{
	
	__super::Priority_Tick(fTimeDelta);
}

void CCovus::Tick(_float fTimeDelta)
{
	if (m_iCurrentLevelIn == 2)
		Collision_Chcek(LEVEL_GAMEPLAY);
	else if (m_iCurrentLevelIn == 6)
		Collision_Chcek(LEVEL_BOSS1);
	else if (m_iCurrentLevelIn == 7)
		Collision_Chcek(LEVEL_BOSS2);

	XMStoreFloat4(&m_LightDesc.vPosition, m_pTransformCom->Get_State(CTransform::STATE_POSITION) + _float4(8.f, 2.f, -5.f, 1.f));
	//_float4 fTemp = m_pTransformCom->Get_Position() + _float4(-5.f, 1.f, -5.f, 1.f);
	m_pLight->Set_Lightpos(m_LightDesc.vPosition);

	__super::Tick(fTimeDelta);
}

void CCovus::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
	if (Get_HasBeenHit() == true)
		++m_iCheckHitTime;

	if (Get_HasBeenHit() == true && m_iCheckHitTime > 10.f)
	{
		Set_HasBeenHit(false);
		m_iCheckHitTime = 0;
	}
}

HRESULT CCovus::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}


_bool CCovus::Collision_Chcek(LEVEL eLevel)//_uint eLevel
{
	_bool bIsCollision = false;

	CCharacter* pAlreadyHittedCharacter = nullptr;
	list<CGameObject*> _Targets = *m_pGameInstance->Get_GameObjects(eLevel, TEXT("Layer_Monster"));
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


void CCovus::Set_Hitted()
{
	if (m_bCheckDead == false &&m_bParry ==false && Get_HasBeenHit() == false)
	{
		CCovus::PlayerState eHitted = CCovus::PlayerState::HurtMFL;
		Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
		PlayerStatus.m_iHP -= 10;
	}
	
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
	BoundingDesc.fRadius = _float(1.f);
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

