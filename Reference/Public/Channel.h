#pragma once

#include "Model.h"

/* 이 애니메이션에서 사용하는 뼈의 정보다. */
/* 시간대에 따른 뼈의 상태(Scale, Rotation, Position)를 저장한다.*/

BEGIN(Engine)

class CChannel final : public CBase
{
private:
	CChannel();
	virtual ~CChannel() = default;

public:
	HRESULT Initialize(const aiNodeAnim* pChannel, const CModel::BONES& Bones);
	void	Invalidate_TransformationMatrix(_float fCurrentTrackPosition, const CModel::BONES& Bones, _uint* pCurrentKeyFrameIndex);
	void	Invalidate_TransformationMatrix_Normal(_float fCurrentTrackPosition, const CModel::BONES& Bones, _uint* pCurrentKeyFrameIndex);
	void	Invalidate_TransformationMatrix_Transition(_float fCurrentTrackPosition, const CModel::BONES& Bones);

public:
	//void		Set_AnimationTransition(_float _fCurrentTrackPosition, KEYFRAME _EndFrame);
	_uint		Get_BoneIndex() { return m_iBoneIndex; };
	KEYFRAME	Get_First_KeyFrame() { return m_KeyFrames[0]; };
	void		Reset_Channel(_float fCurrentTrackPosition, const CModel::BONES& Bones, _uint* pCurrentKeyFrameIndex);

public:
	_bool	Update_KeyFrame(_float fCurrentTrackPosition, _uint* pCurrentKeyFrameIndex);
	_float	Calc_Ratio(_float fCurrentTrackPosition);
	void	Calc_Now_Transform(_vector& vScale, _vector& vRotation, _vector& vPosition, _float fRatio);
	_matrix	Make_TransformationMatrix(_float fRatio);
	_matrix Make_EndFrame_TransformationMatrix();

	KEYFRAME Make_NowFrame(_float fCurrentTrackPosition);
	void	Set_Transition(KEYFRAME _StartFrame, KEYFRAME _EndFrame, _float* _fTransitionDuration);

	

private:
	_char				m_szName[MAX_PATH] = "";
	_uint				m_iNumKeyFrames = { 0 };
	vector<KEYFRAME>	m_KeyFrames;
	//_uint				m_iCurrentKeyFrameIndex = { 0 };
	_uint				m_iBoneIndex = { 0 };

	_bool				m_bTransition = false;
	KEYFRAME			m_StartFrame;
	KEYFRAME			m_EndFrame;

	//_float				m_fCurrentTrackPosition = { 0.0f };

	

public:
	static CChannel* Create(const aiNodeAnim* pChannel, const CModel::BONES& Bones);
	virtual void Free() override;
};

END