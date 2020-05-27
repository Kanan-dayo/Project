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
#include <memory>	// �X�}�[�g�|�C���^�g�p�ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �N���X��`
//=============================================================================
class CObject : public CSceneX
{
public:
	typedef struct MODEL_VTX
	{	// ���f���̍ő�E�ŏ����_���W
		D3DXVECTOR3 VtxMax;	// ���_�̍ő�l
		D3DXVECTOR3 VtxMin;	// ���_�̍ŏ��l
		MODEL_VTX() {};		// �R���X�g���N�^
		MODEL_VTX(const D3DXVECTOR3 Max, const D3DXVECTOR3 Min)
		{
			VtxMax = Max;
			VtxMin = Min;
		}
	} MODEL_VTX;

	typedef struct
	{	// ���f�����̏��
		char			cModelName[128];	// ���f���̃t�@�C����
		LPD3DXMESH		mesh;				// ���b�V��
		LPD3DXBUFFER	matBuff;			// ���_���
		DWORD			matNum;				// �}�e���A����
		MODEL_VTX		modelVtx;			// ���f���̍ő�E�ŏ����_���W
	} MODELINFO;

	CObject(PRIORITY type);		// �R���X�g���N�^
	~CObject();					// �f�X�g���N�^

	void Init(void);			// ������
	void Uninit(void);			// �I��
	void Update(void);			// �X�V
	void Draw(void);			// �`��

	static std::unique_ptr<CObject> Create(void);	// ����

	void SetObjInfo(D3DXVECTOR3 pos,
		D3DXVECTOR3 rot);			// �p�[�c�̏��ݒ�

	//bool CollObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax);

	bool GetRelease(void) { return m_bRelease; }	// �����[�X���邩�ǂ���

#ifdef _DEBUG
	//void ShowObjectInfo(char cPrintText[16]);
#endif

private:
	bool		m_bRelease;		// �����[�X���邩�ǂ���
	MODELINFO	m_modelInfo;	// ���f�����
};

#endif