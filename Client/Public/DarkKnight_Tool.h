#pragma once

#include "DarkKnight.h"

BEGIN(Client)

class CDarkKnight_Tool final : public CDarkKnight
{
private:
	CDarkKnight_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CDarkKnight_Tool(const CDarkKnight_Tool& rhs);
	virtual ~CDarkKnight_Tool() = default;

public:
	virtual HRESULT Initialize(void* pArg) override;
	virtual _bool Pick(_float3* out) override;

private:
	virtual HRESULT Ready_Components() override;

public:
	/* ������ü�� �����Ѵ�. */
	static CDarkKnight_Tool* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

	/* �纻��ü�� �����Ѵ�. */
	virtual CDarkKnight_Tool* Clone(void* pArg) override;

	virtual void Free() override;

private:
	class CGameInstance* m_pGameInstance = nullptr;


};

END