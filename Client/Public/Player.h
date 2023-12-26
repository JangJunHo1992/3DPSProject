#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CNavigation;
<<<<<<< HEAD
class CShader;
class CModel;
=======
class CCollider;
>>>>>>> JJH
END

BEGIN(Client)

class CPlayer final : public CGameObject
{
<<<<<<< HEAD
public:
	typedef struct tagPlayerDesc : public GAMEOBJECT_DESC
	{
		int a;
	}PLAYER_DESC;
=======
>>>>>>> JJH
private:
	CPlayer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

<<<<<<< HEAD
private:
	CNavigation* m_pNavigationCom = { nullptr };
	CShader* m_pShaderCom = { nullptr };
	CModel* m_pModelCom = { nullptr };

private:
	HRESULT Ready_Components();
	HRESULT Bind_ShaderResources();
=======
public:
	CGameObject* Find_PartObject(const wstring& strPartTag);

private:
	CNavigation* m_pNavigationCom = { nullptr };
	CCollider* m_pColliderCom = { nullptr };

private:
	map<const wstring, class CGameObject*>		m_PartObjects;

private:
	HRESULT Ready_Components();
	HRESULT Ready_PartObjects();
	HRESULT Add_PartObject(const wstring& strPrototypeTag, const wstring& strPartTag, void* pArg);
>>>>>>> JJH


public:
	/* ������ü�� �����Ѵ�. */
	static CPlayer* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END