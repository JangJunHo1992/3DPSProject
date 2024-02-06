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
	/* ������ü�� �ʱ�ȭ������ �����Ѵ�. */
	/* 1.�����κ��� ���� �޾ƿͼ� �ʱ�ȭ�Ѵ� .*/
	/* 2.����������� ���� ���� �޾ƿ´�.*/
	//int*		pData_int = new int(3);

	//void**		pData = (void**)&pData_int;

	return S_OK;
}

HRESULT CBoss_HPBar::Initialize(void* pArg)
{
	/* ��׶��� ��ü�� ����� Trnasform������Ʈ�� �����Ͽ� �߰��س��´�. */
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

	// void* pArg : �����Ͽ� ��ü�� �����Ҷ� �������� ä���� ���� �����͸� �߰������� �� �ʱ�ȭ���ֱ����ؼ�. 
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

	/* �� �Τ��̴��� 0��° �н��� �׸�����. */
	m_pShaderCom->Begin(8);

	/* ���� �׸������ϴ� ����, �ΉK�������۸� ��ġ�� ���ε���. */
	m_pVIBufferCom->Bind_VIBuffers();

	/* ���ε��� ����, �ε����� �׷�. */
	if(CBoss_HPBar::m_bCheckBossHPBar == true)
		m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CBoss_HPBar::Ready_Components(LEVEL eLevel)
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

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
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

	/* ������ü�� �ʱ�ȭ�Ѵ�.  */
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

