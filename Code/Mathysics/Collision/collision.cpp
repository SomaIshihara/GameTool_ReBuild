//==========================================
//
//当たり判定プログラム[collision.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "collision.h"

//プロト
void GenerateCollision(CollisionPos *pGeneratedColl, CollisionPos rawColl, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#if 0
void RefrectPlayer(Player *pPlayer, Fence *pFence, float fRate, D3DXVECTOR3 vecLine);
bool HitPlayerToPlayer(Player *pATKPlayer, Player *pHitPlayer, D3DXVECTOR3 collPos, D3DXVECTOR3 vecLine, float fRate);
#endif

#if 0
//========================
//プレイヤー同士の衝突判定処理
//========================
bool CollisionPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth)
{
	//=pos0~pos3の説明==================
	// pos3		pos2
	//	・<-----・		矢印:vecLine
	//	｜		↑
	//	｜		｜
	//	↓		｜
	//	・----->・
	// pos0		pos1
	//==================================

	//頂点
	CollisionPos collPos;

	//ベクトル
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove[2];

	//プレイヤー
	Player *pPlayer = GetPlayer();

	//2は2頂点の2
	float fAreaARight[2], fAreaALeft[2], fAreaBRight[2], fAreaBLeft[2];
	float fAreaAUp[2], fAreaADown[2], fAreaBUp[2], fAreaBDown[2];

	//未反映の位置考慮
	D3DXVECTOR3 posTemp = pATKPlayer->pos +pATKPlayer->move;

	for (int nCntOtherPlayer = 0; nCntOtherPlayer < MAX_USE_GAMEPAD; nCntOtherPlayer++,pPlayer++)
	{
		if (pPlayer !=pATKPlayer)
		{
			//頂点設定
			GenerateCollision(pPlayer->pos,pPlayer->rot, &collPos, fWidth, fDepth);

			//ベクトル求める
			//move
			for (int nCntCollision = 0; nCntCollision < 2; nCntCollision++)
			{
				vecMove[nCntCollision] = (posTemp + pATKPlayer->faceCollider[nCntCollision]) - (pATKPlayer->posOld + pATKPlayer->faceCollider[nCntCollision]);
			}

			//X
			//右方向の計算
			vecLineRight = collPos.pos1 - collPos.pos0;
			vecToPosRight = posTemp - collPos.pos0;
			vecToPosOldRight = pATKPlayer->posOld - collPos.pos0;

			//左方向の計算
			vecLineLeft = collPos.pos3 - collPos.pos2;
			vecToPosLeft = posTemp - collPos.pos2;
			vecToPosOldLeft = pATKPlayer->posOld - collPos.pos2;

			//Z
			//上方向の計算
			vecLineUp = collPos.pos2 - collPos.pos1;
			vecToPosUp = posTemp - collPos.pos1;
			vecToPosOldUp = pATKPlayer->posOld - collPos.pos1;
			//下方向の計算
			vecLineDown = collPos.pos0 - collPos.pos3;
			vecToPosDown = posTemp - collPos.pos3;
			vecToPosOldDown = pATKPlayer->posOld - collPos.pos3;

			//当たり判定本番
			for (int nCntCollision = 0; nCntCollision < 2; nCntCollision++)
			{
				//X
				//面積求める
				fAreaARight[nCntCollision] = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaALeft[nCntCollision] = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBRight[nCntCollision] = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBLeft[nCntCollision] = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);

				//左側AND範囲内
				if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
				{
					if (fAreaARight[nCntCollision] / fAreaBRight[nCntCollision] >= 0.0f && fAreaARight[nCntCollision] / fAreaBRight[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaARight[nCntCollision] / fAreaBRight[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos0, vecLineRight, fRate);
							break;
						}
					}
				}
				else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
				{
					if (fAreaALeft[nCntCollision] / fAreaBLeft[nCntCollision] >= 0.0f && fAreaALeft[nCntCollision] / fAreaBLeft[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaALeft[nCntCollision] / fAreaBLeft[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos2, vecLineLeft, fRate);
							break;
						}
					}
				}

				//Z
				//面積求める
				fAreaAUp[nCntCollision] = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaADown[nCntCollision] = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBUp[nCntCollision] = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBDown[nCntCollision] = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);

				//左側AND範囲内
				if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
				{
					if (fAreaAUp[nCntCollision] / fAreaBUp[nCntCollision] >= 0.0f && fAreaAUp[nCntCollision] / fAreaBUp[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaAUp[nCntCollision] / fAreaBUp[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos1, vecLineUp, fRate);
							break;
						}
					}
				}
				else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
				{
					if (fAreaADown[nCntCollision] / fAreaBDown[nCntCollision] >= 0.0f && fAreaADown[nCntCollision] / fAreaBDown[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaADown[nCntCollision] / fAreaBDown[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos3, vecLineDown, fRate);
							break;
						}
					}
				}
			}
		}
	}
	return false;
}

//========================
//ヒップドロップ時の衝突処理
//========================
bool CollisionHipDropPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth, float fRadius, float fPower)
{
	//=pos0~pos2の説明==================
	//
	//		・g_ap[nPNum].posOld
	//		↓
	//		・g_ap[nPNum].pos
	// pos1		pos0
	//	・<-----・		矢印:vecLine
	//	｜
	//	｜
	//	↓
	//　・
	// pos2
	//==================================

	//頂点
	CollisionPos collPos;

	//ベクトル
	D3DXVECTOR3 vecLineX, vecToPosX, vecToPosOldX;
	D3DXVECTOR3 vecLineZ, vecToPosZ, vecToPosOldZ;
	D3DXVECTOR3 vecMove;

	//プレイヤー
	Player *pPlayer = GetPlayer();

	//面積
	float fAreaAX, fAreaBX, fAreaAZ, fAreaBZ;

	//未反映の位置考慮
	D3DXVECTOR3 posTemp = pATKPlayer->pos + pATKPlayer->move;

	for (int nCntOtherPlayer = 0; nCntOtherPlayer < MAX_USE_GAMEPAD; nCntOtherPlayer++)
	{
		if (pPlayer != pATKPlayer)
		{
			//頂点設定
			GenerateCollision(pPlayer->pos, pPlayer->rot, &collPos, fWidth, fDepth);

			//ベクトル求める
			//move
			vecMove = posTemp - pATKPlayer->posOld;

			//X
			vecLineX = collPos.pos1 - collPos.pos0;
			vecToPosX = posTemp - collPos.pos0;
			vecToPosOldX = pATKPlayer->posOld - collPos.pos0;

			//Z
			vecLineZ = collPos.pos2 - collPos.pos1;
			vecToPosZ = posTemp - collPos.pos1;
			vecToPosOldZ = pATKPlayer->posOld - collPos.pos1;

			//当たり判定本番
			//X
			//面積求める
			fAreaAX = TASUKIGAKE(vecToPosX.x, vecToPosX.y, vecMove.x, vecMove.y);
			fAreaBX = TASUKIGAKE(vecLineX.x, vecLineX.y, vecMove.x, vecMove.y);
			fAreaAZ = TASUKIGAKE(vecToPosZ.z, vecToPosZ.y, vecMove.z, vecMove.y);
			fAreaBZ = TASUKIGAKE(vecLineZ.z, vecLineZ.y, vecMove.z, vecMove.y);
			//左側AND範囲内
			float fHeight = posTemp.y - pPlayer->pos.y;
			if (fHeight <= fHeight)
			{
				float fRadius = PYTHAGORAS(pPlayer->pos.x - posTemp.x,
					pPlayer->pos.z - posTemp.z);

				if (fRadius <= fRadius)
				{
					//移動量計算
					float fAngleHipDrop = atan2f(pPlayer->pos.x - posTemp.x,
						pPlayer->pos.z - posTemp.z);
					pPlayer->move.x = sinf(fAngleHipDrop) * fPower;
					pPlayer->move.z = -cosf(fAngleHipDrop) * fPower;

					//ちょっと飛ばす
					pPlayer->moveV0.y = fPower;
					pPlayer->jumpTime = 0;

					//攻撃された扱いにする
					pPlayer->nLastHitPlayer = pATKPlayer->nPlayerNum;
				}
			}
		}
	}
	return false;
}

//========================
//フェンスの衝突処理（移動処理中に行う）
//========================
bool CollisionFence(Player *pPlayer, float fFenceWidth, float fPlayerHeight, float fFenceDepth, float fenceSize)
{
	//頂点
	CollisionPos collPos;

	//ベクトル
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove;

	//フェンス
	Fence *pFence = GetFence();

	//2は2頂点の2
	float fAreaARight, fAreaALeft, fAreaBRight, fAreaBLeft;
	float fAreaAUp, fAreaADown, fAreaBUp, fAreaBDown;

	//未反映の位置考慮
	D3DXVECTOR3 posTemp = pPlayer->pos + pPlayer->move;

	for (int nCntFence = 0; nCntFence < MAX_USE_FENCE; nCntFence++, pFence++)
	{
		//頂点設定
		GenerateCollision(pFence->pos, pFence->rot, &collPos, fFenceWidth * fenceSize, fFenceDepth * fenceSize);

		//ベクトル求める
		//move
		vecMove = posTemp - pPlayer->posOld;

		//X
		//右方向の計算
		vecLineRight = collPos.pos1 - collPos.pos0;
		vecToPosRight = posTemp - collPos.pos0;
		vecToPosOldRight = pPlayer->posOld - collPos.pos0;

		//左方向の計算
		vecLineLeft = collPos.pos3 - collPos.pos2;
		vecToPosLeft = posTemp - collPos.pos2;
		vecToPosOldLeft = pPlayer->posOld - collPos.pos2;

		//Z
		//上方向の計算
		vecLineUp = collPos.pos2 - collPos.pos1;
		vecToPosUp = posTemp - collPos.pos1;
		vecToPosOldUp = pPlayer->posOld - collPos.pos1;
		//下方向の計算
		vecLineDown = collPos.pos0 - collPos.pos3;
		vecToPosDown = posTemp - collPos.pos3;
		vecToPosOldDown = pPlayer->posOld - collPos.pos3;

		//当たり判定本番
		//X
		//面積求める
		fAreaARight = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove.x, vecMove.z);
		fAreaALeft = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove.x, vecMove.z);
		fAreaBRight = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove.x, vecMove.z);
		fAreaBLeft = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove.x, vecMove.z);

		//左側AND範囲内
		if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
		{
			if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
			{
				//割合求める
				float fRate = fAreaARight / fAreaBRight;

				//反射処理
				RefrectPlayer(pPlayer, pFence, fRate, vecLineRight);

				//終了
				return true;
			}
		}
		else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
		{
			if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
			{
				//割合求める
				float fRate = fAreaALeft / fAreaBLeft;

				//反射処理
				RefrectPlayer(pPlayer, pFence, fRate, vecLineLeft);

				//終了
				return true;
			}
		}

		//Z
		//面積求める
		fAreaAUp = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove.x, vecMove.z);
		fAreaADown = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove.x, vecMove.z);
		fAreaBUp = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove.x, vecMove.z);
		fAreaBDown = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove.x, vecMove.z);

		//左側AND範囲内
		if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
		{
			if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
			{
				//割合求める
				float fRate = fAreaAUp / fAreaBUp;

				//反射処理
				RefrectPlayer(pPlayer, pFence, fRate, vecLineUp);

				//終了
				return true;
			}
		}
		else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
		{
			if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
			{
				//割合求める
				float fRate = fAreaADown / fAreaBDown;

				//反射処理
				RefrectPlayer(pPlayer, pFence, fRate, vecLineDown);

				//終了
				return true;
			}
		}
	}
	return false;
}
#endif

//当たり判定頂点列挙
typedef enum
{//M = マイナス, P = プラス
	BOXCOLLPOINT_MXMYMZ = 0,
	BOXCOLLPOINT_PXMYMZ,
	BOXCOLLPOINT_MXMYPZ,
	BOXCOLLPOINT_PXMYPZ,
	BOXCOLLPOINT_MXPYMZ,
	BOXCOLLPOINT_PXPYMZ,
	BOXCOLLPOINT_MXPYPZ,
	BOXCOLLPOINT_PXPYPZ,
	BOXCOLLPOINT_MAX
} BOXCOLLPOINT;

const BOXCOLLPOINT c_aBoxCollPoint[6][4] = 
{
	{ BOXCOLLPOINT_MXPYMZ ,BOXCOLLPOINT_PXPYMZ ,BOXCOLLPOINT_PXPYPZ ,BOXCOLLPOINT_MXPYPZ },	//上面
	{ BOXCOLLPOINT_MXMYPZ ,BOXCOLLPOINT_MXMYMZ ,BOXCOLLPOINT_MXPYMZ ,BOXCOLLPOINT_MXPYPZ },	//左側面
	{ BOXCOLLPOINT_PXMYMZ ,BOXCOLLPOINT_PXMYPZ ,BOXCOLLPOINT_PXPYPZ ,BOXCOLLPOINT_PXPYMZ },	//右側面
	{ BOXCOLLPOINT_MXMYMZ ,BOXCOLLPOINT_PXMYMZ ,BOXCOLLPOINT_PXPYMZ ,BOXCOLLPOINT_MXPYMZ },	//前側面
	{ BOXCOLLPOINT_PXMYPZ ,BOXCOLLPOINT_MXMYPZ ,BOXCOLLPOINT_MXPYPZ ,BOXCOLLPOINT_PXPYPZ },	//奥側面
	{ BOXCOLLPOINT_MXMYMZ ,BOXCOLLPOINT_PXMYMZ ,BOXCOLLPOINT_PXMYPZ ,BOXCOLLPOINT_MXMYPZ }	//下面
};

//*********************************************
//板の当たり判定
//*********************************************
//========================
//当たり判定生成
//========================
void cCollision::SetCollision(D3DXVECTOR3 rot, CollisionPos collPos)
{
	//memo-------------------------------------------------------------
	//		　	↑
	//		　・-|------・
	//		／	 |	  ／
	//	  ／		／
	//	・--------・
	//
	//	これが0.0f,0.0f,0.0f それに合わせて初期法線ベクトル設定してある
	//memo-------------------------------------------------------------

	//ローカル変数
	D3DXVECTOR3 vecNor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot;

	//当たり判定頂点設定
	GenerateCollision(
		&this->m_coll.m_collPos, 
		collPos, 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	//仮
		rot);

	//角度設定
	this->m_coll.m_rot = rot;

	//単位行列作成
	D3DXMatrixIdentity(&mtxRot);

	//法線ベクトル生成
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXVec3TransformCoord(&this->m_coll.m_vecNor, &vecNor, &mtxRot);
}

//========================
//当たり判定確認
//========================
bool cCollision::CollisionCheck(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *posCloss)
{
	return false;
}

//*********************************************
//箱の当たり判定
//*********************************************
//========================
//当たり判定生成
//========================
void cBoxCollider::SetBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth)
{
	//頂点生成
	D3DXVECTOR3 posPoint[BOXCOLLPOINT_MAX];

	for (int nCntPoint = 0; nCntPoint < 8; nCntPoint++)
	{
		posPoint[nCntPoint] = D3DXVECTOR3(
			pos.x + ((fWidth / 2) * ((nCntPoint % 2 == 0) ? -1 : 1)),
			pos.y + ((fHeight / 2) * ((nCntPoint / 4 == 0) ? -1 : 1)),
			pos.z + ((fDepth / 2) * (((nCntPoint / 2) % 2 == 0) ? -1 : 1)));
	}

	for (int nCntCollider = 0; nCntCollider < 6; nCntCollider++)
	{
		CollisionPos collPos = CollisionPos{
			posPoint[c_aBoxCollPoint[nCntCollider][0]],
			posPoint[c_aBoxCollPoint[nCntCollider][1]],
			posPoint[c_aBoxCollPoint[nCntCollider][2]],
			posPoint[c_aBoxCollPoint[nCntCollider][3]]};

		this->m_collPlane[nCntCollider].SetCollision(rot, collPos);
	}
}


//*********************************************
//CPP内のみ使用
//*********************************************
//========================
//当たり判定用点生成
//========================
void GenerateCollision(CollisionPos *pGeneratedColl, CollisionPos rawColl, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//各頂点を求めるのに必要な変数
	D3DXMATRIX mtxWorld;	//回転のベースとなるワールドマトリ
	D3DXMATRIX mtxRot;		//回転行列
	D3DXMATRIX mtxTrans;	//すべて変換後の行列
	D3DXVECTOR3 vtxTrans;	//変換後の点

	//-mtx----------------------------------------------------------------------------------------------------------------------------
	//回転行列を作る
	D3DXMatrixIdentity(&mtxWorld);

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixRotationY(&mtxRot, rot.y);
	D3DXMatrixMultiply(&mtxWorld, &mtxRot, &mtxWorld);

	//位置反映
	mtxWorld._41 = pos.x;
	mtxWorld._42 = pos.y;
	mtxWorld._43 = pos.z;

	//-mtx----------------------------------------------------------------------------------------------------------------------------

	//-pos0---------------------------------------------------------------------------------------------------------------------------
	//回転行列をもとに頂点を回転する
	//ベースをコピー
	mtxTrans = mtxWorld;

	//0度のときの点を置く
	D3DXVECTOR3 vtxPos = rawColl.pos0;

	//回転行列とかけ合わせる
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	pGeneratedColl->pos0.x = vtxTrans.x;
	pGeneratedColl->pos0.y = vtxTrans.y;
	pGeneratedColl->pos0.z = vtxTrans.z;
	//-pos0---------------------------------------------------------------------------------------------------------------------------

	//-pos1---------------------------------------------------------------------------------------------------------------------------
	//回転行列をもとに頂点を回転する
	//ベースをコピー
	mtxTrans = mtxWorld;

	//0度のときの点を置く
	vtxPos = rawColl.pos1;

	//回転行列とかけ合わせる
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	//変換後の点の場所を代入
	pGeneratedColl->pos1.x = vtxTrans.x;
	pGeneratedColl->pos1.y = vtxTrans.y;
	pGeneratedColl->pos1.z = vtxTrans.z;
	//-pos1---------------------------------------------------------------------------------------------------------------------------

	//-pos2---------------------------------------------------------------------------------------------------------------------------
	//回転行列をもとに頂点を回転する
	//ベースをコピー
	mtxTrans = mtxWorld;

	//0度のときの点を置く
	vtxPos = rawColl.pos2;

	//回転行列とかけ合わせる
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	//変換後の点の場所を代入
	pGeneratedColl->pos2.x = vtxTrans.x;
	pGeneratedColl->pos2.y = vtxTrans.y;
	pGeneratedColl->pos2.z = vtxTrans.z;
	//-pos2---------------------------------------------------------------------------------------------------------------------------

	//-pos3---------------------------------------------------------------------------------------------------------------------------
	//回転行列をもとに頂点を回転する
	//ベースをコピー
	mtxTrans = mtxWorld;

	//0度のときの点を置く
	vtxPos = rawColl.pos3;

	//回転行列とかけ合わせる
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	//変換後の点の場所を代入
	pGeneratedColl->pos3.x = vtxTrans.x;
	pGeneratedColl->pos3.y = vtxTrans.y;
	pGeneratedColl->pos3.z = vtxTrans.z;
	//-pos3---------------------------------------------------------------------------------------------------------------------------
}

#if 0
//========================
//反射処理
//========================
void RefrectPlayer(Player *pPlayer, Fence *pFence, float fRate, D3DXVECTOR3 vecLine)
{
	//ベクトルの割合求める
	//とりあえず交わっている頂点を求める
	D3DXVECTOR3 posCross = vecLine / fRate;

	//頂点をもとにベクトル求める
	D3DXVECTOR3 vecCross = pPlayer->pos - posCross;

	//求めたベクトルをもとに割合求める
	float fRateRemaining = D3DXVec3Length(&vecCross) / D3DXVec3Length(&pPlayer->move);


	//一旦進めるだけ進める
	pPlayer->pos = posCross;


	//移動量のベクトルを代入
	D3DXVECTOR3 vecMove = pPlayer->move;

	//フェンスの法線ベクトルを求める
	D3DXVECTOR3 vecNor;
	vecNor.x = -sinf(pFence->rot.y);
	vecNor.y = 0.0f;
	vecNor.z = -cosf(pFence->rot.y);

	//とりあえず正規化
	D3DXVec3Normalize(&vecMove, &vecMove);
	D3DXVec3Normalize(&vecNor, &vecNor);

	//ドット積（内積）求める
	float fDot = D3DXVec3Dot(&vecMove, &vecNor);

	//反射ベクトルを求める
	D3DXVECTOR3 vecRefrect = vecMove - 2 * fDot * vecNor;

	//実際の移動量を設定
	float fVecLength = D3DXVec3Length(&pPlayer->move);
	vecRefrect *= fVecLength / fRateRemaining;

	//ちゃんと移動する
	pPlayer->pos += vecRefrect;
}

//========================
//当たった時の処理（返り値は動いているかどうか）
//========================
bool HitPlayerToPlayer(Player *pATKPlayer, Player *pHitPlayer, D3DXVECTOR3 collPos, D3DXVECTOR3 vecLine, float fRate)
{
	bool bMove = false;
	if (fabsf(pATKPlayer->move.x) > 0.0f || fabsf(pATKPlayer->move.z) > 0.0f)
	{//動いてる
		pATKPlayer->nFrameAtkPlayer = pHitPlayer->nPlayerNum;
		pHitPlayer->nLastHitPlayer = pATKPlayer->nPlayerNum;

		bMove = true;
	}
	//1.0f = pushback
	pATKPlayer->pos.x = collPos.x + (vecLine.x * fRate) - sinf(pHitPlayer->rot.y) / D3DX_PI * 1.0f;
	pATKPlayer->pos.z = collPos.z + (vecLine.z * fRate) - cosf(pHitPlayer->rot.y) / D3DX_PI * 1.0f;

	//動いているか返す
	return bMove;
}
#endif