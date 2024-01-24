#pragma once

#include "JobMob2_Body.h"

BEGIN(Client)

class CJobMob2_Body_Tool final : public CJobMob2_Body
{
private:
	CJobMob2_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob2_Body_Tool(const CJobMob2_Body_Tool& rhs);
	virtual ~CJobMob2_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CJobMob2_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END