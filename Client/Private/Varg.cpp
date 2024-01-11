#include "stdafx.h"
#include "Varg.h"
#include "GameInstance.h"

#include "Varg_Body.h"
#include "Varg_Weapon.h"

CVarg::CVarg(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCharacter_Client(pDevice, pContext)
{

}

CVarg::CVarg(const CVarg& rhs)
	: CCharacter_Client(rhs)
{
}

HRESULT CVarg::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVarg::Initialize(void* pArg)
{
	m_sName = "Varg";
	m_sLayerTag = "Layer_Monster";

	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 10.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;

	return S_OK;
}

void CVarg::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CVarg::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
}

void CVarg::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);
}

HRESULT CVarg::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CVarg::Set_Hitted()
{
	CVarg::VargState eHitted = CVarg::VargState::HurtF;
	Set_Animation(eHitted, CModel::ANIM_STATE::ANIM_STATE_NORMAL, true);
}

//void CVarg::Write_Json(json& Out_Json)
//{
//	Out_Json["Name"] = m_sName;
//	Out_Json["LayerTag"] = m_sLayerTag;
//	__super::Write_Json(Out_Json);
//}

HRESULT CVarg::Ready_Components_Origin(LEVEL eLevel)
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

HRESULT CVarg::Ready_PartObjects()
{
	CVarg_Body::BODY_DESC		BodyDesc = {};
	if (FAILED(Add_Body(TEXT("Prototype_GameObject_Varg_Body"), BodyDesc)))
		return E_FAIL;


// 	{
//  		CVarg_Weapon::WEAPON_DESC	WeaponDesc = {};
//  		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_Varg_Weapon"), "ik_hand_l", WeaponDesc, TEXT("Weapon_L"))))
//  			return E_FAIL;
// 	}

	{
		CVarg_Weapon::WEAPON_DESC	WeaponDesc = {};
		if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_Varg_Weapon"), "weapon_r", WeaponDesc, TEXT("Weapon_R"))))
			return E_FAIL;
	}

	//CWeapon* m_pWeapon_L = Get_Weapon(TEXT("Weapon_L"));

	CWeapon* m_pWeapon_R = Get_Weapon(TEXT("Weapon_R"));
	m_pWeapon_R->Get_TransformComp()->Rotation(XMVectorSet(0.f, 1.f, 0.f, 0.f), XMConvertToRadians(180.0f));

	//m_pWeapon_L->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.1f, 0.f, 0.f, 1.f));
	m_pWeapon_R->Get_TransformComp()->Set_State(CTransform::STATE_POSITION, XMVectorSet(0.f, 0.f, 0.f, 1.f));



	return S_OK;
}

void CVarg::Free()
{
	__super::Free();
}