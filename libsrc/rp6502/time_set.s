;
; int __fastcall__ time_set (unsigned long time);
;

        .export         _time_set

        .import         _ria_call_int, _ria_push_long

        .include        "rp6502.inc"

_time_set:
        stz     RIA_XSTACK      ; zero on top keeps the unsigned time positive
        jsr     _ria_push_long
        lda     #RIA_OP_TIME_SET
        jmp     _ria_call_int
