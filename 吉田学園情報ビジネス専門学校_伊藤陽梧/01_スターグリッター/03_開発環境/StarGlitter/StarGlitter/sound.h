//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 伊藤陽梧
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
// サウンドクラス
//=============================================================================
class CSound
{
public:
	CSound();
	~CSound();

	typedef enum
	{
		SOUND_LABEL_BULLET_SE = 0, // 弾の発射音
		SOUND_LABEL_EXPLOSION_SE,  // 爆発音
		SOUND_LABEL_BOSSCREATE,	   // ボスアタックの音
		SOUND_LABEL_GAMEBGM,
		SOUND_LABEL_KO,
		SOUND_LABEL_MENUCREATE,
		SOUND_LABEL_MENUKETTEI,
		SOUND_LABEL_MENUKIRIKAE,
		SOUND_LABEL_PRESSENTER,
		SOUND_LABEL_CHARGE,
		SOUND_LABEL_TITLEBGM,
		SOUND_LABEL_CHARGESHOT,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	// 各音素材のパラメータ
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
