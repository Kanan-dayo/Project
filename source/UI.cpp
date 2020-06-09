//==================================================================================================================
//
// UI����[UI.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "UI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"
#include "debugProc.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define START_SIZE 180.0f							// �X�^�[�g���̑傫��
#define LOGO_START_SIZEX 400.0f						// �X�^�[�g���S�̉��̑傫��
#define LOGO_START_SIZEY 200.0f						// �X�^�[�g���S�̏c�̑傫��
#define TITLEFADE_POSX -1500.0f						// �^�C�g�����S�̏����ʒuX
#define TITLEFADE_POSY 250.0f						// �^�C�g�����S�̏����ʒuY
#define TITLELOGO_SIZEX 600.0f						// �^�C�g�����S�̑傫��X
#define TITLELOGO_SIZEY 300.0f						// �^�C�g�����S�̑傫��Y
#define TITLE_CENTER_POSX 620.0f					// �^�C�g�����S�����̈ʒuX
#define TITLELOGO_SPEEDX 5.9f						// �^�C�g�����S�����炷�X�s�[�h
#define TUTORIALLOGO_POSX1 1395.0f					// �`���[�g���A�����S�ʒuX1
#define TUTORIALLOGO_POSX2 630.0f					// �`���[�g���A�����S�ʒuX2
#define TUTORIALLOGO_POSY 620.0f					// �`���[�g���A�����S�ʒuY
#define TUTORIALLOGO_SIZEX 270.0f					// �`���[�g���A�����S�傫��X
#define TUTORIALLOGO_SIZEY 130.0f					// �`���[�g���A�����S�傫��Y
#define ENTER_SIZEX 300.0f							// �G���^�[���SX
#define ENTER_SIZEY 150.0f							// �G���^�[���SY
#define TITLE_ENTER_POSY 600.0f						// �^�C�g���G���^�[���S�ʒuY
#define TUTORIAL_FREAMLOGO_POSX 640.0f				// �`���[�g���A���t���[�����S�ʒuX
#define TUTORIAL_FREAMLOGO_POSY 620.0f				// �`���[�g���A���t���[�����S�ʒuY
#define TUTORIAL_FREAMLOGO_SIZEX 1500.0f			// �`���[�g���A���t���[�����S�傫��X
#define TUTORIAL_FREAMLOGO_SIZEY 130.0f				// �`���[�g���A���t���[�����S�傫��Y
#define TUTORIAL_LOGO_POSX 1200.0f					// �`���[�g���A�����S�ʒuX
#define TUTORIAL_LOGO_POSY 620.0f					// �`���[�g���A�����S�ʒuY
#define TUTORIAL_LOGO_SIZEX 230.0f					// �`���[�g���A�����S�傫��X
#define TUTORIAL_LOGO_SIZEY 130.0f					// �`���[�g���A�����S�傫��Y
#define TUTORIAL_LOGO2_POSX -40.0f					// �`���[�g���A�����S2�ʒuX
#define TUTORIAL_LOGO2_POSY 620.0f					// �`���[�g���A�����S2�ʒuY
#define TUTORIAL_LOGO2_SIZEX 230.0f					// �`���[�g���A�����S2�傫��X
#define TUTORIAL_LOGO2_SIZEY 130.0f					// �`���[�g���A�����S2�傫��Y
#define TUTORIAL_ENTERLOGO_POSX 500.0f				// �`���[�g���A���G���^�[���S�ʒuX
#define TUTORIAL_ENTERLOGO_POSY 670.0f				// �`���[�g���A���G���^�[���S�ʒuY
#define TUTORIAL_ENTERLOGO_SIZEX 220.0f				// �`���[�g���A���G���^�[���S�傫��X
#define TUTORIAL_ENTERLOGO_SIZEY 120.0f				// �`���[�g���A���G���^�[���S�傫��Y
#define TUTORIAL_DELOGO_POSX 640.0f					// �`���[�g���A���Ń��S�ʒuX
#define TUTORIAL_DELOGO_POSY 670.0f					// �`���[�g���A���Ń��S�ʒuY
#define TUTORIAL_DELOGO_SIZEX 90.0f					// �`���[�g���A���Ń��S�傫��X
#define TUTORIAL_DELOGO_SIZEY 90.0f					// �`���[�g���A���Ń��S�傫��Y
#define TUTORIAL_SKIPLOGO_POSX 790.0f				// �`���[�g���A���X�L�b�v���S�ʒuX
#define TUTORIAL_SKIPLOGO_POSY 670.0f				// �`���[�g���A���X�L�b�v���S�ʒuY
#define TUTORIAL_SKIPLOGO_SIZEX 220.0f				// �`���[�g���A���X�L�b�v���S�傫��X
#define TUTORIAL_SKIPLOGO_SIZEY 120.0f				// �`���[�g���A���X�L�b�v���S�傫��Y
#define TUTORIAL_ALOGO_POSX 150.0f					// �`���[�g���A��A���S�ʒuX
#define TUTORIAL_ALOGO_POSY 200.0f					// �`���[�g���A��A���S�ʒuY
#define TUTORIAL_ALOGO_SIZEX 110.0f					// �`���[�g���A��A���S�傫��X
#define TUTORIAL_ALOGO_SIZEY 110.0f					// �`���[�g���A��A���S�傫��Y
#define TUTORIAL_LEFTLOGO_POSX 150.0f				// �`���[�g���A�������񃍃S�ʒuX
#define TUTORIAL_LEFTLOGO_POSY 250.0f				// �`���[�g���A�������񃍃S�ʒuY
#define TUTORIAL_LEFTLOGO_SIZEX 200.0f				// �`���[�g���A�������񃍃S�傫��X
#define TUTORIAL_LEFTLOGO_SIZEY 100.0f				// �`���[�g���A�������񃍃S�傫��Y
#define TUTORIAL_DLOGO_POSX 1110.0f					// �`���[�g���A��D���S�ʒuX
#define TUTORIAL_DLOGO_POSY 200.0f					// �`���[�g���A��D���S�ʒuY
#define TUTORIAL_DLOGO_SIZEX 110.0f					// �`���[�g���A��D���S�傫��X
#define TUTORIAL_DLOGO_SIZEY 110.0f					// �`���[�g���A��D���S�傫��Y
#define TUTORIAL_RIGHTLOGO_POSX 1110.0f				// �`���[�g���A���E���񃍃S�ʒuX
#define TUTORIAL_RIGHTLOGO_POSY 250.0f				// �`���[�g���A���E���񃍃S�ʒuY
#define TUTORIAL_RIGHTLOGO_SIZEX 200.0f				// �`���[�g���A���E���񃍃S�傫��X
#define TUTORIAL_RIGHTLOGO_SIZEY 100.0f				// �`���[�g���A���E���񃍃S�傫��Y
#define TUTORIAL_SLOGO_POSX 300.0f					// �`���[�g���A��S���S�ʒuX
#define TUTORIAL_SLOGO_POSY 400.0f					// �`���[�g���A��S���S�ʒuY
#define TUTORIAL_SLOGO_SIZEX 110.0f					// �`���[�g���A��S���S�傫��X
#define TUTORIAL_SLOGO_SIZEY 110.0f					// �`���[�g���A��S���S�傫��Y
#define TUTORIAL_SPEEDLOGO_POSX 300.0f				// �`���[�g���A���������S�ʒuX
#define TUTORIAL_SPEEDLOGO_POSY 450.0f				// �`���[�g���A���������S�ʒuY
#define TUTORIAL_SPEEDLOGO_SIZEX 130.0f				// �`���[�g���A���������S�傫��X
#define TUTORIAL_SPEEDLOGO_SIZEY 100.0f				// �`���[�g���A���������S�傫��Y
#define TUTORIAL_SPACELOGO_POSX 950.0f				// �`���[�g���A���X�y�[�X���S�ʒuX
#define TUTORIAL_SPACELOGO_POSY 400.0f				// �`���[�g���A���X�y�[�X���S�ʒuY
#define TUTORIAL_SPACELOGO_SIZEX 110.0f				// �`���[�g���A���X�y�[�X���S�傫��X
#define TUTORIAL_SPACELOGO_SIZEY 110.0f				// �`���[�g���A���X�y�[�X���S�傫��Y
#define TUTORIAL_JUMPLOGO_POSX 950.0f				// �`���[�g���A���W�����v���S�ʒuX
#define TUTORIAL_JUMPLOGO_POSY 450.0f				// �`���[�g���A���W�����v���S�ʒuY
#define TUTORIAL_JUMPLOGO_SIZEX 260.0f				// �`���[�g���A���W�����v���S�傫��X
#define TUTORIAL_JUMPLOGO_SIZEY 90.0f				// �`���[�g���A���W�����v���S�傫��Y
#define GAME_TIMEFREAMELOGO_POSX 640.0f				// �Q�[���^�C�}�[�t���[���ʒuX
#define GAME_TIMEFREAMELOGO_POSY 650.0f				// �Q�[���^�C�}�[�t���[���ʒuY
#define GAME_TIMEFREAMELOGO_SIZEX 400.0f			// �Q�[���^�C�}�[�t���[���傫��X
#define GAME_TIMEFREAMELOGO_SIZEY 150.0f			// �Q�[���^�C�}�[�t���[���傫��Y
#define GAME_NOWTIMEFREAMELOGO_POSX 540.0f			// �Q�[�����݂̃^�C�}�[�t���[���ʒuX
#define GAME_NOWTIMEFREAMELOGO_POSY 610.0f			// �Q�[�����݂̃^�C�}�[�t���[���ʒuY
#define GAME_NOWTIMEFREAMELOGO_SIZEX 100.0f			// �Q�[�����݂̃^�C�}�[�t���[���傫��X
#define GAME_NOWTIMEFREAMELOGO_SIZEY 50.0f			// �Q�[�����݂̃^�C�}�[�t���[���傫��Y
#define GAME_BESTTIME_POSX 520.0f					// �Q�[���ō��̃^�C�����S�ʒuX
#define GAME_BESTTIME_POSY 680.0f					// �Q�[���ō��̃^�C�����S�ʒuY
#define GAME_BESTTIME_SIZEX 140.0f					// �Q�[���ō��̃^�C�����S�傫��X
#define GAME_BESTTIME_SIZEY 50.0f					// �Q�[���ō��̃^�C�����S�傫��Y
#define GAME_DOT0_POSX 677.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_0���S�ʒuX
#define GAME_DOT0_POSY 620.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_0���S�ʒuY
#define GAME_DOT0_SIZEX 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_0���S�傫��X
#define GAME_DOT0_SIZEY 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_0���S�傫��Y
#define GAME_DOT1_POSX 757.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_1���S�ʒuX
#define GAME_DOT1_POSY 620.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_1���S�ʒuY
#define GAME_DOT1_SIZEX 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_1���S�傫��X
#define GAME_DOT1_SIZEY 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_1���S�傫��Y
#define GAME_DOT2_POSX 677.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_2���S�ʒuX
#define GAME_DOT2_POSY 690.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_2���S�ʒuY
#define GAME_DOT2_SIZEX 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_2���S�傫��X
#define GAME_DOT2_SIZEY 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_2���S�傫��Y
#define GAME_DOT3_POSX 757.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_3���S�ʒuX
#define GAME_DOT3_POSY 690.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_3���S�ʒuY
#define GAME_DOT3_SIZEX 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_3���S�傫��X
#define GAME_DOT3_SIZEY 100.0f						// �Q�[���^�C���ƃ^�C���̊Ԃ̓_3���S�傫��Y
#define GAME_PAUSE_POSX 207.0f						// �Q�[���|�[�Y���S�ʒuX
#define GAME_PAUSE_POSY 50.0f						// �Q�[���|�[�Y���S�ʒuY
#define GAME_PAUSE_SIZEX 400.0f						// �Q�[���|�[�Y���S�傫��X
#define GAME_PAUSE_SIZEY 130.0f						// �Q�[���|�[�Y���S�傫��Y
#define RANKING_RANK_POSX 450.0f					// �����N���S�ʒuX
#define RANKING_RANK_POSY 350.0f					// �����N���S�ʒuY
#define RANKING_RANK_SIZEX 180.0f					// �����N���S�傫��X
#define RANKING_RANK_SIZEY 500.0f					// �����N���S�傫��Y
#define RANKING_LOGO_POSX SCREEN_WIDTH / 2			// �����L���O���S�ʒuX
#define RANKING_LOGO_POSY 50.0f						// �����L���O���S�ʒuY
#define RANKING_LOGO_SIZEX 300.0f					// �����L���O���S�傫��X
#define RANKING_LOGO_SIZEY 100.0f					// �����L���O���S�傫��Y
#define RANKING_ENTER_POSX 1000.0f					// �����L���O�G���^�[���S�ʒuX
#define RANKING_ENTER_POSY 620.0f					// �����L���O�G���^�[���S�ʒuY
#define RANKING_ENTER_SIZEX 300.0f					// �����L���O�G���^�[���S�傫��X
#define RANKING_ENTER_SIZEY 100.0f					// �����L���O�G���^�[���S�傫��Y
#define RANKING_DOT0_POSX 595.0f					// �����L���O�����Ɛ����̊�0�̓_�ʒuX
#define RANKING_DOT0_POSY 163.0f					// �����L���O�����Ɛ����̊�0�̓_�ʒuY
#define RANKING_DOT_SIZE 130.0f						// �����L���O�����Ɛ����̊Ԃ̓_�傫��
#define RANKING_DOT1_POSX 703.0f					// �����L���O�����Ɛ����̊�1�̓_�ʒuX
#define RANKING_DOT1_POSY 163.0f					// �����L���O�����Ɛ����̊�1�̓_�ʒuY
#define RANKING_DOT2_POSX 595.0f					// �����L���O�����Ɛ����̊�2�̓_�ʒuX
#define RANKING_DOT2_POSY 263.0f					// �����L���O�����Ɛ����̊�2�̓_�ʒuY
#define RANKING_DOT3_POSX 703.0f					// �����L���O�����Ɛ����̊�3�̓_�ʒuX
#define RANKING_DOT3_POSY 263.0f					// �����L���O�����Ɛ����̊�3�̓_�ʒuY
#define RANKING_DOT4_POSX 595.0f					// �����L���O�����Ɛ����̊�4�̓_�ʒuX
#define RANKING_DOT4_POSY 363.0f					// �����L���O�����Ɛ����̊�4�̓_�ʒuY
#define RANKING_DOT5_POSX 703.0f					// �����L���O�����Ɛ����̊�5�̓_�ʒuX
#define RANKING_DOT5_POSY 363.0f					// �����L���O�����Ɛ����̊�5�̓_�ʒuY
#define RANKING_DOT6_POSX 595.0f					// �����L���O�����Ɛ����̊�6�̓_�ʒuX
#define RANKING_DOT6_POSY 463.0f					// �����L���O�����Ɛ����̊�6�̓_�ʒuY
#define RANKING_DOT7_POSX 703.0f					// �����L���O�����Ɛ����̊�7�̓_�ʒuX
#define RANKING_DOT7_POSY 463.0f					// �����L���O�����Ɛ����̊�7�̓_�ʒuY
#define RANKING_DOT8_POSX 595.0f					// �����L���O�����Ɛ����̊�8�̓_�ʒuX
#define RANKING_DOT8_POSY 563.0f					// �����L���O�����Ɛ����̊�8�̓_�ʒuY
#define RANKING_DOT9_POSX 703.0f					// �����L���O�����Ɛ����̊�9�̓_�ʒuX
#define RANKING_DOT9_POSY 563.0f					// �����L���O�����Ɛ����̊�9�̓_�ʒuY
#define TUTORIAL_MOVE 2.0f							// �`���[�g���A�����S�̈ړ���
#define TUTORIAL_PRESSJUMP_POSX 640.0f				// �`���[�g���A�������j�����S�ʒuX
#define TUTORIAL_PRESSJUMP_POSY 290.0f				// �`���[�g���A�������j�����S�ʒuY
#define TUTORIAL_PRESSJUMP_SIZEX 300.0f				// �`���[�g���A�������j�����S�傫��X
#define TUTORIAL_PRESSJUMP_SIZEY 150.0f				// �`���[�g���A�������j�����S�傫��Y
#define TUTORIAL_PLAYSWIM_POSX 640.0f				// �`���[�g���A�������j�����S�ʒuX
#define TUTORIAL_PLAYSWIM_POSY 380.0f				// �`���[�g���A�������j�����S�ʒuY
#define TUTORIAL_PLAYSWIM_SIZEX 400.0f				// �`���[�g���A�������j�����S�傫��X
#define TUTORIAL_PLAYSWIM_SIZEY 210.0f				// �`���[�g���A�������j�����S�傫��Y
#define GOAL_COUNT 4								// �S�[���J�E���g
#define GOAL_COUNTMAX 100							// �S�[���J�E���g�̍ő吔
#define GOAL_LOGO_POSY 250.0f						// �S�[�����S�̈ʒuY

//==================================================================================================================
// �ÓI�����o�[�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CUI::m_pTexture[LOGOTYPE_MAX] = {};		// �e�N�X�`�����
char *CUI::m_apFileName[LOGOTYPE_MAX] =						// �ǂݍ��ރ��f���̃\�[�X��
{
	{ "data/TEXTURE/title.png" },				// �^�C�g��
	{ "data/TEXTURE/PRESS START.png" },			// �G���^�[
	{ "data/TEXTURE/frame.png" },				// �^�C�}�[�t���[��
	{ "data/TEXTURE/tutorial.png" },			// �`���[�g���A�����S0
	{ "data/TEXTURE/tutorial.png" },			// �`���[�g���A�����S1
	{ "data/TEXTURE/PRESS START.png" },			// �`���[�g���A���G���^�[���S
	{ "data/TEXTURE/de.png" },					// �Ń��S
	{ "data/TEXTURE/skip.png" },				// �X�L�b�v���S
	{ "data/TEXTURE/pressJump.png" },			// �W�����v�{�^����
	{ "data/TEXTURE/playswim.png" },			// �����j�����S
	{ "data/TEXTURE/left.jpg" },				// ��
	{ "data/TEXTURE/left.png" },				// ������
	{ "data/TEXTURE/right.jpg" },				// �E
	{ "data/TEXTURE/right.png" },				// �E����
	{ "data/TEXTURE/A�{�^��.jpg" },				// A�{�^��
	{ "data/TEXTURE/speed down.png" },			// ����
	{ "data/TEXTURE/B�{�^��.jpg" },				// B�{�^��
	{ "data/TEXTURE/jump.png" },				// B�{�^��
	{ "data/TEXTURE/time.png" },				// ���݂̃^�C��
	{ "data/TEXTURE/besttime.png" },			// �ō��̃^�C��
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_0
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_1
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_2
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_3
	{ "data/TEXTURE/pauselogo.png" },			// �|�[�Y���S
	{ "data/TEXTURE/goal.png" },				// �S�[��
	{ "data/TEXTURE/start01.png" },				// �X�^�[�g
	{ "data/TEXTURE/1.png" },					// �J�E���g1
	{ "data/TEXTURE/2.png" },					// �J�E���g2
	{ "data/TEXTURE/3.png" },					// �J�E���g3
	{ "data/TEXTURE/Rank01.png" },				// �����N
	{ "data/TEXTURE/RankingLogo.png" },			// �����L���O���S
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_4
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_5
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_6
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_7
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_8
	{ "data/TEXTURE/dot.png" },					// �^�C���ƃ^�C���̊Ԃ̓_9
};

//==================================================================================================================
//
// �R���X�g���N�^
//
//==================================================================================================================
CUI::CUI(PRIORITY type = CScene::PRIORITY_UI) : CScene(type)
{

}

//==================================================================================================================
//
// �f�X�g���N�^
//
//==================================================================================================================
CUI::~CUI()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CUI::Init(void)
{
	m_nCounterAnim = 0;							// �A�j���[�V�����J�E���^

	// ���S�̍ő喇���J�E���g
	for (int nCnt = 0; nCnt < LOGOTYPE_MAX; nCnt++)
	{
		// �^�C�g���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
		{
			// �^�C�g���Ŏg�����S�̂Ƃ�
			if (nCnt <= LOGOTYPE_ENTER)
			{
				// ��������
				m_pScene2D[nCnt] = CScene2D::Create();

				// �e�N�X�`����\��
				m_pScene2D[nCnt]->BindTex(m_pTexture[nCnt]);
			}

			// ���S�ɂ���Đ؂�ւ���
			switch (nCnt)
			{
				// �^�C�g�����S
			case LOGOTYPE_TITLE:
				break;
				// �G���^�[
			case LOGOTYPE_ENTER:
				SetUI(D3DXVECTOR3(SCREEN_WIDTH / 2, TITLE_ENTER_POSY, 0.0f), ENTER_SIZEX, ENTER_SIZEY, LOGOTYPE_ENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
		}

		// �`���[�g���A���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
		{
			// �`���[�g���A���Ŏg�����S�̂Ƃ�
			if (nCnt <= LOGOTYPE_JUMP && nCnt >= LOGOTYPE_TIMEFRAME)
			{
				// ��������
				m_pScene2D[nCnt] = CScene2D::Create();

				// �e�N�X�`����\��
				m_pScene2D[nCnt]->BindTex(m_pTexture[nCnt]);
			}

			// ���S�ɂ���Đ؂�ւ���
			switch (nCnt)
			{
				// �t���[�����S
			case LOGOTYPE_TIMEFRAME:
				SetUI(D3DXVECTOR3(TUTORIAL_FREAMLOGO_POSX, TUTORIAL_FREAMLOGO_POSY, 0.0f), TUTORIAL_FREAMLOGO_SIZEX, TUTORIAL_FREAMLOGO_SIZEY, LOGOTYPE_TIMEFRAME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �`���[�g���A�����S
			case LOGOTYPE_TUTORIAL0:
				SetUI(D3DXVECTOR3(TUTORIAL_LOGO_POSX, TUTORIAL_LOGO_POSY, 0.0f), TUTORIAL_LOGO_SIZEX, TUTORIAL_LOGO_SIZEY, LOGOTYPE_TUTORIAL0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �`���[�g���A�����S
			case LOGOTYPE_TUTORIAL1:
				SetUI(D3DXVECTOR3(TUTORIAL_LOGO2_POSX, TUTORIAL_LOGO2_POSY, 0.0f), TUTORIAL_LOGO2_SIZEX, TUTORIAL_LOGO2_SIZEY, LOGOTYPE_TUTORIAL1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �`���[�g���A���G���^�[���S
			case LOGOTYPE_TUTORIALENTER:
				SetUI(D3DXVECTOR3(TUTORIAL_ENTERLOGO_POSX, TUTORIAL_ENTERLOGO_POSY, 0.0f), TUTORIAL_ENTERLOGO_SIZEX, TUTORIAL_ENTERLOGO_SIZEY, LOGOTYPE_TUTORIALENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �Ń��S
			case LOGOTYPE_DE:
				SetUI(D3DXVECTOR3(TUTORIAL_DELOGO_POSX, TUTORIAL_DELOGO_POSY, 0.0f), TUTORIAL_DELOGO_SIZEX, TUTORIAL_DELOGO_SIZEY, LOGOTYPE_DE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �X�L�b�v���S
			case LOGOTYPE_SKIP:
				SetUI(D3DXVECTOR3(TUTORIAL_SKIPLOGO_POSX, TUTORIAL_SKIPLOGO_POSY, 0.0f), TUTORIAL_SKIPLOGO_SIZEX, TUTORIAL_SKIPLOGO_SIZEY, LOGOTYPE_SKIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �L�[�{�[�h��A
			case LOGOTYPE_A:
				SetUI(D3DXVECTOR3(TUTORIAL_ALOGO_POSX, TUTORIAL_ALOGO_POSY, 0.0f), TUTORIAL_ALOGO_SIZEX, TUTORIAL_ALOGO_SIZEY, LOGOTYPE_A, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// ������
			case LOGOTYPE_LEFT:
				SetUI(D3DXVECTOR3(TUTORIAL_LEFTLOGO_POSX, TUTORIAL_LEFTLOGO_POSY, 0.0f), TUTORIAL_LEFTLOGO_SIZEX, TUTORIAL_LEFTLOGO_SIZEY, LOGOTYPE_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �L�[�{�[�h��D
			case LOGOTYPE_D:
				SetUI(D3DXVECTOR3(TUTORIAL_DLOGO_POSX, TUTORIAL_DLOGO_POSY, 0.0f), TUTORIAL_DLOGO_SIZEX, TUTORIAL_DLOGO_SIZEY, LOGOTYPE_D, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �E����
			case LOGOTYPE_RIGHT:
				SetUI(D3DXVECTOR3(TUTORIAL_RIGHTLOGO_POSX, TUTORIAL_RIGHTLOGO_POSY, 0.0f), TUTORIAL_RIGHTLOGO_SIZEX, TUTORIAL_RIGHTLOGO_SIZEY, LOGOTYPE_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �L�[�{�[�h��S
			case LOGOTYPE_S:
				SetUI(D3DXVECTOR3(TUTORIAL_SLOGO_POSX, TUTORIAL_SLOGO_POSY, 0.0f), TUTORIAL_SLOGO_SIZEX, TUTORIAL_SLOGO_SIZEY, LOGOTYPE_S, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �������S
			case LOGOTYPE_REDUCE_SPEED:
				SetUI(D3DXVECTOR3(TUTORIAL_SPEEDLOGO_POSX, TUTORIAL_SPEEDLOGO_POSY, 0.0f), TUTORIAL_SPEEDLOGO_SIZEX, TUTORIAL_SPEEDLOGO_SIZEY, LOGOTYPE_REDUCE_SPEED, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �L�[�{�[�h�̃X�y�[�X
			case LOGOTYPE_SPACE:
				SetUI(D3DXVECTOR3(TUTORIAL_SPACELOGO_POSX, TUTORIAL_SPACELOGO_POSY, 0.0f), TUTORIAL_SPACELOGO_SIZEX, TUTORIAL_SPACELOGO_SIZEY, LOGOTYPE_SPACE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �W�����v���S
			case LOGOTYPE_JUMP:
				SetUI(D3DXVECTOR3(TUTORIAL_JUMPLOGO_POSX, TUTORIAL_JUMPLOGO_POSY, 0.0f), TUTORIAL_JUMPLOGO_SIZEX, TUTORIAL_JUMPLOGO_SIZEY, LOGOTYPE_JUMP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
		}

		// �Q�[���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_GAME)
		{
			// �Q�[���Ŏg�����S�̂Ƃ�
			if (nCnt >= LOGOTYPE_NOW_TIME && nCnt <= LOGOTYPE_THREE || nCnt == LOGOTYPE_TIMEFRAME)
			{
				// ��������
				m_pScene2D[nCnt] = CScene2D::Create();

				// �e�N�X�`����\��
				m_pScene2D[nCnt]->BindTex(m_pTexture[nCnt]);
			}

			// ���S�ɂ���Đ؂�ւ���
			switch (nCnt)
			{
				// �^�C�}�[�t���[��
			case LOGOTYPE_TIMEFRAME:
				SetUI(D3DXVECTOR3(GAME_TIMEFREAMELOGO_POSX, GAME_TIMEFREAMELOGO_POSY, 0.0f), GAME_TIMEFREAMELOGO_SIZEX, GAME_TIMEFREAMELOGO_SIZEY, LOGOTYPE_TIMEFRAME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// ���݂̃^�C��
			case LOGOTYPE_NOW_TIME:
				SetUI(D3DXVECTOR3(GAME_NOWTIMEFREAMELOGO_POSX, GAME_NOWTIMEFREAMELOGO_POSY, 0.0f), GAME_NOWTIMEFREAMELOGO_SIZEX, GAME_NOWTIMEFREAMELOGO_SIZEY, LOGOTYPE_NOW_TIME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �ō��̃^�C��
			case LOGOTYPE_BEST_TIME:
				SetUI(D3DXVECTOR3(GAME_BESTTIME_POSX, GAME_BESTTIME_POSY, 0.0f), GAME_BESTTIME_SIZEX, GAME_BESTTIME_SIZEY, LOGOTYPE_BEST_TIME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �^�C���ƃ^�C���̊Ԃ̓_
			case LOGOTYPE_DOT0:
				SetUI(D3DXVECTOR3(GAME_DOT0_POSX, GAME_DOT0_POSY, 0.0f), GAME_DOT0_SIZEX, GAME_DOT0_SIZEY, LOGOTYPE_DOT0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �^�C���ƃ^�C���̊Ԃ̓_
			case LOGOTYPE_DOT1:
				SetUI(D3DXVECTOR3(GAME_DOT1_POSX, GAME_DOT1_POSY, 0.0f), GAME_DOT1_SIZEX, GAME_DOT1_SIZEY, LOGOTYPE_DOT1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �^�C���ƃ^�C���̊Ԃ̓_
			case LOGOTYPE_DOT2:
				SetUI(D3DXVECTOR3(GAME_DOT2_POSX, GAME_DOT2_POSY, 0.0f), GAME_DOT2_SIZEX, GAME_DOT2_SIZEY, LOGOTYPE_DOT2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �^�C���ƃ^�C���̊Ԃ̓_
			case LOGOTYPE_DOT3:
				SetUI(D3DXVECTOR3(GAME_DOT3_POSX, GAME_DOT3_POSY, 0.0f), GAME_DOT3_SIZEX, GAME_DOT3_SIZEY, LOGOTYPE_DOT3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �|�[�Y���S
			case LOGOTYPE_PAUSE:
				SetUI(D3DXVECTOR3(GAME_PAUSE_POSX, GAME_PAUSE_POSY, 0.0f), GAME_PAUSE_SIZEX, GAME_PAUSE_SIZEY, LOGOTYPE_PAUSE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
		}

		// �����L���O�̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_RANKING)
		{
			// �����L���O�Ŏg�����S�̂Ƃ�
			if (nCnt >= LOGOTYPE_RANK && nCnt <= LOGOTYPE_DOT9 || nCnt == LOGOTYPE_ENTER || nCnt >= LOGOTYPE_DOT0 && nCnt <= LOGOTYPE_DOT3)
			{
				// ��������
				m_pScene2D[nCnt] = CScene2D::Create();

				// �e�N�X�`����\��
				m_pScene2D[nCnt]->BindTex(m_pTexture[nCnt]);
			}

			// ���S�ɂ���Đ؂�ւ���
			switch (nCnt)
			{
				// �����N�̂Ƃ�
			case LOGOTYPE_RANK:
				SetUI(D3DXVECTOR3(RANKING_RANK_POSX, RANKING_RANK_POSY, 0.0f), RANKING_RANK_SIZEX, RANKING_RANK_SIZEY, LOGOTYPE_RANK, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����L���O���S�̂Ƃ�
			case LOGOTYPE_RANKING_LOGO:
				SetUI(D3DXVECTOR3(RANKING_LOGO_POSX, RANKING_LOGO_POSY, 0.0f), RANKING_LOGO_SIZEX, RANKING_LOGO_SIZEY, LOGOTYPE_RANKING_LOGO, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �G���^�[
			case LOGOTYPE_ENTER:
				SetUI(D3DXVECTOR3(RANKING_ENTER_POSX, RANKING_ENTER_POSY, 0.0f), RANKING_ENTER_SIZEX, RANKING_ENTER_SIZEY, LOGOTYPE_ENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_0
			case LOGOTYPE_DOT0:
				SetUI(D3DXVECTOR3(RANKING_DOT0_POSX, RANKING_DOT0_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_1
			case LOGOTYPE_DOT1:
				SetUI(D3DXVECTOR3(RANKING_DOT1_POSX, RANKING_DOT1_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_2
			case LOGOTYPE_DOT2:
				SetUI(D3DXVECTOR3(RANKING_DOT2_POSX, RANKING_DOT2_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_3
			case LOGOTYPE_DOT3:
				SetUI(D3DXVECTOR3(RANKING_DOT3_POSX, RANKING_DOT3_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_4
			case LOGOTYPE_DOT4:
				SetUI(D3DXVECTOR3(RANKING_DOT4_POSX, RANKING_DOT4_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT4, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_5
			case LOGOTYPE_DOT5:
				SetUI(D3DXVECTOR3(RANKING_DOT5_POSX, RANKING_DOT5_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_6
			case LOGOTYPE_DOT6:
				SetUI(D3DXVECTOR3(RANKING_DOT6_POSX, RANKING_DOT6_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT6, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_7
			case LOGOTYPE_DOT7:
				SetUI(D3DXVECTOR3(RANKING_DOT7_POSX, RANKING_DOT7_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT7, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_8
			case LOGOTYPE_DOT8:
				SetUI(D3DXVECTOR3(RANKING_DOT8_POSX, RANKING_DOT8_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT8, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
				// �����Ɛ����̊Ԃ̓_9
			case LOGOTYPE_DOT9:
				SetUI(D3DXVECTOR3(RANKING_DOT9_POSX, RANKING_DOT9_POSY, 0.0f), RANKING_DOT_SIZE, RANKING_DOT_SIZE, LOGOTYPE_DOT9, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
		}
	}
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CUI::Uninit(void)
{

}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CUI::Update(void)
{

}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CUI::Draw(void)
{

}

//==================================================================================================================
// ��������
//==================================================================================================================
CUI *CUI::Create(void)
{
	// �V�[�����I�Ɋm��
	CUI *pUI = new CUI(CScene::PRIORITY_UI);

	// �V�[��������
	pUI->Init();

	// �l��Ԃ�
	return pUI;
}

//==================================================================================================================
// �e�N�X�`�����[�h
//==================================================================================================================
HRESULT CUI::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾

	//==============================�e�N�X�`���̓ǂݍ���==============================//
	// �e�N�X�`���̍ő吔�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < LOGOTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_apFileName[nCnt], &m_pTexture[nCnt]);
	}

	// �l��Ԃ�
	return S_OK;
}

//==================================================================================================================
// �j��
//==================================================================================================================
void CUI::Unload(void)
{
	// ���S�̍ő��ނ܂ŃJ�E���g
	for (int nCnt = 0; nCnt < LOGOTYPE_MAX; nCnt++)
	{
		m_pTexture[nCnt]->Release();		// �J��
		m_pTexture[nCnt] = NULL;			// NULL�ɂ���
	}
}

//==================================================================================================================
// ��ގ擾
//==================================================================================================================
CUI::UITYPE CUI::GetType(void)
{
	return m_type;
}

//==================================================================================================================
// ���S�쐬
//==================================================================================================================
void CUI::SetUI(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nCnt, D3DXCOLOR col)
{
	m_pScene2D[nCnt]->SetPos(pos);												// �ʒu�ݒ�
	m_pScene2D[nCnt]->SetSize(D3DXVECTOR3(fSizeX, fSizeY, 0.0f));				// �傫���ݒ�
	m_pScene2D[nCnt]->SetCol(col);												// �F�ݒ�
}
