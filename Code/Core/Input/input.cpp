//==========================================================================================
//
//���̓v���O����[input.cpp]
//Author:�Ό��D�n
//
//==========================================================================================
//Ver.3.0.0b�iC++�\�K���_�j
//�g�p�\�ȓ���:�L�[�{�[�h�E�}�E�X�i�J�[�\���ʒu�E�ړ��ʁj�E�Q�[���p�b�h�i1~4��j
//==========================================================================================
#include "input.h"
#include "..\..\Core\Sound\sound.h"

//�}�N����`
#define REPEATE_TIME		(150)	//���s�[�g�̊Ԋu
#define GAMEPAD_BUTTON_NUM	(14)	//�Q�[���p�b�h�̃{�^����
#define STICK_DEADZONE		(655)	//�V��

//�ÓI�����o�\���̂��`
Keyboard cKeyboard::m_Key[NUM_KEY_MAX];
GamePad cGamePad::m_Pad[MAX_USE_GAMEPAD];
Mouse cMouse::m_Mouse;

//�v���g
void AdjustStick(SHORT* pStick);

//==================================================
//						�L�[�{�[�h
//==================================================
//========================
//�L�[�{�[�h�R���X�g���N�^�i���͉������Ȃ��j
//========================
cKeyboard::cKeyboard()
{
	
}

//========================
//�L�[�{�[�h�f�X�g���N�^�i�I�������j
//========================
cKeyboard::~cKeyboard()
{
	//���̓f�o�C�X�̔j��
	if (this->m_pDevKeyboard != NULL)
	{
		this->m_pDevKeyboard->Unacquire();
		this->m_pDevKeyboard->Release();
		this->m_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (this->m_pInputKeyboard != NULL)
	{
		this->m_pInputKeyboard->Release();
		this->m_pInputKeyboard = NULL;
	}
}

//========================
//�L�[�{�[�h����������
//========================
HRESULT cKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DireceInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->m_pInputKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�擾
	if (FAILED(this->m_pInputKeyboard->CreateDevice(GUID_SysKeyboard, &this->m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�ݒ�
	if (FAILED(this->m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�ݒ�
	if (FAILED(this->m_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	this->m_pDevKeyboard->Acquire();

	//���ԏ�����
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		this->m_Key[nCntKey].currentTime = 0;
		this->m_Key[nCntKey].execLastTime = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//�L�[�{�[�h�X�V����
//========================
void cKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	//���̓f�o�C�X����f�o�C�X���擾
	if (SUCCEEDED(this->m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			this->m_Key[nCntKey].trigger = (this->m_Key[nCntKey].state ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			this->m_Key[nCntKey].release = (this->m_Key[nCntKey].state ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];

			//���s�[�g
			this->m_Key->currentTime = timeGetTime();
			if (aKeyState[nCntKey] && (this->m_Key->currentTime - this->m_Key->execLastTime) > REPEATE_TIME)
			{
				this->m_Key->execLastTime = this->m_Key->currentTime;
				this->m_Key[nCntKey].repeate = aKeyState[nCntKey];
			}
			else
			{
				this->m_Key[nCntKey].repeate = 0;
			}
			//�v���X
			this->m_Key[nCntKey].state = aKeyState[nCntKey];	//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		this->m_pDevKeyboard->Acquire();
	}
}

//========================
//�L�[�{�[�h���擾����
//========================
bool cKeyboard::GetKeyboard(INPUTTYPE type, int nKey)
{
	switch (type)
	{
	case INPUTTYPE_PRESS:
		return (m_Key[nKey].state & 0x80) ? true : false;
		break;
	case INPUTTYPE_TRIGGER:
		return (m_Key[nKey].trigger & 0x80) ? true : false;
		break;
	case INPUTTYPE_RELEASE:
		return (m_Key[nKey].release & 0x80) ? true : false;
		break;
	case INPUTTYPE_REPEATE:
		return (m_Key[nKey].repeate & 0x80) ? true : false;
		break;
	}
	return false;
}

//==================================================
//						�Q�[���p�b�h
//==================================================
//========================
//�Q�[���p�b�h�R���X�g���N�^�i���͉������Ȃ��j
//========================
cGamePad::cGamePad()
{

}

//========================
//�Q�[���p�b�h�f�X�g���N�^�i���͉������Ȃ��j
//========================
cGamePad::~cGamePad()
{

}

//========================
//�Q�[���p�b�h����������
//========================
void cGamePad::Init(GAMEPAD_NO PadNum)
{
	//�ϐ�������
	this->m_Pad[PadNum].currentTime = 0;
	this->m_Pad[PadNum].execLastTime = timeGetTime();
	this->m_PadNum = PadNum;
	this->m_Pad[PadNum].bUse = false;
}

//========================
//�Q�[���p�b�h�I������
//========================
void cGamePad::Release(void)
{
	//XInput�I��
	XInputEnable(false);
}

//========================
//�Q�[���p�b�h�X�V����
//========================
void cGamePad::Update(void)
{
	XINPUT_STATE xInputState;

	//�Q�[���p�b�h������擾
	for (int nCntGPad = 0; nCntGPad < MAX_USE_GAMEPAD; nCntGPad++)
	{
		bool bOldUseGPad = this->m_Pad[this->m_PadNum].bUse;
		if (XInputGetState(nCntGPad, &xInputState) == ERROR_SUCCESS)
		{
			//�g���Ă��
			this->m_Pad[this->m_PadNum].bUse = true;

			//�{�^���g���K�[���擾
			this->m_Pad[this->m_PadNum].trigger = (this->m_Pad[this->m_PadNum].state.Gamepad.wButtons ^ xInputState.Gamepad.wButtons) & xInputState.Gamepad.wButtons;

			//�{�^�������[�X���擾
			this->m_Pad[this->m_PadNum].release = (this->m_Pad[this->m_PadNum].state.Gamepad.wButtons ^ xInputState.Gamepad.wButtons) & ~xInputState.Gamepad.wButtons;

			//���s�[�g��񐶐�
			this->m_Pad[this->m_PadNum].currentTime = timeGetTime();
			for (int nCntKey = 0; nCntKey < GAMEPAD_BUTTON_NUM; nCntKey++)
			{
				if (this->m_Pad[this->m_PadNum].state.Gamepad.wButtons & 1 << nCntKey && (this->m_Pad[this->m_PadNum].currentTime - this->m_Pad[this->m_PadNum].execLastTime) > REPEATE_TIME)
				{
					this->m_Pad[this->m_PadNum].execLastTime = this->m_Pad[this->m_PadNum].currentTime;
					this->m_Pad[this->m_PadNum].repeate += 1 << nCntKey;
				}
			}

			//�v���X��񂻂̑��������ݒ�
			this->m_Pad[this->m_PadNum].state = xInputState;

			//�X�e�B�b�N�X������
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbLX);
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbLY);
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbRX);
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbRY);
		}
		else
		{
			//�g���ĂȂ���
			this->m_Pad[this->m_PadNum].bUse = false;
		}
	}
}

//========================
//�Q�[���p�b�h�{�^���擾����
//========================
bool cGamePad::GetGamePadButton(INPUTTYPE type, int nButton)
{
	if (this->m_Pad[this->m_PadNum].bUse == true)
	{
		switch (type)
		{
		case INPUTTYPE_PRESS:
			return this->m_Pad[this->m_PadNum].state.Gamepad.wButtons & nButton ? true : false;
			break;
		case INPUTTYPE_TRIGGER:
			return this->m_Pad[this->m_PadNum].trigger & nButton ? true : false;
			break;
		case INPUTTYPE_RELEASE:
			return this->m_Pad[this->m_PadNum].release & nButton ? true : false;
			break;
		case INPUTTYPE_REPEATE:
			return this->m_Pad[this->m_PadNum].repeate & nButton ? true : false;
			break;
		}
	}
	return false;
}

//========================
//�Q�[���p�b�h�X�e�B�b�N�擾����
//========================
bool cGamePad::GetGamePadStick(char location, char dir)
{
	if (this->m_Pad[this->m_PadNum].bUse == true)
	{
		if (location == 'L')
		{//L�X�e�B�b�N�w��
			if (location == 'X')
			{//X�����w��
				return this->m_Pad->state.Gamepad.sThumbLX > STICK_DEADZONE ? true : false;
			}
			else if (location == 'Y')
			{//Y�����w��
				return this->m_Pad->state.Gamepad.sThumbLY > STICK_DEADZONE ? true : false;
			}
			else
			{//����Ȃ��̂͂Ȃ�
				return 0;
			}
		}
		else if (location == 'R')
		{//R�X�e�B�b�N�w��
			if (location == 'X')
			{//X�����w��
				return this->m_Pad->state.Gamepad.sThumbRX > STICK_DEADZONE ? true : false;
			}
			else if (location == 'Y')
			{//Y�����w��
				return this->m_Pad->state.Gamepad.sThumbRY > STICK_DEADZONE ? true : false;
			}
			else
			{//����Ȃ��̂͂Ȃ�
				return 0;
			}
		}
		else
		{//����Ȃ��̂͂Ȃ�
			return 0;
		}
	}
	else
	{//�g���Ă��Ȃ�������0�Ԃ�
		return 0;
	}
}

//========================
//�Q�[���p�b�h�g�p���Ă��邩�Ԃ�����
//=======================
bool cGamePad::GetUseGamePad(GAMEPAD_NO PadNum)
{
	return m_Pad[PadNum].bUse;
}

//========================
//�X�e�B�b�N�X����������
//=======================
void AdjustStick(SHORT* pStick)
{
	//�V�т͈͓̔���
	if (abs(*pStick) > STICK_DEADZONE)
	{//�͈͊O
		//-�l�ő�Ȃ�+�l�ő�ɍ��킹��
		if (*pStick < -STICK_MAX)
		{
			*pStick = -STICK_MAX;
		}
	}
	else
	{//�͈͓�
		*pStick = 0;
	}
}

//==================================================
//						�}�E�X
//==================================================
//========================
//�L�[�{�[�h�R���X�g���N�^�i���͉������Ȃ��j
//========================
cMouse::cMouse()
{

}

//========================
//�L�[�{�[�h�f�X�g���N�^�i�I�������j
//========================
cMouse::~cMouse()
{
	//���̓f�o�C�X�̔j��
	if (this->m_pDevMouse != NULL)
	{
		this->m_pDevMouse->Unacquire();
		this->m_pDevMouse->Release();
		this->m_pDevMouse = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (this->m_pInputMouse != NULL)
	{
		this->m_pInputMouse->Release();
		this->m_pInputMouse = NULL;
	}
}

//========================
//�}�E�X����������
//========================
HRESULT cMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DireceInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&this->m_pInputMouse, NULL)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�擾
	if (FAILED(this->m_pInputMouse->CreateDevice(GUID_SysMouse, &this->m_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g�ݒ�
	if (FAILED(this->m_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//�������[�h�ݒ�
	if (FAILED(this->m_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�}�E�X�ւ̃A�N�Z�X�����l��
	this->m_pDevMouse->Acquire();

	//���ԏ�����
	for (int nCntInit = 0; nCntInit < MOUSE_BUTTON_MAX; nCntInit++)
	{
		this->m_Mouse.mb[nCntInit].currentTime = 0;
		this->m_Mouse.mb[nCntInit].execLastTime = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//�}�E�X�X�V����
//========================
void cMouse::Update(void)
{
	DIMOUSESTATE MouseState;
	POINT point;

	//�}�E�X�擾
	if (SUCCEEDED(this->m_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
	{
		for (int nCntKey = 0; nCntKey < MOUSE_BUTTON_MAX; nCntKey++)
		{
			//�g���K�[�ƃ����[�X
			this->m_Mouse.mb[nCntKey].trigger = (this->m_Mouse.state.rgbButtons[nCntKey] ^ MouseState.rgbButtons[nCntKey]) & MouseState.rgbButtons[nCntKey];
			this->m_Mouse.mb[nCntKey].release = (this->m_Mouse.state.rgbButtons[nCntKey] ^ MouseState.rgbButtons[nCntKey]) & ~MouseState.rgbButtons[nCntKey];

			//���s�[�g
			this->m_Mouse.mb[nCntKey].currentTime = timeGetTime();
			if (MouseState.rgbButtons[nCntKey] && (this->m_Mouse.mb[nCntKey].currentTime - this->m_Mouse.mb[nCntKey].execLastTime) > REPEATE_TIME)
			{
				this->m_Mouse.mb[nCntKey].execLastTime = this->m_Mouse.mb[nCntKey].currentTime;
				this->m_Mouse.mb[nCntKey].repeate = MouseState.rgbButtons[nCntKey];
			}
			else
			{
				this->m_Mouse.mb[nCntKey].repeate = 0;
			}
		}

		//�v���X
		this->m_Mouse.state = MouseState;	//�L�[�{�[�h�̃v���X����ۑ�

		//�ړ���
		this->m_Mouse.move = D3DXVECTOR3((float)this->m_Mouse.state.lX, (float)this->m_Mouse.state.lY, 0.0f);
	}
	else
	{
		this->m_pDevMouse->Acquire();
	}

	//�}�E�X���W�擾
	GetCursorPos(&point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &point);
	this->m_Mouse.pos.x = (float)point.x;
	this->m_Mouse.pos.y = (float)point.y;
}

//========================
//�}�E�X�̃N���b�N���擾����
//=======================
bool cMouse::GetMouseClick(INPUTTYPE type, int button)
{
	switch (type)
	{
	case INPUTTYPE_PRESS:
		return m_Mouse.state.rgbButtons[button] & 0x80 ? true : false;
		break;
	case INPUTTYPE_TRIGGER:
		return m_Mouse.mb[button].trigger & 0x80 ? true : false;
		break;
	case INPUTTYPE_RELEASE:
		return m_Mouse.mb[button].repeate & 0x80 ? true : false;
		break;
	case INPUTTYPE_REPEATE:
		return false;	//�H����
		break;
	}
	return false;
}

//========================
//�}�E�X�̃J�[�\���ʒu��Ԃ�����
//=======================
D3DXVECTOR3 cMouse::GetMousePos(void)
{
	return m_Mouse.pos;
}

//========================
//�}�E�X�̃J�[�\���ړ��ʂ�Ԃ�����
//=======================
D3DXVECTOR3 cMouse::GetMouseMove(void)
{
	return m_Mouse.move;
}