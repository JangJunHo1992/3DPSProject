#pragma once

#include "Base.h"

/* ������ ���� ��ü�� ��Ƴ��´�. (������Ÿ��) */
/* ������ü�� �����Ͽ� ������ �纻��ü�� ���̾�� �����Ͽ� ��Ƴ��´�. */
/* �����ϰ� �ִ� �纻��ü���� Tick���� �Լ��� �ݺ������� ȣ�����ش�.  */



BEGIN(Engine)
class CGameObject;
class CLayer;
class CObject_Manager final : public CBase
{
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	class CComponent* Get_Component(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strComponentTag, _uint iIndex);

public:
	HRESULT Initialize(_uint iNumLevels);
	HRESULT Add_Prototype_Object(const wstring& strPrototypeTag, CGameObject* pPrototype);
	HRESULT Add_CloneObject(_uint iLevelIndex, const wstring& strLayerTag, const wstring& strPrototypeTag, void* pArg);
	CGameObject* Clone_Prototype(const wstring& strPrototypeTag, void* pArg);
	HRESULT Add_Object(_uint iLevelIndex, const wstring& strLayerTag, CGameObject* pGameObject ,void* pArg);
	void Priority_Tick(_float fTimeDelta);
	void Tick(_float fTimeDelta);
	void Late_Tick(_float fTimeDelta);
	void Clear(_uint iLevelIndex);

public:
	list<CGameObject*>* Get_GameObjects(_uint iLevelIndex, const wstring& strLayerTag);
	void Get_CloneGameObjects(_uint iLevelIndex, vector<CGameObject*>* clonevector);
	void Fill_PrototypeTags(vector<string>* _vector);
	void Fill_LayerTags(vector<string>* _vector);
public:
	void Save_Objects_With_Json(_uint iLevelIndex, string filePath);

public:
	CGameObject* Get_Player();
	void	Set_Player(CGameObject* _pPlayer);
public:
	CGameObject*	m_pPlayer = { nullptr };
private:
	_uint			m_iNumLevels = { 0 };

	class CGameInstance*		m_pGameInstance = { nullptr };
private:
	map<const wstring, CGameObject*>			m_Prototypes;
	map<const wstring, CLayer*>*				m_pLayers = { nullptr } ;
	typedef map<const wstring, CLayer*>		LAYERS;

private:
	CGameObject* Find_Prototype(const wstring& strPrototypeTag);
	CLayer* Find_Layer(_uint iLevelIndex, const wstring& strLayerTag);
public:
	static CObject_Manager* Create(_uint iNumLevels);
	virtual void Free() override;
};

END