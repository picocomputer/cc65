;
; int __fastcall__ f_opendir (const char* name);
;

        .export         _f_opendir

        .import         __ria_push_path, _ria_call_int

        .include        "rp6502.inc"

_f_opendir:
        jsr     __ria_push_path
        bmi     @done
        lda     #RIA_OP_OPENDIR
        jmp     _ria_call_int
@done:  rts
