//==================================================================================================================
//
// UI[UI.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _UI_H_
#define _UI_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CScene2D;

//==================================================================================================================
//
// ���S�N���X�̒�`
//
//==================================================================================================================
class CUI : public CScene
{
public:
	//=============================================================================
	// �񋓌^��`
	//=============================================================================
	typedef enum
	{
		LOGOTYPE_TITLE = 0,			// �^�C�g��
		LOGOTYPE_ENTER,				// �G���^�[���S
		LOGOTYPE_ARROW,				// �R���p�X���
		LOGOTYPE_MAX				// �ő�
	} UITYPE;

	CUI(PRIORITY type);				// �R���X�g���N�^
	~CUI();							// �f�X�g���N�^
	void Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	static CUI *Create(void);		// ��������
	static HRESULT Load(void);		// �e�N�X�`����񃍁[�h����
	static void Unload(void);		// �e�N�X�`�����A�����[�h����

	void SetUI(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nCnt, D3DXCOLOR col);	// ���S�ݒ菈��

	UITYPE GetType(void);			// ���S�^�C�v�擾����

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[LOGOTYPE_MAX];		// �e�N�X�`�����
	static char *m_apFileName[LOGOTYPE_MAX];				// ���S�̃t�@�C����

	UITYPE m_type;											// ���S�^�C�v�ϐ�
	CScene2D *m_pScene2D[LOGOTYPE_MAX];						// scene2D�̏��

	D3DXVECTOR3 TitlePos;									// �^�C�g���̈ʒu

	int m_nCntBound;										// �^�C�g��UI�o�E���h�J�E���^

	float m_nCntUITitle0;									// �^�C�g��UI�p�J�E���^0
	float m_nCntUITitle1;									// �^�C�g��UI�p�J�E���^1
	float m_fWidth;											// �c��
	float m_fSize;											// ����

	bool m_bUITitle0;										// �^�C�g���𓮂������ǂ���0
	bool m_bUITitle1;										// �^�C�g���𓮂������ǂ���1
};
#endif