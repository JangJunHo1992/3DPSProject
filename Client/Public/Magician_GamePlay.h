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
private:
	_bool	m_bLookAt = false;
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