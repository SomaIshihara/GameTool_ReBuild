//==========================================
//
//動かせるモデルプログラム[cMotionModel.cpp]
//Author:石原颯馬
//
//==========================================
#include "cMotionModel.h"
#include "..\..\Core\File\file.h"
#include "..\..\Mathysics\Culc\Culc.h"
#include <stdio.h>
#include <assert.h>

//モーションビューワー用コード
//初期
#define CODE_NUM_MODEL			"NUM_MODEL"			//モデル数
#define CODE_MODEL_FILENAME		"MODEL_FILENAME"	//モデルのファイルパス
#define CODE_CHARACTERSET		"CHARACTERSET"		//キャラクター情報
#define CODE_END_CHARACTERSET	"END_CHARACTERSET"

//パーツ設定
#define CODE_PARTSSET			"PARTSSET"			//パーツ設定開始
#define CODE_END_PARTSSET		"END_PARTSSET"		//パーツ設定終了

//モーション設定
#define CODE_MOTIONSET			"MOTIONSET"			//モーション設定開始
#define CODE_END_MOTIONSET		"END_MOTIONSET"		//モーション設定終了
//キーセット設定
#define CODE_KEYSET				"KEYSET"			//キーセット設定開始
#define CODE_END_KEYSET			"END_KEYSET"		//キーセット設定終了
//キー設定
#define CODE_KEY				"KEY"				//キー設定開始
#define CODE_END_KEY			"END_KEY"			//キー設定終了

//モーションビューワー用パラメーター
#define CODE_MOVE				"MOVE"				//移動量
#define CODE_JUMP				"JUMP"				//ジャンプ量
#define CODE_NUM_PARTS			"NUM_PARTS"			//パーツ数
#define CODE_INDEX				"INDEX"				//番号
#define CODE_PARENT				"PARENT"			//親モデルの番号
#define CODE_LOOP				"LOOP"				//ループするかの設定
#define CODE_NUM_KEY			"NUM_KEY"			//キー数
#define CODE_FRAME				"FRAME"				//フレーム数

//読み取り状態列挙
typedef enum
{
	//共通
	READSTAT_MOTION_NONE = 0,	//何もしてない
	//--モーションビューワー------------------
	READSTAT_MOTION_CHARACTERSET,
	READSTAT_MOTION_PARTSSET,
	READSTAT_MOTION_MOTIONSET,
	READSTAT_MOTION_KEYSET,
	READSTAT_MOTION_KEY,
	//----------------------------------------
	READSTAT_MOTION_MAX
} READSTAT_MOTION;

//========================
//コンストラクタ
//========================
cMotionModel::cMotionModel()
{
	
}

//========================
//デストラクタ
//========================
cMotionModel::~cMotionModel()
{
	for (int cntModel = 0; cntModel < MAX_MOTION_MODEL; cntModel++)
	{
		this->m_model[cntModel].~cModel();
	}
}

//========================
//モーションビューワーのファイル情報取得
//========================
void cMotionModel::LoadMotionModel(const char *pPath)
{
	FILE *pFile;
	char aCode[MAX_STR_LENGTH];
	char *pSprit;
	bool bRead = false;

	READSTAT_MOTION readstat = READSTAT_MOTION_NONE;
	int counterReadModel = 0;
	int counterSetModel = 0;
	int counterMotionInfo = 0;
	int counterKeyInfo = 0;
	int counterKey = 0;
	int idxPartsSet = 0;

	//仮置き
	cModelStruct modelstr;

	//モーション情報
	//読み込みファイル設定
	pFile = fopen(pPath, "r");

	//敵配置情報を取得
	if (pFile != NULL)
	{
		while (1)
		{
			fgets(&aCode[0], MAX_STR_LENGTH, pFile);

			//コメントアウトチェック
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchrの返り値がぬるぽではない
				*pCharPos = '\0';
			}

			//タブ消去
			while (aCode[0] == '\t')
			{
				char aCodeBackup[MAX_STR_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//文字列チェック
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り開始
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//読み取り終了
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOFかもしれない
				if (feof(pFile))
				{//いや、これはEOFだ
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//読み取り
				switch (readstat)
				{
				case READSTAT_MOTION_NONE:	//処理取得
					if (strncmp(&aCode[0], CODE_MODEL_FILENAME, sizeof CODE_MODEL_FILENAME / sizeof(char) - 1) == 0)
					{
						if (counterReadModel < MAX_MOTION_MODEL)
						{
							char aStrPath[MAX_STR_LENGTH];
							pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

							//代入
							strcpy(&aStrPath[0], strtok(NULL, " =\n"));
							//タブ文字が入っているところを消す
							char *pCharPos = strchr(&aStrPath[0], '\t');
							if (pCharPos != nullptr)
							{//strchrの返り値がぬるぽではない
								*pCharPos = '\0';
							}

							//読み込み
							this->m_model[counterReadModel].LoadModel(aStrPath);

							//加算
							counterReadModel++;
						}
					}
					if (strncmp(&aCode[0], CODE_CHARACTERSET, sizeof CODE_CHARACTERSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_CHARACTERSET;
					}
					if (strncmp(&aCode[0], CODE_MOTIONSET, sizeof CODE_MOTIONSET / sizeof(char) - 1) == 0)
					{
						if (counterMotionInfo < MOTIONTYPE_MAX)
						{
							readstat = READSTAT_MOTION_MOTIONSET;
						}
					}
					break;
				case READSTAT_MOTION_CHARACTERSET:		//モデル情報取得
					if (strncmp(&aCode[0], CODE_END_CHARACTERSET, sizeof CODE_END_CHARACTERSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_NONE;
					}
					else if (strncmp(&aCode[0], CODE_PARTSSET, sizeof CODE_PARTSSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_PARTSSET;
					}
					else if (strncmp(&aCode[0], CODE_MOVE, sizeof CODE_MOVE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//移動量取得
						pSprit = strtok(NULL, " =\n");
						this->m_move = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_JUMP, sizeof CODE_JUMP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//ジャンプ量取得
						pSprit = strtok(NULL, " =\n");
						this->m_jump = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_RADIUS, sizeof CODE_RADIUS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//半径取得
						pSprit = strtok(NULL, " =\n");
						this->m_radius = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_NUM_PARTS, sizeof CODE_NUM_PARTS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//パーツ数取得
						pSprit = strtok(NULL, " =\n");
						this->m_numParts = atoi(pSprit);
					}
					break;
				case READSTAT_MOTION_PARTSSET:
					if (strncmp(&aCode[0], CODE_END_PARTSSET, sizeof CODE_END_PARTSSET / sizeof(char) - 1) == 0)
					{
						//取得したものをもらったポインタに代入
						this->m_model[idxPartsSet].SetModelSetup(modelstr);

						//取得したものを消す
						modelstr = {};

						//キャラクター設定状態に戻る
						readstat = READSTAT_MOTION_CHARACTERSET;
					}
					else if (strncmp(&aCode[0], CODE_INDEX, sizeof CODE_INDEX / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//番号取得
						pSprit = strtok(NULL, " =\n");
						idxPartsSet = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_PARENT, sizeof CODE_PARENT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//親番号取得
						pSprit = strtok(NULL, " =\n");
						modelstr.m_IdxModelParent = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(NULL, " =\n");
						modelstr.posOffset.x = fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(NULL, " =\n");
						modelstr.posOffset.y = fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(NULL, " =\n");
						modelstr.posOffset.z = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

						//X座標読み取り
						pSprit = strtok(NULL, " =\n");
						modelstr.rotOffset.x = fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(NULL, " =\n");
						modelstr.rotOffset.y = fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(NULL, " =\n");
						modelstr.rotOffset.z = fatof(pSprit);
					}
					break;
				case READSTAT_MOTION_MOTIONSET:
					if (strncmp(&aCode[0], CODE_KEYSET, sizeof CODE_KEYSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_END_MOTIONSET, sizeof CODE_END_MOTIONSET / sizeof(char) - 1) == 0)
					{
						counterMotionInfo++;
						counterKeyInfo = 0;
						readstat = READSTAT_MOTION_NONE;
					}
					else if (strncmp(&aCode[0], CODE_LOOP, sizeof CODE_LOOP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

															//ループ可否読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_Loop = atoi(pSprit) ? true : false;
					}
					else if (strncmp(&aCode[0], CODE_NUM_KEY, sizeof CODE_NUM_KEY / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

															//キー数読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_numKey = atoi(pSprit);
					}
					break;
				case READSTAT_MOTION_KEYSET:
					if (strncmp(&aCode[0], CODE_KEY, sizeof CODE_KEY / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_KEY;
					}
					else if (strncmp(&aCode[0], CODE_END_KEYSET, sizeof CODE_END_KEYSET / sizeof(char) - 1) == 0)
					{
						counterKeyInfo++;
						counterKey = 0;
						readstat = READSTAT_MOTION_MOTIONSET;
					}
					else if (strncmp(&aCode[0], CODE_FRAME, sizeof CODE_FRAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

															//フレーム数読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_Frame = atoi(pSprit);
					}
					break;
				case READSTAT_MOTION_KEY:
					if (strncmp(&aCode[0], CODE_END_KEY, sizeof CODE_END_KEY / sizeof(char) - 1) == 0)
					{
						counterKey++;
						readstat = READSTAT_MOTION_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

															//X座標読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_PosX = fatof(pSprit);

						//Y座標読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_PosY = fatof(pSprit);

						//Z座標読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_PosZ = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//処理内容の部分消す

															//X向き読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_RotX = fatof(pSprit);

						//Y向き読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_RotY = fatof(pSprit);

						//Z向き読み取り
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_RotZ = fatof(pSprit);
					}
					break;
				}
			}
		}

		//ファイル閉じる
		fclose(pFile);
	}
	else
	{
		assert(pFile != NULL);
	}
}

//========================
//モデル配置
//========================
void cMotionModel::DrawMotionModel(D3DXMATRIX *mtxBace)
{
	D3DXMATRIX mtxParent;
	for (int cntModel = 0; cntModel < MAX_MOTION_MODEL; cntModel++)
	{
		if(this->m_model[cntModel].GetModel().m_IdxModelParent != -1)
		{
			mtxParent = this->m_model[this->m_model[cntModel].GetModel().m_IdxModelParent].GetModel().mtxWorld;
			this->m_model[cntModel].DrawModel(INIT_ZERO, INIT_ZERO, INIT_ZERO, mtxBace, &mtxParent);
		}
		else
		{
			this->m_model[cntModel].DrawModel(INIT_ZERO, INIT_ZERO, INIT_ZERO, mtxBace);
		}
	}
}