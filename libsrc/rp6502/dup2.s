;
; int __fastcall__ dup2 (int fd, int fd2);
;

        .export         _dup2

        .import         popax

        .include        "rp6502.inc"

_dup2:
        sta     RIA_A
        jsr     popax
        stx     RIA_XSTACK
        sta     RIA_XSTACK
        lda     #RIA_OP_DUP2
        sta     RIA_OP
        jmp     RIA_SPIN
