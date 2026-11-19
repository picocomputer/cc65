;
; int __fastcall__ dup (int fd);
;

        .export         _dup

        .include        "rp6502.inc"

_dup:
        sta     RIA_A
        lda     #RIA_OP_DUP
        sta     RIA_OP
        jmp     RIA_SPIN
