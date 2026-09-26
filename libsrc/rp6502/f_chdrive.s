;
; int __fastcall__ f_chdrive (const char* name);
;

        .export         _f_chdrive

        .import         __ria_push_path, _ria_call_int

        .include        "rp6502.inc"

_f_chdrive:
        jsr     __ria_push_path
        bmi     @done
        lda     #RIA_OP_CHDRIVE
        jmp     _ria_call_int
@done:  rts
