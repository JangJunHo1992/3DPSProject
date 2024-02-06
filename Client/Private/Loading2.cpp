#include "stdafx.h"
#include "Loading2.h"
#include "GameInstance.h"


CLoading2::CLoading2(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CLoading2::CLoading2(const CLoading2& rhs)
	: CGameObject(rhs)
{
}

HRESULT CLoading2::Initialize_Prototype()
{
	/* ������ü�� �ʱ�ȭ������ �����Ѵ�. */
	/* 1.�����κ��� ���� �޾ƿͼ� �ʱ�ȭ�Ѵ� .*/
	/* 2.����������� ���� ���� �޾ƿ´�.*/
	//int*		pData_int = new int(3);

	//void**		pData = (void**)&pData_int;

	return S_OK;
}

HRESULT CLoading2::Initialize(void* pArg)
{
	/* ��׶��� ��ü�� ����� Trnasform������Ʈ�� �����Ͽ� �߰��س��´�. */
	/*if (FAILED(__super::Initialize(&CGameObject::GAMEOBJECT_DESC(10.0f, 90.0f))))
		return E_FAIL;*/

	Loading2_DESC* pDesc = (Loading2_DESC*)pArg;

	m_fX = pDesc->fX;
	m_fY = pDesc->fY;
	m_fSizeX = pDesc->fSizeX;
	m_fSizeY = pDesc->fSizeY;


	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	// void* pArg : �����Ͽ� ��ü�� �����Ҷ� �������� ä���� ���� �����͸� �߰������� �� �ʱ�ȭ���ֱ����ؼ�. 
	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Set_Scaling(m_fSizeX, m_fSizeY, 1.f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.02f, 1.f));

	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH(g_iWinSizeX, g_iWinSizeY, 0.f, 1.f));


	return S_OK;
}

void CLoading2::Priority_Tick(_float fTimeDelta)
{
	int a = 10;


}

void CLoading2::Tick(_float fTimeDelta)
{


	//if (GetKeyState(VK_LEFT) & 0x8000)
	//	m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta * -1.f);
	//if (GetKeyState(VK_RIGHT) & 0x8000)
	//	m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), fTimeDelta);

	//if (GetKeyState(VK_UP) & 0x8000)
	//	m_pTransformCom->Go_Straight(fTimeDelta);
	//if (GetKeyState(VK_DOWN) & 0x8000)
	//	m_pTransformCom->Go_Backward(fTimeDelta);

}

void CLoading2::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this)))
		return;
}

HRESULT CLoading2::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* �� �Τ��̴��� 0��° �н��� �׸�����. */
	m_pShaderCom->Begin(0);

	/* ���� �׸������ϴ� ����, �ΉK�������۸� ��ġ�� ���ε���. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* ���ε��� ����, �ε����� �׷�. */
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CLoading2::Ready_Components()
{
	//void** ���� �ƹ��ų� �������� ���� ���� ����ȯ�� ����� ��!
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxPosTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	/* For. Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_LOADING, TEXT("Prototype_Component_Texture_Loading2"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CLoading2::Bind_ShaderResources()
{

	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;
	if (FAILED(m_pTextureCom->Bind_ShaderResources(m_pShaderCom, "g_Texture")))
		return E_FAIL;

	return S_OK;
}

CLoading2* CLoading2::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CLoading2* pInstance = new CLoading2(pDevice, pContext);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CLoading2");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CLoading2::Clone(void* pArg)
{
	CLoading2* pInstance = new CLoading2(*this);

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CLoading2");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoading2::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pShaderCom);
}

