//*************************************************************************************************************
//
// �ǂ̏���[wall.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "wall.h"
#include "renderer.h"
#include "manager.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define WALL_FILENAME	"data/TEXT/wall/WallInfo.txt"	// �t�@�C����
#define WALL_OPENMODE	"r"								// �J�����[�h


//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CWall::m_pAllTexture[WALLTEX::WALLTEX_MAX] = {};					// �S�Ẵe�N�X�`�����
D3DXVECTOR2        CWall::m_Length                            = MYLIB_VEC2_UNSET;	// ���S����̋���
D3DXVECTOR3        CWall::m_CenterPos                         = MYLIB_VEC3_UNSET;	// ���S�ʒu
float              CWall::m_fHeight                           = MYLIB_FLOAT_UNSET;	// ����

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
HRESULT CWall::Load(void)
{
	// �ϐ��錾
	FILE* pFile;
	char aRead[MYLIB_STRINGSIZE];		// �ǂݍ��ݗp
	char aComp[MYLIB_STRINGSIZE];		// ��r�p
	char aEmpty[MYLIB_STRINGSIZE];		// �v��Ȃ����̗p
	char aFileName[MYLIB_STRINGSIZE];	// �t�@�C����
	int  nCntFileName;					// �t�@�C�����J�E���g
	D3DXVECTOR3 CenterPos;				// ���S�ʒu
	D3DXVECTOR2 Length;					// ���S����̋���
	float       fHeight;				// ����
	LPDIRECT3DDEVICE9 pDevice;			// �f�o�C�X�̃|�C���^

	// ������
	aRead[0] = MYLIB_CHAR_UNSET;
	aComp[0] = MYLIB_CHAR_UNSET;
	aEmpty[0] = MYLIB_CHAR_UNSET;
	aFileName[0] = MYLIB_CHAR_UNSET;
	nCntFileName = MYLIB_INT_UNSET;
	fHeight = MYLIB_FLOAT_UNSET;
	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �t�@�C�����J��
	pFile = fopen(WALL_FILENAME, WALL_OPENMODE);

	// �J���Ȃ�������
	if (pFile == NULL)
	{
		return E_FAIL;
	}

#ifdef _DEBUG
	int  nCntError;						// �G���[�J�E���g
	nCntError = MYLIB_INT_UNSET;		// �G���[�J�E���g�̏�����
#endif
	// �X�N���v�g������܂łƂ΂�
	while (strcmp(aComp, "SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(aRead, sizeof(aRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(aRead, "%[^,]s", &aComp);
#ifdef _DEBUG
		// �G���[�J�E���g���C���N�������g
		if (++nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			fclose(pFile);
			return E_FAIL;
		}
#endif
	}
	// END_SCRIPT�܂Ń��[�v
	while (strcmp(aComp, "END_SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(aRead, sizeof(aRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(aRead, "%[^,]s", &aComp);
#ifdef _DEBUG
		// �G���[�J�E���g���C���N�������g
		if (++nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			fclose(pFile);
			return E_FAIL;
		}
#endif
		// �t�@�C��������e�N�X�`����ǂݍ���
		if (sscanf(aRead, "FILENAME = %s", &aFileName) == 1)
		{
			// �e�N�X�`���̓ǂݍ���
			if (D3DXCreateTextureFromFile(pDevice, &aFileName[0], &m_pAllTexture[nCntFileName]) != D3D_OK)
			{// ���s

			}
			else
			{// ����

			}
			// �t�@�C�������C���N�������g
			nCntFileName++;
		}
		// ���S�ʒu�̓ǂݍ���
		else if (sscanf(aRead, "CENTER = %f %f %f", &CenterPos.x, &CenterPos.y, &CenterPos.z) == 3)
		{
			CWall::m_CenterPos = CenterPos;
		}
		// ���S����̋����̓ǂݍ���
		else if (sscanf(aRead, "LENGTH = %f %f", &Length.x, &Length.y) == 2)
		{
			CWall::m_Length = Length;
		}
		// �����̓ǂݍ���
		else if (sscanf(aRead, "HEIGHT = %f,", &fHeight) == 2)
		{
			CWall::m_fHeight = fHeight;
		}
	}

	// �t�@�C�������
	fclose(pFile);
	return S_OK;
}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void CWall::Unload(void)
{
	// �e�N�X�`�����̊J��
	for (int nCntTexture = 0; nCntTexture < WALLTEX::WALLTEX_MAX; nCntTexture++)
	{
		if (m_pAllTexture[nCntTexture] != NULL)
		{
			m_pAllTexture[nCntTexture]->Release();
			m_pAllTexture[nCntTexture] = NULL;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
CWall * CWall::Create(WALLTEX enmWallTex)
{
	// �ǃN���X�̐���
	CWall *pWall = new CWall;
	// ���s������
	if (pWall == NULL)
	{
		return NULL;
	}
	// ������
	pWall->Init();
	// �e�N�X�`���̘A��
	pWall->BindTexType(enmWallTex);
	return pWall;
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void CWall::Init(void)
{
	// �ʒu�̐ݒ�
	m_SingleInfo[SETINGPOS_POSIX].trans.pos = D3DXVECTOR3(m_CenterPos.x + m_Length.x, m_CenterPos.y, m_CenterPos.z);	// +X�̈ʒu
	m_SingleInfo[SETINGPOS_NEGX].trans.pos  = D3DXVECTOR3(m_CenterPos.x - m_Length.x, m_CenterPos.y, m_CenterPos.z);	// -X�̈ʒu
	m_SingleInfo[SETINGPOS_POSIZ].trans.pos = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z+ m_Length.y);		// +Z�̈ʒu
	m_SingleInfo[SETINGPOS_NEGZ].trans.pos  = D3DXVECTOR3(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z + m_Length.y);	// -Z�̒n��

	// �傫���̐ݒ�
	m_SingleInfo[SETINGPOS_POSIX].size = D3DXVECTOR3(0.0f, m_fHeight, m_Length.y);
	m_SingleInfo[SETINGPOS_NEGX].size = D3DXVECTOR3(0.0f, m_fHeight, m_Length.y);
	m_SingleInfo[SETINGPOS_POSIZ].size = D3DXVECTOR3(0.0f, m_fHeight, m_Length.x);
	m_SingleInfo[SETINGPOS_NEGZ].size = D3DXVECTOR3(0.0f, m_fHeight, m_Length.x);

	// �@���x�N�g���̐ݒ�
	m_SingleInfo[SETINGPOS_POSIX].size = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_SingleInfo[SETINGPOS_NEGX].size = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_SingleInfo[SETINGPOS_POSIZ].size = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_SingleInfo[SETINGPOS_NEGZ].size = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// ��]�̐ݒ�
	m_SingleInfo[SETINGPOS_POSIX].trans.rot = MYLIB_VEC3_UNSET;
	m_SingleInfo[SETINGPOS_NEGX].trans.rot = MYLIB_VEC3_UNSET;
	m_SingleInfo[SETINGPOS_POSIZ].trans.rot = MYLIB_VEC3_UNSET;
	m_SingleInfo[SETINGPOS_NEGZ].trans.rot = MYLIB_VEC3_UNSET;

	// ���_���̍쐬
	MakeVertex();
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CWall::Uninit(void)
{
	if (m_pVtexBuff != NULL)
	{
		m_pVtexBuff->Unlock();
		m_pVtexBuff->Release();
		m_pVtexBuff = NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CWall::Update(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CWall::Draw(void)
{
		// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice;	// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	SINGLEINFO *pSingleInfo;		// �G�t�F�N�g�̃|�C���^

	pDevice = CManager::GetRenderer()->GetDevice();		// �f�o�C�X�̎擾
	pSingleInfo = &m_SingleInfo[0];						// �|�C���^�̏�����

	// ���C�e�B���O���[�h����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �J�����O���Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pSingleInfo[nCntWall].trans.mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(
			&mtxRot,
			pSingleInfo[nCntWall].trans.rot.y,
			pSingleInfo[nCntWall].trans.rot.x,
			pSingleInfo[nCntWall].trans.rot.z);
		// �������킹��
		D3DXMatrixMultiply(
			&pSingleInfo[nCntWall].trans.mtxWorld,
			&pSingleInfo[nCntWall].trans.mtxWorld,
			&mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(
			&mtxTrans,
			pSingleInfo[nCntWall].trans.pos.x,
			pSingleInfo[nCntWall].trans.pos.y,
			pSingleInfo[nCntWall].trans.pos.z);
		// �������킹��
		D3DXMatrixMultiply(
			&pSingleInfo[nCntWall].trans.mtxWorld,
			&pSingleInfo[nCntWall].trans.mtxWorld,
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pSingleInfo[nCntWall].trans.mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, m_pVtexBuff, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}

	// ���C�e�B���O���[�h�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// ����(�����)���J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//-------------------------------------------------------------------------------------------------------------
// �e�N�X�`�����̘A��
//-------------------------------------------------------------------------------------------------------------
void CWall::BindTexType(WALLTEX enmTexType)
{
	// �|�C���^����
	this->m_pTexture = CWall::m_pAllTexture[enmTexType];
}

//-------------------------------------------------------------------------------------------------------------
// ���_���̍쐬
//-------------------------------------------------------------------------------------------------------------
HRESULT CWall::MakeVertex(void)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;			// ���_���̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * WALL_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtexBuff,
		NULL)))
	{
		return E_FAIL;
	}

	// �P�̏��̃|�C���^
	SINGLEINFO *pSingleInfo = &m_SingleInfo[0];

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtexBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < WALL_MAX; nCntWall++, pSingleInfo++)
	{
		// ���_�ʒu
		pVtx[0].pos = D3DXVECTOR3(pSingleInfo->trans.pos.x - pSingleInfo->size.x, pSingleInfo->trans.pos.y - pSingleInfo->size.y, pSingleInfo->trans.pos.z - pSingleInfo->size.z);
		pVtx[1].pos = D3DXVECTOR3(pSingleInfo->trans.pos.x + pSingleInfo->size.x, pSingleInfo->trans.pos.y - pSingleInfo->size.y, pSingleInfo->trans.pos.z + pSingleInfo->size.z);
		pVtx[2].pos = D3DXVECTOR3(pSingleInfo->trans.pos.x - pSingleInfo->size.x, pSingleInfo->trans.pos.y + pSingleInfo->size.y, pSingleInfo->trans.pos.z - pSingleInfo->size.z);
		pVtx[3].pos = D3DXVECTOR3(pSingleInfo->trans.pos.x + pSingleInfo->size.x, pSingleInfo->trans.pos.y + pSingleInfo->size.y, pSingleInfo->trans.pos.z + pSingleInfo->size.z);
		// �@���x�N�g��
		pVtx[0].nor = pSingleInfo->nor;
		pVtx[1].nor = pSingleInfo->nor;
		pVtx[2].nor = pSingleInfo->nor;
		pVtx[3].nor = pSingleInfo->nor;
		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// texture���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		// ���_�|�C���^�̍X�V
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N����
	m_pVtexBuff->Unlock();

	return S_OK;

}
