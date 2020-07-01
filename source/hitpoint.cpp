//==================================================================================================================
//
// HP�̕`�� [hitpoint.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS

//==================================================================================================================
//	�C���N���[�h�t�@�C��
//==================================================================================================================
#include <stdio.h>
#include <stdlib.h>
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "inputKeyboard.h"
#include "hitpoint.h"
#include "bar.h"
#include "player.h"
#include "game.h"
#include "character.h"
#include "debugProc.h"

//==================================================================================================================
//	�}�N����`
//==================================================================================================================
#define ROT_ANGLE 0.08f			// ��]������p�x
#define ALPHA_DEGRESS 21.875f		// ���l�̌�����
#define MAX_HPBAR 5				// HP�o�[�̍ő�{��
#define BAR0_POS D3DXVECTOR3(250, 350, 0)	// 0�Ԗ�BarHP
#define BAR1_POS D3DXVECTOR3(250, 354, 0)	// 1�Ԗ�Bar�t���[��
#define BAR2_POS D3DXVECTOR3(200, 350, 0)	// 2�Ԗ�BarHP
#define BAR3_POS D3DXVECTOR3(200, 354, 0)	// 3�Ԗ�Bar�t���[��
#define BAR4_POS D3DXVECTOR3(150, 350, 0)	// 4�Ԗ�BarHP
#define BAR5_POS D3DXVECTOR3(150, 354, 0)	// 5�Ԗ�Bar�t���[��
#define BAR6_POS D3DXVECTOR3(100, 350, 0)	// 6�Ԗ�BarHP
#define BAR7_POS D3DXVECTOR3(100, 354, 0)	// 7�Ԗ�Bar�t���[��
#define BAR8_POS D3DXVECTOR3(50, 350, 0)	// 8�Ԗ�BarHP
#define BAR9_POS D3DXVECTOR3(50, 354, 0)	// 9�Ԗ�Bar�t���[��
#define NORMAL_COLOR D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)	// ���ʂ̐F

//==================================================================================================================
//	�R���X�g���N�^
//==================================================================================================================
CHitPoint::CHitPoint(PRIORITY type = PRIORITY_UI) : CScene(type)
{

}

//==================================================================================================================
//	����������
//==================================================================================================================
void CHitPoint::Init(void)
{
	// �v���C���[�̏��|�C���^
	CPlayer *pPlayer = CGame::GetPlayer(0);

	// ������
	m_pBar = NULL;						// �o�[�̏��|�C���^
	m_pos = D3DXVECTOR3(0, 0, 0);		// �ʒu
	m_rot0 = D3DXVECTOR3(0, 0, 0);		// ��]
	m_rot1 = D3DXVECTOR3(0, 0, 0);		// ��]
	m_rot2 = D3DXVECTOR3(0, 0, 0);		// ��]
	m_rot3 = D3DXVECTOR3(0, 0, 0);		// ��]
	m_nCntCol0 = 0;						// ��]�p�J�E���^
	m_nCntCol1 = 0;						// ��]�p�J�E���^
	m_nCntCol2 = 0;						// ��]�p�J�E���^
	m_nCntCol3 = 0;						// ��]�p�J�E���^
	m_fMaxHP = pPlayer->GetLife();		// �ő�HP
	m_fNowHP = m_fMaxHP;				// ���݂�HP
	m_fHeight = MAX_HEIGHT;				// ����
	m_bBar[5] = false;					// �o�[�����邩�ǂ���

	// Bar�̐���
	m_pBar = CBar::Create();

	// Bar������Ƃ�
	if (m_pBar != NULL)
	{
		// BarHP
		m_pBar->SetVertexBar(0, BAR0_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(1, BAR1_POS, NORMAL_COLOR, MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(2, BAR2_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(3, BAR3_POS, NORMAL_COLOR, MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(4, BAR4_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(5, BAR5_POS, NORMAL_COLOR, MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(6, BAR6_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(7, BAR7_POS, NORMAL_COLOR, MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(8, BAR8_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(9, BAR9_POS, NORMAL_COLOR, MAX_WIDTH, MAX_HEIGHT + 5);

	}
}

//==================================================================================================================
//	�I������
//==================================================================================================================
void CHitPoint::Uninit(void)
{
	// �o�[������Ƃ�
	if (m_pBar != NULL)
	{
		//Bar�̏I������
		m_pBar->Uninit();
	}
}

//==================================================================================================================
//	�X�V����
//==================================================================================================================
void CHitPoint::Update(void)
{
	// Bar�̍X�V����
	m_pBar->Update();

	// �v���C���[���擾
	CPlayer *pPlayer = CGame::GetPlayer(0);

	float NowHP = pPlayer->GetLife();				// ���݂�HP

	// HP�o�[����{�ڂ̂Ƃ�
	if (NowHP >= m_fMaxHP / 5 * 4)
	{
		float fHeight = 0.0f;									// ���݂̉摜�̍���
		m_fNowHP = (NowHP - m_fMaxHP / 5 * 4) / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;							// �`�悷�ׂ��摜����������Ȃ̂�
		m_bBar[0] = true;										// �o�[0�������Ԃɂ���

		// �ő�{���܂ŃJ�E���g
		for (int nCnt = 0; nCnt < MAX_HPBAR; nCnt++)
		{
			m_bBar[nCnt] = true;			// �S��ture�ɂ���
		}

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(0, BAR0_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);
	}
	else if (NowHP >= m_fMaxHP / 5 * 3)
	{// HP�o�[����{�ڂ̂Ƃ�

		float fHeight = 0.0f;									// ���݂̉摜�̍���
		m_fNowHP = (NowHP - m_fMaxHP / 5 * 3) / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;							// �`�悷�ׂ��摜����������Ȃ̂�

		// �ő�{���܂ŃJ�E���g
		for (int nCnt = 1; nCnt < MAX_HPBAR; nCnt++)
		{
			m_bBar[0] = false;			// 0�Ԗڂ�false
			m_bBar[nCnt] = true;		// ����ȊOture�ɂ���
		}

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(2, BAR2_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);

		// HP�o�[0�Ԗڂ�false�̂Ƃ�
		if (!m_bBar[0])
		{
			// �p�xZ��D3DX_PI/2�ȉ��̂Ƃ�
			if (m_rot0.z <= D3DX_PI / 2)
			{
				// �o�[��]�ݒ�
				m_pBar->RotBar(0, BAR0_POS, ROT_ANGLE, MAX_HEIGHT / 2);
				m_pBar->RotBar(1, BAR1_POS, ROT_ANGLE, MAX_HEIGHT / 2);

				// �o�[�F�ݒ�
				m_pBar->SetColBar(0, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f - m_nCntCol0 * (1.0f / ALPHA_DEGRESS)));
				m_pBar->SetColBar(1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - m_nCntCol0 * (1.0f / ALPHA_DEGRESS)));

				// �p�x���Z
				m_rot0.z += ROT_ANGLE;

				// ���l���Z
				m_nCntCol0++;
			}
		}
	}
	else if (NowHP >= m_fMaxHP / 5 * 2)
	{// HP�o�[���O�{�ڂ̂Ƃ�

		float fHeight = 0.0f;									// ���݂̉摜�̍���
		m_fNowHP = (NowHP - m_fMaxHP / 5 * 2) / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;							// �`�悷�ׂ��摜����������Ȃ̂�

		// �ő�{���܂ŃJ�E���g
		for (int nCnt = 2; nCnt < MAX_HPBAR; nCnt++)
		{
			m_bBar[0] = false;			// 0�Ԗڂ�false
			m_bBar[1] = false;			// 1�Ԗڂ�false
			m_bBar[nCnt] = true;		// ����ȊOture�ɂ���
		}

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(4, BAR4_POS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);

		// HP�o�[1�Ԗڂ�false�̂Ƃ�
		if (!m_bBar[1])
		{
			// �p�xZ��D3DX_PI/2�ȉ��̂Ƃ�
			if (m_rot1.z <= D3DX_PI / 2)
			{
				// �o�[��]�ݒ�
				m_pBar->RotBar(2, BAR2_POS, ROT_ANGLE, MAX_HEIGHT / 2);
				m_pBar->RotBar(3, BAR3_POS, ROT_ANGLE, MAX_HEIGHT / 2);

				// �o�[�F�ݒ�
				m_pBar->SetColBar(2, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f - m_nCntCol1 * (1.0f / ALPHA_DEGRESS)));
				m_pBar->SetColBar(3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - m_nCntCol1 * (1.0f / ALPHA_DEGRESS)));

				// �p�x���Z
				m_rot1.z += ROT_ANGLE;

				// ���l���Z
				m_nCntCol1++;
			}
		}
	}
	else if (NowHP >= m_fMaxHP / 5 * 1)
	{// HP�o�[���l�{�ڂ̂Ƃ�

		float fHeight = 0.0f;									// ���݂̉摜�̍���
		m_fNowHP = (NowHP - m_fMaxHP / 5 * 1) / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;							// �`�悷�ׂ��摜����������Ȃ̂�

		// �ő�{���܂ŃJ�E���g
		for (int nCnt = 3; nCnt < MAX_HPBAR; nCnt++)
		{
			m_bBar[0] = false;			// 0�Ԗڂ�false
			m_bBar[1] = false;			// 1�Ԗڂ�false
			m_bBar[2] = false;			// 2�Ԗڂ�false
			m_bBar[nCnt] = true;		// ����ȊOture�ɂ���
		}

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(6, D3DXVECTOR3(100, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);

		// HP�o�[2�Ԗڂ�false�̂Ƃ�
		if (!m_bBar[2])
		{
			// �p�xZ��D3DX_PI/2�ȉ��̂Ƃ�
			if (m_rot2.z <= D3DX_PI / 2)
			{
				// �o�[��]�ݒ�
				m_pBar->RotBar(4, BAR4_POS, ROT_ANGLE, MAX_HEIGHT / 2);
				m_pBar->RotBar(5, BAR5_POS, ROT_ANGLE, MAX_HEIGHT / 2);

				// �o�[�F�ݒ�
				m_pBar->SetColBar(4, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f - m_nCntCol2 * (1.0f / ALPHA_DEGRESS)));
				m_pBar->SetColBar(5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - m_nCntCol2 * (1.0f / ALPHA_DEGRESS)));

				// �p�x���Z
				m_rot2.z += ROT_ANGLE;

				// ���l���Z
				m_nCntCol2++;
			}
		}
	}
	else
	{// HP�o�[���ܖ{�ڂ̂Ƃ�

		float fHeight = 0.0f;				// ���݂̉摜�̍���
		m_fNowHP = NowHP / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;		// �`�悷�ׂ��摜����������Ȃ̂�

		// �ő�{���܂ŃJ�E���g
		for (int nCnt = 4; nCnt < MAX_HPBAR; nCnt++)
		{
			m_bBar[0] = false;			// 0�Ԗڂ�false
			m_bBar[1] = false;			// 1�Ԗڂ�false
			m_bBar[2] = false;			// 2�Ԗڂ�false
			m_bBar[3] = false;			// 3�Ԗڂ�false
			m_bBar[nCnt] = true;		// ����ȊOture�ɂ���
		}

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(8, D3DXVECTOR3(50, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);

		// HP�o�[3�Ԗڂ�false�̂Ƃ�
		if (!m_bBar[3])
		{
			// �p�xZ��D3DX_PI/2�ȉ��̂Ƃ�
			if (m_rot3.z <= D3DX_PI / 2)
			{
				// �o�[��]�ݒ�
				m_pBar->RotBar(6, BAR6_POS, ROT_ANGLE, MAX_HEIGHT / 2);
				m_pBar->RotBar(7, BAR7_POS, ROT_ANGLE, MAX_HEIGHT / 2);

				// �o�[�F�ݒ�
				m_pBar->SetColBar(6, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f - m_nCntCol3 * (1.0f / ALPHA_DEGRESS)));
				m_pBar->SetColBar(7, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - m_nCntCol3 * (1.0f / ALPHA_DEGRESS)));

				// �p�x���Z
				m_rot3.z += ROT_ANGLE;

				// ���l���Z
				m_nCntCol3++;
			}
		}
	}

}

//==================================================================================================================
//	�`�揈��
//==================================================================================================================
void CHitPoint::Draw(void)
{
	//Bar�̕`�揈��
	m_pBar->Draw();
}

//==================================================================================================================
// �I�u�W�F�N�g�̐���
//==================================================================================================================
CHitPoint * CHitPoint::Create(void)
{
	CHitPoint *pHitPoint = NULL;				// �|�C���^�ϐ�

	pHitPoint = new CHitPoint(PRIORITY_UI);		// �������𓮓I�m��
	pHitPoint->Init();							// ����������

	return pHitPoint;							// �l��Ԃ�
}

//==================================================================================================================
//	�ʒu�̐ݒ�
//==================================================================================================================
void CHitPoint::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
//	�ʒu�̎擾
//==================================================================================================================
D3DXVECTOR3 CHitPoint::GetPos(void)
{
	return m_pos;
}

//==================================================================================================================
//	�f�X�g���N�^
//==================================================================================================================
CHitPoint::~CHitPoint(void)
{

}
