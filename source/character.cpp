//=============================================================================
//
// �L�����N�^�[����  [ character.cpp ]
// Author : Seiya Takahashi
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "Inputkeyboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "modelCharacter.h"
#include "debugProc.h"
#include "motion.h"
#include "game.h"
#include "meshField.h"
#include "modelParts.h"
#include "CylinderCollider.h"

//=============================================================================
// �}�N����`
//=============================================================================	
#define SPEED_ROT			(0.1f)		// ��]�̃X�s�[�h
#define LIFE_DEFAULT		(100.0f)	// ���C�t�̏����l
#define TIME_MAX_DOWN		(60)		// �ő�܂Ń_�E���ł��鎞��

#define INERTIA_SMASH		(0.005f)	// �X�}�b�V��������ю��̊���
#define INERTIA_BLOWAWAY	(0.02f)		// �ʏ퐁����ю��̊���

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
int CCharacter::m_nNumCharacter = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(PRIORITY nPriority) : CScene(nPriority)
{
	// �v�f�̏�����
	m_pModelCharacter	= nullptr;
	m_pos				= ZeroVector3;
	m_posOld			= ZeroVector3;
	m_posBegin			= ZeroVector3;
	m_rot				= ZeroVector3;
	m_rotDest			= ZeroVector3;
	m_rotDif			= ZeroVector3;
	m_move				= ZeroVector3;
	m_nCntTrans			= 0;
	m_nAttackFlow		= 0;
	m_nAttackFrame		= 0;
	m_nCntGap			= 0;
	m_nCntJump			= 0;
	m_bDown				= false;
	m_bAttack			= false;
	m_bJump				= false;
	m_bWalk				= false;
	m_bBlowAway			= false;
	m_bSmashBlowAway	= false;
	m_bDaunted			= false;
	m_nMaxLife			= LIFE_DEFAULT;
	m_nLife				= m_nMaxLife;

	// ���������Z
	m_nNumCharacter++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{
	// nullcheck
	if (m_pModelCharacter)
	{
		// ���f���L�����N�^�[��j��
		delete m_pModelCharacter;
		m_pModelCharacter = nullptr;
	}
}

//=============================================================================
// ������
//=============================================================================
void CCharacter::Init()
{
}

//=============================================================================
// �I��
//=============================================================================
void CCharacter::Uninit()
{
	//���f���̏I������
	m_pModelCharacter->Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CCharacter::Update()
{
	// �ړ�����
	Move();

	// ��]����
	Rot();

	// ���[�V��������
	Motion();

	// �ϐg����
	Trans();

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pModelCharacter->SetCharacterMtx(&m_mtxWorld);

	// ���f���̍X�V
	m_pModelCharacter->Update();

	// ���[���h�}�g���b�N�X�̌v�Z
	CKananLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

#ifdef _DEBUG
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();		// �L�[�{�[�h�̎擾

	// �L�[�{�[�h��[5]���������Ƃ�
	if (pKeyboard->GetKeyboardPress(DIK_5))
	{
		// �̗͂����炷
		m_nLife -= 1;
	}
	// �L�[�{�[�h��[6]���������Ƃ�
	if (pKeyboard->GetKeyboardPress(DIK_6))
	{
		// �̗͂𑝂₷
		m_nLife += 1;
	}
	// �L�[�{�[�h��[6]���������Ƃ�
	if (pKeyboard->GetKeyboardPress(DIK_7))
	{
		// �̗͂𑝂₷
		m_nLife = m_nMaxLife;
	}

#endif // _DEBUG

	if (m_nLife <= 0)
		m_nLife = 0;
	if (m_nLife >= m_nMaxLife)
		m_nLife = m_nMaxLife;
}

//=============================================================================
// �`��
//=============================================================================
void CCharacter::Draw()
{
	// ���f���̕`��
	m_pModelCharacter->Draw();
}

//=============================================================================
// ���f���̐ݒ�
//=============================================================================
void CCharacter::SetModelType(CHARACTER_TYPE type)
{
	// ���f���̐���
	m_pModelCharacter = CModelCharacter::Create(type);

	m_type = type;
	m_typeTrans = (CHARACTER_TYPE)(type + 1);

	// ���[���h�}�g���b�N�X�̐ݒ�
	m_pModelCharacter->SetCharacterMtx(&m_mtxWorld);

	// �V�����_�[�R���C�_�[�̐ݒ�
	SetCylinderCoillider();

}

//=============================================================================
// �V�����_�[�R���C�_�[�̐ݒ�
//=============================================================================
void CCharacter::SetCylinderCoillider(void)
{
	// �p�[�c�̃|�C���^
	CModelParts *pParts = m_pModelCharacter->GetModelParts();

	// �E�O�r�̐ݒ�
	m_pCyliColi[CCharacter::COLLIPARTS_FOREARM_R] =
		CCylinderCoillider::Create(CCylinderCoillider::TYPEID_FOREARM_R, pParts[CModelParts::PARTSNAME_LOWARM_R].GetMtx());
	// �E��r�̐ݒ�
	m_pCyliColi[CCylinderCoillider::TYPEID_UPPERARM_R] =
		CCylinderCoillider::Create(CCylinderCoillider::TYPEID_UPPERARM_R, pParts[CModelParts::PARTSNAME_UPARM_R].GetMtx());
	// ���O�r�̐ݒ�
	m_pCyliColi[CCylinderCoillider::TYPEID_FOREARM_L] =
		CCylinderCoillider::Create(CCylinderCoillider::TYPEID_FOREARM_L, pParts[CModelParts::PARTSNAME_LOWARM_L].GetMtx());
	// ����r�̐ݒ�
	m_pCyliColi[CCylinderCoillider::TYPEID_UPPERARM_L] =
		CCylinderCoillider::Create(CCylinderCoillider::TYPEID_UPPERARM_L, pParts[CModelParts::PARTSNAME_UPARM_L].GetMtx());

}

//=============================================================================
// �Ђ�ݏ���
//=============================================================================
void CCharacter::Daunted(const int nGap)
{
	// �J�E���g��ݒ肵�A���ݏ�ԂɈڍs
	m_pModelCharacter->ResetMotion();
	m_nCntGap = nGap;
	m_bDaunted = true;
	m_pModelCharacter->SetMotion(CMotion::PLAYER_DAUNTED);
}

//=============================================================================
// �ړ��̏���
//=============================================================================
void CCharacter::Move(void)
{
	// �O��̈ʒu��ۑ�
	m_posOld = m_pos;

	D3DXVECTOR3 difMove;	// ���݂̈ړ��l�ƖړI�̈ړ��l�̍�
	
	// ����
	if (m_bSmashBlowAway == true)
	{
		CMylibrary::SlowingMove(&m_move.x, INERTIA_SMASH);
		CMylibrary::SlowingMove(&m_move.y, INERTIA_SMASH);
		CMylibrary::SlowingMove(&m_move.z, INERTIA_SMASH);
	}
	else if (m_bBlowAway == true)
	{
		CMylibrary::SlowingMove(&m_move.x, INERTIA_BLOWAWAY);
		CMylibrary::SlowingMove(&m_move.y, INERTIA_BLOWAWAY);
		CMylibrary::SlowingMove(&m_move.z, INERTIA_BLOWAWAY);
	}
	else
	{
		CKananLibrary::InertiaMoveXZ(&m_move);
	}

	// �d��
	CKananLibrary::Gravity(m_move.y);

	//�ړ��ʉ��Z
	m_pos += m_move;

	// �n�ʂƂ̍������r���A�C��
	if (CKananLibrary::FloatLowerLimit(&m_pos.y, CManager::GetRenderer()->GetGame()->GetMeshField()->GetHeight(m_pos)))
	{
		// �X�}�b�V����e���͔���
		if (m_bSmashBlowAway)
			m_move.y *= -1;
		// �n�ʂɏ���Ă�����A�ړ��ʂ��Ȃ���
		if (m_move.y <= -10.0f)
			m_move.y = -10.0f;
		// �W�����v����
		m_bJump = false;
		// �W�����v�J�E���^��������
		m_nCntJump = 0;
	}
}

//=============================================================================
// ��]�̏���
//=============================================================================
void CCharacter::Rot(void)
{
	// ��]�̍��������߂�
	m_rotDif = m_rotDest - m_rot;

	// ��]�̕��
	CKananLibrary::InterpolationRot(&m_rotDif);

	// ���f���̉�]
	m_rot += m_rotDif * SPEED_ROT;

	// ��]�̕��
	CKananLibrary::InterpolationRot(&m_rot);
}

//=============================================================================
// ���[�V�����̏���
//=============================================================================
void CCharacter::Motion(void)
{
	if (!m_bWalk && !m_bAttack && !m_bJump && !m_bDaunted && !m_bBlowAway && !m_bDown)
		m_pModelCharacter->SetMotion(CMotion::PLAYER_NEUTRAL);	// �j���[�g�������[�V����
	if (m_bWalk && !m_bAttack && !m_bJump && !m_bDaunted && !m_bBlowAway && !m_bDown)
		m_pModelCharacter->SetMotion(CMotion::PLAYER_RUN);	// �ړ����[�V����
	// �W�����v�j���[�g����
	if (m_bJump && !m_bDaunted && !m_bBlowAway && !m_bDown)
	{
		// �U���̏�Ԃ�������
		m_nAttackFlow = 0;
		// �W�����v�J�E���^�����Z
		m_nCntJump++;
		// �ŏ��̓W�����v���[�V����
		if (m_nCntJump <= 15)
			m_pModelCharacter->SetMotion(CMotion::PLAYER_JUMP);
		// �ȍ~�͗������[�V����
		else
			m_pModelCharacter->SetMotion(CMotion::PLAYER_FALL);
	}
	// �_�E����
	if (m_bDown)
	{
		// �_�E���J�E���g���Z
		m_nCntDown++;
		m_pModelCharacter->SetMotion(CMotion::PLAYER_DOWN);
		// �_�E���I��
		if (m_nCntDown >= TIME_MAX_DOWN)
		{
			// �_�E����ԉ���
			m_bDown = false;
			// �J�E���g������
			m_nCntDown = 0;
		}
	}

	// �U����
	if (m_bAttack)
	{
		// �U���t���[�������Z
		m_nAttackFrame--;
		// �U���I����
		if (m_nAttackFrame <= 0)
		{
			// �U������
			m_bAttack = false;
			// �U���̏�Ԃ�������
			m_nAttackFlow = 0;
			// �U���t���[����������
			m_nAttackFrame = 0;
		}
	}

	// ���ݒ�
	if (m_bDaunted)
	{
		// �㌄�t���[�����Z
		m_nCntGap--;
		// �U���̏�Ԃ�������
		m_nAttackFlow = 0;
		// ���ݏI��
		if (m_nCntGap <= 0)
		{
			// ���݉���
			m_bDaunted = false;
			// �㌄�t���[����������
			m_nCntGap = 0;
		}
	}

	// ������ђ�
	if (m_bBlowAway)
	{
		// �n�ʂɒ���
		if (m_move.y <= -3.0f)
		{
			// ������яI��
			m_bBlowAway = false;
			// �_�E���J�n
			m_bDown = true;
		}
	}

	// �X�}�b�V��������ђ�
	if (m_bSmashBlowAway)
	{
		// ������т̈З͂�������
		if (abs(m_move.x) <= 5.0f &&
			abs(m_move.z) <= 5.0f &&
			abs(m_move.y) <= 5.0f)
		{
			// ������яI��
			m_bSmashBlowAway = false;
			// �_�E���J�n
			m_bDown = true;
		}
	}
}

//=============================================================================
// �ϐg�̏���
//=============================================================================
void CCharacter::Trans(void)
{
	if (!m_bTrans)
	{
		// �ϐg���Ԃ�������
		m_nCntTrans = 0;
		return;
	}

	// �ϐg���Ԃ����Z
	m_nCntTrans++;
	if (m_nCntTrans < TIME_TRANS)
	{
		// ���f����ϐg�p�Ƀo�C���h
		m_pModelCharacter->ModelRebind(m_typeTrans);
		return;
	}
	// �X�g�[���̎擾����������
	m_nNumStone = 0;
	// �X�g�[���̏o������������
	CGame::SetNumStone(0);
	// �ϐg���Ԃ�������
	m_nCntTrans = 0;
	// �ϐg������
	m_bTrans = false;
	// ���f���̍ăo�C���h
	m_pModelCharacter->ModelRebind(m_type);
}

//=============================================================================
// 1���X�̃��[�V����
//=============================================================================
void CCharacter::IchiyasuMotion(void)
{
	// �U���t���[�������t���[���𒴂���
	/*if (!m_nAttackFrame >= m_pModelCharacter->GetAllFrame())
	{
		return;
	}*/

	/*if (!m_bAttack)
	{
		if (CManager::GetInputKeyboard()->GetKeyboardTrigger(DIK_M))
		{
			m_pModelCharacter->SetMotion(CMotion::PLAYER_ATTACK_0);
			m_nAttackFlow++;
			m_nAttackFrame = 60;
			m_bAttack = true;
			m_bWalk = false;
		}
	}
	else
	{
		// SPACE�L�[
		if (CManager::GetInputKeyboard()->GetKeyboardTrigger(DIK_M))
		{
			// ���[�V�����؂�ւ�
			switch (m_nAttackFlow)
			{
			case 1:
				if (m_nAttackFrame < 15)
				{
					m_pModelCharacter->SetMotion(CMotion::PLAYER_ATTACK_1);
					m_nAttackFrame = 40;
					m_nAttackFlow++;
				}
				break;
			case 2:
				if (m_nAttackFrame < 10)
				{
					m_pModelCharacter->SetMotion(CMotion::PLAYER_ATTACK_2);
					m_nAttackFrame = 40;
					m_nAttackFlow++;
				}
				break;
			case 3:
				if (m_nAttackFrame < 10)
				{
					m_pModelCharacter->SetMotion(CMotion::PLAYER_ATTACK_3);
					m_nAttackFrame = 150;
					m_nAttackFlow = 0;
				}
				break;
			}
		}
	}*/

	/*if (m_bAttack)
	{
		m_nAttackFrame = 0;
		m_nAttackFlow++;
	}*/
}
