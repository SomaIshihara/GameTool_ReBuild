//==========================================
//
//プレイヤープログラムのヘッダ[Player.h]
//Author:石原颯馬
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "..\Core\Main\main.h"
#include "..\3D\MotionModel\cMotionModel.h"

class Player : public cMotionModel
{
public:
	Player();
	~Player();
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3 pos, posOld;
	D3DXVECTOR3 rot, rotOld;
	D3DXMATRIX mtxWorld;
};

#endif // !_PLAYER_H_
