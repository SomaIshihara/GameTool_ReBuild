//==========================================
//
//ライトプログラムのヘッダ[cLight.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CLASS_LIGHT_H_
#define _CLASS_LIGHT_H_

#include "main.h"

class cLight
{
public:
	//コンストラクタ・デストラクタ
	cLight();
	~cLight();

	//設定
	void SetLight(D3DLIGHTTYPE type, D3DCOLORVALUE col, D3DXVECTOR3 vecDir);

	//有効・無効化切換え
	void EnableLight(bool bEnable);
private:
	//ライト情報
	D3DLIGHT9 m_light;

	//このカメラの番号
	int m_thisLightNum;

	//カメラ個数
	static int m_allLightNum;
};

int cLight::m_allLightNum = 0;

#endif // !_LIGHT_H_
