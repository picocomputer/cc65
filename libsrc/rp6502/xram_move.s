;
; 2026, Rumbledethumps
;
; void __fastcall__ xram_move (unsigned dest, unsigned src, unsigned count);
;
; Portal 0 reads and portal 1 writes. Overlapping regions that would be
; overwritten before they are read run backward on a step of -1.

.include "xram.inc"

.export _xram_move

.code

_xram_move:
        sta     ptr3            ; count arrives in A/X
        stx     ptr3+1
        jsr     popax           ; src
        sta     ptr1
        stx     ptr1+1
        sta     RIA_ADDR0
        stx     RIA_ADDR0+1
        jsr     popax           ; dest
        sta     ptr2
        stx     ptr2+1
        sta     RIA_ADDR1
        stx     RIA_ADDR1+1
        sec                     ; dest - src < count means backward
        sbc     ptr1
        tay
        txa
        sbc     ptr1+1
        tax
        tya
        cmp     ptr3
        txa
        sbc     ptr3+1
        lda     #1
        bcs     @step
        lda     ptr3            ; C is clear, so X:Y = count - 1
        sbc     #0
        tay
        lda     ptr3+1
        sbc     #0
        tax
        tya                     ; the last byte of each region
        clc
        adc     ptr1
        sta     RIA_ADDR0
        txa
        adc     ptr1+1
        sta     RIA_ADDR0+1
        tya
        clc
        adc     ptr2
        sta     RIA_ADDR1
        txa
        adc     ptr2+1
        sta     RIA_ADDR1+1
        lda     #$FF
@step:  sta     RIA_STEP0
        sta     RIA_STEP1
        ldx     ptr3+1
        inx                     ; pages, plus one for the partial page
        lda     ptr3
        and     #7
        beq     @blocks
        tay
@rest:  lda     RIA_RW0
        sta     RIA_RW1
        dey
        bne     @rest
@blocks:
        lda     ptr3
        lsr     a
        lsr     a
        lsr     a
        tay
        beq     @next
@page:  .repeat 8
        lda     RIA_RW0
        sta     RIA_RW1
        .endrepeat
        dey
        bne     @page
@next:  ldy     #32
        dex
        bne     @page
        rts
