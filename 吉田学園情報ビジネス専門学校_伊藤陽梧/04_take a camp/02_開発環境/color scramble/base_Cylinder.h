//=============================================================================
//
// べーすの円柱定義 [base_Cylinder.h]
// Author : 齋藤大行
//
//=============================================================================


//二重インクルード防止
#ifndef _BASE_CYLINDERH_
#define _BASE_CYLINDERH_

//=============================================================================
// インクルードファイル
//=============================================================================

#include "main.h"
#include "scene.h"

//*****************************
//マクロ定義
//*****************************
#define NUM_CYL_VERTEX (20)


//=============================================================================
// クラス定義
//=============================================================================
class Cbase_Cylinder : public CScene
{
public:
	//============
	//メンバ関数
	//============
	Cbase_Cylinder(int nPliority = OBJTYPE_PARTICLE);
	~Cbase_Cylinder();

	// static
	static Cbase_Cylinder *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size ,const D3DXCOLOR col); // クラス生成

	virtual HRESULT Init(void); // 初期化
	virtual void Uninit(void);  // 終了
	virtual void Update(void);  // 更新
	virtual void Draw(void);    // 描画

	 LPDIRECT3DTEXTURE9 GetTexture(void) { return m_apTexture; }
	 void BindTexture(const LPDIRECT3DTEXTURE9 pTexture) { m_apTexture = pTexture; }

	// 中心座標のセット、取得
	void SetPos(const D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	// 向きのセット、取得
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	// 移動量の取得・セット
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	// 回転角度のセット、取得
	void SetAddRotValue(const float fAdd) { m_fRotAngle = fAdd;}
	float GetAddRotValue(void) { return m_fRotAngle; }
	// サイズのセット、取得
	void SetSize(const D3DXVECTOR3 size);
	D3DXVECTOR3 GetSize(void) { return m_size; }
	// カラーのセット、取得
	void SetColor(const D3DXCOLOR col);
	D3DXCOLOR GetColor(void) { return m_col; }

	void SetHighRot(const float rot) { m_fHighRot = rot; }
	void SetRowRot(const float rot) { m_fRowRot = rot; }

	void SetAddMode(bool bBool) { m_bAddMode = bBool; }
	void SetTextureUV(const float pos); // テクスチャのUV座標のセット
private:
	//============
	// メンバ変数
	//============
	LPDIRECT3DTEXTURE9		m_apTexture;	    // テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	    // 頂点バッファへのポインタ
	D3DXVECTOR3			    m_pos;	 	    // 位置
	D3DXVECTOR3			    m_move;	 	    // 移動量
	D3DXVECTOR3			    m_rot;	 	    // 向き
	D3DXVECTOR3	            m_size;		    // 大きさ
	
	int                     m_nLife;	    // 寿命
	float					m_fHighRot;		// 上辺角度
	float					m_fRowRot;		// 下辺角度
	float		            m_fRotAngle;    // 回転角度
	float		            m_fFadeout;	    // フェードアウト　
	bool		            m_bFadeoutFlag; // フェードアウトのフラグ
	D3DXCOLOR	            m_col;		    // 色
	D3DXMATRIX				m_mtxWorld;     // ワールドマトリックス
	bool					m_bAddMode;     // 加算合成か
};										    

#endif
