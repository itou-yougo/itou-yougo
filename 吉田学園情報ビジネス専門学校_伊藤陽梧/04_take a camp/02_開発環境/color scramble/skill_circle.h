//=============================================================================
//
// スキルエフェクト定義 [skill_circle.h]
// Author : 齋藤大行
//
//=============================================================================

//二重インクルード防止
#ifndef _SKILL_CIRCLE_
#define _SKILL_CIRCLE_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "base_Cylinder.h"
//*****************************
//マクロ定義
//*****************************
#define NORMAL_SKIIL_HIGHROT (1.0f)
#define NORMAL_SKIIL_ROWROT (1.7f)
#define NORMAL_SKIIL_SIZE D3DXVECTOR3(10.5f,9.5f,10.5f)
#define NORMAL_SKIIL_POS D3DXVECTOR3(0.0f,0.0f,0.0f)
#define NORMAL_SKIIL_COL D3DXCOLOR(0.0f,0.0f,0.0f)


//=============================================================================
// クラス定義
//=============================================================================
class CSkill_circle : public Cbase_Cylinder
{
public:
	//============
	//メンバ関数
	//============
	CSkill_circle(int nPliority = OBJTYPE_PARTICLE);
	~CSkill_circle();



	//============
	// 状態列挙
	//============
	// エフェクトタイプ列挙
	
	typedef enum
	{
		EFFECTTYPE_SKIIL = 0,
		EFFECTTYPE_SKIILMINI,
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	// static
	static CSkill_circle *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col , const EFFECTTYPE type); // クラス生成

	virtual HRESULT Init(void); // 初期化
	virtual void Uninit(void);  // 終了
	virtual void Update(void);  // 更新
	virtual	void Draw(void);    // 描画
	LPDIRECT3DTEXTURE9 GetTexture(void) { return m_apTexture[EFFECTTYPE_MAX]; }


private:
	//============
	// メンバ変数
	//============
	LPDIRECT3DTEXTURE9		m_apTexture[EFFECTTYPE_MAX];	    // テクスチャへのポインタ
	D3DXVECTOR3			    m_pos;	 	    // 位置
	D3DXVECTOR3			    m_move;	 	    // 移動量
	D3DXVECTOR3			    m_rot;	 	    // 向き
	D3DXVECTOR3	            m_size;		    // 大きさ
	int                     m_nLife;	    // 寿命
	float		            m_fRotAngle;    // 回転角度
	float		            m_fFadeout;	    // フェードアウト　
	bool		            m_bFadeoutFlag; // フェードアウトのフラグ
	bool					m_bAddMode;     // 加算合成
	D3DXCOLOR	            m_col;		    // 色
	D3DXMATRIX				m_mtxWorld;     // ワールドマトリックス
	EFFECTTYPE				m_type;			// エフェクトのタイプ
};

#endif
