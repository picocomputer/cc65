;
; char* __fastcall__ getcwd (char* buf, size_t size);
;

        .export         _getcwd

        .import         popptr1

        .importzp       ptr1, ptr2

        .include        "rp6502.inc"
        .include        "errno.inc"

_getcwd:
        sta     ptr2
        stx     ptr2+1          ; size
        jsr     popptr1         ; buf, Y = 0
        lda     ptr2
        ora     ptr2+1
        beq     @inval
        lda     #RIA_OP_GETCWD
        sta     RIA_OP
        jsr     RIA_SPIN        ; length including the terminator
        bmi     @fail
        clc
        sbc     ptr2
        txa
        sbc     ptr2+1
        bcs     @range          ; length > size
; A path has at most 255 bytes, so Y reaches the terminator.
@copy:  lda     RIA_XSTACK
        sta     (ptr1),y
        beq     @done
        iny
        bne     @copy
@done:  lda     ptr1
        ldx     ptr1+1
        rts
@range: stz     RIA_OP          ; RIA_OP_DROP_XSTACK
        lda     #ERANGE
        bra     @err
@inval: lda     #EINVAL
@err:   jsr     ___seterrno     ; A = 0
        tax
        rts
@fail:  inx                     ; NULL
        txa
        rts
