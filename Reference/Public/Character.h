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
	void	Set_Animation(_int _iNextAnimation = -1, CModel::ANIM_STATE _eAnimState = CModel::ANIM_STATE::ANIM_STATE_NORMAL, _bool _bIsTransition = true, _bool _bUseAnimationPos = true, _uint iTargetKeyFrameIndex = 0);
	_uint	Get_CurrentAnimIndex();

	_uint	Get_NumAnimations();
	_float	Get_TickPerSecond();

	_bool	Is_Animation_End();
	_bool	Is_Inputable_Front(_uint _iIndexFront);
	_bool	Is_Inputable_Back(_uint _iIndexBack);

	void Go_Straight(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Straight_L45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Straight_R45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Backward(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Backward_L45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Backward_R45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Left(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Right(_float fTimeDelta, class CNavigation* pNavigation = nullptr);


protected:
	CModel* m_pModelCom = { nullptr };



};

END