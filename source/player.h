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
#include "character.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define TEXTURE_PLAYER "data/TEXTURE/field000.jpg"		// �ǂݍ��ރe�N�X�`���̃\�[�X��
#define PLAYER_MODEL "data/MODEL/testmodel.x"			// �ǂݍ��ރ��f���̃\�[�X��
#define PLAYER_MAX_MODEL (6)							// player.cpp���̃��f���̃p�[�c��

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CMotionModel;
class CMeshField;
class CInputKeyboard;
class CInputGamepad;
class CFade;

//==================================================================================================================
//
// �v���C���[�N���X�̒�`
//
//==================================================================================================================
class CPlayer : public CCharacter
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

protected:

private:
	/*CMotionModel *m_MotionModel[PLAYER_MAX_MODEL];	// ���f�����
	MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];// ���[�V�������

	static CCamera *m_pCamera;				// �J�����̏��|�C���^

	D3DXVECTOR3 posBET[PLAYER_MAX_MODEL];	// �e�p�[�c�̈ʒu
	D3DXVECTOR3 rotBET[PLAYER_MAX_MODEL];	// �e�p�[�c�̉�]

	int m_MotionType;						// ���[�V�����̎��
	int m_MotionOld;						// �O�̃��[�V����
	int m_Fram;								// �t���[��
	int m_nCntKeySet;						// �L�[�Z�b�g�̃J�E���g
	int m_nCntState;						// �X�e�[�^�X�̃J�E���g

	float m_RotModel;						// ���f���̉�]���*/
};
#endif