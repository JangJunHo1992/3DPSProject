#pragma once

#include "Varg.h"
#include "Actor.h"

BEGIN(Client)

class CVarg_GamePlay final : public CVarg
{
private:
	CVarg_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVarg_GamePlay(const CVarg_GamePlay& rhs);
	virtual ~CVarg_GamePlay() = default;

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
private:
	_bool	m_bLookAt = false;
	_bool   m_bCheckStart = true;
private:
	virtual HRESULT Ready_Components() override;
protected:
	virtual void Set_Dead() override;

private:
	CActor<CVarg_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CVarg_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CVarg_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END