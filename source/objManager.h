//=============================================================================
//
// �I�u�W�F�N�g�}�l�[�W���[����  [ objectManager.h ]
// Author : KANAN NAGANAWA
//
//=============================================================================
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "object.h"
#include "scene.h"
#include <vector>
#include <memory>							// �X�}�[�g�|�C���^�̎g�p�ɕK�v
#include "kananlibrary.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CObject;

class CObjectManager : public CScene
{
public:
	CObjectManager(CScene::PRIORITY nPriority);	// �R���X�g���N�^
	~CObjectManager();	// �f�X�g���N�^

	void Init();								// ������
	void Uninit();								// �I��
	void Update();								// �X�V
	void Draw();								// �`��
	static CObjectManager *Create(void);		// ����

	static HRESULT Load(void);					// ���f���̃��[�h
	static void Unload(void);					// ���f���̔j��

	static MODEL_VTX GetModelVtx(const int & nType) { return m_objInfo[nType].modelVtx; }	// �^�C�v���Ƃ̃��f�����_���̎擾

	std::vector<CObject*> GetObj(void) { return m_pObject; }					// �I�u�W�F�N�g�̎擾
	int		GetNumObject(void) { return (int)m_pObject.size(); }		// �I�u�W�F�N�g�����̎擾

#ifdef _DEBUG
	void ShowObjectManagerInfo(void);			// ImGui�̍X�V
#endif

private:
	HRESULT LoadOffset(void);					// �I�t�Z�b�g�ǂݍ���
	static HRESULT LoadFileName(void);			// ���f�����ǂݍ���

	static std::vector<CObject*>	m_pObject;				// �I�u�W�F�N�g�̃|�C���^
	static std::vector<OBJINFO>		m_objInfo;				// ���f���̏ڍ�
	static char						m_aFileName[MAX_TEXT];	// ���f���z�u�̃t�@�C����
	static int	m_nNumTexture;					// �e�N�X�`���̑���
	static int  *m_pModelIndex;					// �e�N�X�`�������蓖�Ă郂�f���̔ԍ�

#ifdef _DEBUG
	// �f�o�b�O���[�h�̍\����
	typedef enum
	{
		MODE_GAME = 0,	// �Q�[��
		MODE_DEBUG		// �f�o�b�O
	} DEBUG_MODE;

	HRESULT SaveObject(void);						// �I�u�W�F�N�g���̃Z�[�u

	static int	m_stateMode;						// ���[�h�̏��
	static bool m_bShowAnother;						// �ʂ̃E�B���h�E
	CObject		*m_pFakeObject;						// �U�̃I�u�W�F�N�g
	static bool m_bObjUse;							// �U�I�u�W�F���g�p���Ă��邩
	static int	m_nFakeType;						// �U�I�u�W�F�̃^�C�v
	static std::string	*m_pObjName;				// ImGui�p�̃I�u�W�F�N�g��
#endif
};
#endif