#include "..\Public\ForkLift_GamePlay.h"

CForkLift_GamePlay::CForkLift_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CForkLift(pDevice, pContext)
{
}

CForkLift_GamePlay::CForkLift_GamePlay(const CForkLift_GamePlay& rhs)
	: CForkLift(rhs)
{
}

HRESULT CForkLift_GamePlay::Ready_Components()
{
	if (FAILED(Ready_Components_Origin(LEVEL_GAMEPLAY)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_ForkLift"),
		TEXT("Com_Model"), reinterpret_cast<CComponent**>(&m_pModelCom))))
		return E_FAIL;

	return S_OK;
}

CForkLift_GamePlay* CForkLift_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CForkLift_GamePlay* pInstance = new CForkLift_GamePlay(pDevice, pContext);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CForkLift_GamePlay");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CForkLift_GamePlay* CForkLift_GamePlay::Clone(void* pArg)
{
	CForkLift_GamePlay* pInstance = new CForkLift_GamePlay(*this);

	/* 원형객체를 초기화한다.  */
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CForkLift");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CForkLift_GamePlay::Free()
{
	__super::Free();
}
