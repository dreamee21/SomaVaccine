#include"stdafx.h"
#include"manager.h"
#include"LibAntiVirus/other.h"

int scanmanager()
{
	struct cl_engine *engine;
	char *file, cwd[1024];
	const char *filename;
	struct stat sb;
	cl_init();
	engine = cl_engine_new();
	return 0;
}