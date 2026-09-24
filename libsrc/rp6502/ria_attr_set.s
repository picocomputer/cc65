;
; int __fastcall__ ria_attr_set (long val, unsigned char id);
;

        .export         _ria_attr_set

        .import         _ria_call_int, _ria_push_long
        .import         popeax

        .include        "rp6502.inc"

_ria_attr_set:
        sta     RIA_A
        jsr     popeax
        jsr     _ria_push_long
        lda     #RIA_OP_ATTR_SET
        jmp     _ria_call_int
