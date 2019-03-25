
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "3D_PCD2.h"

#include "ChildFrm.h"
#include "Guass.h"
#include"ProgressDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_COMMAND(ID_32773, &CChildFrame::OnMenuBoundaryKeep)
	ON_COMMAND(ID_32774, &CChildFrame::OnMenuBoundaryCluster)
	ON_COMMAND(ID_32775, &CChildFrame::OnMenuHoleRepair)
	ON_COMMAND(ID_32776, &CChildFrame::OnAutomaticHoleRepair)
	ON_COMMAND(ID_32777, &CChildFrame::OnMenuSurfaceGeneration)
	ON_COMMAND(ID_32778, &CChildFrame::OnMenuTriShow)
	ON_COMMAND(ID_32779, &CChildFrame::OnMenuSingleShow)
	ON_COMMAND(ID_32771, &CChildFrame::OnMenuOneStepRepair)
	ON_COMMAND(ID_32772, &CChildFrame::OnMenuOneStepRepairAndSurface)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������

}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | FWS_ADDTOTITLE;
	cs.style = cs.style&~FWS_ADDTOTITLE;//ȥ���������е��ĵ���
	cs.lpszName = "����ģ��";
	if (!CMDIChildWnd::PreCreateWindow(cs))
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{

	// TODO: �ڴ����ר�ô����/����û���
	if (!m_wndSplitter.CreateStatic(this, 1, 3, WS_CHILD | WS_VISIBLE))
	{
		TRACE("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	// ��ߵĹ���������
	if (!m_wndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(MyRenderToolBoard), CSize(45, 200), pContext))
	{
		TRACE("Failed to create command view pane\n");
		return FALSE;
	}

	// �м��ģ����ʾ����
	if (!m_wndSplitter.CreateView(0, 1,
		RUNTIME_CLASS(CMy3D_PCD2View), CSize(1155, 200), pContext))
	{
		TRACE("Failed to create preview pane\n");
		return FALSE;
	}

	// �ұߵ�������ʾ������
	if (!m_wndSplitter.CreateView(0, 2,
		RUNTIME_CLASS(PropertyBoard), CSize(100, 200), pContext))
	{
		TRACE("Failed to create preview pane\n");
		return FALSE;
	}
	m_MyDrawView = (CMy3D_PCD2View*) m_wndSplitter.GetPane(0, 1);
	SetActiveView(m_MyDrawView, true);
	m_LeftView = (MyRenderToolBoard*) m_wndSplitter.GetPane(0, 0);
	m_RightView = (PropertyBoard*) m_wndSplitter.GetPane(0, 2);
	return TRUE;
}

//�˵����ı߽籣��
void CChildFrame::OnMenuBoundaryKeep()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		m_MyDrawView->b_BoundaryChecked = true;
		m_RightView->GetProperties();//�����԰��ȡ�㷨����
		AfxBeginThread(BCfunction, this);//����һ��������ִ��function1�����б߽籣��
		ProgressDialog dlg;
		dlg.DoModal();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//�˵����ı߽����
void CChildFrame::OnMenuBoundaryCluster()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_BoundaryChecked)
		{
			((CChildFrame*)AfxGetApp())->m_MyDrawView->b_BoundaryCluster = true;
			((CChildFrame*)AfxGetApp())->m_RightView->GetProperties();//�����԰��ȡ�㷨����
			((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCloudBoundaryClustering();
		}
		else
		{
			MessageBox("���Ƚ���ģ�͵ı߽籣��!", "��ʾ");
		}
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//�˵����Ŀ׶��޲�
void CChildFrame::OnMenuHoleRepair()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_SelectedPoints)
		{
			AfxBeginThread(HRfunction, this);//������һ��������ִ��function2,����ģ�͵Ŀ׶��޲�
			ProgressDialog dlg;
			dlg.DoModal();
			((CChildFrame*)AfxGetApp())->m_MyDrawView->b_SelectedPoints = false;
		}
		else
		{
			MessageBox("���Ƚ���Լ�����ѡ��", "��ʾ");
		}
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//�˵������Զ��׶��޲�
void CChildFrame::OnAutomaticHoleRepair()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_BoundaryCluster)
		{
			AfxBeginThread(AHRfunction, this);//������һ��������ִ��function2,����ģ�͵Ŀ׶��޲�
			ProgressDialog dlg;
			dlg.DoModal();
		}
		else
		{
			MessageBox("���Ƚ��б߽����!", "��ʾ");
		}
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//�˵���ģ�͵ı�������
void CChildFrame::OnMenuSurfaceGeneration()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_RightView->GetProperties();//�����԰��ȡ�㷨����
		AfxBeginThread(Sufunction, this);//������һ��������ִ��function2,����ģ�͵Ŀ׶��޲�
		ProgressDialog dlg;
		dlg.DoModal();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//�˵�����������ʾģʽ
void CChildFrame::OnMenuTriShow()
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->SetTriWindowsMode();
}

//�˵���������ʾ
void CChildFrame::OnMenuSingleShow()
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->SetSingleWindowMode();
}

//�˵���һ���޲�
void CChildFrame::OnMenuOneStepRepair()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_RightView->GetProperties();//�����԰��ȡ�㷨����
		AfxBeginThread(OneStepfunction, this);//������һ��������ִ��function2,����ģ�͵Ŀ׶��޲�
		ProgressDialog dlg;
		dlg.DoModal();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//�˵���һ���޲������б�������
void CChildFrame::OnMenuOneStepRepairAndSurface()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_RightView->GetProperties();//�����԰��ȡ�㷨����
		AfxBeginThread(OneStepAndSurfacefunction, this);//������һ��������ִ��function2,����ģ�͵Ŀ׶��޲�
		ProgressDialog dlg;
		dlg.DoModal();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}


void CChildFrame::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (b_Saved == false && b_FIP == true)
	{
		if (IDNO == ::MessageBox(this->m_hWnd, _T("��δ���б���,�Ƿ�ֱ�ӹر�?"), _T("��ʾ"), MB_ICONQUESTION | MB_YESNO))
		{
			return;
		}
	}
	CMDIChildWnd::OnClose();
}


void CChildFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CMDIChildWnd::OnPaint()
	/*CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(100, 100, 100));   //����Ϊ��ɫ����
	*/
}
