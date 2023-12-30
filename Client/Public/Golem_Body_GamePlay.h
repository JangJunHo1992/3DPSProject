#pragma once

#include "Golem_Body.h"

BEGIN(Client)

class CGolem_Body_GamePlay final : public CGolem_Body
{
private:
	CGolem_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGolem_Body_GamePlay(const CGolem_Body_GamePlay& rhs);
	virtual ~CGolem_Body_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CGolem_Body_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END