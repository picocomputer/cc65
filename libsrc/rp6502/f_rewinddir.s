;
; int __fastcall__ f_rewinddir (int dirdes);
;

        .export         _f_rewinddir

        .import         _ria_call_int

        .include        "rp6502.inc"

_f_rewinddir:
        sta     RIA_A
        lda     #RIA_OP_REWINDDIR
        jmp     _ria_call_int
