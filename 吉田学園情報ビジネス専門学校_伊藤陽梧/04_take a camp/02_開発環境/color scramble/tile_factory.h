//=============================================================================
//
// tile_factoryヘッダ [tile_factory.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _TILE_FACTORY_H_
#define _TILE_FACTORY_H_

//*****************************
// インクルード
//*****************************
#include "main.h"

//*****************************
//前方宣言
//*****************************
class CTile;

//*****************************
//マクロ定義
//*****************************

//*****************************
// クラス定義
//*****************************

// タイルクラス
class CTileFactory
{
private:
	// 隠しコンストラクタ
	CTileFactory();
public:
	// 関数ポインタ
	typedef void(*CTileFactory::SENTENCE_FUNC)(D3DXVECTOR3, D3DXCOLOR);

	typedef struct
	{
		std::string strLabelName;
		SENTENCE_FUNC createFunction;
	}LabelData;

	//メンバ関数
	~CTileFactory();

	static CTileFactory* Create(void);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	static void Release(void);

	static CTileFactory * GetTileFactory(void) { return m_pInstance; }

	SENTENCE_FUNC GetCreateFunction(int nIndex) { return m_CreateSentence[nIndex]; }
private:
	void LoadTileData(void);
	// メンバ変数
	static std::vector<SENTENCE_FUNC>m_CreateSentence;// 関数ポインタ
	static CTileFactory*m_pInstance;
	static const std::vector<LabelData> m_cLabelData;
};

#endif