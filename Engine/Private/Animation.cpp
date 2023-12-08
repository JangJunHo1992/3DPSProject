#include "Animation.h"
#include "Channel.h"

CAnimation::CAnimation()
{
}

HRESULT CAnimation::Initialize(const aiAnimation* pAIAnimation, const CModel::BONES& Bones)
{
	strcpy_s(m_szName, pAIAnimation->mName.data);

	m_fDuration = (_float)pAIAnimation->mDuration;
	m_fTickPerSecond = (_float)pAIAnimation->mTicksPerSecond;

	m_iNumChannels = pAIAnimation->mNumChannels;

	/* �� �ִϸ��̼ǿ��� ����ϱ����� ��(aiNodeAnim,ä��)�� ������ �����. */
	for (size_t i = 0; i < m_iNumChannels; i++)
	{
		CChannel* pChannel = CChannel::Create(pAIAnimation->mChannels[i], Bones);
		if (nullptr == pChannel)
			return E_FAIL;

		m_Channels.push_back(pChannel);
	}

	return S_OK;
}

void CAnimation::Invalidate_TransformationMatrix(_bool isLoop, _float fTimeDelta, const CModel::BONES& Bones)
{
	m_fTrackPosition += m_fTickPerSecond * fTimeDelta;

	if (m_fTrackPosition >= m_fDuration)
	{
		m_isFinished = true;
		m_fTrackPosition = m_fDuration;

		if (true == isLoop)
		{
			m_fTrackPosition = 0.0f;
			m_isFinished = false;
		}
	}

	/* �� �ִϸ��̼��� �̿��ϴ� ��ü ���� ���¸� m_fTrackPosition �ð��� �´� ���·� �����ϴ�.*/
	for (size_t i = 0; i < m_iNumChannels; i++)
	{
		m_Channels[i]->Invalidate_TransformationMatrix(m_fTrackPosition, Bones);
	}
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


void CAnimation::Free()
{
	for (auto& pChannel : m_Channels)
		Safe_Release(pChannel);

	m_Channels.clear();

}