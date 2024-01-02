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
// 	수평 , 수직 수행거리
// 		float hDist, vDist;
// 		//용수철 상수(spring constant)가 커지면 스프링의 탄력이 줄어든다.
// 		//시작값은 카메라를 움직이고 싶은 범위에 따라 달라진다.
// 		float springConstant;
// 		//용수철 상수를 바탕으로 한 감쇠(dampening)상수
// 		float dampConstant;
// 	
// 		//속도벡터와 카메라의 실제 위치를 나타내는 벡터
// 		Vector3 velocity, actualPosition;
// 	
// 		//카메라가 따라다닐 타깃 오브젝트 
// 		//타깃 오브젝트는 위치, 방향벡터 , 타깃의 위쪽을 가리키는 벡터를 지닌다.
// 		GameObject target;
// 		//최종 카메라 행렬
// 		Matrix cameraMatrix;
// 	
// 		//이함수는 실제 카메라의 위치와 타깃의 위치를 사용해서 카메라행렬을 계산한다
// 		function ComputeMatrix()
// 		{
// 			//카메라의 방향은 실제 카메라의 위치에서 타깃의 위치로 향한다. 
// 			Vector3 cameraForward = target.position - actualPosition;
// 			cameraForward.Normalize();
// 	
// 		
// 			//외적을 사용해서 카메라의 왼쪽을 향하는 벡터를 계산한 뒤에 
// 			//카메라의 위쪽을 향하는 벡터를 계산한다.
// 			Vector3 cameraLeft = CrossProduct(target.up, cameraForward);
// 			cameraLeft.Normalize();
// 			Vector3 cameraUp = CrossProduct(cameraForward, cameraLeft);
// 			cameraUp.Normalize();
// 	
// 			//CreateLookAt에 카메라의 눈, 타깃의 위치, 위쪽을 가리키는 벡터를 전달한다.
// 			cameraMatrix = createLookAt(actualPosition, target.position, cameraUp);
// 		}
// 		//필요한 상수와 카메라 방향을 초기화하는 함수 
// 		function Initialize(GameObject myTarget, float mySpringconstant, float myHDist, float myVDist)
// 		{
// 			target = myTarget;
// 			springConstant = mySpringconstant;
// 			hDist = myHDist;
// 			vDist = myVDist;
// 			//용수철 상수를 바탕으로 감쇠 상수를 계산ㄷ
// 			dampConstant = 2.f * sqrt(springConstant);
// 			//이상적인 위치를 실제 위치의 초기값으로 삼는다.
// 			//기본적인 수행 카메라의 눈의 위치와 비슷하다.
// 			actualPosition = target.position - target.forward * hDist + target.up * vDist;
// 			//카메라 속도의 초기값은 0이여야한다.
// 			velocity = Vector3.Zero;
// 			//카메라행렬에 초기값을 설정
// 			ComputeMatrix();
// 	
// 		}
// 		function Update(float timedelta)
// 		{
// 			//먼저 이상적인 위치를 계산
// 			Vector3 idealPosition = target.position - target.forward * hDist + target.up * vDist;
// 			//이상적인 위치에서 실제 위치로 향하는 벡터를 구한다.
// 			Vector3 displacement = actualPosition - idealPosition;
// 			//스프링의 가속도를 구한 뒤에 적분
// 			Vector3 springAccel = (-springConstant * displacement) - (dampConstant * velocity);
// 			velocity += springAccel * timedelta;
// 			actualPosition += velocity * timedelta;
// 			//카메라 행렬 업데이트 
// 			ComputeMatrix();
// 		}

};

END