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

private:
	_float				m_fMouseSensor = { 0.0f };

public:
	static CSpringCamera* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
// 	���� , ���� ����Ÿ�
// 		float hDist, vDist;
// 		//���ö ���(spring constant)�� Ŀ���� �������� ź���� �پ���.
// 		//���۰��� ī�޶� �����̰� ���� ������ ���� �޶�����.
// 		float springConstant;
// 		//���ö ����� �������� �� ����(dampening)���
// 		float dampConstant;
// 	
// 		//�ӵ����Ϳ� ī�޶��� ���� ��ġ�� ��Ÿ���� ����
// 		Vector3 velocity, actualPosition;
// 	
// 		//ī�޶� ����ٴ� Ÿ�� ������Ʈ 
// 		//Ÿ�� ������Ʈ�� ��ġ, ���⺤�� , Ÿ���� ������ ����Ű�� ���͸� ���Ѵ�.
// 		GameObject target;
// 		//���� ī�޶� ���
// 		Matrix cameraMatrix;
// 	
// 		//���Լ��� ���� ī�޶��� ��ġ�� Ÿ���� ��ġ�� ����ؼ� ī�޶������ ����Ѵ�
// 		function ComputeMatrix()
// 		{
// 			//ī�޶��� ������ ���� ī�޶��� ��ġ���� Ÿ���� ��ġ�� ���Ѵ�. 
// 			Vector3 cameraForward = target.position - actualPosition;
// 			cameraForward.Normalize();
// 	
// 		
// 			//������ ����ؼ� ī�޶��� ������ ���ϴ� ���͸� ����� �ڿ� 
// 			//ī�޶��� ������ ���ϴ� ���͸� ����Ѵ�.
// 			Vector3 cameraLeft = CrossProduct(target.up, cameraForward);
// 			cameraLeft.Normalize();
// 			Vector3 cameraUp = CrossProduct(cameraForward, cameraLeft);
// 			cameraUp.Normalize();
// 	
// 			//CreateLookAt�� ī�޶��� ��, Ÿ���� ��ġ, ������ ����Ű�� ���͸� �����Ѵ�.
// 			cameraMatrix = createLookAt(actualPosition, target.position, cameraUp);
// 		}
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
// 			Vector3 idealPosition = target.position - target.forward * hDist + target.up * vDist;
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