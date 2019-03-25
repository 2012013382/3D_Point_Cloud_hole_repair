
// ChildFrm.h : CChildFrame ��Ľӿ�
//
#pragma once
#include"MyRenderToolBoard.h"
#include"3D_PCD2View.h"
#include "PropertyBoard.h"
class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

	// ����
public:
	CSplitterWnd m_wndSplitter;//���ڴ��ڷָ�
	CMy3D_PCD2View *m_MyDrawView;//�ұߵ�ģ����ʾ����
	MyRenderToolBoard *m_LeftView;//��ߵĹ���������
	PropertyBoard *m_RightView;//�ұߵ�����������
	// ����
public:

	// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnMenuBoundaryKeep();
	afx_msg void OnMenuBoundaryCluster();
	afx_msg void OnMenuHoleRepair();
	afx_msg void OnAutomaticHoleRepair();
	afx_msg void OnMenuSurfaceGeneration();
	afx_msg void OnMenuTriShow();
	afx_msg void OnMenuSingleShow();
	afx_msg void OnMenuOneStepRepair();
	afx_msg void OnMenuOneStepRepairAndSurface();
	afx_msg void OnClose();
	afx_msg void OnPaint();
};
