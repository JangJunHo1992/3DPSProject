#include "..\Public\King_GamePlay.h"

#include "GameInstance.h"
#include "TwoHandedHammerSet_Idle.h"
#include "TwoHandedHammerSet_Knockdown02.h"
#include "TwoHandedHammerSet_Hit_Body_Front.h"
#include "TwoHandedHammerSet_Rise01.h"


CKing_GamePlay::CKing_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CKing(pDevice, pContext)
{
}

CKing_GamePlay::CKing_GamePlay(const CKing_GamePlay& rhs)
	: CKing(rhs)
{
}


HRESULT CKing_GamePlay::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CKing_GamePlay::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(-10.f, 0.f, 20.f, 1.f));

	m_pActor = new CActor<CKing_GamePlay>(this);
	m_pActor->Set_State(new CTwoHandedHammerSet_Idle());

	return S_OK;
}

void CKing_GamePlay::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);
}

void CKing_GamePlay::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	m_pActor->Update_State(fTimeDelta);
}

void CKing_GamePlay::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);


	//CCollider* pTargetCollider = dynamic_cast<CCollider*>(m_pGameInstance->Get_Component(LEVEL_GAMEPLAY, TEXT("Layer_Player"), TEXT("Com_Collider")));

	//_bool bIsCollision = m_pColliderCom->Collision(pTargetCollider);

	//if (bIsCollision)
	//{
	//	m_pActor->Set_State(new CTwoHandedHammerSet_Knockdown02());
	//}
}

HRESULT CKing_GamePlay::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

void CKing_GamePlay::Set_Hitted()
{
	CKing::King_State eHitted = CKing::King_State::TwoHandedHammerSet_Hit_Body_Front;
	m_pActor->Set_State(new CTwoHandedHammerSet_Hit_Body_Front());
}

HRESULT CKing_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	return S_OK;
}


CKing_GamePlay* CKing_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CKing_GamePlay* pInstance = new CKing_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CKing_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CKing_GamePlay* CKing_GamePlay::Clone(void* pArg)
{
	CKing_GamePlay* pInstance = new CKing_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CKing_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CKing_GamePlay::Free()
{
	__super::Free();
	Safe_Delete(m_pActor);
}
