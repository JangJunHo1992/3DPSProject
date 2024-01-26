#pragma once

#include "Magician_Card.h"

BEGIN(Client)

class CMagician_Card_Tool final : public CMagician_Card
{
protected:
	CMagician_Card_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Card_Tool(const CMagician_Card_Tool& rhs);
	virtual ~CMagician_Card_Tool() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CMagician_Card_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END
