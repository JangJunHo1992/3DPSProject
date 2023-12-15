#pragma once

#include "Model.h"

/* 특정 애니메이션(대기, 걷기, 뛰기, 때리기, 맞기) 을 표현하기위한 데이터들을 가진다. */

BEGIN(Engine)

class CChannel;
class CModel;

class CAnimation final : public CBase
{
private:
	CAnimation();
	CAnimation(const CAnimation& rhs);
	virtual ~CAnimation() = default;

public:
	HRESULT Initialize(const aiAnimation* pAIAnimation, const CModel::BONES& Bones);
	_bool Invalidate_TransformationMatrix(CModel::ANIM_STATE _eAnimState, _float fTimeDelta, const CModel::BONES& Bones);

public:
	vector<class CChannel*>* Get_Channels() { return &m_Channels; };
	CChannel* Get_Channel_By_BoneIndex(_uint _iBoneIndex);
	_float	Get_TrackPosition() { return m_fTrackPosition; };
	void	Set_TrackPosition(_float* _fTrackPosition) { m_fTrackPosition = *_fTrackPosition; };

	void	Set_Duration(_float _fDuration) { m_fDuration = _fDuration; };

	void	Set_TransitionDuration(_float* _fTransitionDuration) { m_fTransitionDuration = *_fTransitionDuration; };
	void	Set_IsTransition_True() { m_bIsTransition = true; };

	void	Reset_Animation(const CModel::BONES& Bones);

private:
	_char					m_szName[MAX_PATH] = "";
	_float					m_fDuration = { 0.0f }; /* 내 애니메이션을 전체 재생하기위한 전체 길이. */
	_float					m_fTickPerSecond = { 0.f }; /* 애니메이션의 재생 속도 : m_TickPerSecond * fTimeDelta */
	_float					m_fTrackPosition = { 0.f }; /* 현재 재생되고 있는 위치. */

	_uint					m_iNumChannels = { 0 }; /* 이 애니메이션이 사용하는 뼈의 갯수. */
	vector<class CChannel*>	m_Channels;

	vector<_uint>			m_CurrentKeyFrames;
	_bool					m_isFinished = { false };
	
	_bool					m_bIsTransition = { false };
	_float					m_fTransitionDuration = { 0.f };

public:
	static CAnimation* Create(const aiAnimation* pAIAnimation, const CModel::BONES& Bones);
	CAnimation* Clone();
	virtual void Free() override;
};

END


//void	Set_Channel_Animation_Transition(_ushort iChannelIndex, KEYFRAME keyFrame);

//_bool	Get_IsFinished()	{ return m_isFinished; }

//_bool	Get_IsTransitionDuration_End() { return m_fTrackPosition >= m_fTransitionDuration; };

//_float	Get_TransitionDuration() { return m_fTransitionDuration; };