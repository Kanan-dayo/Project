//=============================================================================
//
// ���[�V��������  [ motion.h ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CModelCharacter;

class CMotion
{
public:
	// �L�[
	typedef struct
	{
		D3DXVECTOR3 posDest;		// �ړI�̈ʒu
		D3DXVECTOR3 rotDest;		// �ړI�̉�]
	} KEY;

	// �L�[���
	typedef struct
	{
		KEY *pKey;					// �L�[�̃|�C���^
		int nFrame;					// �t���[����
	} KEY_INFO;

	// ���[�V�����̏��
	typedef struct
	{
		KEY_INFO *pKeyInfo;			// �L�[���̃|�C���^
		int nNumKey;				// �L�[��
		bool bLoop;					// ���[�v���邩�ǂ���
	} MOTION_INFO;

	// ���[�V����
	typedef enum
	{
		MOTION_NONE,
		PLAYER_NEUTRAL = 0,		// �v���C���[ �j���[�g����
		PLAYER_RUN,				// �v���C���[ ����
		//PLAYER_JUMP,			// �v���C���[ �W�����v
		PLAYER_LIFT,			// �v���C���[ ���̎����グ��
		PLAYER_THROW,			// �v���C���[ ���̓���
		PLAYER_ATTACK_0,		// �v���C���[ �U��1
		PLAYER_ATTACK_1,		// �v���C���[ �U��2
		PLAYER_ATTACK_2,		// �v���C���[ �U��3
		PLAYER_ATTACK_3,		// �v���C���[ �U��4
		PLAYER_SMASH_CHARGE,	// �v���C���[ �X�}�b�V���`���[�W
		PLAYER_SMASH,			// �v���C���[ �X�}�b�V��
		//PLAYER_DAMAGE,			// �v���C���[ �_���[�W
		//PLAYER_DOWN,			// �v���C���[ �_�E��
		//PLAYER_WALLDOWN,		// �v���C���[ �ǂ͓\��t��
		MOTION_MAX				// �ő�l
	} MOTION_TYPE;

	CMotion();
	~CMotion();

	static HRESULT Load();						// ���[�V�����̃��[�h
	static void UnLoad();						// ���[�V�����̃A�����[�h

	static D3DXVECTOR3 GetRotDest(MOTION_TYPE motiontype, int nKey, int nIndex)
		{ return m_pMotionInfo[motiontype].pKeyInfo[nKey].pKey[nIndex].rotDest; }	// ���[�V�����̉�]�̃S�[���擾
	static D3DXVECTOR3 GetPosDest(MOTION_TYPE motiontype, int nKey, int nIndex)
		{ return m_pMotionInfo[motiontype].pKeyInfo[nKey].pKey[nIndex].posDest; }	// ���[�V�����̉�]�̃S�[���擾
	static int GetFrame(MOTION_TYPE motiontype, int nKey) 
		{ return m_pMotionInfo[motiontype].pKeyInfo[nKey].nFrame; }					// ���[�V�����̑��t���[�����̎擾
	static int GetNumKey(MOTION_TYPE motiontype) 
		{ return m_pMotionInfo[motiontype].nNumKey; }								// ���[�V�����̑��L�[���̎擾
	static bool GetLoop(MOTION_TYPE motiontype) 
		{ return m_pMotionInfo[motiontype].bLoop; }									// ���[�V���������[�v���邩�ǂ����擾

private:
	static MOTION_INFO *m_pMotionInfo;					// ���[�V�������̃|�C���^
	static HRESULT LoadMotion(MOTION_TYPE motiontype);	// ���[�V�����ǂݍ���	
	static int CheckCharacter(MOTION_TYPE motiontype);	// �ǂ̃L�����N�^�[���m�F

	static char *m_apFileName[CMotion::MOTION_MAX];
};
#endif