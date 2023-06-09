//==========================================
//
//デバッグ表示プログラム[debugproc.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "cDebugproc.h"
#include <stdio.h>
#include <stdarg.h>

//========================
//コンストラクタ（初期化処理）
//========================
cDebugProc::cDebugProc()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//デバッグ表示用フォント生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &this->m_pFont);

	//バッファクリア
	memset(&this->m_aStrPrint, 0, sizeof this->m_aStrPrint);
}

//========================
//デストラクタ（終了処理）
//========================
cDebugProc::~cDebugProc()
{
	//フォント破棄
	if (this->m_pFont != NULL)
	{
		this->m_pFont->Release();
		this->m_pFont = NULL;
	}
}

//========================
//描画処理
//========================
void cDebugProc::DrawDebugProc(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	
	//テキスト描画
	this->m_pFont->DrawText(NULL, &this->m_aStrPrint[0], -1, &rect, DT_LEFT,
		D3DCOLOR_RGBA(255, 255, 255, 255));

	//バッファクリア
	memset(&this->m_aStrPrint, 0, sizeof this->m_aStrPrint);
}

//========================
//入力取り込み処理
//========================
void cDebugProc::PrintDebugProc(const char *fmt, ...)
{
	int nCount;		//カウンタ
	va_list args;	//可変引数の中身

	//出力開始
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