;
; int xregn (char device, char channel, unsigned char index,
;                      unsigned count, ...);
;
; The frame is the xreg() frame with count after index. Y holds the size
; of the frame, so count is skipped and never sent.
;

        .export         _xregn

        .import         addysp

        .importzp       c_sp

        .include        "rp6502.inc"

_xregn:
        phy
        ldx     #3              ; device, channel, index
@copy:  dey
        lda     (c_sp),y
        sta     RIA_XSTACK
        dex
        bne     @next
        dey                     ; skip count
        dey
@next:  tya
        bne     @copy
        ply
        jsr     addysp
        lda     #RIA_OP_XREG
        sta     RIA_OP
        jmp     RIA_SPIN
