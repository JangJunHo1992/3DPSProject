#pragma once

#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Client)
class CCovus;

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
	void CameraRotation(_float fTimeDelta);
public:
	void RotatePlayer();
	void Mouse_Fix();
public:
	// 	수평 , 수직 수행거리
	_float hDist  = 0.f;
	_float vDist = 0.f;
	_float SpringConstant=600.f; //용수철 상수(spring constant)가 커지면 스프링의 탄력이 줄어든다.	//시작값은 카메라를 움직이고 싶은 범위에 따라 달라진다.
	_float DampConstant=0.f;//용수철 상수를 바탕으로 한 감쇠(dampening)상수
	_float3 Velocity = {};
	_float3 ActualPosition = {};//속도벡터와 카메라의 실제 위치를 나타내는 벡터
	_float3 PreActualPosition = {};//카메라 보간을 위해 이전 프레임 포지션가져옴
	_float3 CameraTickPos = {};// tick 에서 값이 자꾸 이상하게 초기화되서 이걸로 다시 값을 맞춰줘야함 
	CTransform* m_ptarget = { nullptr };//카메라가 따라다닐 타깃 오브젝트 //타깃 오브젝트는 위치, 방향벡터 , 타깃의 위쪽을 가리키는 벡터를 지닌다.
	CCovus* m_pPlayer = { nullptr };
	_float	m_fAngle = 0.f;
	_float  m_fPitch = 0.f;
	_matrix cameraMatrix;//최종 카메라 행렬
	_bool m_bCheck = false;//마우스 가운데 모으기 
	_bool m_bFix = true;//마우스 가운데 모으기 
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
};

END