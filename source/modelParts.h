//=============================================================================
//
// ���f���̃p�[�c����  [ modelParts.h ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#ifndef _MODELPARTS_H_
#define _MODELPARTS_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "sceneX.h"
#include "motion.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CModelParts
{
public:
	CModelParts();
	virtual ~CModelParts();

	void Init(void);																	// ������
	void Uninit(void);																	// �I��
	void Update(void);																	// �X�V
	void Draw(void);																	// �`��
	void DrawShadow(void);																// �e�̕`��

	void SetPartsTexInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 pTexture);		// �p�[�c�̏��ݒ�
	void SetPartsInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// �p�[�c�̏��ݒ�
	void SetMotionRotDest(CMotion::MOTION_TYPE motiontype, int nKey);					// ���[�V�����̖ړI�̉�]�̐ݒ�

	void SetMtxParent(D3DXMATRIX *pMtxParent)	{ m_mtxParent = pMtxParent; }		// �e�̃}�g���b�N�X�̐ݒ�
	void BindModelInfo(MODELINFO *pModelInfo)	{ m_pModelInfo = pModelInfo; }	// ���f�����̐ݒ�

	int GetParent(void)			{ return m_nParent; }							// �e�ԍ��擾
	D3DXMATRIX *GetMtx(void)	{ return &m_mtxWorld; }							// ���[���h�}�g���b�N�X�̎擾

	void ShowModelPartsInfo(void);														// ImGui�̍X�V

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	// ���f���̃e�N�X�`��

	D3DXVECTOR3	m_pos;				// ���W
	D3DXVECTOR3	m_rot;				// ��]
	D3DXVECTOR3	m_rot1F;			// ��]�̍���
	D3DXMATRIX	m_mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXMATRIX	*m_mtxParent;		// �e�̃}�g���b�N�X
	MODELINFO	*m_pModelInfo;		// ���f�����
	int m_nIndex;					// ������ID
	int m_nParent;					// �e�̔ԍ�
};
#endif