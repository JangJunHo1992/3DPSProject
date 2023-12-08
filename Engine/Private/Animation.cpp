#include "Animation.h"
#include "Channel.h"

CAnimation::CAnimation()
{
}

HRESULT CAnimation::Initialize(const aiAnimation* pAIAnimation)
{
	strcpy_s(m_szName, pAIAnimation->mName.data);

	m_fDuration = (_float)pAIAnimation->mDuration;
	m_fTickPerSecond = (_float)pAIAnimation->mTicksPerSecond;

	m_iNumChannels = pAIAnimation->mNumChannels;

	/* �� �ִϸ��̼ǿ��� ����ϱ����� ��(aiNodeAnim,ä��)�� ������ �����. */
	for (size_t i = 0; i < m_iNumChannels; i++)
	{
		CChannel* pChannel = CChannel::Create(pAIAnimation->mChannels[i]);
		if (nullptr == pChannel)
			return E_FAIL;

		m_Channels.push_back(pChannel);
	}

	return S_OK;
}

void CAnimation::Invalidate_TransformationMatrix(_float fTimeDelta)
{
	m_fTrackPosition += m_fTickPerSecond * fTimeDelta;

	/* �� �ִϸ��̼��� �̿��ϴ� ��ü ���� ���¸� m_fTrackPosition �ð��� �´� ���·� �����ϴ�.*/
	for (size_t i = 0; i < m_iNumChannels; i++)
	{
		m_Channels[i]->Invalidate_TransformationMatrix(m_fTrackPosition);
	}
}

CAnimation* CAnimation::Create(const aiAnimation* pAIAnimation)
{
	CAnimation* pInstance = new CAnimation();

	if (FAILED(pInstance->Initialize(pAIAnimation)))
	{
		MSG_BOX("Failed to Created : CAnimation");
		Safe_Release(pInstance);
	}
	return pInstance;
}


void CAnimation::Free()
{
}
