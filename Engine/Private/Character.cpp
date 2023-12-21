#include "..\Public\Character.h"
#include "..\Public\Model.h"
#include "Transform.h"

CCharacter::CCharacter(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CCharacter::CCharacter(const CCharacter& rhs)
	: CGameObject(rhs)
{
}

void CCharacter::Set_Animation(_int _iNextAnimation, CModel::ANIM_STATE _eAnimState, _bool _bIsTransition, _bool _bUseAnimationPos)
{
	m_pModelCom->Set_Animation(_iNextAnimation, _eAnimState, _bIsTransition, m_pModelCom->Get_TickPerSecond() / 10.f);
	m_pModelCom->Set_UseAnimationPos(_bUseAnimationPos);
	
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

_float CCharacter::Get_TickPerSecond()
{
	return m_pModelCom->Get_TickPerSecond();
}

_bool CCharacter::Is_Animation_End()
{
	return m_pModelCom->Is_AnimEnd();
}

void CCharacter::Go_Straight(_float fTimeDelta)
{
	m_pTransformCom->Go_Straight(fTimeDelta, nullptr);
}

void CCharacter::Go_Backward(_float fTimeDelta)
{
	m_pTransformCom->Go_Backward(fTimeDelta);
}

void CCharacter::Go_Left(_float fTimeDelta)
{
}

void CCharacter::Go_Right(_float fTimeDelta)
{
}


