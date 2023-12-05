#pragma once

#include "Model.h"

BEGIN(Engine)

class CBone final : public CBase
{
private:
	CBone();
	virtual ~CBone() = default;

public:
	HRESULT	Initialize(aiNode* pAINode, _int iParentIndex);
	void Invalidate_CombinedTransformationMatrix(CModel::BONES& Bones);

private:
	_char				m_szName[MAX_PATH] = "";
	_int				m_iParentIndex = { 0 };
	/* 이 뼈만의 상태행렬 */
	_float4x4			m_TransformationMatrix;

	/* 이 뼈만의 상태행렬 * 부모뼈의 m_CombindTransformationMatrix */
	_float4x4			m_CombindTransformationMatrix;

public:
	static CBone* Create(aiNode* pAINode, _int iParentIndex);
	virtual void Free() override;
};

END