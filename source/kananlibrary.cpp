//=============================================================================
//
//	���C�u�������� [ kananlibrary.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#include "kananlibrary.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "inputKeyboard.h"
#include "inputGamepad.h"
#include "light.h"
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �\���̒�`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
bool CKananLibrary::m_WireFrame = false;
int CKananLibrary::m_nCulling = 0;

//=============================================================================
// �}�g���b�N�X�v�Z
//=============================================================================
void CKananLibrary::CalcMatrix(D3DXMATRIX * pMtx, const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot)
{
	D3DXMATRIX	mtxRot, mtxTrans;			//�v�Z�p

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pMtx);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pMtx, pMtx, &mtxTrans);
}

//=============================================================================
// ��]�̕��
//=============================================================================
void CKananLibrary::InterpolationRot(D3DXVECTOR3 *rot)
{
	// 3.14�ȏ�
	if (rot->x > D3DX_PI)
	{
		rot->x -= D3DX_PI * 2;
	}
	// 3.14�ȉ�
	if (rot->x < -D3DX_PI)
	{
		rot->x += D3DX_PI * 2;
	}
	// 3.14�ȏ�
	if (rot->y > D3DX_PI)
	{
		rot->y -= D3DX_PI * 2;
	}
	// 3.14�ȉ�
	if (rot->y < -D3DX_PI)
	{
		rot->y += D3DX_PI * 2;
	}
	// 3.14�ȏ�
	if (rot->z > D3DX_PI)
	{
		rot->z -= D3DX_PI * 2;
	}
	// 3.14�ȉ�
	if (rot->z < -D3DX_PI)
	{
		rot->z += D3DX_PI * 2;
	}
}

//=============================================================================
// float�^�̉�]�̕��
//=============================================================================
void CKananLibrary::InterpolationFloat(float & Float)
{
	// 3.14�ȏ�
	if (Float > D3DX_PI)
	{
		Float -= D3DX_PI * 2;
	}
	// 3.14�ȉ�
	if (Float < -D3DX_PI)
	{
		Float += D3DX_PI * 2;
	}
}

//=============================================================================
// �������v�Z
//=============================================================================
float CKananLibrary::OutputSqrt(D3DXVECTOR3 difpos)
{
	float fSqrt = sqrt(difpos.x * difpos.x + difpos.y * difpos.y + difpos.z * difpos.z);
	return fSqrt;
}

//=============================================================================
// �����v�Z
//=============================================================================
float CKananLibrary::OutputDistance(D3DXVECTOR3 difpos)
{
	return difpos.x * difpos.x + difpos.y * difpos.y + difpos.z * difpos.z;
}

//=============================================================================
// �����̏���
//=============================================================================
void CKananLibrary::InertiaMove(D3DXVECTOR3 *move)
{
	move->x += (0 - move->x) * INERTIA;
	move->y += (0 - move->y) * INERTIA;
	move->z += (0 - move->z) * INERTIA;
}

//=============================================================================
// �u���b�N�R�����g�g�̕\��
//=============================================================================
void CKananLibrary::PrintBlockCommentFrame(void)
{
	std::cout << "==================================================" << std::endl;
}

//=============================================================================
// �����
//=============================================================================
HRESULT CKananLibrary::Up(CInputKeyboard * Key, CInputGamepad * pGamepad)
{
	// �L�[�{�[�h����
	if (Key && Key->GetKeyboardTrigger(DIK_W))
		return TRUE;

	// �Q�[���p�b�h�ڑ��m�F
	if (pGamepad->GetbConnect())
	{
		// ���X�e�B�b�N�擾
		float fValueX, fValueZ;
		pGamepad->GetStickLeft(&fValueX, &fValueZ);

		// �X�e�B�b�N����
		if (fValueX <= 1.0f && fValueZ > 0.0f)
			return TRUE;

		// �L�[����
		if (pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_UP))
			return TRUE;
	}

	// ���͖���
	return FALSE;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CKananLibrary::Down(CInputKeyboard * Key, CInputGamepad * pGamepad)
{
	// �L�[�{�[�h����
	if (Key && Key->GetKeyboardTrigger(DIK_S))
		return TRUE;

	// �Q�[���p�b�h�ڑ��m�F
	if (pGamepad->GetbConnect())
	{
		// ���X�e�B�b�N�擾
		float fValueX, fValueZ;
		pGamepad->GetStickLeft(&fValueX, &fValueZ);

		// �X�e�B�b�N����
		if (fValueX >= -1.0f && fValueZ < 0.0f)
			return TRUE;

		// �L�[����
		if (pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_DOWN))
			return TRUE;
	}

	// ���͖���
	return FALSE;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CKananLibrary::Left(CInputKeyboard * Key, CInputGamepad * pGamepad)
{
	// �L�[�{�[�h����
	if (Key && Key->GetKeyboardTrigger(DIK_A))
		return TRUE;

	// �Q�[���p�b�h�ڑ��m�F
	if (pGamepad->GetbConnect())
	{
		// ���X�e�B�b�N�擾
		float fValueX, fValueZ;
		pGamepad->GetStickLeft(&fValueX, &fValueZ);

		// �X�e�B�b�N����
		if (fValueX < 0 && fValueZ >= -1.0f)
			return TRUE;

		// �L�[����
		if (pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_LEFT))
			return TRUE;
	}

	// ���͖���
	return FALSE;
}

//=============================================================================
// �E����
//=============================================================================
HRESULT CKananLibrary::Right(CInputKeyboard * Key, CInputGamepad * pGamepad)
{
	// �L�[�{�[�h����
	if (Key && Key->GetKeyboardTrigger(DIK_D))
		return TRUE;

	// �Q�[���p�b�h�ڑ��m�F
	if (pGamepad->GetbConnect())
	{
		// ���X�e�B�b�N�擾
		float fValueX, fValueZ;
		pGamepad->GetStickLeft(&fValueX, &fValueZ);

		// �X�e�B�b�N����
		if (fValueX < 0 && fValueZ <= 1.0f)
			return TRUE;

		// �L�[����
		if (pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_RIGHT))
			return TRUE;
	}

	// ���͖���
	return FALSE;
}

//=============================================================================
// �������
//=============================================================================
HRESULT CKananLibrary::Decide(CInputKeyboard * Key, CInputGamepad * pGamepad)
{
	// �L�[�{�[�h����
	if (Key && Key->GetKeyboardTrigger(DIK_RETURN))
		return TRUE;

	// �Q�[���p�b�h�ڑ��m�F
	if (pGamepad->GetbConnect())
	{
		// �X�e�B�b�N����
		if (pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_A))
			return TRUE;
	}

	// ���͖���
	return FALSE;
}

//=============================================================================
// �߂����
//=============================================================================
HRESULT CKananLibrary::Return(CInputKeyboard * Key, CInputGamepad * pGamepad)
{
	// �L�[�{�[�h����
	if (Key && Key->GetKeyboardTrigger(DIK_BACKSPACE))
		return TRUE;

	// �Q�[���p�b�h�ڑ��m�F
	if (pGamepad->GetbConnect())
	{
		// �X�e�B�b�N����
		if (pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_B))
			return TRUE;
	}

	// ���͖���
	return FALSE;
}

//=============================================================================
// �|�[�Y����
//=============================================================================
HRESULT CKananLibrary::Pause(CInputKeyboard * Key, CInputGamepad * pGamepad)
{
	// �L�[�{�[�h����
	if (Key && Key->GetKeyboardTrigger(DIK_P))
		return TRUE;

	// �Q�[���p�b�h�ڑ��m�F
	if (pGamepad->GetbConnect())
	{
		// �X�e�B�b�N����
		if (pGamepad->GetTrigger(CInputGamepad::JOYPADKEY_START))
			return TRUE;
	}

	// ���͖���
	return FALSE;
}

#ifdef _DEBUG
//=============================================================================
// ImGui�̍X�V
//=============================================================================
void CKananLibrary::ShowDebugInfo(void)
{
	// �c���[�̃w�b�_�[
	if (ImGui::CollapsingHeader("DebugInfo"))
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// FPS�̕\��
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		//// Scene2D�����̕\��
		//ImGui::Text("NumScene2D : %d", CScene2D::GetNumScene2D());
		//// Scene2D�����̕\��
		//ImGui::Text("NumScene3D : %d", CScene3D::GetNumScene3D());
		//// Scene2D�����̕\��
		//ImGui::Text("NumSceneX  : %d", CSceneX::GetNumSceneX());

		// ���C���[�t���[��
		if (ImGui::Checkbox("WireFrame", &m_WireFrame))
		{
			// ? A : B (�������Z�q : �^(A)�U(B)�ǂ��炩�����Ă͂܂��Ă���΁A��������s����)
			m_WireFrame ?
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME) :	//���C���[
				pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			//�ʏ�
		}

		// �S�̂̃J�����O
		if (ImGui::TreeNode("Culling"))
		{
			// �J�����O
			if (ImGui::RadioButton("CCW", &m_nCulling, 0))
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);		// ����(�����)���J�����O����
			// ���s���Ȃ�
			ImGui::SameLine();
			if (ImGui::RadioButton("CW", &m_nCulling, 1))
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);		// �\��(�E���)���J�����O����
			// ���s���Ȃ�
			ImGui::SameLine();
			if (ImGui::RadioButton("NONE", &m_nCulling, 2))
				pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);		// ���ʃJ�����O

			// �c���[�̍Ō�ɕK������
			ImGui::TreePop();
		}
	}
}
#endif