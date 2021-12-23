////////////////////////////////////////////////////
//
//    resource_characterクラスの処理[resource_character.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////

//******************************
// インクルード
//******************************
#include "resource_character.h"

//******************************
// マクロ定義
//******************************

//******************************
// 静的メンバ変数宣言
//******************************
// インスタンス
CResourceCharacter* CResourceCharacter::m_pInstance = NULL;
// キャラクターラベルリスト
const std::vector<CResourceCharacter::LabelData> CResourceCharacter::m_aLabelList =
{
	{ "KNIGHT"  , CResourceModelHierarchy::MODEL_HIERARCHY_KNIGHT },
	{ "LANCER"  , CResourceModelHierarchy::MODEL_HIERARCHY_LANCER },
	{ "WIZARD"  , CResourceModelHierarchy::MODEL_HIERARCHY_WIZARD },
	{ "THIEF"   , CResourceModelHierarchy::MODEL_HIERARCHY_THIEF },
	{ "MAGICIAN", CResourceModelHierarchy::MODEL_HIERARCHY_MAGICIAN },
	{ "ARCHER"  , CResourceModelHierarchy::MODEL_HIERARCHY_ARCHER },
}; 
// キャラクターデータのテキストのパス
const std::string CResourceCharacter::m_aCharacterDataTxtPath[CResourceCharacter::CHARACTER_MAX] =
{
	"data/Text/character/CharacterData_Knight.txt",
	"data/Text/character/CharacterData_Lancer.txt",
	"data/Text/character/CharacterData_Wizard.txt",
	"data/Text/character/CharacterData_Thief.txt",
	"data/Text/character/CharacterData_Magician.txt",
	"data/Text/character/CharacterData_Archer.txt",
};

//===================================
// コンストラクタ
//===================================
CResourceCharacter::CResourceCharacter()
{
	//ZeroMemory(&m_aCharacterData, sizeof(m_aCharacterData));
	for (int nCnt = 0; nCnt < CHARACTER_MAX; nCnt++)
	{
		m_aCharacterData[nCnt].nFinalAttackTime = 0;
		m_aCharacterData[nCnt].nMoveFrame = 0;
		m_aCharacterData[nCnt].nMoveFrameDash = 0;
		m_aCharacterData[nCnt].modelType = CResourceModelHierarchy::MODEL_HIERARCHY_KNIGHT;
		ZeroMemory(&m_aCharacterData[nCnt].anChargeTime, sizeof(m_aCharacterData[nCnt].anChargeTime));
	}
	
}

//===================================
// デストラクタ
//===================================
CResourceCharacter::~CResourceCharacter()
{
}

//=============================================================================
//モデルクラスのクリエイト処理
//=============================================================================
CResourceCharacter * CResourceCharacter::Create(void)
{
	if (m_pInstance == NULL)
	{
		// メモリ確保
		m_pInstance = new CResourceCharacter;

		if (m_pInstance != NULL)
		{
			// メモリ確保に成功したとき
			m_pInstance->Load();
		}
		else
		{
			// メモリ確保に失敗したとき
			return NULL;
		}
	}

	return m_pInstance;
}

//===================================
// クラスの破棄
//===================================
void CResourceCharacter::Release(void)
{
	if (m_pInstance != NULL)
	{
		// メモリの破棄
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

//===================================
// テクスチャ読み込み
//===================================
void CResourceCharacter::Load(void)
{
	for (int nCntCharacter = 0; nCntCharacter < CHARACTER_MAX; nCntCharacter++)
	{
		//ファイルポインタ
		FILE*	pFile = NULL;
		//ファイル読み込み
		pFile = fopen(m_aCharacterDataTxtPath[nCntCharacter].c_str(), "r");
		if (pFile == NULL)
		{
			continue;
		}
		while (1)
		{
			char chInTextData[256] = {};
			// 文字列の取得
			fscanf(pFile, "%s", chInTextData);

			// 文字列比較
			auto JudgeStr = [&chInTextData](const char* pStr)
			{
				if (strcmp(pStr, chInTextData) == 0) return true;

				return false;
			};

			// ループ終了条件
			if (JudgeStr("CHARACTER_DATA_END")) break;
			// ラベル
			else if (JudgeStr("LABEL"))
			{// ラベルリストからモデルタイプの設定
				// 文字列の取得
				fscanf(pFile, " %*c %s", chInTextData);
				// ラベル数スープ
				for (int nCntModel = 0; nCntModel < (int)m_aLabelList.size(); nCntModel++)
				{
					// ラベルデータの参照
					if (!JudgeStr(m_aLabelList[nCntModel].labelName.c_str())) continue;

					// モデルタイプの設定
					m_aCharacterData[nCntCharacter].modelType = m_aLabelList[nCntModel].modelType;
					break;
				}
			}
			// 移動量
			else if (JudgeStr("MOVE_FRAME"))
			{
				int nMoveFrame = 0;
				fscanf(pFile, " %*c %d", &nMoveFrame);
				m_aCharacterData[nCntCharacter].nMoveFrame = nMoveFrame;
			}
			// 移動量*ダッシュ時
			else if (JudgeStr("MOVE_FRAME_DASH"))
			{
				int nMoveFrame = 0;
				fscanf(pFile, " %*c %d", &nMoveFrame);
				m_aCharacterData[nCntCharacter].nMoveFrameDash = nMoveFrame;
			}
			// 初動量
			else if (JudgeStr("MOVE_FRAME_INITIAL"))
			{
				int nMoveFrame = 0;
				fscanf(pFile, " %*c %d", &nMoveFrame);
				m_aCharacterData[nCntCharacter].nMoveFrameInitial = nMoveFrame;
			}
			//加速までの回数
			else if (JudgeStr("MOVE_COUNT"))
			{
				int nMoveFrame = 0;
				fscanf(pFile, " %*c %d", &nMoveFrame);
				m_aCharacterData[nCntCharacter].nMoveCount = nMoveFrame;
			}
			// 攻撃パス
			else if (JudgeStr("ATTACK_PATH"))
			{
				// 文字列の取得
				fscanf(pFile, " %*c %s", chInTextData);
				m_aCharacterData[nCntCharacter].attackTextPath = chInTextData;
			}
			// 必殺技発動時間
			else if (JudgeStr("FINAL_ATTACK_TIME"))
			{
				int nTime = 0;
				fscanf(pFile, " %*c %d", &nTime);
				m_aCharacterData[nCntCharacter].nFinalAttackTime = nTime;
			}
			// 攻撃のチャージ時間
			else if (JudgeStr("CHARGE_TIME_LIST"))
			{
				int nIndex, nTime;
				for (int nCntCharge = 0; nCntCharge < ATTACK_PATTARN_NUM; nCntCharge++)
				{
					fscanf(pFile, "%d %*c %d", &nIndex, &nTime);
					m_aCharacterData[nCntCharacter].anChargeTime[nIndex] = nTime;
				}
			}
			// モーションテキスト
			else if (JudgeStr("MOTION_LIST"))
			{
				char cMotionPath[128] = {};
				for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
				{
					fscanf(pFile, "%s %*c %s", &chInTextData, &cMotionPath);

					if      (JudgeStr("IDLE"))   m_aCharacterData[nCntCharacter].aMotionTextPath[MOTION_IDLE]   = cMotionPath;
					else if (JudgeStr("CHARGE")) m_aCharacterData[nCntCharacter].aMotionTextPath[MOTION_CHARGE] = cMotionPath;
					else if (JudgeStr("ATTACK")) m_aCharacterData[nCntCharacter].aMotionTextPath[MOTION_ATTACK] = cMotionPath;
					else if (JudgeStr("ROLL"))   m_aCharacterData[nCntCharacter].aMotionTextPath[MOTION_ROLL] = cMotionPath;
				}
			}
		}

		// ファイルクローズ
		fclose(pFile);
	}
}
