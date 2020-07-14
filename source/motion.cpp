//=============================================================================
//
// ���[�V��������  [ motion.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "motion.h"
#include "renderer.h"
#include "manager.h"
#include "Inputkeyboard.h"
#include "debugproc.h"
#include "modelcharacter.h"
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
CMotion::MOTION_INFO *CMotion::m_pMotionInfo = nullptr;
char * CMotion::m_apFileName[CMotion::MOTION_MAX] =
{
	{ "data/MOTION/fokker/motion_neutral.txt" },
	{ "data/MOTION/fokker/motion_run.txt" },
	//{ "data/MOTION/fokker/motion_jump.txt" },
	{ "data/MOTION/fokker/motion_lift.txt" },
	{ "data/MOTION/fokker/motion_throw.txt" },
	{ "data/MOTION/fokker/motion_attack_0.txt" },
	{ "data/MOTION/fokker/motion_attack_1.txt" },
	{ "data/MOTION/fokker/motion_attack_2.txt" },
	{ "data/MOTION/fokker/motion_attack_3.txt" },
	{ "data/MOTION/fokker/motion_smashCharge.txt" },
	{ "data/MOTION/fokker/motion_smash.txt" },
	{ "data/MOTION/fokker/motion_daunted.txt" },
	{ "data/MOTION/fokker/motion_blowAway.txt" }
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMotion::CMotion()
{
	m_pMotionInfo = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMotion::~CMotion()
{

}

//=============================================================================
// ���[�V�����̃��[�h
//=============================================================================
HRESULT CMotion::Load()
{
	// �������m��
	m_pMotionInfo = new CMotion::MOTION_INFO[MOTION_MAX];

	// �u���b�N�R�����g
	CKananLibrary::StartBlockComment("���[�V�����t�@�C���̓ǂݍ��݊J�n");

	for (int nCnt = 0; nCnt < MOTION_MAX; nCnt++)
	{
		// ���f���ǂݍ���
		if (FAILED(LoadMotion((CMotion::MOTION_TYPE)nCnt)))
			// ���s
			return E_FAIL;
	}

	// �u���b�N�R�����g
	CKananLibrary::EndBlockComment("���[�V�����t�@�C���̓ǂݍ��ݏI��");

	// ����
	return S_OK;
}

//=============================================================================
// ���[�V�����̃A�����[�h
//=============================================================================
void CMotion::UnLoad()
{
	// ���[�V��������
	for (int nCntMotion = 0; nCntMotion < MOTION_MAX; nCntMotion++)
	{
		// �L�[����
		for (int nCntKeyInfo = 0; nCntKeyInfo < m_pMotionInfo[nCntMotion].nNumKey; nCntKeyInfo++)
		{
			// nullcheck
			if (m_pMotionInfo[nCntMotion].pKeyInfo[nCntKeyInfo].pKey)
			{
				// ���݂̃L�[�̃������J��
				delete[] m_pMotionInfo[nCntMotion].pKeyInfo[nCntKeyInfo].pKey;
				m_pMotionInfo[nCntMotion].pKeyInfo[nCntKeyInfo].pKey = nullptr;
			}
		}
		// nullcheck
		if (m_pMotionInfo[nCntMotion].pKeyInfo)
		{
			// ���݂̃L�[�C���t�H�̃������J��
			delete[] m_pMotionInfo[nCntMotion].pKeyInfo;
			m_pMotionInfo[nCntMotion].pKeyInfo = nullptr;
		}
	}

	// nullcheck
	if (m_pMotionInfo)
	{
		// �������J��
		delete[] m_pMotionInfo;
		m_pMotionInfo = nullptr;

	}
}

//=============================================================================
// �e�L�X�g�t�@�C�����烂�[�V�������[�h
//=============================================================================
HRESULT CMotion::LoadMotion(MOTION_TYPE motiontype)
{
	// �ϐ��錾
	FILE *pFile;
	char cReadText[MAX_TEXT] = {};
	char cHeadText[MAX_TEXT] = {};
	char cDieText[MAX_TEXT] = {};
	int nLoop = 0;
	int nCntkeyInfo = 0;
	int nCntKey = 0;
	bool bInfo = false;	// �Ȃ����L�[����������̂ŁA���̕ϐ��ň��ɂ���

	// �t�@�C�����J��
	pFile = fopen(m_apFileName[motiontype], "r");

	// nullcheck
	if (!pFile)
	{
		// �t�@�C���ǂݍ��ݎ��s
		std::cout << m_apFileName[motiontype] << " �̓ǂݍ��ݎ��s" << std::endl;
		return E_FAIL;
	}

	// �X�N���v�g������܂ŌJ��Ԃ�
	while (strcmp(cHeadText, "SCRIPT") != 0)
	{
		fgets(cReadText, sizeof(cReadText), pFile);
		sscanf(cReadText, "%s", &cHeadText);
	}
	// �X�N���v�g��������
	if (strcmp(cHeadText, "SCRIPT") == 0)
	{
		// �G���h�X�N���v�g������܂ŌJ��Ԃ�
		while (strcmp(cHeadText, "END_SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			// ���s
			if (strcmp(cHeadText, "\n") == 0)
			{
			}
			// ���[�V�����Z�b�g
			else if (strcmp(cHeadText, "MOTIONSET") == 0)
			{
				// �G���h���[�V�����Z�b�g������܂ŌJ��Ԃ�
				while (strcmp(cHeadText, "END_MOTIONSET") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					// ���s
					if (strcmp(cHeadText, "\n") == 0)
					{
					}
					// ���[�v���邩
					else if (strcmp(cHeadText, "LOOP") == 0)
					{
						// ��xint�^�Ŋi�[����
						sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nLoop);

						// 1��0��bool�Ƃ��Ĕ��f����
						m_pMotionInfo[motiontype].bLoop = nLoop ? true : false;
					}
					// �L�[��
					else if (strcmp(cHeadText, "NUM_KEY") == 0 && !bInfo)
					{
						sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfo[motiontype].nNumKey);

						// �L�[�����������m��
						m_pMotionInfo[motiontype].pKeyInfo = new KEY_INFO[m_pMotionInfo[motiontype].nNumKey];

						// �L�[�Z�b�g���s���̂ŁA�L�[���J�E���g������������
						nCntkeyInfo = 0;

						bInfo = true;
					}
					// �L�[�Z�b�g
					else if (strcmp(cHeadText, "KEYSET") == 0)
					{
						// �p�[�c�����̃L�[��錾
						int nKey = CModelCharacter::GetPartsNum((CHARACTER_TYPE)CheckCharacter(motiontype));

						// �L�[�����������m��
						m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].pKey = new KEY[nKey];

						// �L�[�J�E���g������������
						nCntKey = 0;

						// �G���h�L�[�Z�b�g������܂ŌJ��Ԃ�
						while (strcmp(cHeadText, "END_KEYSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);
							// �t���[����
							if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].nFrame);
							}
							// �L�[
							if (strcmp(cHeadText, "KEY") == 0)
							{
								// �G���h�L�[������܂ŌJ��Ԃ�
								while (strcmp(cHeadText, "END_KEY") != 0)
								{
									fgets(cReadText, sizeof(cReadText), pFile);
									sscanf(cReadText, "%s", &cHeadText);
									// �ʒu
									if (strcmp(cHeadText, "POS") == 0)
									{
										sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].pKey[nCntKey].posDest.x,
											&m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].pKey[nCntKey].posDest.y, &m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].pKey[nCntKey].posDest.z);
									}
									// ��]
									if (strcmp(cHeadText, "ROT") == 0)
									{
										sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].pKey[nCntKey].rotDest.x,
											&m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].pKey[nCntKey].rotDest.y, &m_pMotionInfo[motiontype].pKeyInfo[nCntkeyInfo].pKey[nCntKey].rotDest.z);
									}
									// �I��
									if (strcmp(cHeadText, "END_KEY") == 0)
									{
										// �L�[���Z
										nCntKey++;
									}
								}
							}
							// �I��
							if (strcmp(cHeadText, "END_KEYSET") == 0)
							{
								// �L�[�����Z
								nCntkeyInfo++;
								bInfo = false;
							}
						}
					}
				}
			}
		}
	}
	// �t�@�C�������
	fclose(pFile);

	// �f�o�b�O�R�����g�\��
	std::cout << m_apFileName[motiontype] << " �̓ǂݍ��݊���" << std::endl;

	return S_OK;
}

//=============================================================================
// �L�����N�^�[���ǂꂩ�m�F
//=============================================================================
int CMotion::CheckCharacter(MOTION_TYPE type)
{
	// ���f���̎��
	CHARACTER_TYPE CharacterType = CHARACTER_NONE;

	// ���[�V�����̎�ނŔ��f
	/*switch (type)
	{
		// �v���C���[
	case CMotion::PLAYER_NEUTRAL:
	case CMotion::PLAYER_SWIM:
	case CMotion::PLAYER_SWIM_BEGIN:
		CharacterType = CHARACTER_PLAYER;
		break;
	case CMotion::FISH000_NEUTRAL:
		CharacterType = CHARACTER_FISH;
		break;
		case CMotion::FISH001_NEUTRAL:
		CharacterType = CHARACTER_FISH2;
		break;
	}*/

	return CharacterType;
}
