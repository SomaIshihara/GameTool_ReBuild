//==========================================
//
//デバッグ表示プログラムのヘッダ[debugproc.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CLASS_DEBUGPROC_H_
#define _CLASS_DEBUGPROC_H_

//マクロ
#define DEBPRO_MAX_STR	(2048)			//確保する文字数

class cDebugProc
{
public:
	cDebugProc();
	~cDebugProc();
	void DrawDebugProc(void);
	void PrintDebugProc(const char* fmt, ...);
private:
	LPD3DXFONT m_pFont = NULL;				//フォントへのポインタ
	char m_aStrPrint[DEBPRO_MAX_STR];		//表示文字バッファ
};

#endif // !_DEBUGPROC_H_
