//=============================================================================
//
// paint_timeヘッダ [paint_time.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _PAINT_TIME_H_
#define _PAINT_TIME_H_

//*****************************
//インクルード
//*****************************
#include "scene3d.h"
#include "tile_effect.h"

//*****************************
//マクロ定義
//*****************************
#define PAINT_TIME_POLYGON_NUM 2 //使う板ポリの数

//*****************************
//前方宣言
//*****************************
class CScene3d;

//*****************************
//クラス定義
//*****************************

// 再塗可能時間の可視化
class CPaintTime : public CTileEffect
{
public:
	// 列挙
	// パーツ
	typedef enum
	{
		PARTS_FRAME = 0, // 枠
		PARTS_HANDS,     // 針
		PARTSMAX
	}PARTS;

	// メンバ関数
	CPaintTime();
	~CPaintTime();
	static CPaintTime *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);
	void SetPaintTime(int nFrame);

private:
	// メンバ変数
	CScene3d* m_apPolygon[PAINT_TIME_POLYGON_NUM];
	int m_nFrame; // フレーム数
	int m_nCntFrame;
	
};


#endif