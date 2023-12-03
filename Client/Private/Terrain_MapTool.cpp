#include "stdafx.h"
#include "Terrain_MapTool.h"

CTerrain_MapTool::CTerrain_MapTool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CTerrain(pDevice, pContext)
{

}

CTerrain_MapTool::CTerrain_MapTool(const CTerrain_MapTool& rhs)
	: CTerrain(rhs)
{
}

HRESULT CTerrain_MapTool::Ready_Components()
{
	return Ready_Components_Origin(LEVEL::LEVEL_TOOL);
}

CTerrain_MapTool* CTerrain_MapTool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTerrain_MapTool* pInstance = new CTerrain_MapTool(pDevice, pContext);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTerrain_MapTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CTerrain_MapTool::Clone(void* pArg)
{
	CTerrain_MapTool* pInstance = new CTerrain_MapTool(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTerrain_MapTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}