#pragma once

#include "Player.h"

BEGIN(Client)

class CPlayer_GamePlay final : public CPlayer
{
private:
	CPlayer_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPlayer_GamePlay(const CPlayer_GamePlay& rhs);
	virtual ~CPlayer_GamePlay() = default;

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
	static CPlayer_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;
};

END