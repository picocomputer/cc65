;
; 2026, Rumbledethumps
;
; XRAM block copies, optimally unrolled.

.include "rp6502.inc"

.importzp ptr2, ptr3
.import popax

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
