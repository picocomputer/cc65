;
; long __fastcall__ ria_attr_get (unsigned char id);
;

        .export         _ria_attr_get

        .import         _ria_call_long

        .include        "rp6502.inc"

_ria_attr_get:
        sta     RIA_A
        lda     #RIA_OP_ATTR_GET
        jmp     _ria_call_long
