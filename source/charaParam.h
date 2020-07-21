// ===================================================================
//
// �L�����N�^�[�p�����[�^�[���� [ charaParame.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _CHARACTERPARAMETER_H_
#define _CHARACTERPARAMETER_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"
#include "kananlibrary.h"
#include "player.h"

// ===================================================================
// �}�N����`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================

class CCharaParam
{
public:
	typedef enum
	{	// �p�����[�^�[�̃^�C�v
		PARAM_1YASU = 0,	// 1���X
		PARAM_2YASU,		// 2���X
		PARAM_MAX			// �ő吔
	} PARAM_TYPE;

	typedef struct INT_START_END
	{	// int�^�̊J�n�`�I���t���[���̍\����
		int start;	// �J�n
		int end;	// �I��

		// �R���X�g���N�^
		INT_START_END() {};
		INT_START_END(int nStart, int nEnd)
		{
			start = nStart;
			end = nEnd;
		}
	} INT_START_END;

	typedef struct
	{	// �U���̃p�����[�^�[
		float					fAttackPower;	// �U����
		INT_START_END			CancelFrame;	// �L�����Z���t���[��
		CPlayer::BLOWAWAY_TYPE	blowType;		// ������т̎��
	} PARAM_ATTACK;

	typedef struct
	{	// �ړ��̃p�����[�^�[
		float fRunSpeed;	// �ړ���
		float fJumpPower;	// �W�����v��
	} PARAM_MOVE;


	CCharaParam();			// �R���X�g���N�^
	~CCharaParam();			// �f�X�g���N�^

	static HRESULT         Load(void);		// �L�����N�^�[���Ƃ̃p�����[�^�[���[�h
	static void			   Unload(void);	// �f�[�^�̔j��

protected:
	static int			m_nMaxLife[PARAM_MAX];			// �ő�HP
	static PARAM_MOVE	m_moveParam[PARAM_MAX];		// �ړ��̃p�����[�^�[
	static PARAM_ATTACK	*m_pAttackParam[PARAM_MAX];	// �U���̃p�����[�^�[�̃|�C���^

private:
	static char m_aFileName[PARAM_MAX][64];	// �ϐg�O�L���������̃p�����[�^�[�t�@�C����
};

#endif
