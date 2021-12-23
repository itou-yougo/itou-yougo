//=============================================================================
//
// stage_tectureヘッダ [stage_tecture.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _STAGE_TEXTURE_H_
#define _STAGE_TEXTURE_H_

//*****************************
// インクルード
//*****************************
#include "dynamic_texture.h"

//*****************************
// クラス定義
//*****************************

//ステージクラス
class CStageTexture : public CDynamicTexture
{

	//============
	// メンバ関数
	//============
private:
	CStageTexture(); // 隠しコンストラクタ
public:
	~CStageTexture();

	// static
	static CStageTexture *Create(D3DXVECTOR2 size);  // クラス生成
	static void Release(void);

	void DrawStageInTex(void);
	static CStageTexture*GetStateTexturePointa(void) { return m_pInstance; }
	
private:
	// メンバ変数
	const static std::vector<int> m_anDrawObjNum;         // 描画するオブジェクト番号
	static CStageTexture*m_pInstance;

};

#endif