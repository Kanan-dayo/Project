//==================================================================================================================
//
// �v���C���[[player.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "sceneX.h"
#include "fade.h"
#include "character.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define TEXTURE_PLAYER "data/TEXTURE/field000.jpg"		// �ǂݍ��ރe�N�X�`���̃\�[�X��
#define PLAYER_MODEL "data/MODEL/testmodel.x"			// �ǂݍ��ރ��f���̃\�[�X��
#define PLAYER_MAX_MODEL (6)							// player.cpp���̃��f���̃p�[�c��

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CMotionModel;
class CMeshField;
class CInputKeyboard;
class CInputGamepad;
class CFade;

//==================================================================================================================
//
// �v���C���[�N���X�̒�`
//
//==================================================================================================================
class CPlayer : public CCharacter
{
public:
	// ���[�V�����̃^�C�v
	typedef enum
	{
		PLAYER_MOTION_NORMAL = 0,			// �j���[�g����
		PLAYER_MOTION_WALK,					// ����
		PLAYER_MOTION_ACTION,				// �A�N�V����
		PLAYER_MOTION_JUMP,					// �W�����v
		PLAYER_MOTION_LANDING,				// ���n
		PLAYER_MOTION_DAMAGE,				// �_���[�W
		PLAYER_MOTION_MAX					// ���[�V�����̍ő吔
	}PLAYER_MOTION_STATE;

	CPlayer(PRIORITY type);							// �R���X�g���N�^
	~CPlayer();										// �f�X�g���N�^
	void Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static CPlayer *Create(void);					// ��������

protected:

private:
#ifdef _DEBUG
	void ShowDebugInfo(void);									// ImGui�̍X�V
#endif
};
#endif