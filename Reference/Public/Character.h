#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CModel;

class ENGINE_DLL CCharacter abstract : public CGameObject
{
protected:
	CCharacter(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCharacter(const CCharacter& rhs);
	virtual ~CCharacter() = default;



public:
	void	Set_Animation(_int _iNextAnimation = -1, CModel::ANIM_STATE _eAnimState = CModel::ANIM_STATE::ANIM_STATE_NORMAL, _bool _bIsTransition = true);
	void	Test_Animation();
	_uint	Get_CurrentAnimIndex();
	void	Set_Next_AnimationIndex(_int _iNextAnimIndex);
	
	_uint	Get_NumAnimations();

protected:
	CModel* m_pModelCom = { nullptr };
};

END