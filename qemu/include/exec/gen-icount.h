#ifndef GEN_ICOUNT_H
#define GEN_ICOUNT_H

#include "qemu/timer.h"

/* Helpers for instruction counting code generation.  */

//static TCGOp *icount_start_insn;

static inline void gen_tb_start(TCGContext *tcg_ctx, TranslationBlock *tb)
{
    //TCGv_i32 count, imm;
    TCGv_i32 flag;

    tcg_ctx->exitreq_label = gen_new_label(tcg_ctx);
    flag = tcg_temp_new_i32(tcg_ctx);
    tcg_gen_ld_i32(tcg_ctx, flag, tcg_ctx->cpu_env,
                   offsetof(CPUState, tcg_exit_req) - offsetof(ArchCPU, env));
    tcg_gen_brcondi_i32(tcg_ctx, TCG_COND_NE, flag, 0, tcg_ctx->exitreq_label);
    tcg_temp_free_i32(tcg_ctx, flag);

#if 0
    tcg_ctx->exitreq_label = gen_new_label();
    if (tb_cflags(tb) & CF_USE_ICOUNT) {
        count = tcg_temp_local_new_i32(tcg_ctx);
    } else {
        count = tcg_temp_new_i32(tcg_ctx);
    }

    tcg_gen_ld_i32(tcg_ctx, count, tcg_ctx->cpu_env,
                   offsetof(ArchCPU, neg.icount_decr.u32) -
                   offsetof(ArchCPU, env));

    if (tb_cflags(tb) & CF_USE_ICOUNT) {
        imm = tcg_temp_new_i32(tcg_ctx);
        /* We emit a movi with a dummy immediate argument. Keep the insn index
         * of the movi so that we later (when we know the actual insn count)
         * can update the immediate argument with the actual insn count.  */
        tcg_gen_movi_i32(tcg_ctx, imm, 0xdeadbeef);
        icount_start_insn = tcg_last_op(tcg_ctx);

        tcg_gen_sub_i32(tcg_ctx, count, count, imm);
        tcg_temp_free_i32(tcg_ctx, imm);
    }

    tcg_gen_brcondi_i32(tcg_ctx, TCG_COND_LT, count, 0, tcg_ctx->exitreq_label);

    if (tb_cflags(tb) & CF_USE_ICOUNT) {
        tcg_gen_st16_i32(tcg_ctx, count, tcg_ctx, cpu_env,
                         offsetof(ArchCPU, neg.icount_decr.u16.low) -
                         offsetof(ArchCPU, env));
    }

    tcg_temp_free_i32(tcg_ctx, count);
#endif
}

static inline void gen_tb_end(TCGContext *tcg_ctx, TranslationBlock *tb, int num_insns)
{
#if 0
    if (tb_cflags(tb) & CF_USE_ICOUNT) {
        /* Update the num_insn immediate parameter now that we know
         * the actual insn count.  */
        tcg_set_insn_param(tcg_ctx, icount_start_insn, 1, num_insns);
    }
#endif

    gen_set_label(tcg_ctx, tcg_ctx->exitreq_label);
    tcg_gen_exit_tb(tcg_ctx, tb, TB_EXIT_REQUESTED);
}

static inline void gen_io_start(TCGContext *tcg_ctx)
{
#if 0
    TCGv_i32 tmp = tcg_const_i32(tcg_ctx, 1);
    tcg_gen_st_i32(tcg_ctx, tmp, tcg_ctx->tcg_env,
                   offsetof(ArchCPU, parent_obj.can_do_io) -
                   offsetof(ArchCPU, env));
    tcg_temp_free_i32(tcg_ctx, tmp);
#endif
}

static inline void gen_io_end(TCGContext *tcg_ctx)
{
#if 0
    TCGv_i32 tmp = tcg_const_i32(tcg_ctx, 0);
    tcg_gen_st_i32(tcg_ctx, tmp, tcg_ctx->tcg_env,
                   offsetof(ArchCPU, parent_obj.can_do_io) -
                   offsetof(ArchCPU, env));
    tcg_temp_free_i32(tcg_ctx, tmp);
#endif
}

#endif
