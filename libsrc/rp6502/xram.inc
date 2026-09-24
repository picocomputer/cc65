;
; 2026, Rumbledethumps
;
; XRAM block memory access, optimally unrolled.

.include "rp6502.inc"

.importzp ptr1, ptr2, ptr3
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
        ldx     ptr3+1
        inx                     ; pages, plus one for the partial page
        lda     ptr3
        and     #$F8
        tay
        beq     @next
        clc                     ; bias dest so the partial page ends as Y wraps
        adc     ptr2
        sta     ptr2
        bcs     :+
        dec     ptr2+1
:       tya
        eor     #$FF
        tay
        iny
@page:  .repeat 8
        lda     rw
        sta     (ptr2),y
        iny
        .endrepeat
        bne     @page
        inc     ptr2+1
@next:  dex
        bne     @page
        lda     ptr3
        and     #7
        beq     @done
        tax
@rest:  lda     rw
        sta     (ptr2),y
        iny
        dex
        bne     @rest
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
        ldx     ptr3+1
        inx                     ; pages, plus one for the partial page
        lda     ptr3
        and     #$F8
        tay
        beq     @next
        clc                     ; bias src so the partial page ends as Y wraps
        adc     ptr2
        sta     ptr2
        bcs     :+
        dec     ptr2+1
:       tya
        eor     #$FF
        tay
        iny
@page:  .repeat 8
        lda     (ptr2),y
        sta     rw
        iny
        .endrepeat
        bne     @page
        inc     ptr2+1
@next:  dex
        bne     @page
        lda     ptr3
        and     #7
        beq     @done
        tax
@rest:  lda     (ptr2),y
        sta     rw
        iny
        dex
        bne     @rest
@done:  rts
.endmacro

; void __fastcall__ xramN_set (unsigned dest, unsigned char val, unsigned count);

.macro xram_set rw, addr, step
        sta     ptr3            ; count arrives in A/X
        stx     ptr3+1
        jsr     popa            ; value
        pha
        jsr     popax           ; dest is the XRAM address
        sta     addr
        stx     addr+1
        lda     #1
        sta     step
        ply                     ; the value stays in Y across the stores
        ldx     ptr3+1
        inx                     ; pages, plus one for the partial page
        lda     ptr3
        and     #15
        beq     @blocks
@rest:  sty     rw
        dec     a
        bne     @rest
@blocks:
        lda     ptr3
        lsr     a
        lsr     a
        lsr     a
        lsr     a
        beq     @next
@page:  .repeat 16
        sty     rw
        .endrepeat
        dec     a
        bne     @page
@next:  lda     #16
        dex
        bne     @page
        rts
.endmacro
