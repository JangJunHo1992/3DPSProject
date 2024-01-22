#pragma once

#include "JobMob2.h"
#include "Actor.h"

BEGIN(Client)

class CJobMob2_GamePlay final : public CJobMob2
{
private:
	CJobMob2_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob2_GamePlay(const CJobMob2_GamePlay& rhs);
	virtual ~CJobMob2_GamePlay() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Tick(_float fTimeDelta) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void Late_Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
public:
	_bool Get_bLookAt() { return m_bLookAt; }
	void  Set_bLookAt(_bool _bLookAt) { m_bLookAt = _bLookAt; }
private:
	_bool	m_bLookAt = false;

private:
	virtual HRESULT Ready_Components() override;

private:
	CActor<CJobMob2_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CJobMob2_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CJobMob2_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END