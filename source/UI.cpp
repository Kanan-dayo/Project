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
#define ENTER_SIZEX 300.0f							// �G���^�[���SX
#define ENTER_SIZEY 150.0f							// �G���^�[���SY
#define TITLE_ENTER_POSY 600.0f						// �^�C�g���G���^�[���S�ʒuY
#define NORMAL_COLOR D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)// �摜�̂܂܂̐F
#define TITLEUI_BEGIN_X 2000						// �^�C�g��UI�ŏ��̉��̑傫��
#define TITLEUI_BEGIN_Y 1200						// �^�C�g��UI�ŏ��̏c�̑傫��
#define TITLEUI_SMALL_SPEED 15						// �^�C�g��UI�̏��������鑬�x
#define TITLEUI_VALUE_Y	350							// �����T�C�Y�̒lY
#define TITLEUI_LAST_X 1135							// �^�C�g��UI�Ō�̒lX
#define TITLEUI_BOUND_SPEED 5						// �^�C�g��UI�̃o�E���h���x
#define TITLEUI_MAXSIZE_VALUE_Y 370					// �^�C�g��UI�ő�T�C�Y�c
#define TITLEUI_MINSIZE_VALUE_Y 330					// �^�C�g��UI�ő�T�C�Y�c
#define TITLEUI_BOUND_COUNT 60						// �^�C�g��UI�o�E���h�J�E���^
#define TITLEUI_FINISH_Y 250						// �^�C�g��UI�̍Ō�̈ʒuY
#define TITLEUI_UP_SPEED 2							// �^�C�g��UI�オ�鑬�x
#define ENTERUI_SIZE_X 950							// �G���^�[UI�傫����
#define ENTERUI_SIZE_Y 80							// �G���^�[UI�傫���c
#define ENTERUI_POS_Y 600							// �G���^�[UI�ʒuY
#define ENTERUI_ALPHA 0.03f							// �G���^�[UI���l�ύX�l
#define SIGNUI_BEGINPOS_Y 800						// �Ŕ�UI�ŏ��̈ʒu
#define SIGNUI_LASTPOS_Y 600						// �Ŕ�UI�Ō�̈ʒu
#define SIGNUI_LASTPOS_Y 600						// �Ŕ�UI�Ō�̈ʒu
#define SIGNUI_MOVE_SPEED 8.0f						// �Ŕ�UI�������x
#define MODEUI_BEGINPOS_Y 780						// ���[�hUI�ŏ��̈ʒu

//==================================================================================================================
// �ÓI�����o�[�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CUI::m_pTexture[LOGOTYPE_MAX] = {};		// �e�N�X�`�����
char *CUI::m_apFileName[LOGOTYPE_MAX] =						// �ǂݍ��ރ��f���̃\�[�X��
{
	{ "data/TEXTURE/title.png" },			// �^�C�g��
	{ "data/TEXTURE/PressStart.png" },		// �G���^�[
	{ "data/TEXTURE/arrow.png" },			// �R���p�X���
	{ "data/TEXTURE/sign00.png" },			// �Ŕ�
	{ "data/TEXTURE/Mode00.png" },			// ���[�h00
	{ "data/TEXTURE/Mode01.png" },			// ���[�h01
	{ "data/TEXTURE/ModeFream.png" },		// ���[�h�g��
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
	TitlePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �^�C�g���̈ʒu
	m_nCntBound = 0;			// �^�C�g��UI�o�E���h�J�E���^
	m_nMode = 0;				// ���[�h�ԍ�
	m_nCntUITitle0 = 0;			// �^�C�g��UI�p�J�E���^0
	m_nCntUITitle1 = 0;			// �^�C�g��UI�p�J�E���^1
	m_nCntEnter = 0;			// �G���^�[�p�J�E���^
	m_nCntUISign = 0;			// �Ŕp�J�E���^
	m_bUITitle0 = false;		// �^�C�g���𓮂������ǂ���
	m_bUITitle1 = false;		// �^�C�g���𓮂������ǂ���
	m_bUIEnter = false;			// �G���^�[�̃��l�p�ϐ�

	// ���S�̍ő喇���J�E���g
	for (int nCnt = 0; nCnt < LOGOTYPE_MAX; nCnt++)
	{
		// �^�C�g���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
		{
			// �^�C�g���Ŏg�����S�̂Ƃ�
			if (nCnt <= LOGOTYPE_MODEFREAM)
			{
				// ��������
				m_pScene2D[nCnt] = CScene2D::Create();

				// �e�N�X�`����\��
				m_pScene2D[nCnt]->BindTex(m_pTexture[nCnt]);
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
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �^�C�g���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		// ���̃��[�h�ɂ������ǂ�������擾
		bool bModeNext = CTitle::GetbModeNext();

		if (!bModeNext)
		{
			// �^�C�g��UI
			SetUI(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + TitlePos.y, 0.0f), TITLEUI_BEGIN_X + m_nCntUITitle0 - m_nCntUITitle1,
				TITLEUI_BEGIN_Y + m_nCntUITitle0 + m_nCntUITitle1, LOGOTYPE_TITLE, NORMAL_COLOR);

			// �o�E���h�J�E���g���K��l�ȉ��̂Ƃ�
			if (m_nCntBound < TITLEUI_BOUND_COUNT)
			{
				// �^�C�g���𓮂����Ă��ȂƂ�
				if (!m_bUITitle0)
				{
					// �^�C�g��UI�̏c�̒������K��l�ȉ��̂Ƃ�
					if (TITLEUI_BEGIN_Y + m_nCntUITitle0 <= TITLEUI_VALUE_Y)
					{
						// �^�C�g���𓮂�����Ԃɂ���
						m_bUITitle0 = true;
					}
					else
					{
						// �^�C�g���J�E���^���Z
						m_nCntUITitle0 -= TITLEUI_SMALL_SPEED;
					}
				}
				else
				{// �^�C�g���𓮂����Ă����Ƃ�
					// �^�C�g��UI�̏c�̒�����[360]�ȏ�̂Ƃ�
					if (TITLEUI_BEGIN_Y + m_nCntUITitle0 + m_nCntUITitle1 >= TITLEUI_MAXSIZE_VALUE_Y)
					{
						// �^�C�g�����ő�܂Ŋg�傳����
						m_bUITitle1 = true;

					}
					else if (TITLEUI_BEGIN_Y + m_nCntUITitle0 + m_nCntUITitle1 <= TITLEUI_MINSIZE_VALUE_Y)
					{// �^�C�g��UI�̏c�̒�����[330]�ȉ��̂Ƃ�
						// �^�C�g�����ŏ��܂Ŋg��������
						m_bUITitle1 = false;
					}

					// �^�C�g�����ő�܂Ŋg�傳�����Ƃ�
					if (m_bUITitle1)
					{
						// �^�C�g���J�E���^���Z
						m_nCntUITitle1 -= TITLEUI_BOUND_SPEED;
					}
					else
					{// �^�C�g�����ŏ��܂Ŋg���������Ƃ�
						// �^�C�g���J�E���^���Z
						m_nCntUITitle1 += TITLEUI_BOUND_SPEED;
					}

					// �^�C�g��UI�o�E���h�J�E���^���Z
					m_nCntBound++;
				}
			}
			else
			{// �o�E���h�J�E���g���K��l�𒴂����Ƃ�
				// �^�C�g��UI�̈ʒuY���K��l�ȉ��̂Ƃ�
				if (SCREEN_HEIGHT / 2 + TitlePos.y < TITLEUI_FINISH_Y)
				{
					// �G���^�[UI
					SetUI(D3DXVECTOR3(SCREEN_WIDTH / 2, ENTERUI_POS_Y, 0.0f), ENTERUI_SIZE_X, ENTERUI_SIZE_Y,
						LOGOTYPE_ENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f + m_nCntEnter));

					// �G���^�[UI�̃��l��1.0�ȏ�̂Ƃ�
					if (1.0f + m_nCntEnter >= 1.0f)
					{
						// �G���^�[�p���l�����炷��Ԃɂ���
						m_bUIEnter = true;
					}
					else if (1.0f + m_nCntEnter <= 0.0f)
					{
						// �G���^�[�p���l�𑝂₷��Ԃɂ���
						m_bUIEnter = false;
					}

					// �G���^�[UI�����炷��Ԃ̂Ƃ�
					if (m_bUIEnter)
					{
						// �J�E���^���Z
						m_nCntEnter -= ENTERUI_ALPHA;
					}
					else
					{// �G���^�[UI�𑝂₷��Ԃ̂Ƃ�
						// �J�E���^���Z
						m_nCntEnter += ENTERUI_ALPHA;
					}
				}
				else
				{
					// �^�C�g���ʒu���Z
					TitlePos.y -= TITLEUI_UP_SPEED;
				}
			}
		}
		else
		{
			// �^�C�g��UI
			SetUI(D3DXVECTOR3(SCREEN_WIDTH / 2, TITLEUI_FINISH_Y + m_nCntUISign / 5, 0.0f), TITLEUI_LAST_X,
				TITLEUI_VALUE_Y, LOGOTYPE_TITLE, NORMAL_COLOR);

			// �G���^�[UI
			SetUI(D3DXVECTOR3(SCREEN_WIDTH / 2, ENTERUI_POS_Y, 0.0f), ENTERUI_SIZE_X, ENTERUI_SIZE_Y,
				LOGOTYPE_ENTER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

			// �Ŕ�UI
			SetUI(D3DXVECTOR3(SCREEN_WIDTH / 2, SIGNUI_BEGINPOS_Y + m_nCntUISign, 0.0f), 700, 500, LOGOTYPE_SIGN, NORMAL_COLOR);

			// ���[�h00UI
			SetUI(D3DXVECTOR3(480, MODEUI_BEGINPOS_Y + m_nCntUISign, 0.0f), 300, 120, LOGOTYPE_MODE00, NORMAL_COLOR);
			// ���[�h01UI
			SetUI(D3DXVECTOR3(810, MODEUI_BEGINPOS_Y + m_nCntUISign, 0.0f), 300, 120, LOGOTYPE_MODE01, NORMAL_COLOR);

			// �Ŕ�UI���K��l���傫����
			if (SIGNUI_BEGINPOS_Y + m_nCntUISign > SIGNUI_LASTPOS_Y)
			{
				// �Ŕp�J�E���^���Z
				m_nCntUISign -= SIGNUI_MOVE_SPEED;
			}

			// ���[�h�ԍ���[0]�̂Ƃ�
			if (m_nMode == 0)
			{
				// ���[�h�g��UI
				SetUI(D3DXVECTOR3(480, MODEUI_BEGINPOS_Y + m_nCntUISign, 0.0f), 300, 120, LOGOTYPE_MODEFREAM, NORMAL_COLOR);
			}
			else if (m_nMode == 1)
			{
				// ���[�h�g��UI
				SetUI(D3DXVECTOR3(810, MODEUI_BEGINPOS_Y + m_nCntUISign, 0.0f), 300, 120, LOGOTYPE_MODEFREAM, NORMAL_COLOR);
			}

			// �L�[�{�[�h��[��]���������Ƃ�
			if (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHTARROW))
			{
				m_nMode = 1;
			}
			else if (pInputKeyboard->GetKeyboardTrigger(DIK_LEFTARROW))
			{// �L�[�{�[�h��[��]���������Ƃ�
				m_nMode = 0;
			}
		}
	}
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
		// ���[�h���^�C�g���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
		{
			// �^�C�g���Ŏg�����S�̂Ƃ�
			if (nCnt <= LOGOTYPE_MODEFREAM)
			{
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, m_apFileName[nCnt], &m_pTexture[nCnt]);
			}
		}
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
		// ���[�h���^�C�g���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
		{
			// �^�C�g���Ŏg�����S�̂Ƃ�
			if (nCnt <= LOGOTYPE_MODEFREAM)
			{
				m_pTexture[nCnt]->Release();		// �J��
				m_pTexture[nCnt] = NULL;			// NULL�ɂ���
			}
		}
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
	m_pScene2D[nCnt]->SetPos(pos);									// �ʒu�ݒ�
	m_pScene2D[nCnt]->SetSize(D3DXVECTOR3(fSizeX, fSizeY, 0.0f));	// �傫���ݒ�
	m_pScene2D[nCnt]->SetCol(col);									// �F�ݒ�
}
