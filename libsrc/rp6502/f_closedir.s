;
; int __fastcall__ f_closedir (int dirdes);
;

        .export         _f_closedir

        .import         _ria_call_int

        .include        "rp6502.inc"

_f_closedir:
        sta     RIA_A
        lda     #RIA_OP_CLOSEDIR
        jmp     _ria_call_int
