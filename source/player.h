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
class CHitPoint;
class CPlayer;

//==================================================================================================================
//
// �v���C���[�N���X�̒�`
//
//==================================================================================================================
class CPlayer : public CCharacter
{
public:
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

	static CPlayer *Create(int nPlayer, CHARACTER_TYPE type);	// ��������
	static CPlayer *GetPlayer(int nPlayer) { return m_pPlayer[nPlayer]; }// �v���C���[���擾����

	int GetNumStone(void)	{ return m_nNumStone; }	// �擾�����X�g�[���̐����擾
	int GetnPlayer(void) { return m_nPlayer; }		// �v���C���[�ԍ��擾
	inline int GetBoxColliderID(void) { return m_nBoxColliderID; }
protected:

private:
	void Control(void);								// ����֐�
	void Collision(void);							// �����蔻��֐�
	void Attack(void);								// �U���֐�

	CPlayer*GetAnotherPlayer(void);					// �Ⴄ�v���C���[�̎擾
	static CPlayer *m_pPlayer[MAX_PLAYER];			// �v���C���[���
	static CHitPoint *m_pHitPoint;					// HP���

	void ControlGamepad(CInputGamepad *pGamepad);	// �Q�[���p�b�h����
	void ControlKeyboard(CInputKeyboard *pKeyboard);// �L�[�{�[�h����
	void CatchStone(void);							// �X�g�[���̎擾����
	void SetnPlayer(int nPlayerNum);				// �v���C���[�ԍ��ݒ菈��

	inline bool BlowAway(CPlayer *pAnother);		// �������

	int m_nPlayer;			// �v���C���[�ԍ�
	int m_nBoxColliderID;	// �{�b�N�X�R���C�_�[ID

#ifdef _DEBUG
	void ShowDebugInfo(void);									// ImGui�̍X�V
#endif
};
#endif