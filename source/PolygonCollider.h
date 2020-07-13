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
	CPolygonCollider() : CScene(PRIORITY_COLLISION) {}			// �R���X�g���N�^
	~CPolygonCollider() {}										// �f�X�g���N�^

	static CPolygonCollider* Create(D3DXVECTOR3 *pVertexsPos);	// ����

	void Init(void);											// ������
	void Uninit(void);											// �I��
	void Update(void) {};										// �X�V
	void Draw(void);											// �`��

	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pOut_Intersect, D3DXVECTOR3* SurfaceNor, bool bReflection);		// �Փ˔���

	bool Test3DInsidePolygon(D3DXVECTOR3 *pPos);				// �|���S���̒��ɂ��邩�e�X�g

private:
	void SetVtxPos(D3DXVECTOR3 *pVertexsPos);					// ���_�ʒu�̐ݒ�
	HRESULT MakeVertex(void);									// ���_���̍쐬

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// �o�b�t�@
	D3DXVECTOR3             m_VtxPos[POLYCOLLI_USE_VTX];		// ���_�ʒu
	D3DXVECTOR3             m_SurfaceNor;						// �ʂ̖@��
};

#endif