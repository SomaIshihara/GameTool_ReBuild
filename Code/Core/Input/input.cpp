//==========================================================================================
//
//入力プログラム[input.cpp]
//Author:石原颯馬
//
//==========================================================================================
//Ver.3.0.0b（C++予習時点）
//使用可能な入力:キーボード・マウス（カーソル位置・移動量）・ゲームパッド（1~4台）
//==========================================================================================
#include "input.h"
#include "..\..\Core\Sound\sound.h"

//マクロ定義
#define REPEATE_TIME		(150)	//リピートの間隔
#define GAMEPAD_BUTTON_NUM	(14)	//ゲームパッドのボタン数
#define STICK_DEADZONE		(655)	//遊び

//静的メンバ構造体を定義
Keyboard cKeyboard::m_Key[NUM_KEY_MAX];
GamePad cGamePad::m_Pad[MAX_USE_GAMEPAD];
Mouse cMouse::m_Mouse;

//プロト
void AdjustStick(SHORT* pStick);

//==================================================
//						キーボード
//==================================================
//========================
//キーボードコンストラクタ（今は何もしない）
//========================
cKeyboard::cKeyboard()
{
	
}

//========================
//キーボードデストラクタ（終了処理）
//========================
cKeyboard::~cKeyboard()
{
	//入力デバイスの破棄
	if (this->m_pDevKeyboard != NULL)
	{
		this->m_pDevKeyboard->Unacquire();
		this->m_pDevKeyboard->Release();
		this->m_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (this->m_pInputKeyboard != NULL)
	{
		this->m_pInputKeyboard->Release();
		this->m_pInputKeyboard = NULL;
	}
}

//========================
//キーボード初期化処理
//========================
HRESULT cKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DireceInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->m_pInputKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//デバイス取得
	if (FAILED(this->m_pInputKeyboard->CreateDevice(GUID_SysKeyboard, &this->m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマット設定
	if (FAILED(this->m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モード設定
	if (FAILED(this->m_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	this->m_pDevKeyboard->Acquire();

	//時間初期化
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		this->m_Key[nCntKey].currentTime = 0;
		this->m_Key[nCntKey].execLastTime = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//キーボード更新処理
//========================
void cKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	//入力デバイスからデバイスを取得
	if (SUCCEEDED(this->m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			this->m_Key[nCntKey].trigger = (this->m_Key[nCntKey].state ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			this->m_Key[nCntKey].release = (this->m_Key[nCntKey].state ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];

			//リピート
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
			//プレス
			this->m_Key[nCntKey].state = aKeyState[nCntKey];	//キーボードのプレス情報を保存
		}
	}
	else
	{
		this->m_pDevKeyboard->Acquire();
	}
}

//========================
//キーボード情報取得処理
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
//						ゲームパッド
//==================================================
//========================
//ゲームパッドコンストラクタ（今は何もしない）
//========================
cGamePad::cGamePad()
{

}

//========================
//ゲームパッドデストラクタ（今は何もしない）
//========================
cGamePad::~cGamePad()
{

}

//========================
//ゲームパッド初期化処理
//========================
void cGamePad::Init(GAMEPAD_NO PadNum)
{
	//変数初期化
	this->m_Pad[PadNum].currentTime = 0;
	this->m_Pad[PadNum].execLastTime = timeGetTime();
	this->m_PadNum = PadNum;
	this->m_Pad[PadNum].bUse = false;
}

//========================
//ゲームパッド終了処理
//========================
void cGamePad::Release(void)
{
	//XInput終了
	XInputEnable(false);
}

//========================
//ゲームパッド更新処理
//========================
void cGamePad::Update(void)
{
	XINPUT_STATE xInputState;

	//ゲームパッドから情報取得
	for (int nCntGPad = 0; nCntGPad < MAX_USE_GAMEPAD; nCntGPad++)
	{
		bool bOldUseGPad = this->m_Pad[this->m_PadNum].bUse;
		if (XInputGetState(nCntGPad, &xInputState) == ERROR_SUCCESS)
		{
			//使ってるよ
			this->m_Pad[this->m_PadNum].bUse = true;

			//ボタントリガー情報取得
			this->m_Pad[this->m_PadNum].trigger = (this->m_Pad[this->m_PadNum].state.Gamepad.wButtons ^ xInputState.Gamepad.wButtons) & xInputState.Gamepad.wButtons;

			//ボタンリリース情報取得
			this->m_Pad[this->m_PadNum].release = (this->m_Pad[this->m_PadNum].state.Gamepad.wButtons ^ xInputState.Gamepad.wButtons) & ~xInputState.Gamepad.wButtons;

			//リピート情報生成
			this->m_Pad[this->m_PadNum].currentTime = timeGetTime();
			for (int nCntKey = 0; nCntKey < GAMEPAD_BUTTON_NUM; nCntKey++)
			{
				if (this->m_Pad[this->m_PadNum].state.Gamepad.wButtons & 1 << nCntKey && (this->m_Pad[this->m_PadNum].currentTime - this->m_Pad[this->m_PadNum].execLastTime) > REPEATE_TIME)
				{
					this->m_Pad[this->m_PadNum].execLastTime = this->m_Pad[this->m_PadNum].currentTime;
					this->m_Pad[this->m_PadNum].repeate += 1 << nCntKey;
				}
			}

			//プレス情報その他もろもろ設定
			this->m_Pad[this->m_PadNum].state = xInputState;

			//スティック傾き調整
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbLX);
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbLY);
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbRX);
			AdjustStick(&this->m_Pad[this->m_PadNum].state.Gamepad.sThumbRY);
		}
		else
		{
			//使ってないよ
			this->m_Pad[this->m_PadNum].bUse = false;
		}
	}
}

//========================
//ゲームパッドボタン取得処理
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
//ゲームパッドスティック取得処理
//========================
bool cGamePad::GetGamePadStick(char location, char dir)
{
	if (this->m_Pad[this->m_PadNum].bUse == true)
	{
		if (location == 'L')
		{//Lスティック指定
			if (location == 'X')
			{//X方向指定
				return this->m_Pad->state.Gamepad.sThumbLX > STICK_DEADZONE ? true : false;
			}
			else if (location == 'Y')
			{//Y方向指定
				return this->m_Pad->state.Gamepad.sThumbLY > STICK_DEADZONE ? true : false;
			}
			else
			{//そんなものはない
				return 0;
			}
		}
		else if (location == 'R')
		{//Rスティック指定
			if (location == 'X')
			{//X方向指定
				return this->m_Pad->state.Gamepad.sThumbRX > STICK_DEADZONE ? true : false;
			}
			else if (location == 'Y')
			{//Y方向指定
				return this->m_Pad->state.Gamepad.sThumbRY > STICK_DEADZONE ? true : false;
			}
			else
			{//そんなものはない
				return 0;
			}
		}
		else
		{//そんなものはない
			return 0;
		}
	}
	else
	{//使っていなかったら0返す
		return 0;
	}
}

//========================
//ゲームパッド使用しているか返す処理
//=======================
bool cGamePad::GetUseGamePad(GAMEPAD_NO PadNum)
{
	return m_Pad[PadNum].bUse;
}

//========================
//スティック傾き調整処理
//=======================
void AdjustStick(SHORT* pStick)
{
	//遊びの範囲内か
	if (abs(*pStick) > STICK_DEADZONE)
	{//範囲外
		//-値最大なら+値最大に合わせる
		if (*pStick < -STICK_MAX)
		{
			*pStick = -STICK_MAX;
		}
	}
	else
	{//範囲内
		*pStick = 0;
	}
}

//==================================================
//						マウス
//==================================================
//========================
//キーボードコンストラクタ（今は何もしない）
//========================
cMouse::cMouse()
{

}

//========================
//キーボードデストラクタ（終了処理）
//========================
cMouse::~cMouse()
{
	//入力デバイスの破棄
	if (this->m_pDevMouse != NULL)
	{
		this->m_pDevMouse->Unacquire();
		this->m_pDevMouse->Release();
		this->m_pDevMouse = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (this->m_pInputMouse != NULL)
	{
		this->m_pInputMouse->Release();
		this->m_pInputMouse = NULL;
	}
}

//========================
//マウス初期化処理
//========================
HRESULT cMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DireceInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&this->m_pInputMouse, NULL)))
	{
		return E_FAIL;
	}

	//デバイス取得
	if (FAILED(this->m_pInputMouse->CreateDevice(GUID_SysMouse, &this->m_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマット設定
	if (FAILED(this->m_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//協調モード設定
	if (FAILED(this->m_pDevMouse->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//マウスへのアクセス権を獲得
	this->m_pDevMouse->Acquire();

	//時間初期化
	for (int nCntInit = 0; nCntInit < MOUSE_BUTTON_MAX; nCntInit++)
	{
		this->m_Mouse.mb[nCntInit].currentTime = 0;
		this->m_Mouse.mb[nCntInit].execLastTime = timeGetTime() - REPEATE_TIME;
	}

	return S_OK;
}

//========================
//マウス更新処理
//========================
void cMouse::Update(void)
{
	DIMOUSESTATE MouseState;
	POINT point;

	//マウス取得
	if (SUCCEEDED(this->m_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
	{
		for (int nCntKey = 0; nCntKey < MOUSE_BUTTON_MAX; nCntKey++)
		{
			//トリガーとリリース
			this->m_Mouse.mb[nCntKey].trigger = (this->m_Mouse.state.rgbButtons[nCntKey] ^ MouseState.rgbButtons[nCntKey]) & MouseState.rgbButtons[nCntKey];
			this->m_Mouse.mb[nCntKey].release = (this->m_Mouse.state.rgbButtons[nCntKey] ^ MouseState.rgbButtons[nCntKey]) & ~MouseState.rgbButtons[nCntKey];

			//リピート
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

		//プレス
		this->m_Mouse.state = MouseState;	//キーボードのプレス情報を保存

		//移動量
		this->m_Mouse.move = D3DXVECTOR3((float)this->m_Mouse.state.lX, (float)this->m_Mouse.state.lY, 0.0f);
	}
	else
	{
		this->m_pDevMouse->Acquire();
	}

	//マウス座標取得
	GetCursorPos(&point);
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &point);
	this->m_Mouse.pos.x = (float)point.x;
	this->m_Mouse.pos.y = (float)point.y;
}

//========================
//マウスのクリック情報取得処理
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
		return false;	//工事中
		break;
	}
	return false;
}

//========================
//マウスのカーソル位置を返す処理
//=======================
D3DXVECTOR3 cMouse::GetMousePos(void)
{
	return m_Mouse.pos;
}

//========================
//マウスのカーソル移動量を返す処理
//=======================
D3DXVECTOR3 cMouse::GetMouseMove(void)
{
	return m_Mouse.move;
}