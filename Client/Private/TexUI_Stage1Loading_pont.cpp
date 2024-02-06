#include "stdafx.h"
#include "TexUI_Stage1Loading_pont.h"
#include "GameInstance.h"


CTexUI_Stage1Loading_pont::CTexUI_Stage1Loading_pont(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CTexUI_Stage1Loading_pont::CTexUI_Stage1Loading_pont(const CTexUI_Stage1Loading_pont& rhs)
	: CGameObject(rhs)
{
}

HRESULT CTexUI_Stage1Loading_pont::Initialize_Prototype()
{
	/* 원형객체의 초기화과정을 수행한다. */
	/* 1.서버로부터 값을 받아와서 초기화한다 .*/
	/* 2.파일입출력을 통해 값을 받아온다.*/
	//int*		pData_int = new int(3);

	//void**		pData = (void**)&pData_int;

	return S_OK;
}

HRESULT CTexUI_Stage1Loading_pont::Initialize(void* pArg)
{
	/* 백그라운드 객체가 사용할 Trnasform컴포넌트를 생성하여 추가해놓는다. */
	/*if (FAILED(__super::Initialize(&CGameObject::GAMEOBJECT_DESC(10.0f, 90.0f))))
		return E_FAIL;*/

	TexUI_Stage1Loading_pont_DESC* pDesc = (TexUI_Stage1Loading_pont_DESC*)pArg;

	m_fX = pDesc->fX;
	m_fY = pDesc->fY;
	m_fSizeX = pDesc->fSizeX;
	m_fSizeY = pDesc->fSizeY;


	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	// void* pArg : 복제하여 객체를 생성할때 원형에서 채우지 못한 데이터를 추가적으로 더 초기화해주기위해서. 
	if (FAILED(Ready_Components()))
		return E_FAIL;

	m_pTransformCom->Set_Scaling(m_fSizeX, m_fSizeY, 1.f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.01f, 1.f));

	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH(g_iWinSizeX, g_iWinSizeY, 0.f, 1.f));


	return S_OK;
}

void CTexUI_Stage1Loading_pont::Priority_Tick(_float fTimeDelta)
{
	int a = 10;


}

void CTexUI_Stage1Loading_pont::Tick(_float fTimeDelta)
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

void CTexUI_Stage1Loading_pont::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this)))
		return;
}

HRESULT CTexUI_Stage1Loading_pont::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* 이 셰ㅒ이더에 0번째 패스로 그릴꺼야. */
	m_pShaderCom->Begin(6);

	/* 내가 그릴려고하는 정점, 인덷ㄱ스버퍼를 장치에 바인딩해. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* 바인딩된 정점, 인덱스를 그려. */
	
	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CTexUI_Stage1Loading_pont::Ready_Components()
{
	//void** 형은 아무거나 들어가질수가 없음 따라서 형변환을 해줘야 함!
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Shader_VtxPosTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	/* For. Com_Texture */
	if (FAILED(__super::Add_Component(LEVEL_LOADING, TEXT("Prototype_Component_Texture_TexUI_Stage1Loading_pont"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CTexUI_Stage1Loading_pont::Bind_ShaderResources()
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

CTexUI_Stage1Loading_pont* CTexUI_Stage1Loading_pont::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTexUI_Stage1Loading_pont* pInstance = new CTexUI_Stage1Loading_pont(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CTexUI_Stage1Loading_pont");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CTexUI_Stage1Loading_pont::Clone(void* pArg)
{
	CTexUI_Stage1Loading_pont* pInstance = new CTexUI_Stage1Loading_pont(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTexUI_Stage1Loading_pont");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTexUI_Stage1Loading_pont::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pShaderCom);
}

