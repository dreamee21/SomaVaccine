#include"stdafx.h"
#include"other.h"
#include"default.h"
struct cli_matcher
{
    unsigned int type;

    /* Extended Boyer-Moore */
    uint8 *bm_shift;
    struct cli_bm_patt **bm_suffix, **bm_pattab;
    uint32 *soff, soff_len; /* for PE section sigs */
    uint32 bm_offmode, bm_patterns, bm_reloff_num, bm_absoff_num;

    /* HASH */
    struct cli_hash_patt hm;

    /* Extended Aho-Corasick */
    uint32 ac_partsigs, ac_nodes, ac_patterns, ac_lsigs;
    struct cli_ac_lsig **ac_lsigtable;
    struct cli_ac_node *ac_root, **ac_nodetable;
    struct cli_ac_patt **ac_pattable;
    struct cli_ac_patt **ac_reloff;
    uint32 ac_reloff_num, ac_absoff_num;
    uint8 ac_mindepth, ac_maxdepth;
    struct filter *filter;

    uint16 maxpatlen;
    uint8 ac_only;
//#ifdef USE_MPOOL
//    mpool_t *mempool;
//#endif
};