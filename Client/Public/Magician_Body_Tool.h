#pragma once

#include "Magician_Body.h"

BEGIN(Client)

class CMagician_Body_Tool final : public CMagician_Body
{
private:
	CMagician_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Body_Tool(const CMagician_Body_Tool& rhs);
	virtual ~CMagician_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CMagician_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END