#pragma once

#include "JobMob1_Body.h"

BEGIN(Client)

class CJobMob1_Body_Tool final : public CJobMob1_Body
{
private:
	CJobMob1_Body_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob1_Body_Tool(const CJobMob1_Body_Tool& rhs);
	virtual ~CJobMob1_Body_Tool() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* 원형객체를 생성한다. */
	static CJobMob1_Body_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* 사본객체를 생성한다. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;

};

END