//=============================================================================
//
// �I�u�W�F�N�g���� [ object.h ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "sceneX.h"
#include "kananlibrary.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================

class CObject : public CSceneX
{
public:
	CObject(CSceneX::PRIORITY nPriority);
	~CObject();

	void Init(void);								// ������
	void Uninit(void);								// �I��
	void Update(void);								// �X�V
	void Draw(void);								// �`��

	static CObject *Create(void);

	void SetObjInfo(const D3DXVECTOR3 & pos,
		const D3DXVECTOR3 & rot,
		const LPDIRECT3DTEXTURE9 & pTexture,
		const int & type,
		const bool & bCollision);						// �I�u�W�F�N�g�̏��ݒ�

	bool CollObject(D3DXVECTOR3 *pos,
		const D3DXVECTOR3 & posOld,
		D3DXVECTOR3 *move,
		const MODEL_VTX & modelVtx);

	bool GetRelease(void)	{ return m_bRelease; }		// �����[�X���邩�ǂ���
	bool GetbColl(void)		{ return m_bCollision; }	// �����蔻����s����
	int	 GetType(void)		{ return m_nType; }			// �^�C�v�擾

#ifdef _DEBUG
	void ShowObjectInfo(char cPrintText[16]);
#endif

private:
	int		m_nType;		// �I�u�W�F�N�g�^�C�v
	bool	m_bRelease;		// �����[�X���邩�ǂ���
	bool	m_bCollision;	// �����蔻�菈�����s����
};

#endif