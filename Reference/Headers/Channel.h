#pragma once

#include "Base.h"

/* �� �ִϸ��̼ǿ��� ����ϴ� ���� ������. */
/* �ð��뿡 ���� ���� ����(Scale, Rotation, Position)�� �����Ѵ�.*/

BEGIN(Engine)

class CChannel final : public CBase
{
private:
	CChannel();
	virtual ~CChannel() = default;

public:
	HRESULT Initialize(const aiNodeAnim* pChannel);
	void Invalidate_TransformationMatrix(_float fCurrentTrackPosition);

private:
	_char				m_szName[MAX_PATH] = "";
	_uint				m_iNumKeyFrames = { 0 };
	vector<KEYFRAME>	m_KeyFrames;
	_uint				m_iCurrentKeyFrameIndex = { 0 };

public:
	static CChannel* Create(const aiNodeAnim* pChannel);
	virtual void Free() override;
};

END