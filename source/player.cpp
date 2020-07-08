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

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
#define VALUE_MOVE_PLAYER	(1.0f)	// �v���C���[�̈ړ��l
#define VALUE_JUMP			(5.0f)	// �W�����v�͂̒l

#define POS_1P	(D3DXVECTOR3(0.0f, 0.0f, 100.0f))	// 1P�v���C���[�̏������W
#define POS_2P	(D3DXVECTOR3(0.0f, 0.0f, -100.0f))	// 2P�v���C���[�̏������W

//==================================================================================================================
// �}�N����`
//==================================================================================================================

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
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CPlayer::Update(void)
{
	// ����
	Control();

	// �X�V
	CCharacter::Update();

	// �����蔻��
	Collision();

	// �X�g�[���̎擾����
	CatchStone();
	
#ifdef _DEBUG
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
	// ������
	pPlayer->Init();
	// �v���C���[�ԍ��̕ۑ�
	pPlayer->m_nPlayer = nPlayer;

	// �v���C���[�ԍ��ɂ���č��W���Đݒ�
	if (nPlayer == 0)
		pPlayer->SetPos(POS_1P);
	if (nPlayer == 1)
		pPlayer->SetPos(POS_2P);

	// �l��Ԃ�
	return pPlayer;
}

//==================================================================================================================
// �v���C���[�̑���
//==================================================================================================================
void CPlayer::Control(void)
{
	CInputGamepad *pGamepad = CManager::GetInputGamepad(m_nPlayer);	// �Q�[���p�b�h�擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();		// �L�[�{�[�h�̎擾

	if (m_nPlayer == 0)
		CDebugProc::Print("�v���C���[1���� : WASD, SPACE�L�[\n");
	if (m_nPlayer == 1)
		CDebugProc::Print("�v���C���[2���� : ���, 0(�e���L�[)\n");

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
	// �����蔻��ʒu�̍X�V
	C3DBoxCollider::ChangePosition(this->m_nBoxColliderID, this->m_pos, MYLIB_3DVECTOR_ZERO);
	// �����蔻��
	C3DBoxCollider::CollisionBox(this->m_nBoxColliderID, this->m_pos, m_move);


	// �ǂ̎擾
	CWall *pWall = CGame::GetWall();

	// �o�͂�����_
	D3DXVECTOR3 out_intersect = ZeroVector3;
	// �X�}�b�V���ɂ�钵�˕Ԃ���󂯂Ă��邩
	bool bReflection = false;

	// �ǂƂ̓����蔻��
	pWall->Collision(&m_pos, &m_posOld, &out_intersect, bReflection);
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

	CCamera *pCamera = CManager::GetRenderer()->GetGame()->GetCamera();	// �J�����擾

	D3DXVECTOR3 move		= GetMove();			// �ړ��l�擾
	D3DXVECTOR3 rotDest		= GetRotDest();			// �ړI�̌������i�[����ϐ�
	float		CameraRotY	= pCamera->GetRotY();	// �J������Y����]�̎擾

	if (!m_bAttack &&
		(m_nPlayer == PLAYER_ONE && (pKeyboard->GetKeyboardTrigger(ONE_ATTACK)) ||
		m_nPlayer == PLAYER_TWO && (pKeyboard->GetKeyboardTrigger(TWO_ATTACK))))
	{
		m_bAttack = true;
	}

	if (!m_bJump && 
		(m_nPlayer == PLAYER_ONE && (pKeyboard->GetKeyboardTrigger(ONE_JUMP)) || 
		m_nPlayer == PLAYER_TWO && (pKeyboard->GetKeyboardTrigger(TWO_JUMP))))
	{
		move.y += VALUE_JUMP;
		m_bJump = true;
		m_bWalk = false;
	}

	if (m_bTrans && m_nPlayer == PLAYER_ONE && pKeyboard->GetKeyboardTrigger(ONE_ATTACK))
	{
		m_bWalk = false;

		if (m_pModelCharacter->GetMotion() == CMotion::PLAYER_SMASH_CHARGE)
		{
			m_pModelCharacter->ResetMotion();
			m_pModelCharacter->SetMotion(CMotion::PLAYER_SMASH);
		}
		else if (m_pModelCharacter->GetMotion() != CMotion::PLAYER_SMASH_CHARGE)
		{
			m_pModelCharacter->ResetMotion();
			m_pModelCharacter->SetMotion(CMotion::PLAYER_SMASH_CHARGE);
		}
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
		// �����Ă���
		m_bWalk = true;

	/*if (pKeyboard->GetKeyboardTrigger(DIK_M))
	{
		m_bAttack = true;
	}*/

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
		// �X�g�[���̎擾
		((CStone *)pScene)->Catch();

		// �X�g�[���̎擾�������Z
		m_nNumStone++;
		// �o���X�g�[���������Z
		CGame::RemoveNumStone();
		// 3�擾���Ă���
		if (m_nNumStone >= 3)
			// �ϐg
			this->m_bTrans = true;
	}
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
		// ���̕\��
		CKananLibrary::ShowOffsetInfo(GetPos(), GetRot(), GetMove());
		ImGui::Text("nLife       : %f", m_nLife);
		ImGui::Text("bJump       : %d", m_bJump);
		ImGui::Text("GetNumStone : %d", m_nNumStone);
		if (m_bTrans)
			ImGui::Text("TransTime   : %d", TIME_TRANS - m_nCntTrans);
	}
}
#endif