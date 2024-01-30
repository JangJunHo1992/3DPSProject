#include "stdafx.h"
#include "Level_EffectTool.h"
#include "GameInstance.h"
#include "Camera_Dynamic.h"
#include "Level_Loading.h"

#include "Particle_Custom_EffectTool.h"

#include "Imgui_Manager.h"
#include "Effect_Window.h"

#include "Camera_Dynamic.h"

CLevel_EffectTool::CLevel_EffectTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CLevel(pDevice, pContext)
{
}

HRESULT CLevel_EffectTool::Initialize()
{
	Load_Desc();

	_float3 vPos = _float3(0.f, 0.f, 0.f);
	m_Desc.vPos = vPos;


	if (FAILED(Ready_LightDesc()))
		return E_FAIL;

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_EFFECT_TOOL, TEXT("Layer_Weapon"), TEXT("Prototype_GameObject_Raider_Weapon_DoubleSword"))))
		return E_FAIL;

	m_pWaepon = m_pGameInstance->Get_GameObjects(LEVEL_EFFECT_TOOL, TEXT("Layer_Weapon"))->back();
	m_Desc.parentMatrix = m_pWaepon->Get_TransformComp()->Get_WorldFloat4x4();


	m_pImguiManager = CImgui_Manager::GetInstance();
	m_pEffectWin = CEffect_Window::GetInstance();


	if (FAILED(m_pImguiManager->SetUp_Imgui(m_pDevice, m_pContext)))
		return E_FAIL;

	m_pEffectWin->Set_Level(this);

	return S_OK;
}

void CLevel_EffectTool::Tick(_float fTimeDelta)
{
	m_pImguiManager->Tick(fTimeDelta);

	m_fDelay -= fTimeDelta;
	if (0 >= m_fDelay)
	{
		Ready_Layer_Effect(TEXT("Layer_Effect"));
		m_fDelay = m_fMaxDelay;
	}

	if (m_pGameInstance->Key_Down(DIK_P))
	{
		Save_Desc();
	}

}

HRESULT CLevel_EffectTool::Render()
{
	SetWindowText(g_hWnd, TEXT("이펙트툴 레벨입니다."));

	m_pImguiManager->Render();

	return S_OK;
}

HRESULT CLevel_EffectTool::Ready_LightDesc()
{
	LIGHT_DESC			LightDesc{};

	LightDesc.eType = LIGHT_DESC::TYPE_DIRECTIONAL;
	LightDesc.vDirection = _float4(1.f, -1.f, 1.f, 0.f);
	LightDesc.vDiffuse = _float4(1.f, 1.0f, 1.0f, 1.0f);
	LightDesc.vAmbient = _float4(0.5f, 0.5f, 0.5f, 1.f);
	LightDesc.vSpecular = _float4(0.1f, 0.1f, 0.1f, 0.1f);

	if (FAILED(m_pGameInstance->Add_Light(LightDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_EffectTool::Ready_Layer_Camera(const wstring& strLayerTag)
{
	CCamera_Dynamic::DYNAMIC_CAMERA_DESC		Desc = {};

	Desc.fMouseSensor = 0.05f;

	Desc.fFovy = XMConvertToRadians(60.0f);
	Desc.fAspect = (_float)g_iWinSizeX / g_iWinSizeY;
	Desc.fNear = 0.1f;
	Desc.fFar = 1000.f;
	Desc.fSpeedPerSec = 20.f;
	Desc.fRotationPerSec = XMConvertToRadians(180.0f);

	Desc.vEye = _float4(0.f, 0.f, -3.f, 1.f);
	Desc.vAt = _float4(0.f, 0.f, 0.f, 1.f);
	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_EFFECT_TOOL, strLayerTag, TEXT("Prototype_GameObject_Camera_Dynamic"), &Desc)))
		return E_FAIL;

	m_pCamera = static_cast<CCamera_Dynamic*>(m_pGameInstance->Get_GameObjects(LEVEL_EFFECT_TOOL, strLayerTag)->back());


	return S_OK;
}

HRESULT CLevel_EffectTool::Ready_Layer_Effect(const wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_EFFECT_TOOL, TEXT("Layer_Effect"), TEXT("Prototype_GameObject_Particle_Custom"), &m_Desc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CLevel_EffectTool::Load_Objects_With_Json(string filePath)
{
	json json_in;
	m_pGameInstance->Load_Json(filePath, json_in);

	for (auto& item : json_in.items())
	{
		json object = item.value();

		if (NULL == object)
			continue;

		string tagObject = "Prototype_GameObject_";

		string targetName = object["Name"];
		tagObject += targetName;

		string tagLayer = object["LayerTag"];

		wstring wStringLayerTag;
		wStringLayerTag.assign(tagLayer.begin(), tagLayer.end());

		wstring wStringObjTag;
		wStringObjTag.assign(tagObject.begin(), tagObject.end());


		if (FAILED(m_pGameInstance->Add_CloneObject(LEVEL_EFFECT_TOOL, wStringLayerTag, wStringObjTag)))
			return E_FAIL;

		list<CGameObject*>* pGameObjects = m_pGameInstance->Get_GameObjects(LEVEL_EFFECT_TOOL, wStringLayerTag);
		if (nullptr == pGameObjects)
			continue;

		CGameObject* pGameObject = pGameObjects->back();
		if (nullptr == pGameObject)
			continue;

		_float4x4 WorldMatrix;
		ZeroMemory(&WorldMatrix, sizeof(_float4x4));
		CJson_Utility::Load_JsonFloat4x4(object["Component"]["Transform"], WorldMatrix);

		pGameObject->Set_WorldMatrix(WorldMatrix);

	}

	return S_OK;
}

void CLevel_EffectTool::Set_CamPos(_float fDistance)
{
	_float3 vPos = { 0.f, 0.f, fDistance * -1.0f };
	m_pCamera->Set_Position(vPos);
}

void CLevel_EffectTool::Save_Desc()
{
	string filePath = "Particle_Desc";
	json Out_Json;

	Out_Json["CenterX"] = m_Desc.ParticleDesc.vCenter.x;
	Out_Json["CenterY"] = m_Desc.ParticleDesc.vCenter.y;
	Out_Json["CenterZ"] = m_Desc.ParticleDesc.vCenter.z;

	Out_Json["CullingX"] = m_Desc.ParticleDesc.vCulling.x;
	Out_Json["CullingY"] = m_Desc.ParticleDesc.vCulling.y;
	Out_Json["CullingZ"] = m_Desc.ParticleDesc.vCulling.z;

	//Out_Json["CenterX"] = m_Desc.ParticleDesc.vCenter.x;
	//Out_Json["CenterY"] = m_Desc.ParticleDesc.vCenter.y;
	//Out_Json["CenterZ"] = m_Desc.ParticleDesc.vCenter.z;

	Out_Json["Range_Min"] = m_Desc.ParticleDesc.vRange.x;
	Out_Json["Range_Max"] = m_Desc.ParticleDesc.vRange.y;

	Out_Json["RotationX_Min"] = m_Desc.ParticleDesc.vRotationX.x;
	Out_Json["RotationX_Max"] = m_Desc.ParticleDesc.vRotationX.y;

	Out_Json["RotationY_Min"] = m_Desc.ParticleDesc.vRotationY.x;
	Out_Json["RotationY_Max"] = m_Desc.ParticleDesc.vRotationY.y;

	Out_Json["RotationZ_Min"] = m_Desc.ParticleDesc.vRotationZ.x;
	Out_Json["RotationZ_Max"] = m_Desc.ParticleDesc.vRotationZ.y;

	Out_Json["Speed_Min"] = m_Desc.ParticleDesc.vSpeed.x;
	Out_Json["Speed_Max"] = m_Desc.ParticleDesc.vSpeed.y;

	Out_Json["Acceleration"] = m_Desc.ParticleDesc.fAcceleration;

	Out_Json["ScaleX_Min"] = m_Desc.ParticleDesc.vScaleX.x;
	Out_Json["ScaleX_Max"] = m_Desc.ParticleDesc.vScaleX.y;

	Out_Json["ScaleY_Min"] = m_Desc.ParticleDesc.vScaleY.x;
	Out_Json["ScaleY_Max"] = m_Desc.ParticleDesc.vScaleY.y;

	Out_Json["LifeTime_Min"] = m_Desc.ParticleDesc.vLifeTime.x;
	Out_Json["LifeTime_Max"] = m_Desc.ParticleDesc.vLifeTime.y;


	m_pGameInstance->Save_Json(filePath, Out_Json);
}

void CLevel_EffectTool::Load_Desc()
{
	json json_in;
	string filePath = "Particle_Desc";
	if (FAILED(m_pGameInstance->Load_Json(filePath, json_in)))
	{
		return;
	}

	m_Desc.ParticleDesc.vCenter.x = json_in["CenterX"];
	m_Desc.ParticleDesc.vCenter.y = json_in["CenterY"];
	m_Desc.ParticleDesc.vCenter.z = json_in["CenterZ"];

	m_Desc.ParticleDesc.vCulling.x = json_in["CullingX"];
	m_Desc.ParticleDesc.vCulling.y = json_in["CullingY"];
	m_Desc.ParticleDesc.vCulling.z = json_in["CullingZ"];

	m_Desc.ParticleDesc.vRange.x = json_in["Range_Min"];
	m_Desc.ParticleDesc.vRange.y = json_in["Range_Max"];

	m_Desc.ParticleDesc.vRotationX.x = json_in["RotationX_Min"];
	m_Desc.ParticleDesc.vRotationX.y = json_in["RotationX_Max"];

	m_Desc.ParticleDesc.vRotationY.x = json_in["RotationY_Min"];
	m_Desc.ParticleDesc.vRotationY.y = json_in["RotationY_Max"];

	m_Desc.ParticleDesc.vRotationZ.x = json_in["RotationZ_Min"];
	m_Desc.ParticleDesc.vRotationZ.y = json_in["RotationZ_Max"];

	m_Desc.ParticleDesc.vSpeed.x = json_in["Speed_Min"];
	m_Desc.ParticleDesc.vSpeed.y = json_in["Speed_Max"];

	m_Desc.ParticleDesc.fAcceleration = json_in["Acceleration"];

	m_Desc.ParticleDesc.vScaleX.x = json_in["ScaleX_Min"];
	m_Desc.ParticleDesc.vScaleX.y = json_in["ScaleX_Max"];

	m_Desc.ParticleDesc.vScaleY.x = json_in["ScaleY_Min"];
	m_Desc.ParticleDesc.vScaleY.y = json_in["ScaleY_Max"];

	m_Desc.ParticleDesc.vLifeTime.x = json_in["LifeTime_Min"];
	m_Desc.ParticleDesc.vLifeTime.y = json_in["LifeTime_Max"];

}

CLevel_EffectTool* CLevel_EffectTool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CLevel_EffectTool* pInstance = new CLevel_EffectTool(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_EffectTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_EffectTool::Free()
{
	__super::Free();

}
