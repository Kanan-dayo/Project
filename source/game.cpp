//==================================================================================================================
//
// Game�̕`�� [game.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================

//==================================================================================================================
//	�C���N���[�h�t�@�C��
//==================================================================================================================
#include "game.h"
#include "number.h"
#include "fade.h"
#include "inputKeyboard.h"
#include "meshField.h"
#include "scene3D.h"
#include "camera.h"
#include "light.h"
#include "time.h"
#include "renderer.h"
#include "motionModel.h"
#include "pause.h"
#include "inputGamepad.h"
#include "meshSphere.h"
#include "player.h"
#include "modelCharacter.h"
#include "stone.h"
#include "3DBoxCollider.h"
#include "hitpoint.h"
#include "bar.h"
#include "wall.h"

//==================================================================================================================
//	�}�N����`
//==================================================================================================================
#define PLAYER_START_POS_X 390.0f									// �v���C���[�̏����ʒuX
#define PLAYER_START_POS_Z -585.0f									// �v���C���[�̏����ʒuZ
#define RESPAWN_SIZE 0.000001f										// ���X�|�[�����f���̑傫��

#define PROBABILITY_CREATE_STONE (10)								// 1 / this �̊m���ŃX�g�[���𐶐�

//==================================================================================================================
//	�ÓI�����o�ϐ��錾
//==================================================================================================================
CPlayer				*CGame::m_pPlayer[MAX_PLAYER]	= {};							// �L�����N�^�[���
CMeshField			*CGame::m_pMeshField			= NULL;							// ���b�V���t�B�[���h���
CCamera				*CGame::m_pCamera				= NULL;							// �J�������
CLight				*CGame::m_pLight				= NULL;							// ���C�g���
CLogo				*CGame::m_pLogo					= NULL;							// ���S���
CPause				*CGame::m_pPause				= NULL;							// �|�[�Y���
CMeshSphere			*CGame::m_pMeshSphere			= NULL;							// ���b�V�����̏��
CHitPoint			*CGame::m_pHitPoint				= NULL;							// HP�̏��
CTime				*CGame::m_pTime					= NULL;							// �^�C�����
CGame::GAMESTATE	CGame::m_gameState				= CGame::GAMESTATE_NONE;		// �Q�[�����
int					CGame::m_nCounterGameState		= NULL;							// �Q�[���̏�ԊǗ��J�E���^�[
int					CGame::m_nNumStone				= 0;							// ���������X�g�[���̐�
int					CGame::m_nCntDecide				= 0;							// �X�g�[�������̃^�C�~���O�����߂�J�E���^

D3DXVECTOR3			CGame::m_stonePos[STONE_POS] = 									// �X�g�[���̐����ꏊ
{
	ZeroVector3,
	D3DXVECTOR3(100.0f, 0.0f, 100.0f),
	D3DXVECTOR3(100.0f, 0.0f, -100.0f),
	D3DXVECTOR3(-100.0f, 0.0f, 100.0f),
	D3DXVECTOR3(-100.0f, 0.0f, -100.0f)
};

//==================================================================================================================
//	�R���X�g���N�^
//==================================================================================================================
CGame::CGame()
{

}

//==================================================================================================================
//	�f�X�g���N�^
//==================================================================================================================
CGame::~CGame()
{

}

//==================================================================================================================
//	����������
//==================================================================================================================
void CGame::Init(void)
{
	CNumber::Load();						// �����e�N�X�`�����[�h
	CMeshField::Load();						// ���e�N�X�`�����[�h
	CMotionModel::Load();					// ���[�V�����p���f�����[�h
	CPause::Load();							// �|�[�Y�e�N�X�`�����[�h
	CMeshSphere::Load();					// ���b�V�����̃e�N�X�`�����[�h
	CStone::Load();							// �X�g�[���̓ǂݍ���
	CBar::Load();							// Bar�e�N�X�`�����[�h
	C3DBoxCollider::Load();					// 3D�{�b�N�X�R���C�_�[�̓ǂݍ���
	CWall::Load();							// �ǂ̃��[�h

	// �{�b�N�X�R���C�_�[�̐���
	C3DBoxCollider::Create();

	// �ǂ̐���
	CWall::Create(CWall::WALLTEX_FIELD);

	// �J�����̐�������
	m_pCamera = CCamera::Create();

	// ���C�g�̐�������
	m_pLight = CLight::Create();

	// ���b�V�����̐�������
	m_pMeshSphere = CMeshSphere::Create();

	// �v���C���[�̍ő吔�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		// �v���C���[����
		m_pPlayer[nCnt] = CPlayer::Create(nCnt, CHARACTER_1YASU);
	}

	// ���b�V���t�B�[���h����
	m_pMeshField = CMeshField::Create();

	// HP����
	m_pHitPoint = CHitPoint::Create();

	// �^�C������
	m_pTime = CTime::Create();

	// �|�[�Y�̐�������
	m_pPause = CPause::Create();

	SetGameState(GAMESTATE_NORMAL);			// �ʏ��Ԃɐݒ�
	m_nCounterGameState = 0;				// �Q�[���̏�ԊǗ��J�E���^�[��0�ɂ���
	m_nNumStone			= 0;				// �l��������
	m_nCntDecide		= 0;				// �l��������
}

//==================================================================================================================
//	�I������
//==================================================================================================================
void CGame::Uninit(void)
{
	// �Q�[����Ԃ�ʏ�ɂ���
	m_gameState = GAMESTATE_NORMAL;

	CScene2D::ReleaseAll();				// 2D�̂��̑S�Ĕj��
	CScene3D::ReleaseAll();				// 3D�̂��̑S�Ĕj��

	CWall::Unload();					// �ǂ̊J��
	C3DBoxCollider::Unload();			// 3D�{�b�N�X�R���C�_�[�̊J��
	CStone::Unload();					// �X�g�[���̊J��
	CNumber::Unload();					// �����e�N�X�`���A�����[�h
	CMeshField::Unload();				// ���e�N�X�`���A�����[�h
	CMotionModel::Unload();				// ���[�V�����p���f���A�����[�h
	CBar::Unload();						// Bar�e�N�X�`���A�����[�h

	// �|�[�Y�̏I������
	m_pPause->Uninit();

	delete m_pPause;					// �������폜
	m_pPause = nullptr;					// �|�C���^NULL

	delete m_pCamera;					// �������폜
	m_pCamera = nullptr;				// �|�C���^NULL

	delete m_pLight;					// �������폜
	m_pLight = nullptr;					// �|�C���^NULL

	m_pHitPoint = nullptr;				// �|�C���^NULL

	m_pTime = nullptr;					// �|�C���^NULL
}

//==================================================================================================================
//	�X�V����
//==================================================================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �t�F�[�h�擾
	CFade::FADE fade = CFade::GetFade();

	// �Q�[���̏�Ԏ擾
	m_gameState = GetGameState();

	// �Q�[����Ԃ��|�[�Y�̂Ƃ�
	if (m_gameState == GAMESTATE_PAUSE)
	{
		// �|�[�Y�̍X�V����
		m_pPause->Update();

		// �Q�[����Ԃ����߂����蒼���Ƃ�
		if (m_gameState == GAMESTATE_START_OVER)
		{
			// �t�F�[�h��ݒ肷��
			CFade::SetFade(CRenderer::MODE_GAME);
		}
		else if (m_gameState == GAMESTATE_BREAK)
		{// �Q�[����Ԃ����f�̂Ƃ�
			// �t�F�[�h��ݒ肷��
			CFade::SetFade(CRenderer::MODE_TITLE);
		}
	}
	else
	{
		// �J�����̍X�V����
		m_pCamera->Update();

		// ���C�g�̍X�V����
		m_pLight->Update();

		// �X�g�[���𐶐����邩���߂�
		DecideCreateStone();
	}

	// �L�[�{�[�h��[P] ���� �R���g���[���[��[START]�{�^���������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_P))
	{// �|�[�Y�؂�ւ�
		// �Q�[����Ԃ��|�[�Y�̂Ƃ�
		if (m_gameState == GAMESTATE_PAUSE)
		{
			// �Q�[����Ԃ�NORMAL�ɂ���
			m_gameState = GAMESTATE_NORMAL;

			// �|�[�Y��Ԃ̐ݒ�
			m_pPause->SetPause(false);
		}
		else
		{// �Q�[����Ԃ��|�[�Y����Ȃ��Ƃ�
			// �Q�[����Ԃ��|�[�Y�ɂ���
			m_gameState = GAMESTATE_PAUSE;

			// �|�[�Y��Ԃ̐ݒ�
			m_pPause->SetPause(true);
		}
	}
#ifdef _DEBUG
	// �L�[�{�[�h��[0]���������Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		// �t�F�[�h�������Ȃ���
		if (fade == CFade::FADE_NONE)
		{
			// �t�F�[�h��ݒ肷��
			CFade::SetFade(CRenderer::MODE_RANKING);
		}
	}
#endif // _DEBUG
}

//==================================================================================================================
//	�`�揈��
//==================================================================================================================
void CGame::Draw(void)
{
	// �J�����̐ݒ�
	m_pCamera->SetCamera();

	// �J�����̕`�揈��
	m_pCamera->Draw();

	// �|�[�Y��Ԃ�true�̂Ƃ�
	if (m_pPause->GetPause() == true)
	{
		// �|�[�Y�̍X�V����
		m_pPause->Draw();
	}
}

//==================================================================================================================
//	��������
//==================================================================================================================
CGame * CGame::Create(void)
{
	CGame *pGame = NULL;		// �Q�[���ϐ�NULL

	pGame = new CGame;			// ���I�Ɋm��
	pGame->Init();				// ����������

//	CModelCharacter::Load();

	return pGame;				// �l��Ԃ�
}

//==================================================================================================================
//	�X�g�[���𐶐����邩���߂�
//==================================================================================================================
void CGame::DecideCreateStone(void)
{
	// �J�E���^�����Z
	m_nCntDecide++;

	// ��b�ȓ�
	if (m_nCntDecide <= ONE_SECOND_FPS)
	{
		// �������I����
		return;
	}

	// ������
	srand((unsigned int)time(NULL));

	if (m_nNumStone + GetPlayer(0)->GetNumStone() + GetPlayer(1)->GetNumStone() < 3)
	{
		// �擾 + �o�� �̃X�g�[������3�����̂Ƃ��A�m���ŃX�g�[������
		if (rand() % PROBABILITY_CREATE_STONE + 1 == PROBABILITY_CREATE_STONE)
		{
			// ���߂�ꂽ�ʒu���烉���_���Ő���
			CStone::Create(CStone::STONE_ID_DEFAULT, m_stonePos[rand() % STONE_POS + 1]);
			// �o���������Z
			m_nNumStone++;
		}
	}

	// �J�E���^��������
	m_nCntDecide = 0;
}
