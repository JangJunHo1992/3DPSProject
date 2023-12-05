#include "stdafx.h"
#include "Terrain_MapTool.h"
#include "GameInstance.h"

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

	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	/* For.Com_Brush */
	if (FAILED(__super::Add_Component(LEVEL::LEVEL_TOOL, TEXT("Prototype_Component_Texture_Terrain_Brush"),
		TEXT("Com_Brush"), reinterpret_cast<CComponent**>(&m_pTextureCom[TYPE_BRUSH]))))
		return E_FAIL;


	return S_OK;
}

CTerrain_MapTool* CTerrain_MapTool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTerrain_MapTool* pInstance = new CTerrain_MapTool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
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

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTerrain_MapTool");
		Safe_Release(pInstance);
	}
	return pInstance;
}



void CTerrain_MapTool::pick()
{
	m_pVIBufferCom->Update_Terrain(m_vPickedPos, m_fBrushRange * 2 / 3.f, 1.0f);
}

HRESULT CTerrain_MapTool::Bind_ShaderResources()
{
	if (FAILED(Bind_ShaderResources_Origin()))
		return E_FAIL;

	if (FAILED(m_pTextureCom[TYPE_BRUSH]->Bind_ShaderResource(m_pShaderCom, "g_BrushTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Bind_RawValue("g_vBrushPos", &m_vPickedPos, sizeof(_float4))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_RawValue("g_fBrushRange", &m_fBrushRange, sizeof(_float))))
		return E_FAIL;

	return S_OK;
}

void CTerrain_MapTool::Update_MousePos()
{
	_matrix matWorld = m_pTransformCom->Get_WorldMatrix();

	RAY mousRayLocal = CGameInstance::GetInstance()->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, matWorld);

	_bool bResult = m_pVIBufferCom->Picking(mousRayLocal, &m_vPickedPosFloat3);
	m_vPickedPos = XMLoadFloat3(&m_vPickedPosFloat3);
}




