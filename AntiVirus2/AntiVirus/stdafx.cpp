
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// AntiVirus.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"


__declspec( dllimport ) void WINAPI GetTestMsg(char* pMsg);
#pragma comment(lib, "LibAntiVirus")