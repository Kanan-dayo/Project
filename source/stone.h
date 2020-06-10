//*************************************************************************************************************
//
// �X�g�[������[stone.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
#ifndef _STONE_H_
#define _STONE_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "sceneX.h"
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#ifndef CSTONE_USE_TEXTURE
//#define CSTONE_USE_TEXTURE	// �e�N�X�`�����g��
#endif // !CSTONE_USE_TEXTURE

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CStone : public CSceneX
{
public:
	typedef enum
	{
		STONE_ID_NONE = -1,
		STONE_ID_DEFAULT,
		STONE_ID_MAX
	} STONE_ID;

	// ���f�����
	typedef struct
	{
		LPD3DXMESH			pMesh;			// ���b�V�����̃|�C���^
		LPD3DXBUFFER		pBuffMat;		// �}�e���A�����̃|�C���^
		DWORD				nNumMat;		// �}�e���A���̐�
		D3DXVECTOR3			vtxMax;			// �ő咸�_
		D3DXVECTOR3			vtxMin;			// �ŏ����_
		float				*pAlphaValue;	// �A���t�@�l�̃|�C���^
#ifdef CSTONE_USE_TEXTURE
		int					*pTextureID;	// �e�N�X�`��ID
		LPDIRECT3DTEXTURE9	*ppTexture;		// �e�N�X�`�����
		int					nNumTexture;	// �e�N�X�`����
#endif
	} MODEL_INFO;

	// �R���X�g���N�^
	CStone();
	// ��������R���X�g���N�^
	CStone(PRIORITY type);
	// �f�X�g���N�^
	~CStone() {};
	// �ǂݍ���(�}�l�[�W���[�̏������ɓ����)
	static HRESULT Load(void);
	// �J��(�}�l�[�W���[�̏I�������ɓ����)
	static void Unload(void);
	// �����̒��B
	static CString *GetResource(void);

	// ����
	static CStone* Create(
		CONST STONE_ID     eumID = STONE_ID_NONE,
		CONST D3DXVECTOR3  &pos = MYLIB_3DVECTOR_ZERO
	);

	// ������
	void Init(void);
	// �I��
	void Uninit(void);
	// �X�V
	void Update(void);
	// �`��
	void Draw(void);

private:
	/* �����o�֐� */
	// �ő�ŏ��̒��_�ʒu�̎擾
	static void GetMaxMinVertices(int nIndex);
#ifdef CSTONE_USE_TEXTURE
	// X�t�@�C������擾�����e�N�X�`������ID�̎擾����
	static void CreateTexturefrom_Xfile(const int nIndex, CONST STRING sFileName);
#endif
	/* �����o�ϐ��@*/
	static MODEL_INFO* m_pAllStoneTypeInfo;		// �X�g�[���̑S�Ẵ��f�����
	static int         m_nNumTypeAll;			// �X�g�[���̎�ސ�
	STONE_ID           m_enmStoneID;			// �X�g�[��ID
	int                m_fCntShake;				// ����J�E���g
	MODELINFO          m_pModelInfo;			// ���f�����Q�Ƃ��邽�߂̏��
};




#endif