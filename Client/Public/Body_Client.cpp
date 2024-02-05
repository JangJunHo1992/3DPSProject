#include "stdafx.h"
#include "Body_Client.h"

HRESULT CBody_Client::Ready_Components_Origin(LEVEL eLevel)
{
	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(eLevel, TEXT("Prototype_Component_Shader_AnimModel"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	if (FAILED(__super::Add_Component(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dissolve"),
		TEXT("Com_DissolveTexture"), reinterpret_cast<CComponent**>(&m_pDissolveTexture))))
		return E_FAIL;

    return S_OK;
}
