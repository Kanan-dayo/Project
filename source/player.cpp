//==================================================================================================================
//
// �v���C���[����[player.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "inputKeyboard.h"
#include "renderer.h"
#include "player.h"
#include "debugProc.h"
#include "camera.h"
#include "meshField.h"
#include "motionModel.h"
#include "time.h"
#include "title.h"
#include <initializer_list>
#include "tutorial.h"
#include "game.h"
#include "inputGamepad.h"
#include "character.h"
#include "scene.h"
#include "modelCharacter.h"
#include "motion.h"
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v
#include "3DBoxCollider.h"
#include "stone.h"
#include "wall.h"
#include "CylinderCollider.h"
#include "motion.h"
#include "Reflection.h"
#include "hitpoint.h"
#include "PolygonCollider.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define VALUE_MOVE_PLAYER	(1.0f)	// �v���C���[�̈ړ��l
#define VALUE_JUMP			(5.0f)	// �W�����v�͂̒l

#define POS_1P	(D3DXVECTOR3(0.0f, 0.0f, 100.0f))	// 1P�v���C���[�̏������W
#define POS_2P	(D3DXVECTOR3(0.0f, 0.0f, -100.0f))	// 2P�v���C���[�̏������W

#define BLOWAWAYFORCE_SMASH		(100.0f)	// ������΂���(�X�}�b�V���U��)
#define BLOWAWAYFORCE_NORMAL	(8.0f)		// ������΂���(�ʏ�U��)

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CHitPoint *CPlayer::m_pHitPoint = NULL;				// HP���

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CPlayer::CPlayer(PRIORITY type = CScene::PRIORITY_PLAYER) : CCharacter(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CPlayer::~CPlayer()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CPlayer::Init(void)
{
	// �v�f�̏�����
	m_bTrans = false;

	// ������
	CCharacter::Init();
	CCharacter::SetModelType(m_type);

	// �����蔻��̐ݒ�
	this->m_nBoxColliderID = C3DBoxCollider::SetColliderInfo(&this->GetPos(), this, C3DBoxCollider::COLLIDER_SUB_NORMAL, C3DBoxCollider::ID_CHARACTER);

	m_pHitPoint = CHitPoint::Create(m_nPlayer);		// �v���C���[�̐�������
	m_pHitPoint->SetnPlayerNum(m_nPlayer);			// �v���C���[�ԍ��ݒ�
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();

	m_pHitPoint = nullptr;	// �ϐ�NULL
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CPlayer::Update(void)
{
	if (m_bBlowAway == false && m_bDaunted == false)
	{
		// ����
		Control();
	}

	// �X�V
	CCharacter::Update();

	// �����蔻��
	Collision();

	// �X�g�[���̎擾����
	CatchStone();

	// �v���C���[�̔ԍ��ݒ�
	SetnPlayer(m_nPlayer);
	 
#ifdef _DEBUG
	CDebugProc::Print("�v���C���[�̈ʒu [%.4f][%.4f][%.4f]\n", m_pos.x, m_pos.y, m_pos.z);

	ShowDebugInfo();

	if (CManager::GetInputKeyboard()->GetKeyboardTrigger(DIK_2))
	{
		m_bTrans = true;
	}
#endif
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}

//==================================================================================================================
// ��������
//==================================================================================================================
CPlayer *CPlayer::Create(int nPlayer, CHARACTER_TYPE type)
{
	// �V�[�����I�Ɋm��
	CPlayer *pPlayer = new CPlayer(CScene::PRIORITY_PLAYER);

	// ���s
	if (!pPlayer)
		return nullptr;

	// �v���C���[�̃L�����^�C�v��ݒ�
	pPlayer->m_type = type;
	// �v���C���[�ԍ��̕ۑ�
	pPlayer->m_nPlayer = nPlayer;
	// ������
	pPlayer->Init();

	// �v���C���[�ԍ��ɂ���č��W���Đݒ�
	if (nPlayer == PLAYER_ONE)
		pPlayer->SetPos(POS_1P);
	if (nPlayer == PLAYER_TWO)
		pPlayer->SetPos(POS_2P);

	// �l��Ԃ�
	return pPlayer;
}

//==================================================================================================================
// �v���C���[�̑���
//==================================================================================================================
void CPlayer::Control(void)
{
	// �Q�[���p�b�h�擾
	CInputGamepad *pGamepad = CManager::GetInputGamepad(m_nPlayer);
	// �L�[�{�[�h�̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�L����
	if (pGamepad->GetbConnect())
		// �Q�[���p�b�h����
		ControlGamepad(pGamepad);
	// �Q�[���p�b�h������
	else
		// �L�[�{�[�h����
		ControlKeyboard(pKeyboard);
}

//==================================================================================================================
// �����蔻�菈��
//==================================================================================================================
void CPlayer::Collision(void)
{
	// �U������
	CollisionAttack();

	// �����蔻��ʒu�̍X�V
	C3DBoxCollider::ChangePosition(this->m_nBoxColliderID, this->m_pos, MYLIB_3DVECTOR_ZERO);
	// �����蔻��
	C3DBoxCollider::CollisionBox(this->m_nBoxColliderID, this->m_pos, m_move);

	// �ǂ̎擾
	CWall *pWall = CGame::GetWall();
	// �o�͂�����_
	D3DXVECTOR3 out_intersect = ZeroVector3;
	// �o�͂����@��
	D3DXVECTOR3 out_nor = ZeroVector3;
	// �ǂƂ̓����蔻��
	if (pWall->Collision(&m_pos, &m_posOld, &out_intersect,&out_nor, m_bSmashBlowAway) == true)
	{
		// ���˃t���O�������Ă���Ƃ�����
		// �o�͂��ꂽ�@�����[������Ȃ�������
		// �o�͂��ꂽ��_���[������Ȃ���
		if (m_bSmashBlowAway == true &&
			out_nor != ZeroVector3 &&
			out_intersect != ZeroVector3)
		{
			// �_���[�W
			this->Damage(2);
			// ����������
			this->m_rotDest.y =  atan2f(out_nor.x, out_nor.z);
			// ��]����
			CKananLibrary::InterpolationFloat(m_rotDest.y);
			// ��u�Ō�����ς���
			this->m_rot.y = this->m_rotDest.y;
			CReflection::GetPlaneReflectingAfterPosAndVec(&this->m_pos,&this->m_move, &out_intersect, &this->m_move, &out_nor);
		}
	}

	for (int nCntPolyColli = 0; nCntPolyColli < CPolygonCollider::POLYCOLLI_MAX; nCntPolyColli++)
	{
		// �|���S���R���C�_�[�̎擾
		CPolygonCollider*pPolyColli = CGame::GetpolyColly(nCntPolyColli);
		// �|���S���R���C�_�[�̏Փ˔���
		if (pPolyColli[0].Collision(&m_pos, &m_posOld, &m_move, &out_intersect, &out_nor, m_bSmashBlowAway) == true)
		{
			if (m_bSmashBlowAway == false)
			{
#ifdef _DEBUG
				CDebugProc::Print("����Ă���\n");
#endif
				// �n�ʂɏ���Ă�����A�ړ��ʂ��Ȃ���
				if (m_move.y <= -5.0f)
					m_move.y = -5.0f;
				// �W�����v����
				m_bJump = false;
				// �W�����v�J�E���^��������
				m_nCntJump = 0;
			}
			else
			{
				CReflection::GetPlaneReflectingAfterPosAndVec(&this->m_pos, &this->m_move, &out_intersect, &this->m_move, &out_nor);
			}
		}
	}

	// ��������
	if (m_pos.y > 200.0f)
	{
		m_pos.y = 200.0f;
		m_move.y *= -1;
	}
}

//==================================================================================================================
// �U���̏���
//==================================================================================================================
void CPlayer::Attack(void)
{
	if (!m_bAttack)
		return;
}

//==================================================================================================================
// �U������
//==================================================================================================================
void CPlayer::CollisionAttack(void)
{
	// �Ⴄ�v���C���[�̎擾
	CPlayer *pAnother = GetAnotherPlayer();

	// �Ⴄ�v���C���[���U���𓖂Ă��t���O�������ĂȂ���
	if (pAnother->m_bAttakHit == false)
	{
		// �ʂ̃v���C���[�̃��[�V�������r
		switch (pAnother->m_pModelCharacter->GetMotion())
		{
		case CMotion::PLAYER_ATTACK_0:
			// �ʂ̃v���C���[���U��0�����Ă��鎞
			this->AnotherPlayerAttack0(pAnother);
			break;
		case CMotion::PLAYER_ATTACK_1:
			// �ʂ̃v���C���[���U��1�����Ă��鎞
			this->AnotherPlayerAttack1(pAnother);
			break;
		case CMotion::PLAYER_ATTACK_2:
			// �ʂ̃v���C���[���U��2�����Ă��鎞
			this->AnotherPlayerAttack2(pAnother);
			break;
		case CMotion::PLAYER_ATTACK_3:
			// �ʂ̃v���C���[���U��3�����Ă��鎞
			this->AnotherPlayerAttack3(pAnother);
			break;
		case CMotion::PLAYER_SMASH:
			// �ʂ̃v���C���[���X�}�b�V���U�����Ă���Ƃ�
			this->AnotherPlayerSmash(pAnother);
			break;
		}
	}
}

//==================================================================================================================
// �Ⴄ�v���C���[�̎擾
//==================================================================================================================
CPlayer * CPlayer::GetAnotherPlayer(void)
{
	return (this->m_nPlayer == PLAYER_ONE) ? CGame::GetPlayer(PLAYER_TWO) : CGame::GetPlayer(PLAYER_ONE);
}

//==================================================================================================================
// �Q�[���p�b�h�̑���
//==================================================================================================================
void CPlayer::ControlGamepad(CInputGamepad * pGamepad)
{
	float fValueX, fValueY;	// �Q�[���p�b�h�̃X�e�B�b�N���̎擾�p

	// ���X�e�B�b�N�擾
	pGamepad->GetStickLeft(&fValueX, &fValueY);

	// �������͂���Ă��Ȃ���΁A�������Ȃ�
	if (FAILED(CKananLibrary::GetMoveByGamepad(pGamepad)) && 
		fValueX == 0 && fValueY == 0)
	{
		m_bWalk = false;
		return;
	}

	// �����Ă���
	SetbWalk(true);

	CCamera *pCamera = CManager::GetRenderer()->GetGame()->GetCamera();	// �J�����擾

	D3DXVECTOR3 move = GetMove();					// �ړ��l�擾
	D3DXVECTOR3 rotDest = GetRotDest();				// �ړI�̌������i�[����ϐ�
	D3DXVECTOR3 *vecCamera = pCamera->GetVec();		// �J�����̌����Ă�������̎擾
	float		CameraRotY = pCamera->GetRotY();	// �J������Y����]�̎擾
	float		fSpeed = 0.0f;						// �v���C���[�̑��x
	float		fAngle;								// �X�e�B�b�N�p�x�̌v�Z�p�ϐ�

	// �p�x�̌v�Z���ĕ␳
	fAngle = atan2f(fValueX, fValueY);
	CKananLibrary::InterpolationFloat(fAngle);

	// �X�e�B�b�N�̓|���ŃX�s�[�h������
	if (abs(fValueX) > abs(fValueY))
		fSpeed = (abs(fValueX));		// ���̓|��
	else
		fSpeed = (abs(fValueY));		// �c�̓|��

	// �X�e�B�b�N�̊p�x�ɂ���ăv���C���[�ړ�
	move.x += sinf(fAngle + CameraRotY) * fSpeed;
	move.z += cosf(fAngle + CameraRotY) * fSpeed;

	// �ړI�̌���������
	if (fValueX != 0 || fValueY != 0)
	{
		rotDest.y = D3DX_PI + fAngle + CameraRotY;
		m_bWalk = true;
	}

	// �W�����v����
	if (!m_bJump &&
		pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_A))
	{
		move.y += VALUE_JUMP;
		m_bJump = true;
	}

	if (m_bJump)
		m_bWalk = false;

	// ��]�̕␳
	CKananLibrary::InterpolationRot(&rotDest);

	// �ړ��l�̐ݒ�
	SetMove(move);

	// �ړI�̉�]�̐ݒ�
	SetRotDest(rotDest);
}

//==================================================================================================================
// �L�[�{�[�h�̑���
//==================================================================================================================
void CPlayer::ControlKeyboard(CInputKeyboard * pKeyboard)
{
	// ���͂���Ă��Ȃ���Ώ������I����
	if (FAILED(CKananLibrary::GetMoveByKeyboard(pKeyboard, m_nPlayer)))
	{
		m_bWalk = false;
		return;
	}

	// �ϐ��錾
	CCamera *pCamera = CManager::GetRenderer()->GetGame()->GetCamera();	// �J�����擾
	D3DXVECTOR3 move = GetMove();										// �ړ��l�擾
	D3DXVECTOR3 rotDest = GetRotDest();										// �ړI�̌������i�[����ϐ�
	float		CameraRotY = pCamera->GetRotY();								// �J������Y����]�̎擾

	if (m_bTrans &&
		((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardTrigger(ONE_SMASH)) ||
		(m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardTrigger(TWO_SMASH))))
	{
		// ������ݒ�
		m_bWalk = false;
		m_bAttack = true;

		// �X�}�b�V��
		if (m_pModelCharacter->GetMotion() == CMotion::PLAYER_SMASH_CHARGE)
			m_pModelCharacter->SetMotion(CMotion::PLAYER_SMASH);
		// �X�}�b�V���`���[�W
		else if (m_pModelCharacter->GetMotion() != CMotion::PLAYER_SMASH_CHARGE &&
			m_pModelCharacter->GetMotion() != CMotion::PLAYER_SMASH)
			m_pModelCharacter->SetMotion(CMotion::PLAYER_SMASH_CHARGE);

		// �U�������������t���O���I�t�ɂ���
		m_bAttakHit = false;
		// �U���t���[����ݒ�
		m_nAttackFrame = m_pModelCharacter->GetAllFrame();
	}

	// �X�}�b�V���n���[�V�������͈ȍ~�̏��������Ȃ�
	if (m_pModelCharacter->GetMotion() == CMotion::PLAYER_SMASH_CHARGE ||
		m_pModelCharacter->GetMotion() == CMotion::PLAYER_SMASH)
	{
		// �������I����
		return;
	}

	if (((m_nPlayer == PLAYER_ONE && (pKeyboard->GetKeyboardTrigger(ONE_ATTACK)) ||
		m_nPlayer == PLAYER_TWO && (pKeyboard->GetKeyboardTrigger(TWO_ATTACK))) &&
		m_pModelCharacter->GetMotion() != CMotion::PLAYER_SMASH_CHARGE &&
		m_pModelCharacter->GetMotion() != CMotion::PLAYER_SMASH))
	{
		if (!m_bAttack && !m_bJump)
		{
			// ������ݒ�
			m_bWalk = false;
			m_bAttack = true;
		}
		else if (m_bAttack)
		{
			switch (m_nAttackFlow)
			{
			case 0:
				return;
				break;
			case 1:
				if (m_pModelCharacter->GetAllFrame() - m_nAttackFrame < 15)
					return;
				break;
			case 2:
				if (m_pModelCharacter->GetAllFrame() - m_nAttackFrame < 10)
					return;
				break;
			case 3:
				if (m_pModelCharacter->GetAllFrame() - m_nAttackFrame < 25)
					return;
				break;
			}
		}

		// ���[�V�����̐؂�ւ�
		m_pModelCharacter->SetMotion((CMotion::MOTION_TYPE)(CMotion::PLAYER_ATTACK_0 + m_nAttackFlow));
		// �U�������������t���O���I�t�ɂ���
		m_bAttakHit = false;
		// �U���t���[����ݒ�
		m_nAttackFrame = m_pModelCharacter->GetAllFrame();
		// �U���̏��Ԃ�ݒ�
		m_nAttackFlow++;
		if (m_nAttackFlow >= 4)
			m_nAttackFlow = 0;

		// �������I����
		return;
	}

	if (!m_bJump && !m_bAttack &&
		(m_nPlayer == PLAYER_ONE && (pKeyboard->GetKeyboardTrigger(ONE_JUMP)) ||
			m_nPlayer == PLAYER_TWO && (pKeyboard->GetKeyboardTrigger(TWO_JUMP))))
	{
		// ������ݒ�
		m_bJump = true;
		m_bWalk = false;

		// �ړ��l��ݒ�
		move.y = VALUE_JUMP;
	}

	if (m_bAttack)
	{
		m_bWalk = false;
		return;
	}

	if (m_bDown)
	{
		m_bWalk = false;
		return;
	}

	// A�L�[������
	if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_LEFT)) ||
		m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_LEFT))
	{
		// W�L�[������
		if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_UP)) ||
			m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_UP))
		{
			// ����ړ�
			move.x += sinf(-D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(-D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.y = D3DX_PI * 0.75f + CameraRotY;
		}
		// S�L�[������
		else if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_DOWN)) ||
			m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_DOWN))
		{
			// �����ړ�
			move.x += sinf(-D3DX_PI * 0.25f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(-D3DX_PI * 0.25f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.y = D3DX_PI * 0.25f + CameraRotY;
		}
		// A�L�[�̂�
		else
		{
			// ���ړ�
			move.x += sinf(-D3DX_PI * 0.5f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(-D3DX_PI * 0.5f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.x = 0.0f;
			rotDest.y = D3DX_PI * 0.5f + CameraRotY;
		}
	}
	// D�L�[������
	else if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_RIGHT)) ||
		m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_RIGHT))
	{
		// W�L�[������
		if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_UP)) ||
			m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_UP))
		{
			// �E��ړ�
			move.x += sinf(D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.y = -D3DX_PI * 0.75f + CameraRotY;
		}
		// S�L�[������
		else if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_DOWN)) ||
			m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_DOWN))
		{
			// �E���ړ�
			move.x += sinf(D3DX_PI * 0.25f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(D3DX_PI * 0.25f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.y = -D3DX_PI * 0.25f + CameraRotY;
		}
		// D�L�[�̂�
		else
		{
			// �E�ړ�
			move.x += sinf(D3DX_PI * 0.5f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(D3DX_PI * 0.5f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.y = -D3DX_PI * 0.5f + CameraRotY;
		}
	}
	// W�L�[������
	else if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_UP)) ||
		m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_UP))
	{
		// ��ړ�
		move.x += sinf(D3DX_PI * 1.0f - CameraRotY) * VALUE_MOVE_PLAYER;
		move.z -= cosf(D3DX_PI * 1.0f - CameraRotY) * VALUE_MOVE_PLAYER;
		// �ړI�̌���������
		rotDest.y = -D3DX_PI * 1.0f + CameraRotY;
	}
	// S�L�[������
	else if ((m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardPress(ONE_DOWN)) ||
		m_nPlayer == PLAYER_TWO && pKeyboard->GetKeyboardPress(TWO_DOWN))
	{
		// ���ړ�
		move.x += sinf(D3DX_PI * 0.0f - CameraRotY) * VALUE_MOVE_PLAYER;
		move.z -= cosf(D3DX_PI * 0.0f - CameraRotY) * VALUE_MOVE_PLAYER;
		// �ړI�̌���������
		rotDest.y = CameraRotY;
	}

	if (!m_bJump)
	{
		if (!m_bWalk)
			// �����n�߂̓��[�V�������Z�b�g
			m_pModelCharacter->ResetMotion();
		// �����Ă���
		m_bWalk = true;
	}

	// ��]�̕␳
	CKananLibrary::InterpolationRot(&rotDest);

	// �ړ��l�̐ݒ�
	SetMove(move);

	// �ړI�̉�]�̐ݒ�
	SetRotDest(rotDest);
}

//==================================================================================================================
// �X�g�[���̎擾����
//==================================================================================================================
void CPlayer::CatchStone(void)
{
	// �ϐ��錾
	int nHitID = MYLIB_INT_NOELEM;	// ��������ID
	// ���������R���C�_��ID���擾
	if (C3DBoxCollider::Collisionoverlap(this->m_nBoxColliderID, &nHitID) == false)
	{
		return;
	}

	// scene�擾
	CScene *pScene = C3DBoxCollider::GetScene(nHitID);	// �V�[���|�C���^
	// �擾�Ɏ��s�����Ƃ�
	if (pScene == NULL)
	{
		return;
	}
	// �v���C�I���e�B���X�g�[���̂Ƃ�
	if (pScene->GetPriority() == CScene::PRIORITY_STONE)
	{
		// �o���X�g�[���������Z
		CGame::RemoveNumStone(((CStone *)pScene)->GetIndexPos());
		// �X�g�[���̎擾
		((CStone *)pScene)->Catch();

		// �X�g�[���̎擾�������Z
		m_nNumStone++;
		// 3�擾���Ă���
		if (m_nNumStone >= 3)
			// �ϐg
			this->m_bTrans = true;
	}
}

//==================================================================================================================
// �ʂ̃v���C���[���U��0���Ă��鎞
//==================================================================================================================
void CPlayer::AnotherPlayerAttack0(CPlayer * pAnother)
{
	if (pAnother->m_pCyliColi[CCharacter::COLLIPARTS_FOREARM_L]->Collision(this->m_nBoxColliderID) == true ||
		pAnother->m_pCyliColi[CCharacter::COLLIPARTS_UPPERARM_L]->Collision(this->m_nBoxColliderID) == true)
	{
		// �_���[�W
		this->Damage(2);
		if (!m_bTrans)
			// ����
			this->Daunted(20);
		// ���Ă��t���O�𗧂Ă�
		pAnother->m_bAttakHit = true;
	}
}

//==================================================================================================================
// �ʂ̃v���C���[���U��1���Ă��鎞
//==================================================================================================================
void CPlayer::AnotherPlayerAttack1(CPlayer * pAnother)
{
	if (pAnother->m_pCyliColi[CCharacter::COLLIPARTS_FOREARM_R]->Collision(this->m_nBoxColliderID) == true ||
		pAnother->m_pCyliColi[CCharacter::COLLIPARTS_UPPERARM_R]->Collision(this->m_nBoxColliderID) == true)
	{
		// �_���[�W
		this->Damage(2);
		if (!m_bTrans)
			// ����
			this->Daunted(20);
		// ���Ă��t���O�𗧂Ă�
		pAnother->m_bAttakHit = true;
	}
}

//==================================================================================================================
// �ʂ̃v���C���[���U��2���Ă��鎞
//==================================================================================================================
void CPlayer::AnotherPlayerAttack2(CPlayer * pAnother)
{
	if (pAnother->m_pCyliColi[CCharacter::COLLIPARTS_FOREARM_L]->Collision(this->m_nBoxColliderID) == true ||
		pAnother->m_pCyliColi[CCharacter::COLLIPARTS_UPPERARM_L]->Collision(this->m_nBoxColliderID) == true)
	{
		// �_���[�W
		this->Damage(2);
		if (!m_bTrans)
			// ����
			this->Daunted(20);
		// ���Ă��t���O�𗧂Ă�
		pAnother->m_bAttakHit = true;
	}
}

//==================================================================================================================
// �ʂ̃v���C���[���U��3���Ă��鎞
//==================================================================================================================
void CPlayer::AnotherPlayerAttack3(CPlayer * pAnother)
{
	if (pAnother->m_pCyliColi[CCharacter::COLLIPARTS_FOREARM_R]->Collision(this->m_nBoxColliderID) == true ||
		pAnother->m_pCyliColi[CCharacter::COLLIPARTS_UPPERARM_R]->Collision(this->m_nBoxColliderID) == true)
	{
		// �_���[�W
		this->Damage(2);
		// �ϐg���ȊO�͐������
		if (!m_bTrans)
		{
			// �������
			BlowAway(pAnother, 0.5f, BLOWAWAYFORCE_NORMAL);
			// ������т�L��
			m_bBlowAway = true;
			if (m_nNumStone > 0)
			{
				// �����X�g�[��������炷n
				m_nNumStone--;
				// ���炵���X�g�[���𑦐���
				CGame::AppearStone();
			}
		}
		// ���Ă��t���O�𗧂Ă�
		pAnother->m_bAttakHit = true;
	}
}

//==================================================================================================================
// �ʂ̃v���C���[���X�}�b�V���U�����Ă��鎞
//==================================================================================================================
void CPlayer::AnotherPlayerSmash(CPlayer * pAnother)
{
	// �V�����_�[�R���C�_�[�̏Փ˔���
	if (pAnother->m_pCyliColi[CCharacter::COLLIPARTS_FOREARM_R]->Collision(this->m_nBoxColliderID) == true ||
		pAnother->m_pCyliColi[CCharacter::COLLIPARTS_UPPERARM_R]->Collision(this->m_nBoxColliderID) == true)
	{
		// �_���[�W
		this->Damage(2);
		// �ϐg���ȊO�͐������
		BlowAway(pAnother, 0.5f, BLOWAWAYFORCE_SMASH);
		// �X�}�b�V���ɂ�鐁����т����s
		m_bSmashBlowAway = true;
		// ���Ă��t���O�𗧂Ă�
		pAnother->m_bAttakHit = true;
	}
}
//==================================================================================================================
// �v���C���[�ԍ��ݒ菈��
//==================================================================================================================
void CPlayer::SetnPlayer(int nPlayerNum)
{
	m_nPlayer = nPlayerNum;
}

//==================================================================================================================
// �������
//==================================================================================================================
inline bool CPlayer::BlowAway(CPlayer *pAnother, const float MoveVecY, const float fBlowAwayForce)
{
	// NULL���������������Ȃ�
	if (pAnother == NULL)
	{
		return false;
	}
	// �ϐ��錾
	D3DXVECTOR3 MoveVec;	// �ړ��x�N�g��

	MoveVec.x = sinf(pAnother->m_rot.y + D3DX_PI);
	MoveVec.y = MoveVecY;
	MoveVec.z = cosf(pAnother->m_rot.y + D3DX_PI);

	// �Ԃ���у��[�V����
	m_pModelCharacter->ResetMotion();
	m_pModelCharacter->SetMotion(CMotion::PLAYER_BLOWAWAY);
	// ����������
	m_rotDest.y = pAnother->m_rot.y + D3DX_PI;
	// ��]�̕��
	CKananLibrary::InterpolationFloat(m_rotDest.y);
	// ��u�Ō�����ς���
	m_rot.y = m_rotDest.y;

	// �ړ��l�ɉ��Z
	this->m_move.x = MoveVec.x * fBlowAwayForce;
	this->m_move.z = MoveVec.z * fBlowAwayForce;
	this->m_move.y = MoveVec.y * fBlowAwayForce;

	return true;
}

#ifdef _DEBUG
//==================================================================================================================
// ImGui�̍X�V
//==================================================================================================================
void CPlayer::ShowDebugInfo()
{
	char cHead[8];
	sprintf(cHead, "Player%d", m_nPlayer);			// �v���C���[�ԍ��𕶎���ɒǉ�

	if (ImGui::CollapsingHeader(cHead))
	{
		int nAllFrame = m_pModelCharacter->GetAllFrame();
		// ���̕\��
		CKananLibrary::ShowOffsetInfo(GetPos(), GetRot(), GetMove());
		ImGui::Text("nLife       : %f", m_nLife);
		ImGui::Text("bJump       : %d", m_bJump);
		ImGui::Text("bWalk       : %d", m_bWalk);
		ImGui::Text("bDown       : %d", m_bDown);
		ImGui::Text("bAttack     : %d", m_bAttack);
		if (m_bAttack)
		{
			ImGui::Text("AttackFlow  : %d", m_nAttackFlow);
			ImGui::Text("AttackFrame : %d / %d", nAllFrame - m_nAttackFrame, nAllFrame);
		}
		ImGui::Text("GetNumStone : %d", m_nNumStone);
		if (m_bTrans)
			ImGui::Text("TransTime   : %d", TIME_TRANS - m_nCntTrans);
	}
}
#endif