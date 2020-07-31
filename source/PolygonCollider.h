//*************************************************************************************************************
//
// �|���S���R���C�_�[����[PolygonCollider.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
#ifndef _POLYGONCOLLIDER_H_
#define _POLYGONCOLLIDER_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "Scene.h"
#include "Mylibrary.h"

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#define POLYCOLLI_USE_VTX	4

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CPolygonCollider : public CScene
{
public:
	enum
	{
		POLYCOLLI_STAIRS = 0,		// �K�i
		POLYCOLLI_STAIRS_TOP,		// �K�i�̏㕔
		POLYCOLLI_LONGSTAIRS,		// �ɂ₩�ȊK�i
		POLYCOLLI_LONGSTAIRS_TOP,	// �ɂ₩�ȊK�i�̏㕔
		POLYCOLLI_MAX				// �ő�
	};



	CPolygonCollider() : CScene(PRIORITY_COLLISION) {}			// �R���X�g���N�^
	~CPolygonCollider() {}										// �f�X�g���N�^

	static CPolygonCollider* Create(int nType);					// ����

	void Init(void);											// ������
	void Uninit(void);											// �I��
	void Update(void) {};										// �X�V
	void Draw(void);											// �`��

	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pOut_Intersect, D3DXVECTOR3* SurfaceNor, bool bReflection);		// �Փ˔���

	bool Test3DInsidePolygon(D3DXVECTOR3 *pPos);				// �|���S���̒��ɂ��邩�e�X�g

private:
	void SetVtxPos(D3DXVECTOR3 *pVertexsPos);					// ���_�ʒu�̐ݒ�
	HRESULT MakeVertex(void);									// ���_���̍쐬
	
	static D3DXVECTOR3 m_conSetingVtxPos[POLYCOLLI_MAX][POLYCOLLI_USE_VTX];	// �ݒ�p���_�ʒu
	LPDIRECT3DVERTEXBUFFER9  m_pVtxBuff;											// �o�b�t�@
	D3DXVECTOR3              m_VtxPos[POLYCOLLI_USE_VTX];							// ���_�ʒu
	D3DXVECTOR3              m_SurfaceNor;											// �ʂ̖@��
};

#endif