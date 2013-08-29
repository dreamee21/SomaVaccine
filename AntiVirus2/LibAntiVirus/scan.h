typedef enum {
    /* libclamav specific */
    CL_CLEAN = 0,
    CL_SUCCESS = 0,
    CL_VIRUS,
    CL_ENULLARG,
    CL_EARG,
    CL_EMALFDB,
    CL_ECVD,
    CL_EVERIFY,
    CL_EUNPACK,

    /* I/O and memory errors */
    CL_EOPEN,
    CL_ECREAT,
    CL_EUNLINK,
    CL_ESTAT,
    CL_EREAD,
    CL_ESEEK,
    CL_EWRITE,
    CL_EDUP,
    CL_EACCES,
    CL_ETMPFILE,
    CL_ETMPDIR,
    CL_EMAP,
    CL_EMEM,
    CL_ETIMEOUT,

    /* internal (not reported outside libclamav) */
    CL_BREAK,
    CL_EMAXREC,
    CL_EMAXSIZE,
    CL_EMAXFILES,
    CL_EFORMAT,
    CL_EBYTECODE,/* may be reported in testmode */
    CL_EBYTECODE_TESTFAIL, /* may be reported in testmode */

    /* c4w error codes */
    CL_ELOCK,
    CL_EBUSY,
    CL_ESTATE,

    /* no error codes below this line please */
    CL_ELAST_ERROR
} cl_error_t;

enum cl_engine_field {
    CL_ENGINE_MAX_SCANSIZE,	    /* uint64_t */
    CL_ENGINE_MAX_FILESIZE,	    /* uint64_t */
    CL_ENGINE_MAX_RECURSION,	    /* uint32_t	*/
    CL_ENGINE_MAX_FILES,	    /* uint32_t */
    CL_ENGINE_MIN_CC_COUNT,	    /* uint32_t */
    CL_ENGINE_MIN_SSN_COUNT,	    /* uint32_t */
    CL_ENGINE_PUA_CATEGORIES,	    /* (char *) */
    CL_ENGINE_DB_OPTIONS,	    /* uint32_t */
    CL_ENGINE_DB_VERSION,	    /* uint32_t */
    CL_ENGINE_DB_TIME,		    /* time_t */
    CL_ENGINE_AC_ONLY,		    /* uint32_t */
    CL_ENGINE_AC_MINDEPTH,	    /* uint32_t */
    CL_ENGINE_AC_MAXDEPTH,	    /* uint32_t */
    CL_ENGINE_TMPDIR,		    /* (char *) */
    CL_ENGINE_KEEPTMP,		    /* uint32_t */
    CL_ENGINE_BYTECODE_SECURITY,    /* uint32_t */
    CL_ENGINE_BYTECODE_TIMEOUT,     /* uint32_t */
    CL_ENGINE_BYTECODE_MODE         /* uint32_t */
};

enum bytecode_security {
    CL_BYTECODE_TRUST_ALL=0, /* obsolete */
    CL_BYTECODE_TRUST_SIGNED, /* default */
    CL_BYTECODE_TRUST_NOTHING /* paranoid setting */
};

enum bytecode_mode {
    CL_BYTECODE_MODE_AUTO=0, /* JIT if possible, fallback to interpreter */
    CL_BYTECODE_MODE_JIT, /* force JIT */
    CL_BYTECODE_MODE_INTERPRETER, /* force interpreter */
    CL_BYTECODE_MODE_TEST, /* both JIT and interpreter, compare results,
			      all failures are fatal */
    CL_BYTECODE_MODE_OFF /* for query only, not settable */
};


struct cl_cvd {		    /* field no. */
    char *time;		    /* 2 */
    unsigned int version;   /* 3 */
    unsigned int sigs;	    /* 4 */
    unsigned int fl;	    /* 5 */
			    /* padding */
    char *md5;		    /* 6 */
    char *dsig;		    /* 7 */
    char *builder;	    /* 8 */
    unsigned int stime;	    /* 9 */
};

struct cl_stat {
    char *dir;
    struct stat *stattab;
    char **statdname;
    unsigned int entries;
};


enum cl_msg {
    /* leave room for more message levels in the future */
    CL_MSG_INFO_VERBOSE = 32, /* verbose */
    CL_MSG_WARN = 64, /* LibClamAV WARNING: */
    CL_MSG_ERROR = 128/* LibClamAV ERROR: */
};

extern int cl_engine_set_num(struct cl_engine *engine, enum cl_engine_field field, long long num);
extern int cl_engine_set_str(struct cl_engine *engine, enum cl_engine_field field, const char *str);
extern int cl_engine_settings_apply(struct cl_engine *engine, const struct cl_settings *settings);
extern int cl_engine_settings_free(struct cl_settings *settings);
extern int cl_engine_compile(struct cl_engine *engine);
extern int cl_engine_free(struct cl_engine *engine);
typedef void (*clcb_msg)(enum cl_msg severity, const char *fullmsg, const char *msg, void *context);
extern void cl_set_clcb_msg(clcb_msg callback);