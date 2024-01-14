#pragma once

#include "JobMob1_Body.h"

BEGIN(Client)

class CJobMob1_Body_GamePlay final : public CJobMob1_Body
{
private:
	CJobMob1_Body_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CJobMob1_Body_GamePlay(const CJobMob1_Body_GamePlay& rhs);
	virtual ~CJobMob1_Body_GamePlay() = default;

private:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CJobMob1_Body_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END