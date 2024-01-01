#pragma once

#include "Player.h"

BEGIN(Client)

class CPlayer_Tool final : public CPlayer
{
private:
	CPlayer_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPlayer_Tool(const CPlayer_Tool& rhs);
	virtual ~CPlayer_Tool() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	virtual HRESULT Ready_Components() override;


public:
	/* ������ü�� �����Ѵ�. */
	static CPlayer_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END