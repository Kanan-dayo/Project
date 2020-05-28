//==================================================================================================================
//
// �L�����N�^�[[character.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "sceneX.h"
#include "fade.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MAX_CHARA 2							// �L�����N�^�[�̍ő吔

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CMotionModel;
class CMeshField;
class CInputKeyboard;
class CInputGamepad;
class CPlayer;

//==================================================================================================================
//
// �v���C���[�N���X�̒�`
//
//==================================================================================================================
class CCharacter : public CScene
{
public:

	// �L�����N�^�[�̎��
	typedef enum
	{
		CHARACTER_PENGUIN = 0,						// �y���M��
		CHARACTER_MAX								// �ő�
	}CHARACTER;										// �L�����N�^�[�ϐ���

	CCharacter(PRIORITY type);						// �R���X�g���N�^
	~CCharacter();									// �f�X�g���N�^
	void Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	void SetPos(D3DXVECTOR3 pos);					// �ʒu�ݒ菈��
	void SetRot(D3DXVECTOR3 rot);					// ��]�ݒ菈��
	void SetSize(D3DXVECTOR3 size);					// �傫���ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// ��]�擾����
	D3DXVECTOR3 GetSize(void) { return m_size; }	// �傫���擾����

protected:
	D3DXVECTOR3 m_pos;			// �ʒu
	D3DXVECTOR3 m_posOld;		// �O��̈ʒu
	D3DXVECTOR3 m_rot;			// ��]
	D3DXVECTOR3 m_difference;	// ��]�̖ڕW�n�_
	D3DXVECTOR3 m_move;			// �ړ�
	D3DXVECTOR3 m_size;			// �傫��
	D3DXMATRIX  m_mtxWorld;							// �}�g���b�N�X

private:

	void OperationMove(CInputKeyboard *pInputKeyboard,
		CInputGamepad *pInputGamepad);				// ���쏈��

	CHARACTER m_Type;								// �L�����N�^�[�̎��

	static CCharacter *m_pCharacter[MAX_CHARA][CHARACTER_MAX];	// �L�����N�^�[�̏��|�C���^
	static CCamera *m_pCamera;									// �J�����̏��|�C���^
	static CPlayer *m_pPenguin;									// �y���M���̏��|�C���^
	static int m_nNumAll;										// �v���C���[�̐l��

	bool m_bJump;				// �W�����v�������ǂ���
	bool m_bWalk;				// �����Ă邩�ǂ���
};
#endif