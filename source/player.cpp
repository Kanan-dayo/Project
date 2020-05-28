//==================================================================================================================
//
// �v���C���[����[player.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "inputKeyboard.h"
#include "renderer.h"
#include "player.h"
#include "debugProc.h"
#include "camera.h"
#include "meshField.h"
#include "motionModel.h"
#include "time.h"
#include "title.h"
#include <initializer_list>
#include "tutorial.h"
#include "game.h"
#include "inputGamepad.h"
#include "character.h"
#include "scene.h"

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CCamera *CPlayer::m_pCamera = NULL;				// �J�������

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MOTION_FILE_NAME "data/TEXT/C++3DMotion.txt"// �ǂݍ��ރe�L�X�g�f�[�^�̃\�[�X��
#define TITLE_PLAYER_MOVE 0.15f		// �^�C�g���̃v���C���[�̈ړ���
#define PLAYER_MOVE 0.25f			// �v���C���[�̈ړ���
#define PLAYER_INERTIA 3.0f			// �����X�s�[�h
#define PLAYER_SPEED_DOWN -0.2f		// �X�s�[�h�_�E�����x
#define JUMP_MOVE 11.0f				// �W�����v����Ƃ��̈ړ���
#define MAX_JAMP_SPEED 0.05f		// �ő�W�����v�X�s�[�h
#define MAX_GRAVITY -6.0f			// �d�͂̍ő�l
#define GRAVITY -0.4f				// �d��
#define ROT_LIMIT 1.0f				// ��]����
#define ROT_SPEED 0.4f				// ��]���x
#define ROT_AMOUNT 0.1f				// ��]�̍������炵�Ă�����
#define REDUCE_SPEED 0.06f			// �����X�s�[�h

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CPlayer::CPlayer(PRIORITY type = CScene::PRIORITY_PLAYER) : CCharacter(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CPlayer::~CPlayer()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CPlayer::Init(void)
{
	CCharacter::Init();

	//���[�V�����̏�����
	for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_MAX; nCntMotion++)
	{
		m_PlayerMotion[nCntMotion].nLoop = 0;										// ���[�v
		m_PlayerMotion[nCntMotion].nNumKey = 0;										// �L�[���̐�
		m_PlayerMotion[nCntMotion].Collision_nParts = 0;							// �p�[�c�ԍ�
		m_PlayerMotion[nCntMotion].CollisionOfset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �I�t�Z�b�g
		m_PlayerMotion[nCntMotion].CollisionRadius = 0.0f;							// �~�̔��a
		m_PlayerMotion[nCntMotion].CollisionStartFram = 0;							// �J�n�t���[��
		m_PlayerMotion[nCntMotion].CollisionEndFram = 0;							// �I���t���[��
		m_PlayerMotion[nCntMotion].Collision_Damage = 0;							// �_���[�W��

		// �L�[�̑������J�E���g
		for (int nCntKeySet = 0; nCntKeySet < 10; nCntKeySet++)
		{
			m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram = 0;				// �e�L�[�̃t���[��

			for (int nCntKey = 0; nCntKey < 11; nCntKey++)
			{
				m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�p�[�c�̊e�L�[�̈ʒu
				m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�p�[�c�̊e�L�[�̉�]
			}
		}
	}

	//=================================���f���̐ݒ�=================================//
	//�� 0
	m_MotionModel[0] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_BODY);		// �̐���
	m_MotionModel[0]->SetPos(D3DXVECTOR3(0, -2.0f, 0));										// �ʒu�ݒ�
	m_MotionModel[0]->SetRot(D3DXVECTOR3(0.0f, -1.5f, 0.0f));								// ��]�ݒ�
	m_MotionModel[0]->SetParent(NULL);														// �e�ݒ�
	//�� 1
	m_MotionModel[1] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_HEAD);		// ���p�[�c����
	m_MotionModel[1]->SetPos(D3DXVECTOR3(-11.0f, 5.0f, -0.44f));							// �ʒu�ݒ�
	m_MotionModel[1]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//���r 2
	m_MotionModel[2] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_LARM);		// ���r����
	m_MotionModel[2]->SetPos(D3DXVECTOR3(-5.0f, 3.0f, -4.0f));								// �ʒu�ݒ�
	m_MotionModel[2]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//�E�r 3
	m_MotionModel[3] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_RARM);		// �E�r����
	m_MotionModel[3]->SetPos(D3DXVECTOR3(-5.0f, 3.0f, 4.0f));								// �ʒu�ݒ�
	m_MotionModel[3]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//���� 4
	m_MotionModel[4] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_LLEG);		// ��������
	m_MotionModel[4]->SetPos(D3DXVECTOR3(6.0f, 0.0f, -3.0f));								// �ʒu�ݒ�
	m_MotionModel[4]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//�E�� 5
	m_MotionModel[5] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_RLEG);		// �E������
	m_MotionModel[5]->SetPos(D3DXVECTOR3(6.0f, 0.0f, 3.0f));								// �ʒu�ݒ�
	m_MotionModel[5]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�

	// ���[�V�����̓ǂݍ���
	LoadMotion();
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CPlayer::Uninit(void)
{
	// �v���C���[���f���̍ő�p�[�c�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// ���f���̏I������
		m_MotionModel[nCnt]->Uninit();

		// �������폜
		delete m_MotionModel[nCnt];

		// �|�C���^�pNULL
		m_MotionModel[nCnt] = nullptr;
	}

	CCharacter::Uninit();
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CPlayer::Update(void)
{
	/*m_pos = GetPos();			// �ʒu�擾
	m_rot = GetRot();			// ��]�擾
	m_size = GetSize();			// �傫���擾

	// �O�̃��[�V�����̑��
	m_MotionOld = m_MotionType;

	// ���[�V����
	Moation();

	SetPos(m_pos);				// �ʒu�ݒ�
	SetRot(m_rot);				// ��]�ݒ�
	SetSize(m_size);			// �傫���ݒ�*/

	CCharacter::Update();

#ifdef _DEBUG
	// �f�o�b�O�\��
	CDebugProc::Print("�v���C���[�̈ʒu : %.2f, %.2f, %.2f\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("�v���C���[�̈ړ��� : %.2f, %.2f, %.2f\n", m_move.x, m_move.y, m_move.z);
	CDebugProc::Print("�v���C���[�̉�] : %.2f, %.2f, %.2f\n", m_rot.x, m_rot.y, m_rot.z);
#endif // _DEBUG
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();

	// ���f���̕`��
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// ���S�̃}�g���b�N�X�ݒ�
		m_MotionModel[nCnt]->SetMtxCenter(m_mtxWorld);

		// �`�揈��
		m_MotionModel[nCnt]->Draw();
	}
}

//==================================================================================================================
// ��������
//==================================================================================================================
CPlayer *CPlayer::Create(void)
{
	// �V�[�����I�Ɋm��
	CPlayer *pPlayer = new CPlayer(CScene::PRIORITY_PLAYER);

	pPlayer->Init();			// �v���C���[�̏�����

	// �l��Ԃ�
	return pPlayer;
}

////==================================================================================================================
//// �ʒu�ݒ�
////==================================================================================================================
//void CPlayer::SetPos(D3DXVECTOR3 pos)
//{
//	m_pos = pos;
//}
//
////==================================================================================================================
//// ��]�ݒ�
////==================================================================================================================
//void CPlayer::SetRot(D3DXVECTOR3 rot)
//{
//	m_rot = rot;
//}
//
////==================================================================================================================
//// �傫���ݒ�
////==================================================================================================================
//void CPlayer::SetSize(D3DXVECTOR3 size)
//{
//	m_size = size;
//}

//==================================================================================================================
// ���[�V�����ǂݍ���
//==================================================================================================================
void CPlayer::LoadMotion(void)
{
	FILE *pFile;			// �t�@�C���|�C���g
	int nCntMotion = 0;		// ���[�V�����̐�
	int nCntModel = 0;		// ���f���̃J�E���g
	int nCntKeySet = 0;		// �t���[���̕�����
	int nCntKey = 0;		// �p�[�c�̔ԍ�
	char cReadText[128];	// �����Ƃ��ēǂݎ��p
	char cHeadText[128];	// ��r����p
	char cDie[128];			// �s�v�ȕ���

	// �t�@�C�����J��
	pFile = fopen(MOTION_FILE_NAME, "r");

	// �t�@�C��������Ƃ�
	if (pFile != NULL)
	{
		// �ǂݍ��񂾕�����[SCRIPT]�܂ŌJ��Ԃ�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);						// �ꕶ��ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);							// ��r�p�e�L�X�g�ɕ�������
		}

		// �ǂݍ��񂾕�����[SCRIPT]�̂Ƃ�
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// �G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);					// �ꕶ��ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);						// ��r�p�e�L�X�g�ɕ�������

				// ���[�V�����Z�b�g��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// �t���[���������̏�����
					nCntKeySet = 0;

					// �G���h���[�V�����Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);			// �ꕶ��ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);				// ��r�p�e�L�X�g�ɕ�������

						// �ǂݍ��񂾕�����[LOOP]�̂Ƃ�
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nLoop);			// ���[�v�ϐ��ɒl����
						}
						// �ǂݍ��񂾕�����[NUM_KEY]�̂Ƃ�
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nNumKey);		// �L�[���̐��ɒl����
						}
						// �ǂݍ��񂾕�����[KEYSET]�̂Ƃ�
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							nCntKey = 0;									// �L�[��񏉊���

							// �ǂݍ��񂾕�����[END_KEYSET]�܂ŌJ��Ԃ�
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);							// �ꕶ��ǂݍ���
								sscanf(cReadText, "%s", &cHeadText);								// ��r�p�e�L�X�g�ɕ�������

								// �ǂݍ��񂾕�����[FRAME]�̂Ƃ�
								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie,
										&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram);	// �t���[���ɒl����
								}
								// �ǂݍ��񂾕�����[KEY]�̂Ƃ�
								else if (strcmp(cHeadText, "KEY") == 0)
								{
									// �ǂݍ��񂾕�����[END_KEY]�܂ŌJ��Ԃ�
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);				// �ꕶ��ǂݍ���
										sscanf(cReadText, "%s", &cHeadText);					// ��r�p�e�L�X�g�ɕ�������

										// �ǂݍ��񂾕�����[POS]�̂Ƃ�
										if (strcmp(cHeadText, "POS") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",					// �ʒu�ɒl����
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.z);

											//m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos += m_Model[nCntKey]->GetPosition();
										}
										// �ǂݍ��񂾕�����[ROT]�̂Ƃ�
										else if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",					// ��]�ɒl����
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.z);
										}
									}

									// �p�[�c�ԍ����Z
									nCntKey++;
								}
							}

							// �t���[���̕��������Z
							nCntKeySet++;
						}
					}
					// ���[�V�����̐����Z
					nCntMotion++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	// �t�@�C���������Ƃ�
	else
	{
		// ���b�Z�[�W�Œm�点��
		MessageBox(NULL, "���[�V�����f�[�^�̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

//==================================================================================================================
// ���[�V����������
//==================================================================================================================
void CPlayer::Moation(void)
{
	// �O�̃��[�V�����ƍ��̃��[�V�������Ⴄ�Ƃ�
	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;					// �t���[���������l�ɖ߂�
		m_nCntKeySet = 0;			// ���[�V�������������l�ɖ߂�
	}

	// �v���C���[�̃��f���̍ő�p�[�c���܂ŃJ�E���g
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// �t���[����0�̂Ƃ�
		if (m_Fram == 0)
		{
			// ���[�V�������̃t���[����0����Ȃ��Ƃ�
			if (m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram != 0)
			{
				// �ړ���ROT�̌v�Z
				rotBET[nCnt] = (m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].key[nCnt].rot - m_MotionModel[nCnt]->GetRot()) /
					(float)m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram;
			}
			else
			{
				//m_MotionModel[nCnt]->GetPosition() = m_PlayerMotion[m_MotionType].key_info[mCntKeySet].key[nCnt].pos;
				m_MotionModel[nCnt]->GetRot() = m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].key[nCnt].rot;
				posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		// �t���[���ړ�
		if (m_Fram <= m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram)
		{
			m_MotionModel[nCnt]->SetPos(m_MotionModel[nCnt]->GetPos() + posBET[nCnt]);
			m_MotionModel[nCnt]->SetRot(m_MotionModel[nCnt]->GetRot() + rotBET[nCnt]);
		}
	}

	// �t���[�������[�V�������̃t���[���Ɠ����ł���Ƃ�
	if (m_Fram == m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram)
	{
		m_nCntKeySet++;
		m_Fram = 0;

		// �L�[�Z�b�g�����K��l�Ɠ����ɂȂ�����
		if (m_nCntKeySet == m_PlayerMotion[m_MotionType].nNumKey)
		{
			// ���[�v���Ȃ��Ƃ�
			if (m_PlayerMotion[m_MotionType].nLoop == 0)
			{
				m_nCntKeySet = 0;
				m_MotionType = 0;
				m_Fram = m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram;
				//g_Player.bAttack = false;
			}
			// ���[�v����Ƃ�
			else if (m_PlayerMotion[m_MotionType].nLoop == 1)
			{
				m_nCntKeySet = 0;
				m_MotionType = 0;
			}
		}
	}
	// �t���[�������K��l�Ɠ����ł͂Ȃ��Ƃ�
	else
	{
		// �t���[�����Z
		m_Fram++;
	}
}
