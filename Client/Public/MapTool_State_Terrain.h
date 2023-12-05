#pragma once
#include "Client_Defines.h"
#include "State.h"
#include "Level_MapTool.h"

BEGIN(Client)

class CMapTool_State_Terrain : public CState<CLevel_MapTool>
{
	// CState��(��) ���� ��ӵ�
	virtual void Initialize(CLevel_MapTool* pActor) override;
	virtual CState<CLevel_MapTool>* Update(CLevel_MapTool* pActor) override;
	virtual void Release(CLevel_MapTool* pActor) override;
};

END