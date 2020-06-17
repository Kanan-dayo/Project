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
	//������
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

}

//=============================================================================
// �I��
//=============================================================================
void CModelParts::Uninit(void)
{

}

//=============================================================================
//�X�V
//=============================================================================
void CModelParts::Update(void)
{
	// ��]�ɉ��Z
	//m_rot += m_rot1F;
}

//=============================================================================
// �`��
//=============================================================================
void CModelParts::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX		mtxShadow;		// �e�̃��[���h�}�g���b�N�X
	D3DXMATRIX		DrawMtx;		// �`��p�̃��[���h�}�g���b�N�X
	D3DXMATERIAL	*pMat;
	D3DMATERIAL9	matDef;

	// ���[���h�}�g���b�N�X�̌v�Z
	CKananLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	// �e�̏��������
	if (m_nParent >= 0)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, m_mtxParent);

	// �e�N�X�`���̐ݒ�
	if (m_pModelInfo->bTex)
		pDevice->SetTexture(0, m_pModelInfo->pTexture);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pModelInfo->matBuff->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_pModelInfo->matNum; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �`��
		m_pModelInfo->mesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

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
// �����ȏ��Z�b�g (�e�N�X�`���t��)
//=============================================================================
void CModelParts::SetPartsTexInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 pTexture)
{
	m_pos = pos;
	m_rot = rot;
	m_nParent = nParent;
	m_nIndex = nIndex;
	m_pTexture = pTexture;
}

//=============================================================================
// �����ȏ��Z�b�g
//=============================================================================
void CModelParts::SetPartsInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
	m_nParent = nParent;
	m_nIndex = nIndex;
}

//=============================================================================
// �ړI�̉�]�̐ݒ�
//=============================================================================
void CModelParts::SetMotionRotDest(CMotion::MOTION_TYPE motiontype, int nKey)
{
	D3DXVECTOR3 rotDest = CMotion::GetRotDest(motiontype, nKey, m_nIndex);		// �ړI�̉�]
	D3DXVECTOR3 rot = m_rot;													// ���݂̉�]
	int nFrame = CMotion::GetFrame(motiontype, nKey);							// ������t���[����

	// 1F������̉�]�ʂ��擾
	m_rot1F = (rotDest - rot) / (float)nFrame;
}