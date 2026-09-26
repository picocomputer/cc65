;
; int __fastcall__ f_seekdir (long offs, int dirdes);
;

        .export         _f_seekdir

        .import         _ria_call_int, _ria_push_long
        .import         popeax

        .include        "rp6502.inc"

_f_seekdir:
        sta     RIA_A
        jsr     popeax
        jsr     _ria_push_long
        lda     #RIA_OP_SEEKDIR
        jmp     _ria_call_int
