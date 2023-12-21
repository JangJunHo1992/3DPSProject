#include "stdafx.h"
#include "MapTool_State_Object_Create.h"
#include "GameInstance.h"

#include "MapTool_State_Terrain.h"
#include "MapTool_State_Object_Delete.h"

void CMapTool_State_Object_Create::Initialize(CLevel_MapTool* pActor)
{
}

CState<CLevel_MapTool>* CMapTool_State_Object_Create::Update(CLevel_MapTool* pActor, _float fTimeDelta)
{
	if (CGameInstance::GetInstance()->Mouse_Down(DIM_LB))
	{
		pActor->Update_MousePos();
		pActor->Create_Raider();
	}

	if (CGameInstance::GetInstance()->Key_Down(DIK_1))
	{
		return new CMapTool_State_Terrain();
	}

	if (CGameInstance::GetInstance()->Key_Down(DIK_3))
	{
		return new CMapTool_State_Object_Delete();
	}

	return nullptr;
}

void CMapTool_State_Object_Create::Release(CLevel_MapTool* pActor)
{
}
