#include "Mesh_Tool.h"
#include "GameInstance.h"

CMesh_Tool::CMesh_Tool(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    : CMesh(pDevice, pContext)
{
}

CMesh_Tool::CMesh_Tool(const CMesh_Tool& rhs)
    : CMesh(rhs)
{
}

HRESULT CMesh_Tool::Initialize_Prototype(CModel::TYPE eModelType, const aiMesh* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones)
{
    Initialize_Prototype_Origin(eModelType, pAIMesh, PivotMatrix, Bones);
    //Safe_Delete_Array(m_pIndices);
    return S_OK;
}

HRESULT CMesh_Tool::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    m_pGameInstance = CGameInstance::GetInstance();

    return S_OK;
}

HRESULT CMesh_Tool::Ready_Vertices_NonAnim(const aiMesh* pAIMesh, DirectX::XMMATRIX PivotMatrix)
{
    Ready_Vertices_NonAnim_Origin(pAIMesh, PivotMatrix);
    //Safe_Delete_Array(m_pVertices);
    return S_OK;
}

HRESULT CMesh_Tool::Ready_Vertices_Anim(const aiMesh* pAIMesh, const std::vector<Engine::CBone*, std::allocator<Engine::CBone*>>& Bones)
{
    Ready_Vertices_Anim_Origin(pAIMesh, Bones);
    //Safe_Delete_Array(m_pAnimVertices);
    return S_OK;
}

_bool CMesh_Tool::Picking(RAY ray, _float3* out)
{
    _uint triNum = m_iNumIndices / 3;

    return m_pGameInstance->Picking_Vertex(ray, out, triNum, m_pVertices, m_pIndices);
}

CMesh_Tool* CMesh_Tool::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CModel::TYPE eModelType, const aiMesh* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones)
{
    CMesh_Tool* pInstance = new CMesh_Tool(pDevice, pContext);

    if (FAILED(pInstance->Initialize_Prototype(eModelType, pAIMesh, PivotMatrix, Bones)))
    {
        MSG_BOX("Failed to Created : CMesh_Tool");
        Safe_Release(pInstance);
    }
    return pInstance;
}

CComponent* CMesh_Tool::Clone(void* pArg)
{
    return nullptr;
}

void CMesh_Tool::Free()
{
    if (false == m_isCloned)
    {
        Safe_Delete_Array(m_pIndices);
        Safe_Delete_Array(m_pVertices);
        Safe_Delete_Array(m_pAnimVertices);
    }

    __super::Free();
}


