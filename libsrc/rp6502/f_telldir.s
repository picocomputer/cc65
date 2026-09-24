;
; long __fastcall__ f_telldir (int dirdes);
;

        .export         _f_telldir

        .import         _ria_call_long

        .include        "rp6502.inc"

_f_telldir:
        sta     RIA_A
        lda     #RIA_OP_TELLDIR
        jmp     _ria_call_long
