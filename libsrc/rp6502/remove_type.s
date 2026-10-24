;
; int __fastcall__ unlink (const char* name);
; int __fastcall__ rmdir (const char* name);
;
; REMOVE takes a file or an empty directory, so the type is tested first.
; unlink() takes a file and refuses a directory, and rmdir() takes a
; directory and refuses a file, both with EACCES.
;

        .export         _unlink, _rmdir

        .import         __ria_push_path

        .importzp       ptr1, tmp1

        .include        "rp6502.inc"
        .include        "errno.inc"

; The directory bit of fattrib in f_stat_t.
FATTRIB_DIR     = $10

_unlink:
        ldy     #0              ; take a file, whose directory bit is 0
        .byte   $2C             ; bit abs, skips the ldy below
_rmdir: ldy     #FATTRIB_DIR    ; take a directory
        sty     tmp1
        jsr     __ria_push_path
        bmi     @done
        lda     #RIA_OP_STAT
        sta     RIA_OP
        jsr     RIA_SPIN
        bmi     @done
        ldy     #13             ; fattrib follows fsize and the dates and times
@attr:  lda     RIA_XSTACK
        dey
        bne     @attr
        stz     RIA_OP          ; RIA_OP_DROP_XSTACK
        and     #FATTRIB_DIR
        eor     tmp1
        bne     @wrong
        lda     ptr1
        ldx     ptr1+1
        jsr     __ria_push_path
        lda     #RIA_OP_REMOVE
        sta     RIA_OP
        jmp     RIA_SPIN
@wrong: lda     #EACCES
        jmp     ___directerrno
@done:  rts
