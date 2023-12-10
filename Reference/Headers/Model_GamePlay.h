#pragma once

#include "Model.h"

BEGIN(Engine)

class ENGINE_DLL CModel_GamePlay final : public CModel
{
private:
	CModel_GamePlay(ID3D11Device * pDevice , ID3D11DeviceContext * pContext);
	CModel_GamePlay(const CModel_GamePlay& rhs);
	virtual ~CModel_GamePlay() = default;

public:
	virtual HRESULT	Ready_Meshes(_fmatrix PivotMatrix) override;

public:
	static CModel_GamePlay* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, TYPE eType, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
