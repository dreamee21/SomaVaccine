
// AntiVirus.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CAntiVirusApp:
// �� Ŭ������ ������ ���ؼ��� AntiVirus.cpp�� �����Ͻʽÿ�.
//

class CAntiVirusApp : public CWinApp
{
public:
	CAntiVirusApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CAntiVirusApp theApp;