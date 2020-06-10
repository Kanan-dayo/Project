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
#include "objManager.h"
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject(PRIORITY nPriority) : CSceneX(nPriority)
{

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
	// �v�f�̏�����
	m_bRelease = false;

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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	D3DXMATRIX *pMtx = GetMatrix();;

	CKananLibrary::CalcMatrix(pMtx, *GetPos(), *GetRot());

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, pMtx);

	CSceneX::DrawMesh();
}

//=============================================================================
// ����
//=============================================================================
CObject * CObject::Create(void)
{
	// �������m��
	CObject *pObject = new CObject(CScene::PRIORITY_OBJECT);

	// nullcheck
	if (!pObject)
	{
		// ���s
		return nullptr;
	}

	// ������
	pObject->Init();

	// �l��Ԃ�
	return pObject;
}

//=============================================================================
// �I�u�W�F�N�g�̏��ݒ�
//=============================================================================
void CObject::SetObjInfo(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot, const LPDIRECT3DTEXTURE9 & pTexture, const int & type, const bool & bCollision)
{
	SetPos(pos);
	SetRot(rot);
	BindTex(pTexture);
	m_nType = type;
	m_bCollision = bCollision;
}

//=============================================================================
// �I�u�W�F�N�g�̓����蔻��
//=============================================================================
bool CObject::CollObject(D3DXVECTOR3 *pos, const D3DXVECTOR3 & posOld, D3DXVECTOR3 *move, const MODEL_VTX & modelVtx)
{
	bool bLand = false;
	D3DXVECTOR3 objPos = *GetPos();
	D3DXVECTOR3 objPosOld = *GetPosOld();
	MODEL_VTX	Vtx = CObjectManager::GetModelVtx(m_nType);

	if (pos->x + modelVtx.VtxMax.x > objPos.x + Vtx.VtxMin.x && pos->x + modelVtx.VtxMin.x < objPos.x + Vtx.VtxMax.x &&
		pos->y + modelVtx.VtxMax.y >= objPos.y + Vtx.VtxMin.y && pos->y + modelVtx.VtxMin.y < objPos.y + Vtx.VtxMax.y)
	{
		// �u���b�N�O���̔���
		if (pos->z + modelVtx.VtxMax.z >= objPos.z + Vtx.VtxMin.z && posOld.z + modelVtx.VtxMax.z <= objPosOld.z + Vtx.VtxMin.z)
		{
			pos->z = objPos.z + Vtx.VtxMin.z - modelVtx.VtxMax.z;
			move->z = 0.0f;
			bLand = true;
			CDebugProc::Print("�O\n");
		}
		// �u���b�N�㕔�̔���
		if (pos->z + modelVtx.VtxMin.z <= objPos.z + Vtx.VtxMax.z && posOld.z + modelVtx.VtxMin.z >= objPosOld.z + Vtx.VtxMax.z)
		{
			pos->z = objPos.z + Vtx.VtxMax.z - modelVtx.VtxMin.z;
			move->z = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
	}

	if (pos->z + modelVtx.VtxMax.z > objPos.z + Vtx.VtxMin.z && pos->z + modelVtx.VtxMin.z < objPos.z + Vtx.VtxMax.z &&
		pos->y + modelVtx.VtxMax.y >= objPos.y + Vtx.VtxMin.y && pos->y + modelVtx.VtxMin.y < objPos.y + Vtx.VtxMax.y)
	{
		// �u���b�N�����̔���
		if (pos->x + modelVtx.VtxMax.x >= objPos.x + Vtx.VtxMin.x && posOld.x + modelVtx.VtxMax.x <= objPosOld.x + Vtx.VtxMin.x)
		{
			pos->x = objPos.x + Vtx.VtxMin.x - modelVtx.VtxMax.x;
			move->x = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
		// �u���b�N�E���̔���
		if (pos->x + modelVtx.VtxMin.x <= objPos.x + Vtx.VtxMax.x && posOld.x + modelVtx.VtxMin.x >= objPosOld.x + Vtx.VtxMax.x)
		{
			pos->x = objPos.x + Vtx.VtxMax.x - modelVtx.VtxMin.x;
			move->x = 0.0f;
			bLand = true;
			CDebugProc::Print("�E\n");
		}
	}

	if (pos->x + modelVtx.VtxMax.x > objPos.x + Vtx.VtxMin.x && pos->x + modelVtx.VtxMin.x < objPos.x + Vtx.VtxMax.x &&
		pos->z + modelVtx.VtxMax.z > objPos.z + Vtx.VtxMin.z && pos->z + modelVtx.VtxMin.z < objPos.z + Vtx.VtxMax.z)
	{
		// �u���b�N�㕔�̔���
		if (pos->y + modelVtx.VtxMin.y <= objPos.y + Vtx.VtxMax.y && posOld.y + modelVtx.VtxMin.y >= objPosOld.y + Vtx.VtxMax.y)
		{
			pos->y = objPos.y + Vtx.VtxMax.y - modelVtx.VtxMin.y;
			move->y = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
		// �u���b�N�����̔���
		if (pos->y + modelVtx.VtxMax.y >= objPos.y + Vtx.VtxMin.y && posOld.y + modelVtx.VtxMax.y <= objPosOld.y + Vtx.VtxMin.y)
		{
			pos->y = objPos.y + Vtx.VtxMin.y - modelVtx.VtxMax.y;
			move->y = 0.0f;
			bLand = true;
			CDebugProc::Print("��\n");
		}
	}

	return bLand;
}

#ifdef _DEBUG
//=============================================================================
// ImGui�̍X�V
//=============================================================================
void CObject::ShowObjectInfo(char cPrintText[16])
{
	// ���擾
	D3DXVECTOR3 pos = *GetPos();
	D3DXVECTOR3 rot = *GetRot();

	// �c���[
	if (ImGui::TreeNode(cPrintText))
	{
		// �U�I�u�W�F�N�g�ȊO
		if (cPrintText != "FakeObject")
		{
			ImGui::Text("type : %d", m_nType);
		}

		ImGui::DragFloat3("pos", pos, 0.5f);
		ImGui::DragFloat3("rot", rot, 0.05f, -D3DX_PI, D3DX_PI);
		ImGui::Checkbox("Collision", &m_bCollision);

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

	SetPos(pos);
	SetRot(rot);
}
#endif