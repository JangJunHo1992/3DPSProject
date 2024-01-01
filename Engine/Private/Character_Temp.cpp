#include "..\Public\Character_Temp.h"
#include "..\Public\Model.h"
#include "Transform.h"

CCharacter_Temp::CCharacter_Temp(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CCharacter_Temp::CCharacter_Temp(const CCharacter_Temp& rhs)
	: CGameObject(rhs)
{
}

void CCharacter_Temp::Set_Animation(_uint _iNextAnimation, CModel::ANIM_STATE _eAnimState, _bool _bIsTransition, _bool _bUseAnimationPos, _uint iTargetKeyFrameIndex)
{
	m_pModelCom->Set_Animation(_iNextAnimation, _eAnimState, _bIsTransition, m_pModelCom->Get_TickPerSecond() / 10.f, iTargetKeyFrameIndex);
	m_pModelCom->Set_UseAnimationPos(_bUseAnimationPos);
	
}


_uint CCharacter_Temp::Get_CurrentAnimIndex()
{
	return m_pModelCom->Get_CurrentAnimIndex();
}

//void CCharacter_Temp::Set_Next_AnimationIndex(_int _iNextAnimIndex)
//{
//	m_pModelCom->Set_Next_AnimationIndex(_iNextAnimIndex);
//}

_uint CCharacter_Temp::Get_NumAnimations()
{
	return m_pModelCom->Get_NumAnimations();
}

_float CCharacter_Temp::Get_TickPerSecond()
{
	return m_pModelCom->Get_TickPerSecond();
}

_bool CCharacter_Temp::Is_Animation_End()
{
	return m_pModelCom->Is_AnimEnd();
}

_bool CCharacter_Temp::Is_Inputable_Front(_uint _iIndexFront)
{
	return m_pModelCom->Is_Inputable_Front(_iIndexFront);
}

_bool CCharacter_Temp::Is_Inputable_Back(_uint _iIndexBack)
{
	return m_pModelCom->Is_Inputable_Back(_iIndexBack);
}



void CCharacter_Temp::Go_Straight(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Straight(fTimeDelta, pNavigation);
}

void CCharacter_Temp::Go_Straight_L45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Straight_L45(fTimeDelta, pNavigation);
}

void CCharacter_Temp::Go_Straight_R45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Straight_R45(fTimeDelta, pNavigation);
}

void CCharacter_Temp::Go_Backward(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Backward(fTimeDelta, pNavigation);
}

void CCharacter_Temp::Go_Backward_L45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Backward_L45(fTimeDelta, pNavigation);
}

void CCharacter_Temp::Go_Backward_R45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Backward_R45(fTimeDelta, pNavigation);
}

void CCharacter_Temp::Go_Left(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Left(fTimeDelta, pNavigation);
}

void CCharacter_Temp::Go_Right(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Right(fTimeDelta, pNavigation);
}



