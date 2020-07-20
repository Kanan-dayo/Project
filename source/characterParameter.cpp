//=============================================================================
//
// �L�����N�^�[�p�����[�^�[����  [ characterParameter.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "characterParameter.h"

//=============================================================================
// �}�N����`
//=============================================================================	

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
char CCharacterParameter::m_aFileName[PARAMETER_MAX][64] =
{
	"data/PARAMETER/parameter_fokker.txt",
	"data/PARAMETER/parameter_niyasu.txt"
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacterParameter::CCharacterParameter() {}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacterParameter::~CCharacterParameter() {}
//=============================================================================
// ������
//=============================================================================
void CCharacterParameter::Init(void)
{

}

//=============================================================================
// �I��
//=============================================================================
void CCharacterParameter::Uninit(void)
{

}

//=============================================================================
// �L�����N�^�[���Ƃ̃p�����[�^�[���[�h
//=============================================================================
HRESULT CCharacterParameter::Load(PARAMETER_TYPE type)
{
	// �ϐ��錾
	FILE *pFile = nullptr;
	char cReadText[MAX_TEXT] = "";
	char cHeadText[MAX_TEXT] = "";
	char cDieText[MAX_TEXT] = "";

	// �t�@�C�����J��
	pFile = fopen(m_aFileName[type], "r");

	CKananLibrary::StartBlockComment("�p�����[�^�[�t�@�C���̓ǂݍ��݊J�n");

	if (!pFile)
	{
		// �u���b�N�R�����g
		CKananLibrary::EndBlockComment("�p�����[�^�[�t�@�C�����J���܂���ł���");
		// ���s
		return E_FAIL;
	}

	return S_OK;
}

/*HRESULT CObjectManager::LoadFileName(void)
{
	// �ϐ��錾
	FILE *pFile = nullptr;
	char cReadText[MAX_TEXT] = "";
	char cHeadText[MAX_TEXT] = "";
	char cDieText[MAX_TEXT] = "";
	int nNumType = 0;
	int nNumObj = 0;

	// �t�@�C�����J��
	pFile = fopen(&m_aFileName[0], "r");

	CKananLibrary::StartBlockComment("�I�u�W�F�N�g�t�@�C���̓ǂݍ��݊J�n�B");

	// nullcheck
	if (!pFile)
	{
		// �u���b�N�R�����g
		CKananLibrary::EndBlockComment("�I�u�W�F�N�g�t�@�C�����J���܂���ł����B");
		// ���s
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
				continue;
			// ���f���ԍ���������
			else if (strcmp(cHeadText, "NUM_TYPE") == 0)
			{
				// ���f���^�C�v���ǂݍ���
				sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumType);
				printf("�ǂݍ��񂾃I�u�W�F�N�g�^�C�v�� %d\n", nNumType);

				OBJINFO objInfo;
				int nCntModel = 0;
				while (nCntModel != nNumType)
				{
					// ��s�ǂݍ���
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					// �t�@�C�����ǂݍ���
					if (strcmp(cHeadText, "MODEL_FILENAME") == 0)
					{
						// ���f�����擾
						if (SUCCEEDED(sscanf(cReadText, "%s %s %s",
							&cDieText,
							&cDieText,
							&objInfo.modelInfo.cModelName[0])))
						{
							// �ǂݍ��񂾃t�@�C������\��
							printf("���f�� %s ��ǂݍ���\n", &objInfo.modelInfo.cModelName[0]);
							// �e�N�X�`������
							objInfo.modelInfo.bTex = false;
							// �I�u�W�F�N�g����ۑ�
							m_objInfo.push_back(objInfo);
							// ���f���������Z
							nCntModel++;
						}
					}
				}
			}
			// �e�N�X�`���ԍ���������
			else if (strcmp(cHeadText, "NUM_TEXTURE") == 0)
			{
				// �e�N�X�`�����ǂݍ���
				sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &m_nNumTexture);
				printf("�ǂݍ��񂾃e�N�X�`���� %d\n", m_nNumTexture);

				if (m_nNumTexture > 0)
					m_pModelIndex = new int[m_nNumTexture];	// �e�N�X�`�������蓖�Ă郂�f���ԍ�

				int nCntTex = 0;
				// �ǂݍ��񂾃e�N�X�`�������ݒ萔�ɂȂ�܂ŌJ��Ԃ�
				while (nCntTex != m_nNumTexture)
				{
					// ��s�ǂݍ���
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					// �t�@�C�����ǂݍ���
					if (strcmp(cHeadText, "TEXTURE_FILENAME") == 0)
					{
						int nModel = 0;
						char cFileName[MAX_TEXT];
						// ���f���ԍ��擾
						if (SUCCEEDED(sscanf(cReadText, "%s %s %s : %s %s %d",
							&cDieText,		// TEX_FILE
							&cDieText,		// =
							&cFileName[0],	// �e�N�X�`����
							&cDieText,		// MODEL
							&cDieText,		// =
							&nModel)))		// ���f���ԍ�
						{
							// �e�N�X�`������ۑ�
							strcpy(m_objInfo[nModel].modelInfo.cTextureName, cFileName);
							// ���f���ԍ���ۑ�
							m_pModelIndex[nCntTex] = nModel;
							// �ǂݍ��񂾃t�@�C������\��
							printf("�e�N�X�`�� %s ��ǂݍ���\n", &m_objInfo[nModel].modelInfo.cTextureName[0]);
							// �e�N�X�`���������Z
							nCntTex++;
						}
					}
				}
			}
			// �L�����N�^�[�Z�b�g��������
			else if (strcmp(cHeadText, "NUM_OBJECT") == 0)
				// ���f���^�C�v���̎擾
				sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumObj);
		}
	}

	// �t�@�C�������
	fclose(pFile);

	// �I�u�W�F�N�g������\��
	printf("�ǂݍ��񂾃I�u�W�F�N�g���� %d\n", nNumObj);
	// ���f�������J��Ԃ�
	for (int nCntModel = 0; nCntModel < nNumObj; nCntModel++)
		// �������̃������m��
		m_pObject.push_back(CObject::Create());

	CKananLibrary::EndBlockComment("�I�u�W�F�N�g�t�@�C���̓ǂݍ��ݏI������");

	// ����
	return S_OK;
}*/