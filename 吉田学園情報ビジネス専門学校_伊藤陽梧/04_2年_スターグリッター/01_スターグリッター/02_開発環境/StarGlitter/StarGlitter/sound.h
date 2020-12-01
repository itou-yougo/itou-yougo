//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
// �T�E���h�N���X
//=============================================================================
class CSound
{
public:
	CSound();
	~CSound();

	typedef enum
	{
		SOUND_LABEL_BULLET_SE = 0, // �e�̔��ˉ�
		SOUND_LABEL_EXPLOSION_SE,  // ������
		SOUND_LABEL_BOSSCREATE,	   // �{�X�A�^�b�N�̉�
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
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
