//*************************************************************************************************************
//
// �|���S���R���C�_�[����[PolygonCollider.h]
// Author : Sekine Ikuto
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "CapsuleCollider.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"
#include "debugProc.h"

//-------------------------------------------------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------------------------------------------------
#define CAPCOLLI_SLICES		5
#define CAPCOLLI_STACKS		5

#define CAPCOLLI_BOTTOMUNITVEC_NUMVTX	(3)		// ��ʂ̒P�ʃx�N�g���v�Z�ɕK�v�Ȓ��_��

#define CAPCOLLI_FILENAME						"data/TEXT/ColliInfo/Cylinder.csv"	// �t�@�C����
#define CAPCOLLI_OPENMODE						"r"		// �t�@�C���̊J�����[�h

#define CAPCOLLI_WORDSIZE						16		// ���[�h�T�C�Y

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-------------------------------------------------------------------------------------------------------------
CCapsuleCollider::READINFOFILEBUFFER	CCapsuleCollider::m_ReadInfoFileBuff;		// �ǂ݂��񂾃t�@�C�����

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
CCapsuleCollider::CCapsuleCollider() : CScene(PRIORITY_COLLISION)
{
	m_ColliderInfo.fLength = MYLIB_FLOAT_UNSET;			// ����

	m_ColliderInfo.Difference = MYLIB_VEC3_UNSET;		// ����
	m_ColliderInfo.TopTransVec = MYLIB_VEC3_UNSET;		// ��ʂ܂ł̒����ƌ���
	m_ColliderInfo.BottomTransVec = MYLIB_VEC3_UNSET;	// ��ʂ܂ł̒����ƌ���
	m_ColliderInfo.enmTtpeID = TYPEID_NOEN;				// �^�C�vID
	m_ColliderInfo.trans.pos = MYLIB_VEC3_UNSET;
	m_ColliderInfo.trans.rot = MYLIB_VEC3_UNSET;
	m_ColliderInfo.trans.scal = MYLIB_SCALE_UNSET;
	m_ColliderInfo.pMtxParent = NULL;		// �e�̃}�g���b�N�X�|�C���^
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
HRESULT CCapsuleCollider::Load(void)
{
	// �ǂ݂��񂾃t�@�C�����̏�����
	m_ReadInfoFileBuff.nNumReadInfo = MYLIB_INT_UNSET;
	m_ReadInfoFileBuff.pCell = NULL;
	m_ReadInfoFileBuff.pSetThisID = NULL;
#ifdef _DEBUG
	cout << "---------------------------------------------------------------------\n";
	cout << "CCapsuleCollider::Load �J�v�Z���R���C�_�[�̓ǂݍ��݊J�n\n";
	DWORD start = timeGetTime();			// �v���X�^�[�g����
#endif
											// �ϐ��錾
	FILE *pFile = fopen(CAPCOLLI_FILENAME, CAPCOLLI_OPENMODE);
	// �J���Ȃ�����
	if (pFile == NULL)
	{
#ifdef _DEBUG
		cout << "CCapsuleCollider::Load �J�v�Z���R���C�_�[�̓ǂݍ��݂̃t�@�C�����J���܂���ł���\n";
		cout << "---------------------------------------------------------------------\n";
#endif
		return E_FAIL;
	}

	// �ϐ��錾
	char aRead[MYLIB_STRINGSIZE];		// �ǂݍ��ݗp
	char aComp[MYLIB_STRINGSIZE];		// ��r�p
	char aEmpty[MYLIB_STRINGSIZE];		// �v��Ȃ����̗p
	int  nCntInfo;						// ���J�E���g

	aRead[0] = MYLIB_CHAR_UNSET;		// �ǂݍ��ݗp
	aComp[0] = MYLIB_CHAR_UNSET;		// ��r�p
	aEmpty[0] = MYLIB_CHAR_UNSET;		// �v��Ȃ����̗p
	nCntInfo = MYLIB_INT_UNSET;			// ���J�E���g

#ifdef _DEBUG
	int  nCntError;						// �G���[�J�E���g
	nCntError = MYLIB_INT_UNSET;		// �G���[�J�E���g
#endif
										// �X�N���v�g������܂łƂ΂�
	while (strcmp(aComp, "SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(aRead, sizeof(aRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(aRead, "%[^,]s", &aComp);
#ifdef _DEBUG
		// �G���[�J�E���g���C���N�������g
		if (++nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			fclose(pFile);
			return E_FAIL;
		}
#endif
	}
	// END_SCRIPT�܂Ń��[�v
	while (strcmp(aComp, "END_SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(aRead, sizeof(aRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(aRead, "%[^,]s", &aComp);
#ifdef _DEBUG
		// �G���[�J�E���g���C���N�������g
		if (++nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			fclose(pFile);
			return E_FAIL;
		}
#endif
		if (m_ReadInfoFileBuff.nNumReadInfo <= 0)
		{
			// �ݒ肷���
			if (strcmp(aComp, "SET_NUM") == 0)
			{
				sscanf(aRead, "%[^,],%d", &aEmpty, &m_ReadInfoFileBuff.nNumReadInfo);
				// �P�̏�����������
				m_ReadInfoFileBuff.pCell = new READINFOFILE_CELL[m_ReadInfoFileBuff.nNumReadInfo];
				// ����������ID����������
				m_ReadInfoFileBuff.pSetThisID = new int[m_ReadInfoFileBuff.nNumReadInfo];
				// ������̏�����
				aComp[0] = '\0';
				cout << "�ǂ݂��݌����擾���܂���\n";
			}
		}
		else
		{
			// �ݒ肷�����
			if (strcmp(aComp, "SET") == 0)
			{
				// �ϐ��錾
				char aSizeWord[CAPCOLLI_WORDSIZE];		// �T�C�Y�̃t���O����
				char aDiffWord[CAPCOLLI_WORDSIZE];		// �����̃t���O����
				READINFOFILE_CELL *pCell;					// �Z���|�C���^

															// ������
				aSizeWord[0] = MYLIB_CHAR_UNSET;
				aDiffWord[0] = MYLIB_CHAR_UNSET;
				pCell = &m_ReadInfoFileBuff.pCell[nCntInfo];

				/* ��s���̏�����͂��� */
				//			   SET     ����   ID  ��傫��               ����                  �^�C�v
				sscanf(aRead, "%[^, ],%[^, ], %d, %[^, ], %[^, ], %[^, ],%[^, ], %[^, ], %[^, ], %d",
					&aEmpty, &aEmpty,
					&m_ReadInfoFileBuff.pSetThisID[nCntInfo],
					&aSizeWord,
					&aEmpty, &aEmpty,
					&aDiffWord,
					&aEmpty, &aEmpty,
					&pCell->nColliderType);
				// �T�C�Y��ݒ肵�Ȃ���
				if (strcmp(aSizeWord, "UNSET") != 0)
				{
					// �T�C�Y���̐���
					pCell->pSizeInfo = new SIZE_INFO;
					//             SET     ����    ID      
					sscanf(aRead, "%[^, ], %[^, ], %[^, ], %f, %f, %f, ",
						&aEmpty, &aEmpty, &aEmpty,
						&pCell->pSizeInfo->fTop,
						&pCell->pSizeInfo->fBottom,
						&pCell->pSizeInfo->fRadius);
				}
				else
				{// ����ȊO�̎�
					pCell->pSizeInfo = NULL;
				}
				// ������ݒ肵�Ȃ���
				if (strcmp(aDiffWord, "UNSET") != 0)
				{
					// �����̐���
					pCell->pDifference = new D3DXVECTOR3;
					sscanf(aRead, "%[^, ], %[^, ], %[^, ], %[^, ], %[^, ], %[^, ], %f, %f, %f, ",
						&aEmpty, &aEmpty, &aEmpty, &aEmpty, &aEmpty, &aEmpty,
						&pCell->pDifference->x,
						&pCell->pDifference->y,
						&pCell->pDifference->z);
				}
				else
				{// ����ȊO�̎�
					pCell->pDifference = NULL;
				}
				// ���J�E���g�C���N�������g
				nCntInfo++;
				// ������̏�����
				aComp[0] = '\0';
#ifdef _DEBUG
				cout << "[" << nCntInfo << "]�ڂ̏����擾���܂���\n";
#endif
			}
		}
	}
	fclose(pFile);
#ifdef _DEBUG
	DWORD end = timeGetTime();			// �v���X�^�[�g����
	cout << "CCapsuleCollider::Load �J�v�Z���R���C�_�[�̓ǂݍ��ݏI��\n";
	cout << " CCapsuleCollider::Load �J�v�Z���R���C�_�[�̓ǂݍ��� �������x = " << (end - start) << "�@[" << (end - start) * 0.001f << "sec.]\n";
#endif
	cout << "---------------------------------------------------------------------\n";
	return S_OK;

}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::Unload(void)
{
	// �P�̏��̌������[�v
	for (int nCntCell = 0; nCntCell < m_ReadInfoFileBuff.nNumReadInfo; nCntCell++)
	{
		// �傫���̔j��
		if (m_ReadInfoFileBuff.pCell[nCntCell].pSizeInfo != NULL)
		{
			delete m_ReadInfoFileBuff.pCell[nCntCell].pSizeInfo;
			m_ReadInfoFileBuff.pCell[nCntCell].pSizeInfo = NULL;
		}
		// �����̔j��
		if (m_ReadInfoFileBuff.pCell[nCntCell].pDifference != NULL)
		{
			delete m_ReadInfoFileBuff.pCell[nCntCell].pDifference;
			m_ReadInfoFileBuff.pCell[nCntCell].pDifference = NULL;
		}
	}
	// �P�̏���j��
	if (m_ReadInfoFileBuff.pCell != NULL)
	{
		delete[]m_ReadInfoFileBuff.pCell;
		m_ReadInfoFileBuff.pCell = NULL;
	}
	// ����������ID�̔j��
	if (m_ReadInfoFileBuff.pSetThisID != NULL)
	{
		delete[]m_ReadInfoFileBuff.pSetThisID;
		m_ReadInfoFileBuff.pSetThisID = NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::Init(void)
{
	m_ColliderInfo.nSlices = CAPCOLLI_SLICES * 2;
	m_ColliderInfo.nStacks_1_2 = (CAPCOLLI_STACKS % 2 == 0) ? CAPCOLLI_STACKS: CAPCOLLI_STACKS + 1;
	// ���_��
	m_ColliderInfo.nNumVertex = (m_ColliderInfo.nStacks_1_2 + 1) * (m_ColliderInfo.nSlices + 1);
	// �����ڂ̒��_��
	m_ColliderInfo.nNumindex = 2 * m_ColliderInfo.nSlices * (m_ColliderInfo.nStacks_1_2 + 1);
	// �O�p�`�̐�
	m_ColliderInfo.nNumPolygon = m_ColliderInfo.nNumVertex - 2;


	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// ���_�̍쐬
	MakeVertex(pDevice);
	// �C���f�b�N�X�̍쐬
	MakeIndex(pDevice);

	// �J�v�Z�����̏�����
	InitCapsInfo();
}
//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::Uninit(void)
{
	// ���_�o�b�t�@��NULL����Ȃ���
	if (m_ColliderInfo.pVtexBuff != NULL)
	{
		// ���_�o�b�t�@�̊J��
		m_ColliderInfo.pVtexBuff->Release();
		m_ColliderInfo.pVtexBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@��NULL����Ȃ���
	if (m_ColliderInfo.pIdxBuff != NULL)
	{
		// �C���f�b�N�X�o�b�t�@�̊J��
		m_ColliderInfo.pIdxBuff->Release();
		m_ColliderInfo.pIdxBuff = NULL;
	}
}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::Update(void)
{
	// �V�[����NULL����Ȃ���
	if (m_ColliderInfo.pScene != NULL)
	{// �Փ˔���
		this->Collision();
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans, mtxRot;							// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O���[�h����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// Fill Mode �̐ݒ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	// �J�����O���Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_ColliderInfo.trans.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_ColliderInfo.trans.rot.y,
		m_ColliderInfo.trans.rot.x,
		m_ColliderInfo.trans.rot.z);
	D3DXMatrixMultiply(&m_ColliderInfo.trans.mtxWorld,
		&m_ColliderInfo.trans.mtxWorld,
		&mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_ColliderInfo.Difference.x,
		m_ColliderInfo.Difference.y,
		m_ColliderInfo.Difference.z);

	D3DXMatrixMultiply(&m_ColliderInfo.trans.mtxWorld,
		&m_ColliderInfo.trans.mtxWorld,
		&mtxTrans);

	D3DXMatrixMultiply(&m_ColliderInfo.trans.mtxWorld,
		&m_ColliderInfo.trans.mtxWorld,
		&mtxTrans);


	// �e���f���̏�񂪂���Ƃ�
	if (m_ColliderInfo.pMtxParent != NULL)
	{
		D3DXMatrixMultiply(&m_ColliderInfo.trans.mtxWorld
			, &m_ColliderInfo.trans.mtxWorld
			, m_ColliderInfo.pMtxParent);
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_ColliderInfo.trans.mtxWorld);

	// �J�v�Z���ʒu�̌v�Z
	CalCapPosition();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_ColliderInfo.pVtexBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_ColliderInfo.pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_ColliderInfo.nNumindex, 0, m_ColliderInfo.nNumPolygon);

	// ���C�e�B���O���[�h�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// Fill Mode �̐ݒ�
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// �����_���[�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����

}

//-------------------------------------------------------------------------------------------------------------
// �e�̃}�g���b�N�X�|�C���^�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::SetMtxParent(D3DXMATRIX * pMtxParent)
{
	m_ColliderInfo.pMtxParent = pMtxParent;
}

//-------------------------------------------------------------------------------------------------------------
// �V�[���̃|�C���^
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::SetScene(CScene * pScene)
{
	m_ColliderInfo.pScene = pScene;
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
CCapsuleCollider * CCapsuleCollider::Create(CScene *pScene, D3DXMATRIX *pMtxParent, int nTypeID)
{
	// �ϐ��錾
	CCapsuleCollider *pCollider = new CCapsuleCollider;

	int nID = CCapsuleCollider::m_ReadInfoFileBuff.pSetThisID[nTypeID];	// ID�̎擾
	READINFOFILE_CELL *pCell = &CCapsuleCollider::m_ReadInfoFileBuff.pCell[nID];			// �Z���̃|�C���^

	// ���̐ݒ�Ɠ���
	pCollider->InfoSetSync(
		pCell->pSizeInfo->fRadius,		// ���a
		pCell->pSizeInfo->fTop,			// ��ʂ܂ł̃T�C�Y
		pCell->pSizeInfo->fBottom,		// ��ʂ܂ł̃T�C�Y
		*pCell->pDifference				// ����
	);

	// �e�̃}�g���b�N�X�|�C���^�̐ݒ�
	pCollider->SetMtxParent(pMtxParent);
	// �V�[���̐ݒ�
	pCollider->SetScene(pScene);
	// �ݒ�
	pCollider->Init();
	return pCollider;
}

//-------------------------------------------------------------------------------------------------------------
// ���̐ݒ�Ɠ���
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::InfoSetSync(float fRadius, float fLengthMax, float fLengthMin, D3DXVECTOR3 & diff)
{
	m_ColliderInfo.TopTransVec.y = fLengthMax;		// �����ő�
	m_ColliderInfo.BottomTransVec.y = fLengthMin;	// �����ŏ�
	m_ColliderInfo.Difference = diff;				// ����

	m_ColliderInfo.Capsule.fRadius = fRadius;
	m_ColliderInfo.Capsule.Segment.Point.y = fLengthMax;
	m_ColliderInfo.Capsule.Segment.Vec.y = fLengthMin - fLengthMax;
}

//-------------------------------------------------------------------------------------------------------------
// �J�v�Z�����̏�����
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::InitCapsInfo(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �Փ˔���
//-------------------------------------------------------------------------------------------------------------
bool CCapsuleCollider::Collision(void)
{
	if (m_ColliderInfo.enmTtpeID == COLLIPARTS_BODY)
	{
		return false;
	}
	// �ϐ��錾
	CPlayer          *pOwn            = (CPlayer *)m_ColliderInfo.pScene;						// ���̃R���C�_�[�������Ă���v���C���[
	CPlayer          *pOthers         = pOwn->GetAnotherPlayer();								// ���̑��̃v���C���[
	CCapsuleCollider *pOthersCapColli = pOthers->GetCapCollider(CCharacter::COLLIPARTS_BODY);	// ���̑��̃v���C���[�̃R���C�_�[���

	CDebugProc::Print("COLLIPARTS [%d]", m_ColliderInfo.enmTtpeID);
	// 2�����̍ŒZ�������߂�
	colCapsuleCapsule(m_ColliderInfo.Capsule, pOthersCapColli->m_ColliderInfo.Capsule) ?
		CDebugProc::Print("�������Ă�\n"):
		CDebugProc::Print("�������ĂȂ�\n");

	return false;
}

//-------------------------------------------------------------------------------------------------------------
// �J�v�Z���ʒu�̌v�Z
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::CalCapPosition(void)
{
	// �ϐ��錾
	D3DXVECTOR3 BottomPoint;	// ��ʂ̈ʒu

	// ��ʂ̈ʒu
	D3DXVec3TransformCoord(&m_ColliderInfo.Capsule.Segment.Point, &m_ColliderInfo.TopTransVec, &m_ColliderInfo.trans.mtxWorld);
	// ��ʂ̈ʒu
	D3DXVec3TransformCoord(&BottomPoint, &m_ColliderInfo.BottomTransVec, &m_ColliderInfo.trans.mtxWorld);

	m_ColliderInfo.Capsule.Segment.Vec = BottomPoint - m_ColliderInfo.Capsule.Segment.Point;
}

bool CCapsuleCollider::IsSharpAngle(CONST FLOAT3 & Point1, CONST FLOAT3 & Point2, CONST FLOAT3 & Point3)
{
	return VEC3(Point1 - Point2).IsSharpAngle(Point3 - Point2);
}

float CCapsuleCollider::calcPointLineDist(const FLOAT3 & Point, const LINE & Line, FLOAT3 & Perp, float & fVecCoeffi)
{
	// �ϐ��錾
	float fLenSqV = Line.Vec.LengthSq();		// �ׂ���̒���
	// �x�N�g���W���̏�����
	fVecCoeffi = MYLIB_FLOAT_UNSET;

	// �ׂ���̒�����0.0f���傫���Ƃ�
	if (fLenSqV > MYLIB_FLOAT_UNSET)
	{// �x�N�g���W�����v�Z����
		fVecCoeffi = Line.Vec.Dot(Point - Line.Point) / fLenSqV;
	}

	Perp = Line.Point + fVecCoeffi * Line.Vec;
	return (Perp - Point).Length();
}

float CCapsuleCollider::calcPointSegmentDist(const FLOAT3 & Point, const SEGMENT & Seg, FLOAT3 & EndPtShortdist, float & EndPoint)
{
	// �����̏I�_�̎擾
	const FLOAT3 SegEndPoint = Seg.GetEndPoint();

	// �����̒����A�����̑��̍��W�y��t���Z�o
	float fLength = calcPointLineDist(Point, LINE(Seg.Point, SegEndPoint - Seg.Point), EndPtShortdist, EndPoint);

	// �s�p����Ȃ���
	if (IsSharpAngle(Point, Seg.Point, SegEndPoint) == false) {
		// �n�_���̊O��
		EndPtShortdist = Seg.Point;
		return (Seg.Point - Point).Length();
	}
	// �s�p����Ȃ���
	else if (IsSharpAngle(Point, SegEndPoint, Seg.Point) == false) {
		// �I�_���̊O��
		EndPtShortdist = SegEndPoint;
		return (SegEndPoint - Point).Length();
	}

	return fLength;
}

float CCapsuleCollider::calcLineLineDist(const LINE & Line1, const LINE & Line2, FLOAT3 & PerpendFoot1, FLOAT3 & PerpendFoot2, float & fVecCoeffi1, float & fVecCoeffi2)
{
	// 2���������s�H
	if (Line1.Vec.IsParallel(Line2.Vec) == true)
	{
		// �_P11�ƒ���L2�̍ŒZ�����̖��ɋA��
		float fLength = calcPointLineDist(Line1.Point, Line2, PerpendFoot2, fVecCoeffi2);
		PerpendFoot1 = Line1.Point;
		fVecCoeffi1 = 0.0f;

		return fLength;
	}

	// 2�����͂˂���֌W
	float fDistVec1Vec2 = Line1.Vec.Dot(Line2.Vec);	// �x�N�g��1��2�̂˂���
	float fDistVec1Vec1 = Line1.Vec.LengthSq();		// �x�N�g��1��1�̂˂���
	float fDistVec2Vec2 = Line2.Vec.LengthSq();		// �x�N�g��2��2�̂˂���
	VEC3 VecPt2Pt1 = Line1.Point - Line2.Point;		// �����̈ʒu���m�̃x�N�g��
	fVecCoeffi1 = (fDistVec1Vec2 * Line2.Vec.Dot(VecPt2Pt1) - fDistVec2Vec2 * Line1.Vec.Dot(VecPt2Pt1)) / (fDistVec1Vec1 * fDistVec2Vec2 - fDistVec1Vec2 * fDistVec1Vec2);
	PerpendFoot1 = Line1.GetPoint(fVecCoeffi1);
	fVecCoeffi2 = Line2.Vec.Dot(PerpendFoot1 - Line2.Point) / fDistVec2Vec2;
	PerpendFoot2 = Line2.GetPoint(fVecCoeffi2);

	return (PerpendFoot2 - PerpendFoot1).Length();
}

void CCapsuleCollider::Limit0to1(float & fValue)
{
	if (fValue < 0.0f)
	{
		fValue = 0.0f;
	}
	else if (fValue > 1.0f)
	{
		fValue = 1.0f;
	}
}

float CCapsuleCollider::calcSegmentSegmentDist(const SEGMENT & Seg1, const SEGMENT & Seg2, FLOAT3 & PerpendFoot1, FLOAT3 & PerpendFoot2, float & fVecCoeffi1, float & fVecCoeffi2)
{
	// S1���k�ނ��Ă���H
	if (Seg1.Vec.LengthSq() < MYLIB_OX_EPSILON)
	{// S2���k�ށH
		if (Seg2.Vec.LengthSq() < MYLIB_OX_EPSILON)
		{// �_�Ɠ_�̋����̖��ɋA��
			float fLength = (Seg2.Point - Seg1.Point).Length();
			PerpendFoot1 = Seg1.Point;
			PerpendFoot2 = Seg2.Point;
			fVecCoeffi1 = fVecCoeffi2 = 0.0f;
			return fLength;
		}
		else
		{// S1�̎n�_��S2�̍ŒZ���ɋA��
			float fLength = calcPointSegmentDist(Seg1.Point, Seg2, PerpendFoot2, fVecCoeffi2);
			PerpendFoot1 = Seg1.Point;
			fVecCoeffi1 = 0.0f;
			Limit0to1(fVecCoeffi2);
			return fLength;
		}
	}

	// S2���k�ނ��Ă���H
	else if (Seg2.Vec.LengthSq() < MYLIB_OX_EPSILON)
	{// S2�̎n�_��S1�̍ŒZ���ɋA��
		float fLength = calcPointSegmentDist(Seg2.Point, Seg1, PerpendFoot1, fVecCoeffi1);
		PerpendFoot2 = Seg2.Point;
		Limit0to1(fVecCoeffi1);
		fVecCoeffi2 = 0.0f;
		return fLength;
	}

	// 2���������s�������琂���̒[�_�̈��P1�ɉ�����
	if (Seg1.Vec.IsParallel(Seg2.Vec) == true)
	{
		fVecCoeffi1 = 0.0f;
		PerpendFoot1 = Seg1.Point;
		float fLength = calcPointSegmentDist(Seg1.Point, Seg2, PerpendFoot2, fVecCoeffi2);
		if (0.0f <= fVecCoeffi2 && fVecCoeffi2 <= 1.0f)
		{
			return fLength;
		}
	}
	else
	{// �����͂˂���̊֌W
		// 2�����Ԃ̍ŒZ���������߂ĉ���fVecCoeffi1,fVecCoeffi2�����߂�
		float fLength = calcLineLineDist(Seg1, Seg2, PerpendFoot1, PerpendFoot2, fVecCoeffi1, fVecCoeffi2);
		if (0.0f <= fVecCoeffi1 && fVecCoeffi1 <= 1.0f &&
			0.0f <= fVecCoeffi2 && fVecCoeffi2 <= 1.0f)
		{
			return fLength;
		}
	}

	// �����̑����O�ɂ��鎖������
	// S1����fVecCoeffi1��0�`1�̊ԂɃN�����v���Đ������~�낷
	Limit0to1(fVecCoeffi1);
	PerpendFoot1 = Seg1.GetPoint(fVecCoeffi1);
	float fLength = calcPointSegmentDist(PerpendFoot1, Seg2, PerpendFoot2, fVecCoeffi2);
	if (0.0f <= fVecCoeffi2 && fVecCoeffi2 <= 1.0f)
	{
		return fLength;
	}

	// S2�����O�������̂�S2�����N�����v�AS1�ɐ������~�낷
	Limit0to1(fVecCoeffi2);
	PerpendFoot2 = Seg2.GetPoint(fVecCoeffi2);
	fLength = calcPointSegmentDist(PerpendFoot2, Seg1, PerpendFoot1, fVecCoeffi1);
	if (0.0f <= fVecCoeffi1 && fVecCoeffi1 <= 1.0f)
	{
		return fLength;
	}

	// �o���̒[�_���ŒZ�Ɣ���
	Limit0to1(fVecCoeffi1);
	PerpendFoot1 = Seg1.GetPoint(fVecCoeffi1);
	return (PerpendFoot2 - PerpendFoot1).Length();
}

bool CCapsuleCollider::colCapsuleCapsule(const CAPSULE & Cap1, const CAPSULE & Cap2)
{
	// �ϐ��錾
	FLOAT3 PerpendFoot1;	// ����1���̐����̑�
	FLOAT3 PerpendFoot2;	// ����2���̐����̑�
	float fVecCoeffi1;		// ����1���x�N�g���̌W��
	float fVecCoeffi2;		// ����2���x�N�g���̌W��
	float fDist;			// �������m�̋���

	// �������m�̋����̌v�Z
	fDist = calcSegmentSegmentDist(Cap1.Segment, Cap2.Segment, PerpendFoot1, PerpendFoot2, fVecCoeffi1, fVecCoeffi2);

	// �������m�̋��������a�ȉ��̎��Փ˂��Ă���
	return (fDist <= Cap1.fRadius + Cap2.fRadius);
}

//-------------------------------------------------------------------------------------------------------------
// ���_�̍쐬
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_ColliderInfo.nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_ColliderInfo.pVtexBuff,
		NULL);

	// �ϐ��錾
	D3DXVECTOR3 TopPoint = m_ColliderInfo.Capsule.Segment.Point;			// ��ʂ̈ʒu
	D3DXVECTOR3 BottomPoint = m_ColliderInfo.Capsule.Segment.GetEndPoint();	// ��ʂ̈ʒu
	float fSlicesPI = (D3DX_PI * 2.0f) / m_ColliderInfo.nSlices;			// �������ɑΉ������~����
	float fStacksPI = (D3DX_PI * 2.0f) / m_ColliderInfo.nStacks_1_2;		// �������ɑΉ������~����
	// �c���J�E���g
	int nCompSlices = (CAPCOLLI_SLICES / 2);
	nCompSlices += (CAPCOLLI_SLICES % 2 == 0) ? 0 : 1;

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�f�[�^�͈̔̓��b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_ColliderInfo.pVtexBuff->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntSlices = 0; nCntSlices < m_ColliderInfo.nSlices + 1; nCntSlices++)
	{
		float fSlicesRadian = fSlicesPI * nCntSlices;
		float fSlicesSinValue = sinf((fSlicesPI * nCntSlices));
		float fPos_y = cosf(fSlicesRadian) *  m_ColliderInfo.Capsule.fRadius;

		D3DXVECTOR3 pos = (nCntSlices <  nCompSlices) ? TopPoint : BottomPoint;

		// �����J�E���g
		for (int nCntStacks = 0; nCntStacks < m_ColliderInfo.nStacks_1_2 + 1; nCntStacks++)
		{
			float fStacksRadian = fStacksPI * nCntStacks;

			// ���_���W�̐ݒ�
			pVtx[0].pos.x = pos.x+ fSlicesSinValue * cosf(fStacksRadian) * m_ColliderInfo.Capsule.fRadius;
			pVtx[0].pos.y = pos.y+ fPos_y;
			pVtx[0].pos.z = pos.z+ fSlicesSinValue * sinf(fStacksRadian) * m_ColliderInfo.Capsule.fRadius;
			// ���_���ɖ@���̌v�Z���ʑ��
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �e�N�X�`���`�ʂ̈ʒu
			pVtx[0].tex = D3DXVECTOR2(1.0f / m_ColliderInfo.nStacks_1_2 * nCntStacks, 1.0f / m_ColliderInfo.nSlices * nCntSlices);

			// ���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���_�ԍ����Z
			pVtx++;
		}
	}

	// ���_�f�[�^���A�����b�N����
	m_ColliderInfo.pVtexBuff->Unlock();
}

//-------------------------------------------------------------------------------------------------------------
// �C���f�b�N�X�̍쐬
//-------------------------------------------------------------------------------------------------------------
void CCapsuleCollider::MakeIndex(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_ColliderInfo.nNumindex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_ColliderInfo.pIdxBuff,
		NULL);

	WORD *pIdx;				// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int nNumber = 0;		// �C���f�b�N�X�ԍ�

	// �C���f�b�N�X�o�b�t�@�����b�N���C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_ColliderInfo.pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �c���J�E���g
	for (int nCntSlices = 0; nCntSlices < m_ColliderInfo.nSlices; nCntSlices++)
	{
		// �����J�E���g
		for (int nCntStacks = 0; nCntStacks < m_ColliderInfo.nStacks_1_2 + 1; nCntStacks++)
		{
			// ���ɃC���f�b�N�X�i�[
			pIdx[nNumber++] = nCntSlices * (m_ColliderInfo.nStacks_1_2 + 1) + nCntStacks;
			pIdx[nNumber++] = pIdx[nNumber - 1] + m_ColliderInfo.nStacks_1_2 + 1;
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_ColliderInfo.pIdxBuff->Unlock();
}
