#include "..\Public\Character.h"
#include "..\Public\Model.h"

CCharacter::CCharacter(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{
}

CCharacter::CCharacter(const CCharacter& rhs)
	: CGameObject(rhs)
{
}

void CCharacter::Set_Animation(_int _iNextAnimation, CModel::ANIM_STATE _eAnimState, _bool _bIsTransition)
{
	m_pModelCom->Set_Animation(_iNextAnimation, _eAnimState, _bIsTransition);


	/*m_pModelCom->Set_AnimationIndex(_iNextAnimation);

	m_pModelCom->Set_AnimState(_eAnimState);

	if (_bResetAnimation)
	{
		m_pModelCom->Reset_Animation();
	}*/
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

