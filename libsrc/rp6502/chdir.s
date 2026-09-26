;
; int __fastcall__ chdir (const char* name);
;

        .export         _chdir

        .import         __ria_push_path, _ria_call_int

        .include        "rp6502.inc"

_chdir:
        jsr     __ria_push_path
        bmi     @done
        lda     #RIA_OP_CHDIR
        jmp     _ria_call_int
@done:  rts
