//==================================================================================================================
//
// �v���C���[[player.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "sceneX.h"
#include "fade.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define TEXTURE_PLAYER "data/TEXTURE/field000.jpg"		// �ǂݍ��ރe�N�X�`���̃\�[�X��
#define PLAYER_MODEL "data/MODEL/testmodel.x"			// �ǂݍ��ރ��f���̃\�[�X��
#define PLAYERSIZE_X	(100)							// �v���C���[��X�T�C�Y
#define PLAYERSIZE_Y	(100)							// �v���C���[��Y�T�C�Y
#define PLAYER_MAX_MODEL (6)							// player.cpp���̃��f���̃p�[�c��
#define CALCULATION_POS_Y 120							// �v�Z����ʒuY

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CMeshOrbit;
class CMotionModel;
class CRecord;
class CModel;
class CMeshField;
class CInputKeyboard;
class CInputGamepad;
class CFade;
class CParticle;
class CEnemy;

//==================================================================================================================
//
// �v���C���[�N���X�̒�`
//
//==================================================================================================================
class CPlayer : public CScene
{
public:
	//=============================================================================
	// �\���̒�`
	//=============================================================================
	// �L�[�v�f
	typedef struct
	{
		D3DXVECTOR3 pos;				// �L�[�v�f�̈ʒu
		D3DXVECTOR3 rot;				// �L�[�v�f�̉�]
	}KEY;

	// �L�[���
	typedef struct
	{
		KEY key[PLAYER_MAX_MODEL];		// �p�[�c��
		int nFram;						// �t���[��
	}KEY_INFO;

	// �v���C���[�̃��[�V����
	typedef struct
	{
		KEY_INFO key_info[10];				// �L�[�����Z�b�g���邩
		D3DXVECTOR3 CollisionOfset;			// �I�t�Z�b�g
		int nLoop;							// ���[�v
		int nNumKey;						// �L�[���̐�
		int Collision_nParts;				// �p�[�c�ԍ�
		int CollisionStartFram;				// �J�n�t���[��
		int CollisionEndFram;				// �I���t���[��
		int Collision_Damage;				// �_���[�W��
		float CollisionRadius;				// �~�̔��a
	}MOTION_PLAYER;

	// ���[�V�����̃^�C�v
	typedef enum
	{
		PLAYER_MOTION_NORMAL = 0,			// �j���[�g����
		PLAYER_MOTION_WALK,					// ����
		PLAYER_MOTION_ACTION,				// �A�N�V����
		PLAYER_MOTION_JUMP,					// �W�����v
		PLAYER_MOTION_LANDING,				// ���n
		PLAYER_MOTION_DAMAGE,				// �_���[�W
		PLAYER_MOTION_MAX					// ���[�V�����̍ő吔
	}PLAYER_MOTION_STATE;

	CPlayer(PRIORITY type);							// �R���X�g���N�^
	~CPlayer();										// �f�X�g���N�^
	void Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static CPlayer *Create(void);					// ��������

	void SetPos(D3DXVECTOR3 pos);					// �ʒu�ݒ菈��
	void SetRot(D3DXVECTOR3 rot);					// ��]�ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// ��]�擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �ړ��ʎ擾����

protected:

private:
	void LoadMotion(void);							// ���[�V�����ǂݍ���
	void Moation(void);								// ���[�V����������
	void OperationMove(CInputKeyboard *pInputKeyboard, 
		CInputGamepad *pInputGamepad);				// ���쏈��

	float MeshFieldUpdate(CMeshField *pMeshField);	// �v���C���[���ł̃��b�V���t�B�[���h�̍X�V����

	CMotionModel *m_MotionModel[PLAYER_MAX_MODEL];	// ���f�����
	MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];// ���[�V�������
	D3DXMATRIX  m_mtxWorld;							// �}�g���b�N�X

	static CCamera *m_pCamera;				// �J�����̏��|�C���^
	static CMeshOrbit *m_pMeshOrbit;		// �O�Ղ̏��|�C���^
	static CRecord *m_pRecord;				// �L�^���|�C���^
	static CParticle *m_pParticle;			// �p�[�e�B�N�����|�C���^
	static CEnemy *m_pEnemy;				// �G���|�C���^

	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_posOld;					// �O��̈ʒu
	D3DXVECTOR3 m_rot;						// ��]
	D3DXVECTOR3 m_move;						// �ړ�
	D3DXVECTOR3 m_size;						// �傫��
	D3DXVECTOR3 m_difference;				// ��]�̖ڕW�n�_
	D3DXVECTOR3 posBET[PLAYER_MAX_MODEL];	// �e�p�[�c�̈ʒu
	D3DXVECTOR3 rotBET[PLAYER_MAX_MODEL];	// �e�p�[�c�̉�]
	D3DXVECTOR3 m_RespownPos;				// ���X�|�[���ʒu
	D3DXVECTOR3 m_RespownRot;				// ���X�|�[����]

	int m_MotionType;						// ���[�V�����̎��
	int m_MotionOld;						// �O�̃��[�V����
	int m_Fram;								// �t���[��
	int m_nCntKeySet;						// �L�[�Z�b�g�̃J�E���g
	int m_nCntState;						// �X�e�[�^�X�̃J�E���g
	int m_nCntGravity;						// �d�͗p�J�E���g

	float m_RotModel;						// ���f���̉�]���
	float m_fStickMove;						// �R���g���[���[�̃X�e�B�b�N�̈ړ���

	bool m_bJump;							// �W�����v�������ǂ���
};
#endif