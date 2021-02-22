//=============================================================================
//
// �i���o�[�̏��� [number.h]
// Author : �ɓ��z��
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NUMBER ("data/TEXTURE/number001.png")

//=============================================================================
//	�i���o�[�N���X
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	static CNumber * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9   m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
	int m_nPatternAnim;//�e�N�X�`���p�^�[��
	int m_nAlpha;
};

#endif // !_NUMBER_H_