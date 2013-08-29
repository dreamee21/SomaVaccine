#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include"stdafx.h"
#include"other.h"
#include"gettimeofday.h"
#include"default.h"
//#include"md5.h"

//int (*cli_unrar_open)(int fd, const char *dirname, unrar_state_t *state);
//int (*cli_unrar_extract_next_prepare)(unrar_state_t *state, const char *dirname);
//int (*cli_unrar_extract_next)(unrar_state_t *state, const char *dirname);
//void (*cli_unrar_close)(unrar_state_t *state);
//int have_rar = 0;
void cl_init()
{
	//int rc;
	struct timeval tv;
	//unsigned int pid = (unsigned int) getpid();

	/*{
	unrar_main_header_t x;
	if (((char*)&x.flags - (char*)&x) != 3) {
	cli_errmsg("Structure packing not working, got %u offset, expected %u\n",
	(unsigned)((char*)&x.flags - (char*)&x), 3);
	return CL_EARG;
	}
	}*/
	/* put dlopen() stuff here, etc. */
	/*if (lt_init() == 0) {
	cli_rarload();
	}*/
	gettimeofday(&tv, (struct timezone *) 0);
	//srand(pid + tv.tv_usec*(pid+1) + clock());
	//rc = bytecode_init();
	//if (rc)
	//	return rc;
	//return CL_SUCCESS;
}

struct cl_engine *cl_engine_new()
{
	struct cl_engine *new_engine;
	new_engine = (struct cl_engine *) cli_calloc(1, sizeof(struct cl_engine));
	/*if(!new){
	cli_errmsg("cl_engine_new: Can't allocate memory for cl_engine\n");
	return NULL;
	}*/

	/* Setup default limits */
	new_engine->maxscansize = CLI_DEFAULT_MAXSCANSIZE;
	new_engine->maxfilesize = CLI_DEFAULT_MAXFILESIZE;
	new_engine->maxreclevel = CLI_DEFAULT_MAXRECLEVEL;
	new_engine->maxfiles = CLI_DEFAULT_MAXFILES;
	new_engine->min_cc_count = CLI_DEFAULT_MIN_CC_COUNT;
	new_engine->min_ssn_count = CLI_DEFAULT_MIN_SSN_COUNT;

	//new_engine->bytecode_security = CL_BYTECODE_TRUST_SIGNED;
	/* 5 seconds timeout */
	//new_engine->bytecode_timeout = 60000;
	//new_engine->bytecode_mode = CL_BYTECODE_MODE_AUTO;
	new_engine->refcount = 1;
	new_engine->ac_only = 0;
	new_engine->ac_mindepth = CLI_DEFAULT_AC_MINDEPTH;
	new_engine->ac_maxdepth = CLI_DEFAULT_AC_MAXDEPTH;

	//#ifdef USE_MPOOL
	//    if(!(new->mempool = mpool_create())) {
	//	cli_errmsg("cl_engine_new: Can't allocate memory for memory pool\n");
	//	free(new);
	//	return NULL;
	//    }
	//#endif
	//
	//	new->root = mpool_calloc(new->mempool, CLI_MTARGETS, sizeof(struct cli_matcher *));
	//	if(!new->root) {
	//		cli_errmsg("cl_engine_new: Can't allocate memory for roots\n");
	////#ifdef USE_MPOOL
	////		mpool_destroy(new->mempool);
	////#endif
	//		free(new);
	//		return NULL;
	//	}

	//	new->dconf = cli_mpool_dconf_init(new->mempool);
	//	if(!new->dconf) {
	//		cli_errmsg("cl_engine_new: Can't initialize dynamic configuration\n");
	//		mpool_free(new->mempool, new->root);
	////#ifdef USE_MPOOL
	////		mpool_destroy(new->mempool);
	////#endif
	//		free(new);
	//		return NULL;
	//	}

	/*cli_dbgmsg("Initialized %s engine\n", cl_retver());*/
	return new_engine;
}
int cl_engine_set_num(struct cl_engine *engine, enum cl_engine_field field, long long num)
{
	if(!engine)
	return CL_ENULLARG;

	/* TODO: consider adding checks and warn/errs when num overflows the
	* destination type
	*/
	switch(field) {
	case CL_ENGINE_MAX_SCANSIZE:
		engine->maxscansize = num;
		break;
	case CL_ENGINE_MAX_FILESIZE:
		engine->maxfilesize = num;
		break;
	case CL_ENGINE_MAX_RECURSION:
		if(!num) {
			cli_warnmsg("MaxRecursion: the value of 0 is not allowed, using default: %u\n", CLI_DEFAULT_MAXRECLEVEL);
			engine->maxreclevel = CLI_DEFAULT_MAXRECLEVEL;
		} else
			engine->maxreclevel = num;
		break;
	case CL_ENGINE_MAX_FILES:
		engine->maxfiles = num;
		break;
	case CL_ENGINE_MIN_CC_COUNT:
		engine->min_cc_count = num;
		break;
	case CL_ENGINE_MIN_SSN_COUNT:
		engine->min_ssn_count = num;
		break;
	case CL_ENGINE_DB_OPTIONS:
	case CL_ENGINE_DB_VERSION:
	case CL_ENGINE_DB_TIME:
		cli_warnmsg("cl_engine_set_num: The field is read only\n");
		return CL_EARG;
	/*case CL_ENGINE_AC_ONLY:
		engine->ac_only = num;
		break;
	case CL_ENGINE_AC_MINDEPTH:
		engine->ac_mindepth = num;
		break;
	case CL_ENGINE_AC_MAXDEPTH:
		engine->ac_maxdepth = num;
		break;
	case CL_ENGINE_KEEPTMP:
		engine->keeptmp = num;
		break;
	case CL_ENGINE_BYTECODE_SECURITY:
		if (engine->dboptions & CL_DB_COMPILED) {
			cli_errmsg("cl_engine_set_num: CL_ENGINE_BYTECODE_SECURITY cannot be set after engine was compiled\n");
			return CL_EARG;
		}
		engine->bytecode_security = num;
		break;
	case CL_ENGINE_BYTECODE_TIMEOUT:
		engine->bytecode_timeout = num;
		break;
	case CL_ENGINE_BYTECODE_MODE:
		if (engine->dboptions & CL_DB_COMPILED) {
			cli_errmsg("cl_engine_set_num: CL_ENGINE_BYTECODE_MODE cannot be set after engine was compiled\n");
			return CL_EARG;
		}
		if (num == CL_BYTECODE_MODE_OFF) {
			cli_errmsg("cl_engine_set_num: CL_BYTECODE_MODE_OFF is not settable, use dboptions to turn off!\n");
			return CL_EARG;
		}
		engine->bytecode_mode = num;
		if (num == CL_BYTECODE_MODE_TEST)
			cli_infomsg(NULL, "bytecode engine in test mode\n");
		break;*/
	default:
		cli_errmsg("cl_engine_set_num: Incorrect field number\n");
		return CL_EARG;
	}

	return CL_SUCCESS;
}