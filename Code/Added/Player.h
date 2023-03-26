//==========================================
//
//プレイヤー（動かせるもの）プログラムのヘッダ[Player.h]
//Author:石原颯馬
//
//==========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../Core/Main/main.h"
#include "../Resource/Model/cModel.h"

class Player : public cModel
{
public:
	Player();
	~Player();

private:
	D3DXVECTOR3 pos, posOld;
	D3DXVECTOR3 rot, rotOld;

};

#endif // !_PLAYER_H_