#pragma once

#include "Golem.h"

BEGIN(Client)

class CGolem_GamePlay final : public CGolem
{
private:
	CGolem_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGolem_GamePlay(const CGolem_GamePlay& rhs);
	virtual ~CGolem_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CGolem_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGolem_GamePlay* Clone(void* pArg) override;

	virtual void Free() override;


};

END