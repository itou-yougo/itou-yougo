//===================================================
//
// キャラのポリゴンの処理 [caharacter_polygon.h]
// Author : 増澤未来
//
//===================================================
#ifndef  _CHARACTER_POLYGON_H_
#define  _CHARACTER_POLYGON_H_

//===================================================
// インクルードファイル
//===================================================
#include "scene2d.h"
#include "resource_character.h"

//===================================================
// 前方宣言
//===================================================
class CDynamicTexture;
class CPlayerModel;

//===================================================
// マクロ定義
//===================================================
#define DEFAULT_CHARACTER_POLYGON_SIZE (D3DXVECTOR3(300.0f,400.0f,0.0f))

//===================================================
// クラス宣言
//===================================================
class CCharacterPolygon : public CScene2d
{
public:
	//===============================================
	// 列挙
	//===============================================
	enum CharaPolygonMode
	{
		MODE_NONE = 0,
		MODE_ROTATION,
	};

	//===============================================
	// メンバ関数
	//===============================================
    CCharacterPolygon();
    ~CCharacterPolygon();

    static CCharacterPolygon *Create(D3DXVECTOR3 pos, CharaPolygonMode mode = MODE_NONE);    // 生成処理
    HRESULT Init(void);             // 初期化処理
    void Uninit(void);              // 終了処理
    void Update(void);              // 更新処理
    void Draw(void);                // 描画処理

	// キャラタイプのセット・取得
	void SetCharaType(CResourceCharacter::CHARACTER_TYPE type);
	CResourceCharacter::CHARACTER_TYPE GetCharaType(void) { return m_charaType; }
	void SetRimColor(D3DXCOLOR col);
	void SetTexColor(D3DXCOLOR col);

	CPlayerModel*GetCharaModel(void) { return m_pCharacterModel; }
private:
    //===============================================
    // メンバ変数宣言
    //===============================================
    CDynamicTexture *m_pDynamicTex;          // 動的テクスチャクラス
    CPlayerModel    *m_pCharacterModel;      // キャラクターも出る
    CResourceCharacter::CHARACTER_TYPE m_charaType; // キャラクタータイプ
	CharaPolygonMode m_mode;

};
#endif
