#pragma once


// PropertyBoard ������ͼ

class PropertyBoard : public CFormView
{
	DECLARE_DYNCREATE(PropertyBoard)

protected:
	PropertyBoard();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~PropertyBoard();

public:
	enum { IDD = IDD_PROPERTYBOARD };
	//��ʾ���ƺ͵�����
	void SetNameAndNum();
	//��ȡ���԰��еĲ���
	void GetAndSetAngleProperties();
	//��ʾ�۲�ǶȲ���
	void SetAngle();
	//���ڻ�ȡ���԰�Ĳ���
	void GetProperties();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	//����һЩĬ�ϲ���
	double m_RotationX;
	double m_RotationY;
	double m_textBoundary;
	double m_clusterDistace;
	double m_clusterNum;
	double m_trianMaxDistace;
	double m_trianMaxAngle;
	double m_trianMinAngle;
	double m_trianMaxSAngle;
	//��һ��
	bool b_FirstTime;
public:
	afx_msg void OnBnClickedSetangle();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedMyhelp();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


