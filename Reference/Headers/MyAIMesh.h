#pragma once
#include "Base.h"
#include "MyAIBone.h"
#include "MyAIFace.h"

BEGIN(Engine)

class ENGINE_DLL CMyAIMesh
{
public:
	CMyAIMesh() {};
	CMyAIMesh(aiMesh* _pMesh);
	CMyAIMesh(ifstream& is);

private:
	//_bool			m_bIsBianry = { false };
	//aiMesh*			m_pMesh = { nullptr };

	string mName;

	_uint mMaterialIndex;

	_uint mNumVertices;
	_uint mNumFaces;
	_uint mNumBones;

	vector<_float3> mVertices;
	vector<_float3> mNormals;
	vector<_float3> mTextureCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS];
	vector<_float3> mTangents;

	vector<CMyAIFace> mFaces;
	vector<CMyAIBone> mBones;


public:
	void Bake_Binary(ofstream& os)
	{
		write_typed_data(os, mName.size());
		os.write(&mName[0], mName.size());

		write_typed_data(os, mMaterialIndex);

		write_typed_data(os, mNumVertices);
		write_typed_data(os, mNumFaces);
		write_typed_data(os, mNumBones);


		for (_uint i = 0; i < mNumVertices; ++i)
		{
			write_typed_data(os, mVertices[i]);
		}

		for (_uint i = 0; i < mNumVertices; ++i)
		{
			write_typed_data(os, mNormals[i]);
		}

		for (_uint i = 0; i < mNumVertices; ++i)
		{
			write_typed_data(os, mTextureCoords[0][i]);
		}

		for (_uint i = 0; i < mNumVertices; ++i)
		{
			write_typed_data(os, mTangents[i]);
		}


		for (_uint i = 0; i < mNumFaces; ++i)
		{
			mFaces[i].Bake_Binary(os);
		}

		for (_uint i = 0; i < mNumBones; ++i)
		{
			mBones[i].Bake_Binary(os);
		}
	}

	_uint Get_MaterialIndex() { 
		//return m_pMesh->mMaterialIndex; 
		return mMaterialIndex;
	}

	string Get_Name() { 
		//return m_pMesh->mName.data; 
		return mName;
	}

	_uint Get_NumVertices() { 
		//return m_pMesh->mNumVertices; 
		return mNumVertices;
	}

	_uint Get_NumFaces() { 
		//return m_pMesh->mNumFaces; 
		return mNumFaces;
	}
	CMyAIFace Get_Face(_uint _iIndex) {
		//return m_pMesh->mFaces[_iIndex]; 
		return CMyAIFace(mFaces[_iIndex]);
	};


	_float3 Get_Vertice(_uint _iIndex) { 
		//_float3 _pVertices;
		//memcpy(&_pVertices, &m_pMesh->mVertices[_iIndex], sizeof(_float3));
		//return _pVertices;
		return mVertices[_iIndex];
	};

	_float3 Get_Normal(_uint _iIndex) {
		//_float3 _pNormal;
		//memcpy(&_pNormal, &m_pMesh->mNormals[_iIndex], sizeof(_float3));
		//return _pNormal;
		return mNormals[_iIndex];
	};

	_float3 Get_TextureCoord(_uint _iIndex) {
		//_float3 _TextureCoords;
		//memcpy(&_TextureCoords, &m_pMesh->mTextureCoords[0][_iIndex], sizeof(_float3));
		//return _TextureCoords;
		return mTextureCoords[0][_iIndex];
	};
	_float3 Get_Tangent(_uint _iIndex) { 
		//_float3 _Tangents;
		//memcpy(&_Tangents, &m_pMesh->mTangents[_iIndex], sizeof(_float3));
		//return _Tangents;
		return mTangents[_iIndex];
	};

	_uint Get_NumBones() { 
		//return m_pMesh->mNumBones; 
		return mNumBones;
	}

	CMyAIBone Get_Bone(_uint _iIndex) { 
		//return CMyAIBone(m_pMesh->mBones[_iIndex]); 
		return mBones[_iIndex];
	}
};

END