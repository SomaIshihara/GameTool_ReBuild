//==========================================
//
//計算プログラムのヘッダ[Culc.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CULC_H_
#define _CULC_H_

//マクロ
#define ACCELERATION_GRAVITY	(9.8f)		//重力加速度

//便利マクロ関数
#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//角度を-PI~PIに修正
#define fatof(x)				(float)atof(x)										//通常のatofだとdouble型で返してくるのでfloatキャストも行うようにしたもの
#define TASUKIGAKE(ax,az,bx,bz)	((az * bx) - (ax * bz))								//名前の通り。それ以上の説明はない。
#define PYTHAGORAS(a,b)			sqrtf(powf(a,2) + powf(b,2))						//三平方の定理
#define CONVERT_FPS(x)			(int)(x * MAX_FPS)									//秒数をFPSに変換

//プロトタイプ宣言
void UpdateCulc(void);

#endif // !_BILLBOARD_H_
