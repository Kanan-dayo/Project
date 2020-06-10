//*************************************************************************************************************
//
// �X�g�[������[stone.cpp]
// Author : Sekine Ikuto
//
//*************************************************************************************************************

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "stone.h"
#include "manager.h"
#include "renderer.h"
#include "debugProc.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define CSTONE_INITVTXVALUE_MAX		1000000.0f
#define CSTONE_INITVTXVALUE_MIN		-1000000.0f

#define CSTONE_SHAKE_SIZE			0.1f			// ���̑傫��
#define CSTONE_SHAKECOEFF			0.02f			// ����W��
#define CSTONE_ROTSPEED				0.02f			// ��]���x

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
CStone::MODEL_INFO* CStone::m_pAllStoneTypeInfo = NULL;				// �X�g�[���̑S�Ẵ��f�����
int                 CStone::m_nNumTypeAll       = MYLIB_INT_UNSET;	// �X�g�[���̎�ސ�

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CStone::CStone()
{
}

//-------------------------------------------------------------------------------------------------------------
// ��������R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CStone::CStone(PRIORITY type) : CSceneX(type)
{
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
HRESULT CStone::Load(void)
{
	// �ϐ��錾
	CString* pFileName;			// �t�@�C����
	pFileName = CStone::GetResource();
	// �擾�Ɏ��s������
	if (pFileName == NULL)
	{
		return E_FAIL;
	}
	// �X�g�[���̑S�Ẵ��f�����̐���
	if (m_pAllStoneTypeInfo == NULL)
	{
		m_pAllStoneTypeInfo = new MODEL_INFO[m_nNumTypeAll];
	}

	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̎擾
	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �X�g�[���̎�ސ����[�v
	for (int nCntModelType = 0; nCntModelType < m_nNumTypeAll; nCntModelType++)
	{
#ifdef CSTONE_USE_TEXTURE
		// �e�N�X�`�����̏�����
		m_pAllStoneTypeInfo[nCntModelType].pTextureID = NULL;
		m_pAllStoneTypeInfo[nCntModelType].ppTexture = NULL;
		m_pAllStoneTypeInfo[nCntModelType].nNumTexture = MYLIB_INT_UNSET;
#endif
		// X�t�@�C���̓ǂݍ���
		if (FAILED(D3DXLoadMeshFromX(pFileName[nCntModelType].Get(),
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pAllStoneTypeInfo[nCntModelType].pBuffMat,
			NULL,
			&m_pAllStoneTypeInfo[nCntModelType].nNumMat,
			&m_pAllStoneTypeInfo[nCntModelType].pMesh)))
		{
			return E_FAIL;
		}
		// �ő�ŏ��̒��_�ʒu�̎擾
		GetMaxMinVertices(nCntModelType);
#ifdef CSTONE_USE_TEXTURE
		// X�t�@�C������擾�����e�N�X�`���𐶐�
		CreateTexturefrom_Xfile(nCntModelType, pFileName[nCntModelType].Get());
#endif
	}

	// ������̊J��
	for (int nCntFileName = 0; nCntFileName < m_nNumTypeAll; nCntFileName++)
	{
		pFileName[nCntFileName].release();
	}
	// �t�@�C�����̊J��
	delete[] pFileName;
	pFileName = NULL;

	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void CStone::Unload(void)
{
	if (m_pAllStoneTypeInfo != NULL)
	{
		// �X�g�[���̎�ސ����[�v
		for (int nCntModelType = 0; nCntModelType < m_nNumTypeAll; nCntModelType++)
		{
#ifdef CSTONE_USE_TEXTURE
			// �e�N�X�`��ID���g���Ă���Ƃ�
			if (m_pAllStoneTypeInfo[nCntModelType].pTextureID != NULL)
			{// �e�N�X�`��ID�̔j��
				delete[] m_pAllStoneTypeInfo[nCntModelType].pTextureID;
				m_pAllStoneTypeInfo[nCntModelType].pTextureID = NULL;
			}
			// �e�N�X�`�����g���Ă�����
			if (m_pAllStoneTypeInfo[nCntModelType].ppTexture != NULL)
			{
				// �e�N�X�`���̊J��
				for (int nCntTex = 0; nCntTex < m_pAllStoneTypeInfo[nCntModelType].nNumTexture; nCntTex++)
				{
					m_pAllStoneTypeInfo[nCntModelType].ppTexture[nCntTex]->Release();
					m_pAllStoneTypeInfo[nCntModelType].ppTexture[nCntTex] = NULL;
				}
			}
#endif
			// �}�e���A�����g���Ă���Ƃ�
			if (m_pAllStoneTypeInfo[nCntModelType].pBuffMat != NULL)
			{// �}�e���A���̔j��
				m_pAllStoneTypeInfo[nCntModelType].pBuffMat->Release();
				m_pAllStoneTypeInfo[nCntModelType].pBuffMat = NULL;
			}
			// ���b�V�����g���Ă���Ƃ�
			if (m_pAllStoneTypeInfo[nCntModelType].pMesh != NULL)
			{// ���b�V���̔j��
				m_pAllStoneTypeInfo[nCntModelType].pMesh->Release();
				m_pAllStoneTypeInfo[nCntModelType].pMesh = NULL;
			}

		}
		// �S��̃��f�����̔j��
		delete[m_nNumTypeAll] m_pAllStoneTypeInfo;
		m_pAllStoneTypeInfo = NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �����̒��B
//-------------------------------------------------------------------------------------------------------------
CString * CStone::GetResource(void)
{
	// �ϐ��錾
	const STRING sOpenFileName = "data/TEXT/StoneInfo/StoneTypeFileName.txt";
	// �t�@�C�����J��
	FILE *pFile;
	// ���s������
	if ((pFile = fopen(sOpenFileName, "r")) == NULL)
	{
		return NULL;
	}
	// �ϐ��錾
	CString * pFileName;		// �t�@�C����
	char cRead[MYLIB_STRINGSIZE];			// �ǂݍ��ݗp
	char cComp[MYLIB_STRINGSIZE];			// ��r�p
	char cEmpty[MYLIB_STRINGSIZE];			// �v��Ȃ����̗p
	int nCntFileName;			// �t�@�C�����J�E���g

	// �ϐ��̏�����
	pFileName = NULL;
	cRead[0] = MYLIB_CHAR_UNSET;
	cComp[0] = MYLIB_CHAR_UNSET;
	cEmpty[0] = MYLIB_CHAR_UNSET;
	nCntFileName = MYLIB_INT_UNSET;

	// SCRIPT�܂Ŕ�΂�
	while (strcmp(cComp, "SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);
	}

	// END_SCRIPT�܂Ń��[�v
	while (strcmp(cComp, "END_SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		if (strcmp(cComp, "NUMBER") == 0)
		{
			if (pFileName == NULL)
			{
				// �����񂩂���𔲂����
				sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &m_nNumTypeAll);
				// �t�@�C�����̐���
				pFileName = new CString[m_nNumTypeAll];
			}
			// ��r�p�̏�����
			cComp[0] = MYLIB_CHAR_UNSET;
		}
		else if (strcmp(cComp, "FILENAME") == 0)
		{
			if (pFileName != NULL)
			{
				// �ϐ��錾
				char aSeting[MYLIB_STRINGSIZE];
				aSeting[0] = MYLIB_CHAR_UNSET;
				// �����񂩂���𔲂����
				sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &aSeting);
				// ������̐ݒ�
				pFileName[nCntFileName].Set(aSeting);
				// �t�@�C���J�E���g���C���N�������g
				nCntFileName++;
			}
			// ��r�p�̏�����
			cComp[0] = MYLIB_CHAR_UNSET;
		}
	}
	// �t�@�C�������
	fclose(pFile);
	// �t�@�C�����|�C���^��Ԃ�
	return pFileName;
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
CStone * CStone::Create(CONST STONE_ID eumID, CONST D3DXVECTOR3 & pos)
{
	// ID���ݒ肳��Ă���
	if (eumID == STONE_ID_NONE)
	{
#if 0
		return NULL;
#else
		return nullptr;
#endif
	}
	// �ϐ��錾
	CStone* pStone;		// �X�g�[���|�C���^
	// ����
	pStone  = new CStone;
	// �������s������
	if (pStone == NULL)
	{
#if 0
		return NULL;
#else
		return nullptr;
#endif
	}
	// �ʒu�̐ݒ�
	pStone->m_pos = pos;

	// ������
	pStone->Init();
	// ���f�����̐ݒ�
	pStone->m_pModelInfo.matBuff = m_pAllStoneTypeInfo[eumID].pBuffMat;
	pStone->m_pModelInfo.matNum = m_pAllStoneTypeInfo[eumID].nNumMat;
	pStone->m_pModelInfo.mesh = m_pAllStoneTypeInfo[eumID].pMesh;
	pStone->m_pModelInfo.pTexture = NULL;
	// ���f�����̌���
	pStone->BindModel(pStone->m_pModelInfo);

	return pStone;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void CStone::Init(void)
{
	this->CSceneX::Init();
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CStone::Uninit(void)
{
	this->CSceneX::Uninit();
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CStone::Update(void)
{
	// ��]����
	this->m_rot.y += CSTONE_ROTSPEED;
	// ��]�𒼂�
	CMylibrary::SetFixTheRotation(&this->m_rot.y);
	// �����
	this->m_pos.y += sinf((m_fCntShake++) * CSTONE_SHAKECOEFF) * CSTONE_SHAKE_SIZE;

#ifdef CSTONE_DEBUG_DRAW
	CDebugProc::Print("Stone�̈ʒuY = [%.4f]\n", this->m_pos.y);
#endif // CSTONE_DEBUG_DRAW
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CStone::Draw(void)
{
	this->CSceneX::Draw();
}

//-------------------------------------------------------------------------------------------------------------
// �ő�ŏ��̒��_�ʒu�̎擾
//-------------------------------------------------------------------------------------------------------------
void CStone::GetMaxMinVertices(int nIndex)
{
	// �ϐ��錾
	int	  nNumVertices;			// ���_��
	DWORD sizeFVF;				// ���_�t�H�[�}�b�g�T�C�Y
	BYTE  *pVertexBuffer;		// ���_�o�b�t�@�̃|�C���^

	m_pAllStoneTypeInfo[nIndex].vtxMax = D3DXVECTOR3(CSTONE_INITVTXVALUE_MIN, CSTONE_INITVTXVALUE_MIN, CSTONE_INITVTXVALUE_MIN);
	m_pAllStoneTypeInfo[nIndex].vtxMin = D3DXVECTOR3(CSTONE_INITVTXVALUE_MAX, CSTONE_INITVTXVALUE_MAX, CSTONE_INITVTXVALUE_MAX);

	// ���_���擾
	nNumVertices = m_pAllStoneTypeInfo[nIndex].pMesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(m_pAllStoneTypeInfo[nIndex].pMesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	m_pAllStoneTypeInfo[nIndex].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

	// ���_�������[�v
	for (int nCntModel = 0; nCntModel < nNumVertices; nCntModel++)
	{
		// ���_�ʒu���擾����
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

		// �ŏ����傫���Ƃ��ݒ�
		Mybfunc_WhenBiggerSet(m_pAllStoneTypeInfo[nIndex].vtxMin.x, vtx.x);
		Mybfunc_WhenBiggerSet(m_pAllStoneTypeInfo[nIndex].vtxMin.y, vtx.y);
		Mybfunc_WhenBiggerSet(m_pAllStoneTypeInfo[nIndex].vtxMin.z, vtx.z);
		// �ő傪�������Ƃ��ݒ�
		Mybfunc_WhenSmallerSet(m_pAllStoneTypeInfo[nIndex].vtxMax.x, vtx.x);
		Mybfunc_WhenSmallerSet(m_pAllStoneTypeInfo[nIndex].vtxMax.y, vtx.y);
		Mybfunc_WhenSmallerSet(m_pAllStoneTypeInfo[nIndex].vtxMax.z, vtx.z);

		pVertexBuffer += sizeFVF;		// �T�C�Y���|�C���^��i�߂�
	}

	// ���_�f�[�^���A�����b�N����
	m_pAllStoneTypeInfo[nIndex].pMesh->UnlockVertexBuffer();
}

#ifdef CSTONE_USE_TEXTURE
//-------------------------------------------------------------------------------------------------------------
// X�t�@�C������擾�����e�N�X�`������ID�̎擾����
//-------------------------------------------------------------------------------------------------------------
void CStone::CreateTexturefrom_Xfile(const int nIndex, CONST STRING sFileName)
{
	// �ϐ��錾
	FILE *pFile;				// �t�@�C���̃|�C���^
	int nNumTexture;			// �e�N�X�`����
	// ������
	nNumTexture = MYLIB_INT_UNSET;
	// �t�@�C�����J��
	pFile = fopen(sFileName, "r");
	if (pFile != NULL)
	{
		// �ϐ��錾
		char cRead[MYLIB_STRINGSIZE];		// �ǂݍ��ݗp
		char cComp[MYLIB_STRINGSIZE];		// ��r�p
		char cEmpty[MYLIB_STRINGSIZE];		// �v��Ȃ����̗p
		// ������
		cRead[0] = MYLIB_CHAR_UNSET;
		cComp[0] = MYLIB_CHAR_UNSET;
		cEmpty[0] = MYLIB_CHAR_UNSET;
		do
		{	// 1�s�ǂݍ���
			fgets(cRead, sizeof(cRead), pFile);
			// �ǂݍ���Ǖ�������
			sscanf(cRead, "%s", &cComp);
		} while (strcmp(cComp, "Mesh") != 0);

		if (strcmp(cComp, "Mesh") == 0)
		{
			cComp[0] = MYLIB_CHAR_UNSET;
			do
			{		// 1�s�ǂݍ���
				fgets(cRead, sizeof(cRead), pFile);
				// �ǂݍ���Ǖ�������
				sscanf(cRead, "%s", &cComp);

				if (strcmp(cComp, "Material") == 0)
				{
					cComp[0] = MYLIB_CHAR_UNSET;
					do
					{	// 1�s�ǂݍ���
						fgets(cRead, sizeof(cRead), pFile);
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s", &cComp);
						if (strcmp(cComp, "TextureFilename") == 0)
						{
							cComp[0] = MYLIB_CHAR_UNSET;
							nNumTexture++;
						}
					} while (strcmp(cComp, "}") != 0);
					cComp[0] = MYLIB_CHAR_UNSET;
				}
			} while (strcmp(cComp, "}") != 0);
		}
	}
	// �e�N�X�`�������݂��Ȃ��������𒆒f
	if (nNumTexture == 0)
	{
		// �e�N�X�`�����̏�����
		m_pAllStoneTypeInfo[nIndex].nNumTexture = MYLIB_INT_UNSET;
		m_pAllStoneTypeInfo[nIndex].ppTexture = NULL;
		m_pAllStoneTypeInfo[nIndex].pTextureID = NULL;
		return;
	}
	// �e�N�X�`�����̐ݒ�
	m_pAllStoneTypeInfo[nIndex].nNumTexture = nNumTexture;
	// �e�N�X�`��ID�̐���
	m_pAllStoneTypeInfo[nIndex].pTextureID = new int[nNumTexture];
	// �e�N�X�`�����̐���
	m_pAllStoneTypeInfo[nIndex].ppTexture = new LPDIRECT3DTEXTURE9[nNumTexture];

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X�̎擾

	// �o�b�t�@�̐擪�|�C���^��D3DXMATERIAL�ɃL���X�g���Ď擾
	D3DXMATERIAL* materials = (D3DXMATERIAL*)m_pAllStoneTypeInfo[nIndex].pBuffMat->GetBufferPointer();

	int nCntxture = MYLIB_INT_UNSET;

	// �J�E���g�}�e���A��
	for (int nCntMat = 0; nCntMat < (int)m_pAllStoneTypeInfo[nIndex].nNumMat; nCntMat++)
	{
		if (materials[nCntMat].pTextureFilename != NULL)
		{// �t�@�C�����̎擾
			STRING sName = strstr(materials[nCntMat].pTextureFilename, "DATA");
			if (sName != NULL)
			{
				if (D3DXCreateTextureFromFile(pDevice, sName, &m_pAllStoneTypeInfo[nIndex].ppTexture[nCntxture]) != D3D_OK)
				{
					// ���s
				}
				else
				{
					// ����
				}
			}
		}
	}
}
#endif