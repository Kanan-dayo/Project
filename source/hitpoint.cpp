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
	//CPlayer *pPlayer = CGame::GetPlayer();

	//������
	m_pBar = NULL;
	m_pos = D3DXVECTOR3(0, 0, 0);
	//m_fMaxHP = pPlayer->GetLife();
	m_fNowHP = m_fMaxHP;
	m_fWidth = MAX_WIDTH;

	//Bar�̐���
	m_pBar = CBar::Create();
	if (m_pBar != NULL)
	{
		m_pBar->SetVertexBar(0, D3DXVECTOR3(50, 650, 0), D3DXCOLOR(0.0f, 1.0f, 0.25f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
		m_pBar->SetVertexBar(1, D3DXVECTOR3(39, 650, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_WIDTH + 22, MAX_HEIGHT);
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
	//Bar�̍X�V����
	m_pBar->Update();

	//CPlayer *pPlayer = CGame::GetPlayer();

	//float NowHP = pPlayer->GetLife();													//�v���C���[�̗͎̑擾
	float fWidth = 0;																	//���݂̉摜�̕�
	float fResidue = 0.0f;																//�c��̐��l

	//m_fNowHP = NowHP / m_fMaxHP;														//HP�̔䗦�v�Z
	fWidth = m_fNowHP * m_fWidth;														//�`�悷�ׂ��摜����������Ȃ̂�
	//fResidue = (m_fMaxHP - NowHP) / m_fMaxHP;

	if (m_fNowHP > 0.5f)
	{
		m_pBar->SetVertexBar(0, D3DXVECTOR3(50, 650, 0), D3DXCOLOR(0.0f + fResidue * 2, 1.0f, 0.25f - (fResidue / 2), 1.0f), fWidth, MAX_HEIGHT);
	}
	else
	{
		m_pBar->SetVertexBar(0, D3DXVECTOR3(50, 650, 0), D3DXCOLOR(1.0f, m_fNowHP * 2, 0.0f, 1.0f), fWidth, MAX_HEIGHT);
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