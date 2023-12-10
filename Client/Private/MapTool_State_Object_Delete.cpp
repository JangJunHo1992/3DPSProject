#include "stdafx.h"
#include "MapTool_State_Object_Delete.h"
#include "GameInstance.h"
#include "GameObject.h"

#include "MapTool_State_Terrain.h"
#include "MapTool_State_Object_Create.h"

void CMapTool_State_Object_Delete::Initialize(CLevel_MapTool* pActor)
{
}

CState<CLevel_MapTool>* CMapTool_State_Object_Delete::Update(CLevel_MapTool* pActor)
{
	if (CGameInstance::GetInstance()->Mouse_Down(DIM_LB))
	{
		//pActor->Update_MousePos();
		list<CGameObject*>* list = CGameInstance::GetInstance()->Get_GameObjects(LEVEL_TOOL, TEXT("Layer_Monster"));


		CGameObject* pGameObject = pActor->Select_Object(TEXT("Layer_Monster"));
		if (pGameObject) 
		{
			pGameObject->Test_ResetPos();
			return nullptr;
		}
	}

	if (CGameInstance::GetInstance()->Key_Down(DIK_1))
	{
		return new CMapTool_State_Terrain();
	}

	if (CGameInstance::GetInstance()->Key_Down(DIK_2))
	{
		return new CMapTool_State_Object_Create();
	}

	return nullptr;
}

void CMapTool_State_Object_Delete::Release(CLevel_MapTool* pActor)
{
}
