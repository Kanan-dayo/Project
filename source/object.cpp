//=============================================================================
//
// �I�u�W�F�N�g���� [ object.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "debugProc.h"
//#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
//#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
//#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(PRIORITY type = CSceneX::PRIORITY_PLAYER) :CSceneX(type)
{
	// �v�f�̏�����
	m_bRelease = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{

}

//=============================================================================
// ������
//=============================================================================
void CObject::Init(void)
{
	CSceneX::Init();
}

//=============================================================================
// �I��
//=============================================================================
void CObject::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �X�V
//=============================================================================
void CObject::Update(void)
{
	CSceneX::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CObject::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// ����
//=============================================================================
std::unique_ptr<CObject> CObject::Create(void)
{
	// �������m��
	std::unique_ptr<CObject> pObject = std::make_unique<CObject>();

	// ������
	pObject->Init();

	// �l��Ԃ�
	return pObject;
}

//=============================================================================
// ���f�����̊i�[
//=============================================================================
void CObject::SetObjInfo(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPos(pos);
	SetRot(rot);
}

//=============================================================================
// �I�u�W�F�N�g�̓����蔻��
//=============================================================================
/*bool CObject::CollObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax)
{
	bool bLand = false;
	D3DXVECTOR3 objPos = GetPos();
	D3DXVECTOR3 objPosOld = GetPosOld();

	if (pos->x + vtxMax.x > objPos.x + m_vtxMin.x && pos->x + vtxMin.x < objPos.x + m_vtxMax.x &&
		pos->y + vtxMax.y >= objPos.y + m_vtxMin.y && pos->y + vtxMin.y < objPos.y + m_vtxMax.y)
	{
		// �u���b�N�O���̔���
		if (pos->z + vtxMax.z >= objPos.z + m_vtxMin.z && posOld->z + vtxMax.z <= objPosOld.z + m_vtxMin.z)
		{
			pos->z = objPos.z + m_vtxMin.z - vtxMax.z;
			move->z = 0.0f;
			bLand = true;
			CDebugProc::Print("�O\n");
		}
		// �u���b�N�㕔�̔���
		if (pos->z + vtxMin.z <= objPos.z + m_vtxMax.z && posOld->z + vtxMin.z >= objPosOld.z + m_vtxMax.z)
		{
			pos->z = objPos.z + m_vtxMax.z - vtxMin.z;
			move->z = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
	}

	if (pos->z + vtxMax.z > objPos.z + m_vtxMin.z && pos->z + vtxMin.z < objPos.z + m_vtxMax.z &&
		pos->y + vtxMax.y >= objPos.y + m_vtxMin.y && pos->y + vtxMin.y < objPos.y + m_vtxMax.y)
	{
		// �u���b�N�����̔���
		if (pos->x + vtxMax.x >= objPos.x + m_vtxMin.x && posOld->x + vtxMax.x <= objPosOld.x + m_vtxMin.x)
		{
			pos->x = objPos.x + m_vtxMin.x - vtxMax.x;
			move->x = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
		// �u���b�N�E���̔���
		if (pos->x + vtxMin.x <= objPos.x + m_vtxMax.x && posOld->x + vtxMin.x >= objPosOld.x + m_vtxMax.x)
		{
			pos->x = objPos.x + m_vtxMax.x - vtxMin.x;
			move->x = 0.0f;
			bLand = true;
			CDebugProc::Print("�E\n");
		}
	}

	if (pos->x + vtxMax.x > objPos.x + m_vtxMin.x && pos->x + vtxMin.x < objPos.x + m_vtxMax.x &&
		pos->z + vtxMax.z > objPos.z + m_vtxMin.z && pos->z + vtxMin.z < objPos.z + m_vtxMax.z)
	{
		// �u���b�N�㕔�̔���
		if (pos->y + vtxMin.y <= objPos.y + m_vtxMax.y && posOld->y + vtxMin.y >= objPosOld.y + m_vtxMax.y)
		{
			pos->y = objPos.y + m_vtxMax.y - vtxMin.y;
			move->y = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
		// �u���b�N�����̔���
		if (pos->y + vtxMax.y >= objPos.y + m_vtxMin.y && posOld->y + vtxMax.y <= objPosOld.y + m_vtxMin.y)
		{
			pos->y = objPos.y + m_vtxMin.y - vtxMax.y;
			move->y = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
	}

	return bLand;
}*/

/*#ifdef _DEBUG
//=============================================================================
// ImGui�̍X�V
//=============================================================================
void CObject::ShowObjectInfo(char cPrintText[16])
{
	// ���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	int nType = m_type;

	// �c���[
	if (ImGui::TreeNode(cPrintText))
	{
		// �U�I�u�W�F�N�g�ȊO
		if (cPrintText != "FakeObject")
		{
			ImGui::Text("type : %d", m_type);
		}

		ImGui::DragFloat3("pos", pos, 0.5f);
		ImGui::DragFloat3("rot", rot, 0.05f, -D3DX_PI, D3DX_PI);

		// �U�I�u�W�F�N�g�ȊO
		if (cPrintText != "FakeObject")
		{
			// ���s�����ɊԊu��������
			ImGui::Dummy(ImVec2(200.0f, 0.0f));
			ImGui::SameLine();

			// �폜
			if (ImGui::Button("delete"))
			{
				// �����[�X����
				m_bRelease = true;
			}
		}

		// �c���[�̍Ō�ɕK������
		ImGui::TreePop();
	}

	// ���W�E��]�̍X�V
	SetPos(pos);
	SetRot(rot);
}
#endif*/