//==========================================
//
//���f���֌W�v���O����[cModel.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "cModel.h"

cModel::cModel()
{
	this->m_cModelStr = {};
}

cModel::~cModel()
{
	//���b�V���̔j��
	if (this->m_cModelStr.pMesh != NULL)
	{
		this->m_cModelStr.pMesh->Release();
		this->m_cModelStr.pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (this->m_cModelStr.pBuffMat != NULL)
	{	
		this->m_cModelStr.pBuffMat->Release();
		this->m_cModelStr.pBuffMat = NULL;
	}
}

void cModel::LoadModel(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	D3DXLoadMeshFromX(
		pPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&this->m_cModelStr.pBuffMat,
		NULL,
		&this->m_cModelStr.dwNumMatModel,
		&this->m_cModelStr.pMesh);

	//�e�N�X�`���ǂݍ���
	D3DXMATERIAL* pMat;	//�}�e���A���|�C���^

	//�}�e���A�����ɑ΂���|�C���^�擾
	pMat = (D3DXMATERIAL*)this->m_cModelStr.pBuffMat->GetBufferPointer();

	for (int nCntTex = 0; nCntTex < (int)this->m_cModelStr.dwNumMatModel; nCntTex++)
	{
		if (pMat[nCntTex].pTextureFilename != NULL)
		{
			//�e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntTex].pTextureFilename,
				&this->m_cModelStr.apTexture[nCntTex]);
		}
	}
}

cModelStruct cModel::GetModel(void)
{
	return this->m_cModelStr;
}