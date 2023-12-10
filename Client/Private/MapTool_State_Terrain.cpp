#include "stdafx.h"
#include "MapTool_State_Terrain.h"
#include "GameInstance.h"

#include "MapTool_State_Object_Create.h"
#include "MapTool_State_Object_Delete.h"


void CMapTool_State_Terrain::Initialize(CLevel_MapTool* pActor)
{
	pActor->Update_MousePos();
	pActor->Set_BrushRange(30.f);
}

CState<CLevel_MapTool>* CMapTool_State_Terrain::Update(CLevel_MapTool* pActor)
{
	pActor->Update_MousePos();

	if (CGameInstance::GetInstance()->Mouse_Pressing(DIM_LB))
	{
		pActor->Terrain_Pick();
	}

	if (CGameInstance::GetInstance()->Key_Down(DIK_2))
	{
		return new CMapTool_State_Object_Create();
	}

	if (CGameInstance::GetInstance()->Key_Down(DIK_3))
	{
		return new CMapTool_State_Object_Delete();
	}

	return nullptr;
}

void CMapTool_State_Terrain::Release(CLevel_MapTool* pActor)
{
	pActor->Set_BrushRange(0.f);
}