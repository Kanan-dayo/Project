//*************************************************************************************************************
//
// �J�v�Z���R���C�_�[����[PolygonCollider.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
#ifndef _CAPSULECOLLIDER_H_
#define _CAPSULECOLLIDER_H_

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
class CCapsuleCollider : public CScene
{
public:
	// �񋓌^��`
	typedef enum
	{
		TYPEID_NOEN = -1,	// ����
		COLLIPARTS_BODY,	// ��
		TYPEID_FOREARM_R,	// �E�O�r
		TYPEID_UPPERARM_R,	// �E��r
		TYPEID_FOREARM_L,	// �O�r
		TYPEID_UPPERARM_L,	// ��r
		TYPEID_MAX			// �ő吔
	}TYPEID;

	// �\���̒�`
	typedef struct
	{
		LPDIRECT3DVERTEXBUFFER9		pVtexBuff;		// ���_�o�b�t�@�̃|�C���^
		LPDIRECT3DINDEXBUFFER9		pIdxBuff;			// �C���f�b�N�X�̃o�b�t�@�̃|�C���^

		float			fLength;			// ����
		int				nSlices;			// ���𒆐S�Ƃ���������
		int				nStacks_1_2;		// ���������̕�����

		int				nNumVertex;			// ���_��
		int				nNumindex;			// �C���f�b�N�X��
		int				nNumPolygon;		// �|���S����

		D3DXVECTOR3		Difference;			// ����
		D3DXVECTOR3		TopTransVec;		// ��ʂ܂ł̒����ƌ���
		D3DXVECTOR3		BottomTransVec;		// ��ʂ܂ł̒����ƌ���

		CAPSULE			Capsule;			// �J�v�Z�����
		TYPEID			enmTtpeID;			// �^�C�vID

		TRANSFORM		trans;				// �g�����X���
		D3DXMATRIX*		pMtxParent;			// �e�̃}�g���b�N�X�|�C���^
		CScene*			pScene;				// �e�̃V�[���|�C���^
	}CAPSULECOLLIDERINFO;

	// �V�����_�[�̑傫����ݒ肷����
	typedef struct
	{
		float fTop;		// ��ʂ܂ł̃T�C�Y
		float fBottom;	// ��ʂ܂ł̃T�C�Y
		float fRadius;	// ���a
	} SIZE_INFO;

	// �ǂ݂��񂾃t�@�C���̒P�̂̏��
	typedef struct
	{
		SIZE_INFO	*pSizeInfo;		// �T�C�Y���̃|�C���^
		D3DXVECTOR3	*pDifference;	// �����̃|�C���^
		int			nColliderType;	// �Փˎ��
	} READINFOFILE_CELL;

	// �ǂ݂��񂾃t�@�C���̑S�̏��
	typedef struct
	{
		int				   nNumReadInfo;			// �ǂ݂��ޏ��̌�
		int*			   pSetThisID;				// ����������ID�̃|�C���^
		READINFOFILE_CELL* pCell;					// �P�̏��|�C���^
	} READINFOFILEBUFFER;
	

	// �R���X�g���N�^
	CCapsuleCollider();
	// �f�X�g���N�^
	~CCapsuleCollider() {}


	// �ǂݍ���
	static HRESULT Load(void);
	// �J��
	static void Unload(void);

	void Init(void);																		// ������
	void Uninit(void);																		// �I��
	void Update(void);																		// �X�V
	void Draw(void);																		// �`��
	void SetMtxParent(D3DXMATRIX *pMtxParent);												// �e�̃}�g���b�N�X�|�C���^�̐ݒ�
	void SetScene(CScene *pScene);															// �V�[���̐ݒ�

	static CCapsuleCollider *Create(CScene *pScene,D3DXMATRIX *pMtxParent, int nTypeID);	// ����
	void InfoSetSync(float fRadius, float fLengthMax, float fLengthMin, D3DXVECTOR3 &diff);	// ���̐ݒ�Ɠ���
	void InitCapsInfo(void);																// �J�v�Z�����̏�����
	bool Collision(void);																	// �Փ˔���

	void CalCapPosition(void);																// �J�v�Z���ʒu�̌v�Z

	//* [contents] ��p1p2p3�͉s�p���ǂ���
	//* [in] Point�i�_�j, Line�i�����j
	//* [return] �s�p���ǂ����itrue : �s�p, false : �s�p�ł͂Ȃ��j
	static bool IsSharpAngle(CONST FLOAT3 &Point1, CONST FLOAT3 &Point2, CONST FLOAT3 &Point3);

	//* [contents] �_�ƒ����̍ŒZ����
	//* [in] Point�i�_�j, Line�i�����j
	//* [out] Perp�i�����j, fVecCoeffi�i�x�N�g���W���j
	//* [return] �ŒZ����
	float calcPointLineDist(const FLOAT3 &Point, const LINE &Line, FLOAT3 &Perp, float &fVecCoeffi);

	//* [contents] �_�Ɛ����̍ŒZ����
	//* [in] Point�i�_�j, Seg�i�����j
	//* [out] EndPtShortdist�i�ŒZ�����ƂȂ�[�_�j, EndPoint�i�[�_�j
	//* [return] �ŒZ����
	float calcPointSegmentDist(const FLOAT3 &Point, const SEGMENT &Seg, FLOAT3 &EndPtShortdist, float &EndPoint);

	//* [contents] 2�����̍ŒZ����
	//* [in] Line1�i����1�j, Line2�i����2�j
	//* [out] PerpendFoot1�i����1���̐����̑��j,PerpendFoot2�i����2���̐����̑��j,fVecCoeffi1�i����1���̃x�N�g���W���j, fVecCoeffi2�i����2���̃x�N�g���W���j
	//* [return] �ŒZ����
	float calcLineLineDist(const LINE &Line1, const LINE &Line2, FLOAT3 &PerpendFoot1, FLOAT3 &PerpendFoot2, float &fVecCoeffi1, float &fVecCoeffi2);

	//* [contents] 0�`1�̊Ԃɐ�������
	//* [out] fValue�i��������l�j
	void Limit0to1(float &fValue);

	//* [contents] 2�����̍ŒZ����
	//* [in] Seg1�i����1�j, Seg2�i����2�j
	//* [out] PerpendFoot1�i����1���̐����̑��j,PerpendFoot2�i����2���̐����̑��j,fVecCoeffi1�i����1���̃x�N�g���W���j, fVecCoeffi2�i����2���̃x�N�g���W���j
	//* [return] �ŒZ����
	float calcSegmentSegmentDist(const SEGMENT &Seg1, const SEGMENT &Seg2, FLOAT3 &PerpendFoot1, FLOAT3 &PerpendFoot2, float &fVecCoeffi1, float &fVecCoeffi2);

	//* [contents] �J�v�Z�����m�̏Փ˔���
	//* [in] Cap1�i�J�v�Z��1�j, Cap2�i�J�v�Z��2�j
	//* [return] �Փ˂��Ă��鎞true
	bool colCapsuleCapsule(const CAPSULE &Cap1, const CAPSULE &Cap2);

private:
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);		// ���_�̍쐬
	void MakeIndex(LPDIRECT3DDEVICE9 pDevice);		// �C���f�b�N�X�̍쐬

	static READINFOFILEBUFFER	m_ReadInfoFileBuff;		// �ǂ݂��񂾃t�@�C�����
	CAPSULECOLLIDERINFO m_ColliderInfo;				// ���
};

#endif