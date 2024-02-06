#include "stdafx.h"
#include "Boss_HPBar.h"
#include "GameInstance.h"
#include "Varg.h"


_bool		CBoss_HPBar::m_bCheckBossHPBar = false;
CBoss_HPBar::CBoss_HPBar(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject(pDevice, pContext)
{

}

CBoss_HPBar::CBoss_HPBar(const CBoss_HPBar& rhs)
	: CGameObject(rhs)
{
}

HRESULT CBoss_HPBar::Initialize_Prototype()
{
	/* 원형객체의 초기화과정을 수행한다. */
	/* 1.서버로부터 값을 받아와서 초기화한다 .*/
	/* 2.파일입출력을 통해 값을 받아온다.*/
	//int*		pData_int = new int(3);

	//void**		pData = (void**)&pData_int;

	return S_OK;
}

HRESULT CBoss_HPBar::Initialize(void* pArg)
{
	/* 백그라운드 객체가 사용할 Trnasform컴포넌트를 생성하여 추가해놓는다. */
	/*if (FAILED(__super::Initialize(&CGameObject::GAMEOBJECT_DESC(10.0f, 90.0f))))
		return E_FAIL;*/

	Boss_HPBar_DESC* pDesc = (Boss_HPBar_DESC*)pArg;

	m_fCurrentHP = pDesc->CurrentHP;
	m_fX = pDesc->fX;
	m_fY = pDesc->fY;
	m_fSizeX = pDesc->fSizeX;
	m_fSizeY = pDesc->fSizeY;


	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	// void* pArg : 복제하여 객체를 생성할때 원형에서 채우지 못한 데이터를 추가적으로 더 초기화해주기위해서. 
	if (m_pGameInstance->Get_NextLevel() == 2)
	{
		if (FAILED(Ready_Components(LEVEL_GAMEPLAY)))
			return E_FAIL;
	}
	else if (m_pGameInstance->Get_NextLevel() == 6)
	{
		if (FAILED(Ready_Components(LEVEL_BOSS1)))
			return E_FAIL;
	}
	else if (m_pGameInstance->Get_NextLevel() == 7)
	{
		if (FAILED(Ready_Components(LEVEL_BOSS2)))
			return E_FAIL;
	}

	//m_pPlayer = dynamic_cast<CCovus*>(m_pGameInstance->Get_Player());


	m_pTransformCom->Set_Scaling(m_fSizeX, m_fSizeY, 1.f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, XMVectorSet(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.02f, 1.f));

	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH(g_iWinSizeX, g_iWinSizeY, 0.f, 1.f));


	return S_OK;
}

void CBoss_HPBar::Priority_Tick(_float fTimeDelta)
{
	//list<CGameObject*>* playerList = m_pGameInstance->Get_GameObjects(m_pGameInstance->Get_NextLevel(), TEXT("Layer_Player"));
	//m_pPlayer = dynamic_cast<CCharacter*>((*playerList).back());
	//m_pGameInstance->Set_Player(m_pPlayer);


}

void CBoss_HPBar::Tick(_float fTimeDelta)
{
	m_fCurrentHP = CVarg::m_pVargHP;
	m_fRatio = m_fCurrentHP / m_fMaxHP;
	//m_pTransformCom->Set_Scaling(m_fSizeX * m_fRatio, m_fSizeY, 1.f);
	/*m_fRatio -= fRatio;*/

	if (m_fRatio <= 0.f)
		m_fRatio = 0.f;
}

void CBoss_HPBar::Late_Tick(_float fTimeDelta)
{
	if (FAILED(m_pGameInstance->Add_RenderGroup(CRenderer::RENDER_PRIORITY, this)))
		return;
}

HRESULT CBoss_HPBar::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	/* 이 셰ㅒ이더에 0번째 패스로 그릴꺼야. */
	m_pShaderCom->Begin(8);

	/* 내가 그릴려고하는 정점, 인덷ㄱ스버퍼를 장치에 바인딩해. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* 바인딩된 정점, 인덱스를 그려. */
	if(CBoss_HPBar::m_bCheckBossHPBar == true)
		m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CBoss_HPBar::Ready_Components(LEVEL eLevel)
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
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Texture_Boss_HPBar"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CBoss_HPBar::Bind_ShaderResources()
{

	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;
	if (FAILED(m_pTextureCom->Bind_ShaderResources(m_pShaderCom, "g_Texture")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_RawValue("g_fRatio", &m_fRatio, sizeof(_float))))
		return E_FAIL;

	return S_OK;
}
void CBoss_HPBar::Decrease_Ratio(_float fRatio)
{
	m_fRatio -= fRatio;

	if (m_fRatio <= 0.f)
		m_fRatio = 0.f;
}
CBoss_HPBar* CBoss_HPBar::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CBoss_HPBar* pInstance = new CBoss_HPBar(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CBoss_HPBar");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBoss_HPBar::Clone(void* pArg)
{
	CBoss_HPBar* pInstance = new CBoss_HPBar(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CBoss_HPBar");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBoss_HPBar::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pShaderCom);
}

