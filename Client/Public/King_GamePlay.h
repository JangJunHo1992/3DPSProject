#pragma once

#include "King.h"

BEGIN(Client)

class CKing_GamePlay final : public CKing
{
private:
	CKing_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CKing_GamePlay(const CKing_GamePlay& rhs);
	virtual ~CKing_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* 원형객체를 생성한다. */
	static CKing_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CKing_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END