//==================================================================================================================
//
// �J����[camera.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "camera.h"
#include "scene.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "title.h"
#include "mouse.h"
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define camera_move 3.1f							// �J�����̈ړ��X�s�[�h
#define CAMERA_ROT_SPEED_Y 0.05f					// �J�����̉�]�X�s�[�h
#define CAMERA_ROT_SPEED_X 0.025f					// �J�����̉�]�X�s�[�h
#define cameraLength 100.0f							// �J��������̋���
#define posR_Length 3.0f							// ���f���ƒ����_�̈ʒu
#define posR_distance 80.0f							// ���f���ƒ����_�̋���
#define coefficient 0.05f							// �W��
#define posV_distance 100.0f						// ���f���Ǝ��_�̋���
#define posV_Height 70.0f							// ���_�̍���
#define SHRINK_SPEED_Y 0.2f							// posV��Y�̏k�߂鑬�x
#define ROT_SHRINK 0.1f								// ��]�̏k�߂鑬�x
#define TITLE_FADE_COUNT 60							// �^�C�g���t�F�[�h�J�E���g
#define TITLE_POSV_X 0.0f							// �^�C�g���ł̃J�������_�ʒuX
#define TITLE_POSV_Y 20.0f							// �^�C�g���ł̃J�������_�ʒuY
#define TITLE_POSV_Z 50.0f							// �^�C�g���ł̃J�������_�ʒuZ
#define TITLE_POSR_X 0.0f							// �^�C�g���ł̃J���������_�ʒuX
#define TITLE_POSR_Y 1.0f							// �^�C�g���ł̃J���������_�ʒuY
#define TITLE_POSR_Z 50.0f							// �^�C�g���ł̃J���������_�ʒuZ
#define DISTANCE 100.0f								// ���_�ƒ����_�̋���
#define ROT_COUNT 5									// ��]���n�߂�J�E���g

#define POSV_Y_DOWN_LIMIT (5.0f)					// ���_�̉��~����

#define CAMERA_RADIAN	(45.0f)						// �J�����̎���p
#define CAMERA_NEAR_Z	(10.0f)						// �J������NearZ�l
#define CAMERA_FAR_Z	(6000.0f)					// �J������FarZ�l

#define SPEED_INERTIA	(5)							// �J�����̊���

#define MOUSE_SPEED		(0.20f)						// �}�E�X�J�[�\������������̂Œ���

#define ROT_X_LIMIT_LOW	(-1.51f)						// �J����X���̉���
#define ROT_X_LIMIT_UP	(1.51f)						// �J����X���̏��

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CCamera *CCamera::m_pCamera = NULL;					// �J�������

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CCamera::CCamera()
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CCamera::~CCamera()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CCamera::Init(void)
{
	// �ϐ��̏�����
	m_posV		= ZeroVector3;
	m_posDebug	= ZeroVector3;
	m_posR		= ZeroVector3;
	m_posVDest	= ZeroVector3;
	m_posRDest	= ZeroVector3;
	m_posU		= ZeroVector3;
	m_rot		= ZeroVector3;
	m_rotDest	= ZeroVector3;
	m_mousePos	= ZeroVector3;
	m_fDistance = 0.0f;
	m_fDisScale = 1.0f;
	nCntRot = 0;										// ��]���n�߂�J�E���^
	m_nCntTitleFade = 0;								// �^�C�g���t�F�[�h�J�E���^
	m_bCameraMode = false;								// �J�������[�h���ǂ���
	m_mode = CAMERA_GAME;

#ifdef _DEBUG
	m_mode = CAMERA_DEBUG;
#endif
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CCamera::Uninit(void)
{

}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CCamera::Update(void)
{
	// �Q�[�����[�h���^�C�g���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{

	}

	// �Q�[�����[�h���Q�[���̂Ƃ� ���� �`���[�g���A���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME || CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		// �Q�[�����[�h���`���[�g���A���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
		{

		}

		// �Q�[�����[�h���Q�[���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_GAME){}
			GameCamera();
	}

#ifdef _DEBUG
	if (CAMERA_DEBUG == m_mode)
		// �f�o�b�O���̑���
		DebugControl();

	// ImGui�̍X�V
	ShowDebugInfo();
#endif // _DEBUG

	// �x�N�g�����Z�o���Đ��K��
	m_vec = m_posR - m_posV;
	D3DXVec3Normalize(&m_vec, &m_vec);
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CCamera::Draw(void)
{
#ifdef _DEBUG
	// �f�o�b�O�\��
#endif // _DEBUG
}

//==================================================================================================================
// �J�����̐ݒ�
//==================================================================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice(); // �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,
		D3DXToRadian(CAMERA_RADIAN),				// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// �A�X�y�N�g��
		CAMERA_NEAR_Z,								// NearZ�l
		CAMERA_FAR_Z);								// FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,	// �J�����̎��_
		&m_posR,	// �J�����̒����_
		&m_posU);	// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==================================================================================================================
// �J�����̈ʒu�ݒ�
//==================================================================================================================
void CCamera::SetCameraPos(const D3DXVECTOR3 posV, const D3DXVECTOR3 posR)
{
	// ���̏�����
	m_posV = posV;
	m_posR = posR;
	m_posVDest = posV;
	m_posRDest = posR;
	m_posDebug = ZeroVector3;
	m_posU = AboveNormal;
	m_rot = D3DXVECTOR3(0.6f, -0.8f, 0.0f);
	m_fDistance = 0.0f;

	// �ʒu�̍������߁A�����𑪂�
	D3DXVECTOR3 difpos = m_posR - m_posV;
	m_fDistance = (float)sqrt(difpos.y * difpos.y + difpos.z * difpos.z);
}

//==================================================================================================================
// ImGui�̍X�V
//==================================================================================================================
void CCamera::ShowDebugInfo(void)
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		// ���̕\��
		ImGui::Text("posR : %.4f, %.4f, %.4f", m_posR.x, m_posR.y, m_posR.z);
		ImGui::Text("posV : %.4f, %.4f, %.4f", m_posV.x, m_posV.y, m_posV.z);
		ImGui::Text("rot  : %.4f, %.4f, %.4f", m_rot.x, m_rot.y, m_rot.z);
		ImGui::Text("Distance : %.4f", m_fDistance);
		// �������������
		ImGui::DragFloat("Distance", &m_fDisScale, 0.05f, 0.0f, 100.0f);
	}
}

//==================================================================================================================
// �Q�[���̃J����
//==================================================================================================================
void CCamera::GameCamera(void)
{
	D3DXVECTOR3 difposR, difposV;	// pos��posDest�̍����i�[�p

	// �ړI�̒����_�̌v�Z
	m_posRDest.x = sinf(m_rot.y);
	m_posRDest.y = tanf(m_rot.x);
	m_posRDest.z = cosf(m_rot.y);

	// ���݂̒����_�ƖړI�̒����_�̍����̌v�Z
	difposR = m_posRDest - m_posR;

	// �����_��ǂ������鑬�x
	m_posR += difposR / SPEED_INERTIA;

	// �ړI�̎��_�̌v�Z
	m_posVDest.x = -cosf(m_rot.x) * sinf(m_rot.y) * m_fDistance * m_fDisScale;
	m_posVDest.y = sinf(m_rot.x) * m_fDistance * m_fDisScale;
	m_posVDest.z = -cosf(m_rot.x) * cosf(m_rot.y) * m_fDistance * m_fDisScale;

	if (m_mode == CAMERA_GAME)
	{
		// posV�̍�������
		if (m_posVDest.y <= POSV_Y_DOWN_LIMIT)
			m_posVDest.y = POSV_Y_DOWN_LIMIT;
	}

	// ���݂̎��_�ƖړI�̎��_�̍����̌v�Z
	difposV = m_posVDest - m_posV;

	// ���_�������_�ɒǂ������x
	m_posV += difposV / SPEED_INERTIA;


	if (m_mode == CAMERA_GAME)
	{
		// posV�̍�������
		if (m_posV.y <= POSV_Y_DOWN_LIMIT)
			m_posV.y = POSV_Y_DOWN_LIMIT;
	}

	if (m_rot.x >= ROT_X_LIMIT_UP)
		m_rot.x = ROT_X_LIMIT_UP;
	if (m_rot.x <= ROT_X_LIMIT_LOW)
		m_rot.x = ROT_X_LIMIT_LOW;
}

#ifdef _DEBUG
//==================================================================================================================
// �f�o�b�O���̑���
//==================================================================================================================
void CCamera::DebugControl(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// F1�L�[�Ń��[�h�ؑ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_F1))
		m_mode ?
		m_mode = CAMERA_DEBUG :
		m_mode = CAMERA_GAME;

	CDebugProc::Print("%d\n", m_mode);

	if (m_mode == CAMERA_DEBUG)
	{
		// �}�E�X�ł̑���
		ControlMouse();
		// �L�[�{�[�h�ł̑���
		ControlKeyboard(pInputKeyboard);
	}

	CKananLibrary::InterpolationRot(&m_rot);
}
#endif

//==================================================================================================================
// �}�E�X�̑���
//==================================================================================================================
void CCamera::ControlMouse(void)
{
	// �}�E�X�̎擾
	CMouse *pMouse = CManager::GetMouse();

	// ���N���b�N��
	if (pMouse->GetPressTrigger(1))
	{
		// �}�E�X�̍��W�擾
		m_mousePos.x = (float)pMouse->GetposX();
		m_mousePos.y = (float)pMouse->GetposY();
	}
	// ���N���b�N��������
	if (pMouse->GetPress(1))
	{
		// �}�E�X���W�̍������i�[
		D3DXVECTOR2 difPos;

		// ���������̃}�E�X�̍��W�擾
		difPos.x = (float)pMouse->GetposX();
		difPos.y = (float)pMouse->GetposY();

		// ���W�̍����m�F
		if (m_mousePos != difPos)
		{
			// �����̉�]
			if (m_mousePos.x > difPos.x)
				m_rot.y -= (m_mousePos.x - difPos.x) / SCREEN_HEIGHT / D3DX_PI * MOUSE_SPEED;
			else if (m_mousePos.x < difPos.x)
				m_rot.y -= (m_mousePos.x - difPos.x) / SCREEN_HEIGHT / D3DX_PI * MOUSE_SPEED;
			m_rot.x += (m_mousePos.y - difPos.y) / SCREEN_HEIGHT / D3DX_PI * MOUSE_SPEED;

			// ��]�̕��
			CKananLibrary::InterpolationRot(&m_rot);
		}
	}
}

//==================================================================================================================
// �L�[�{�[�h�ł̑���
//==================================================================================================================
void CCamera::ControlKeyboard(CInputKeyboard *pKeyboard)
{

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	/*if (pKeyboard->GetKeyboardPress(DIK_LEFTARROW))
	{
		// ���_�����ɓ�����
		m_posV.x += sinf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posV.z += cosf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;

		// ���_�����ɓ�����
		m_posR.x += sinf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posR.z += cosf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pKeyboard->GetKeyboardPress(DIK_RIGHTARROW))
	{
		// ���_���E�ɓ�����
		m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
		// ���_���E�ɓ�����
		m_posR.x += sinf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posR.z += cosf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pKeyboard->GetKeyboardPress(DIK_UP))
	{
		// ���_��O�ɓ�����
		m_posV.x += sinf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		m_posV.z += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		// ���_��O�ɓ�����
		m_posR.x += sinf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		m_posR.z += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pKeyboard->GetKeyboardPress(DIK_DOWN))
	{
		// ���_�����ɓ�����
		m_posV.x += sinf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
		m_posV.z += cosf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
		// ���_�����ɓ�����
		m_posR.x += sinf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
		m_posR.z += cosf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
	}*/

	if (pKeyboard->GetKeyboardPress(DIK_1))
	{// �L�[�{�[�h��[1]�������ꂽ�Ƃ�
	 // ���_����ɓ�����
		m_posV.y += cosf(D3DX_PI * 1.0f + m_rot.y) * camera_move;
		// ���_����ɓ�����
		m_posR.y += cosf(D3DX_PI * 1.0f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[2]�������ꂽ�Ƃ�
	if (pKeyboard->GetKeyboardPress(DIK_2))
	{
		// ���_�����ɓ�����
		m_posV.y += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		// ���_�����ɓ�����
		m_posR.y += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
	}

	if (!pKeyboard->GetKeyboardPress(DIK_LSHIFT))
	{
		// �L�[�{�[�h��[Q]�������ꂽ�Ƃ�
		if (pKeyboard->GetKeyboardPress(DIK_Q))
		{
			// ���_�𒆐S�ɉ�]����(�����)
			m_rot.y -= CAMERA_ROT_SPEED_Y;

			// ��]���-D3DX_PI��菬�����Ȃ����Ƃ�
			if (m_rot.y < -D3DX_PI)
				m_rot.y += D3DX_PI * 2;
		}

		// �L�[�{�[�h��[E]�������ꂽ�Ƃ�
		if (pKeyboard->GetKeyboardPress(DIK_E))
		{
			// ���_�𒆐S�ɉ�]����(�E���)
			m_rot.y += CAMERA_ROT_SPEED_Y;

			// ��]���D3DX_PI���傫���Ȃ����Ƃ�
			if (m_rot.y > D3DX_PI)
				m_rot.y -= D3DX_PI * 2;
		}
	}
	else
	{
		// �L�[�{�[�h��[Q]�������ꂽ�Ƃ�
		if (pKeyboard->GetKeyboardPress(DIK_Q))
		{
			// ���_�𒆐S�ɉ�]����(�����)
			m_rot.x -= CAMERA_ROT_SPEED_X;

			// ��]���-D3DX_PI��菬�����Ȃ����Ƃ�
			if (m_rot.x < -D3DX_PI)
				m_rot.x += D3DX_PI * 2;
		}

		// �L�[�{�[�h��[E]�������ꂽ�Ƃ�
		if (pKeyboard->GetKeyboardPress(DIK_E))
		{
			// ���_�𒆐S�ɉ�]����(�E���)
			m_rot.x += CAMERA_ROT_SPEED_X;

			// ��]���D3DX_PI���傫���Ȃ����Ƃ�
			if (m_rot.x > D3DX_PI)
				m_rot.x -= D3DX_PI * 2;
		}
	}

	// �J�����̉��ߒ���
	if (pKeyboard->GetKeyboardPress(DIK_C))
		m_fDisScale += 0.005f;
	if (pKeyboard->GetKeyboardPress(DIK_Z))
		m_fDisScale -= 0.005f;

	CKananLibrary::InterpolationRot(&m_rot);
}

//==================================================================================================================
// �J�����̐���
//==================================================================================================================
CCamera * CCamera::Create(void)
{
	// �������𓮓I�Ɋm��
	m_pCamera = new CCamera();

	// �J�����̏�����
	m_pCamera->Init();

	m_pCamera->SetCameraPos(D3DXVECTOR3(280.0f, 280.0f, -280.0f),
							D3DXVECTOR3(0.0f, 10.0f, 0.0f));

	//m_posV = D3DXVECTOR3(0.0f, 150.0f, -500.0f);		// ���_
	//m_posVDest = D3DXVECTOR3(0.0f, 150.0f, -500.0f);	// ���_�̖ڕW�n�_
	//m_posR = D3DXVECTOR3(0.0f, 10.0f, 0.0f);			// �����_
	//m_posRDest = D3DXVECTOR3(0.0f, 10.0f, 0.0f);		// �����_�̖ڕW�n�_
	//m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// ������x�N�g��
	//m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�̖ڕW�n�_

	// �l��Ԃ�
	return m_pCamera;
}