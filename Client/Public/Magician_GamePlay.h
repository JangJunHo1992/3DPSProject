#pragma once

#include "Magician.h"
#include "Actor.h"

BEGIN(Client)

class CMagician_GamePlay final : public CMagician
{
private:
	CMagician_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_GamePlay(const CMagician_GamePlay& rhs);
	virtual ~CMagician_GamePlay() = default;

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

	_bool Get_bCheckStart() { return m_bCheckStart; }
	void  Set_bCheckStart(_bool _bCheckStart) { m_bCheckStart = _bCheckStart; }

	_bool Get_bCheckShoot() { return m_bCheckShoot; }
	void  Set_bCheckShoot(_bool _bCheckShoot) { m_bCheckShoot = _bCheckShoot; }

	_bool Get_bCheckRender() { return m_bCheckRender; }
	void  Set_bCheckRender(_bool _bCheckRender) { m_bCheckRender = _bCheckRender; }
private:
	_bool	m_bLookAt = false;
	_bool   m_bCheckStart = true;
	_bool   m_bCheckShoot = false;
	_bool   m_bCheckRender = true;
protected:
	virtual void Set_Dead() override;
private:
	virtual HRESULT Ready_Components() override;
public:
	void Create_Card();
private:
	CActor<CMagician_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CMagician_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CMagician_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END