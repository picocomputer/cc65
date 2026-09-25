;
; void __randomize (void);
;

        .export         ___randomize

        .import         _ria_call_int, _srand

        .include        "rp6502.inc"

___randomize:
        lda     #RIA_ATTR_LRAND
        sta     RIA_A
        lda     #RIA_OP_ATTR_GET
        jsr     _ria_call_int
        jmp     _srand
