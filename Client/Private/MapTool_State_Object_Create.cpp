#include "stdafx.h"
#include "MapTool_State_Object_Create.h"
#include "GameInstance.h"

#include "MapTool_State_Terrain.h"

void CMapTool_State_Object_Create::Initialize(CLevel_MapTool* pActor)
{
}

CState<CLevel_MapTool>* CMapTool_State_Object_Create::Update(CLevel_MapTool* pActor)
{
	if (CGameInstance::GetInstance()->Get_DIMouseState(DIM_LB))
	{
		pActor->Update_MousePos();
		//pActor->Create_Raider();
	}

	if (CGameInstance::GetInstance()->Get_DIKeyState(DIK_1))
	{
		return new CMapTool_State_Terrain();
	}

	return nullptr;
}

void CMapTool_State_Object_Create::Release(CLevel_MapTool* pActor)
{
}
