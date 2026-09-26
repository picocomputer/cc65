;
; long __fastcall__ f_lseek (long offset, int whence, int fildes);
;

        .export         _f_lseek

        .import         _ria_call_long
        .import         incsp6

        .importzp       c_sp

        .include        "rp6502.inc"

_f_lseek:
        sta     RIA_A           ; fildes
        ldy     #5
@push:  lda     (c_sp),y        ; offset, high byte first
        sta     RIA_XSTACK
        dey
        cpy     #1
        bne     @push
        lda     (c_sp)          ; whence
        sta     RIA_XSTACK
        lda     #RIA_OP_LSEEK
        jsr     _ria_call_long
        jmp     incsp6
