#include "..\Public\Object_Manager.h"
#include "GameObject.h"
#include "Layer.h"
#include "GameInstance.h"

CObject_Manager::CObject_Manager()
{
}

CComponent* CObject_Manager::Get_Component(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strComponentTag, _uint iIndex)
{
	CLayer* pLayer = Find_Layer(iLevelIndex, strLayerTag);

	if (nullptr == pLayer)
		return nullptr;

	return pLayer->Get_Component(strComponentTag, iIndex);

	return nullptr;
}

HRESULT CObject_Manager::Initialize(_uint iNumLevels)
{
	if (nullptr != m_pLayers)
		return E_FAIL;

	m_iNumLevels = iNumLevels;

	m_pLayers = new LAYERS[iNumLevels];

	m_pGameInstance= CGameInstance::GetInstance();

	return S_OK;
}

HRESULT CObject_Manager::Add_Prototype_Object(const wstring & strPrototypeTag, CGameObject * pPrototype)
{
	if (nullptr == pPrototype || 
		nullptr != Find_Prototype(strPrototypeTag))
		return E_FAIL;

	m_Prototypes.emplace(strPrototypeTag, pPrototype);

	return S_OK;
}

HRESULT CObject_Manager::Add_CloneObject(_uint iLevelIndex, const wstring & strLayerTag, const wstring & strPrototypeTag, void * pArg)
{
	/* 원형을 찾고. */
	CGameObject*		pPrototype = Find_Prototype(strPrototypeTag);

	if (nullptr == pPrototype)
		return E_FAIL;

// 	CGameObject::GAMEOBJECT_DESC Desc = *(CGameObject::GAMEOBJECT_DESC*)pArg;
// 
// 	Desc.iLevelIndex = iLevelIndex;

	/* 원형을 복제하여 실제 게임내에 사용할 사본 객체를 생성해낸다.  */
	CGameObject*		pGameObject = pPrototype->Clone(pArg);
	if (nullptr == pGameObject)
		return E_FAIL;

	/* 만들어낸 사본객체를 추가해야할 레이어를 찾자. */
	CLayer*			pLayer = Find_Layer(iLevelIndex, strLayerTag);

	/* 아직 해당 이름을 가진 레이어가 없었다. */
	/* 이 이름을 가진 레이어에 최초로 추가하고 있는 상황이다. */
	if (nullptr == pLayer)
	{
		pLayer = CLayer::Create();
		if (nullptr == pLayer)
			return E_FAIL;

		pLayer->Add_GameObject(pGameObject);

		m_pLayers[iLevelIndex].emplace(strLayerTag, pLayer);
	}
	/* 이미 이름을 가진 레이어가 있었어. */
	else
		pLayer->Add_GameObject(pGameObject);
	
	return S_OK;
}

CGameObject* CObject_Manager::Clone_Prototype(const wstring& strPrototypeTag, void* pArg)
{
	CGameObject* pPrototype = Find_Prototype(strPrototypeTag);
	if (nullptr == pPrototype)
		return nullptr;

	return pPrototype->Clone(pArg);
}

HRESULT CObject_Manager::Add_Object(_uint iLevelIndex, const wstring& strLayerTag, CGameObject* pGameObject, void* pArg)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	/* 만들어낸 사본객체를 추가해야할 레이어를 찾자. */
	CLayer* pLayer = Find_Layer(iLevelIndex, strLayerTag);

	/* 아직 해당 이름을 가진 레이어가 없었다. */
	/* 이 이름을 가진 레이어에 최초로 추가하고 있는 상황이다. */
	if (nullptr == pLayer)
	{
		pLayer = CLayer::Create();
		if (nullptr == pLayer)
			return E_FAIL;

		pLayer->Add_GameObject(pGameObject);

		m_pLayers[iLevelIndex].emplace(strLayerTag, pLayer);
	}
	/* 이미 이름을 가진 레이어가 있었어. */
	else
		pLayer->Add_GameObject(pGameObject);

	return S_OK;
}

void CObject_Manager::Priority_Tick(_float fTimeDelta)
{
	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->Priority_Tick(fTimeDelta);		

			
		}
	}
}

void CObject_Manager::Tick(_float fTimeDelta)
{
	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])
			Pair.second->Tick(fTimeDelta);
	}
}

void CObject_Manager::Late_Tick(_float fTimeDelta)
{
	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->Late_Tick(fTimeDelta);

			//list<CGameObject*> pGameObjects = *Pair.second->Get_GameObjects();

// 			for (auto& pGameObject : pGameObjects)
// 			{
// 				if (true == pGameObject->Get_isdead())
// 				{
// 					Safe_Release(pGameObject);
// 					pGameObjects.erase(pGameObject);
// 				}
// 			}

		}
	}
}


void CObject_Manager::Clear(_uint iLevelIndex)
{
	for (auto& Pair : m_pLayers[iLevelIndex])
		Safe_Release(Pair.second);

	m_pLayers[iLevelIndex].clear();
}

list<class CGameObject*>* CObject_Manager::Get_GameObjects(_uint iLevelIndex, const wstring& strLayerTag)
{
	CLayer* layer = Find_Layer(iLevelIndex, strLayerTag);
	if (nullptr == layer)
		return nullptr;

	return layer->Get_GameObjects();
}

void CObject_Manager::Get_CloneGameObjects(_uint iLevelIndex, vector<CGameObject*>* clonevector)
{
	for (auto& item : m_pLayers[iLevelIndex]) 
	{
		
		list<CGameObject*> pGameObjects = *item.second->Get_GameObjects();
		for (auto& pGameObject : pGameObjects)
		{
			clonevector->push_back(pGameObject);
		}
	}
	//_bool test = false;
}

void CObject_Manager::Save_Objects_With_Json(_uint iLevelIndex, string filePath)
{
	json Out_Json;

	_ushort iIndex = 0;
	for (auto& Pair : m_pLayers[iLevelIndex])
	{
		list<class CGameObject*>* pGameObjects = Pair.second->Get_GameObjects();
		for (auto& pGameObject : *pGameObjects)
		{
			json object;
			pGameObject->Write_Json(object);
			Out_Json.emplace(to_string(iIndex++), object);
		}
	}

	CGameInstance::GetInstance()->Save_Json(filePath, Out_Json);
}

CGameObject* CObject_Manager::Get_Player()
{

	return m_pPlayer;
}

void CObject_Manager::Set_Player(CGameObject* _pPlayer)
{
	m_pPlayer = _pPlayer;
}

CGameObject* CObject_Manager::Get_Varg()
{
	return m_pVarg;
}

void CObject_Manager::Set_Varg(CGameObject* _pVarg)
{
	m_pVarg = _pVarg;
}

CGameObject* CObject_Manager::Get_Magician()
{
	return m_pMagician;
}

void CObject_Manager::Set_Magician(CGameObject* _pMagician)
{
	m_pMagician = _pMagician;
}

void CObject_Manager::Fill_PrototypeTags(vector<string>* _vector)
{
	for (auto& item : m_Prototypes) 
	{
		string key;
		m_pGameInstance->WString_To_String(item.first, key);

		_vector->push_back(key);
	}
}

void CObject_Manager::Fill_LayerTags(vector<string>* _vector)
{

}

CGameObject * CObject_Manager::Find_Prototype(const wstring & strPrototypeTag)
{
	auto	iter = m_Prototypes.find(strPrototypeTag);

	if (iter == m_Prototypes.end())
		return nullptr;

	return iter->second;
}

CLayer * CObject_Manager::Find_Layer(_uint iLevelIndex, const wstring & strLayerTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return nullptr;

	auto	iter = m_pLayers[iLevelIndex].find(strLayerTag);
	if (iter == m_pLayers[iLevelIndex].end())
		return nullptr;

	return iter->second;	
}

CObject_Manager * CObject_Manager::Create(_uint iNumLevels)
{
	CObject_Manager*		pInstance = new CObject_Manager;

	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX("Failed to Created : CObject_Manager");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CObject_Manager::Free()
{
	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pLayers[i])		
			Safe_Release(Pair.second);

		m_pLayers[i].clear();		
	}

	Safe_Delete_Array(m_pLayers);


	for (auto& Pair : m_Prototypes)
		Safe_Release(Pair.second);

	m_Prototypes.clear();
}
