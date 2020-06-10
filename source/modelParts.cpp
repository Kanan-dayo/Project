//=============================================================================
//
// ���f���̃p�[�c����  [ modelParts.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "modelparts.h"
#include "renderer.h"
#include "manager.h"
#include "Inputkeyboard.h"
#include "ImGui/imgui.h"
#include "debugproc.h"
#include "player.h"
#include "sceneX.h"
#include "kananlibrary.h"

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelParts::CModelParts()
{
}

CModelParts::CModelParts(PRIORITY nPriority) : CSceneX(nPriority)
{
	//������
	m_pParentMtx = nullptr;
	m_nIndex = 0;
	m_nParent = 0;
	m_rot1F = ZeroVector3;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelParts::~CModelParts()
{

}

//=============================================================================
// ������
//=============================================================================
void CModelParts::Init(void)
{
	// �V�[���̏�����
	CSceneX::Init();
}

//=============================================================================
// �I��
//=============================================================================
void CModelParts::Uninit(void)
{
	// �V�[���̏I��
	CSceneX::Uninit();
}

//=============================================================================
//�X�V
//=============================================================================
void CModelParts::Update(void)
{
	//���݂̉�]��skj
	D3DXVECTOR3 rot = *GetRot();

	//��]�ɉ��Z
	rot += m_rot1F;

	//�X�V������]������
	CSceneX::SetRot(rot);

	//�X�V
	CSceneX::Update();
}

//=============================================================================
// �`��
//=============================================================================
void CModelParts::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX			mtxShadow;		// �e�̃��[���h�}�g���b�N�X
	D3DXMATRIX			DrawMtx;		// �`��p�̃��[���h�}�g���b�N�X
	D3DXMATRIX			*mtxWorld = GetMatrix();	// ���f���̃}�g���b�N�X

	// �}�g���b�N�X�v�Z
	CKananLibrary::CalcMatrix(mtxWorld, *GetPos(), *GetRot());
	D3DXMatrixMultiply(mtxWorld, mtxWorld, m_pParentMtx);

	// ���f���̕`��
	CSceneX::DrawMesh();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	// ���f���̃��[���h���W�擾
	pDevice->GetTransform(D3DTS_WORLD, &DrawMtx);

	// �e�̃}�g���b�N�X�v�Z
	CKananLibrary::CalcShadowMatrix(mtxShadow, D3DXVECTOR3(0.0f, 1.0f, 0.0f), AboveNormal);

	// �`��p�̃}�g���b�N�X�ɂ������킹��
	D3DXMatrixMultiply(&DrawMtx, &DrawMtx, &mtxShadow);

	// ���f�����W���烏�[���h���W�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, &DrawMtx);

	// �e�̕`��
	//CSceneX::DrawShadow();
}

//=============================================================================
// �e�̃}�g���b�N�X�ݒ�
//=============================================================================
void CModelParts::SetParentMtx(D3DXMATRIX *mtx)
{
	m_pParentMtx = mtx;
}

//=============================================================================
// �����ȏ��Z�b�g (�e�N�X�`���t��)
//=============================================================================
void CModelParts::SetPartsTexInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 pTexture)
{
	CSceneX::SetPos(pos);
	CSceneX::SetRot(rot);
	m_nParent = nParent;
	m_nIndex = nIndex;
	CSceneX::BindTex(pTexture);
}

//=============================================================================
// �����ȏ��Z�b�g
//=============================================================================
void CModelParts::SetPartsInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSceneX::SetPos(pos);
	CSceneX::SetRot(rot);
	m_nParent = nParent;
	m_nIndex = nIndex;
}

//=============================================================================
// �ړI�̉�]�̐ݒ�
//=============================================================================
void CModelParts::SetMotionRotDest(CMotion::MOTION_TYPE motiontype, int nKey)
{
	D3DXVECTOR3 rotDest = CMotion::GetRotDest(motiontype, nKey, m_nIndex);		// �ړI�̉�]
	D3DXVECTOR3 rot = *GetRot();													// ���݂̉�]
	int nFrame = CMotion::GetFrame(motiontype, nKey);							// ������t���[����

	// 1F������̉�]�ʂ��擾
	m_rot1F = (rotDest - rot) / (float)nFrame;
}