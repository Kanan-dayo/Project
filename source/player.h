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
class CTransformBar;

//==================================================================================================================
//
// �v���C���[�N���X�̒�`
//
//==================================================================================================================
class CPlayer : public CCharacter
{
public:
	CPlayer(PRIORITY type);							// �R���X�g���N�^
	~CPlayer();										// �f�X�g���N�^
	void Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static CPlayer *Create(int nPlayer, CHARACTER_TYPE type);	// ��������

	int GetNumStone(void)	{ return m_nNumStone; }	// �擾�����X�g�[���̐����擾
	int GetnPlayer(void) { return m_nPlayer; }		// �v���C���[�ԍ��擾
	inline int GetBoxColliderID(void) { return m_nBoxColliderID; }
	CPlayer*GetAnotherPlayer(void);					// �Ⴄ�v���C���[�̎擾


	bool ReadyToHit(const int &nCapColliID);			// �U�����Ă鏀�����ł��Ă��邩
	bool HitConditionAttack0(const int &nCapColliID);	// �U��0�𓖂Ă����
	bool HitConditionAttack1(const int &nCapColliID);	// �U��1�𓖂Ă����
	bool HitConditionAttack2(const int &nCapColliID);	// �U��2�𓖂Ă����
	bool HitConditionAttack3(const int &nCapColliID);	// �U��3�𓖂Ă����
	bool HitConditionSmash(const int &nCapColliID);		// �X�}�b�V���U�𓖂Ă����
protected:

private:
	void Control(void);								// ����֐�
	void Collision(void);							// �����蔻��֐�
	void Smash(void);								// �X�}�b�V������
	void NormalAttack(void);						// �ʏ�U������
	void Jump(void);								// �W�����v����
	void Lift(void);								// ����������

	void CollisionAttack(void);						// �U������

	static CHitPoint *m_pHitPoint;					// HP���
	static CTransformBar *m_pTransBar;				// �ϐg�o�[���

	void ControlGamepad(CInputGamepad *pGamepad);	// �Q�[���p�b�h����
	void ControlKeyboard(CInputKeyboard *pKeyboard);// �L�[�{�[�h����
	void CatchStone(void);							// �X�g�[���̎擾����
	void SetnPlayer(int nPlayerNum);				// �v���C���[�ԍ��ݒ菈��

	void AnotherPlayerAttack0(CPlayer *pAnother);	// �ʂ̃v���C���[���U��0���Ă��鎞
	void AnotherPlayerAttack1(CPlayer *pAnother);	// �ʂ̃v���C���[���U��1���Ă��鎞
	void AnotherPlayerAttack2(CPlayer *pAnother);	// �ʂ̃v���C���[���U��2���Ă��鎞
	void AnotherPlayerAttack3(CPlayer *pAnother);	// �ʂ̃v���C���[���U��3���Ă��鎞
	void AnotherPlayerSmash(CPlayer *pAnother);		// �ʂ̃v���C���[���X�}�b�V���U�����Ă��鎞

	void TakeDamage(CPlayer * pAnother);							// �_���[�W���󂯂�
	void TakeAttack3Damage(CPlayer * pAnother);					// �U��3�̃_���[�W���󂯂�
	void TakeSmashDamage(CPlayer * pAnother);						// �U��3�̃_���[�W���󂯂�


	bool BlowAway(CPlayer *pAnother, const float MoveVecY, const float fBlowAwayForce);		// �������

	int m_nPlayer;			// �v���C���[�ԍ�
	int m_nBoxColliderID;	// �{�b�N�X�R���C�_�[ID

#ifdef _DEBUG
	void ShowDebugInfo(void);									// ImGui�̍X�V
#endif
};
#endif