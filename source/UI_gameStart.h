//==================================================================================================================
//
// �Q�[���J�n����UI���� [ UI_gameStart.h ]
// Author : KANAN NAGANAWA
//
//==================================================================================================================
#ifndef _UI_START_H_
#define _UI_START_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
//
// �|�[�Y�N���X�̒�`
//
//==================================================================================================================
// �O���錾
class CScene2D;

class CUI_GameStart
{
public:
	typedef enum
	{
		GAMEUITEX_ROUND = 0,// Round
		GAMEUITEX_1,		// 1
		GAMEUITEX_2,		// 2
		GAMEUITEX_3,		// 3
		GAMEUITEX_FIGHT,	// Fight
		GAMEUITEX_MAX		// �ő吔
	} GAMEUITEX_TYPE;		// �Q�[���J�n���̃e�N�X�`���̃^�C�v

	CUI_GameStart();			// �R���X�g���N�^
	~CUI_GameStart();		// �f�X�g���N�^
	void Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static CUI_GameStart *Create(void);		// ��������
	static HRESULT Load(void);				// ���[�h
	static void Unload(void);				// �A�����[�h

protected:

private:
	void CreateUI(int type);		// UI�̐���
	static LPDIRECT3DTEXTURE9 m_pTexture[GAMEUITEX_MAX];	// �e�N�X�`�����
	static CScene2D *m_pScene2D[GAMEUITEX_MAX];				// �e�N�X�`��������2DUI
	static char *m_apFileName[GAMEUITEX_MAX];				// �e�N�X�`���̃t�@�C����
	int m_nCntFase;											// �e�N�X�`�������̏���
	int m_nCntAny;											// UI�̈ړ���\���ȂǂɎg��
};
#endif
