//=============================================================================
//
// �|���S���̕`��̏��� [main.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include <Windows.h>
#include <xaudio2.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

//=============================================================================
// ���C�u�����t�@�C���̃����N
//=============================================================================
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//=============================================================================
// �}�N����`
//=============================================================================
#define SCREEN_WIDTH	(1728)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)				// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W
#define PLAYER_START_POS	(442.5f) 
#define PLAYER2_START_POS	(1286.5f) 
#define NUM_VERTEX		(4)					// ���_��
#define NUM_POLYGON		(2)					// �|���S���̐�
#define MAX_POLYGON (512)					// �|���S���̍ő吔
#define MAX_KEY_NUM (256)					// �L�[�̍ő吔
#define MAX_DRAWORDER (21)					// �D�揇�ʂ̍ő吔
#define PLAYER_SIZE_X	(57.0f)				// ���@�̏c�̒���
#define PLAYER_SIZE_Y	(90.0f)				// ���@�̉��̒���
#define PLAYER_LIFE (5)						// ���@�̗̑�
#define ENEMY_SIZE_X	(104.0f)				// �G�̏c�̒���
#define ENEMY_SIZE_Y	(60.0f)				// �G�̉��̒���
#define MAX_ENEMY_TEXTURE (3)				// �G�̃e�N�X�`���̐�
#define BULLET_SIZE_X (20.0f)				// �e�̏c�̒���
#define BULLET_SIZE_Y (20.0f)				// �e�̉��̒���
#define BOSSBULLET_SIZE_X (80.0f)				// �e�̏c�̒���
#define BOSSBULLET_SIZE_Y (80.0f)				// �e�̉��̒���
#define CHARGEBULLET_SIZE_X (118.0f)				// �e�̏c�̒���
#define CHARGEBULLET_SIZE_Y (200.0f)				// �e�̉��̒���
#define LASERBULLET_SIZE_X (100.0f)				// �e�̏c�̒���
#define LASERBULLET_SIZE_Y (1080.0f)				// �e�̉��̒���
#define BARRIER_SIZE_X	(70.0f)				// �o���A�[�̏c�̒���
#define BARRIER_SIZE_Y	(70.0f)				// �o���A�[�̉��̒���
#define MAX_BG_TEXTURE (4)					// �w�i�̃e�N�X�`���̍ő吔	
#define MAX_SCORE_CREATE (8)				// �X�R�A�̐�������ő吔
#define LIFEPOLYGON_SIZE_X (50.0f)			// ���C�t�̉��̒���
#define LIFEPOLYGON_SIZE_Y (50.0f)			// ���C�t�̏c�̒���
#define BOMB_SIZE_X (100.0f)
#define BOMB_SIZE_Y (100.0f)
#define MAX_LIFEPOLYGON (8)					// �̗͂̐�������ő吔
#define TEXTURE_PLAYER	("data/TEXTURE/player.png")
#define TEXTURE_PLAYER2	("data/TEXTURE/player2.png")
#define TEXTURE_BULLET	("data/TEXTURE/bullet000.png")
#define TEXTURE_BULLETCHARGE	("data/TEXTURE/dekaitama.png")
#define TEXTURE_BULLETLASER	("data/TEXTURE/laser.png")
#define TEXTURE_BULLETBOSSLASER	("data/TEXTURE/bosslaser.png")
#define TEXTURE_EXPLOSION	("data/TEXTURE/explosion000.png")
#define TEXTURE_BOSSEXPLOSION	("data/TEXTURE/pipo-btleffect036.png")
#define TEXTURE_ENEMY1 ("data/TEXTURE/teki.png")
#define TEXTURE_BOSSMAHOU ("data/TEXTURE/bossmahou.png")
#define TEXTURE_BOSSKABOTYA ("data/TEXTURE/bosskabocha.png")
#define TEXTURE_BG1	("data/TEXTURE/haikei.png")
#define TEXTURE_BG2	("data/TEXTURE/bg101.png")
#define TEXTURE_BG3	("data/TEXTURE/bg102.png")
#define TEXTURE_BG4	("data/TEXTURE/frame.png")
#define TEXTURE_BGTUTORIAL	("data/TEXTURE/sousahouhou.png")
#define TEXTURE_BGRESULT	("data/TEXTURE/result.png")
#define TEXTURE_SCORE	("data/TEXTURE/number000.png")
#define TEXTURE_BARRIER_BRUE	("data/TEXTURE/barrier.png")
#define TEXTURE_LIFE	("data/TEXTURE/life.png")
#define TEXTURE_EFFECT_BULLET	("data/TEXTURE/effect000.jpg")
#define TEXTURE_EFFECT_CHARGE	("data/TEXTURE/charge.png")
#define TEXTURE_BOMB	("data/TEXTURE/bomb.png")
#define TEXTURE_BOMBEXPLOSION	("data/TEXTURE/bombexplosion2.png")
#define TEXTURE_ENEMYEXPLOSION1	("data/TEXTURE/enemyexplosion1.png")
#define TEXTURE_ENEMYEXPLOSION2	("data/TEXTURE/enemyexplosion2.png")
#define TEXTURE_GAUGE	("data/TEXTURE/gauge.png")
#define TEXTURE_TIKATIKA	("data/TEXTURE/tikatika.png")
#define TEXTURE_OBAKE ("data/TEXTURE/obake.png")
#define TEXTURE_HONE ("data/TEXTURE/hone.png")
#define TEXTURE_EXTRAEXPLOSION	("data/TEXTURE/extraexplosion.png")
#define TEXTURE_SIROHAIKEI	("data/TEXTURE/sirohaikei.png")
#define TEXTURE_TITLELOGO	("data/TEXTURE/titlelogo.png")
#define TEXTURE_PRESSENTER	("data/TEXTURE/pressenter.png")

#define TEXTURE_READY ("data/TEXTURE/ready.png")
#define TEXTURE_GO ("data/TEXTURE/go.png")
#define TEXTURE_KO ("data/TEXTURE/ko.png")
#define TEXTURE_WON ("data/TEXTURE/won.png")
#define TEXTURE_LOST ("data/TEXTURE/lost.png")
#define TEXTURE_RESTART	("data/TEXTURE/restart.png")
#define TEXTURE_TITLEMODORU ("data/TEXTURE/ttitlemodoru.png")
#define TEXTURE_MENUHAIKEI	("data/TEXTURE/kurohaikei.png")
#define TEXTURE_MENU	("data/TEXTURE/menu.png")

#define TEXTURE_GATTYANN1	("data/TEXTURE/gattyann1.png")
#define TEXTURE_GATTYANN2	("data/TEXTURE/gattyann2.png")
#define TEXTURE_GATTYANN3	("data/TEXTURE/gattyann3.png")
#define TEXTURE_GATTYANN4	("data/TEXTURE/gattyann4.png")
#define TEXTURE_GATTYANN5	("data/TEXTURE/gattyann5.png")
#define TEXTURE_GATTYANN6	("data/TEXTURE/gattyann6.png")
#define TEXTURE_GATTYANN7	("data/TEXTURE/gattyann7.png")
#define TEXTURE_GATTYANN8	("data/TEXTURE/gattyann8.png")

#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw;       //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex; // �e�N�X�`�����W
}VERTEX_2D;

#endif