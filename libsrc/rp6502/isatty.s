;
; int __fastcall__ isatty (int fd);
;

        .export         _isatty
        .import         return0

        .include        "rp6502.inc"

; 1 for the console, CON: or TTY:, on any descriptor. A closed one is -1
; with errno set, and is not a terminal either.
_isatty:
        sta     RIA_A
        lda     #RIA_OP_ISATTY
        sta     RIA_OP
        jsr     RIA_SPIN
        cpx     #$00
        bne     @no
        rts
@no:    jmp     return0
