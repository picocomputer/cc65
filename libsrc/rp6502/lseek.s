;
; off_t __fastcall__ lseek (int fd, off_t offset, int whence);
;

        .export         _lseek

        .import         _ria_call_long
        .import         incsp6

        .importzp       c_sp

        .include        "rp6502.inc"

_lseek:
        pha                     ; whence
        ldy     #3
@push:  lda     (c_sp),y        ; offset, high byte first
        sta     RIA_XSTACK
        dey
        bpl     @push
        pla
        sta     RIA_XSTACK
        ldy     #4
        lda     (c_sp),y
        sta     RIA_A           ; fd
        lda     #RIA_OP_LSEEK
        jsr     _ria_call_long
        jmp     incsp6
