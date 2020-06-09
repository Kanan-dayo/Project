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
class CModelParts : public CSceneX
{
public:
	CModelParts(CSceneX::PRIORITY nPriority);
	virtual ~CModelParts();

	void Init(void);																	// ������
	void Uninit(void);																	// �I��
	void Update(void);																	// �X�V
	void Draw(void);																	// �`��

	void SetParentMtx(D3DXMATRIX *mtx);													// �}�g���b�N�X�ݒ�
	void SetPartsTexInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPDIRECT3DTEXTURE9 pTexture);		// �p�[�c�̏��ݒ�
	void SetPartsInfo(int nIndex, int nParent, D3DXVECTOR3 pos, D3DXVECTOR3 rot);		// �p�[�c�̏��ݒ�
	void SetMotionRotDest(CMotion::MOTION_TYPE motiontype, int nKey);					// ���[�V�����̖ړI�̉�]�̐ݒ�

	int GetParent(void)				{ return m_nParent; }								// �e�ԍ��擾
	D3DXMATRIX *GetMtxParts(void)	{ return m_pParentMtx; }							// �}�g���b�N�X�̎擾

	void ShowModelPartsInfo(void);														// ImGui�̍X�V

	CModelParts();

private:
	D3DXVECTOR3	m_rot1F;																// ��]�̍���
	int m_nIndex;																		// ������ID
	int m_nParent;																		// �e�̔ԍ�
	D3DXMATRIX *m_pParentMtx;															// �e�̃}�g���b�N�X
};
#endif