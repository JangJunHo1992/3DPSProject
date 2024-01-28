#include "Magician_Card_Bullet_GamePlay.h"

CMagician_Card_Bullet_GamePlay::CMagician_Card_Bullet_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CMagician_Card_Bullet(pDevice, pContext)
{
}

CMagician_Card_Bullet_GamePlay::CMagician_Card_Bullet_GamePlay(const CMagician_Card_Bullet_GamePlay& rhs)
	: CMagician_Card_Bullet(rhs)
{
}

HRESULT CMagician_Card_Bullet_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_BOSS2)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_BOSS2, TEXT("Prototype_Component_Model_Magician_Card_Bullet"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CMagician_Card_Bullet_GamePlay* CMagician_Card_Bullet_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CMagician_Card_Bullet_GamePlay* pInstance = new CMagician_Card_Bullet_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CMagician_Card_Bullet_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CMagician_Card_Bullet_GamePlay* CMagician_Card_Bullet_GamePlay::Clone(void* pArg)
{
	CMagician_Card_Bullet_GamePlay* pInstance = new CMagician_Card_Bullet_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CMagician_Card_Bullet");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician_Card_Bullet_GamePlay::Free()
{
	__super::Free();
}
