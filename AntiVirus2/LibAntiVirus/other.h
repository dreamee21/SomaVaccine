#include"stdafx.h"
#include"scan.h"
#include"default.h"
#include<stdio.h>
#include<stdlib.h>

struct cli_dbinfo {
    char *name;
    unsigned char *hash;
    uint32 size;
    struct cl_cvd *cvd;
    struct cli_dbinfo *next;
};

struct cl_engine{
	uint32 refcount; /* reference counter */
    uint32 sdb;
    uint32 dboptions;
    uint32 dbversion[2];
    uint32 ac_only;
    uint32 ac_mindepth;
    uint32 ac_maxdepth;
    char *tmpdir;
    uint32 keeptmp;

    /* Limits */
    uint64 maxscansize;  /* during the scanning of archives this size
				     * will never be exceeded
				     */
    uint64 maxfilesize;  /* compressed files will only be decompressed
				     * and scanned up to this size
				     */
    uint32 maxreclevel;	    /* maximum recursion level for archives */
    uint32 maxfiles;	    /* maximum number of files to be scanned
				     		   within a single archive */
    uint32 min_cc_count;
    uint32 min_ssn_count;

    /* Roots table */
    struct cli_matcher **root;

    /* hash matcher for standard MD5 sigs */
    struct cli_matcher *hm_hdb;
    /* hash matcher for MD5 sigs for PE sections */
    struct cli_matcher *hm_mdb;
    /* hash matcher for whitelist db */
    struct cli_matcher *hm_fp;


    /* Container metadata */
    struct cli_cdb *cdb;

    /* Phishing .pdb and .wdb databases*/
    struct regex_matcher *whitelist_matcher;
    struct regex_matcher *domainlist_matcher;
    struct phishcheck *phishcheck;

    /* Dynamic configuration */
    struct cli_dconf *dconf;

    /* Filetype definitions */
    struct cli_ftype *ftypes;

    /* Ignored signatures */
    struct cli_matcher *ignored;

    /* PUA categories (to be included or excluded) */
    char *pua_cats;

    /* Icon reference storage */
    struct icon_matcher *iconcheck;

    /* Negative cache storage */
    struct CACHE *cache;

    /* Database information from .info files */
    struct cli_dbinfo *dbinfo;

    /* Used for memory pools */
    //mpool_t *mempool;

    /* Callback(s) */
    //clcb_pre_scan cb_pre_scan;
    //clcb_post_scan cb_post_scan;
    //clcb_sigload cb_sigload;
    //void *cb_sigload_ctx;
    //clcb_hash cb_hash;

    /* Used for bytecode */
    //struct cli_all_bc bcs;
    //unsigned *hooks[_BC_LAST_HOOK - _BC_START_HOOKS];
    //unsigned hooks_cnt[_BC_LAST_HOOK - _BC_START_HOOKS];
    //unsigned hook_lsig_ids;
    //enum bytecode_security bytecode_security;
    //uint32 bytecode_timeout;
    //enum bytecode_mode bytecode_mode;
};

//extern int (*cli_unrar_open)(int fd, const char *dirname, unrar_state_t *state);
//extern int (*cli_unrar_extract_next_prepare)(unrar_state_t *state, const char *dirname);
//extern int (*cli_unrar_extract_next)(unrar_state_t *state, const char *dirname);
//extern void (*cli_unrar_close)(unrar_state_t *state);
//extern int have_rar;
struct cl_settings {
    /* don't store dboptions here; it needs to be provided to cl_load() and
     * can be optionally obtained with cl_engine_get() or from the original
     * settings stored by the application
     */
    uint32 ac_only;
    uint32 ac_mindepth;
    uint32 ac_maxdepth;
    char *tmpdir;
    uint32 keeptmp;
    uint64 maxscansize;
    uint64 maxfilesize;
    uint32 maxreclevel;
    uint32 maxfiles;
    uint32 min_cc_count;
    uint32 min_ssn_count;
    enum bytecode_security bytecode_security;
    uint32 bytecode_timeout;
    enum bytecode_mode bytecode_mode;
    char *pua_cats;

    /* callbacks */
    /*clcb_pre_scan cb_pre_scan;
    clcb_post_scan cb_post_scan;
    clcb_sigload cb_sigload;
    void *cb_sigload_ctx;
    clcb_msg cb_msg;
    clcb_hash cb_hash;*/
};
typedef struct bitset_tag
{
        unsigned char *bitset;
        unsigned long length;
} bitset_t;
typedef struct cli_ctx_tag {
    const char **virname;
    unsigned int num_viruses;         /* manages virname when CL_SCAN_ALLMATCHES == 1 */
    unsigned int size_viruses;        /* manages virname when CL_SCAN_ALLMATCHES == 1 */
    unsigned long int *scanned;
    const struct cli_matcher *root;
    const struct cl_engine *engine;
    unsigned long scansize;
    unsigned int options;
    unsigned int recursion;
    unsigned int scannedfiles;
    unsigned int found_possibly_unwanted;
    unsigned int corrupted_input;
    //cli_file_t container_type; /* FIXME: to be made into a stack or array - see bb#1579 & bb#1293 */
    size_t container_size;
    unsigned char handlertype_hash[16];
    //struct cli_dconf *dconf;
    //fmap_t **fmap;
    bitset_t* hook_lsig_matches;
    void *cb_ctx;
//#ifdef HAVE__INTERNAL__SHA_COLLECT
//    char entry_filename[2048];
//    int sha_collect;
//#endif
} cli_ctx;

void *cli_calloc(uint32 nmemb, uint32 size);
extern struct cl_engine *cl_engine_new(void);
extern void cl_init();
void cli_errmsg(const char *str, ...);
void cli_warnmsg(const char *str, ...);