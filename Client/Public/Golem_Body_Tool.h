#pragma once

#include "Golem_Body.h"

BEGIN(Client)

class CGolem_Body_Tool final : public CGolem_Body
{
private:
	CGolem_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CGolem_Body_Tool(const CGolem_Body_Tool& rhs);
	virtual ~CGolem_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CGolem_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END