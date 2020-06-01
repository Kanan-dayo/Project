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
#define ZeroVector2		(D3DXVECTOR2(0.0f, 0.0f))
#define OneVector2		(D3DXVECTOR2(1.0f, 1.0f))
#define ZeroVector3		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define OneVec2Zero		(D3DXVECTOR3(1.0f, 1.0f, 0.0f))
#define ZeroVector4		(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
#define ZeroColor		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))
#define AlphaColor		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
#define WhiteColor		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define BlackColor		(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))
#define AbobeNormal		(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
#define MAX_TEXT		(128)

// ===================================================================
// �\���̒�`
// ===================================================================

// ===================================================================
// �N���X��`
// ===================================================================
class CKeyboard;
class CXGamepad;

class CKananLibrary
{
public:
	CKananLibrary() {};
	~CKananLibrary() {};

	static void CalcMatrix(D3DXMATRIX *pMtx, const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot);			// �}�g���b�N�X�v�Z
	static void ReleaseModelInfo(MODELINFO *pModelInfo);												// ���f�����̔j��
	static void Billboard(D3DXMATRIX *mtxWorld, const D3DXMATRIX mtxView);								// �r���{�[�h������
	static void InterpolationRot(D3DXVECTOR3 *rot);														// ��]�̕��
	static void InertiaMove(D3DXVECTOR3 *move);															// �����̏���
	static void IntegerUpperLimit(int *nValue, int upperLimit);											// int�^�̏��
	static void IntegerLowerLimit(int *nValue, int lowerLimit);											// int�^�̉���
	static bool LimitVector3(D3DXVECTOR3 *Value, const D3DXVECTOR3 lowerLimit, const D3DXVECTOR3 upperLimit);		// ��������̐�������
	static void LimitLoopVector3(D3DXVECTOR3 *Value, const D3DXVECTOR3 lowerLimit, const D3DXVECTOR3 upperLimit);	// ��������̃��[�v����
	static void SetFog(const float fStartPos, const float fEndPos, const D3DXCOLOR col);							// �t�H�O�̐���
	static void PrintBlockCommentFrame(void)