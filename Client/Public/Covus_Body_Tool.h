#pragma once

#include "Covus_Body.h"

BEGIN(Client)

class CCovus_Body_Tool final : public CCovus_Body
{
private:
	CCovus_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CCovus_Body_Tool(const CCovus_Body_Tool& rhs);
	virtual ~CCovus_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CCovus_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END