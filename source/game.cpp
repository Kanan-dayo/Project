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
#include "debugProc.h"
#include "objManager.h"
#include "CylinderCollider.h"
//==================================================================================================================
//	�}�N����`
//==================================================================================================================
#define PLAYER_START_POS_X 390.0f									// �v���C���[�̏����ʒuX
#define PLAYER_START_POS_Z -585.0f									// �v���C���[�̏����ʒuZ
#define RESPAWN_SIZE 0.000001f										// ���X�|�[�����f���̑傫��

#define TIME_CREATE_STONE (5 * ONE_SECOND_FPS)						// �X�g�[���𐶐����鎞��

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
CWall				*CGame::m_pWall					= NULL;							// �ǂ̃|�C���^
CGame::GAMESTATE	CGame::m_gameState				= CGame::GAMESTATE_NONE;		// �Q�[�����
int					CGame::m_nCounterGameState		= NULL;							// �Q�[���̏�ԊǗ��J�E���^�[
int					CGame::m_nNumStone				= 0;							// ���������X�g�[���̐�
int					CGame::m_nCntDecide				= 0;							// �X�g�[�������̃^�C�~���O�����߂�J�E���^
std::unique_ptr<CObjectManager>	CGame::m_pObjMana	= nullptr;						// �I�u�W�F�N�g�}�l�[�W���[�̃|�C���^

D3DXVECTOR3			CGame::m_stonePos[STONE_POS] = 									// �X�g�[���̐����ꏊ
{
	D3DXVECTOR3(0.0f, 20.0f, 0.0f),
	D3DXVECTOR3(100.0f, 20.0f, 100.0f),
	D3DXVECTOR3(100.0f, 20.0f, -100.0f),
	D3DXVECTOR3(-100.0f, 20.0f, 100.0f),
	D3DXVECTOR3(-100.0f, 20.0f, -100.0f)
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
	/* ���[�h */
	CNumber::Load();						// �����e�N�X�`�����[�h
	CMeshField::Load();						// ���e�N�X�`�����[�h
	CMotionModel::Load();					// ���[�V�����p���f�����[�h
	CPause::Load();							// �|�[�Y�e�N�X�`�����[�h
	CMeshSphere::Load();					// ���b�V�����̃e�N�X�`�����[�h
	CStone::Load();							// �X�g�[���̓ǂݍ���
	CBar::Load();							// Bar�e�N�X�`�����[�h
	C3DBoxCollider::Load();					// 3D�{�b�N�X�R���C�_�[�̓ǂݍ���
	CWall::Load();							// �ǂ̃��[�h
	CObjectManager::Load();					// �I�u�W�F�N�g�}�l�[�W���[�̃��[�h
	CCylinderCoillider::Load();				// �V�����_�[�R���C�_�[�̃��[�h

	/* ���� */
	C3DBoxCollider::Create();										// �{�b�N�X�R���C�_�[�̐���
	m_pObjMana    = CObjectManager::Create();						// �I�u�W�F�N�g�}�l�[�W���[�̐���
	m_pWall       = CWall::Create(CWall::WALLTEX_FIELD);			// �ǂ̐���
	m_pCamera     = CCamera::Create();								// �J�����̐�������
	m_pLight      = CLight::Create();								// ���C�g�̐�������
	m_pMeshSphere = CMeshSphere::Create();							// ���b�V�����̐�������
	// �v���C���[�̍ő吔�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_pPlayer[nCnt] = CPlayer::Create(nCnt, CHARACTER_1YASU);	// �v���C���[����
	}
	m_pMeshField = CMeshField::Create();							// ���b�V���t�B�[���h����
	m_pHitPoint  = CHitPoint::Create();								// HP��
	m_pTime      = CTime::Create();									// �^�C������
	m_pPause     = CPause::Create();								// �|�[�Y�̐�������

	/* �Q�[���̏����� */
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

	// �S�Ă̊J��
	CScene2D::ReleaseAll();				// 2D�̂��̑S�Ĕj��
	CScene3D::ReleaseAll();				// 3D�̂��̑S�Ĕj��

	/* �A�����[�h */
	CCylinderCoillider::Unload();
	CWall::Unload();					// �ǂ̊J��
	C3DBoxCollider::Unload();			// 3D�{�b�N�X�R���C�_�[�̊J��
	CStone::Unload();					// �X�g�[���̊J��
	CNumber::Unload();					// �����e�N�X�`���A�����[�h
	CMeshField::Unload();				// ���e�N�X�`���A�����[�h
	CMotionModel::Unload();				// ���[�V�����p���f���A�����[�h
	CBar::Unload();						// Bar�e�N�X�`���A�����[�h
	CObjectManager::Unload();			// �I�u�W�F�N�g�}�l�[�W���[�̃A�����[�h

	// �|�[�Y�̏I������
	m_pPause->Uninit();

	m_pObjMana->Uninit();				// �I������
	m_pObjMana.reset();					// �������폜
	m_pObjMana = nullptr;				// �|�C���^NULL

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

		// �I�u�W�F�N�g�}�l�[�W���[�̍X�V
		m_pObjMana->Update();
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

	// �I�u�W�F�N�g�}�l�[�W���[�̕`�揈��
	m_pObjMana->Draw();

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
	// �ϐ��錾
	CGame *pGame = NULL;		// �Q�[���ϐ�NULL
	pGame = new CGame;			// ���I�Ɋm��
	pGame->Init();				// ����������
	return pGame;				// �l��Ԃ�
}

//==================================================================================================================
//	�X�g�[���𐶐����邩���߂�
//==================================================================================================================
void CGame::DecideCreateStone(void)
{
	// ������
	srand((unsigned int)time(NULL));

	// �J�E���^�����Z
	m_nCntDecide++;

#ifdef _DEBUG
	if (CManager::GetInputKeyboard()->GetKeyboardTrigger(DIK_1) && 
		m_nNumStone + GetPlayer(0)->GetNumStone() + GetPlayer(1)->GetNumStone() < 3)
	{
		// ���߂�ꂽ�ʒu���烉���_���Ő���
		CStone::Create(CStone::STONE_ID_DEFAULT, m_stonePos[rand() % STONE_POS + 1]);
		m_nNumStone++;
	}
#endif

	// ���Ԉȓ�
	if (m_nCntDecide <= TIME_CREATE_STONE)
	{
		// �������I����
		return;
	}

	if (m_nNumStone + GetPlayer(0)->GetNumStone() + GetPlayer(1)->GetNumStone() < 3)
	{
		// ���߂�ꂽ�ʒu���烉���_���Ő���
		CStone::Create(CStone::STONE_ID_DEFAULT, m_stonePos[rand() % STONE_POS + 1]);
		// �o���������Z
		m_nNumStone++;
	}

	// �J�E���^��������
	m_nCntDecide = 0;
}
