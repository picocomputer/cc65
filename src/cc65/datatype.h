/*****************************************************************************/
/*                                                                           */
/*				  datatype.h				     */
/*                                                                           */
/*		 Type string handling for the cc65 C compiler		     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 1998-2004 Ullrich von Bassewitz                                       */
/*               Römerstrasse 52                                             */
/*               D-70794 Filderstadt                                         */
/* EMail:        uz@cc65.org                                                 */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/



#ifndef DATATYPE_H
#define DATATYPE_H



#include <stdio.h>

/* common */
#include "attrib.h"
#include "inline.h"

/* cc65 */
#include "funcdesc.h"



/*****************************************************************************/
/*     	      	    	       	     Data   				     */
/*****************************************************************************/




/* Basic data types */
enum {
    T_END	    = 0x0000,

    /* Basic types */
    T_TYPE_NONE	    = 0x0000,
    T_TYPE_CHAR	    = 0x0001,
    T_TYPE_SHORT    = 0x0002,
    T_TYPE_INT 	    = 0x0003,
    T_TYPE_LONG	    = 0x0004,
    T_TYPE_LONGLONG = 0x0005,
    T_TYPE_ENUM	    = 0x0006,
    T_TYPE_FLOAT    = 0x0007,
    T_TYPE_DOUBLE   = 0x0008,
    T_TYPE_VOID     = 0x0009,
    T_TYPE_STRUCT   = 0x000A,
    T_TYPE_UNION    = 0x000B,
    T_TYPE_ARRAY    = 0x000C,
    T_TYPE_PTR      = 0x000D,
    T_TYPE_FUNC     = 0x000E,
    T_MASK_TYPE	    = 0x001F,

    /* Type classes */
    T_CLASS_NONE    = 0x0000,
    T_CLASS_INT	    = 0x0020,
    T_CLASS_FLOAT   = 0x0040,
    T_CLASS_PTR	    = 0x0060,
    T_CLASS_STRUCT  = 0x0080,
    T_CLASS_FUNC    = 0x00A0,
    T_MASK_CLASS    = 0x00E0,

    /* Type signedness */
    T_SIGN_NONE	    = 0x0000,
    T_SIGN_UNSIGNED = 0x0100,
    T_SIGN_SIGNED   = 0x0200,
    T_MASK_SIGN     = 0x0300,

    /* Type size modifiers */
    T_SIZE_NONE	    = 0x0000,
    T_SIZE_SHORT    = 0x0400,
    T_SIZE_LONG     = 0x0800,
    T_SIZE_LONGLONG = 0x0C00,
    T_MASK_SIZE	    = 0x0C00,

    /* Type qualifiers */
    T_QUAL_NONE     = 0x0000,
    T_QUAL_CONST    = 0x1000,
    T_QUAL_VOLATILE = 0x2000,
    T_MASK_QUAL	    = 0x3000,

    /* Types */
    T_CHAR     	= T_TYPE_CHAR     | T_CLASS_INT    | T_SIGN_UNSIGNED | T_SIZE_NONE,
    T_SCHAR    	= T_TYPE_CHAR     | T_CLASS_INT    | T_SIGN_SIGNED   | T_SIZE_NONE,
    T_UCHAR    	= T_TYPE_CHAR     | T_CLASS_INT    | T_SIGN_UNSIGNED | T_SIZE_NONE,
    T_SHORT    	= T_TYPE_SHORT    | T_CLASS_INT    | T_SIGN_SIGNED   | T_SIZE_SHORT,
    T_USHORT    = T_TYPE_SHORT    | T_CLASS_INT    | T_SIGN_UNSIGNED | T_SIZE_SHORT,
    T_INT      	= T_TYPE_INT      | T_CLASS_INT    | T_SIGN_SIGNED   | T_SIZE_NONE,
    T_UINT     	= T_TYPE_INT      | T_CLASS_INT    | T_SIGN_UNSIGNED | T_SIZE_NONE,
    T_LONG     	= T_TYPE_LONG     | T_CLASS_INT    | T_SIGN_SIGNED   | T_SIZE_LONG,
    T_ULONG    	= T_TYPE_LONG     | T_CLASS_INT    | T_SIGN_UNSIGNED | T_SIZE_LONG,
    T_LONGLONG 	= T_TYPE_LONGLONG | T_CLASS_INT    | T_SIGN_SIGNED   | T_SIZE_LONGLONG,
    T_ULONGLONG	= T_TYPE_LONGLONG | T_CLASS_INT    | T_SIGN_UNSIGNED | T_SIZE_LONGLONG,
    T_ENUM     	= T_TYPE_ENUM     | T_CLASS_INT    | T_SIGN_SIGNED   | T_SIZE_NONE,
    T_FLOAT    	= T_TYPE_FLOAT    | T_CLASS_FLOAT  | T_SIGN_NONE     | T_SIZE_NONE,
    T_DOUBLE   	= T_TYPE_DOUBLE   | T_CLASS_FLOAT  | T_SIGN_NONE     | T_SIZE_NONE,
    T_VOID     	= T_TYPE_VOID     | T_CLASS_NONE   | T_SIGN_NONE     | T_SIZE_NONE,
    T_STRUCT    = T_TYPE_STRUCT   | T_CLASS_STRUCT | T_SIGN_NONE     | T_SIZE_NONE,
    T_UNION     = T_TYPE_UNION    | T_CLASS_STRUCT | T_SIGN_NONE     | T_SIZE_NONE,
    T_ARRAY    	= T_TYPE_ARRAY    | T_CLASS_PTR    | T_SIGN_NONE     | T_SIZE_NONE,
    T_PTR      	= T_TYPE_PTR      | T_CLASS_PTR    | T_SIGN_NONE     | T_SIZE_NONE,
    T_FUNC     	= T_TYPE_FUNC     | T_CLASS_FUNC   | T_SIGN_NONE     | T_SIZE_NONE,

    /* Aliases */
    T_SIZE_T    = T_UINT,
};



/* Forward for a symbol entry */
struct SymEntry;

/* Type entry */
typedef unsigned short type;

/* Maximum length of a type string */
#define MAXTYPELEN   	30

/* Type elements needed for Encode/Decode */
#define DECODE_SIZE    	5

/* Special encodings for element counts of an array */
#define UNSPECIFIED     -1L     /* Element count was not specified */
#define FLEXIBLE        0L      /* Flexible array struct member */

/* Sizes */
#define SIZEOF_CHAR     1
#define SIZEOF_SHORT    2
#define SIZEOF_INT      2
#define SIZEOF_LONG     4
#define SIZEOF_LONGLONG 8
#define SIZEOF_FLOAT    4
#define SIZEOF_DOUBLE   4
#define SIZEOF_PTR      2

/* Predefined type strings */
extern type type_uchar [];
extern type type_int [];
extern type type_uint [];
extern type type_long [];
extern type type_ulong [];
extern type type_void [];
extern type type_size_t [];



/*****************************************************************************/
/*     	      	      	       	     Code				     */
/*****************************************************************************/



unsigned TypeLen (const type* Type);
/* Return the length of the type string */

type* TypeCpy (type* Dest, const type* Src);
/* Copy a type string */

type* TypeCat (type* Dest, const type* Src);
/* Append Src */

type* TypeDup (const type* Type);
/* Create a copy of the given type on the heap */

type* TypeAlloc (unsigned Len);
/* Allocate memory for a type string of length Len. Len *must* include the
 * trailing T_END.
 */

void TypeFree (type* Type);
/* Free a type string */

int SignExtendChar (int C);
/* Do correct sign extension of a character */

type GetDefaultChar (void);
/* Return the default char type (signed/unsigned) depending on the settings */

type* GetCharArrayType (unsigned Len);
/* Return the type for a char array of the given length */

type* GetImplicitFuncType (void);
/* Return a type string for an inplicitly declared function */

type* PointerTo (const type* T);
/* Return a type string that is "pointer to T". The type string is allocated
 * on the heap and may be freed after use.
 */

void PrintType (FILE* F, const type* Type);
/* Output translation of type array. */

void PrintRawType (FILE* F, const type* Type);
/* Print a type string in raw format (for debugging) */

void PrintFuncSig (FILE* F, const char* Name, type* Type);
/* Print a function signature. */

void Encode (type* Type, unsigned long Val);
/* Encode Val into the given type string */

void EncodePtr (type* Type, void* P);
/* Encode a pointer into a type array */

unsigned long Decode (const type* Type);
/* Decode an unsigned long from a type array */

void* DecodePtr (const type* Type);
/* Decode a pointer from a type array */

int HasEncode (const type* Type);
/* Return true if the given type has encoded data */

void CopyEncode (const type* Source, type* Target);
/* Copy encoded data from Source to Target */

#if defined(HAVE_INLINE)
INLINE type UnqualifiedType (type T)
/* Return the unqalified type */
{
    return (T & ~T_MASK_QUAL);
}
#else
#  define UnqualifiedType(T)    ((T) & ~T_MASK_QUAL)
#endif

unsigned SizeOf (const type* Type);
/* Compute size of object represented by type array. */

unsigned PSizeOf (const type* Type);
/* Compute size of pointer object. */

unsigned CheckedSizeOf (const type* T);
/* Return the size of a data type. If the size is zero, emit an error and
 * return some valid size instead (so the rest of the compiler doesn't have
 * to work with invalid sizes).
 */
unsigned CheckedPSizeOf (const type* T);
/* Return the size of a data type that is pointed to by a pointer. If the
 * size is zero, emit an error and return some valid size instead (so the
 * rest of the compiler doesn't have to work with invalid sizes).
 */

unsigned TypeOf (const type* Type);
/* Get the code generator base type of the object */

type* Indirect (type* Type);
/* Do one indirection for the given type, that is, return the type where the
 * given type points to.
 */

type* ArrayToPtr (const type* Type);
/* Convert an array to a pointer to it's first element */

#if defined(HAVE_INLINE)
INLINE int IsTypeChar (const type* T)
/* Return true if this is a character type */
{
    return (T[0] & T_MASK_TYPE) == T_TYPE_CHAR;
}
#else
#  define IsTypeChar(T)         (((T)[0] & T_MASK_TYPE) == T_TYPE_CHAR)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeInt (const type* T)
/* Return true if this is an int type (signed or unsigned) */
{
    return (T[0] & T_MASK_TYPE) == T_TYPE_INT;
}
#else
#  define IsTypeInt(T)          (((T)[0] & T_MASK_TYPE) == T_TYPE_INT)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeLong (const type* T)
/* Return true if this is a long type (signed or unsigned) */
{
    return (T[0] & T_MASK_TYPE) == T_TYPE_LONG;
}
#else
#  define IsTypeLong(T)         (((T)[0] & T_MASK_TYPE) == T_TYPE_LONG)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeFloat (const type* T)
/* Return true if this is a float type */
{
    return (T[0] & T_MASK_TYPE) == T_TYPE_FLOAT;
}
#else
#  define IsTypeFloat(T)        (((T)[0] & T_MASK_TYPE) == T_TYPE_FLOAT)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeDouble (const type* T)
/* Return true if this is a double type */
{
    return (T[0] & T_MASK_TYPE) == T_TYPE_DOUBLE;
}
#else
#  define IsTypeDouble(T)       (((T)[0] & T_MASK_TYPE) == T_TYPE_DOUBLE)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypePtr (const type* T)
/* Return true if this is a pointer type */
{
    return ((T[0] & T_MASK_TYPE) == T_TYPE_PTR);
}
#else
#  define IsTypePtr(T)          (((T)[0] & T_MASK_TYPE) == T_TYPE_PTR)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeStruct (const type* T)
/* Return true if this is a struct type */
{
    return ((T[0] & T_MASK_TYPE) == T_TYPE_STRUCT);
}
#else
#  define IsTypeStruct(T)       (((T)[0] & T_MASK_TYPE) == T_TYPE_STRUCT)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeUnion (const type* T)
/* Return true if this is a union type */
{
    return ((T[0] & T_MASK_TYPE) == T_TYPE_UNION);
}
#else
#  define IsTypeUnion(T)       (((T)[0] & T_MASK_TYPE) == T_TYPE_UNION)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeArray (const type* T)
/* Return true if this is an array type */
{
    return ((T[0] & T_MASK_TYPE) == T_TYPE_ARRAY);
}
#else
#  define IsTypeArray(T)        (((T)[0] & T_MASK_TYPE) == T_TYPE_ARRAY)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeVoid (const type* T)
/* Return true if this is a void type */
{
    return (T[0] & T_MASK_TYPE) == T_TYPE_VOID;
}
#else
#  define IsTypeVoid(T)         (((T)[0] & T_MASK_TYPE) == T_TYPE_VOID)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeFunc (const type* T)
/* Return true if this is a function class */
{
    return ((T[0] & T_MASK_TYPE) == T_TYPE_FUNC);
}
#else
#  define IsTypeFunc(T)         (((T)[0] & T_MASK_TYPE) == T_TYPE_FUNC)
#endif

#if defined(HAVE_INLINE)
INLINE int IsTypeFuncPtr (const type* T)
/* Return true if this is a function pointer */
{
    return ((T[0] & T_MASK_TYPE) == T_TYPE_PTR && (T[1] & T_MASK_TYPE) == T_TYPE_FUNC);
}
#else
#  define IsTypeFuncPtr(T)      \
        ((((T)[0] & T_MASK_TYPE) == T_TYPE_PTR) && (((T)[1] & T_MASK_TYPE) == T_TYPE_FUNC))
#endif

int IsClassInt (const type* Type) attribute ((const));
/* Return true if this is an integer type */

int IsClassFloat (const type* Type) attribute ((const));
/* Return true if this is a float type */

int IsClassPtr (const type* Type) attribute ((const));
/* Return true if this is a pointer type */

int IsClassStruct (const type* Type) attribute ((const));
/* Return true if this is a struct type */

int IsSignUnsigned (const type* Type) attribute ((const));
/* Return true if this is an unsigned type */

int IsQualConst (const type* T) attribute ((const));
/* Return true if the given type has a const memory image */

int IsQualVolatile (const type* T) attribute ((const));
/* Return true if the given type has a volatile type qualifier */

int IsFastCallFunc (const type* T) attribute ((const));
/* Return true if this is a function type or pointer to function with
 * __fastcall__ calling conventions
 */

int IsVariadicFunc (const type* T) attribute ((const));
/* Return true if this is a function type or pointer to function type with
 * variable parameter list
 */

#if defined(HAVE_INLINE)
INLINE type GetType (const type* T)
/* Get the raw type */
{
    return (T[0] & T_MASK_TYPE);
}
#else
#  define GetType(T)    ((T)[0] & T_MASK_TYPE)
#endif

#if defined(HAVE_INLINE)
INLINE type GetClass (const type* T)
/* Get the class of a type string */
{
    return (T[0] & T_MASK_CLASS);
}
#else
#  define GetClass(T)    ((T)[0] & T_MASK_CLASS)
#endif

#if defined(HAVE_INLINE)
INLINE type GetSignedness (const type* T)
/* Get the sign of a type */
{
    return (T[0] & T_MASK_SIGN);
}
#else
#  define GetSignedness(T)      ((T)[0] & T_MASK_SIGN)
#endif

#if defined(HAVE_INLINE)
INLINE type GetSizeModifier (const type* T)
/* Get the size modifier of a type */
{
    return (T[0] & T_MASK_SIZE);
}
#else
#  define GetSizeModifier(T)      ((T)[0] & T_MASK_SIZE)
#endif

type GetQualifier (const type* T) attribute ((const));
/* Get the qualifier from the given type string */

FuncDesc* GetFuncDesc (const type* T) attribute ((const));
/* Get the FuncDesc pointer from a function or pointer-to-function type */

type* GetFuncReturn (type* T) attribute ((const));
/* Return a pointer to the return type of a function or pointer-to-function type */

long GetElementCount (const type* T);
/* Get the element count of the array specified in T (which must be of
 * array type).
 */

type* GetElementType (type* T);
/* Return the element type of the given array type. */



/* End of datatype.h */

#endif



