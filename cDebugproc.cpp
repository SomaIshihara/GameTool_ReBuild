//==========================================
//
//�f�o�b�O�\���v���O����[debugproc.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "cDebugproc.h"
#include "input.h"
#include <stdio.h>
#include <stdarg.h>

//========================
//�R���X�g���N�^�i�����������j
//========================
cDebugProc::cDebugProc()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�f�o�b�O�\���p�t�H���g����
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &this->m_pFont);

	//�o�b�t�@�N���A
	memset(&this->m_aStrPrint, 0, sizeof this->m_aStrPrint);
}

//========================
//�f�X�g���N�^�i�I�������j
//========================
cDebugProc::~cDebugProc()
{
	//�t�H���g�j��
	if (this->m_pFont != NULL)
	{
		this->m_pFont->Release();
		this->m_pFont = NULL;
	}
}

//========================
//�`�揈��
//========================
void cDebugProc::DrawDebugProc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	
	//�e�L�X�g�`��
	this->m_pFont->DrawText(NULL, &this->m_aStrPrint[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));

	//�o�b�t�@�N���A
	memset(&this->m_aStrPrint, 0, sizeof this->m_aStrPrint);
}

//========================
//���͎�荞�ݏ���
//========================
void cDebugProc::PrintDebugProc(const char *fmt, ...)
{
	int nCount;		//�J�E���^
	va_list args;	//�ψ����̒��g

	//�o�͊J�n
	va_start(args, fmt);

	for (nCount = 0; *fmt != '\0'; fmt++)
	{
		if (*fmt == '%')
		{
			char aStr[10] = {};
			switch (*(fmt + 1))
			{
			case 'd':
				sprintf(&aStr[0], "%d", va_arg(args, int));
				snprintf(&this->m_aStrPrint[0], sizeof this->m_aStrPrint, "%s%s", &this->m_aStrPrint[0], &aStr[0]);
				fmt++;
				break;
			case 'f':
				sprintf(&aStr[0], "%.2f", va_arg(args, double));
				snprintf(&this->m_aStrPrint[0], sizeof this->m_aStrPrint, "%s%s", &this->m_aStrPrint[0], &aStr[0]);
				fmt++;
				break;
			case 'c':
				strcat(&this->m_aStrPrint[0], &va_arg(args, char));
				fmt++;
				break;
			case 's':
				strcat(&this->m_aStrPrint[0], va_arg(args, const char*));
				fmt++;
				break;
			default:
				strcat(&this->m_aStrPrint[0], "< ERROR >");
				break;
			}
		}
		else
		{
			char cData = *fmt;
			snprintf(&this->m_aStrPrint[0], sizeof this->m_aStrPrint, "%s%c", &this->m_aStrPrint[0], cData);
		}
	}

	va_end(args);
}