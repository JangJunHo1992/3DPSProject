#include "stdafx.h"
#include "Raider.h"

#include "GameInstance.h"

#include "Raider_Body.h"
#include "Raider_Weapon.h"



CRaider::CRaider(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCharacter_Client(pDevice, pContext)
{

}

CRaider::CRaider(const CRaider& rhs)
	: CCharacter_Client(rhs)
{
}

HRESULT CRaider::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CRaider::Initialize(void* pArg)
{
	m_sName = "Raider";
	m_sLayerTag = "Layer_Monster";

	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 10.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;

	return S_OK;
}

void CRaider::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CRaider::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CRaider::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CRaider::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CRaider::Set_Hitted()
{
	CRaider::Raider_State eHitted = CRaider::Raider_State::Great_DualBlade_anim_hit01;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

//void CRaider::Write_Json(json& Out_Json)
//{
//	Out_Json["Name"] = m_sName;
//	Out_Json["LayerTag"] = m_sLayerTag;
//	__super::Write_Json(Out_Json);
//}

HRESULT CRaider::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Navigation */
	CNavigation::NAVI_DESC		NaviDesc = {};
	NaviDesc.iCurrentIndex = 0;

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Navigation"),
		TEXT("Com_Navigation"), reinterpret_cast<CComponent**>(&m_pNavigationCom), &NaviDesc)))
		return E_FAIL;

	/* For.Com_Collider */
	CBounding_OBB::BOUNDING_OBB_DESC		BoundingDesc = {};

	BoundingDesc.vExtents = _float3(0.5f, 0.7f, 0.5f);
	BoundingDesc.vCenter = _float3(0.f, BoundingDesc.vExtents.y, 0.f);
	BoundingDesc.vRotation = _float3(0.f, XMConvertToRadians(45.0f), 0.f);

	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Collider_OBB"),
		TEXT("Com_Collider"), reinterpret_cast<CComponent**>(&m_pColliderCom), &BoundingDesc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CRaider::Ready_PartObjects()
{
	CRaider_Body::BODY_DESC		BodyDesc = {};
	if (FAILED(Add_Body(TEXT("Prototype_GameObject_Raider_Body"), BodyDesc)))
		return E_FAIL;


	{
		CRaider_Weapon::WEAPON_DESC	WeaponDesc = {};
		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_Raider_Weapon"), "ik_hand_l", WeaponDesc, TEXT("Weapon_L"))))
			return E_FAIL;
	}

	{
		CRaider_Weapon::WEAPON_DESC	WeaponDesc = {};
		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_Raider_Weapon"), "ik_hand_r", WeaponDesc, TEXT("Weapon_R"))))
			return E_FAIL;
	}

	CWeapon* m_pWeapon_L = Get_Weapon(TEXT("Weapon_L"));
	
	CWeapon* m_pWeapon_R = Get_Weapon(TEXT("Weapon_R"));
	m_pWeapon_R->Get_TransformComp()->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180.0f));

	m_pWeapon_L->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.1f, 0.f, 0.f, 1.f));
	m_pWeapon_R->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(-0.1f, 0.f, 0.f, 1.f));



	return S_OK;
}

void CRaider::Free()
{
	__super::Free();
}

