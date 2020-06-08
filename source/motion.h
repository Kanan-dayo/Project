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
		PLAYER_NEUTRAL,			// �v���C���[�@�j���[�g����
		PLAYER_SWIM_BEGIN,		// �v���C���[�@�j���n��
		PLAYER_SWIM,			// �v���C���[�@�j��
		FISH000_NEUTRAL,		// ��000�@�j���[�g����
		FISH001_NEUTRAL,		// ��001�@�j���[�g����
		MOTION_MAX				// �ő�l
	} MOTION_TYPE;

	CMotion();
	~CMotion();

	static HRESULT Load();						// ���[�V�����̃��[�h
	static void UnLoad();						// ���[�V�����̃A�����[�h

	static D3DXVECTOR3 GetRotDest(MOTION_TYPE motiontype, int nKey, int nIndex);			// ���[�V�����̉�]�̃S�[���擾
	static int GetFrame(MOTION_TYPE motiontype, int nKey);
	static int GetNumKey(MOTION_TYPE motiontype);
	static bool GetLoop(MOTION_TYPE motiontype);

private:
	static MOTION_INFO *m_pMotionInfo;					// ���[�V�������̃|�C���^
	static HRESULT LoadMotion(MOTION_TYPE motiontype);	// ���[�V�����ǂݍ���	
	static int CheckCharacter(MOTION_TYPE motiontype);	// �ǂ̃L�����N�^�[���m�F

	static char *m_apFileName[CMotion::MOTION_MAX];
};
#endif