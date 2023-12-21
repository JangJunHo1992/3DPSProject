#pragma once

#include "GameObject.h"
#include "Model.h"

BEGIN(Engine)

//class CModel;

class ENGINE_DLL CCharacter abstract : public CGameObject
{
protected:
	CCharacter(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	CCharacter(const CCharacter& rhs);
	virtual ~CCharacter() = default;

public:
	void	Set_Animation(_int _iNextAnimation = -1, CModel::ANIM_STATE _eAnimState = CModel::ANIM_STATE::ANIM_STATE_NORMAL, _bool _bIsTransition = true, _bool _bUseAnimationPos = true);
	_uint	Get_CurrentAnimIndex();

	_uint	Get_NumAnimations();
	_float	Get_TickPerSecond();

	_bool	Is_Animation_End();

	void	Go_Straight(_float fTimeDelta);
	void	Go_Backward(_float fTimeDelta);
	void	Go_Left(_float fTimeDelta);
	void	Go_Right(_float fTimeDelta);


protected:
	CModel* m_pModelCom = { nullptr };



};

END