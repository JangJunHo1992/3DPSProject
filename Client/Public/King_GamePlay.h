#pragma once

#include "King.h"
#include "Actor.h"

BEGIN(Client)

class CKing_GamePlay final : public CKing
{
private:
	CKing_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKing_GamePlay(const CKing_GamePlay& rhs);
	virtual ~CKing_GamePlay() = default;

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
	CActor<CKing_GamePlay>* m_pActor = { nullptr };

public:
	/* 원형객체를 생성한다. */
	static CKing_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CKing_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END