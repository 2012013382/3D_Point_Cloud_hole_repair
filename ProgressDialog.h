#pragma once


// ProgressDialog �Ի���

class ProgressDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ProgressDialog)

public:
	ProgressDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProgressDialog();

// �Ի�������
	enum { IDD = IDD_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
