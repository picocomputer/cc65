;
; int __fastcall__ syncfs (int fd);
;

        .export         _syncfs

        .import         _ria_call_int

        .include        "rp6502.inc"

_syncfs:
        sta     RIA_A
        lda     #RIA_OP_SYNCFS
        jmp     _ria_call_int
