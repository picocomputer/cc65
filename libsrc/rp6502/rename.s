;
; int __fastcall__ rename (const char* oldname, const char* newname);
;

        .export         _rename

        .import         __ria_push_path, _ria_call_int
        .import         popax

        .importzp       ptr2

        .include        "rp6502.inc"

_rename:
        sta     ptr2
        stx     ptr2+1
        jsr     popax
        jsr     __ria_push_path
        bmi     @done
        stz     RIA_XSTACK      ; terminates newname
        lda     ptr2
        ldx     ptr2+1
        jsr     __ria_push_path
        bmi     @drop
        lda     #RIA_OP_RENAME
        jmp     _ria_call_int
@drop:  stz     RIA_OP          ; RIA_OP_DROP_XSTACK removes oldname
@done:  rts
