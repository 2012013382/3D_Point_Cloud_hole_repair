#pragma once


// PointProperty �Ի���

class PointProperty : public CDialogEx
{
	DECLARE_DYNAMIC(PointProperty)

public:
	int m_PointNum;
	double m_X;
	double m_Y;
	double m_Z;
	PointProperty(CWnd* pParent = NULL);   // ��׼���캯��
	PointProperty(int pointNum, double x, double y, double z, CWnd* pParent = NULL);//���ع��캯��
	virtual ~PointProperty();

// �Ի�������
	enum { IDD = IDD_POINTPROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
