;
; int __fastcall__ close (int fd);
;

        .export         _close

        .import         _ria_call_int

        .include        "rp6502.inc"

_close:
        sta     RIA_A
        lda     #RIA_OP_CLOSE
        jmp     _ria_call_int
