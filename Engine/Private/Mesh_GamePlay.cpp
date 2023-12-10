#include "..\Public\Mesh_GamePlay.h"

CMesh_GamePlay::CMesh_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
    : CMesh(pDevice, pContext)
{
}

CMesh_GamePlay::CMesh_GamePlay(const CMesh_GamePlay& rhs)
    : CMesh(rhs)
{
}

HRESULT CMesh_GamePlay::Initialize_Prototype(CModel::TYPE eModelType, const aiMesh* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones)
{
    Initialize_Prototype_Origin(eModelType, pAIMesh, PivotMatrix, Bones);
    Safe_Delete_Array(m_pIndices);
    return S_OK;
}

HRESULT CMesh_GamePlay::Ready_Vertices_NonAnim(const aiMesh* pAIMesh, DirectX::XMMATRIX PivotMatrix)
{
    Ready_Vertices_NonAnim_Origin(pAIMesh, PivotMatrix);
    Safe_Delete_Array(m_pVertices);
    return S_OK;
}


HRESULT CMesh_GamePlay::Ready_Vertices_Anim(const aiMesh* pAIMesh, const std::vector<Engine::CBone*, std::allocator<Engine::CBone*>>& Bones)
{
    Ready_Vertices_Anim_Origin(pAIMesh, Bones);
    Safe_Delete_Array(m_pAnimVertices);
    return S_OK;
}

CMesh_GamePlay* CMesh_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CModel::TYPE eModelType, const aiMesh* pAIMesh, _fmatrix PivotMatrix, const vector<class CBone*>& Bones)
{
    CMesh_GamePlay* pInstance = new CMesh_GamePlay(pDevice, pContext);

    if (FAILED(pInstance->Initialize_Prototype(eModelType, pAIMesh, PivotMatrix, Bones)))
    {
        MSG_BOX("Failed to Created : CMesh_GamePlay");
        Safe_Release(pInstance);
    }
    return pInstance;
}

CComponent* CMesh_GamePlay::Clone(void* pArg)
{
    return nullptr;
}

void CMesh_GamePlay::Free()
{
    //Safe_Delete_Array(m_pIndices);
    //Safe_Delete_Array(m_pVertices);
    //Safe_Delete_Array(m_pAnimVertices);

    __super::Free();
}


