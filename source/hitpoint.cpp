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
	m_fMaxHP = pPlayer->GetLife();		// �ő�HP
	m_fNowHP = m_fMaxHP;				// ���݂�HP
	m_fHeight = MAX_HEIGHT;				// ����

	// Bar�̐���
	m_pBar = CBar::Create();

	// Bar������Ƃ�
	if (m_pBar != NULL)
	{
		// BarHP
		m_pBar->SetVertexBar(0, D3DXVECTOR3(250, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(1, D3DXVECTOR3(250, 354, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(2, D3DXVECTOR3(200, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(3, D3DXVECTOR3(200, 354, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(4, D3DXVECTOR3(150, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(5, D3DXVECTOR3(150, 354, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(6, D3DXVECTOR3(100, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(7, D3DXVECTOR3(100, 354, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT + 5);

		// BarHP
		m_pBar->SetVertexBar(8, D3DXVECTOR3(50, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		// Bar�t���[��
		m_pBar->SetVertexBar(9, D3DXVECTOR3(50, 354, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_WIDTH, MAX_HEIGHT + 5);

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

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(0, D3DXVECTOR3(250, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);
	}
	else if (NowHP >= m_fMaxHP / 5 * 3)
	{// HP�o�[����{�ڂ̂Ƃ�

		float fHeight = 0.0f;									// ���݂̉摜�̍���
		m_fNowHP = (NowHP - m_fMaxHP / 5 * 3) / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;							// �`�悷�ׂ��摜����������Ȃ̂�

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(2, D3DXVECTOR3(200, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);
	}
	else if (NowHP >= m_fMaxHP / 5 * 2)
	{// HP�o�[���O�{�ڂ̂Ƃ�

		float fHeight = 0.0f;									// ���݂̉摜�̍���
		m_fNowHP = (NowHP - m_fMaxHP / 5 * 2) / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;							// �`�悷�ׂ��摜����������Ȃ̂�

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(4, D3DXVECTOR3(150, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);
	}
	else if (NowHP >= m_fMaxHP / 5 * 1)
	{// HP�o�[���l�{�ڂ̂Ƃ�

		float fHeight = 0.0f;									// ���݂̉摜�̍���
		m_fNowHP = (NowHP - m_fMaxHP / 5 * 1) / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;							// �`�悷�ׂ��摜����������Ȃ̂�

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(6, D3DXVECTOR3(100, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);
	}
	else
	{// HP�o�[���ܖ{�ڂ̂Ƃ�

		float fHeight = 0.0f;				// ���݂̉摜�̍���
		m_fNowHP = NowHP / (m_fMaxHP / 5);	// HP�̔䗦�v�Z
		fHeight = m_fNowHP * m_fHeight;		// �`�悷�ׂ��摜����������Ȃ̂�

		// BarHP�̐ݒ�
		m_pBar->SetVertexBar(8, D3DXVECTOR3(50, 350, 0), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), MAX_WIDTH, fHeight);
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
