#include "stdafx.h"
#include "Terrain_Tool.h"
#include "GameInstance.h"

CTerrain_Tool::CTerrain_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CTerrain(pDevice, pContext)
{

}

CTerrain_Tool::CTerrain_Tool(const CTerrain_Tool& rhs)
	: CTerrain(rhs)
{
}

HRESULT CTerrain_Tool::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL::LEVEL_TOOL)))
		return E_FAIL;

	/* For.Com_Brush */
	if (FAILED(__super::Add_Component(LEVEL::LEVEL_TOOL, TEXT("Prototype_Component_Texture_Terrain_Brush"),
		TEXT("Com_Brush"), reinterpret_cast<CComponent**>(&m_pTextureCom[TYPE_BRUSH]))))
		return E_FAIL;

	return S_OK;
}


HRESULT CTerrain_Tool::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	return S_OK;
}

void CTerrain_Tool::pick()
{
	m_pVIBufferCom->Invalidate_Terrain(m_vPickedPos, m_fBrushRange * 2 / 3.f, m_fBrushHeight, m_iMode);
}

HRESULT CTerrain_Tool::Bind_ShaderResources()
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

void CTerrain_Tool::Change_Plane_Buffer(_ushort x, _ushort z)
{
	if (!m_bIsPlane)
		return;

}

void CTerrain_Tool::Update_MousePos()
{
	_matrix matWorld = m_pTransformCom->Get_WorldMatrix();

	RAY mousRayLocal = CGameInstance::GetInstance()->Get_MouseRayLocal(g_hWnd, g_iWinSizeX, g_iWinSizeY, matWorld);

	_bool bResult = m_pVIBufferCom->Picking(mousRayLocal, &m_vPickedPosFloat3);
	m_vPickedPos = XMLoadFloat3(&m_vPickedPosFloat3);
}


CTerrain_Tool* CTerrain_Tool::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, _bool isPlane)
{
	CTerrain_Tool*		pInstance = new CTerrain_Tool(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype(isPlane)))
	{
		MSG_BOX("Failed to Created : CTerrain_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CTerrain_Tool::Clone(void* pArg)
{
	CTerrain_Tool*		pInstance = new CTerrain_Tool(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTerrain_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTerrain_Tool::Free()
{
	__super::Free();
	//Safe_Release(m_pGameInstance);
}




