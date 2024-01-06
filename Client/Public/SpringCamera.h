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
	// 	수평 , 수직 수행거리
	_float hDist  = 0.f;
	_float vDist = 0.f;
	_float SpringConstant=100.f; //용수철 상수(spring constant)가 커지면 스프링의 탄력이 줄어든다.	//시작값은 카메라를 움직이고 싶은 범위에 따라 달라진다.
	_float DampConstant=0.f;//용수철 상수를 바탕으로 한 감쇠(dampening)상수
	_float3 Velocity = {};
	_float3 ActualPosition = {};//속도벡터와 카메라의 실제 위치를 나타내는 벡터
	_float3 PreActualPosition = {};//카메라 보간을 위해 이전 프레임 포지션가져옴
	_float3 CameraTickPos = {};// tick 에서 값이 자꾸 이상하게 초기화되서 이걸로 다시 값을 맞춰줘야함 
	CTransform* m_ptarget = { nullptr };//카메라가 따라다닐 타깃 오브젝트 //타깃 오브젝트는 위치, 방향벡터 , 타깃의 위쪽을 가리키는 벡터를 지닌다.
	_float	m_fAngle = 0.f;
	_float  m_fPitch = 0.f;
	_matrix cameraMatrix;//최종 카메라 행렬
public:
	//카메라 X,Y,Z
	_float m_CameraOffsetX = 0.f;
	_float m_CameraOffsetY = 0.f;
	_float m_CameraOffsetZ = 0.f;
	_float CameraMoveSpeed = 3.f;//카메라 보간용 이동속도
private:
	_float				m_fMouseSensor = { 0.0f };
public:
	static CSpringCamera* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;



// 		
// 		function ComputeMatrix()
// 		
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
// 			Vector3 idealPosition = targetPositon - target.position - target.forward * hDist + target.up * vDist;
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