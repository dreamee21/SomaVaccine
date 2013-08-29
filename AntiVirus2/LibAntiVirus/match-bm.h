#include"stdafx.h"
struct cli_bm_patt{
	unsigned char *pattern, *prefix;
    char *virname;
    uint32_t offdata[4], offset_min, offset_max;
    struct cli_bm_patt *next;
    uint16_t length, prefix_length;
    uint16_t cnt;
    unsigned char pattern0;
    uint32_t boundary, filesize;
};