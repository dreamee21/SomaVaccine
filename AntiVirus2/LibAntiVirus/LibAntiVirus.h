// LibAntiVirus.h : LibAntiVirus DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CLibAntiVirusApp
// �� Ŭ������ ������ ������ LibAntiVirus.cpp�� �����Ͻʽÿ�.
//

class CLibAntiVirusApp : public CWinApp
{
public:
	CLibAntiVirusApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
