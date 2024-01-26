#pragma once

#include "Magician_Cane.h"

BEGIN(Client)

class CMagician_Cane_GamePlay final : public CMagician_Cane
{
protected:
	CMagician_Cane_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CMagician_Cane_GamePlay(const CMagician_Cane_GamePlay& rhs);
	virtual ~CMagician_Cane_GamePlay() = default;

protected:
	virtual HRESULT Ready_Components() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	/* ������ü�� �����Ѵ�. */
	static CMagician_Cane_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CGameObject* Clone(void* pArg) override;

	virtual void Free() override;


};

END
