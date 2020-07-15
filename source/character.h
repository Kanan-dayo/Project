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
#define TIME_TRANS		(15 * ONE_SECOND_FPS)	// �ϐg�̎���

// ===================================================================
// �N���X��`
// ===================================================================
class CModelCharacter;
class CCylinderCoillider;

class CCharacter : public CScene
{
public:
	enum COLLIPARTS
	{
		COLLIPARTS_NONE = -1,	// �Ȃ�
		COLLIPARTS_FOREARM_R,	// �E�O�r
		COLLIPARTS_UPPERARM_R,	// �E��r
		COLLIPARTS_FOREARM_L,	// �O�r
		COLLIPARTS_UPPERARM_L,	// ��r
		COLLIPARTS_MAX			// �ő�
	};

	CCharacter(CScene::PRIORITY nPriority);			// �R���X�g���N�^
	~CCharacter();									// �f�X�g���N�^

	void               Init(void);					// ������
	void               Uninit(void);				// �I��
	void               Update(void);				// �X�V
	void               Draw(void);					// �`��

	inline void        SetPos(const D3DXVECTOR3 & pos)			{ m_pos = pos; }			// �ʒu�̐ݒ�
	inline void        SetMove(const D3DXVECTOR3 & move)		{ m_move = move; }			// �ړ��l�̐ݒ�
	inline void        SetRot(const D3DXVECTOR3 & rot)			{ m_rot = rot; }			// ��]�̐ݒ�
	inline void        SetRotDest(const D3DXVECTOR3 & rotDest)	{ m_rotDest = rotDest; }	// �ړI�̉�]�̐ݒ�
	inline void        SetbWalk(const bool &bWalk)				{ m_bWalk = bWalk; }		// �����̐ݒ�
	inline void        SetbJump(const bool &bJump)				{ m_bJump = bJump; }		// �W�����v�̐ݒ�
	inline void        SetLife(const float nLife)				{ m_nLife = nLife; }		// ���C�t�̐ݒ�
	void               SetModelType(CHARACTER_TYPE type);									// ���f���̐ݒ�
	void               SetCylinderCoillider(void);											// �V�����_�[�R���C�_�[�̐ݒ�

	inline D3DXVECTOR3 GetPos(void)		{ return m_pos; }			// �ʒu�̎擾
	inline D3DXVECTOR3 GetMove(void)	{ return m_move; }			// �ړ��l�̎擾
	inline D3DXVECTOR3 GetRot(void)		{ return m_rot; }			// ��]�̎擾
	inline D3DXVECTOR3 GetRotDest(void)	{ return m_rotDest; }		// ��]��̎擾
	inline float       GetMaxLife(void)	{ return m_nMaxLife; }		// �ő僉�C�t�擾
	inline float       GetLife(void)	{ return m_nLife; }			// ���C�t�擾

	inline void        Damage(const int nDamage)	{ m_nLife -= nDamage; }	// �_���[�W����
	void			   Daunted(const int nGap);		// ���ݏ���

protected:
	CModelCharacter *m_pModelCharacter;					// ���f���L�����N�^�[�̃|�C���^
	CHARACTER_TYPE	 m_type;							// �L�����N�^�[�̃^�C�v
	CHARACTER_TYPE	 m_typeTrans;						// �ϐg���̃^�C�v

	LPD3DXMESH		m_pMesh;							// ���b�V�����
	LPD3DXBUFFER	m_pBuffMat;							// �}�e���A�����
	DWORD			m_nNumMat;							// �}�e���A�����̐�

	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_posOld;								// �O��̈ʒu
	D3DXVECTOR3 m_posBegin;								// �����ʒu
	D3DXVECTOR3 m_move;									// �ړ��l
	D3DXVECTOR3 m_rot;									// ��]
	D3DXVECTOR3 m_rotDest;								// �ړI�̉�]
	D3DXVECTOR3 m_rotDif;								// ��]�̍�
	D3DXMATRIX	m_mtxWorld;								// ���[���h�}�g���b�N�X

	CCylinderCoillider* m_pCyliColi[COLLIPARTS_MAX];	// �V�����_�[�R���C�_�[�|�C���^

	int			m_nCntMove;								// �ǂꂮ�炢�̎��ԓ����Ă��邩
	int			m_nCntTrans;							// �ǂꂮ�炢�̎��ԕϐg���Ă��邩
	int			m_nNumStone;							// �擾�����X�g�[���̐�
	float		m_nLife;								// ���C�t
	float		m_nMaxLife;								// �ő僉�C�t
	bool		m_bJump;								// �W�����v�������ǂ���
	bool		m_bWalk;								// �����Ă邩�ǂ���
	bool		m_bTrans;								// �ϐg���Ă��邩
	bool		m_bAttack;								// �U�����Ă��邩
	bool		m_bBlowAway;							// �������ł��邩
	bool		m_bSmashBlowAway;						// �X�}�b�V���Ő������ł��邩
	bool		m_bDaunted;								// �Ђ��ł��邩
	static int	m_nNumCharacter;						// �L�����N�^�[�̑���
	int			m_nCntJump;								// �W�����v���[�V�����؂�ւ��̃J�E���^
	int			m_nAttackFrame;							// �U�����[�V�����؂�ւ��̃J�E���^
	int			m_nAttackFlow;							// �U���̗���
	int			m_nCntGap;								// ���̃J�E���^

	bool		m_bAttakHit;							// �U���𓖂Ă��t���O

private:
	void Move(void);									// �ړ��֐�
	void Rot(void);										// ��]�֐�
	void Motion(void);									// ���[�V�����֐�
	void Trans(void);									// �ϐg�֐�
	void IchiyasuMotion(void);							// 1���X�̃��[�V����
};

#endif
