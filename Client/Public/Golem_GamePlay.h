#pragma once

#include "Golem.h"
#include "Actor.h"

BEGIN(Client)

class CGolem_GamePlay final : public CGolem
{
private:
	CGolem_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGolem_GamePlay(const CGolem_GamePlay& rhs);
	virtual ~CGolem_GamePlay() = default;

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
	CActor<CGolem_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CGolem_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGolem_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END