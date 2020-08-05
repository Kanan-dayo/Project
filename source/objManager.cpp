//=============================================================================
//
// �I�u�W�F�N�g�}�l�[�W���[����  [ objManager.cpp ]
// Author : KANAN NAGANAWA
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "objManager.h"
#include "manager.h"
#include "renderer.h"
#include "Inputkeyboard.h"
#include "debugproc.h"
#include "mouse.h"
#include "camera.h"
#include "game.h"
#include "ImGui/imgui.h"				// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_dx9.h"		// Imgui�̎����ɕK�v
#include "ImGui/imgui_impl_win32.h"		// Imgui�̎����ɕK�v

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �ÓI�����o�ϐ��̏�����
//=============================================================================
char					CObjectManager::m_aFileName[MAX_TEXT] = "data/OFFSET/offset_object.txt";
std::vector<CObject*>	CObjectManager::m_pObject = {};
std::vector<OBJINFO>	CObjectManager::m_objInfo = {};
int						CObjectManager::m_nNumTexture = 0;
int						*CObjectManager::m_pModelIndex = {};

#ifdef _DEBUG
int						CObjectManager::m_nFakeType = 0;
int						CObjectManager::m_stateMode = CObjectManager::MODE_GAME;
bool					CObjectManager::m_bObjUse = false;
bool					CObjectManager::m_bShowAnother = false;
std::string				*CObjectManager::m_pObjName = {};
#endif

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectManager::CObjectManager(PRIORITY type = CScene::PRIORITY_OBJECT) : CScene(type)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectManager::~CObjectManager()
{

}

//=============================================================================
// ������
//=============================================================================
void CObjectManager::Init()
{
	// �p�[�c�̃I�t�Z�b�g�擾
	LoadOffset();
}

//=============================================================================
// �I��
//=============================================================================
void CObjectManager::Uninit()
{
#ifdef _DEBUG
	if (m_pFakeObject)
	{
		m_pFakeObject->Uninit();
		delete m_pFakeObject;
		m_pFakeObject = nullptr;
	}

	// �j��
	delete[] m_pObjName;
	m_pObjName = nullptr;
#endif

	// �T�C�Y���J��Ԃ� (size_t = unsigned, vector.size()�Ń���������Ԃ�)
	for (size_t nCnt = 0; nCnt < m_pObject.size(); nCnt++)
	{
		// �������폜
		delete m_pObject[nCnt];
	}
	// ���g���Ȃ���
	m_pObject.clear();
}

//=============================================================================
// �X�V
//=============================================================================
void CObjectManager::Update()
{
	// ���f�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pObject.size(); nCnt++)
	{
		// nullcheck
		if (m_pObject[nCnt])
			m_pObject[nCnt]->Update();
	}

#ifdef _DEBUG
	if (m_pFakeObject)
	{
		m_pFakeObject->Update();
	}
	// ImGui�̍X�V
	ShowObjectManagerInfo();
#endif
}

//=============================================================================
// �`��	
//=============================================================================
void CObjectManager::Draw()
{
	// ���f�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pObject.size(); nCnt++)
	{
		// nullcheck
		if (m_pObject[nCnt])
			m_pObject[nCnt]->Draw();
	}

#ifdef _DEBUG
	if (m_pFakeObject)
		m_pFakeObject->DrawAlpha();
#endif
}

//=============================================================================
// ����
//=============================================================================
CObjectManager *CObjectManager::Create(void)
{
	// �������m��
	CObjectManager *pMana = new CObjectManager();

	// nullcheck
	if (!pMana)
	{
		// ���s
		std::cout << "�I�u�W�F�N�g�}�l�[�W���[�������s" << std::endl;
		return nullptr;
	}

	// ������
	pMana->Init();

	// ����
	return pMana;
}

//=============================================================================
// ���[�h
//=============================================================================
HRESULT CObjectManager::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���f�����擾
	LoadFileName();

	// �e�N�X�`��������
	for (int nCnt = 0; nCnt < m_nNumTexture; nCnt++)
	{
		// �e�N�X�`������
		if (FAILED(D3DXCreateTextureFromFile(pDevice,
			m_objInfo[m_pModelIndex[nCnt]].modelInfo.cTextureName,
			&m_objInfo[m_pModelIndex[nCnt]].modelInfo.pTexture)))
		{
			// �ł��Ȃ���Ύ��s
			char cText[MAX_TEXT];
			sprintf(cText, "�I�u�W�F�N�g�e�N�X�`���������s (%s)", &m_objInfo[m_pModelIndex[nCnt]].modelInfo.cTextureName[0]);
			printf("%s\n", &cText[0]);
			return E_FAIL;
		}
	}

#ifdef _DEBUG
	// �I�u�W�F�N�g���̃������m��
	m_pObjName = new std::string[(int)m_objInfo.size()];
#endif

	// ��ސ�����
	for (size_t nCnt = 0; nCnt < m_objInfo.size(); nCnt++)
	{
		// ���f�����̐���
		CKananLibrary::CreateModelInfo(&m_objInfo[nCnt].modelInfo);

		// ���f���̒��_���W�̍ő�E�ŏ������߂�
		m_objInfo[nCnt].modelVtx =
			CKananLibrary::OutputModelVtxColl(m_objInfo[nCnt].modelInfo.mesh);

#ifdef _DEBUG
		// ���f���̃p�X���擾
		std::string modelName = m_objInfo[nCnt].modelInfo.cModelName;
		// ���f�����̂ݕۑ�
		m_pObjName[nCnt] = modelName.substr(12);
#endif
	}
	// ����
	return S_OK;
}

//=============================================================================
// �A�����[�h
//=============================================================================
void CObjectManager::Unload(void)
{
	// nullcheck
	if (m_pModelIndex)
	{
		// �j��
		delete m_pModelIndex;
		m_pModelIndex = nullptr;
	}
}

//=============================================================================
// �I�t�Z�b�g�ǂݍ���
//=============================================================================
HRESULT CObjectManager::LoadOffset(void)
{
	// �ϐ��錾
	FILE *pFile = nullptr;
	char cReadText[MAX_TEXT] = "";
	char cHeadText[MAX_TEXT] = "";
	char cDieText[MAX_TEXT] = "";

	D3DXVECTOR3 pos = ZeroVector3;
	D3DXVECTOR3 rot = ZeroVector3;
	bool		bCollision = false;
	int			nUseTex = 99;
	int			nType = 0;
	int			nModel = 0;

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
			{
			}
			// �I�u�W�F�N�g�Z�b�g��������
			if (strcmp(cHeadText, "OBJECTSET") == 0)
			{
				// �G���h�I�u�W�F�N�g�Z�b�g������܂ŌJ��Ԃ�
				while (strcmp(cHeadText, "END_OBJECTSET") != 0)
				{
					bCollision = false;
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					// ���
					if (strcmp(cHeadText, "TYPE") == 0)
						sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nType);
					// �ʒu
					if (strcmp(cHeadText, "POS") == 0)
						sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pos.x, &pos.y, &pos.z);
					// ��]
					if (strcmp(cHeadText, "ROT") == 0)
						sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &rot.x, &rot.y, &rot.z);
					// �����蔻��
					if (strcmp(cHeadText, "COLLISION_ON") == 0)
						bCollision = true;
				}

				// ���f�����i�[
				m_pObject[nModel]->SetObjInfo(pos, rot, &m_objInfo[nType].modelInfo, nType, bCollision);



				// ���f���������Z
				nModel++;
			}
		}
	}

	// �t�@�C�������
	fclose(pFile);

	// �u���b�N�R�����g
	CKananLibrary::EndBlockComment("�I�u�W�F�N�g�t�@�C���̓ǂݍ��ݐ����B");

	// ����
	return S_OK;
}

//=============================================================================
// �I�u�W�F�N�g�t�@�C���ǂݍ���
//=============================================================================
HRESULT CObjectManager::LoadFileName(void)
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
}

#ifdef _DEBUG
//=============================================================================
// ImGui�̍X�V
//=============================================================================
void CObjectManager::ShowObjectManagerInfo(void)
{
	// �E�B���h�E��\�����邩
	ImGui::Checkbox("show object window", &m_bShowAnother);

	// �\������
	if (!m_bShowAnother)
	{
		return;
	}

	// ImGui�̍X�V�J�n
	ImGui::Begin("object window", &m_bShowAnother);

	// �J�����̎擾
	CCamera *pCamera = CManager::GetRenderer()->GetGame()->GetCamera();

	// �Z�[�u�{�^��
	if (ImGui::Button("save object offset"))
	{
		// �Z�[�u������
		if (SaveObject() == S_OK)
		{
			// �}�E�X�̎擾
			CMouse *pMouse = CManager::GetMouse();
			// �E�B���h�E�n���h���̎擾
			HWND hWnd = pMouse->GetWnd();
			// �m�F�̃��b�Z�[�W
			MessageBox(hWnd, "�I�u�W�F�N�g�t�@�C�����Z�[�u���܂���", "�m�F", MB_OK);
		}
	}

	// �Q�[�����[�h�ɐ؂�ւ�
	if (ImGui::RadioButton("GAME", &m_stateMode, MODE_GAME))
	{
		if (m_bObjUse)
		{
			delete m_pFakeObject;
			m_pFakeObject = nullptr;
			m_bObjUse = false;
		}
	}
	// ���s���Ȃ�
	ImGui::SameLine();
	// �f�o�b�O���[�h�ɐ؂�ւ�
	if (ImGui::RadioButton("DEBUG", &m_stateMode, MODE_DEBUG))
	{
		// �U�I�u�W�F���g���Ă��Ȃ�
		if (!m_bObjUse)
		{
			// �������Ďg�p
			m_pFakeObject = new CObject();
			m_bObjUse = true;
		}

		// �U�I�u�W�F�����݂���
		if (m_pFakeObject)
		{
			// �f�t�H���g�^�C�v�Ƃ��ď�����
			m_pFakeObject->Init();

			// �������f����ݒ�
			m_pFakeObject->SetObjInfo(*pCamera->GetPosR(), ZeroVector3, &m_objInfo[0].modelInfo, 0, false);
		}
	}

	if (m_stateMode == MODE_GAME)
	{
		// ���[�h�̏ڍׂ�\��
		ImGui::Text("This mode displays the details of the object.");
		ImGui::Dummy(ImVec2(0.0f, 10.0f));
	}
	else if (m_stateMode == MODE_DEBUG)
	{
		// ���[�h�̏ڍׂ�\��
		ImGui::Text("This mode allows you to place objects.");

		m_pFakeObject->ShowObjectInfo("FakeObject");

		// �I�u�W�F�^�C�v���ς������
		if (ImGui::InputInt("ObjectType", &m_nFakeType))
		{
			// �^�C�v�������Ȃ��悤
			if (m_nFakeType < 0)
			{
				m_nFakeType = 0;
			}
			else if (m_nFakeType >= (int)m_objInfo.size())
			{
				m_nFakeType = (int)m_objInfo.size() - 1;
			}

			// ���f�����i�[
			m_pFakeObject->SetObjInfo(*m_pFakeObject->GetPos(), *m_pFakeObject->GetRot(), &m_objInfo[m_nFakeType].modelInfo, m_nFakeType, false);
		}

		// �I�u�W�F�N�g�̐���
		if (ImGui::Button("Create"))
		{
			// �������m��
			m_pObject.push_back(CObject::Create());
			// �������E���ݒ�
			m_pObject[(int)m_pObject.size() - 1]->Init();
			// ���f�����i�[
			m_pObject[(int)(m_pObject.size() - 1)]->SetObjInfo(*m_pFakeObject->GetPos(), *m_pFakeObject->GetRot(), &m_objInfo[m_nFakeType].modelInfo, m_nFakeType, false);
		}
	}

	// ���f�������J��Ԃ�
	for (int nCnt = (int)m_pObject.size() - 1; nCnt > -1; nCnt--)
	{
		// nullcheck
		if (m_pObject[nCnt])
		{
			// �p�X��char�ɃL���X�g
			char *cObjName = new char[m_pObjName[m_pObject[nCnt]->GetType()].size() + 1];
			// ������𕡐�
			strcpy(cObjName, m_pObjName[m_pObject[nCnt]->GetType()].c_str());
			// �c���[���̐ݒ�
			char cText[32] = {};
			sprintf(cText, "Object : %d (%s)", nCnt, cObjName);
			// ImGui�̍X�V
			m_pObject[nCnt]->ShowObjectInfo(cText);
			// ��������j��
			delete cObjName;
		}

		// �����[�X���L��
		if (m_pObject[nCnt]->GetRelease())
		{
			m_pObject[nCnt]->Uninit();
			delete m_pObject[nCnt];
			// �w�肵���ԍ��̃I�u�W�F�N�g���폜 : vector.erase( vector�̎n�܂� + �w�肵���ԍ� )
			m_pObject.erase(m_pObject.begin() + nCnt);
		}
	}

	// ����{�^��
	if (ImGui::Button("close this window"))
		m_bShowAnother = false;

	// ImGui�̍X�V�I��
	ImGui::End();
}

//=============================================================================
// �I�u�W�F�N�g���̃Z�[�u
//=============================================================================
HRESULT CObjectManager::SaveObject(void)
{
	// �ϐ��錾
	FILE *pFile;

	// �e�L�X�g�t�@�C�������₷������R�����g
	char cEqual[2] = "=";

	// �ϐ����p�Ə������ݗp�̕ϐ�
	char cHeadText[MAX_TEXT];
	char cWriteText[MAX_TEXT];

	// �ʒu�E��]�̎擾�p
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	// �t�@�C�����J��
	pFile = fopen(&m_aFileName[0], "w");

	// nullcheck
	if (pFile)
	{
		fputs(COMMENT_BLOCK, pFile);													// #=====================================================
		fputs(COMMENT_BLOCK_LINE, pFile);													// #

		strcpy(cWriteText, "# �I�u�W�F�N�g�̃I�t�Z�b�g\n");
		fputs(cWriteText, pFile);													// # �I�u�W�F�N�g�̃I�t�Z�b�g

		strcpy(cWriteText, COMMENT_AUTHOR);
		fputs(cWriteText, pFile);													// # Author : KANAN NAGANAWA
		fputs(COMMENT_BLOCK_LINE, pFile);													// #
		fputs(COMMENT_BLOCK, pFile);													// #=====================================================

		strcpy(cHeadText, "SCRIPT");
		fputs(cHeadText, pFile);													// SCRIPT
		fputs(COMMENT_NEW_LINE, pFile);													// \n
		fputs(COMMENT_NEW_LINE, pFile);													// \n

																						// �X�N���v�g�������瑱����
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			fputs(COMMENT_BLOCK, pFile);													// #=====================================================

			strcpy(cWriteText, "# �I�u�W�F�N�g�^�C�v��\n");
			fputs(cWriteText, pFile);													// #�I�u�W�F�N�g�^�C�v��
			fputs(COMMENT_BLOCK, pFile);													// #=====================================================

			strcpy(cHeadText, "NUM_TYPE");
			sprintf(cWriteText, "%s %s %d\n",
				&cHeadText,
				&cEqual,
				(int)m_objInfo.size());

			fputs(cWriteText, pFile);												// NUM_TYPE = m_nNumType
			fputs(COMMENT_NEW_LINE, pFile);												// \n
			fputs(COMMENT_BLOCK, pFile);												// #=====================================================

			strcpy(cWriteText, "# ���f���t�@�C����\n");
			fputs(cWriteText, pFile);													// # ���f���t�@�C����
			fputs(COMMENT_BLOCK, pFile);													// #=====================================================

																							// �^�C�v�����J��Ԃ�
			for (size_t nCnt = 0; nCnt < m_objInfo.size(); nCnt++)
			{
				strcpy(cHeadText, "MODEL_FILENAME");
				sprintf(cWriteText, "%s %s %s\n",
					&cHeadText,
					&cEqual,
					&m_objInfo[nCnt].modelInfo.cModelName[0]);
				fputs(cWriteText, pFile);												// MODEL_FILENAME = cModelName
			}
			fputs(COMMENT_NEW_LINE, pFile);												// \n
			fputs(COMMENT_BLOCK, pFile);												// #=====================================================

			strcpy(cWriteText, "# �I�u�W�F�N�g�e�N�X�`����\n");
			fputs(cWriteText, pFile);													// # �I�u�W�F�N�g�e�N�X�`����
			fputs(COMMENT_BLOCK, pFile);													// #=====================================================

																							// �R�����g�ݒ�
			strcpy(cHeadText, "NUM_TEXTURE");
			sprintf(cWriteText, "%s %s %d\n",
				&cHeadText,
				&cEqual,
				m_nNumTexture);

			fputs(cWriteText, pFile);												// NUM_TEXTURE = m_nNumTexture
			fputs(COMMENT_NEW_LINE, pFile);												// \n

			fputs(COMMENT_BLOCK, pFile);												// #=====================================================

			strcpy(cWriteText, "# �e�N�X�`���t�@�C����\n");
			fputs(cWriteText, pFile);													// # �e�N�X�`���t�@�C����
			fputs(COMMENT_BLOCK, pFile);													// #=====================================================

			for (int nCntTex = 0; nCntTex < m_nNumTexture; nCntTex++)
			{
				strcpy(cHeadText, "TEXTURE_FILENAME");
				sprintf(cWriteText, "%s %s %d : %s %s %s\n",
					"MODEL",
					&cEqual,
					m_pModelIndex[nCntTex],
					&cHeadText,
					&cEqual,
					&m_objInfo[m_pModelIndex[nCntTex]].modelInfo.cTextureName[0]);
				fputs(cWriteText, pFile);													// TEXTURE_FILENAME = m_pNameTexture
			}
			fputs(COMMENT_NEW_LINE, pFile);												// \n
			fputs(COMMENT_BLOCK, pFile);												// #=====================================================

			strcpy(cWriteText, "# �I�u�W�F�N�g����\n");
			fputs(cWriteText, pFile);													// # �I�u�W�F�N�g����
			fputs(COMMENT_BLOCK, pFile);													// #=====================================================

			strcpy(cHeadText, "NUM_OBJECT");
			sprintf(cWriteText, "%s %s %d\n",
				&cHeadText,
				&cEqual,
				(int)m_pObject.size());
			fputs(cWriteText, pFile);														// NUM_OBJECT = m_nNumObject
			fputs(COMMENT_NEW_LINE, pFile);												// \n
			fputs(COMMENT_BLOCK, pFile);												// #=====================================================

			strcpy(cWriteText, "# �I�u�W�F�N�g���\n");
			fputs(cWriteText, pFile);													// # �I�u�W�F�N�g���
			fputs(COMMENT_BLOCK, pFile);													// #=====================================================

			for (size_t nCnt = 0; nCnt < m_pObject.size(); nCnt++)
			{
				strcpy(cWriteText, "OBJECTSET\n");
				fputs(cWriteText, pFile);													// OBJECTSET

				strcpy(cHeadText, "TYPE");
				sprintf(cWriteText, "	%s %s %d",
					&cHeadText,
					&cEqual,
					(int)m_pObject[nCnt]->GetType());
				fputs(cWriteText, pFile);													//	TYPE = GetType()
				fputs(COMMENT_NEW_LINE, pFile);												//	\n

				strcpy(cHeadText, "POS");
				sprintf(cWriteText, "	%s %s %.3f %.3f %.3f",
					&cHeadText,
					&cEqual,
					m_pObject[nCnt]->GetPos()->x,
					m_pObject[nCnt]->GetPos()->y,
					m_pObject[nCnt]->GetPos()->z);
				fputs(cWriteText, pFile);											//	POS = GetPos()
				fputs(COMMENT_NEW_LINE, pFile);											//	\n

				strcpy(cHeadText, "ROT");
				sprintf(cWriteText, "	%s %s %.3f %.3f %.3f",
					&cHeadText,
					&cEqual,
					m_pObject[nCnt]->GetRot()->x,
					m_pObject[nCnt]->GetRot()->y,
					m_pObject[nCnt]->GetRot()->z);
				fputs(cWriteText, pFile);											//	ROT = GetRot()
				fputs(COMMENT_NEW_LINE, pFile);											//	\n
				
				if (m_pObject[nCnt]->GetbColl())
				{
					strcpy(cHeadText, "COLLISION_ON");
					sprintf(cWriteText, "	%s",
						&cHeadText);
					fputs(cWriteText, pFile);											//	COLLISION_ON
					fputs(COMMENT_NEW_LINE, pFile);											//	\n
				}

				strcpy(cWriteText, "END_OBJECTSET\n");
				fputs(cWriteText, pFile);													// END_OBJECTSET
				fputs(COMMENT_NEW_LINE, pFile);												// \n
			}
			fputs(COMMENT_NEW_LINE, pFile);													// \n

			strcpy(cWriteText, "END_SCRIPT\n");
			fputs(cWriteText, pFile);														// END_SCRIPT
		}
		// �t�@�C�������
		fclose(pFile);
	}

	// �t�@�C�����J���Ȃ�������
	else
	{
		// �R���\�[���ɕ\��
		printf("�I�u�W�F�N�g�t�@�C�����J���܂���ł����B\n");
		// ���s
		return E_FAIL;
	}

	// ����
	return S_OK;
}

#endif