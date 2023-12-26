#include "..\Public\Character.h"
#include "..\Public\Model.h"
<<<<<<< HEAD
=======
#include "Transform.h"
>>>>>>> JJH

CCharacter::CCharacter(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CCharacter::CCharacter(const CCharacter& rhs)
	: CGameObject(rhs)
{
}

<<<<<<< HEAD
void CCharacter::Set_Animation(_int _iNextAnimation, CModel::ANIM_STATE _eAnimState, _bool _bIsTransition)
{
	m_pModelCom->Set_Animation(_iNextAnimation, _eAnimState, _bIsTransition);


	/*m_pModelCom->Set_AnimationIndex(_iNextAnimation);

	m_pModelCom->Set_AnimState(_eAnimState);

	if (_bResetAnimation)
	{
		m_pModelCom->Reset_Animation();
	}*/
=======
void CCharacter::Set_Animation(_int _iNextAnimation, CModel::ANIM_STATE _eAnimState, _bool _bIsTransition, _bool _bUseAnimationPos, _uint iTargetKeyFrameIndex)
{
	m_pModelCom->Set_Animation(_iNextAnimation, _eAnimState, _bIsTransition, m_pModelCom->Get_TickPerSecond() / 10.f, iTargetKeyFrameIndex);
	m_pModelCom->Set_UseAnimationPos(_bUseAnimationPos);
	
>>>>>>> JJH
}


_uint CCharacter::Get_CurrentAnimIndex()
{
	return m_pModelCom->Get_CurrentAnimIndex();
}

//void CCharacter::Set_Next_AnimationIndex(_int _iNextAnimIndex)
//{
//	m_pModelCom->Set_Next_AnimationIndex(_iNextAnimIndex);
//}

_uint CCharacter::Get_NumAnimations()
{
	return m_pModelCom->Get_NumAnimations();
}

<<<<<<< HEAD
=======
_float CCharacter::Get_TickPerSecond()
{
	return m_pModelCom->Get_TickPerSecond();
}

_bool CCharacter::Is_Animation_End()
{
	return m_pModelCom->Is_AnimEnd();
}

_bool CCharacter::Is_Inputable_Front(_uint _iIndexFront)
{
	return m_pModelCom->Is_Inputable_Front(_iIndexFront);
}

_bool CCharacter::Is_Inputable_Back(_uint _iIndexBack)
{
	return m_pModelCom->Is_Inputable_Back(_iIndexBack);
}



void CCharacter::Go_Straight(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Straight(fTimeDelta, pNavigation);
}

void CCharacter::Go_Straight_L45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Straight_L45(fTimeDelta, pNavigation);
}

void CCharacter::Go_Straight_R45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Straight_R45(fTimeDelta, pNavigation);
}

void CCharacter::Go_Backward(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Backward(fTimeDelta, pNavigation);
}

void CCharacter::Go_Backward_L45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Backward_L45(fTimeDelta, pNavigation);
}

void CCharacter::Go_Backward_R45(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Backward_R45(fTimeDelta, pNavigation);
}

void CCharacter::Go_Left(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Left(fTimeDelta, pNavigation);
}

void CCharacter::Go_Right(_float fTimeDelta, CNavigation* pNavigation)
{
	m_pTransformCom->Go_Right(fTimeDelta, pNavigation);
}



>>>>>>> JJH
