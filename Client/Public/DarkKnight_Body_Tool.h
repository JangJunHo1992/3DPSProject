#pragma once

#include "DarkKnight_Body.h"

BEGIN(Client)

class CDarkKnight_Body_Tool final : public CDarkKnight_Body
{
private:
	CDarkKnight_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CDarkKnight_Body_Tool(const CDarkKnight_Body_Tool& rhs);
	virtual ~CDarkKnight_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CDarkKnight_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END