//==================================================================================================================
//
// ���b�V���t�B�[���h����[meshField.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "renderer.h"
#include "meshField.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "player.h"
#include "tutorial.h"
#include "game.h"
#include "title.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MASS_WIDTH 100										// ���̃}�X
#define MASS_DEPTH 100										// �c�̃}�X
#define FIELD_ALPHA 0.1f									// ���b�V���t�B�[���h�A���t�@

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;			// �e�N�X�`���ϐ�
CMeshField *CMeshField::m_pMeshField = NULL;				// ���b�V���t�B�[���h�̏��
CPlayer *CMeshField::m_pPlayer = NULL;						// �v���C���[�̏��

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CMeshField::CMeshField(PRIORITY type = CScene::PRIORITY_FIELD) : CScene(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CMeshField::~CMeshField()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CMeshField::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();		// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// �f�o�C�X�̎擾

	m_nDepth = MASS_DEPTH;												// �c�̃u���b�N��
	m_nWidth = MASS_WIDTH;												// ���̃u���b�N��

	// �ʒu�E��]�̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// ��]
	m_nNumVertex = ((m_nWidth + 1) * m_nDepth * 2) + (m_nDepth - 1) * 2;// �����_��
	m_nNumIndex = (m_nDepth + 1) * (m_nWidth + 1);						// ���C���f�b�N�X��
	m_nNumPolygon = m_nNumVertex - 2;									// �O�p�`�̐�
	m_aVecA[m_nDepth * m_nWidth] = {};									// �@���x�N�g����ʂ̐����ꎞ�I�Ɋi�[
	m_aVecB[m_nDepth * m_nWidth] = {};									// �@���x�N�g����ʂ̐����ꎞ�I�Ɋi�[
	m_vectorA = D3DXVECTOR3(0, 0, 0);									// ��ڂ̊O�ϗp�ϐ�
	m_vectorB = D3DXVECTOR3(0, 0, 0);									// ��ڂ̊O�ϗp�ϐ�
	m_vectorC = D3DXVECTOR3(0, 0, 0);									// �O�ڂ̊O�ϗp�ϐ�
	m_nNumber = 0;														// �z��̔ԍ�
	m_nStartBox = m_nWidth + 1;											// �n�܂锠
	m_nEndBox = 0;														// ������锠
	fDivide = 0;														// sin�̒��g������ϐ�

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// ���_���W�̐ݒ�
			m_pVtx[0].pos.x = (-WhileX * m_nWidth) / 2 + WhileX * nWide;
			m_pVtx[0].pos.y = 0.0f;
			m_pVtx[0].pos.z = (WhileZ / 2 * m_nDepth) - WhileZ * nDepth;

			// ���_�J���[
			m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, FIELD_ALPHA);

			// �e�N�X�`���`�ʂ̈ʒu
			m_pVtx[0].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

			// ���_�ԍ����Z
			m_pVtx++;
		}
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//////////////////////////////�@���x�N�g��//////////////////////////////
	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// �C���f�b�N�X�ԍ�
			int nIdx = nDepth * (m_nWidth + 1) + nWide;

			// �[�͌v�Z�����Ȃ�
			if (nWide != m_nWidth && nDepth != m_nDepth)
			{
				m_vectorA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;								// ��ڂ̃x�N�g��
				m_vectorB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;							// ��ڂ̃x�N�g��
				m_vectorC = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;								// �O�ڂ̃x�N�g��
				D3DXVec3Cross(&m_aVecA[m_nNumber], &m_vectorA, &m_vectorB);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecA[m_nNumber], &m_aVecA[m_nNumber]);								// ���K������
				D3DXVec3Cross(&m_aVecB[m_nNumber], &m_vectorB, &m_vectorC);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecB[m_nNumber], &m_aVecB[m_nNumber]);								// ���K������

				// �z��̔ԍ�1�v���X����
				m_nStartBox++;
				m_nEndBox++;
				m_nNumber++;
			}

			// �E�ゾ�����Ƃ�
			if (nIdx == m_nWidth)
			{
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecB[m_nWidth - 1];
			}
			else if (nIdx == m_nDepth * (m_nWidth + 1))
			{// �����������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecA[(m_nDepth - 1) * m_nWidth];
			}
			else if (nIdx == 0)
			{// ���ゾ�����Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[nIdx] + m_aVecB[nIdx]) / 2;
			}
			else if (nIdx == (m_nDepth + 1) * (m_nWidth + 1) - 1)
			{// �E���������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[m_nDepth * m_nWidth - 1] + m_aVecB[m_nDepth * m_nWidth - 1]) / 2;
			}
			else if (nWide != 0 && nWide != m_nWidth)
			{// ���̗񂪒[����Ȃ��Ƃ�
				// �c�����ڂ������Ƃ�
				if (nDepth == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[nWide - 1] + m_aVecA[nWide] + m_aVecB[nWide]) / 3;
				}
				else if (nDepth == m_nDepth)
				{// �c���Ō���������Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[(m_nDepth - 1) * m_nWidth - 1 + nWide] +
						m_aVecA[(m_nDepth - 1) * m_nWidth + nWide] +
						m_aVecB[(m_nDepth - 1) * m_nWidth + nWide]) / 3;
				}
				else
				{// ����ȊO
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1]) / 6;
				}
			}
			else if (nDepth != 0 && nDepth != m_nDepth)
			{// �c�̗񂪒[����Ȃ��Ƃ�
				// �擪�̂Ƃ�
				if (nWide == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nDepth - 1) * m_nWidth] +
						m_aVecB[m_nWidth + (nDepth - 1) * m_nWidth] +
						m_aVecA[m_nWidth + (nDepth - 1) * m_nWidth]) / 3;
				}
				else if (nWide == m_nWidth)
				{// �Ō���̂Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[m_nWidth - 1 + m_nWidth * (nDepth - 1)] +
						m_aVecA[m_nWidth - 1 + m_nWidth * (nDepth - 1)] +
						m_aVecB[m_nWidth - 1 + m_nWidth * nDepth]) / 3;
				}
			}
		}
		// �z��̔ԍ�1�v���X����
		m_nStartBox++;
		m_nEndBox++;
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	WORD *pIdx;				// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �c���J�E���g
	for (int nCntY = 0; nCntY < m_nDepth; nCntY++)
	{
		// ��s�ڂ���Ȃ��Ƃ�
		if (nCntY != 0)
		{
			pIdx[0] = (m_nWidth + 1) + nCntY * (m_nWidth + 1);
			pIdx++;
		}

		// �����J�E���g
		for (int nCntX = 0; nCntX < m_nWidth + 1; nCntX++)
		{
			pIdx[0] = (m_nWidth + 1) + nCntX + nCntY * (m_nWidth + 1);
			pIdx[1] = nCntX + nCntY * (m_nWidth + 1);
			pIdx += 2;
		}

		// �k�ރ|���S��
		if (nCntY + 1 < m_nDepth)
		{
			pIdx[0] = m_nWidth + nCntY * (m_nWidth + 1);
			pIdx++;
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@��NULL����Ȃ��Ƃ�
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();				// ���_�o�b�t�@�̊J��
		m_pVtxBuff = NULL;					// NULL�ɂ���
	}

	// �C���f�b�N�X�o�b�t�@��NULL����Ȃ��Ƃ�
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();				// �C���f�b�N�X�o�b�t�@�̊J��
		m_pIdxBuff = NULL;					// NULL�ɂ���
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CMeshField::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	VERTEX_3D *m_pVtx;									// ���_���

	// �ď�����
	m_nNumber = 0;										// �z��̔ԍ�
	m_nStartBox = m_nWidth + 1;							// �n�܂锠
	m_nEndBox = 0;										// ������锠

	// ������
	fDivide -= 0.05f;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// ���_���W�̐ݒ�
			m_pVtx[0].pos.x = (-WhileX * m_nWidth) / 2 + WhileX * nWide;
			m_pVtx[0].pos.y = 0.0f;
			m_pVtx[0].pos.z = (WhileZ / 2 * m_nDepth) - WhileZ * nDepth;

			// ���_�J���[
			m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, FIELD_ALPHA);

			// ���_�����Z
			m_pVtx++;
		}
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//////////////////////////////�@���x�N�g��//////////////////////////////
	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// �C���f�b�N�X�ԍ�
			int nIdx = nDepth * (m_nWidth + 1) + nWide;

			// �[�͌v�Z�����Ȃ�
			if (nWide != m_nWidth && nDepth != m_nDepth)
			{
				m_vectorA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;								// ��ڂ̃x�N�g��
				m_vectorB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;							// ��ڂ̃x�N�g��
				m_vectorC = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;								// �O�ڂ̃x�N�g��
				D3DXVec3Cross(&m_aVecA[m_nNumber], &m_vectorA, &m_vectorB);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecA[m_nNumber], &m_aVecA[m_nNumber]);								// ���K������
				D3DXVec3Cross(&m_aVecB[m_nNumber], &m_vectorB, &m_vectorC);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecB[m_nNumber], &m_aVecB[m_nNumber]);								// ���K������

				// �z��̔ԍ�1�v���X����
				m_nStartBox++;
				m_nEndBox++;
				m_nNumber++;
			}

			// �E�ゾ�����Ƃ�
			if (nIdx == m_nWidth)
			{
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecB[m_nWidth - 1];
			}
			else if (nIdx == m_nDepth * (m_nWidth + 1))
			{// �����������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecA[(m_nDepth - 1) * m_nWidth];
			}
			else if (nIdx == 0)
			{// ���ゾ�����Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[nIdx] + m_aVecB[nIdx]) / 2;
			}
			else if (nIdx == (m_nDepth + 1) * (m_nWidth + 1) - 1)
			{// �E���������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[m_nDepth * m_nWidth - 1] + m_aVecB[m_nDepth * m_nWidth - 1]) / 2;
			}
			else if (nWide != 0 && nWide != m_nWidth)
			{// ���̗񂪒[����Ȃ��Ƃ�
				// �c�����ڂ������Ƃ�
				if (nDepth == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[nWide - 1] + m_aVecA[nWide] + m_aVecB[nWide]) / 3;
				}
				else if (nDepth == m_nDepth)
				{// �c���Ō���������Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[(m_nDepth - 1) * m_nWidth - 1 + nWide] +
						m_aVecA[(m_nDepth - 1) * m_nWidth + nWide] +
						m_aVecB[(m_nDepth - 1) * m_nWidth + nWide]) / 3;
				}
				else
				{// ����ȊO
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1]) / 6;
				}
			}
			else if (nDepth != 0 && nDepth != m_nDepth)
			{// �c�̗񂪒[����Ȃ��Ƃ�
				 // �擪�̂Ƃ�
				if (nWide == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nDepth - 1) * m_nWidth] +
						m_aVecA[m_nWidth + (nDepth - 1) * m_nWidth] +
						m_aVecB[m_nWidth + (nDepth - 1) * m_nWidth]) / 3;
				}
				else if (nWide == m_nWidth)
				{// �Ō���̂Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[(m_nWidth - 1) + m_nWidth * nDepth] +
						m_aVecA[(m_nWidth - 1) + m_nWidth * nDepth] +
						m_aVecB[m_nWidth - 1 + m_nWidth * nDepth]) / 3;
				}
			}
		}
		// �z��̔ԍ���1�v���X����
		m_nStartBox++;
		m_nEndBox++;
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CMeshField::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;							// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CMeshField::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// �|���S������
//==================================================================================================================
CMeshField *CMeshField::Create(void)
{
	// �������𓮓I�Ɋm��
	m_pMeshField = new CMeshField(CScene::PRIORITY_FIELD);

	// ���b�V����������Ƃ�
	if (m_pMeshField != NULL)
	{
		// �V�[��������
		m_pMeshField->Init();
	}

	// �l��Ԃ�
	return m_pMeshField;
}

//==================================================================================================================
// �e�N�X�`����񃍁[�h
//==================================================================================================================
HRESULT CMeshField::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();						// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();					// �f�o�C�X���擾����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		FIELD_TEXTUE,							// �t�@�C���̖��O
		&m_pTexture);							// �ǂݍ��ރ������[

	// �l��Ԃ�
	return S_OK;
}

//==================================================================================================================
// �e�N�X�`�����j��
//==================================================================================================================
void CMeshField::Unload(void)
{
	// �e�N�X�`����񂪂���Ƃ�
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();			// �e�N�X�`�����̊J��
		m_pTexture = NULL;				// NULL�ɂ���
	}
}

//==================================================================================================================
// ���b�V���t�B�[���h���擾
//==================================================================================================================
CMeshField * CMeshField::GetMeshField(void)
{
	return m_pMeshField;
}

//==================================================================================================================
// �ʒu�擾
//==================================================================================================================
D3DXVECTOR3 CMeshField::GetPos(void)
{
	return m_pos;
}

//==================================================================================================================
// �ړ��ʎ擾
//==================================================================================================================
D3DXVECTOR3 CMeshField::GetMove(void)
{
	return m_move;
}

//==================================================================================================================
// �ړ��ʐݒ�
//==================================================================================================================
void CMeshField::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}