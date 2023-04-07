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
#include "..\3D\Camera\cCamera.h"

typedef struct
{
	D3DXVECTOR3 pos, posOld;
	D3DXVECTOR3 rot, rotOld;
	D3DXMATRIX mtxWorld;
} Player;

class cPlayer : public cMotionModel
{
public:
	cPlayer();
	~cPlayer();
	void Update(void);
	void Draw(void);
	Player *GetPlayer(void);
	Camera **GetLinkCamera(void);
private:
	Player m_player;
	Camera *m_pCamera;
};

#endif // !_PLAYER_H_
