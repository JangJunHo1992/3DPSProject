#include "stdafx.h"
#include "JobMob2.h"
#include "GameInstance.h"

#include "JobMob2_Body.h"
#include "JobMob2_Weapon.h"

CJobMob2::CJobMob2(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCharacter_Client(pDevice, pContext)
{

}

CJobMob2::CJobMob2(const CJobMob2& rhs)
	: CCharacter_Client(rhs)
{
}

HRESULT CJobMob2::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CJobMob2::Initialize(void* pArg)
{
	m_sName = "JobMob2";
	m_sLayerTag = "Layer_Monster";

	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 10.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(-20.f, 0.f, 10.f, 1.f));

	return S_OK;
}

void CJobMob2::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CJobMob2::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CJobMob2::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CJobMob2::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CJobMob2::Set_Hitted()
{
	CJobMob2::JobMob2State eHitted = CJobMob2::JobMob2State::HrutS_FL;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

void CJobMob2::Write_Json(json& Out_Json)
{
	Out_Json["Name"] = m_sName;
	Out_Json["LayerTag"] = m_sLayerTag;
	__super::Write_Json(Out_Json);
}

HRESULT CJobMob2::Ready_Components_Origin(LEVEL eLevel)
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

HRESULT CJobMob2::Ready_PartObjects()
{
	CJobMob2_Body::BODY_DESC		BodyDesc = {};
	if (FAILED(Add_Body(TEXT("Prototype_GameObject_JobMob2_Body"), BodyDesc)))
		return E_FAIL;


	// 	{
	//  		CJobMob2_Weapon::WEAPON_DESC	WeaponDesc = {};
	//  		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_JobMob2_Weapon"), "ik_hand_l", WeaponDesc, TEXT("Weapon_L"))))
	//  			return E_FAIL;
	// 	}

	{
		CJobMob2_Weapon::WEAPON_DESC	WeaponDesc = {};
		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_JobMob2_Weapon"), "weapon_r", WeaponDesc, TEXT("Weapon_R"))))
			return E_FAIL;
	}

	//CWeapon* m_pWeapon_L = Get_Weapon(TEXT("Weapon_L"));

	CWeapon* m_pWeapon_R = Get_Weapon(TEXT("Weapon_R"));
	m_pWeapon_R->Get_TransformComp()->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180.0f));

	//m_pWeapon_L->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.1f, 0.f, 0.f, 1.f));
	m_pWeapon_R->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));



	return S_OK;
}

void CJobMob2::Free()
{
	__super::Free();
}