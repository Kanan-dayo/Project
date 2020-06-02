//==================================================================================================================
//
// �L�����N�^�[����[character.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "inputKeyboard.h"
#include "renderer.h"
#include "character.h"
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
#include "player.h"

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CCamera *CCharacter::m_pCamera = NULL;									// �J�������
CCharacter *CCharacter::m_pCharacter[MAX_CHARA][CHARACTER_MAX] = {};	// �L�����N�^�[���
CPlayer *CCharacter::m_pPenguin = NULL;									// �y���M�����
int CCharacter::m_nNumAll = 0;											// �v���C���[�̐l��

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define PLAYER_MOVE 0.25f			// �v���C���[�̈ړ���
#define JUMP_MOVE 11.0f				// �W�����v����Ƃ��̈ړ���
#define MAX_JAMP_SPEED 0.05f		// �ő�W�����v�X�s�[�h
#define MAX_GRAVITY -6.0f			// �d�͂̍ő�l
#define GRAVITY -0.4f				// �d��
#define ROT_LIMIT 1.0f				// ��]����
#define ROT_SPEED 0.4f				// ��]���x
#define ROT_AMOUNT 0.1f				// ��]�̍������炵�Ă�����
#define REDUCE_SPEED 0.06f			// �����X�s�[�h

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CCharacter::CCharacter(PRIORITY type = CScene::PRIORITY_PLAYER) : CScene(type)
{
	// �v���C���[�̐l�����Z
	m_nNumAll++;

	// �z��i�[�̂���0�Ԗڂ���i�[�����悤�ɂ���
	m_nNumAll -= 1;
}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CCharacter::~CCharacter()
{
	// �v���C���[�̐l��������
	m_nNumAll = 0;
}

//==================================================================================================================
// ����������
//==================================================================================================================
void CCharacter::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, WhileY, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);				// ��]
	m_difference = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);		// ��]�̖ڕW�n�_
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ړ���
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �傫��
	m_bJump = false;										// �W�����v�������ǂ���
	m_bWalk = false;										// �����Ă��邩�ǂ���
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CCharacter::Uninit(void)
{

}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CCharacter::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �R���g���[���[�擾
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	//m_pos = GetPos();					// �ʒu�擾
	//m_rot = GetRot();					// ��]�擾
	//m_size = GetSize();					// �傫���擾
	m_posOld = m_pos;					// ���̈ʒu��O��̈ʒu�ɂ���

	// �W�����v�X�s�[�h���K��l�𒴂�����
	if (m_move.y > MAX_JAMP_SPEED)
	{
		// �W�����v�X�s�[�h���K��l�ɂ���
		m_move.y += MAX_JAMP_SPEED;
	}

	// �W�����v���Ă��Ȃ��Ƃ�
	if (m_bJump == false)
	{
		// �L�[�{�[�h��[SPACE] ���� �R���g���[���[��B�������ꂽ�Ƃ�
		if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || pInputGamepad->GetTrigger(CInputGamepad::JOYPADKEY_B))
		{
			// ��Ɉړ��ʂ��K��l���₷
			m_move.y += JUMP_MOVE;

			//// ���[�V����������
			//m_MotionType = PLAYER_MOTION_JUMP;

			// �W�����v������Ԃɂ���
			m_bJump = true;
		}
	}

	// �ʒu�X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// ����
	m_move.x += (0 - m_move.x) * REDUCE_SPEED;
	m_move.z += (0 - m_move.z) * REDUCE_SPEED;

	// �v���C���[�̈ʒu��0�ȉ��ɂȂ����Ƃ�
	if (m_pos.y <= 0)
	{
		// �v���C���[�̈ʒu��0�ɂ���
		m_pos.y = 0;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}

	// �d�͏���
	m_move.y += GRAVITY;

	// �����X�s�[�h���K��l�𒴂�����
	if (m_move.y < MAX_GRAVITY)
	{
		// �����X�s�[�h���K��l�ɂ���
		m_move.y = MAX_GRAVITY;
	}

	// �`���[�g���A�� ���� �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL || CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// �ړ�����
		OperationMove(pInputKeyboard, pInputGamepad);
	}

	//SetPos(m_pos);			// �ʒu�ݒ�
	//SetRot(m_rot);			// ��]�ݒ�
	//SetSize(m_size);		// �傫���ݒ�

#ifdef _DEBUG
	// �f�o�b�O�\��
	CDebugProc::Print("�L�����N�^�[�̈ʒu : %.2f, %.2f, %.2f\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("�L�����N�^�[�̈ړ��� : %.2f, %.2f, %.2f\n", m_move.x, m_move.y, m_move.z);
	CDebugProc::Print("�L�����N�^�[�̉�] : %.2f, %.2f, %.2f\n", m_rot.x, m_rot.y, m_rot.z);
#endif // _DEBUG
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CCharacter::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;			// �v�Z�p�i�[�ϐ�

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// ��]�ݒ�
//==================================================================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==================================================================================================================
// �傫���ݒ�
//==================================================================================================================
void CCharacter::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//==================================================================================================================
// ���쏈��
//==================================================================================================================
void CCharacter::OperationMove(CInputKeyboard *pInputKeyboard, CInputGamepad *pInputGamepad)
{
	D3DXVECTOR3 Diff;	// �v�Z�p�i�[�ϐ�

	// �R���g���[���[
	float fValueH = 0.0f;		// �c
	float fValueV = 0.0f;		// ��
	float fMove = 0.0f;			// �R���g���[���[�X�e�B�b�N�ړ���

	// �ړ����� ���X�e�B�b�N
	pInputGamepad->GetStickLeft(&fValueV, &fValueH);

	// �L�[�{�[�h�̈ړ��L�[��������Ă��Ȃ��Ƃ�
	if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A))
	{
		// ���X�e�B�b�N ���� �c�X�e�B�b�N��0����Ȃ��Ƃ�
		if (fValueH != 0 || fValueV != 0)
		{
			// ���ɃX�e�B�b�N���|�ꂽ�Ƃ�
			if (fValueV >= -JOY_MAX_RANGE && fValueV < 0)
			{
				// �ړ��ʌv�Z
				fMove = fValueV * -PLAYER_MOVE / JOY_MAX_RANGE;

				// �X�e�B�b�N�̌X���x�ňړ�������
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = -ROT_LIMIT;

				// ��]�̖ڕW�n�_����
				m_difference.y = m_rot.y - ROT_SPEED;

				//// ���[�V����������
				//m_MotionType = PLAYER_MOTION_WALK;

				// ������Ԃɂ���
				m_bWalk = true;
			}
			else if (fValueV <= JOY_MAX_RANGE && fValueV > 0)
			{// �E�ɃX�e�B�b�N���|�ꂽ�Ƃ�
			 // �ړ��ʌv�Z
				fMove = fValueV * PLAYER_MOVE / JOY_MAX_RANGE;

				// �X�e�B�b�N�̌X���x�ňړ�������
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = ROT_LIMIT;

				// ��]�̖ڕW�n�_����
				m_difference.y = m_rot.y + ROT_SPEED;

				//// ���[�V����������
				//m_MotionType = PLAYER_MOTION_WALK;

				// ������Ԃɂ���
				m_bWalk = true;
			}
		}
	}

	// �R���g���[���[�̍��X�e�B�b�N���|����Ă��Ȃ��Ƃ�
	if (fValueV == 0)
	{
		// �L�[�{�[�h��[A]�������ꂽ�Ƃ�
		if (pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			// �L�[�{�[�h��[W]�������ꂽ�Ƃ�
			if (pInputKeyboard->GetKeyboardPress(DIK_W))
			{// ����
				m_move.x += sinf(-D3DX_PI * 0.25f) * PLAYER_MOVE;
				m_move.z += cosf(-D3DX_PI * 0.25f) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_����
				m_difference.y = D3DX_PI * 0.75f;
			}
			else if (pInputKeyboard->GetKeyboardPress(DIK_S))
			{// �L�[�{�[�h��[S]�������ꂽ�Ƃ�
			 // ����
				m_move.x += sinf(-D3DX_PI * 0.75f) * PLAYER_MOVE;
				m_move.z += cosf(-D3DX_PI * 0.75f) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_����
				m_difference.y = D3DX_PI * 0.25f;
			}
			else
			{// ��
				m_move.x += sinf(-D3DX_PI * 0.5f) * PLAYER_MOVE;
				m_move.z += cosf(-D3DX_PI * 0.5f) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_����
				m_difference.y = D3DX_PI * 0.5f;
			}

			//// ���[�V����������
			//m_MotionType = PLAYER_MOTION_WALK;

			// ������Ԃɂ���
			m_bWalk = true;
		}
		else if (pInputKeyboard->GetKeyboardPress(DIK_D))
		{// �L�[�{�[�h��[D]�������ꂽ�Ƃ�
		 // �L�[�{�[�h��[W]�������ꂽ�Ƃ�
			if (pInputKeyboard->GetKeyboardPress(DIK_W))
			{// �E��
				m_move.x += sinf(D3DX_PI * 0.25f) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI * 0.25f) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_����
				m_difference.y = -D3DX_PI * 0.75f;
			}
			else if (pInputKeyboard->GetKeyboardPress(DIK_S))
			{// �L�[�{�[�h��[S]�������ꂽ�Ƃ�
			 // �E��
				m_move.x += sinf(D3DX_PI * 0.75f) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI * 0.75f) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_����
				m_difference.y = -D3DX_PI * 0.25f;
			}
			else
			{// �E
				m_move.x += sinf(D3DX_PI * 0.5f) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI * 0.5f) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_����
				m_difference.y = -D3DX_PI * 0.5f;
			}

			//// ���[�V����������
			//m_MotionType = PLAYER_MOTION_WALK;

			// ������Ԃɂ���
			m_bWalk = true;
		}
		else if (pInputKeyboard->GetKeyboardPress(DIK_W))
		{// �L�[�{�[�h��[W]�������ꂽ�Ƃ�
		 // ��
			m_move.x += sinf(-D3DX_PI * 0.0f) * PLAYER_MOVE;
			m_move.z += cosf(-D3DX_PI * 0.0f) * PLAYER_MOVE;

			// ��]�̖ڕW�n�_����
			m_difference.y = D3DX_PI * 1.0f;
		}
		else if (pInputKeyboard->GetKeyboardPress(DIK_S))
		{// �L�[�{�[�h��[S]�������ꂽ�Ƃ�
		 // ��
			m_move.x += sinf(-D3DX_PI * 1.0f) * PLAYER_MOVE;
			m_move.z += cosf(-D3DX_PI * 1.0f) * PLAYER_MOVE;

			// ��]�̖ڕW�n�_����
			m_difference.y = D3DX_PI * 0.0f;
		}
	}

	// �v���C���[�̉�]�ƖڕW�n�_�̍����i�[
	Diff.y = m_rot.y - m_difference.y;

	// D3DX_PI���傫���Ƃ�
	if (Diff.y > D3DX_PI)
	{
		Diff.y -= D3DX_PI * 2;
	}
	else if (Diff.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ƃ�
		Diff.y += D3DX_PI * 2;
	}

	// �v���C���[�����X�ɉ�]�����Ă���
	m_rot.y -= Diff.y * ROT_AMOUNT;

	// �v���C���[�̉�]��D3DX_PI���傫���ꍇ
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{// �v���C���[�̉�]��-D3DX_PI��菬�����ꍇ
		m_rot.y += D3DX_PI * 2;
	}

	// ��Βl��D3DX_PI���傫���ꍇ
	if (fabs(m_rot.y) > D3DX_PI)
	{
		m_rot.y *= -1;
	}
}
