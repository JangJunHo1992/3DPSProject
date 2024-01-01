#pragma once
#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CMyAINode
{
public:
	CMyAINode() {};
	CMyAINode(aiNode* _pNode);
	CMyAINode(ifstream& is);


private:
	//_bool			m_bIsBianry = { false };
	//aiNode*				m_pNode = { nullptr };

	string				mName;

	_uint				mNumChildren = 0;
	_float4x4			mTransformation;

	vector<CMyAINode>	mChildren;


public:
	void Bake_Binary(ofstream& os)
	{
		write_typed_data(os, mName.size());
		os.write(&mName[0], mName.size());

		write_typed_data(os, mNumChildren);
		write_typed_data(os, mTransformation);

		for (_uint i = 0; i < mNumChildren; ++i) 
		{
			mChildren[i].Bake_Binary(os);
		}
	}

	string Get_Name() {
		//mName = m_pNode->mName.data;
		return mName;
	};

	_float4x4 Get_Transformation() 
	{
		//memcpy(&mTransformation, &m_pNode->mTransformation, sizeof(_float4x4));
		return mTransformation;
	}

	_uint	Get_NumChildren() {
		//mNumChildren = m_pNode->mNumChildren;
		return mNumChildren;
	};

	CMyAINode Get_Children(_uint _iIndex) {
		//return CMyAINode(m_pNode->mChildren[_iIndex]);
		return mChildren[_iIndex];
	};

};

END