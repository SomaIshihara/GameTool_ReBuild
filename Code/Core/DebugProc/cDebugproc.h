//==========================================
//
//�f�o�b�O�\���v���O�����̃w�b�_[debugproc.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CLASS_DEBUGPROC_H_
#define _CLASS_DEBUGPROC_H_

//�}�N��
#define DEBPRO_MAX_STR	(2048)			//�m�ۂ��镶����

class cDebugProc
{
public:
	cDebugProc();
	~cDebugProc();
	void DrawDebugProc(void);
	void PrintDebugProc(const char* fmt, ...);
private:
	LPD3DXFONT m_pFont = NULL;				//�t�H���g�ւ̃|�C���^
	char m_aStrPrint[DEBPRO_MAX_STR];		//�\�������o�b�t�@
};

#endif // !_DEBUGPROC_H_
