#include "..\Public\Animation.h"
#include "Channel.h"

CAnimation::CAnimation()
{
}

CAnimation::CAnimation(const CAnimation& rhs)
	: m_fDuration(rhs.m_fDuration)
	, m_fTickPerSecond(rhs.m_fTickPerSecond)
	, m_fTrackPosition(rhs.m_fTrackPosition)
	, m_iNumChannels(rhs.m_iNumChannels)
	, m_Channels(rhs.m_Channels)
	, m_isFinished(rhs.m_isFinished)
	, m_CurrentKeyFrames(rhs.m_CurrentKeyFrames)
{
	strcpy_s(m_szName, rhs.m_szName);

	for (auto& pChannel : m_Channels)
		Safe_AddRef(pChannel);
}

HRESULT CAnimation::Initialize(const aiAnimation* pAIAnimation, const CModel::BONES& Bones)
{
	strcpy_s(m_szName, pAIAnimation->mName.data);

	m_fDuration = (_float)pAIAnimation->mDuration;
	m_fTickPerSecond = (_float)pAIAnimation->mTicksPerSecond;

	m_iNumChannels = pAIAnimation->mNumChannels;

	m_CurrentKeyFrames.resize(m_iNumChannels);

	/* 이 애니메이션에서 사용하기위한 뼈(aiNodeAnim,채널)의 정보를 만든다. */
	for (size_t i = 0; i < m_iNumChannels; i++)
	{
		CChannel* pChannel = CChannel::Create(pAIAnimation->mChannels[i], Bones);
		if (nullptr == pChannel)
			return E_FAIL;

		m_Channels.push_back(pChannel);
	}

	return S_OK;
}

_bool CAnimation::Invalidate_TransformationMatrix(CModel::ANIM_STATE _eAnimState, _float fTimeDelta, const CModel::BONES& Bones)
{
	m_fTrackPosition += m_fTickPerSecond * fTimeDelta;

	if (m_bIsTransition)
	{
		if (m_fTransitionDuration <= m_fTrackPosition) 
		{
			//m_isFinished = true;
			m_bIsTransition = false;
			m_fTrackPosition = m_fTransitionDuration;
		}
	}
	else 
	{
		switch (_eAnimState)
		{
		case Engine::CModel::ANIM_STATE_NORMAL:
			if (m_fTrackPosition >= m_fDuration)
			{
				m_isFinished = true;
				m_fTrackPosition = m_fDuration;
			}

			break;
		case Engine::CModel::ANIM_STATE_LOOP:
			if (m_fTrackPosition >= m_fDuration)
			{
				m_fTrackPosition = 0.0f;
			}
			break;
		case Engine::CModel::ANIM_STATE_REVERSE:
			break;
		case Engine::CModel::ANIM_STATE_STOP:
			break;
		default:
			break;
		}
	}
		


	/* 내 애니메이션이 이용하는 전체 뼈의 상태를 m_fTrackPosition 시간에 맞는 상태로 갱신하다.*/
	for (size_t i = 0; i < m_iNumChannels; i++)
	{
		m_Channels[i]->Invalidate_TransformationMatrix(m_fTrackPosition, Bones, &m_CurrentKeyFrames[i]);
	}

	return m_isFinished;
}

void CAnimation::Reset_Animation(const CModel::BONES& Bones)
{
	m_fTransitionDuration = 0.0f;
	m_fTrackPosition = 0.0f; 
	m_isFinished = false;

	for (size_t i = 0; i < m_iNumChannels; i++)
	{
		m_Channels[i]->Reset_Channel(m_fTrackPosition, Bones, &m_CurrentKeyFrames[i]);
	}

}

CChannel* CAnimation::Get_Channel_By_BoneIndex(_uint _iBoneIndex)
{
	for (CChannel* pChannel : m_Channels) 
	{
		if (_iBoneIndex == pChannel->Get_BoneIndex()) 
		{
			return pChannel;
		}
	}
	return nullptr;
}


CAnimation* CAnimation::Create(const aiAnimation* pAIAnimation, const CModel::BONES& Bones)
{
	CAnimation* pInstance = new CAnimation();

	if (FAILED(pInstance->Initialize(pAIAnimation, Bones)))
	{
		MSG_BOX("Failed to Created : CAnimation");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CAnimation* CAnimation::Clone()
{
	return new CAnimation(*this);
}



void CAnimation::Free()
{
	for (auto& pChannel : m_Channels)
		Safe_Release(pChannel);

	m_Channels.clear();
}