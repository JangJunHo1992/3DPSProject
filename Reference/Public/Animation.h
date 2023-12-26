#pragma once

#include "Model.h"
#include "MyAIAnimation.h"

/* Ư�� �ִϸ��̼�(���, �ȱ�, �ٱ�, ������, �±�) �� ǥ���ϱ����� �����͵��� ������. */

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
<<<<<<< HEAD
	HRESULT Initialize(const aiAnimation* pAIAnimation, const CModel::BONES& Bones);
=======
	HRESULT Initialize(CMyAIAnimation pAIAnimation, const CModel::BONES& Bones);
>>>>>>> JJH
	_bool Invalidate_TransformationMatrix(CModel::ANIM_STATE _eAnimState, _float fTimeDelta, const CModel::BONES& Bones);

public:
	vector<class CChannel*>* Get_Channels() { return &m_Channels; };
<<<<<<< HEAD
	CChannel* Get_Channel_By_BoneIndex(_uint _iBoneIndex);
	_float	Get_TrackPosition() { return m_fTrackPosition; };
	void	Set_TrackPosition(_float* _fTrackPosition) { m_fTrackPosition = *_fTrackPosition; };

	void	Set_Duration(_float _fDuration) { m_fDuration = _fDuration; };

	void	Set_TransitionDuration(_float* _fTransitionDuration) { m_fTransitionDuration = *_fTransitionDuration; };
	void	Set_IsTransition_True() { m_bIsTransition = true; };

	void	Reset_Animation(const CModel::BONES& Bones);
=======
	CChannel* Get_Channel_By_BoneIndex(_uint _iBoneIndex, _uint& _iChannelIndex);
	void	Reset_Animation(const CModel::BONES& Bones);

	_float	Get_TrackPosition() { return m_fTrackPosition; };
	void	Set_TrackPosition_End() { m_fTrackPosition = m_fDuration; };


	void	Set_Transition(CAnimation* prevAnimation, _float _fTransitionDuration = 0.2f, _uint iTargetKeyFrameIndex = 0);
	_bool	Is_Transition_End() { return m_fTransitionEnd <= m_fTrackPosition; }
	_bool	Is_Transition() { return m_bIsTransition; }

	KEYFRAME Make_NowFrame(_uint m_iChannelIndex);

	void	Reset_TransitionKeyFrame() {
		m_StartTransitionKeyFrame.clear();
		m_EndTransitionKeyFrame.clear();
	};

	void	Get_TransitionKeyFrame_By_ChannelIndex(KEYFRAME& _StartKeyFrame, KEYFRAME& _EndKeyFrame, _uint _iChannelIndex) 
	{
		_StartKeyFrame = m_StartTransitionKeyFrame[_iChannelIndex];
		_EndKeyFrame = m_EndTransitionKeyFrame[_iChannelIndex];
	};

	_float3 Get_PrevPos() {
		return m_PrevPos;
	}

	void	Set_PrevPos(_float3 _PrevPos) { 
		m_PrevPos = _PrevPos; 
	}

	_float	Get_TickPerSecond() { 
		return m_fTickPerSecond; 
	}

	_bool	Is_TransitionEnd_Now() {
		return m_bIsTransitionEnd_Now;
	}

	//_bool	Is_Inputable();
	_bool	Is_Inputable_Front(_uint _iIndexFront);
	_bool	Is_Inputable_Back(_uint _iIndexBack);

>>>>>>> JJH

private:
	_char					m_szName[MAX_PATH] = "";
	_float					m_fDuration = { 0.0f }; /* �� �ִϸ��̼��� ��ü ����ϱ����� ��ü ����. */
	_float					m_fTickPerSecond = { 0.f }; /* �ִϸ��̼��� ��� �ӵ� : m_TickPerSecond * fTimeDelta */
	_float					m_fTrackPosition = { 0.f }; /* ���� ����ǰ� �ִ� ��ġ. */

	_uint					m_iNumChannels = { 0 }; /* �� �ִϸ��̼��� ����ϴ� ���� ����. */
	vector<class CChannel*>	m_Channels;

	vector<_uint>			m_CurrentKeyFrames;
	_bool					m_isFinished = { false };
	
	_bool					m_bIsTransition = { false };
<<<<<<< HEAD
	_float					m_fTransitionDuration = { 0.f };
=======
	_bool					m_bIsTransitionEnd_Now = { false };

	_float					m_fTransitionEnd = { 0.f };

	vector<KEYFRAME>		m_StartTransitionKeyFrame;
	vector<KEYFRAME>		m_EndTransitionKeyFrame;

	_float3					m_PrevPos = { 0.f, 0.f, 0.f };

>>>>>>> JJH

public:
	static CAnimation* Create(CMyAIAnimation pAIAnimation, const CModel::BONES& Bones);
	CAnimation* Clone();
	virtual void Free() override;
};

END
<<<<<<< HEAD


//void	Set_Channel_Animation_Transition(_ushort iChannelIndex, KEYFRAME keyFrame);

//_bool	Get_IsFinished()	{ return m_isFinished; }

//_bool	Get_IsTransitionDuration_End() { return m_fTrackPosition >= m_fTransitionDuration; };

//_float	Get_TransitionDuration() { return m_fTransitionDuration; };
=======
>>>>>>> JJH
