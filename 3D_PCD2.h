
// 3D_PCD2.h : 3D_PCD2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy3D_PCD2App:
// �йش����ʵ�֣������ 3D_PCD2.cpp
//

class CMy3D_PCD2App : public CWinApp
{
public:
	CMy3D_PCD2App();


	// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3D_PCD2App theApp;
