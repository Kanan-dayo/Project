//=============================================================================
//
// ���f���L�����N�^�[����  [ modelCharacter.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "modelcharacter.h"
#include "modelparts.h"
#include "manager.h"
#include "renderer.h"
#include "Inputkeyboard.h"
#include "debugproc.h"
#include "sceneX.h"
#include "motion.h"
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
MODELCHARACTER	CModelCharacter::m_pModelCharacter[CHARACTER_MAX] = {};
char			CModelCharacter::m_aFileName[CHARACTER_MAX][64] =
{
	{ "data/OFFSET/offset_man.txt" },
	{ "data/OFFSET/offset_fish00.txt" },
	{ "data/OFFSET/offset_rob.txt" }
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CModelCharacter::CModelCharacter()
{
	// ������
	m_pModelParts = nullptr;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CModelCharacter::~CModelCharacter()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CModelCharacter::Init()
{
	// ���f������������
	m_pModelParts = new CModelParts[m_pModelCharacter[m_type].nNumParts];

	for (int nCnt = 0; nCnt < m_pModelCharacter[m_type].nNumParts; nCnt++)
	{
		// ������
		m_pModelParts[nCnt].Init();

		// ���f�����ݒ�
		m_pModelParts[nCnt].BindModel(m_pModelCharacter[m_type].pModelInfo[nCnt].matBuff, m_pModelCharacter[m_type].pModelInfo[nCnt].matNum, m_pModelCharacter[m_type].pModelInfo[nCnt].mesh);
	}
	// �p�[�c�̃I�t�Z�b�g�擾
	LoadOffset(m_type);

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CModelCharacter::Uninit()
{
	// nullcheck
	if (m_pModelParts)
	{
		// �j��
		delete[] m_pModelParts;
		m_pModelParts = nullptr;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CModelCharacter::Update()
{
	// �t���[�����Z
	m_nFrame++;

	// �t���[�������l�܂ŗ�����
	if (m_nFrame >= CMotion::GetFrame(m_motion, m_nKey))
	{
		// �t���[��������
		m_nFrame = 0;

		// �L�[���Z
		m_nKey++;

		// �L�[�����l�܂ŗ�����
		if (m_nKey >= CMotion::GetNumKey(m_motion))
		{
			//�t���[���ƃL�[������
			ResetMotion();

			// ���[�v���Ȃ���
			if (!CMotion::GetLoop(m_motion))
			{
				// �j���[�g�����ɖ߂�
				m_motion = CMotion::PLAYER_NEUTRAL;
			}
		}

		// ���̃��[�V���������Z�b�g
		SetMotion(m_motion);
	}

	// ���f�������J��Ԃ�
	for (int nCnt = 0; nCnt < m_pModelCharacter[m_type].nNumParts; nCnt++)
	{
		// nullcheck
		if (&m_pModelParts[nCnt])
		{
			// �X�V
			m_pModelParts[nCnt].Update();
		}
	}

#ifdef _DEBUG
	// ImGui�̍X�V
	ShowModelCharaInfo();
#endif
}

//=============================================================================
// �`��	
//=============================================================================
void CModelCharacter::Draw()
{
	// ���f�������J��Ԃ�
	for (int nCnt = 0; nCnt < m_pModelCharacter[m_type].nNumParts; nCnt++)
	{
		// nullcheck
		if (&m_pModelParts[nCnt])
		{
			// �`��
			m_pModelParts[nCnt].Draw();
		}
	}
}

//=============================================================================
// ����
//=============================================================================
CModelCharacter *CModelCharacter::Create(CHARACTER_TYPE modeltype)
{
	// �������m��
	CModelCharacter *pModelCharacter = new CModelCharacter;

	// �^�C�v�̐ݒ�
	pModelCharacter->m_type = modeltype;

	// ������
	pModelCharacter->Init();

	return pModelCharacter;
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CModelCharacter::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �L�����N�^�[������
	for (int nCntModel = 0; nCntModel < CHARACTER_MAX; nCntModel++)
	{
		// ���f�����擾
		LoadFileName((CHARACTER_TYPE)nCntModel);

		// �e�N�X�`��������
		for (int nCntTex = 0; nCntTex < m_pModelCharacter[nCntModel].nNumTexture; nCntTex++)
		{
			// �p�[�c������
			for (int nCntParts = 0; nCntParts < m_pModelCharacter[nCntModel].nNumParts; nCntParts++)
			{
				// �e�N�X�`������
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					&m_pModelCharacter[nCntModel].pModelInfo[nCntTex].cTextureName[0],
					&m_pModelCharacter[nCntModel].pModelInfo[nCntParts].pTexture)))
				{
					// �ł��Ȃ���Ύ��s
					char cText[128];
					sprintf(cText, "�e�N�X�`���������s (�L�����N�^�[ %d, �e�N�X�`�� %d)", nCntModel, nCntTex);
					printf("%s\n", &cText[0]);
					return E_FAIL;
				}
			}
		}

		// �p�[�c������
		for (int nCntParts = 0; nCntParts < m_pModelCharacter[nCntModel].nNumParts; nCntParts++)
		{
			// ���f������
			if (FAILED(D3DXLoadMeshFromX(&m_pModelCharacter[nCntModel].pModelInfo[nCntParts].cModelName[0],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_pModelCharacter[nCntModel].pModelInfo[nCntParts].matBuff,
				NULL,
				&m_pModelCharacter[nCntModel].pModelInfo[nCntParts].matNum,
				&m_pModelCharacter[nCntModel].pModelInfo[nCntParts].mesh)))
			{
				// �ł��Ȃ���Ύ��s
				char cText[128];
				sprintf(cText, "���f���������s (�L�����N�^�[ %d, �p�[�c %d)", nCntModel, nCntParts);
				printf("%s\n", &cText[0]);
				return E_FAIL;
			}
		}
	}

	// ����
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CModelCharacter::Unload(void)
{
	for (int nCntModel = 0; nCntModel < CHARACTER_MAX; nCntModel++)
	{
		// �����[�X���s��
		for (int nCnt = 0; nCnt < m_pModelCharacter[nCntModel].nNumParts; nCnt++)
		{
			CKananLibrary::ReleaseModelInfo(&m_pModelCharacter[nCntModel].pModelInfo[nCnt]);
		}

		if (m_pModelCharacter[nCntModel].pModelInfo)
		{
			delete[] m_pModelCharacter[nCntModel].pModelInfo;
			m_pModelCharacter[nCntModel].pModelInfo = nullptr;
		}
	}
}

//=============================================================================
// �L�����N�^�[�̃}�g���b�N�X�ݒ�
//=============================================================================
void CModelCharacter::SetCharacterMtx(D3DXMATRIX *mtx)
{
	// ���f��������
	for (int nCnt = 0; nCnt < m_pModelCharacter[m_type].nNumParts; nCnt++)
	{
		// �e�����Ȃ���
		if (m_pModelParts[nCnt].GetParent() == -1)
		{
			// �匳�̃}�g���b�N�X�ݒ�
			m_pModelParts[nCnt].SetParentMtx(mtx);
		}
		else
		{
			// �e�p�[�c�̃}�g���b�N�X�ݒ�	
			m_pModelParts[nCnt].SetParentMtx(m_pModelParts[m_pModelParts[nCnt].GetParent()].GetMatrix());
		}
	}
}

//=============================================================================
// ���[�V�������擾
//=============================================================================
CMotion::MOTION_TYPE CModelCharacter::GetMotion(void)
{
	return m_motion;
}

//=============================================================================
// ���f���p�[�c�̎擾
//=============================================================================
CModelParts *CModelCharacter::GetModelParts(void)
{
	return m_pModelParts;
}

//=============================================================================
// ���[�V�����Z�b�g
//=============================================================================
void CModelCharacter::SetMotion(CMotion::MOTION_TYPE motiontype)
{
	m_motion = motiontype;

	// ���f�������J��Ԃ�
	for (int nCnt = 0; nCnt < m_pModelCharacter[m_type].nNumParts; nCnt++)
	{
		// nullcheck
		if (&m_pModelParts[nCnt])
		{
			m_pModelParts[nCnt].SetMotionRotDest(motiontype, m_nKey);
		}
	}
}

//=============================================================================
// �I�t�Z�b�g�ǂݍ���
//=============================================================================
HRESULT CModelCharacter::LoadOffset(CHARACTER_TYPE type)
{
	// �ϐ��錾
	FILE *pFile;
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nCntParts = 0;

	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	int nParent;

	// �t�@�C�����J��
	pFile = fopen(&m_aFileName[type][0], "r");

	// nullcheck
	if (pFile)
	{
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
				// �L�����N�^�[�Z�b�g��������
				else if (strcmp(cHeadText, "CHARACTERSET") == 0)
				{
					// �G���h�L�����N�^�[�Z�b�g������܂ŌJ��Ԃ�
					while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);
						// ���s
						if (strcmp(cHeadText, "\n") == 0)
						{
						}
						// �p�[�c�Z�b�g��������
						else if (strcmp(cHeadText, "PARTSSET") == 0)
						{
							// �G���h�p�[�c�Z�b�g������܂ŌJ��Ԃ�
							while (strcmp(cHeadText, "END_PARTSSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								int nBeWeapon = 0;
								float fRadius = 0.0f;
								//	�y�A�����g
								if (strcmp(cHeadText, "PARENT") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nParent);
								}
								//	���킩�ǂ���
								if (strcmp(cHeadText, "WEAPON") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nBeWeapon);
								}
								//	�����蔻��̔��a
								if (strcmp(cHeadText, "RADIUS") == 0)
								{
									sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fRadius);
								}
								// �ʒu
								if (strcmp(cHeadText, "POS") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pos.x, &pos.y, &pos.z);
								}
								// ��]
								if (strcmp(cHeadText, "ROT") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &rot.x, &rot.y, &rot.z);
								}
								if (strcmp(cHeadText, "END_PARTSSET") == 0)
								{
									if (m_pModelCharacter[type].nNumTexture > 0)
									{
										// �e�N�X�`���t���̃p�[�c���i�[
										m_pModelParts[nCntParts].SetPartsTexInfo(nCntParts, nParent, pos, rot, m_pModelCharacter[type].pModelInfo[nCntParts].pTexture);
									}
									else
									{
										// �e�N�X�`���Ȃ��̃p�[�c���i�[
										m_pModelParts[nCntParts].SetPartsInfo(nCntParts, nParent, pos, rot);
									}

									if (nBeWeapon == 1)
									{

									}

									// �p�[�c�����Z
									nCntParts++;
								}
							}
						}
					}
				}
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}

	// �t�@�C�����J���Ȃ�������
	else
	{
		printf("�I�t�Z�b�g�t�@�C�����J���܂���ł����B\n");
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// ���f�����E���f�����ǂݍ���
//=============================================================================
HRESULT CModelCharacter::LoadFileName(CHARACTER_TYPE type)
{
	// �ϐ��錾
	FILE *pFile;
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nNumModel = 0;
	int nNumTexture = 0;
	int nCntModel = 0;
	int nCntTexture = 0;

	// �t�@�C�����J��
	pFile = fopen(&m_aFileName[type][0], "r");

	// nullcheck
	if (pFile)
	{
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
				// ���f���ԍ���������
				else if (strcmp(cHeadText, "NUM_MODEL") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumModel);

					m_pModelCharacter[type].pModelInfo = new MODELINFO[nNumModel];
					m_pModelCharacter[type].nNumParts = nNumModel;

					// ���f���������
					if (nNumModel > 0)
					{
						// ���f�������J��Ԃ�
						while (1)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);
							// �t�@�C�����ǂݍ���
							if (strcmp(cHeadText, "MODEL_FILENAME") == 0)
							{
								// ���f�����擾
								sscanf(cReadText, "%s %s %s %s %s", &cDieText, &cDieText, m_pModelCharacter[type].pModelInfo[nCntModel].cModelName, &cDieText, &cDieText);

								// ���f���J�E���g���Z
								nCntModel++;

								// ���f���J�E���g�����f�������ɂȂ�����
								if (nCntModel == nNumModel)
								{
									// ���[�v�𔲂���
									break;
								}
							}
						}
					}
				}
				// �e�N�X�`���ԍ���������
				else if (strcmp(cHeadText, "NUM_TEXTURE") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumTexture);

					m_pModelCharacter[type].nNumTexture = nNumTexture;

					// �e�N�X�`���������
					if (nNumTexture > 0)
					{
						// �e�N�X�`�������J��Ԃ�
						while (1)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);
							// �t�@�C�����ǂݍ���
							if (strcmp(cHeadText, "TEXTURE_FILENAME") == 0)
							{
								// �e�N�X�`�����擾
								sscanf(cReadText, "%s %s %s %s %s", &cDieText, &cDieText, m_pModelCharacter[type].pModelInfo[nCntTexture].cTextureName, &cDieText, &cDieText);

								// �e�N�X�`���J�E���g���Z
								nCntTexture++;

								// �e�N�X�`���J�E���g���e�N�X�`�������ɂȂ�����
								if (nCntTexture == nNumTexture)
								{
									// ���[�v�𔲂���
									break;
								}
							}
						}
					}
				}
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}

	// �t�@�C�����J���Ȃ������Ƃ�
	else
	{
		printf("���f���t�@�C�����J���܂���ł����B\n");
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// ���[�V������񃊃Z�b�g
//=============================================================================
void CModelCharacter::ResetMotion()
{
	m_nFrame = 0;
	m_nKey = 0;
}

//=============================================================================
// �L�����N�^�[�̃��f�������擾
//=============================================================================
int CModelCharacter::GetPartsNum(CHARACTER_TYPE type)
{
	return m_pModelCharacter[type].nNumParts;
}

#ifdef _DEBUG
//=============================================================================
// ImGui�̍X�V
//=============================================================================
void CModelCharacter::ShowModelCharaInfo(void)
{
	// ���݂̃t���[������\��
	/*ImGui::Text("nFrame : %d / %d", m_nFrame, CMotion::GetFrame(m_motion, m_nKey));
	// ���݂̃L�[����\��
	ImGui::Text("nKey : %d / %d", m_nKey, CMotion::GetNumKey(m_motion));*/
}
#endif