;
; clock_t clock (void);
;

        .export         _clock

        .import         _ria_call_long

        .include        "rp6502.inc"

_clock:
        lda     #RIA_ATTR_CLK_RUN_MS
        sta     RIA_A
        lda     #RIA_OP_ATTR_GET
        jmp     _ria_call_long
