;
; int open (const char* name, int flags, ...);
;

        .export         _open

        .import         __ria_push_path, _ria_call_int
        .import         addysp, popax

        .include        "rp6502.inc"

_open:
        dey
        dey
        dey
        dey
        jsr     addysp          ; drop the optional mode
        jsr     popax
        sta     RIA_A           ; flags
        jsr     popax
        jsr     __ria_push_path
        bmi     @done
        lda     #RIA_OP_OPEN
        jmp     _ria_call_int
@done:  rts
