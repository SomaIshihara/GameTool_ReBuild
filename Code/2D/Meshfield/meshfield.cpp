//==========================================
//
//�|���S���֌W�v���O����[meshfield.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "meshfield.h"

//�v���g
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx, int width);

//========================
//����������
//========================
cMeshfield::cMeshfield()
{
	//�ϐ�������
	this->m_meshData.m_pos = INIT_ZERO;
	this->m_meshData.m_rot = INIT_ZERO;
}

//========================
//�I������
//========================
cMeshfield::~cMeshfield()
{
	//�e�N�X�`���̔j��
	if (this->m_meshData.m_pTexture != (LPDIRECT3DTEXTURE9)0xcccccccc)
	{
		this->m_meshData.m_pTexture->Release();
		this->m_meshData.m_pTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (this->m_meshData.m_pVtxbuff != (LPDIRECT3DVERTEXBUFFER9)0xcccccccc)
	{
		this->m_meshData.m_pVtxbuff->Release();
		this->m_meshData.m_pVtxbuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�j��
	if (this->m_meshData.m_pIdxBuff != NULL)
	{
		this->m_meshData.m_pIdxBuff->Release();
		this->m_meshData.m_pIdxBuff = NULL;
	}
}

//========================
//�X�V����
//========================
void cMeshfield::Update(void)
{
	//��
}

//========================
//�`�揈��
//========================
void cMeshfield::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&this->m_meshData.m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->m_meshData.m_rot.y, this->m_meshData.m_rot.x, this->m_meshData.m_rot.z);
	D3DXMatrixMultiply(&this->m_meshData.m_mtxWorld, &this->m_meshData.m_mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, this->m_meshData.m_pos.x, this->m_meshData.m_pos.y, this->m_meshData.m_pos.z);
	D3DXMatrixMultiply(&this->m_meshData.m_mtxWorld, &this->m_meshData.m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &this->m_meshData.m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, this->m_meshData.m_pVtxbuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(this->m_meshData.m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���ݒ�
	if (this->m_meshData.m_pTexture != (LPDIRECT3DTEXTURE9)0xcccccccc)
	{
		pDevice->SetTexture(0, this->m_meshData.m_pTexture);
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	//�|���S���`��i�C���f�b�N�X���ꂽ��j
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (this->m_meshData.m_width + 1) * (this->m_meshData.m_height + 1), 0, 
		((((this->m_meshData.m_width + 1) * this->m_meshData.m_height * 2) + (2 * (this->m_meshData.m_height - 1))) - 2));
}

//========================
//���b�V���t�B�[���h�z�u����
//========================
void cMeshfield::SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pPath, int width, int height,float length)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�ϐ��ݒ�
	this->m_meshData.m_pos = pos;
	this->m_meshData.m_rot = rot;
	this->m_meshData.m_width = width;
	this->m_meshData.m_height = height;
	this->m_meshData.m_length = length;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pPath,
		&this->m_meshData.m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * (this->m_meshData.m_width + 1) * (this->m_meshData.m_height + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&this->m_meshData.m_pVtxbuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((this->m_meshData.m_width + 1) * this->m_meshData.m_height * 2) + (2 * (this->m_meshData.m_height - 1))),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&this->m_meshData.m_pIdxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//�o�b�t�@���b�N
	//���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	this->m_meshData.m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W+�e�N�X�`�����W
	for (int nCount = 0; nCount < (this->m_meshData.m_height + 1) * (this->m_meshData.m_height + 1); nCount++, pVtx++)
	{
		//���_���W�i���΍��W�j
		pVtx->pos = D3DXVECTOR3(this->m_meshData.m_length * (nCount % (this->m_meshData.m_height + 1)), 0.0f, -this->m_meshData.m_length * (nCount / (this->m_meshData.m_height + 1)));

		//�@���x�N�g��
		pVtx->nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//�J���[
		pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx->tex = D3DXVECTOR2(((float)(nCount % (this->m_meshData.m_height + 1)) / (this->m_meshData.m_height)), ((float)(nCount / (this->m_meshData.m_height + 1)) / (this->m_meshData.m_height)));
	}

	//���_�o�b�t�@���A�����b�N
	this->m_meshData.m_pVtxbuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	WORD *pIdx;	//�C���f�b�N�X���ւ̃|�C���^
	int nCntWidth = 0;	//�C���f�b�N�X�J�E���^

	//�o�b�t�@���b�N
	this->m_meshData.m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	for (; nCntWidth < this->m_meshData.m_height - 1; nCntWidth++)
	{
		//�O�l�O�l�p�[�g
		pIdx = SetIdxSwaingField(nCntWidth, pIdx, this->m_meshData.m_height);

		//�`�����ł�����p�[�g
		//�Ō�̃C���f�b�N�X�������̂ɂ������
		*pIdx = this->m_meshData.m_height + (this->m_meshData.m_height + 1) * nCntWidth;
		pIdx++;

		//���̎��̂Ɏ��̃��[�v�ōŏ��ɓ��鐔��������
		*pIdx = (this->m_meshData.m_height + 1) + (this->m_meshData.m_height + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//�Ō�̃O�l�O�l�p�[�g
	SetIdxSwaingField(nCntWidth, pIdx, this->m_meshData.m_height);

	//�o�b�t�@�A�����b�N
	this->m_meshData.m_pIdxBuff->Unlock();
}

//========================
//�O�l�O�l�C���f�b�N�X�ݒ菈��
//========================
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx,int width)
{
	//�O�l�O�l�p�[�g
	for (int nCountHeight = 0; nCountHeight < (width + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (width + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (width + 1) * nCntWidth;
	}
	return pIdx;
}