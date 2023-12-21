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
	/* ������ü�� �����Ѵ�. */
	static CKing_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CKing_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END