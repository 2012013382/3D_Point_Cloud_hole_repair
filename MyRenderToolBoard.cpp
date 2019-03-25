// MyRenderToolBoard.cpp : ʵ���ļ�
//��Ⱦ���࣬ʵ�ֹ�������������Ⱦ���ߵ�ѡ��

#include "stdafx.h"
#include "3D_PCD2.h"
#include "MyRenderToolBoard.h"
#include "ProgressDialog.h"
#include "3D_PCD2View.h"
#include"ChildFrm.h"
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
// MyRenderToolBoard



MyRenderToolBoard::MyRenderToolBoard()
: CFormView(IDD_MY_RENDER_TOOL)
{
	((CChildFrame*)AfxGetApp())->m_LeftView = this;
}

MyRenderToolBoard::~MyRenderToolBoard()
{
}

void MyRenderToolBoard::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//Ϊ��ť����ͼƬ
	HBITMAP   hBitmap1;
	hBitmap1 = (HBITMAP)::LoadImage(
		NULL,
		"res\1.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_NORMALMODE))->SetBitmap(hBitmap1);

	HBITMAP   hBitmap2;
	hBitmap2 = (HBITMAP)::LoadImage(
		NULL,
		"res\2.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_GETPOINT))->SetBitmap(hBitmap2);

	HBITMAP   hBitmap3;
	hBitmap3 = (HBITMAP)::LoadImage(
		NULL,
		"res\3.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_GETREPOINT))->SetBitmap(hBitmap3);
	
	HBITMAP   hBitmap4;
	hBitmap4 = (HBITMAP)::LoadImage(
		NULL,
		"res\4.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_BSAVE))->SetBitmap(hBitmap4);

	HBITMAP   hBitmap5;
	hBitmap5 = (HBITMAP)::LoadImage(
		NULL,
		"res\5.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_HOLEREPAIR))->SetBitmap(hBitmap5);

	HBITMAP   hBitmap6;
	hBitmap6 = (HBITMAP)::LoadImage(
		NULL,
		"res\6.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_POINTPROPERTY))->SetBitmap(hBitmap6);
	
	HBITMAP   hBitmap7;
	hBitmap7 = (HBITMAP)::LoadImage(
		NULL,
		"res\7.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_SINGLEWINDOW))->SetBitmap(hBitmap7);
	
	HBITMAP   hBitmap8;
	hBitmap8 = (HBITMAP)::LoadImage(
		NULL,
		"res\8.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_TRIWINDOW))->SetBitmap(hBitmap8);
	
	HBITMAP   hBitmap9;
	hBitmap9 = (HBITMAP)::LoadImage(
		NULL,
		"res\9.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_SURFACE))->SetBitmap(hBitmap9);

	HBITMAP   hBitmap10;
	hBitmap10 = (HBITMAP)::LoadImage(
		NULL,
		"res\10.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_LIMITSELF))->SetBitmap(hBitmap10);

	HBITMAP   hBitmap11;
	hBitmap11 = (HBITMAP)::LoadImage(
		NULL,
		"res\11.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_CLUSTER))->SetBitmap(hBitmap11);

	HBITMAP   hBitmap12;
	hBitmap12 = (HBITMAP)::LoadImage(
		NULL,
		"res\12.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_MAXERSIZE))->SetBitmap(hBitmap12);
	
	HBITMAP   hBitmap13;
	hBitmap13 = (HBITMAP)::LoadImage(
		NULL,
		"res\13.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_MINERSIZE))->SetBitmap(hBitmap13);

	HBITMAP   hBitmap14;
	hBitmap14 = (HBITMAP)::LoadImage(
		NULL,
		"res\14.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_NORMALVECTOR))->SetBitmap(hBitmap14);

	HBITMAP   hBitmap15;
	hBitmap15 = (HBITMAP)::LoadImage(
		NULL,
		"res\15.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_AHREPAIR))->SetBitmap(hBitmap15);

	HBITMAP   hBitmap16;
	hBitmap16 = (HBITMAP)::LoadImage(
		NULL,
		"res\16.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_HRASUR))->SetBitmap(hBitmap16);

	//��Ӱ�ť����ʾ��Ϣ
	m_Mytip.Create(this);
	m_Mytip.AddTool(GetDlgItem(IDC_NORMALMODE), "��ͨģʽ");
	m_Mytip.AddTool(GetDlgItem(IDC_GETPOINT), "���ʰȡģʽ");
	m_Mytip.AddTool(GetDlgItem(IDC_POINTPROPERTY), "������ʰȡģʽ");
	m_Mytip.AddTool(GetDlgItem(IDC_GETREPOINT), "Լ����ѡ��ģʽ");
	m_Mytip.AddTool(GetDlgItem(IDC_BSAVE), "�߽籣��");
	m_Mytip.AddTool(GetDlgItem(IDC_HOLEREPAIR), "�׶��޲�");
	m_Mytip.AddTool(GetDlgItem(IDC_LIMITSELF), "�Զ��׶��޲�");
	m_Mytip.AddTool(GetDlgItem(IDC_CLUSTER), "�߽����");
	m_Mytip.AddTool(GetDlgItem(IDC_SURFACE), "��������");
	m_Mytip.AddTool(GetDlgItem(IDC_MAXERSIZE), "�Ŵ�");
	m_Mytip.AddTool(GetDlgItem(IDC_MINERSIZE), "��С");
	m_Mytip.AddTool(GetDlgItem(IDC_SINGLEWINDOW), "������ʾ");
	m_Mytip.AddTool(GetDlgItem(IDC_TRIWINDOW), "������ʾ");
	m_Mytip.AddTool(GetDlgItem(IDC_NORMALVECTOR), "��ʾ/����ʾ��ʸ��");
	m_Mytip.AddTool(GetDlgItem(IDC_AHREPAIR), "һ���޲�");
	m_Mytip.AddTool(GetDlgItem(IDC_HRASUR), "һ���޲��������ؽ�");
	m_Mytip.SetDelayTime(200); //�����ӳ�
	//m_Mytip.SetTipTextColor(RGB(0, 0, 255)); //������ʾ�ı�����ɫ
	//m_Mytip.SetTipBkColor(RGB(255, 255, 255)); //������ʾ��ı�����ɫ
	m_Mytip.Activate(TRUE); //�����Ƿ�������ʾ

}
IMPLEMENT_DYNCREATE(MyRenderToolBoard, CFormView)

BEGIN_MESSAGE_MAP(MyRenderToolBoard, CFormView)
	ON_BN_CLICKED(IDC_GETPOINT, &MyRenderToolBoard::OnBnClickedGetpoint)
	ON_BN_CLICKED(IDC_NORMALMODE, &MyRenderToolBoard::OnBnClickedNormalmode)
	ON_BN_CLICKED(IDC_GETREPOINT, &MyRenderToolBoard::OnBnClickedGetrepoint)
	ON_BN_CLICKED(IDC_BSAVE, &MyRenderToolBoard::OnBnClickedBsave)
	ON_BN_CLICKED(IDC_HOLEREPAIR, &MyRenderToolBoard::OnBnClickedHolerepair)
	ON_BN_CLICKED(IDC_SINGLEWINDOW, &MyRenderToolBoard::OnBnClickedSinglewindow)
	ON_BN_CLICKED(IDC_TRIWINDOW, &MyRenderToolBoard::OnBnClickedTriwindow)
	ON_BN_CLICKED(IDC_CLUSTER, &MyRenderToolBoard::OnBnClickedCluster)
	ON_BN_CLICKED(IDC_LIMITSELF, &MyRenderToolBoard::OnBnClickedLimitself)
	ON_BN_CLICKED(IDC_SURFACE, &MyRenderToolBoard::OnBnClickedSurface)
	ON_BN_CLICKED(IDC_POINTPROPERTY, &MyRenderToolBoard::OnBnClickedPointproperty)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MAXERSIZE, &MyRenderToolBoard::OnBnClickedMaxersize)
	ON_BN_CLICKED(IDC_MINERSIZE, &MyRenderToolBoard::OnBnClickedMinersize)
	ON_BN_CLICKED(IDC_NORMALVECTOR, &MyRenderToolBoard::OnBnClickedNormalvector)
	ON_BN_CLICKED(IDC_AHREPAIR, &MyRenderToolBoard::OnBnClickedAhrepair)
	ON_BN_CLICKED(IDC_HRASUR, &MyRenderToolBoard::OnBnClickedHrasur)
END_MESSAGE_MAP()


// MyRenderToolBoard ���

#ifdef _DEBUG
void MyRenderToolBoard::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MyRenderToolBoard::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MyRenderToolBoard ��Ϣ�������

//����Ϊ���ʰȡģʽ
void MyRenderToolBoard::OnBnClickedGetpoint()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_MyDrawView->SetSelectingMode();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//����Ϊ��ͨ��ʾģʽ
void MyRenderToolBoard::OnBnClickedNormalmode()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CChildFrame*)AfxGetApp())->m_MyDrawView->SetNormalMode();
}

//��ΪԼ����ѡ��ģʽ
void MyRenderToolBoard::OnBnClickedGetrepoint()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_MyDrawView->b_SelectedPoints = true;
		((CChildFrame*)AfxGetApp())->m_MyDrawView->SetGetRPMode();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!","��ʾ");
	}
}

//��ģ�ͽ��б߽籣��
void MyRenderToolBoard::OnBnClickedBsave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_MyDrawView->b_BoundaryChecked = true;
		((CChildFrame*)AfxGetApp())->m_RightView->GetProperties();//�����԰��ȡ�㷨����
		AfxBeginThread(BCfunction, this);//����һ��������ִ��function1�����б߽籣��
		ProgressDialog dlg;
		dlg.DoModal();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
}

//���п׶��޲�
void MyRenderToolBoard::OnBnClickedHolerepair()
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


void MyRenderToolBoard::OnBnClickedProgress()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

UINT BCfunction(LPVOID pParam)
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCloudBoundaryCheck();
	gProgress = 0;
	return 0;
}

UINT HRfunction(LPVOID pParam)
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCloudHoleRepair();
	gProgress = 0;
	return 0;
}
UINT AHRfunction(LPVOID pParam)
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCloudAutomaticHoleRepair();
	gProgressAu = 0;
	return 0;
}
UINT Sufunction(LPVOID pParam)
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCLoudSurfaceGenerating();
	gProgress = 0;
	return 0;
}
UINT OneStepfunction(LPVOID pParam)
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCloudOneStepRepair();
	gProgressAu = 0;
	return 0;
}
UINT OneStepAndSurfacefunction(LPVOID pParam)
{
	((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCloudOneStepRepairAndSurface();
	gProgressAu = 0;
	return 0;
}
//����Ϊ��һ����
void MyRenderToolBoard::OnBnClickedSinglewindow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CChildFrame*)AfxGetApp())->m_MyDrawView->SetSingleWindowMode();
}

//����Ϊ����ͼ
void MyRenderToolBoard::OnBnClickedTriwindow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	((CChildFrame*)AfxGetApp())->m_MyDrawView->SetTriWindowsMode();
}

//���б߽����
void MyRenderToolBoard::OnBnClickedCluster()
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

//�Զ��޲�
void MyRenderToolBoard::OnBnClickedLimitself()
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

//���е��Ƶ����ǻ�
void MyRenderToolBoard::OnBnClickedSurface()
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


void MyRenderToolBoard::OnBnClickedPointproperty()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_MyDrawView->SetGetPointPropertyMode();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}
	
}


void MyRenderToolBoard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(100,100,100));   //����Ϊ��ɫ����
	
}

BOOL MyRenderToolBoard::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_MOUSEMOVE)
	{
		m_Mytip.RelayEvent(pMsg);
	}
   return CFormView::PreTranslateMessage(pMsg);
}

//�Ŵ�ť
void MyRenderToolBoard::OnBnClickedMaxersize()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_MyDrawView->m_xScaling = 1.2
			* ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_xScaling;

		((CChildFrame*)AfxGetApp())->m_MyDrawView->m_yScaling = 1.2
			* ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_yScaling;

		((CChildFrame*)AfxGetApp())->m_MyDrawView->m_zScaling = 1.2
			* ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_zScaling;
		((CChildFrame*)AfxGetApp())->m_MyDrawView->ViewInvalidateRect();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}

}
//��С��ť
void MyRenderToolBoard::OnBnClickedMinersize()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_MyDrawView->m_xScaling = 0.8
			* ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_xScaling;

		((CChildFrame*)AfxGetApp())->m_MyDrawView->m_yScaling = 0.8
			* ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_yScaling;

		((CChildFrame*)AfxGetApp())->m_MyDrawView->m_zScaling = 0.8
			* ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_zScaling;
		((CChildFrame*)AfxGetApp())->m_MyDrawView->ViewInvalidateRect();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}

}

//��ʾ�������ݵ�ķ�ʸ��
void MyRenderToolBoard::OnBnClickedNormalvector()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (((CChildFrame*)AfxGetApp())->m_MyDrawView->b_FileInputed)
	{//���Ѿ�����ģ���ļ���
		((CChildFrame*)AfxGetApp())->m_MyDrawView->PointCloudGetSelectedPointsNormalVectors();
	}
	else
	{
		MessageBox("δ�����κ�ģ��!", "��ʾ");
	}

}

//ģ��һ���޲�
void MyRenderToolBoard::OnBnClickedAhrepair()
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

//ģ��һ���޲������б����޲�
void MyRenderToolBoard::OnBnClickedHrasur()
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


