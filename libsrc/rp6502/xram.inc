;
; 2026, Rumbledethumps
;
; XRAM block memory access, optimally unrolled.

.include "rp6502.inc"

.importzp ptr1, ptr2, ptr3, tmp1
.import popa, popax

; void __fastcall__ xramN_read (void* dest, unsigned src, unsigned count);

.macro xram_read rw, addr, step
        sta     ptr3            ; count arrives in A/X
        stx     ptr3+1
        jsr     popax           ; src is the XRAM address
        sta     addr
        stx     addr+1
        lda     #1
        sta     step
        jsr     popax           ; dest walks 6502 RAM
        sta     ptr2
        stx     ptr2+1
        ldy     #0              ; popax leaves Y at 1 on a 65C02
        ldx     ptr3+1
        beq     @tail
@page:  .repeat 8
        lda     rw
        sta     (ptr2),y
        iny
        .endrepeat
        bne     @page
        inc     ptr2+1
        dex
        bne     @page
@tail:  lda     ptr3
        beq     @done
        and     #7
        beq     @eights
        tax
@rest:  lda     rw
        sta     (ptr2),y
        iny
        dex
        bne     @rest
@eights:
        lda     ptr3
        lsr     a
        lsr     a
        lsr     a
        beq     @done
        tax
@eight: .repeat 8
        lda     rw
        sta     (ptr2),y
        iny
        .endrepeat
        dex
        bne     @eight
@done:  rts
.endmacro

; void __fastcall__ xramN_write (unsigned dest, const void* src, unsigned count);

.macro xram_write rw, addr, step
        sta     ptr3            ; count arrives in A/X
        stx     ptr3+1
        jsr     popax           ; src walks 6502 RAM
        sta     ptr2
        stx     ptr2+1
        jsr     popax           ; dest is the XRAM address
        sta     addr
        stx     addr+1
        lda     #1
        sta     step
        ldy     #0              ; popax leaves Y at 1 on a 65C02
        ldx     ptr3+1
        beq     @tail
@page:  .repeat 8
        lda     (ptr2),y
        sta     rw
        iny
        .endrepeat
        bne     @page
        inc     ptr2+1
        dex
        bne     @page
@tail:  lda     ptr3
        beq     @done
        and     #7
        beq     @eights
        tax
@rest:  lda     (ptr2),y
        sta     rw
        iny
        dex
        bne     @rest
@eights:
        lda     ptr3
        lsr     a
        lsr     a
        lsr     a
        beq     @done
        tax
@eight: .repeat 8
        lda     (ptr2),y
        sta     rw
        iny
        .endrepeat
        dex
        bne     @eight
@done:  rts
.endmacro

; void __fastcall__ xramN_set (unsigned dest, unsigned char val, unsigned count);

.macro xram_set rw, addr, step
        sta     ptr3            ; count arrives in A/X
        stx     ptr3+1
        jsr     popa            ; value
        sta     tmp1
        jsr     popax           ; dest is the XRAM address
        sta     addr
        stx     addr+1
        lda     #1
        sta     step
        lda     tmp1            ; the value stays in A across the stores
        ldx     ptr3+1
        beq     @tail
@page:  ldy     #16
@pg:    .repeat 16
        sta     rw
        .endrepeat
        dey
        bne     @pg
        dex
        bne     @page
@tail:  ldy     ptr3
        beq     @done
        tya
        and     #15
        beq     @sixteens
        tax
        lda     tmp1
@rest:  sta     rw
        dex
        bne     @rest
@sixteens:
        tya
        lsr     a
        lsr     a
        lsr     a
        lsr     a
        beq     @done
        tax
        lda     tmp1
@blk:   .repeat 16
        sta     rw
        .endrepeat
        dex
        bne     @blk
@done:  rts
.endmacro
