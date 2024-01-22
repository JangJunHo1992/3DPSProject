#pragma once

#include "JobMob1.h"
#include "Actor.h"

BEGIN(Client)

class CJobMob1_GamePlay final : public CJobMob1
{
private:
	CJobMob1_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob1_GamePlay(const CJobMob1_GamePlay& rhs);
	virtual ~CJobMob1_GamePlay() = default;

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
protected:
	virtual void Set_Dead() override;
private:
	virtual HRESULT Ready_Components() override;

private:
	CActor<CJobMob1_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CJobMob1_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CJobMob1_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END