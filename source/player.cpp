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
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v
#include "3DBoxCollider.h"
#include "stone.h"

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
	this->m_nBoxColliderID = C3DBoxCollider::SetColliderInfo(&this->GetPos(), this, C3DBoxCollider::ID_CHARACTER);
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
	// �����蔻��ʒu�̍X�V
	C3DBoxCollider::ChangePosition(this->m_nBoxColliderID, this->GetPos(), MYLIB_3DVECTOR_ZERO);

	// �X�g�[���̎擾����
	CatchStone();
	
#ifdef _DEBUG
	ShowDebugInfo();
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
// �Q�[���p�b�h�̑���
//==================================================================================================================
void CPlayer::ControlGamepad(CInputGamepad * pGamepad)
{
	float fValueX, fValueY;	// �Q�[���p�b�h�̃X�e�B�b�N���̎擾�p

	// ���X�e�B�b�N�擾
	pGamepad->GetStickLeft(&fValueX, &fValueY);

	// �X�e�B�b�N�������ĂȂ���Ώ������Ȃ�
	if (fValueX == 0 && fValueY == 0)
	{
		SetbWalk(false);
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
	rotDest.y = D3DX_PI + fAngle + CameraRotY;

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

	if (!m_bJump && 
		(m_nPlayer == 0 && (pKeyboard->GetKeyboardTrigger(ONE_JUMP)) || 
		m_nPlayer == 1 && (pKeyboard->GetKeyboardTrigger(TWO_JUMP))))
	{
		move.y += VALUE_JUMP;
		m_bJump = true;
		m_bWalk = false;
	}

	// A�L�[������
	if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_LEFT)) ||
		m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_LEFT))
	{
		// W�L�[������
		if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_UP)) ||
			m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_UP))
		{
			// ����ړ�
			move.x += sinf(-D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(-D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.y = D3DX_PI * 0.75f + CameraRotY;
		}
		// S�L�[������
		else if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_DOWN)) ||
			m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_DOWN))
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
	else if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_RIGHT)) ||
		m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_RIGHT))
	{
		// W�L�[������
		if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_UP)) ||
			m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_UP))
		{
			// �E��ړ�
			move.x += sinf(D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			move.z -= cosf(D3DX_PI * 0.75f - CameraRotY) * VALUE_MOVE_PLAYER;
			// �ړI�̌���������
			rotDest.y = -D3DX_PI * 0.75f + CameraRotY;
		}
		// S�L�[������
		else if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_DOWN)) ||
			m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_DOWN))
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
	else if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_UP)) ||
		m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_UP))
	{
		// ��ړ�
		move.x += sinf(D3DX_PI * 1.0f - CameraRotY) * VALUE_MOVE_PLAYER;
		move.z -= cosf(D3DX_PI * 1.0f - CameraRotY) * VALUE_MOVE_PLAYER;
		// �ړI�̌���������
		rotDest.y = -D3DX_PI * 1.0f + CameraRotY;
	}
	// S�L�[������
	else if ((m_nPlayer == 0 && pKeyboard->GetKeyboardPress(ONE_DOWN)) ||
		m_nPlayer == 1 && pKeyboard->GetKeyboardPress(TWO_DOWN))
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
	if (ImGui::CollapsingHeader("Player"))
	{
		CKananLibrary::ShowOffsetInfo(GetPos(), GetRot(), GetMove());
		ImGui::Text("nLife : %f", m_nLife);
		ImGui::Text("bJump : %d", m_bJump);
	}
}
#endif