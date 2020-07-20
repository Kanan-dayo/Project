// ===================================================================
//
// �L�����N�^�[�p�����[�^�[���� [ characterParameter.h ]
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

class CCharacterParameter
{
public:
	typedef enum
	{	// �p�����[�^�[�̃^�C�v
		PARAMETER_1YASU = 0,	// 1���X
		PARAMETER_2YASU,		// 2���X
		PARAMETER_MAX			// �ő吔
	} PARAMETER_TYPE;

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
	} PARAMETER_ATTACK;

	typedef struct
	{	// �ړ��̃p�����[�^�[
		float fRunSpeed;	// �ړ���
		float fJumpPower;	// �W�����v��
	} PARAMETER_MOVE;


	CCharacterParameter();			// �R���X�g���N�^
	~CCharacterParameter();			// �f�X�g���N�^

	void               Init(void);					// ������
	void               Uninit(void);				// �I��
	HRESULT            Load(PARAMETER_TYPE type);	// �L�����N�^�[���Ƃ̃p�����[�^�[���[�h

protected:
	int m_nMaxLife;		// �ő�HP
	PARAMETER_ATTACK	*m_attackParameter;	// �U���̃p�����[�^�[�̃|�C���^
	PARAMETER_MOVE		m_moveParameter;	// �ړ��̃p�����[�^�[

private:
	static char m_aFileName[PARAMETER_MAX][64];	// �ϐg�O�L���������̃p�����[�^�[�t�@�C����
};

#endif
