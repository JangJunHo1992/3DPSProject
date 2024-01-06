#pragma once

#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Client)

class CSpringCamera final : public CCamera
{
public:
	typedef struct tagSpringCameraDesc : public tagCameraDesc
	{
		_float		fMouseSensor = 0.0f;
	}SPRING_CAMERA_DESC;

private:
	CSpringCamera(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CSpringCamera(const CSpringCamera& rhs);
	virtual ~CSpringCamera() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;

public:
	virtual void Write_Json(json & Out_Json) override;
public:
	void CameraComputeMatrix();
	void CameraRotation();

public:
	// 	���� , ���� ����Ÿ�
	_float hDist  = 0.f;
	_float vDist = 0.f;
	_float SpringConstant=100.f; //���ö ���(spring constant)�� Ŀ���� �������� ź���� �پ���.	//���۰��� ī�޶� �����̰� ���� ������ ���� �޶�����.
	_float DampConstant=0.f;//���ö ����� �������� �� ����(dampening)���
	_float3 Velocity = {};
	_float3 ActualPosition = {};//�ӵ����Ϳ� ī�޶��� ���� ��ġ�� ��Ÿ���� ����
	_float3 PreActualPosition = {};//ī�޶� ������ ���� ���� ������ �����ǰ�����
	_float3 CameraTickPos = {};// tick ���� ���� �ڲ� �̻��ϰ� �ʱ�ȭ�Ǽ� �̰ɷ� �ٽ� ���� ��������� 
	CTransform* m_ptarget = { nullptr };//ī�޶� ����ٴ� Ÿ�� ������Ʈ //Ÿ�� ������Ʈ�� ��ġ, ���⺤�� , Ÿ���� ������ ����Ű�� ���͸� ���Ѵ�.
	_float	m_fAngle = 0.f;
	_float  m_fPitch = 0.f;
	_matrix cameraMatrix;//���� ī�޶� ���
public:
	//ī�޶� X,Y,Z
	_float m_CameraOffsetX = 0.f;
	_float m_CameraOffsetY = 0.f;
	_float m_CameraOffsetZ = 0.f;
	_float CameraMoveSpeed = 3.f;//ī�޶� ������ �̵��ӵ�
private:
	_float				m_fMouseSensor = { 0.0f };
public:
	static CSpringCamera* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;



// 		
// 		function ComputeMatrix()
// 		
// 		//�ʿ��� ����� ī�޶� ������ �ʱ�ȭ�ϴ� �Լ� 
// 		function Initialize(GameObject myTarget, float mySpringconstant, float myHDist, float myVDist)
// 		{
// 			target = myTarget;
// 			springConstant = mySpringconstant;
// 			hDist = myHDist;
// 			vDist = myVDist;
// 			//���ö ����� �������� ���� ����� ��ꤧ
// 			dampConstant = 2.f * sqrt(springConstant);
// 			//�̻����� ��ġ�� ���� ��ġ�� �ʱⰪ���� ��´�.
// 			//�⺻���� ���� ī�޶��� ���� ��ġ�� ����ϴ�.
// 			actualPosition = target.position - target.forward * hDist + target.up * vDist;
// 			//ī�޶� �ӵ��� �ʱⰪ�� 0�̿����Ѵ�.
// 			velocity = Vector3.Zero;
// 			//ī�޶���Ŀ� �ʱⰪ�� ����
// 			ComputeMatrix();
// 	
// 		}
// 		function Update(float timedelta)
// 		{
// 			//���� �̻����� ��ġ�� ���
// 			Vector3 idealPosition = targetPositon - target.position - target.forward * hDist + target.up * vDist;
// 			//�̻����� ��ġ���� ���� ��ġ�� ���ϴ� ���͸� ���Ѵ�.
// 			Vector3 displacement = actualPosition - idealPosition;
// 			//�������� ���ӵ��� ���� �ڿ� ����
// 			Vector3 springAccel = (-springConstant * displacement) - (dampConstant * velocity);
// 			velocity += springAccel * timedelta;
// 			actualPosition += velocity * timedelta;
// 			//ī�޶� ��� ������Ʈ 
// 			ComputeMatrix();
// 		}

};

END