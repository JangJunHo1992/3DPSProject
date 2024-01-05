#pragma once

#include "Varg_Body.h"

BEGIN(Client)

class CVarg_Body_Tool final : public CVarg_Body
{
private:
	CVarg_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CVarg_Body_Tool(const CVarg_Body_Tool& rhs);
	virtual ~CVarg_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CVarg_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END