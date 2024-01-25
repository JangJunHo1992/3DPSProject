#pragma once

#include "Magician_Card.h"

BEGIN(Client)

class CMagician_Card_GamePlay final : public CMagician_Card
{
protected:
	CMagician_Card_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Card_GamePlay(const CMagician_Card_GamePlay& rhs);
	virtual ~CMagician_Card_GamePlay() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CMagician_Card_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END