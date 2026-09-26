;
; int __fastcall__ remove (const char* name);
;

        .export         _remove

        .import         __ria_push_path, _ria_call_int

        .include        "rp6502.inc"

_remove:
        jsr     __ria_push_path
        bmi     @done
        lda     #RIA_OP_UNLINK
        jmp     _ria_call_int
@done:  rts
