#include"stdafx.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include"other.h"
void *cli_calloc(uint32 nmemb, uint32 size)
{
	void *alloc;


	//   if(!nmemb || !size || size > CLI_MAX_ALLOCATION || nmemb > CLI_MAX_ALLOCATION
	//       || (nmemb*size > CLI_MAX_ALLOCATION)) {
	//return NULL;
	//   }

	alloc = calloc(nmemb, size);

	if(!alloc) {
		cli_errmsg("cli_calloc(): Can't allocate memory (%lu bytes).\n", (unsigned long int) (nmemb * size));
		perror("calloc_problem");
		return NULL;
	}
	else return alloc;
}

//static inline void *cli_getctx(void)
//{
//    cli_ctx *ctx;
//    pthread_once(&cli_ctx_tls_key_once, cli_ctx_tls_key_alloc);
//    ctx = pthread_getspecific(cli_ctx_tls_key);
//    return ctx ? ctx->cb_ctx : NULL;
//}

static void fputs_callback(enum cl_msg severity, const char *fullmsg, const char *msg, void *context)
{
    fputs(fullmsg, stderr);
}

static clcb_msg msg_callback = fputs_callback;

void cl_set_clcb_msg(clcb_msg callback)
{
    msg_callback = callback;
}

#define MSGCODE(buff, len, x)								\
	va_list args;										    \
	int len = sizeof(x) - 1;								\
	char buff[BUFSIZ];									    \
    strncpy_s(buff, x, len);								\
    va_start(args, str);									\
    vsnprintf_s(buff + len, sizeof(buff) - len, 0, str, args);   \
    buff[sizeof(buff) - 1] = '\0';							\
    va_end(args)

void cli_errmsg(const char *str, ...)
{
    MSGCODE(buff, len, "LibClamAV Error: ");
   // msg_callback(CL_MSG_ERROR, buff, buff+len, cli_getctx());
}

void cli_warnmsg(const char *str, ...)
{
    MSGCODE(buff, len, "LibClamAV Warning: ");
   // msg_callback(CL_MSG_WARN, buff, buff+len, cli_getctx());
}