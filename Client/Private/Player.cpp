#include "stdafx.h"
#include "..\Public\Player.h"

#include "GameInstance.h"
#include "Weapon_Player.h"
#include "Body_Player.h"


CPlayer::CPlayer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CCharacter_Client(pDevice, pContext)
{

}

CPlayer::CPlayer(const CPlayer& rhs)
	: CCharacter_Client(rhs)
{
}

HRESULT CPlayer::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
	CGameObject::GAMEOBJECT_DESC		GameObjectDesc = {};

	GameObjectDesc.fSpeedPerSec = 10.f;
	GameObjectDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;

	return S_OK;
}

void CPlayer::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CPlayer::Tick(_float fTimeDelta)
{
	CBody_Player* pBody = dynamic_cast<CBody_Player*>(Find_PartObject(TEXT("Part_Body")));
	Safe_AddRef(pBody);

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_pTransformCom->Go_Backward(fTimeDelta);
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta * -1.f);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_pTransformCom->Go_Straight(fTimeDelta, m_pNavigationCom);
		//m_pTransformCom->Go_Straight(fTimeDelta, nullptr);
		pBody->Set_Animation(4, CModel::ANIM_STATE::ANIM_STATE_LOOP);
	}
	else 
	{
		pBody->Set_Animation(3, CModel::ANIM_STATE::ANIM_STATE_LOOP);
	}
		


	Safe_Release(pBody);

	__super::Tick(fTimeDelta);
	//m_pColliderCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CPlayer::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	//if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
	//	return;
}

HRESULT CPlayer::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CPlayer::Set_Hitted()
{
	return;
}

//HRESULT CPlayer::Ready_Components()
//{
//	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
//		return E_FAIL;
//
//	return S_OK;
//}

HRESULT CPlayer::Ready_Components_Origin(LEVEL eLevel)
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

HRESULT CPlayer::Ready_PartObjects()
{
	CBody_Player::BODY_DESC		BodyDesc = {};
	if (FAILED(Add_Body(TEXT("Prototype_GameObject_Body_Player"), BodyDesc)))
		return E_FAIL;

	CWeapon_Player::WEAPON_DESC	WeaponDesc = {};
	if (FAILED(Add_Weapon(TEXT("Prototype_GameObject_Weapon_Player"), "SWORD", WeaponDesc)))
		return E_FAIL;

	return S_OK;
}

//CPlayer* CPlayer::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
//{
//	CPlayer* pInstance = new CPlayer(pDevice, pContext);
//
//	/* 원형객체를 초기화한다.  */
//	if (FAILED(pInstance->Initialize_Prototype()))
//	{
//		MSG_BOX("Failed to Created : CPlayer");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}
//
//CGameObject* CPlayer::Clone(void* pArg)
//{
//	CPlayer* pInstance = new CPlayer(*this);
//
//	/* 원형객체를 초기화한다.  */
//	if (FAILED(pInstance->Initialize(pArg)))
//	{
//		MSG_BOX("Failed to Cloned : CPlayer");
//		Safe_Release(pInstance);
//	}
//	return pInstance;
//}

void CPlayer::Free()
{
	__super::Free();
}

