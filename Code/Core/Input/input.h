//==========================================================================================
//
//入力プログラムのヘッダ[input.h]
//Author:石原颯馬
//
//==========================================================================================
//Ver.3.0.0b（C++予習時点）
//使用可能な入力:キーボード・マウス（カーソル位置・移動量）・ゲームパッド（1~4台）
//==========================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "..\..\Core\Main\main.h"

//==========================================================================================
// マクロ定義
//==========================================================================================
#define STICK_MAX			(32767)	//スティック最大値
#define MOUSE_CLICK_LEFT	(0)		//マウス左クリック
#define MOUSE_CLICK_RIGHT	(1)		//マウス右クリック
#define MOUSE_BUTTON_MAX	(3)		//マウスボタンの最大数
#define NUM_KEY_MAX			(256)	//キーの最大数

//ゲームパッドのスティック系
#define GAMEPAD_STICK_L		'L'
#define GAMEPAD_STICK_R		'R'
#define GAMEPAD_STICK_X		'X'
#define GAMEPAD_STICK_Y		'Y'

//==========================================================================================
// 列挙型定義
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
// 構造体定義
//==========================================================================================
//キーボード
typedef struct
{
	BYTE state;		//状態（保存用およびプレス情報）
	BYTE trigger;	//トリガー情報
	BYTE release;	//リリース情報
	BYTE repeate;	//リピート情報
	DWORD currentTime;	//現在の時間
	DWORD execLastTime;	//最後にtrueにした時間
} Keyboard;

//ゲームパッド
typedef struct
{
	XINPUT_STATE state;	//状態全部（およびプレス情報）
	WORD trigger;		//トリガー情報
	WORD release;		//リリース情報
	WORD repeate;		//リピート情報
	DWORD currentTime;	//現在の時間
	DWORD execLastTime;	//最後にtrueにした時間
	bool bUse;			//使用の有無
} GamePad;

//マウスのボタン部
typedef struct
{
	BYTE trigger;		//ボタンのトリガー情報
	BYTE release;		//ボタンのリリース情報
	BYTE repeate;		//リピート情報
	DWORD currentTime;	//現在の時間（リピート使用）
	DWORD execLastTime;	//最後にtrueを返した時間（リピート使用)
} MouseButton;

//マウスすべて
typedef struct
{
	MouseButton mb[MOUSE_BUTTON_MAX];	//マウスボタン
	DIMOUSESTATE state;					//状態およびプレス情報
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 move;					//移動量
} Mouse;

//==========================================================================================
// クラス
//==========================================================================================
//=============================
// キーボード
//=============================
class cKeyboard
{
public:
	//コンストラクタ・デストラクタ
	cKeyboard();
	~cKeyboard();

	//初期化
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	//更新
	void Update(void);

	//取得
	bool GetKeyboard(INPUTTYPE type, int nKey);
private:
	//取得に必要
	LPDIRECTINPUT8 m_pInputKeyboard;
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;

	//保存場所
	static Keyboard m_Key[NUM_KEY_MAX];
};

//=============================
// ゲームパッド
//=============================
class cGamePad
{
public:
	//コンストラクタ・デストラクタ
	cGamePad();
	~cGamePad();

	//初期化
	void Init(GAMEPAD_NO PadNum);

	//破棄
	void Release(void);

	//更新
	void Update(void);

	//取得
	bool GetGamePadButton(INPUTTYPE type, int nButton);	//ボタン
	bool GetGamePadStick(char location, char dir);		//スティック
	static bool GetUseGamePad(GAMEPAD_NO PadNum);		//使用の有無
private:
	//保存場所
	static GamePad m_Pad[MAX_USE_GAMEPAD];

	//パッド番号
	GAMEPAD_NO m_PadNum;
};

//=============================
// マウス
//=============================
class cMouse
{
	//コンストラクタ・デストラクタ
	cMouse();
	~cMouse();

	//初期化
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	//更新
	void Update(void);

	//取得
	//ボタン
	bool GetMouseClick(INPUTTYPE type, int button);

	//位置
	D3DXVECTOR3 GetMousePos(void);

	//移動量
	D3DXVECTOR3 GetMouseMove(void);
private:
	//取得に必要
	LPDIRECTINPUT8 m_pInputMouse;
	LPDIRECTINPUTDEVICE8 m_pDevMouse;

	//保存場所
	Mouse m_Mouse;
};

#endif // !_INPUT_H_
