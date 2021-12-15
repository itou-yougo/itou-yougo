//=============================================================================
//
// 攻撃範囲 タイプ騎士 [attack_knight.h]
// Author : 吉田悠人
//
//=============================================================================
#ifndef _ATTACK_KNIGHT_H_
#define _ATTACK_KNIGHT_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "attack.h"
#include "scene.h"

//=============================================================================
// クラス定義
//=============================================================================
class CAttackKnight : public CAttackBased
{
public:
	//関数定義
	CAttackKnight();
	~CAttackKnight();

	static CAttackKnight *Create(CPlayer* pPlayer);

private:
	void CreateEffect(D3DXVECTOR3 pos); // エフェクト生成
	//void	AttackCreate(void);	//攻撃生成処理

	//int		m_nAttackCount;		//攻撃までのカウント
	//int		m_nType;			//攻撃の間隔用のタイプ
};
#endif