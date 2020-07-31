//==================================================================================================================
//
// �Q�[������[game.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _GAME_H
#define _GAME_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include <memory>	// �X�}�[�g�|�C���^�̎g�p�ɕK�v

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define STONE_POS (5)
#define POLYCOLLI_USE_TYPE	4

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CMeshField;
class CCamera;
class CLight;
class CLogo;
class CModel;
class CPause;
class CMeshSphere;
class CPlayer;
class CTime;
class CWall;
class CObjectManager;
class CPolygonCollider;

//==================================================================================================================
//
// �Q�[���N���X�̒�`
//
//==================================================================================================================
class CGame
{
public:
	// ==========================================================
	// �Q�[���̏��
	// ==========================================================
	typedef enum
	{
		GAMESTATE_NONE = 0,		// �������Ă��Ȃ����
		GAMESTATE_NORMAL,		// �ʏ���
		GAMESTATE_PAUSE,		// �|�[�Y���
		GAMESTATE_START_OVER,	// ���߂����蒼��
		GAMESTATE_BREAK,		// �Q�[�����f
		GAMESTATE_END,			// �Q�[���̏I��
		GAMESTATE_MAX			// �ő�
	} GAMESTATE;				// �Q�[���̏��

	CGame();									// �R���X�g���N�^
	~CGame();									// �f�X�g���N�^
	void Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��
	static CGame *Create(void);					// ��������

	static void SetGameState(GAMESTATE state)	{ m_gameState = state; }	// �Q�[���̏�Ԑݒ�
	static void RemoveNumStone(int nIndexPos)	{ m_nNumStone--; m_bSetPos[nIndexPos] = false; }			// �X�g�[���̐������Z
	static void SetNumStone(const int &nStone)	{ m_nNumStone = nStone; }	// �X�g�[���̐��̐ݒ�

	static GAMESTATE GetGameState(void)			{ return m_gameState; }			// �Q�[���̏�Ԏ擾
	static CPlayer *GetPlayer(int nPlayer)		{ return m_pPlayer[nPlayer]; }	// �L�����N�^�[�̏��擾����
	static CCamera *GetCamera(void)				{ return m_pCamera; }			// �J�����̎擾
	static CLight *GetLight(void)				{ return m_pLight; }			// ���C�g�̎擾
	static CMeshField *GetMeshField(void)		{ return m_pMeshField; }		// ���b�V���t�B�[���h�̎擾
	static int GetNumStone(void)				{ return m_nNumStone; }			// �X�g�[���̐����擾
	static CWall *GetWall(void)					{ return m_pWall; }				// �ǂ̎擾
	static CObjectManager *GetObjMana(void)		{ return m_pObjMana; }			// �I�u�W�F�N�g�}�l�[�W���[���擾

	static CPolygonCollider* GetpolyColly(int nIndex) { return m_pPolyColli[nIndex]; }

	static void AppearStone(void);				// �ǂ�����ł��Ăяo����X�g�[���o��

protected:

private:
	void DecideCreateStone(void);				// �X�g�[���𐶐����邩���߂�
	static int DecideRandomPos(void);			// �����ʒu�������_���Ō��߂�
	static GAMESTATE m_gameState;				// �Q�[�����
	static CPlayer *m_pPlayer[MAX_PLAYER];		// �v���C���[�̔z��|�C���^
	static CMeshField *m_pMeshField;			// ���b�V���t�B�[���h�̏��|�C���^
	static CCamera *m_pCamera;					// �J�����̏��|�C���^
	static CLight *m_pLight;					// ���C�g�̏��|�C���^
	static CLogo *m_pLogo;						// ���S�̏��|�C���^
	static CPause *m_pPause;					// �|�[�Y�̏��|�C���^
	static CMeshSphere *m_pMeshSphere;			// ���b�V�����̏��|�C���^
	static CTime *m_pTime;						// �^�C���̏��|�C���^
	static CWall *m_pWall;						// �ǂ̃|�C���^
	static int m_nCounterGameState;				// �Q�[���̏�ԊǗ��J�E���^�[
	static int m_nNumStone;						// ���������X�g�[���̐�
	static int m_nCntDecide;					// �X�g�[�������̃^�C�~���O�����߂�J�E���^
	static D3DXVECTOR3 m_stonePos[STONE_POS];	// �X�g�[���̐����ꏊ
	static bool m_bSetPos[STONE_POS];			// �X�g�[������������Ă��邩
	static CObjectManager *m_pObjMana;			// �I�u�W�F�N�g�}�l�[�W���[�̃|�C���^
	static CPolygonCollider* m_pPolyColli[POLYCOLLI_USE_TYPE];		// �|���S���R���C�_�[�̃|�C���^
	D3DXMATRIX  m_mtxWorld;						// �}�g���b�N�X
};
#endif
