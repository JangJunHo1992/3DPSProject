#pragma once

#include "Bounding.h"

BEGIN(Engine)

class CBounding_Sphere final : public CBounding
{
public:
	typedef struct : public BOUNDING_DESC
	{
		_float		fRadius;
	}BOUNDING_SPHERE_DESC;
private:
	CBounding_Sphere(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual ~CBounding_Sphere() = default;

public:
	const BoundingSphere* Get_Bounding() {
		return m_pSphere;
	}

public:
	HRESULT Initialize(BOUNDING_DESC* pBoundingDesc);
	virtual void Update(_fmatrix TransformMatrix);

#ifdef _DEBUG
public:
	virtual HRESULT Render(PrimitiveBatch<VertexPositionColor>* pBatch, _vector vColor) override;
#endif

public:
	virtual _bool Collision(class CCollider* pTargetCollider, _bool* pisCollision) override;

private:
	BoundingSphere* m_pOriginalSphere = { nullptr };
	BoundingSphere* m_pSphere = { nullptr };



public:
	static CBounding_Sphere* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, BOUNDING_DESC* pBoundingDesc);
	virtual void Free() override;
};

END