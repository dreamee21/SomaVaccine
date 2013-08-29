#include"stdafx.h"
#include"gettimeofday.h"
#include<sys/types.h>
#include<sys/timeb.h>
#include<time.h>

int gettimeofday(struct timeval *tv, struct timezone *tz) {
	struct _timeb t;

	_ftime_s(&t);
	tv->tv_sec = t.time;
	tv->tv_usec = t.millitm * 1000;
	return 0;
}
