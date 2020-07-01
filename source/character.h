// ===================================================================
//
// �L�����N�^�[���� [ character.h ]
// Author : Seiya Takahashi
//
// ===================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "scene.h"
#include "motion.h"
#include "kananlibrary.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CModelCharacter;

class CCharacter : public CScene
{
public:
	CCharacter(CScene::PRIORITY nPriority);
	~CCharacter();

	void Init(void);								// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	void Draw(void);								// �`��

	void SetPos(const D3DXVECTOR3 & pos)			{ m_pos = pos; }			// �ʒu�̐ݒ�
	void SetMove(const D3DXVECTOR3 & move)			{ m_move = move; }			// �ړ��l�̐ݒ�
	void SetRot(const D3DXVECTOR3 & rot)			{ m_rot = rot; }			// ��]�̐ݒ�
	void SetRotDest(const D3DXVECTOR3 & rotDest)	{ m_rotDest = rotDest; }	// �ړI�̉�]�̐ݒ�
	void SetbWalk(const bool &bWalk)				{ m_bWalk = bWalk; }		// �����̐ݒ�
	void SetbJump(const bool &bJump)				{ m_bJump = bJump; }		// �W�����v�̐ݒ�
	void SetLife(const float nLife)					{ m_nLife = nLife; }		// ���C�t�̐ݒ�
	void SetModelType(CHARACTER_TYPE type);			// ���f���̐ݒ�

	D3DXVECTOR3 GetPos(void)		{ return m_pos; }		// �ʒu�̎擾
	D3DXVECTOR3 GetMove(void)		{ return m_move; }		// �ړ��l�̎擾
	D3DXVECTOR3 GetRot(void)		{ return m_rot; }		// ��]�̎擾
	D3DXVECTOR3 GetRotDest(void)	{ return m_rotDest; }	// ��]��̎擾
	float		GetMaxLife(void)	{ return m_nMaxLife; }	// �ő僉�C�t�擾
	float		GetLife(void)		{ return m_nLife; }		// ���C�t�擾

	void Damage(const float nDamage)	{ m_nLife -= nDamage; }	// �_���[�W����

protected:
	CModelCharacter *m_pModelCharacter;				// ���f���L�����N�^�[�̃|�C���^
	CHARACTER_TYPE	 m_type;						// �L�����N�^�[�̃^�C�v

	LPD3DXMESH		m_pMesh;						// ���b�V�����
	LPD3DXBUFFER	m_pBuffMat;						// �}�e���A�����
	DWORD			m_nNumMat;						// �}�e���A�����̐�

	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_posBegin;							// �����ʒu
	D3DXVECTOR3 m_move;								// �ړ��l
	D3DXVECTOR3 m_rot;								// ��]
	D3DXVECTOR3 m_rotDest;							// �ړI�̉�]
	D3DXVECTOR3 m_rotDif;							// ��]�̍�
	D3DXMATRIX	m_mtxWorld;							// ���[���h�}�g���b�N�X

	int			m_nCntMove;							// �ǂꂮ�炢�̎��ԓ����Ă��邩
	float		m_nLife;							// ���C�t
	float		m_nMaxLife;							// �ő僉�C�t
	bool		m_bJump;							// �W�����v�������ǂ���
	bool		m_bWalk;							// �����Ă邩�ǂ���
	bool		m_bTrans;							// �ϐg���Ă��邩

	static int	m_nNumCharacter;					// �L�����N�^�[�̑���

private:
	void Move(void);								// �ړ��֐�
	void Rot(void);									// ��]�֐�
	void Motion(void);								// ���[�V�����֐�
	void Trans(void);								// �ϐg�֐�
};

#endif
