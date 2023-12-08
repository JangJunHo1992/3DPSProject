#include "stdafx.h"
#include "MapTool_State_Terrain.h"
#include "GameInstance.h"

#include "MapTool_State_Object_Create.h"

void CMapTool_State_Terrain::Initialize(CLevel_MapTool* pActor)
{
	pActor->Update_MousePos();
	//pActor->Set_BrushRange(30.f);
}

CState<CLevel_MapTool>* CMapTool_State_Terrain::Update(CLevel_MapTool* pActor)
{
	pActor->Update_MousePos();

	if (CGameInstance::GetInstance()->Get_DIMouseState(DIM_LB)) 
	{
		pActor->Terrain_Pick();
	}

	if (CGameInstance::GetInstance()->Get_DIKeyState(DIK_2))
	{
		return new CMapTool_State_Object_Create();
	}

	return nullptr;
}

void CMapTool_State_Terrain::Release(CLevel_MapTool* pActor)
{
	pActor->Set_BrushRange(0.f);
}
