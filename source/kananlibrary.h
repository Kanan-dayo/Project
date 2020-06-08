// ===================================================================
//
// ���C�u�������� [ kananlibrary.h ]
// Author : KANAN NAGANAWA
//
// ===================================================================
#ifndef _KANANLIBRARY_H_
#define _KANANLIBRARY_H_

#define _CRT_SECURE_NO_WARNINGS // �x������

// ===================================================================
// �C���N���[�h�t�@�C��
// ===================================================================
#include "main.h"

// ===================================================================
// �}�N����`
// ===================================================================
// �x�N�g��
#define ZeroVector2		(D3DXVECTOR2(0.0f, 0.0f))
#define OneVector2		(D3DXVECTOR2(1.0f, 1.0f))
#define ZeroVector3		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define OneVec2Zero		(D3DXVECTOR3(1.0f, 1.0f, 0.0f))
#define ZeroVector4		(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))

// �J���[
#define ZeroColor		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))		// ���F
#define AlphaColor		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))		// ����
#define WhiteColor		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		// ��
#define BlackColor		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))		// ��

// �@��
#define AboveNormal		(D3DXVECTOR3(0.0f, 1.0f, 0.0f))			// �^��̖@���x�N�g��

// �e�L�X�g
#define MAX_TEXT		(128)									// �e�L�X�g�̍ő吔

// ����
#define INERTIA			(0.3f)									// ����

// ===================================================================
// �N���X��`
// ===================================================================
class CInputKeyboard;
class CInputGamepad;

class CKananLibrary
{
public:
	CKananLibrary() {};
	~CKananLibrary() {};

	static void CalcMatrix(D3DXMATRIX *pMtx, const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot);			// �}�g���b�N�X�v�Z

	static void InterpolationRot(D3DXVECTOR3 *rot);		// ��]�̕��
	static void InterpolationFloat(float & Float);		// float�^�̕��
	static void InertiaMove(D3DXVECTOR3 *move);			// �����̏���
	static void PrintBlockCommentFrame(void);			// �u���b�N�R�����g�g�̕\��

	static HRESULT Up(CInputKeyboard	*Key,	CInputGamepad *pGamepad);	// �����
	static HRESULT Down(CInputKeyboard	*Key,	CInputGamepad *pGamepad);	// ������
	static HRESULT Left(CInputKeyboard	*Key,	CInputGamepad *pGamepad);	// ������
	static HRESULT Right(CInputKeyboard *Key,	CInputGamepad *pGamepad);	// �E����
	static HRESULT Decide(CInputKeyboard *Key,	CInputGamepad *pGamepad);	// �������
	static HRESULT Return(CInputKeyboard *Key,	CInputGamepad *pGamepad);	// �߂����
	static HRESULT Pause(CInputKeyboard *Key,	CInputGamepad *pGamepad);	// �|�[�Y����

	static float OutputSqrt(D3DXVECTOR3 difpos);				// �������v�Z
	static float OutputDistance(D3DXVECTOR3 difpos);			// �����v�Z

#ifdef _DEBUG
	static void ShowDebugInfo(void);					// ImGui�̍X�V
	static bool GetWire(void) { return m_WireFrame; }	// ���C���[�t���[���`��̎擾
#endif

private:

#ifdef _DEBUG
	static bool m_WireFrame;			// ���C���[�t���[���`��̐؂�ւ��p
	static int m_nCulling;				// �J�����O�̐؂�ւ��p
#endif

};
#endif