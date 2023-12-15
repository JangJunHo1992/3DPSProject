#pragma once

#include "Model.h"

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
	_float					m_fDuration = { 0.0f }; /* �� �ִϸ��̼��� ��ü ����ϱ����� ��ü ����. */
	_float					m_fTickPerSecond = { 0.f }; /* �ִϸ��̼��� ��� �ӵ� : m_TickPerSecond * fTimeDelta */
	_float					m_fTrackPosition = { 0.f }; /* ���� ����ǰ� �ִ� ��ġ. */

	_uint					m_iNumChannels = { 0 }; /* �� �ִϸ��̼��� ����ϴ� ���� ����. */
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