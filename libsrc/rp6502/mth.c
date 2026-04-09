#include <rp6502.h>

/* ---- Integer ---- */

unsigned int __fastcall__ mth_mul8(unsigned char a, unsigned char b)
{
    ria_set_a(b);
    ria_push_char(a);
    return ria_call_int(RIA_OP_MTH_MUL8);
}

unsigned long __fastcall__ mth_mul16(unsigned int a, unsigned int b)
{
    ria_set_ax(b);
    ria_push_int(a);
    return ria_call_long(RIA_OP_MTH_MUL16);
}

long __fastcall__ mth_muls16(int a, int b)
{
    ria_set_ax((unsigned int)b);
    ria_push_int((unsigned int)a);
    return ria_call_long(RIA_OP_MTH_MULS16);
}

unsigned long __fastcall__ mth_div16(unsigned long dividend, unsigned int divisor)
{
    ria_set_ax(divisor);
    ria_push_long(dividend);
    return ria_call_long(RIA_OP_MTH_DIV16);
}

unsigned int __fastcall__ mth_sqrt32(unsigned long n)
{
    ria_set_axsreg(n);
    return ria_call_int(RIA_OP_MTH_SQRT32);
}

/* ---- Float32 conversions ---- */

fp32_t __fastcall__ mth_itof(long i)
{
    ria_set_axsreg((unsigned long)i);
    return (fp32_t)ria_call_long(RIA_OP_MTH_ITOF);
}

long __fastcall__ mth_ftoi(fp32_t x)
{
    ria_set_axsreg(x);
    return ria_call_long(RIA_OP_MTH_FTOI);
}

/* ---- Float32 arithmetic (binary: a on xstack, b fastcall) ---- */

fp32_t __fastcall__ mth_addf(fp32_t a, fp32_t b)
{
    ria_set_axsreg(b);
    ria_push_long(a);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FADD);
}

fp32_t __fastcall__ mth_subf(fp32_t a, fp32_t b)
{
    ria_set_axsreg(b);
    ria_push_long(a);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FSUB);
}

fp32_t __fastcall__ mth_mulf(fp32_t a, fp32_t b)
{
    ria_set_axsreg(b);
    ria_push_long(a);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FMUL);
}

fp32_t __fastcall__ mth_divf(fp32_t a, fp32_t b)
{
    ria_set_axsreg(b);
    ria_push_long(a);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FDIV);
}

/* ---- Float32 unary ---- */

fp32_t __fastcall__ mth_sqrtf(fp32_t x)
{
    ria_set_axsreg(x);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FSQRT);
}

fp32_t __fastcall__ mth_sinf(fp32_t x)
{
    ria_set_axsreg(x);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FSIN);
}

fp32_t __fastcall__ mth_cosf(fp32_t x)
{
    ria_set_axsreg(x);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FCOS);
}

fp32_t __fastcall__ mth_logf(fp32_t x)
{
    ria_set_axsreg(x);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FLOG);
}

fp32_t __fastcall__ mth_expf(fp32_t x)
{
    ria_set_axsreg(x);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FEXP);
}

/* ---- Float32 binary transcendental (y on xstack, x fastcall) ---- */

fp32_t __fastcall__ mth_atan2f(fp32_t y, fp32_t x)
{
    ria_set_axsreg(x);
    ria_push_long(y);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FATAN2);
}

fp32_t __fastcall__ mth_powf(fp32_t base, fp32_t exp)
{
    ria_set_axsreg(exp);
    ria_push_long(base);
    return (fp32_t)ria_call_long(RIA_OP_MTH_FPOW);
}
