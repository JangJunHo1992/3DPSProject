#pragma once

#include "Model.h"

BEGIN(Engine)

class ENGINE_DLL CModel_Tool final : public CModel
{
private:
	CModel_Tool(ID3D11Device* pDevice , ID3D11DeviceContext* pContext);
	CModel_Tool(const CModel_Tool& rhs);
	virtual ~CModel_Tool() = default;

public:
	virtual HRESULT	Ready_Meshes(_fmatrix PivotMatrix) override;

public:
	static CModel_Tool* Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, const MODEL_TYPE eType, const string & strModelFilePath, _fmatrix PivotMatrix);
	virtual CComponent* Clone(void* pArg) override;
	virtual void Free() override;
};

END
