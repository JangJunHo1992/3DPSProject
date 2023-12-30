#pragma once

#include "KnightGuard.h"
#include "Actor.h"

BEGIN(Client)

class CKnightGuard_GamePlay final : public CKnightGuard
{
private:
	CKnightGuard_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKnightGuard_GamePlay(const CKnightGuard_GamePlay& rhs);
	virtual ~CKnightGuard_GamePlay() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	virtual void Set_Hitted() override;

private:
	virtual HRESULT Ready_Components() override;

private:
	CActor<CKnightGuard_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CKnightGuard_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CKnightGuard_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END