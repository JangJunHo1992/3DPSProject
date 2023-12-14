#pragma once

#include "Client_Defines.h"
#include "Camera.h"

BEGIN(Client)

class CCamera_Dynamic_Tool final : public CCamera
{
public:
	typedef struct tagDynamicCameraDesc : public tagCameraDesc
	{
		_float		fMouseSensor = 0.0f;
	}DYNAMIC_CAMERA_DESC;

private:
	CCamera_Dynamic_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCamera_Dynamic_Tool(const CCamera_Dynamic_Tool& rhs);
	virtual ~CCamera_Dynamic_Tool() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;

public:
	virtual void Write_Json(json& Out_Json) override;

private:
	_float				m_fMouseSensor = { 0.0f };
	LEVEL				m_eLevel;
public:
	static CCamera_Dynamic_Tool* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;
};

END