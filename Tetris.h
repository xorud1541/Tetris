
// Tetris.h : Tetris ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTetrisApp:
// �� Ŭ������ ������ ���ؼ��� Tetris.cpp�� �����Ͻʽÿ�.
//

class CTetrisApp : public CWinApp
{
public:
	CTetrisApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTetrisApp theApp;
