//==========================================================================================
//
//���̓v���O�����̃w�b�_[input.h]
//Author:�Ό��D�n
//
//==========================================================================================
//Ver.3.0.0b�iC++�\�K���_�j
//�g�p�\�ȓ���:�L�[�{�[�h�E�}�E�X�i�J�[�\���ʒu�E�ړ��ʁj�E�Q�[���p�b�h�i1~4��j
//==========================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "..\..\Core\Main\main.h"

//==========================================================================================
// �}�N����`
//==========================================================================================
#define STICK_MAX			(32767)	//�X�e�B�b�N�ő�l
#define MOUSE_CLICK_LEFT	(0)		//�}�E�X���N���b�N
#define MOUSE_CLICK_RIGHT	(1)		//�}�E�X�E�N���b�N
#define MOUSE_BUTTON_MAX	(3)		//�}�E�X�{�^���̍ő吔
#define NUM_KEY_MAX			(256)	//�L�[�̍ő吔

//�Q�[���p�b�h�̃X�e�B�b�N�n
#define GAMEPAD_STICK_L		'L'
#define GAMEPAD_STICK_R		'R'
#define GAMEPAD_STICK_X		'X'
#define GAMEPAD_STICK_Y		'Y'

//==========================================================================================
// �񋓌^��`
//==========================================================================================
typedef enum
{
	INPUTTYPE_PRESS = 0,
	INPUTTYPE_TRIGGER,
	INPUTTYPE_RELEASE,
	INPUTTYPE_REPEATE,
	INPUTTYPE_MAX
} INPUTTYPE;

typedef enum
{
	GAMEPAD_NO_1 = 0,
	GAMEPAD_NO_2,
	GAMEPAD_NO_3,
	GAMEPAD_NO_4,
	MAX_USE_GAMEPAD
} GAMEPAD_NO;

//==========================================================================================
// �\���̒�`
//==========================================================================================
//�L�[�{�[�h
typedef struct
{
	BYTE state;		//��ԁi�ۑ��p����уv���X���j
	BYTE trigger;	//�g���K�[���
	BYTE release;	//�����[�X���
	BYTE repeate;	//���s�[�g���
	DWORD currentTime;	//���݂̎���
	DWORD execLastTime;	//�Ō��true�ɂ�������
} Keyboard;

//�Q�[���p�b�h
typedef struct
{
	XINPUT_STATE state;	//��ԑS���i����уv���X���j
	WORD trigger;		//�g���K�[���
	WORD release;		//�����[�X���
	WORD repeate;		//���s�[�g���
	DWORD currentTime;	//���݂̎���
	DWORD execLastTime;	//�Ō��true�ɂ�������
	bool bUse;			//�g�p�̗L��
} GamePad;

//�}�E�X�̃{�^����
typedef struct
{
	BYTE trigger;		//�{�^���̃g���K�[���
	BYTE release;		//�{�^���̃����[�X���
	BYTE repeate;		//���s�[�g���
	DWORD currentTime;	//���݂̎��ԁi���s�[�g�g�p�j
	DWORD execLastTime;	//�Ō��true��Ԃ������ԁi���s�[�g�g�p)
} MouseButton;

//�}�E�X���ׂ�
typedef struct
{
	MouseButton mb[MOUSE_BUTTON_MAX];	//�}�E�X�{�^��
	DIMOUSESTATE state;					//��Ԃ���уv���X���
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 move;					//�ړ���
} Mouse;

//==========================================================================================
// �N���X
//==========================================================================================
//=============================
// �L�[�{�[�h
//=============================
class cKeyboard
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	cKeyboard();
	~cKeyboard();

	//������
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	//�X�V
	void Update(void);

	//�擾
	bool GetKeyboard(INPUTTYPE type, int nKey);
private:
	//�擾�ɕK�v
	LPDIRECTINPUT8 m_pInputKeyboard;
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;

	//�ۑ��ꏊ
	static Keyboard m_Key[NUM_KEY_MAX];
};

//=============================
// �Q�[���p�b�h
//=============================
class cGamePad
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	cGamePad();
	~cGamePad();

	//������
	void Init(GAMEPAD_NO PadNum);

	//�j��
	void Release(void);

	//�X�V
	void Update(void);

	//�擾
	bool GetGamePadButton(INPUTTYPE type, int nButton);	//�{�^��
	bool GetGamePadStick(char location, char dir);		//�X�e�B�b�N
	static bool GetUseGamePad(GAMEPAD_NO PadNum);		//�g�p�̗L��
private:
	//�ۑ��ꏊ
	static GamePad m_Pad[MAX_USE_GAMEPAD];

	//�p�b�h�ԍ�
	GAMEPAD_NO m_PadNum;
};

//=============================
// �}�E�X
//=============================
class cMouse
{
	//�R���X�g���N�^�E�f�X�g���N�^
	cMouse();
	~cMouse();

	//������
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	//�X�V
	void Update(void);

	//�擾
	//�{�^��
	bool GetMouseClick(INPUTTYPE type, int button);

	//�ʒu
	D3DXVECTOR3 GetMousePos(void);

	//�ړ���
	D3DXVECTOR3 GetMouseMove(void);
private:
	//�擾�ɕK�v
	LPDIRECTINPUT8 m_pInputMouse;
	LPDIRECTINPUTDEVICE8 m_pDevMouse;

	//�ۑ��ꏊ
	Mouse m_Mouse;
};

#endif // !_INPUT_H_
