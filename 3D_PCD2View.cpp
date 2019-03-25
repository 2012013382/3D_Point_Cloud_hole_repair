
// 3D_PCD2View.cpp : CMy3D_PCD2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "3D_PCD2.h"
#endif

#include "3D_PCD2Doc.h"
#include "3D_PCD2View.h"
#include "ChildFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3D_PCD2View

IMPLEMENT_DYNCREATE(CMy3D_PCD2View, CView)

BEGIN_MESSAGE_MAP(CMy3D_PCD2View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, &CMy3D_PCD2View::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMy3D_PCD2View::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMy3D_PCD2View::OnFileSaveAs)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CMy3D_PCD2View ����/����

CMy3D_PCD2View::CMy3D_PCD2View()
{
	// TODO: �ڴ˴���ӹ������
	((CChildFrame*)AfxGetApp())->m_MyDrawView = this;
	// OpenGL
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;
	// Mouse
	b_LeftButtonDown = FALSE;
	b_RightButtonDown = FALSE;
	//m_CursorRotation = AfxGetApp()->LoadCursor(IDC_CURSOR_ROTATION);
	//��ʼ������������ʾ�ı���
	b_FileInputed = FALSE;
	b_BoundaryChecked = false;
	b_BoundaryCluster = false;
	b_SelectedPoints = false;
	InitGeometry();
	//��Ϊ��ʰȡģʽ
	b_SelectingMode = false;
	//��Ϊ��Լ����ѡ��ģʽ
	b_GetingRPMode = false;
	//����Ϊ�ǵ�����ѡ��ģʽ
	b_SelectingPointPropertyMode = false;
	//����ͼ��ʾ
	b_TriWindowMode = false;
	b_LeftButtonFirstDown = true;
	b_SurfaceGenerated = false;
	b_NormalVectorMode = false;
	b_test = false;

}

void CMy3D_PCD2View::InitGeometry(void)
{
	m_xRotation = 0.0f;
	m_yRotation = 0.0f;
	m_xTranslation = 0.0f;
	m_yTranslation = 0.0f;
	m_zTranslation = 0.0f;
	m_xScaling = 1.0f;
	m_yScaling = 1.0f;
	m_zScaling = 1.0f;
}

CMy3D_PCD2View::~CMy3D_PCD2View()
{
}

BOOL CMy3D_PCD2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMy3D_PCD2View ����

void CMy3D_PCD2View::OnDraw(CDC* /*pDC*/)
{
	CMy3D_PCD2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMy3D_PCD2View ��ӡ

BOOL CMy3D_PCD2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMy3D_PCD2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMy3D_PCD2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMy3D_PCD2View ���

#ifdef _DEBUG
void CMy3D_PCD2View::AssertValid() const
{
	CView::AssertValid();
}

void CMy3D_PCD2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3D_PCD2Doc* CMy3D_PCD2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3D_PCD2Doc)));
	return (CMy3D_PCD2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy3D_PCD2View ��Ϣ�������


int CMy3D_PCD2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if (SetWindowPixelFormat(hDC) == FALSE)
	{
		return 0;
	}

	if (CreateViewGLContext(hDC) == FALSE)
	{
		return 0;
	}
	/*
	glEnable(GL_NORMALIZE);//���й���ģ��ǰ��Ҫ�Է��������е�λ������
	//��ʼ���й��ռ���.
	//glClearDepth(1);
	GLfloat light1PosType[] = { 0.0, 1.0, 0.0, 0.0 };//����һ������Զ�Ĺ�Դ
	glLightfv(GL_LIGHT1, GL_POSITION, light1PosType);
	// Default : lighting
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	*/
	return 0;
}

bool CMy3D_PCD2View::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;

	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if (m_GLPixelIndex == 0) // Choose default
	{
		m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
			return FALSE;
	}

	if (!SetPixelFormat(hDC, m_GLPixelIndex, &pixelDesc))
		return FALSE;

	return TRUE;
}

bool CMy3D_PCD2View::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);

	if (m_hGLContext == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return FALSE;

	return TRUE;
}


void CMy3D_PCD2View::OnDestroy()
{
	if (wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL, NULL);

	if (m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}

	CView::OnDestroy();
}


void CMy3D_PCD2View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_DisplayWidth = cx;
	m_DisplayHeight = cy;
	//glDrawBuffer(GL_BACK);
	//glEnable(GL_DEPTH_TEST);//������������ʾ���

}

//�������������Ϣ��Ӧ����
void CMy3D_PCD2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	b_LeftButtonDown = TRUE;
	m_LeftDownPos = point;
	if (b_SelectingMode == true || b_SelectingPointPropertyMode == true)
	{
		SelectObject(point,point);//���ʰȡ
	}
	InvalidateRect(NULL, FALSE);
	CView::OnLButtonDown(nFlags, point);
}

//�������������Ϣ��Ӧ����
void CMy3D_PCD2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (b_GetingRPMode == true)
	{//��ʱΪԼ����ѡ��ģʽ
		SelectObject(point, m_LastPoint);
	}
	b_LeftButtonFirstDown = true;
	b_LeftButtonDown = FALSE;
	InvalidateRect(NULL, FALSE);
	CView::OnLButtonUp(nFlags, point);
}


void CMy3D_PCD2View::OnMouseMove(UINT nFlags, CPoint point)
{
	if (b_LeftButtonDown)//���������ת��
	{
		if (b_LeftButtonFirstDown == true)
		{
			m_LastPoint = point;
			b_LeftButtonFirstDown = false;
		}
		if (b_SelectingMode == false && b_GetingRPMode == false && b_SelectingPointPropertyMode == false)
		{
			m_yRotation -= (float)(m_LeftDownPos.x - point.x) / 3.0f;
			m_xRotation -= (float)(m_LeftDownPos.y - point.y) / 3.0f;
			((CChildFrame*)AfxGetApp())->m_RightView->SetAngle();
			m_LeftDownPos = point;
		}
		InvalidateRect(NULL, FALSE);
	}
	else if (b_RightButtonDown)
	{
		m_xScaling -= (float)(m_RightDownPos.x - point.x) / 50;
		if (m_xScaling <= 0)
		{
			m_xScaling += (float)(m_RightDownPos.x - point.x) / 50;
		}
		else
		{
			m_yScaling -= (float)(m_RightDownPos.x - point.x) / 50;
			m_zScaling -= (float)(m_RightDownPos.x - point.x) / 50;
		}
		m_RightDownPos = point;
		InvalidateRect(NULL, FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}

//�Դ����ڵ����ݽ��л���


void CMy3D_PCD2View::OnPaint()
{
	// Device context for painting
	CPaintDC dc(this);

	// Useful in multidoc templates
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);
	wglMakeCurrent(hDC, m_hGLContext);

	// Start rendering...
	//����������ط����Ե���һ������ģ�͵Ļ��ƺ���
	PointCloudDisplay();
	if (b_SurfaceGenerated)
	{
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		//������Դ
		GLfloat light_position0[] = { 0.0f, 0.0f, -1.0f, 0.0f };
		GLfloat light_position1[] = { 0.0f, 0.0f, 1.0f, 0.0f };
		GLfloat light_position2[] = { 0.0f, 1.0f, 0.0f, 0.0f };
		GLfloat light_position3[] = { 0.0f, -1.0f, 0.0f, 0.0f };
		GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
		glEnable(GL_LIGHTING);        //�������չ��ܣ�����������
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);//����˫�����(important!)
		InvalidateRect(NULL, FALSE);
	}
	/*GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	*/
	// Double buffer
	//��������������ʾ�������е����ݣ�
	//�������ô������˫����ļ����¾Ϳ�����ͼ���ˡ�
	SwapBuffers(dc.m_ps.hdc);
}

void CMy3D_PCD2View::PointCloudDisplay()
{
	if (b_TriWindowMode)/*�ඥ��ͼ*/
	{
		glEnable(GL_SCISSOR_TEST);/*�������ò���*/
		glScissor(0, 0, m_DisplayWidth / 2, m_DisplayHeight);/*��һ����ʾ�����СΪ�����ͻ��������*/
		glClearColor(1, 1, 1, 1.0);/*���õ�һ���ͻ�����������ɫ*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);/*�����ɫ�������Ȼ���*/
		//glClearDepth(1.0);
		glDisable(GL_SCISSOR_TEST);/*�رռ��ò���*/
		glViewport(0, 0, m_DisplayWidth / 2, m_DisplayHeight);/*�����ӿ�*/

		glMatrixMode(GL_PROJECTION);//����ͶӰģʽ
		glLoadIdentity();/*��յ�ǰ����*/
		if ((m_DisplayWidth / 2) <= m_DisplayHeight)/*����ͶӰ��ʽ*/
		{
			glOrtho(-1.5, 1.5, -1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth / 2), 1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth / 2), -10.0, 10.0);
		}
		else
		{
			glOrtho(-1.5*(GLdouble)(m_DisplayWidth / 2) / (GLdouble)m_DisplayHeight, 1.5*(GLdouble)(m_DisplayWidth / 2) / (GLdouble)m_DisplayHeight, -1.5, 1.5, -10.0, 10.0);
		}
		//�������������Ϊǰ��
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 1.5, 0, 0, 0, 0, 1, 0);
		ReadPointCloudData();


		glEnable(GL_SCISSOR_TEST);/*�������ò���*/
		glScissor(m_DisplayWidth / 2, 0, m_DisplayWidth / 2, m_DisplayHeight / 2);/*�ڶ�������Ĵ�СΪ�Ұ벿�ֵ��ϰ벿��*/
		glClearColor(1 - 0.05, 1 - 0.05, 1 - 0.05, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearDepth(1.0);
		glDisable(GL_SCISSOR_TEST);
		glViewport(m_DisplayWidth / 2, 0, m_DisplayWidth / 2, m_DisplayHeight / 2);


		glMatrixMode(GL_PROJECTION);//����ͶӰģʽ
		glLoadIdentity();/*��յ�ǰ����*/
		if ((m_DisplayWidth) <= m_DisplayHeight)/*����ͶӰ��ʽ*/
		{
			glOrtho(-1.5, 1.5, -1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth), 1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth), -10.0, 10.0);
		}
		else
		{
			glOrtho(-1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, 1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, -1.5, 1.5, -10.0, 10.0);
		}
		//�������������Ϊ����
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(1.5, 0, 0, 0, 0, 0, 0, 1, 0);
		ReadPointCloudData();

		glEnable(GL_SCISSOR_TEST);
		glScissor(m_DisplayWidth / 2, m_DisplayHeight / 2, m_DisplayWidth / 2, m_DisplayHeight / 2);/*�������ͻ������Ұ벿�ֵ��°벿��*/
		glClearColor(1 - 0.1, 1 - 0.1, 1 - 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	glClearDepth(1.0);
		glDisable(GL_SCISSOR_TEST);
		glViewport(m_DisplayWidth / 2, m_DisplayHeight / 2, m_DisplayWidth / 2, m_DisplayHeight / 2);


		glMatrixMode(GL_PROJECTION);//����ͶӰģʽ
		glLoadIdentity();/*��յ�ǰ����*/
		if ((m_DisplayWidth) <= m_DisplayHeight)/*����ͶӰ��ʽ*/
		{
			glOrtho(-1.5, 1.5, -1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth), 1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth), -10.0, 10.0);
		}
		else
		{
			glOrtho(-1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, 1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, -1.5, 1.5, -10.0, 10.0);
		}
		//�������������Ϊ�Ϸ�
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 1.5, 0, 0, 0, 0, 0, 0, -1);
		ReadPointCloudData();
	}
	else/*ȫ����ͼ��*/
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearDepth(1.0);
		glViewport(0, 0, m_DisplayWidth, m_DisplayHeight);

		glMatrixMode(GL_PROJECTION);//����ͶӰģʽ
		glLoadIdentity();
		if ((m_DisplayWidth) <= m_DisplayHeight)
		{
			glOrtho(-1.5, 1.5, -1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth), 1.5*(GLdouble)m_DisplayHeight / (GLdouble)(m_DisplayWidth), -10.0, 10.0);
		}
		else
		{
			glOrtho(-1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, 1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, -1.5, 1.5, -10.0, 10.0);
		}
		//glFrustum( -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 );

		//�趨�������λ�ú���Ӱ����
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 1.5, 0, 0, 0, 0, 1, 0);
		ReadPointCloudData();
	}
	//////////////////////////////////////////////////////////////////
	glFlush();/*ǿ����ʾģ��*/
}
//��ȡ��������
void CMy3D_PCD2View::ReadPointCloudData()
{
	// Position / translation / scale
	glTranslated(m_xTranslation, m_yTranslation, m_zTranslation);
	glRotatef(m_xRotation, 1.0, 0.0, 0.0);
	glRotatef(m_yRotation, 0.0, 1.0, 0.0);
	glScalef(m_xScaling, m_yScaling, m_zScaling);
	//��ʼ��һ����ʱ���ƴ洢��
	if (b_FileInputed && !b_SurfaceGenerated)
	{
		glPointSize(4.0);
		PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();//��ȡ����ģ��
		for (int num = 0; num < m_myPointCloudData.GetPointSumNumber(); num++)
		{
			glLoadName(num);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_DOUBLE, 0, tempPointCloud[num].m_Coordinate);
			glColorPointer(3, GL_DOUBLE, 0, tempPointCloud[num].m_Color);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		//��ʾ������޲���
		vector<PCPoint>* AddedPoingCLoud = m_myPointCloudData.GetNewAddedPoint();
		for (int num = 0; num < AddedPoingCLoud->size(); num++)
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_DOUBLE, 0, (*AddedPoingCLoud)[num].m_Coordinate);
			glColorPointer(3, GL_DOUBLE, 0, (*AddedPoingCLoud)[num].m_Color);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		//��ʾ�߽�����Ľ��
		if (b_test)
		{
			vector<PCPoint>* boundaryPointClusters = m_myPointCloudData.GetBoundaryPointClusters();
			for (int i = 0; i < m_myPointCloudData.GetCloudClusterNum(); i++)
			{
				for (int num = 0; num < boundaryPointClusters[i].size(); num++)
				{
					glEnableClientState(GL_VERTEX_ARRAY);
					glEnableClientState(GL_COLOR_ARRAY);
					glVertexPointer(3, GL_DOUBLE, 0, boundaryPointClusters[i][num].m_Coordinate);
					glColorPointer(3, GL_DOUBLE, 0, boundaryPointClusters[i][num].m_Color);
					glDrawArrays(GL_POINTS, 0, 1);
				}
			}
		}
		if (b_NormalVectorMode)
		{//���Ϊ��ʸ����ʾģʽ������з�ʸ������ʾ
			for (int num = 0; num < m_myPointCloudData.m_SelectedPointsNormalPoints.size(); num++)
			{
				glBegin(GL_LINES);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(m_myPointCloudData.m_SelectedPointsNormalPoints[num].m_Coordinate[0]
					, m_myPointCloudData.m_SelectedPointsNormalPoints[num].m_Coordinate[1]
					, m_myPointCloudData.m_SelectedPointsNormalPoints[num].m_Coordinate[2]);
				glVertex3f(m_myPointCloudData.m_SelectedPointsNormalPoints2[num].m_Coordinate[0]
					, m_myPointCloudData.m_SelectedPointsNormalPoints2[num].m_Coordinate[1],
					m_myPointCloudData.m_SelectedPointsNormalPoints2[num].m_Coordinate[2]);
				glEnd();
			}
		}
		///test begin///
	/*	for (int num = 0; num < m_myPointCloudData.m_TestSeletedPointCloud.size() / 2; num++)
		{
		glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(m_myPointCloudData.m_TestSeletedPointCloud[num].m_Coordinate[0], m_myPointCloudData.m_TestSeletedPointCloud[num].m_Coordinate[1], m_myPointCloudData.m_TestSeletedPointCloud[num].m_Coordinate[2]);
		glVertex3f(m_myPointCloudData.m_TestSeletedPointCloud[num + m_myPointCloudData.m_TestSeletedPointCloud.size() / 2].m_Coordinate[0], m_myPointCloudData.m_TestSeletedPointCloud[num + m_myPointCloudData.m_TestSeletedPointCloud.size() / 2].m_Coordinate[1], m_myPointCloudData.m_TestSeletedPointCloud[num + m_myPointCloudData.m_TestSeletedPointCloud.size() / 2].m_Coordinate[2]);
		glEnd();
		}
		*/
		
		/*for (int i = 0; i < m_myPointCloudData.m_TestSeletedPointCloud.size(); i++)
		{
			m_myPointCloudData.m_TestSeletedPointCloud[i].m_Color[1] = 0.4;
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_DOUBLE, 0, m_myPointCloudData.m_TestSeletedPointCloud[i].m_Coordinate);
			glColorPointer(3, GL_DOUBLE, 0, m_myPointCloudData.m_TestSeletedPointCloud[i].m_Color);
			glDrawArrays(GL_POINTS, 0, 1);
		}*/
		///test  end///
		////test begin////*/
		/*PCPoint* ttempPoint = m_myPointCloudData.GetOriginPointCloud();
		m_myPointCloudData.PCLKDtreeNKSearch(ttempPoint[15245], 50);
		for (int i = 0; i < m_myPointCloudData.RkNearestPoints.size(); i++)
		{
			if (i == 0)
				m_myPointCloudData.RkNearestPoints[i].m_Color[1] = 1;
			else
				m_myPointCloudData.RkNearestPoints[i].m_Color[2] = 0.1;
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_DOUBLE, 0, m_myPointCloudData.RkNearestPoints[i].m_Coordinate);
			glColorPointer(3, GL_DOUBLE, 0, m_myPointCloudData.RkNearestPoints[i].m_Color);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		m_myPointCloudData.RkNearestPoints.clear();
		////test end//*/
	}
	else if (b_SurfaceGenerated && b_FileInputed)
	{//��������ģ�͵����ǻ�
		//�������
		GLfloat mat_disffuse[] = { 0.8f, 0.8f, 0.5f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_disffuse);
		
		glClearColor(0.0,0.0,0.0,0.0);
		glShadeModel(GL_SMOOTH);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.0f,1.0f,0.0f);
		PCPoint* addedRepairingPointCloud = m_myPointCloudData.GetAddedRepairingPointCloud();
		for (size_t i = 0; i < m_myPointCloudData.triangles.polygons.size(); i++)
		{

			PCPoint point1 = addedRepairingPointCloud[m_myPointCloudData.triangles.polygons[i].vertices[0]];
			PCPoint point2 = addedRepairingPointCloud[m_myPointCloudData.triangles.polygons[i].vertices[1]];
			PCPoint point3 = addedRepairingPointCloud[m_myPointCloudData.triangles.polygons[i].vertices[2]];
			
			GLdouble dpoint1[3] = { point1.m_Coordinate[0], point1.m_Coordinate[1], point1.m_Coordinate[2] };
			GLdouble dpoint2[3] = { point2.m_Coordinate[0], point2.m_Coordinate[1], point2.m_Coordinate[2] };
			GLdouble dpoint3[3] = { point3.m_Coordinate[0], point3.m_Coordinate[1], point3.m_Coordinate[2] };
			GLdouble dNormal[3] = {0.0, 0.0, 1.0};
			CaculateNormal(dpoint1, dpoint2, dpoint3, dNormal);
			glBegin(GL_POLYGON);
			glNormal3dv(dNormal);
			glVertex3f(point1.m_Coordinate[0], point1.m_Coordinate[1], point1.m_Coordinate[2]);
			glVertex3f(point2.m_Coordinate[0], point2.m_Coordinate[1], point2.m_Coordinate[2]);
			glVertex3f(point3.m_Coordinate[0], point3.m_Coordinate[1], point3.m_Coordinate[2]);
			glEnd();  //����������
		}
	}

/*	vector<PCPoint>* selectedPoint = m_myPointCloudData.GetSelectedPoint();
	for (int num = 0; num < selectedPoint->size() / 2; num++)
	{
		glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f((*selectedPoint)[num].m_Coordinate[0], (*selectedPoint)[num].m_Coordinate[1], (*selectedPoint)[num].m_Coordinate[2]);
		glVertex3f((*selectedPoint)[num + selectedPoint->size() / 2].m_Coordinate[0], (*selectedPoint)[num + selectedPoint->size() / 2].m_Coordinate[1], (*selectedPoint)[num + selectedPoint->size() / 2].m_Coordinate[2]);
		glEnd();
	}
	*/
	/*///test begin//
	vector<PCPoint>* selectedPoint2 = m_myPointCloudData.GetSelectedPoint();
		for (int num = 0; num < selectedPoint2->size() / 2; num++)
		{
			(*selectedPoint2)[num].m_Color[0] = 1.0;
			(*selectedPoint2)[num].m_Color[1] = 0.5;
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_DOUBLE, 0, (*selectedPoint2)[num].m_Coordinate);
			glColorPointer(3, GL_DOUBLE, 0, (*selectedPoint2)[num].m_Color);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	//test end///*/

}

void CMy3D_PCD2View::OnFileOpen()//�򿪵����ļ�
{
	// TODO: �ڴ���������������
	CFileDialog fdlg(true, "txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("��������(*.txt)||"), NULL);
	fdlg.m_ofn.lpstrTitle = "browse";
	if (fdlg.DoModal() == IDOK) {//������ʽ�Ի���
		CString m_strDirectory = fdlg.GetPathName();
		CString m_filename = fdlg.GetFileName();
		char *filename = (LPSTR)(LPCTSTR)m_filename;
		m_myPointCloudData.ReadPointCloudFile((LPSTR)(LPCTSTR)m_strDirectory);//��ȡ���������ļ�
		//����ģ�����ƺ͵���������������ʾ
		m_ShowFileName = filename;
		m_ShowPointCloudNum = m_myPointCloudData.GetPointSumNumber();
		((CChildFrame*)AfxGetApp())->m_RightView->SetNameAndNum();
		b_FileInputed = TRUE;
		b_FIP = true;
		MessageBox("����ɹ�", "��ʾ");
	}
	InvalidateRect(NULL, FALSE);
}

void CMy3D_PCD2View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_RightDownPos = CPoint(0, 0);
	b_RightButtonDown = FALSE;
	CView::OnRButtonUp(nFlags, point);
}


void CMy3D_PCD2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	b_RightButtonDown = TRUE;
	m_RightDownPos.x = point.x;
	m_RightDownPos.y = point.y;
	CView::OnRButtonDown(nFlags, point);
}
//�������ʰȡ
void CMy3D_PCD2View::SelectObject(CPoint point, CPoint lastPoint)
{
	GLuint selectBuf[51200];
	GLint hits;
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(51200, selectBuf);

	glRenderMode(GL_SELECT);				// Enter the SELECT render mode
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	if (b_GetingRPMode == true)
	{//��ΪԼ����ѡ��ģʽʱ��ѡ��һƬ���ε���
		gluPickMatrix((GLdouble)((point.x + lastPoint.x) / 2), (GLdouble)(viewport[3] - (point.y + lastPoint.y) / 2), point.x - lastPoint.x, point.y - lastPoint.y, viewport);
	}
	if (b_SelectingMode == true || b_SelectingPointPropertyMode == true)
	{//��Ϊ���ʰȡģʽʱ��ÿ��ֻʰȡһ����
		gluPickMatrix((GLdouble)point.x, (GLdouble)(viewport[3] - point.y), 5.0, 5.0, viewport);
	}
	glViewport(0, 0, m_DisplayWidth, m_DisplayHeight);
	glOrtho(-1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, 1.5*(GLdouble)(m_DisplayWidth) / (GLdouble)m_DisplayHeight, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	ReadPointCloudData();
	glPopMatrix();
	glFlush();

	hits = glRenderMode(GL_RENDER);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
	if (hits>0)
	{
		int n = 0; double minz = selectBuf[1];
		for (int i = 1; i<hits; i++)
		{
			if (b_SelectingMode == true)
			{
				if (selectBuf[1 + i * 4] < minz)
				{
					n = i;
					minz = selectBuf[1 + i * 4];
				}
			}
			if (b_GetingRPMode == true)
			{
				tempPointCloud[selectBuf[3 + i * 4]].b_Selected = true;//��Ϊ��ѡ��
				tempPointCloud[selectBuf[3 + i * 4]].m_Color[1] = 1.0;//��Ϊ��ɫ
			}
		}
		if (b_SelectingMode == true)
		{
			tempPointCloud[selectBuf[3 + n * 4]].b_Selected = true;//��Ϊ��ѡ��
			tempPointCloud[selectBuf[3 + n * 4]].m_Color[1] = 1.0;//��Ϊ��ɫ
		}
		if (b_SelectingPointPropertyMode == true)
		{
			tempPointCloud[selectBuf[3 + n * 4]].b_Selected = true;//��Ϊ��ѡ��
			tempPointCloud[selectBuf[3 + n * 4]].m_Color[1] = 1.0;//��Ϊ��ɫ
			//��ʾ�����ԶԻ���
			PointProperty *pdlg = new PointProperty(tempPointCloud[selectBuf[3 + n * 4]].m_ID
				, tempPointCloud[selectBuf[3 + n * 4]].m_Coordinate[0]
				, tempPointCloud[selectBuf[3 + n * 4]].m_Coordinate[1]
				, tempPointCloud[selectBuf[3 + n * 4]].m_Coordinate[2]);
			pdlg->Create(IDD_POINTPROPERTY, this);
			pdlg->ShowWindow(SW_SHOW);
		}
	}
}
//��Ϊ���ʰȡģʽ
void  CMy3D_PCD2View::SetSelectingMode()
{
	b_SelectingMode = true;
	b_GetingRPMode = false;
	b_NormalVectorMode = false;
}
//��Ϊ��ͨ��ʾģʽ
void CMy3D_PCD2View::SetNormalMode()
{
	b_SelectingMode = false;
	b_GetingRPMode = false;
	b_SelectingPointPropertyMode = false;
	//���������Ϊ��ͨģʽ
	SetClassLong(this->GetSafeHwnd(), GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_ARROW));
}
//����ΪԼ����ѡ��ģʽ
void CMy3D_PCD2View::SetGetRPMode()
{
	b_GetingRPMode = true;
	b_SelectingMode = false;
	//���������Ϊʮ��
	SetClassLong(this->GetSafeHwnd(), GCL_HCURSOR, (LONG)LoadCursor(NULL, IDC_CROSS));
}
//����Ϊ�������ѡ��ģʽ
void  CMy3D_PCD2View::SetGetPointPropertyMode()
{
	b_SelectingPointPropertyMode = true;
	b_GetingRPMode = false;
}

void CMy3D_PCD2View::OnFileSave()
{
	// TODO: �ڴ���������������
	b_Saved = true;
	CFileDialog hFileDlg(false, "txt", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY,
		_T("��������(*.txt)||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 1;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("����ͼ��\0");
	hFileDlg.m_ofn.nMaxFile = MAX_PATH;
	if (hFileDlg.DoModal() == IDOK)
	{
		CString m_path = hFileDlg.GetPathName();
		//��ʵ����������c++�ļ������Ķ����� �������ѽ������
		CStdioFile file;
		file.Open(_T(m_path), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		file.Close();
		FILE* fp;
		fopen_s(&fp, m_path, "w");
		PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
		for (int i = 0; i<m_myPointCloudData.GetPointSumNumber(); i++)
		{
			if (tempPointCloud[i].b_Selected == false)//���澫�������ݵ�
			{
				fprintf(fp, "%f %f %f\n", tempPointCloud[i].m_Coordinate[2], tempPointCloud[i].m_Coordinate[0], tempPointCloud[i].m_Coordinate[1]);
			}

		}
		fclose(fp);
		MessageBox("����ɹ���", "��ʾ");
		UpdateData(FALSE);//����ܹ��رնԻ���
	}

}


void CMy3D_PCD2View::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	b_Saved = true;
	CFileDialog hFileDlg(false, "txt", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY,
		_T("��������(*.txt)||"), NULL);
	hFileDlg.m_ofn.nFilterIndex = 1;
	hFileDlg.m_ofn.hwndOwner = m_hWnd;
	hFileDlg.m_ofn.lStructSize = sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle = TEXT("����ͼ��\0");
	hFileDlg.m_ofn.nMaxFile = MAX_PATH;
	if (hFileDlg.DoModal() == IDOK)
	{
		CString m_path = hFileDlg.GetPathName();
		//��ʵ����������c++�ļ������Ķ����� �������ѽ������
		CStdioFile file;
		file.Open(_T(m_path), CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		file.Close();
		FILE* fp;
		fopen_s(&fp, m_path, "w");
		PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
		for (int i = 0; i<m_myPointCloudData.GetPointSumNumber(); i++)
		{

			if (tempPointCloud[i].b_Selected == false)//���澫�������ݵ�
			{

				fprintf(fp, "%f %f %f\n", tempPointCloud[i].m_Coordinate[2], tempPointCloud[i].m_Coordinate[0], tempPointCloud[i].m_Coordinate[1]);
			}

		}
		fclose(fp);
		MessageBox("����ɹ���", "��ʾ");
		UpdateData(FALSE);//����ܹ��رնԻ��򣬵��ǲ�û�д������������ֻ��Ҫ������Ӧ���ļ������ͺ��ˡ�����

	}
}
//����ģ�͵ı߽���
void CMy3D_PCD2View::PointCloudBoundaryCheck()
{
	PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
	for (int num = 0; num < m_myPointCloudData.GetPointSumNumber(); num++)
	{//����Ϊ��ʼ״̬
		tempPointCloud[num].b_BoundaryPoint = false;
		tempPointCloud[num].m_Color[0] = 0.0;
		tempPointCloud[num].m_Color[1] = 0.0;
		tempPointCloud[num].m_Color[2] = 0.0;
	}
	/*PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
	for (int num = 0; num < m_myPointCloudData.GetPointSumNumber(); num++)
	{//��ÿ�����ݵ���б߽���
		gProgress = 50 * ((double)num / (double)m_myPointCloudData.GetPointSumNumber());//������ʾ������
		if (m_myPointCloudData.BoundaryCheck(tempPointCloud[num]) == true)
		{
			tempPointCloud[num].b_BoundaryPoint = true;//��Ϊ�߽��
			tempPointCloud[num].m_Color[0] = 1.0;//��Ϊ��ɫ
		}
		else
		{
			tempPointCloud[num].m_Color[2] = 1.0;//��Ϊ��ɫ
		}
	}*/
	//PCL�е�ģ�ͱ߽籣���㷨
	m_myPointCloudData.PCLBoundaryKeep();
	gProgressAu = -1;//���ٽ�����
	MessageBox("�߽籣����ɣ�","��ʾ");
	InvalidateRect(NULL, FALSE);
}
//����ģ�Ϳ׶��޲�
void CMy3D_PCD2View::PointCloudHoleRepair()
{
	b_Saved = false;//�ļ����޸�
	//���п׶��޲����������޲����
	if (m_myPointCloudData.HoleRepair())
	{
		MessageBox("�ն��޲���ɣ�", "��ʾ");
	}
	else
	{
		MessageBox("�ÿ׶��޷�ʵ���޲�", "��ʾ");
	}
	InvalidateRect(NULL, FALSE);
}
//����ͼ��ʾ
void CMy3D_PCD2View::SetTriWindowsMode()
{
	b_TriWindowMode = true;
	InvalidateRect(NULL, FALSE);
}
//��ͨ��ͼ��ʾ
void CMy3D_PCD2View::SetSingleWindowMode()
{
	b_TriWindowMode = false;
	InvalidateRect(NULL, FALSE);
}
//�߽����
void CMy3D_PCD2View::PointCloudBoundaryClustering()
{
	//���б߽����
	m_myPointCloudData.BoundaryClustering();
	MessageBox("�߽�������","��ʾ");
	InvalidateRect(NULL, FALSE);
	b_test = true;
}
//�Զ��޲�
void CMy3D_PCD2View::PointCloudAutomaticHoleRepair()
{
	b_Saved = false;//�ļ����޸�
	gProgressAu = 0;
	m_myPointCloudData.AutomaticHoleRepair();
	gProgressAu = -1;
	MessageBox("�Զ��޲����", "��ʾ");
	InvalidateRect(NULL, FALSE);
}
//����ģ�����ǻ�
void CMy3D_PCD2View::PointCLoudSurfaceGenerating()
{
	//����ģ�����ǻ�
	gProgressAu = 0;
	m_myPointCloudData.SurfaceGenerating();
	MessageBox("ģ�ͱ����ؽ����", "��ʾ");
	//���ǻ����
	b_SurfaceGenerated = true;
	InvalidateRect(NULL, FALSE);
}
//�����ػ棬��Ҫ����������������
void  CMy3D_PCD2View::ViewInvalidateRect()
{
	InvalidateRect(NULL, FALSE);
}
//��ȡѡȡ���ݵ�ķ�ʸ��
void  CMy3D_PCD2View::PointCloudGetSelectedPointsNormalVectors()
{
	if (b_NormalVectorMode == false)
	{
		bool flag = false;
		PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
		for (int num = 0; num < m_myPointCloudData.GetPointSumNumber(); num++)
		{
			if (tempPointCloud[num].b_Selected == true)
			{
				flag = true;
			}
		}
		if (flag)
		{
			m_myPointCloudData.GetSelectedPointsNormalVectors();
			InvalidateRect(NULL, FALSE);
			b_NormalVectorMode = true;
		}
		else
		{
			MessageBox("���Ƚ���Լ����ѡ��ģʽ��ѡ����Ҫ�����ݵ㣡", "��ʾ");
		}
	}
	else
	{
		b_NormalVectorMode = false;
		InvalidateRect(NULL, FALSE);
	}
}
//һ���޲�ģ��
void CMy3D_PCD2View::PointCloudOneStepRepair()
{
	m_myPointCloudData.b_OneStepMode = true;
	//ģ�ͱ߽籣��
	/*PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
	for (int num = 0; num < m_myPointCloudData.GetPointSumNumber(); num++)
	{//��ÿ�����ݵ���б߽���
		gProgressAu = 10 * ((double)num / (double)m_myPointCloudData.GetPointSumNumber());//������ʾ������
		if (m_myPointCloudData.BoundaryCheck(tempPointCloud[num]) == true)
		{
			tempPointCloud[num].b_BoundaryPoint = true;//��Ϊ�߽��
		}
	}*/
	//PCL�е�ģ�ͱ߽籣���㷨
	m_myPointCloudData.PCLBoundaryKeep();
	//�߽����
	m_myPointCloudData.BoundaryClustering();
	//�Զ��޲�
	m_myPointCloudData.AutomaticHoleRepair();
	gProgressAu = -1;
	m_myPointCloudData.b_OneStepMode = false;
	MessageBox("һ���޲���ɣ�","��ʾ");
	InvalidateRect(NULL, FALSE);
}
//һ���޲�ģ�Ͳ��ҽ��б����ؽ�
void CMy3D_PCD2View::PointCloudOneStepRepairAndSurface()
{
	
	m_myPointCloudData.b_OneStepMode = true; 
	m_myPointCloudData.b_AllPoint = true;
	//ģ�ͱ߽籣��
	/*PCPoint* tempPointCloud = m_myPointCloudData.GetOriginPointCloud();
	for (int num = 0; num < m_myPointCloudData.GetPointSumNumber(); num++)
	{//��ÿ�����ݵ���б߽���
		gProgressAu = 5 * ((double)num / (double)m_myPointCloudData.GetPointSumNumber());//������ʾ������
		if (m_myPointCloudData.BoundaryCheck(tempPointCloud[num]) == true)
		{
			tempPointCloud[num].b_BoundaryPoint = true;//��Ϊ�߽��
		}
	}*/
	//PCL�е�ģ�ͱ߽籣���㷨
	m_myPointCloudData.PCLBoundaryKeep();
	//�߽����
	m_myPointCloudData.BoundaryClustering();
	//�Զ��޲�
	m_myPointCloudData.AutomaticHoleRepair();
	//ģ�ͱ����ؽ�
	m_myPointCloudData.SurfaceGenerating();
	b_SurfaceGenerated = true;
	gProgressAu = -1;
	m_myPointCloudData.b_OneStepMode = false;
	m_myPointCloudData.b_AllPoint = false;
	MessageBox("һ���޲����ؽ�������ɣ�", "��ʾ");
	InvalidateRect(NULL, FALSE);
}
//���㷨ʸ��
void CMy3D_PCD2View::CaculateNormal(GLdouble* dVertex1, GLdouble* dVertex2,
	GLdouble* dVertex3, GLdouble* dNormal)               //����ÿ�����ǵķ����������ڹ��յ���ʾ
{
	GLdouble dVector1[3], dVector2[3];     //��������������
	dVector1[0] = dVertex2[0] - dVertex1[0];
	dVector1[1] = dVertex2[1] - dVertex1[1];
	dVector1[2] = dVertex2[2] - dVertex1[2];   //dVector1�������1,2����֮�������
	dVector2[0] = dVertex3[0] - dVertex1[0];
	dVector2[1] = dVertex3[1] - dVertex1[1];
	dVector2[2] = dVertex3[2] - dVertex1[2];   //dVector2�������1,3����֮�������
	dNormal[0] = dVector1[1] * dVector2[2] - dVector1[2] * dVector2[1];//��������Ǵ�ֱ��������������
	dNormal[1] = dVector1[2] * dVector2[0] - dVector1[0] * dVector2[2];//��xʱ�Ͳ�����x����yʱ�Ͳ�����y
	dNormal[2] = dVector1[0] * dVector2[1] - dVector1[1] * dVector2[0];

	double dNormalLength = sqrt(dNormal[0] * dNormal[0] +
		dNormal[1] * dNormal[1] + dNormal[2] * dNormal[2]);
	//����������λ��
	if (dNormalLength != 0.0)
	{
		dNormal[0] = dNormal[0] / dNormalLength;
		dNormal[1] = dNormal[1] / dNormalLength;
		dNormal[2] = dNormal[2] / dNormalLength;
	}
	//������ķ�����ģΪ��ʱ����ȡz�����һ����λ����
	else
	{
		dNormal[0] = 0.0;
		dNormal[1] = 0.0;
		dNormal[2] = 1.0;
	}
}