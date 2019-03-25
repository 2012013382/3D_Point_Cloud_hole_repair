
// 3D_PCD2View.h : CMy3D_PCD2View ��Ľӿ�
//

#pragma once
#include"3D_PCD2Doc.h"
#include "PointCloudData.h"
#include "PointProperty.h"
class CMy3D_PCD2View : public CView
{
protected: // �������л�����
	CMy3D_PCD2View();
	DECLARE_DYNCREATE(CMy3D_PCD2View)

	// ����
public:
	CMy3D_PCD2Doc* GetDocument() const;

	// OpenGL�������ñ���
	HGLRC m_hGLContext;
	int m_GLPixelIndex;
	//OpenGLͼ�α���
	float m_xRotation;
	float m_yRotation;
	float m_xTranslation;
	float m_yTranslation;
	float m_zTranslation;
	float m_xScaling;
	float m_yScaling;
	float m_zScaling;

	// Mouse 
	BOOL b_LeftButtonDown;
	BOOL b_RightButtonDown;
	CPoint m_LeftDownPos;
	CPoint m_RightDownPos;
	HCURSOR m_CursorRotation;
	//������ʾ���Ŀ��
	int m_DisplayWidth;

	//������ʾ���ĳ���
	int m_DisplayHeight;

	//�ѵ����ļ�
	BOOL b_FileInputed;
	//�Ѿ������˱߽籣��
	bool b_BoundaryChecked;
	//�Ѿ������˱߽����
	bool b_BoundaryCluster;
	//�Ѿ�������Լ�����ѡȡ
	bool b_SelectedPoints;
	//����������������ʾģ������
	char* m_ShowFileName;
	//����������������ʾģ�͵�������
	int m_ShowPointCloudNum;

	PointCloudData m_myPointCloudData;//��������
private:
	//ʰȡģʽ
	bool b_SelectingMode;
	//Լ����ѡ���ģʽ
	bool b_GetingRPMode;
	//������ģʽ
	bool b_SelectingPointPropertyMode;
	//����ͼ��ʾ
	bool b_TriWindowMode;
	//ĳ�ΰ�ס�������ƶ�ʱ
	bool b_LeftButtonFirstDown;
	//�洢��һ����
	CPoint m_LastPoint;
	//test
	bool b_test;
	//���ģ�����ǻ�
	bool b_SurfaceGenerated;
	//��ʸ����ʾģʽ
	bool b_NormalVectorMode;

	// ����
public:
	//OpenGL�������ú���
	bool SetWindowPixelFormat(HDC hDC);
	bool CreateViewGLContext(HDC hDC);
	//��ʼ��ͼ�α���
	void InitGeometry(void);
	//��ʾ����ģ��
	void PointCloudDisplay();
	//��ȡ����ģ��
	void ReadPointCloudData();
	//���ʰȡ����
	void SelectObject(CPoint point, CPoint lastPoint);
	//����Ϊ���ʰȡ״̬
	void SetSelectingMode();
	//����Ϊ��ͨ��ʾģʽ
	void SetNormalMode();
	//����ΪԼ����ѡ��ģʽ
	void SetGetRPMode();
	//����
	void OnFileSaveAs();
	//����
	void OnFileSave();
	//�߽籣��
	void PointCloudBoundaryCheck();
	//�׶��޲�
	void PointCloudHoleRepair();
	//����ͼ��ʾ
	void SetTriWindowsMode();
	//��ͨ��ͼ��ʾ
	void SetSingleWindowMode();
	//�߽����
	void PointCloudBoundaryClustering();
	//�Զ��׶��޲�
	void PointCloudAutomaticHoleRepair();
	//����ģ�����ǻ�
	void PointCLoudSurfaceGenerating();
	//���㷨ʸ��
	void CaculateNormal(GLdouble* dVertex1, GLdouble* dVertex2,
		GLdouble* dVertex3, GLdouble* dNormal);
	//�����ػ棬��Ҫ����������������
	void ViewInvalidateRect();
	//����Ϊ�������ѡ��ģʽ
	void SetGetPointPropertyMode();
	//��ȡ�������ݵ�ķ�ʸ��
	void PointCloudGetSelectedPointsNormalVectors();
	//һ���޲�ģ�Ϳ׶�
	void PointCloudOneStepRepair();
	//һ���޲�ģ�Ϳ׶����ҽ��б����ؽ�
	void PointCloudOneStepRepairAndSurface();
	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CMy3D_PCD2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnFileOpen();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // 3D_PCD2View.cpp �еĵ��԰汾
inline CMy3D_PCD2Doc* CMy3D_PCD2View::GetDocument() const
{
	return reinterpret_cast<CMy3D_PCD2Doc*>(m_pDocument);
}
#endif

