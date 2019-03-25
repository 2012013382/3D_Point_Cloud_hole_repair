// PropertyBoard.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3D_PCD2.h"
#include "PropertyBoard.h"
#include "ChildFrm.h"
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
// PropertyBoard

IMPLEMENT_DYNCREATE(PropertyBoard, CFormView)

PropertyBoard::PropertyBoard()
	: CFormView(PropertyBoard::IDD)
	, m_RotationX(0.0)
	, m_RotationY(0.0)
	, m_textBoundary(0.05)
	, m_clusterDistace(0.05)
	, m_clusterNum(20)
	, m_trianMaxDistace(0.05)
	, m_trianMaxAngle(4.5)
	, m_trianMinAngle(0.1)
	, m_trianMaxSAngle(0.9)
{
	((CChildFrame*)AfxGetApp())->m_RightView = this;
	b_FirstTime = true;
}

PropertyBoard::~PropertyBoard()
{
}

void PropertyBoard::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	if (b_FirstTime)
	{
		SetDlgItemText(IDC_EDITX, "0.0");
		SetDlgItemText(IDC_EDITY, "0.0");
		SetDlgItemText(IDC_EDITZ, "0.0");
		SetDlgItemText(IDC_EDITBCOE, "0.05");
		SetDlgItemText(IDC_EDITMINDISTANCE, "0.05");
		SetDlgItemText(IDC_EDITMINNUM, "20");
		SetDlgItemText(IDC_EDITMAXDISTANCE, "0.05");
		SetDlgItemText(IDC_EDITMAXANGLE, "4.5");
		SetDlgItemText(IDC_EDITMINANGLE, "0.1");
		SetDlgItemText(IDC_EDITMAXSEARCHD, "0.9");
		b_FirstTime = false;
	}
	HBITMAP   hBitmap1;
	hBitmap1 = (HBITMAP)::LoadImage(
		NULL,
		"D://help.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_MYHELP))->SetBitmap(hBitmap1);
	
	HBITMAP   hBitmap2;
	hBitmap2 = (HBITMAP)::LoadImage(
		NULL,
		"D://sure.bmp",                           // ͼƬȫ·��  
		IMAGE_BITMAP,                          // ͼƬ��ʽ  
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);  // ע��LR_LOADFROMFILE  
	((CButton *)GetDlgItem(IDC_SETANGLE))->SetBitmap(hBitmap2);
}

BEGIN_MESSAGE_MAP(PropertyBoard, CFormView)
	ON_BN_CLICKED(IDC_SETANGLE, &PropertyBoard::OnBnClickedSetangle)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MYHELP, &PropertyBoard::OnBnClickedMyhelp)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// PropertyBoard ���

#ifdef _DEBUG
void PropertyBoard::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void PropertyBoard::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// PropertyBoard ��Ϣ�������
void PropertyBoard::SetNameAndNum()
{
	char* fileName = ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_ShowFileName;
	SetDlgItemText(IDC_EDITNAME, fileName);
	int num = ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_ShowPointCloudNum;
	char cNum[10];
	wsprintf(cNum, "%d", num);
	SetDlgItemText(IDC_EDITPOINTNUM, cNum);
}
//��ȡ�����ù۲�ǶȲ���
void PropertyBoard::GetAndSetAngleProperties()
{
	char textX[10];
	char textY[10];
	//��ȡ�û�����ֵ
	GetDlgItemText(IDC_EDITX, textX, 10);
	GetDlgItemText(IDC_EDITY, textY, 10);
	double dX = atof(textX);
	double dY = atof(textY);
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_xRotation = dX;
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_yRotation = dY;
}
//���ù۲�Ƕ�
void PropertyBoard::OnBnClickedSetangle()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetAndSetAngleProperties();
	//�����ػ�
	((CChildFrame*)AfxGetApp())->m_MyDrawView->ViewInvalidateRect();
}
//��ʾ�۲�ǶȲ���
void PropertyBoard::SetAngle()
{
	double x, y;
	x = ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_xRotation;
	y = ((CChildFrame*)AfxGetApp())->m_MyDrawView->m_yRotation;
	char cX[20];
	char cY[20];
	sprintf(cX, "%f", x);
	sprintf(cY, "%f", y);
	SetDlgItemText(IDC_EDITX, cX);
	SetDlgItemText(IDC_EDITY, cY);
}
//��ȡ���԰����
void PropertyBoard::GetProperties()
{
	char textBoundary[10];
	char clusterDistace[10];
	char clusterNum[10];
	char trianMaxDistace[10];
	char trianMaxAngle[10];
	char trianMinAngle[10];
	char trianMaxSAngle[10];
	GetDlgItemText(IDC_EDITBCOE, textBoundary, 10);
	GetDlgItemText(IDC_EDITMINDISTANCE, clusterDistace, 10);
	GetDlgItemText(IDC_EDITMINNUM, clusterNum, 10);
	GetDlgItemText(IDC_EDITMAXDISTANCE, trianMaxDistace, 10);
	GetDlgItemText(IDC_EDITMAXANGLE, trianMaxAngle, 10);
	GetDlgItemText(IDC_EDITMINANGLE, trianMinAngle, 10);
	GetDlgItemText(IDC_EDITMAXSEARCHD, trianMaxSAngle, 10);
	
	double d_textBoundary = atof(textBoundary);
	double d_clusterDistace = atof(clusterDistace);
	double d_clusterNum = atof(clusterNum);
	double d_trianMaxDistace = atof(trianMaxDistace);
	double d_trianMaxAngle = atof(trianMaxAngle);
	double d_trianMinAngle = atof(trianMinAngle);
	double d_trianMaxSAngle = atof(trianMaxSAngle);
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_myPointCloudData.Threadshold = d_textBoundary;
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_myPointCloudData.m_clusterDistace = d_clusterDistace;
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_myPointCloudData.m_clusterNum = d_clusterNum;
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_myPointCloudData.m_trianMaxDistace = d_trianMaxDistace;
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_myPointCloudData.m_trianMaxAngle = d_trianMaxAngle;
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_myPointCloudData.m_trianMinAngle = d_trianMinAngle;
	((CChildFrame*)AfxGetApp())->m_MyDrawView->m_myPointCloudData.m_trianMaxSAngle = d_trianMaxSAngle;

}

void PropertyBoard::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()
//	CRect   rect;
//	GetClientRect(rect);
//	dc.FillSolidRect(rect, RGB(100,100,100));   //����Ϊ��ɫ����
}


void PropertyBoard::OnBnClickedMyhelp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBox("��鿴˵���ĵ���","��ʾ");
}


HBRUSH PropertyBoard::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	/*// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetBkColor(RGB(100, 100, 100));//����ɫΪ��ɫ
		//pDC->SetBkMode(TRANSPARENT);//�豳��Ϊ͸��
		pDC->SetTextColor(RGB(255, 255, 255));//����Ϊ��ɫ
	}
	if (pWnd->GetDlgCtrlID() == IDC_SETANGLE)
	{
		pDC->SetBkColor(RGB(100, 100, 100));//����ɫΪ��ɫ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������*/
	return hbr;
}
