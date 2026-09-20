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
        jsr     popax           ; dest
        sta     ptr2
        stx     ptr2+1
        sec                     ; dest - src < count means backward
        lda     ptr2
        sbc     ptr1
        tay
        lda     ptr2+1
        sbc     ptr1+1
        tax
        tya
        cmp     ptr3
        txa
        sbc     ptr3+1
        bcc     @back
        lda     ptr1
        sta     RIA_ADDR0
        lda     ptr1+1
        sta     RIA_ADDR0+1
        lda     ptr2
        sta     RIA_ADDR1
        lda     ptr2+1
        sta     RIA_ADDR1+1
        lda     #1
        bne     @step
@back:  clc                     ; the last byte of each region
        lda     ptr1
        adc     ptr3
        sta     ptr1
        lda     ptr1+1
        adc     ptr3+1
        sta     ptr1+1
        clc
        lda     ptr2
        adc     ptr3
        sta     ptr2
        lda     ptr2+1
        adc     ptr3+1
        sta     ptr2+1
        lda     ptr1
        bne     :+
        dec     ptr1+1
:       dec     ptr1
        lda     ptr2
        bne     :+
        dec     ptr2+1
:       dec     ptr2
        lda     ptr1
        sta     RIA_ADDR0
        lda     ptr1+1
        sta     RIA_ADDR0+1
        lda     ptr2
        sta     RIA_ADDR1
        lda     ptr2+1
        sta     RIA_ADDR1+1
        lda     #$FF
@step:  sta     RIA_STEP0
        sta     RIA_STEP1
        ldx     ptr3+1
        beq     @tail
@page:  ldy     #32
@pg:    .repeat 8
        lda     RIA_RW0
        sta     RIA_RW1
        .endrepeat
        dey
        bne     @pg
        dex
        bne     @page
@tail:  lda     ptr3
        beq     @done
        and     #7
        beq     @eights
        tax
@rest:  lda     RIA_RW0
        sta     RIA_RW1
        dex
        bne     @rest
@eights:
        lda     ptr3
        lsr     a
        lsr     a
        lsr     a
        beq     @done
        tax
@blk:   .repeat 8
        lda     RIA_RW0
        sta     RIA_RW1
        .endrepeat
        dex
        bne     @blk
@done:  rts
