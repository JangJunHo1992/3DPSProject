#include "Character.h"
#include "Model.h"
#include "GameInstance.h"
//#include "Body.h"
//#include "Weapon.h"


CCharacter::CCharacter(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CCharacter::CCharacter(const CCharacter& rhs)
	: CGameObject(rhs)
{
}

HRESULT CCharacter::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CCharacter::Initialize(void* pArg)
{

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	if (FAILED(Ready_PartObjects()))
		return E_FAIL;
	m_iCurrentLevelIn = m_pGameInstance->Get_NextLevel();
	return S_OK;
}

void CCharacter::Priority_Tick(_float fTimeDelta)
{
	__super::Priority_Tick(fTimeDelta);

	for (auto& Pair : m_PartObjects)
	{
		if (nullptr != Pair.second)
			Pair.second->Priority_Tick(fTimeDelta);
	}
}

void CCharacter::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	for (auto& Pair : m_PartObjects)
	{
		if (nullptr != Pair.second)
			Pair.second->Tick(fTimeDelta);
	}

	m_pTransformCom->Add_RootBone_Position(m_pBody->Get_MovePos(), m_pNavigationCom);

	if(nullptr !=m_pColliderCom)
		m_pColliderCom->Update(m_pTransformCom->Get_WorldMatrix());

	Update_RigidBody(fTimeDelta);

// 	if (m_fInvincibleTime > 0.f)
// 	{
// 		m_fInvincibleTime -= fTimeDelta;
// 	}
}

void CCharacter::Late_Tick(_float fTimeDelta)
{
	__super::Late_Tick(fTimeDelta);

	for (auto& Pair : m_PartObjects)
	{
		if (nullptr != Pair.second)
			Pair.second->Late_Tick(fTimeDelta);
	}

	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_NONBLEND, this)))
		return;
#ifdef _DEBUG
	m_pNavigationCom->Render();
	m_pColliderCom->Render();
#endif
}

HRESULT CCharacter::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;



	return S_OK;
}

CGameObject* CCharacter::Find_PartObject(const wstring& strPartTag)
{
	auto	iter = m_PartObjects.find(strPartTag);

	if (iter == m_PartObjects.end())
		return nullptr;

	return iter->second;
}

HRESULT CCharacter::Add_PartObject(const wstring& strPrototypeTag, const wstring& strPartTag, void* pArg)
{
	if (nullptr != Find_PartObject(strPrototypeTag))
		return E_FAIL;

	CGameObject* pPartObject = m_pGameInstance->Clone_Prototype(strPrototypeTag, pArg);
	if (nullptr == pPartObject)
		return E_FAIL;

	m_PartObjects.emplace(strPartTag, pPartObject);

	return S_OK;
}

HRESULT CCharacter::Add_Body(const wstring& strPrototypeTag, CBody::BODY_DESC pArg)
{
	//CBody::BODY_DESC	BodyDesc = pArg;
	pArg.m_pParentTransform = m_pTransformCom;
	if (FAILED(Add_PartObject(strPrototypeTag, TEXT("Part_Body"), &pArg)))
		return E_FAIL;

	m_pBody = Get_Body();
	if (nullptr == m_pBody)
		return E_FAIL;

	Safe_AddRef(m_pBody);

	return S_OK;
}

HRESULT CCharacter::Add_Weapon(const wstring& strPrototypeTag, string strBoneName, CWeapon::WEAPON_DESC pArg, const wstring& strWeaponTag)
{
	if (nullptr == m_pBody)
		return E_FAIL;

	pArg.m_pSocketBone = m_pBody->Get_BonePtr(strBoneName.c_str());
	pArg.m_pParentTransform = m_pTransformCom;

	/* For.Part_Weapon*/
	if (FAILED(Add_PartObject(strPrototypeTag, strWeaponTag, &pArg)))
		return E_FAIL;

	CWeapon* pWeapon = Get_Weapon(strWeaponTag);
	if (nullptr == pWeapon)
		return E_FAIL;

	m_Weapons.push_back(pWeapon);
	Safe_AddRef(pWeapon);

	return S_OK;
}


CBody* CCharacter::Get_Body()
{
	return dynamic_cast<CBody*>(Find_PartObject(TEXT("Part_Body")));
}

CWeapon* CCharacter::Get_Weapon(const wstring& strWeaponTag)
{
	return dynamic_cast<CWeapon*>(Find_PartObject(strWeaponTag));
}

CCollider* CCharacter::Get_Collider()
{
	return m_pColliderCom;
}

CNavigation* CCharacter::Get_Navigation()
{
	return m_pNavigationCom;
}


void CCharacter::Set_Animation(
	_uint _iNextAnimation
	, CModel::ANIM_STATE _eAnimState
	, _bool _bIsTransition
	, _bool _bUseAnimationPos
	, _uint iTargetKeyFrameIndex)
{
	m_pBody->Set_Animation(_iNextAnimation, _eAnimState, _bIsTransition, _bUseAnimationPos, iTargetKeyFrameIndex);
}

_bool CCharacter::Is_Animation_End()
{
	return m_pBody->Is_Animation_End();
}

_bool CCharacter::Is_Inputable_Front(_uint _iIndexFront)
{
	return m_pBody->Is_Inputable_Front(_iIndexFront);
}

_bool CCharacter::Is_Inputable_Back(_uint _iIndexBack)
{
	return m_pBody->Is_Inputable_Back(_iIndexBack);
}

void CCharacter::Go_Straight(_float fTimeDelta)
{
	m_pTransformCom->Go_Straight(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Go_Straight_L45(_float fTimeDelta)
{
	m_pTransformCom->Go_Straight_L45(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Go_Straight_R45(_float fTimeDelta)
{
	m_pTransformCom->Go_Straight_R45(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Go_Backward(_float fTimeDelta)
{
	m_pTransformCom->Go_Backward(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Go_Backward_L45(_float fTimeDelta)
{
	m_pTransformCom->Go_Backward_L45(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Go_Backward_R45(_float fTimeDelta)
{
	m_pTransformCom->Go_Backward_R45(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Go_Left(_float fTimeDelta)
{
	m_pTransformCom->Go_Left(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Go_Right(_float fTimeDelta)
{
	m_pTransformCom->Go_Right(fTimeDelta, m_pNavigationCom);
}

void CCharacter::Knockback(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Knockback(fTimeDelta, pNavigation);
}

void CCharacter::Update_RigidBody(_float fTimeDelta)
{
	if (abs(m_vNetPower.x) > 0.0001 || abs(m_vNetPower.y) > 0.0001 || abs(m_vNetPower.z) > 0.0001)
		m_bIsPowered = true;


	_float3 vMovePos = m_vNetPower * fTimeDelta * 20;
	m_vNetPower -= vMovePos;

	_vector vPos = m_pTransformCom->Get_State(CTransform::STATE::STATE_POSITION);
	_float3 vPosFloat3 = m_pTransformCom->Get_State(CTransform::STATE::STATE_POSITION);
	_float fCellHeight = m_pNavigationCom->Get_CurrentHeight(vPos);

	//{
	//	m_pTransformCom->Set_Position(vPosFloat3 + vMovePos);
	//	return;
	//}


	_float3 vResult = m_vNetPower;

	if (fCellHeight < (vPosFloat3 + m_vNetPower).y)
	{
		if (false == m_bIsJump)
		{
			m_vNetPower.y = 0;
			vResult.y = fCellHeight - vPosFloat3.y;
		}
	}

	else
	{
		vResult.y = fCellHeight - (vPosFloat3 + m_vNetPower).y;
	}

	m_pTransformCom->Move_On_Navigation(vResult, m_pNavigationCom);
}

void CCharacter::Search_Target()
{
	if (nullptr == m_pTargetPlayer)
	{
		CCharacter* pTarget;
		list<CGameObject*>* _ObjectList = m_pGameInstance->Get_GameObjects(m_iCurrentLevelIn, TEXT("Layer_Player"));

		if (nullptr == _ObjectList)
			return;

		for (CGameObject* pObject : *_ObjectList)
		{
			pTarget = dynamic_cast<CCharacter*>(pObject);
			if (nullptr == pTarget)
				continue;

			m_pTargetPlayer = pTarget;
			Safe_AddRef(m_pTargetPlayer);
			break;
		}

	}

}

_float CCharacter::Calc_Distance(CCharacter* pTarget)
{
	if (nullptr == pTarget)
		return 1000000.f;

	_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float3 vTargetPos = pTarget->m_pTransformCom->Get_State(CTransform::STATE_POSITION);

	_float3 vDiff = vTargetPos - vPos;

	return sqrt(vDiff.x * vDiff.x + vDiff.y * vDiff.y + vDiff.z * vDiff.z);

}

_float CCharacter::Calc_Distance()
{
	return Calc_Distance(m_pTargetPlayer);
}

void CCharacter::Look_At_Target()
{
	if (nullptr == m_pTargetPlayer)
		return;

	_fvector vTargetPos = m_pTargetPlayer->m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	m_pTransformCom->Look_At_OnLand(vTargetPos);
}


_float4 CCharacter::Get_Pos4()
{
	return m_pTransformCom->Get_Position();
}


void CCharacter::Free()
{
	__super::Free();

	for (auto& Pair : m_PartObjects)
		Safe_Release(Pair.second);
	m_PartObjects.clear();

	Safe_Release(m_pColliderCom);
	Safe_Release(m_pNavigationCom);

	Safe_Release(m_pBody);
	for (CWeapon* pWeapon : m_Weapons) 
	{
		Safe_Release(pWeapon);
	}
	m_Weapons.clear();
}










