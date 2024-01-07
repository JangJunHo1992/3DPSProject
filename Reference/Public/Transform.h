#pragma once

#include "Component.h"


/* 객체들의 월드 상태를 표현하기위한 데이터를 가진다. (월드행렬) */
/* 해당 월드 상에서의 변환을 위한 기능을 가진다. */

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	enum STATE { STATE_RIGHT,STATE_UP,STATE_LOOK,STATE_POSITION,STATE_END};
private:
	CTransform(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public:
	//행렬의 행의 정보를 교체한다.
	void Set_State(STATE eState, const _float4& vState)
	{
		memcpy(&m_WorldMatrix.m[eState], &vState, sizeof(_float3));
	}
	void Set_State(STATE eState, _fvector vState)
	{
		m_WorldMatrix.m[eState][0] = XMVectorGetX(vState);
		m_WorldMatrix.m[eState][1] = XMVectorGetY(vState);
		m_WorldMatrix.m[eState][2] = XMVectorGetZ(vState);
		m_WorldMatrix.m[eState][3] = XMVectorGetW(vState);
	}

	void Set_Scaling(_float fScaleX, _float fScaleY, _float fScaleZ);

	_vector Get_State(STATE eState)
	{
		return XMVectorSet(m_WorldMatrix.m[eState][0],
						   m_WorldMatrix.m[eState][1],
						   m_WorldMatrix.m[eState][2],
						   m_WorldMatrix.m[eState][3]);
	}

	_float3 Get_Scaled()
	{
		return _float3(XMVectorGetX(XMVector3Length(XMLoadFloat4x4(&m_WorldMatrix).r[STATE_RIGHT]))
					 , XMVectorGetX(XMVector3Length(XMLoadFloat4x4(&m_WorldMatrix).r[STATE_UP]))
					 , XMVectorGetX(XMVector3Length(XMLoadFloat4x4(&m_WorldMatrix).r[STATE_LOOK])));
	}

	_matrix Get_WorldMatrix()
	{
		return XMLoadFloat4x4(&m_WorldMatrix);
	}
	_float4x4 Get_WorldFloat4x4() {
		return m_WorldMatrix;
	}
	_matrix Get_WorldMatrixInverse() {
		return XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_WorldMatrix));
	}
	_float4x4 Get_WorldFloat4x4Inverse() {
		_float4x4	InverseMatrix;
		XMStoreFloat4x4(&InverseMatrix, XMMatrixInverse(nullptr, XMLoadFloat4x4(&m_WorldMatrix)));
		return InverseMatrix;
	}

	void	Set_WorldMatrix(_float4x4 matrix) { m_WorldMatrix = matrix; }

public:
	HRESULT Initialize_Prototype(_float fSpeedPerSec, _float fRotationPerSec);

public:
	void Go_Straight(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Straight_L45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Straight_R45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Backward(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Backward_L45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Backward_R45(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Left(_float fTimeDelta, class CNavigation* pNavigation = nullptr);
	void Go_Right(_float fTimeDelta, class CNavigation* pNavigation = nullptr);

	void Knockback(_float fTimeDelta, class CNavigation* pNavigation = nullptr);

	void Turn(_fvector vAxis, _float fTimeDelta);
	void Rotation(_fvector vAxis, _float fRadian);
	void Go_Target(_fvector vTargetPos, _float fTimeDelta, _float fSpare = 0.1f);
	void Look_At(_fvector vTargetPos);
	void Look_At_OnLand(_fvector vTargetPos);
	void Look_At_Around(_fvector vTargetPos , _float fTimeDelta);

public:
	void Set_Position(const _float3& vState)
	{
		_vector vPosVec = XMLoadFloat3(&vState);
		
		XMStoreFloat4(&m_fPosition, vPosVec);
		Set_State(STATE::STATE_POSITION, m_fPosition);
	}

	void Add_Position(const _float3& vState)
	{
		_vector vPosVec = XMLoadFloat3(&vState);
		//_float4 vPos;
		//XMStoreFloat4(&vPos, vPosVec);
		m_WorldMatrix.m[STATE::STATE_POSITION][0] += vState.x;
		m_WorldMatrix.m[STATE::STATE_POSITION][1] += vState.y;
		m_WorldMatrix.m[STATE::STATE_POSITION][2] += vState.z;

	}
	void Add_RootBone_Position(const _float3& vPos);
public:
	_matrix		Get_RotationMatrix(FXMMATRIX Mat);
	_float3		Extract_PitchYawRollFromRotationMatrix(FXMMATRIX Mat);
public:
	HRESULT	Bind_ShaderResource(class CShader* pShader, const _char* pConstantName);

public:
	virtual void Write_Json(json& Out_Json) override;
	virtual void Load_FromJson(const json& In_Json) override;


private:
	_float				m_fSpeedPerSec = { 0.0f };
	_float				m_fRotationPerSec = { 0.0f };

	_float4x4			m_WorldMatrix = {};
	_float4				m_fPosition = {};

public:
	static CTransform* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, _float fSpeedPerSec, _float fRotationPerSec);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END