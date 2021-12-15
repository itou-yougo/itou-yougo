//=============================================================================
//
// camera_charaselectヘッダ [camera_charaselect.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CAMERA_CHARA_SELECT_H_
#define _CAMERA_CHARA_SELECT_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "camera_base.h"

//*****************************
// クラス定義
//*****************************

// 三人称カメラクラス
class CCharaSelectCamera : public CCamera
{
public:
	//============
	// メンバ関数
	//============
	CCharaSelectCamera();
	~CCharaSelectCamera();

	// static
	static CCharaSelectCamera *Create(void);  // クラス生成

	HRESULT Init(void);   // 初期化
	void SetCamera(void);

private:
};

#endif