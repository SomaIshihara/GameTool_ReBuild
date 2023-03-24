//==========================================
//
//���f���֌W�v���O����[cModel.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
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

void cModel::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;	//�v�Z�p
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//���f���擾
	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&this->m_cModelStr.mtxWorld);

	//�I�t�Z�b�g�𑫂�
	//pos = this->m_cModelStr.posOffset;
	//rot = this->m_cModelStr.rotOffset;

	//�g�k�𔽉f
	//D3DXMatrixScaling(&mtxScall, FENCE_SCALE, FENCE_SCALE, FENCE_SCALE);
	//D3DXMatrixMultiply(&g_aFence[nCount].mtxWorld, &g_aFence[nCount].mtxWorld, &mtxScall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &this->m_cModelStr.mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)this->m_cModelStr.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)this->m_cModelStr.dwNumMatModel; nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, this->m_cModelStr.apTexture[nCntMat]);

		//���f���`��
		this->m_cModelStr.pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

cModelStruct cModel::GetModel(void)
{
	return this->m_cModelStr;
}