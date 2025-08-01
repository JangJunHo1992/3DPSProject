#include "Layer.h"
#include "GameObject.h"

CLayer::CLayer()
{

}

CComponent* CLayer::Get_Component(const wstring& strComponentTag, _uint iIndex)
{
	auto	iter = m_GameObjects.begin();

	for (size_t i = 0; i < iIndex; i++)
		++iter;

	return (*iter)->Find_Component(strComponentTag);
}


HRESULT CLayer::Add_GameObject(CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_GameObjects.push_back(pGameObject);

	return S_OK;
}

void CLayer::Priority_Tick(_float fTimeDelta)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (nullptr != pGameObject)
			pGameObject->Priority_Tick(fTimeDelta);
	}	
}

void CLayer::Tick(_float fTimeDelta)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (nullptr != pGameObject)
			pGameObject->Tick(fTimeDelta);
	}
}

void CLayer::Late_Tick(_float fTimeDelta)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (nullptr != pGameObject)
			pGameObject->Late_Tick(fTimeDelta);

		 for (auto iter = m_GameObjects.begin(); iter != m_GameObjects.end();)
		{
			if ((*iter)->Get_isdead() == true)
			{
				Safe_Release((*iter));
				iter = m_GameObjects.erase(iter);

			}
			else
			{
				++iter;
			}
		}
	}
}

CLayer * CLayer::Create()
{
	return new CLayer;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_GameObjects)
		Safe_Release(pGameObject);

	m_GameObjects.clear();
}
