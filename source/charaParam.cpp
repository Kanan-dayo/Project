//=============================================================================
//
// �L�����N�^�[�p�����[�^�[����  [ charaParam.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "charaParam.h"

//=============================================================================
// �}�N����`
//=============================================================================	

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
CCharaParam::PLAYER_PARAM	CCharaParam::m_playerParam[PARAM_MAX] = {};

char						CCharaParam::m_aFileName[PARAM_MAX][64] =
{
	"data/PARAMETER/parameter_fokker.txt",
	"data/PARAMETER/parameter_niyasu.txt",
	"data/PARAMETER/parameter_sanyasu.txt",
	"data/PARAMETER/parameter_yonyasu.txt"
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharaParam::CCharaParam() {}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharaParam::~CCharaParam() {}

//=============================================================================
// �L�����N�^�[���Ƃ̃p�����[�^�[���[�h
//=============================================================================
HRESULT CCharaParam::Load(void)
{
	// �ϐ��錾
	FILE *pFile = nullptr;
	char cReadText[MAX_TEXT] = "";
	char cHeadText[MAX_TEXT] = "";
	char cDieText[MAX_TEXT] = "";

	CKananLibrary::StartBlockComment("�p�����[�^�[�t�@�C���̓ǂݍ��݊J�n");

	for (int type = 0; type < PARAM_MAX; type++)
	{
		// �L��������\��
		printf("�L�����N�^�[ %d ��ǂݍ��� (%s)\n", type, m_aFileName[type]);
		// �t�@�C�����J��
		pFile = fopen(m_aFileName[type], "r");

		// nullcheck
		if (!pFile)
		{
			// ���s
			printf("�t�@�C�����J���܂���ł���\n");
			continue;
		}

		// �X�N���v�g������܂ŌJ��Ԃ�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			// ��s���ǂݍ���
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}

		// �G���h�X�N���v�g������܂ŌJ��Ԃ�
		while (strcmp(cHeadText, "END_SCRIPT") != 0)
		{
			// ��s���ǂݍ���
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);

			// �U���ǂݍ��݂̃J�E���^
			int nCntAttack = 0;

			// ���s
			if (strcmp(cHeadText, "\n") == 0)
				continue;
			// �ő�HP
			else if (strcmp(cHeadText, "MAX_LIFE") == 0)
				sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_playerParam[type].fMaxLife);
			// ���鑬�x
			else if (strcmp(cHeadText, "RUN_SPEED") == 0)
				sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_playerParam[type].moveParam.fRunSpeed);
			// �W�����v��
			else if (strcmp(cHeadText, "JUMP_POWER") == 0)
				sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &m_playerParam[type].moveParam.fJumpPower);
			// �U��
			else if (strcmp(cHeadText, "SET_ATTACKPARAM") == 0)
			{
				// �G���h�X�N���v�g������܂ŌJ��Ԃ�
				while (strcmp(cHeadText, "END_ATTACKPARAM") != 0)
				{
					// ��s���ǂݍ���
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					// �U����
					if (strcmp(cHeadText, "ATTACK_POWER") == 0)
						sscanf(cReadText, "%s %s %f",
							&cDieText,
							&cDieText,
							&m_playerParam[type].attackParam[nCntAttack].fAttackPower);
					// �U���̃L�����Z���t���[��
					if (strcmp(cHeadText, "CANCEL_FRAME") == 0)
						sscanf(cReadText, "%s %s %d %s %d",
							&cDieText,
							&cDieText,
							&m_playerParam[type].attackParam[nCntAttack].CancelFrame.start,
							&cDieText,
							&m_playerParam[type].attackParam[nCntAttack].CancelFrame.end);
					// ������ѕ�
					if (strcmp(cHeadText, "BLOWAWAY_TYPE") == 0)
						sscanf(cReadText, "%s %s %d",
							&cDieText,
							&cDieText,
							&m_playerParam[type].attackParam[nCntAttack].blowType);
				}
				// �U���̉��Z
				nCntAttack++;
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}

	// ����
	CKananLibrary::EndBlockComment("�p�����[�^�[�t�@�C���̓ǂݍ��ݏI��");
	return S_OK;
}

//=============================================================================
// �f�[�^�̔j��
//=============================================================================
void CCharaParam::Unload(void)
{
	// ��ސ����J��Ԃ�
	/*for (int type = 0; type < PARAM_MAX; type++)
	{
		// nullcheck
		if (m_pAttackParam[type])
		{
			// �j��
			delete m_pAttackParam[type];
			m_pAttackParam[type] = nullptr;
		}
	}*/
}
