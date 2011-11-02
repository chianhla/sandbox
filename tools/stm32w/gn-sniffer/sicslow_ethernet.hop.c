# 1 "sicslow_ethernet.c"
# 1 "/home/anhlc/contiki-2.5/tools/stm32w/gn-sniffer//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "sicslow_ethernet.c"
# 146 "sicslow_ethernet.c"
# 1 "../../../core/net/uip.h" 1
# 57 "../../../core/net/uip.h"
# 1 "../../../core/./net/uipopt.h" 1
# 75 "../../../core/./net/uipopt.h"
# 1 "../../../platform/mb851/./contiki-conf.h" 1
# 47 "../../../platform/mb851/./contiki-conf.h"
# 1 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h" 1
# 40 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h"
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stdarg.h" 1 3 4
# 40 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 102 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 41 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h" 2

# 1 "../../../cpu/stm32w108/hal/micro/cortexm3/stm32w108/regs.h" 1
# 43 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h" 2
# 1 "../../../cpu/stm32w108/hal/micro/cortexm3/stm32w108/stm32w108_type.h" 1
# 23 "../../../cpu/stm32w108/hal/micro/cortexm3/stm32w108/stm32w108_type.h"
typedef signed long s32;
typedef signed short s16;
typedef signed char s8;

typedef signed long const sc32;
typedef signed short const sc16;
typedef signed char const sc8;

typedef volatile signed long vs32;
typedef volatile signed short vs16;
typedef volatile signed char vs8;

typedef volatile signed long const vsc32;
typedef volatile signed short const vsc16;
typedef volatile signed char const vsc8;

typedef unsigned long u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef unsigned long const uc32;
typedef unsigned short const uc16;
typedef unsigned char const uc8;

typedef volatile unsigned long vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;

typedef volatile unsigned long const vuc32;
typedef volatile unsigned short const vuc16;
typedef volatile unsigned char const vuc8;



typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;


typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
# 44 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h" 2
# 92 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h"
typedef unsigned char boolean;
typedef unsigned char int8u;
typedef signed char int8s;
typedef unsigned short int16u;
typedef signed short int16s;
typedef unsigned int int32u;
typedef signed int int32s;
typedef unsigned int PointerType;
# 184 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h"
extern char __ApplicationFlashStart;
extern char __ApplicationFlashEnd;






void halInternalResetWatchDog(void);
# 324 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h"
void _executeBarrierInstructions(void);
# 375 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h"
    extern int8u _readBasePri(void);
    extern void _writeBasePri(int8u priority);



    extern void _enableBasePri(void);
    extern int8u _disableBasePri(void);
    extern boolean _basePriIsDisabled(void);



    extern void _setPriMask(void);
    extern void _clearPriMask(void);
# 522 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h"
int abs(int I);
# 533 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h"
# 1 "../../../cpu/stm32w108/./hal/micro/generic/compiler/platform-common.h" 1
# 123 "../../../cpu/stm32w108/./hal/micro/generic/compiler/platform-common.h"
  void halCommonMemCopy(void *dest, const void *src, int8u bytes);





  void halCommonMemSet(void *dest, int8u val, int16u bytes);





  int8s halCommonMemCompare(const void *source0, const void *source1, int8u bytes);
# 534 "../../../cpu/stm32w108/./hal/micro/cortexm3/compiler/gnu.h" 2
# 48 "../../../platform/mb851/./contiki-conf.h" 2

# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/inttypes.h" 1 3
# 16 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/inttypes.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stdint.h" 1 3 4


# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 1 3 4
# 41 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
typedef signed char int8_t ;
typedef unsigned char uint8_t ;




typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;




typedef signed short int16_t;
typedef unsigned short uint16_t;
# 67 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
typedef int16_t int_least16_t;
typedef uint16_t uint_least16_t;
# 79 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
typedef signed long int32_t;
typedef unsigned long uint32_t;
# 97 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
typedef int32_t int_least32_t;
typedef uint32_t uint_least32_t;
# 119 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
# 129 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
typedef int64_t int_least64_t;
typedef uint64_t uint_least64_t;
# 159 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
  typedef signed int int_fast8_t;
  typedef unsigned int uint_fast8_t;




  typedef signed int int_fast16_t;
  typedef unsigned int uint_fast16_t;




  typedef signed int int_fast32_t;
  typedef unsigned int uint_fast32_t;
# 213 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
  typedef int_least64_t int_fast64_t;
  typedef uint_least64_t uint_fast64_t;







  typedef long long int intmax_t;
# 231 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
  typedef long long unsigned int uintmax_t;
# 243 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdint.h" 3 4
typedef signed int intptr_t;
typedef unsigned int uintptr_t;
# 4 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stdint.h" 2 3 4
# 17 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/inttypes.h" 2 3

# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 1 3 4
# 323 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 3 4
typedef unsigned int wchar_t;
# 19 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/inttypes.h" 2 3
# 271 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/inttypes.h" 3
typedef struct {
  intmax_t quot;
  intmax_t rem;
} imaxdiv_t;





extern intmax_t imaxabs(intmax_t j);
extern imaxdiv_t imaxdiv(intmax_t numer, intmax_t denomer);
extern intmax_t strtoimax(const char *__restrict, char **__restrict, int);
extern uintmax_t strtoumax(const char *__restrict, char **__restrict, int);
extern intmax_t wcstoimax(const wchar_t *__restrict, wchar_t **__restrict, int);
extern uintmax_t wcstoumax(const wchar_t *__restrict, wchar_t **__restrict, int);
# 50 "../../../platform/mb851/./contiki-conf.h" 2
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/string.h" 1 3
# 10 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/string.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/_ansi.h" 1 3
# 15 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/_ansi.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/newlib.h" 1 3
# 16 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/_ansi.h" 2 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/config.h" 1 3



# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/ieeefp.h" 1 3
# 5 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/config.h" 2 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/features.h" 1 3
# 6 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/config.h" 2 3
# 17 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/_ansi.h" 2 3
# 11 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/string.h" 2 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 1 3
# 13 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/_ansi.h" 1 3
# 14 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 2 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/_types.h" 1 3
# 12 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/_types.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_types.h" 1 3






# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_default_types.h" 1 3
# 26 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_default_types.h" 3
typedef signed char __int8_t ;
typedef unsigned char __uint8_t ;
# 36 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_default_types.h" 3
typedef signed short __int16_t;
typedef unsigned short __uint16_t;
# 46 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_default_types.h" 3
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
# 58 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_default_types.h" 3
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
# 76 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_default_types.h" 3
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
# 99 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_default_types.h" 3
typedef signed long long __int64_t;
typedef unsigned long long __uint64_t;
# 8 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/_types.h" 2 3
# 13 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/_types.h" 2 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/lock.h" 1 3





typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
# 14 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/_types.h" 2 3


typedef long _off_t;







typedef short __dev_t;




typedef unsigned short __uid_t;


typedef unsigned short __gid_t;



__extension__ typedef long long _off64_t;







typedef long _fpos_t;
# 56 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/_types.h" 3
typedef int _ssize_t;






# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 1 3 4
# 352 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 64 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/_types.h" 2 3



typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;



typedef _LOCK_RECURSIVE_T _flock_t;




typedef void *_iconv_t;
# 15 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 2 3






typedef unsigned long __ULong;
# 37 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
struct _reent;






struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};


struct _atexit {
 struct _atexit *_next;
 int _ind;
 void (*_fns[32])(void);
        struct _on_exit_args * _on_exit_args_ptr;
};
# 105 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 141 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
struct __sFILE_fake {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;

  struct _reent *_data;
};




extern void __sinit (struct _reent *);
# 179 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;


  struct _reent *_data;



  void * _cookie;

  int (* _read) (struct _reent *, void *, char *, int)
                     ;
  int (* _write) (struct _reent *, void *, const char *, int)
                            ;
  _fpos_t (* _seek) (struct _reent *, void *, _fpos_t, int);
  int (* _close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  int _offset;






  _flock_t _lock;

  _mbstate_t _mbstate;
  int _flags2;
};
# 286 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
typedef struct __sFILE __FILE;



struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
# 318 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;


  __extension__ unsigned long long _rand_next;

};
# 351 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
struct _mprec
{

  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;
};


struct _misc_reent
{

  char *_strtok_last;
  _mbstate_t _mblen_state;
  _mbstate_t _wctomb_state;
  _mbstate_t _mbtowc_state;
  char _l64a_buf[8];
  int _getdate_err;
  _mbstate_t _mbrlen_state;
  _mbstate_t _mbrtowc_state;
  _mbstate_t _mbsrtowcs_state;
  _mbstate_t _wcrtomb_state;
  _mbstate_t _wcsrtombs_state;
};



struct _reent
{


  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;

  char *_emergency;

  int __sdidinit;

  int _current_category;
  const char *_current_locale;

  struct _mprec *_mp;

  void (* __cleanup) (struct _reent *);

  int _gamma_signgam;


  int _cvtlen;
  char *_cvtbuf;

  struct _rand48 *_r48;
  struct __tm *_localtime_buf;
  char *_asctime_buf;


  void (**(_sig_func))(int);


  struct _atexit *_atexit;
  struct _atexit _atexit0;

  struct _glue __sglue;
  __FILE *__sf;
  struct _misc_reent *_misc;
  char *_signal_buf;
};

extern const struct __sFILE_fake __sf_fake_stdin;
extern const struct __sFILE_fake __sf_fake_stdout;
extern const struct __sFILE_fake __sf_fake_stderr;
# 840 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/reent.h" 3
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;

void _reclaim_reent (struct _reent *);
# 12 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/string.h" 2 3


# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 1 3 4
# 211 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 3 4
typedef unsigned int size_t;
# 15 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/string.h" 2 3







void * memchr (const void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void * memcpy (void *, const void *, size_t);
void * memmove (void *, const void *, size_t);
void * memset (void *, int, size_t);
char *strcat (char *, const char *);
char *strchr (const char *, int);
int strcmp (const char *, const char *);
int strcoll (const char *, const char *);
char *strcpy (char *, const char *);
size_t strcspn (const char *, const char *);
char *strerror (int);
size_t strlen (const char *);
char *strncat (char *, const char *, size_t);
int strncmp (const char *, const char *, size_t);
char *strncpy (char *, const char *, size_t);
char *strpbrk (const char *, const char *);
char *strrchr (const char *, int);
size_t strspn (const char *, const char *);
char *strstr (const char *, const char *);


char *strtok (char *, const char *);


size_t strxfrm (char *, const char *, size_t);


char *strtok_r (char *, const char *, char **);

int bcmp (const void *, const void *, size_t);
void bcopy (const void *, void *, size_t);
void bzero (void *, size_t);
int ffs (int);
char *index (const char *, int);
void * memccpy (void *, const void *, int, size_t);
void * mempcpy (void *, const void *, size_t);
void * memmem (const void *, size_t, const void *, size_t);
char *rindex (const char *, int);
char *stpcpy (char *, const char *);
char *stpncpy (char *, const char *, size_t);
int strcasecmp (const char *, const char *);
char *strcasestr (const char *, const char *);
char *strdup (const char *);
char *_strdup_r (struct _reent *, const char *);
char *strndup (const char *, size_t);
char *_strndup_r (struct _reent *, const char *, size_t);
char *strerror_r (int, char *, size_t);
size_t strlcat (char *, const char *, size_t);
size_t strlcpy (char *, const char *, size_t);
int strncasecmp (const char *, const char *, size_t);
size_t strnlen (const char *, size_t);
char *strsep (char **, const char *);
char *strlwr (char *);
char *strupr (char *);
# 100 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/string.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/string.h" 1 3
# 101 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/string.h" 2 3


# 51 "../../../platform/mb851/./contiki-conf.h" 2
# 61 "../../../platform/mb851/./contiki-conf.h"
typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef int32_t s32_t;
typedef unsigned short uip_stats_t;
# 138 "../../../platform/mb851/./contiki-conf.h"
typedef unsigned long clock_time_t;



typedef unsigned long long rtimer_clock_t;
# 160 "../../../platform/mb851/./contiki-conf.h"
# 1 "./bridge-conf.h" 1
# 161 "../../../platform/mb851/./contiki-conf.h" 2
# 76 "../../../core/./net/uipopt.h" 2
# 572 "../../../core/./net/uipopt.h"
void uip_log(char *msg);
# 58 "../../../core/net/uip.h" 2






typedef union uip_ip6addr_t {
  u8_t u8[16];
  u16_t u16[8];
} uip_ip6addr_t;

typedef uip_ip6addr_t uip_ipaddr_t;
# 85 "../../../core/net/uip.h"
typedef struct uip_802154_shortaddr {
  u8_t addr[2];
} uip_802154_shortaddr;

typedef struct uip_802154_longaddr {
  u8_t addr[8];
} uip_802154_longaddr;


typedef struct uip_80211_addr {
  u8_t addr[6];
} uip_80211_addr;


typedef struct uip_eth_addr {
  u8_t addr[6];
} uip_eth_addr;




typedef uip_802154_longaddr uip_lladdr_t;
# 122 "../../../core/net/uip.h"
# 1 "../../../core/./net/tcpip.h" 1
# 70 "../../../core/./net/tcpip.h"
# 1 "../../../core/./contiki.h" 1
# 38 "../../../core/./contiki.h"
# 1 "../../../core/./contiki-version.h" 1
# 39 "../../../core/./contiki.h" 2


# 1 "../../../core/./sys/process.h" 1
# 57 "../../../core/./sys/process.h"
# 1 "../../../core/./sys/pt.h" 1
# 52 "../../../core/./sys/pt.h"
# 1 "../../../core/./sys/lc.h" 1
# 125 "../../../core/./sys/lc.h"
# 1 "../../../core/./sys/lc-switch.h" 1
# 64 "../../../core/./sys/lc-switch.h"
typedef unsigned short lc_t;
# 126 "../../../core/./sys/lc.h" 2
# 53 "../../../core/./sys/pt.h" 2

struct pt {
  lc_t lc;
};
# 58 "../../../core/./sys/process.h" 2
# 1 "../../../core/./sys/cc.h" 1
# 59 "../../../core/./sys/process.h" 2

typedef unsigned char process_event_t;
typedef void * process_data_t;
typedef unsigned char process_num_events_t;
# 316 "../../../core/./sys/process.h"
struct process {
  struct process *next;



  const char *name;


  char (* thread)(struct pt *, process_event_t, process_data_t);
  struct pt pt;
  unsigned char state, needspoll;
};
# 343 "../../../core/./sys/process.h"
 void process_start(struct process *p, const char *arg);
# 366 "../../../core/./sys/process.h"
 int process_post(struct process *p, process_event_t ev, void* data);
# 378 "../../../core/./sys/process.h"
 void process_post_synch(struct process *p,
        process_event_t ev, void* data);
# 391 "../../../core/./sys/process.h"
 void process_exit(struct process *p);
# 404 "../../../core/./sys/process.h"
 extern struct process *process_current;
# 454 "../../../core/./sys/process.h"
 process_event_t process_alloc_event(void);
# 471 "../../../core/./sys/process.h"
 void process_poll(struct process *p);
# 486 "../../../core/./sys/process.h"
void process_init(void);
# 501 "../../../core/./sys/process.h"
int process_run(void);
# 513 "../../../core/./sys/process.h"
 int process_is_running(struct process *p);







int process_nevents(void);



 extern struct process *process_list;
# 42 "../../../core/./contiki.h" 2
# 1 "../../../core/./sys/autostart.h" 1
# 44 "../../../core/./sys/autostart.h"
# 1 "../../../core/./sys/process.h" 1
# 45 "../../../core/./sys/autostart.h" 2
# 58 "../../../core/./sys/autostart.h"
 extern struct process * const autostart_processes[];

void autostart_start(struct process * const processes[]);
void autostart_exit(struct process * const processes[]);
# 43 "../../../core/./contiki.h" 2

# 1 "../../../core/./sys/timer.h" 1
# 77 "../../../core/./sys/timer.h"
# 1 "../../../core/./sys/clock.h" 1
# 82 "../../../core/./sys/clock.h"
void clock_init(void);
# 91 "../../../core/./sys/clock.h"
 clock_time_t clock_time(void);

void clock_delay(unsigned int);
# 106 "../../../core/./sys/clock.h"
int clock_fine_max(void);
unsigned short clock_fine(void);

 unsigned long clock_seconds(void);
# 78 "../../../core/./sys/timer.h" 2
# 87 "../../../core/./sys/timer.h"
struct timer {
  clock_time_t start;
  clock_time_t interval;
};

void timer_set(struct timer *t, clock_time_t interval);
void timer_reset(struct timer *t);
void timer_restart(struct timer *t);
int timer_expired(struct timer *t);
clock_time_t timer_remaining(struct timer *t);
# 45 "../../../core/./contiki.h" 2
# 1 "../../../core/./sys/ctimer.h" 1
# 58 "../../../core/./sys/ctimer.h"
# 1 "../../../core/./sys/etimer.h" 1
# 66 "../../../core/./sys/etimer.h"
# 1 "../../../core/./sys/timer.h" 1
# 67 "../../../core/./sys/etimer.h" 2
# 77 "../../../core/./sys/etimer.h"
struct etimer {
  struct timer timer;
  struct etimer *next;
  struct process *p;
};
# 99 "../../../core/./sys/etimer.h"
 void etimer_set(struct etimer *et, clock_time_t interval);
# 116 "../../../core/./sys/etimer.h"
 void etimer_reset(struct etimer *et);
# 133 "../../../core/./sys/etimer.h"
void etimer_restart(struct etimer *et);
# 155 "../../../core/./sys/etimer.h"
void etimer_adjust(struct etimer *et, int td);
# 164 "../../../core/./sys/etimer.h"
clock_time_t etimer_expiration_time(struct etimer *et);
# 174 "../../../core/./sys/etimer.h"
clock_time_t etimer_start_time(struct etimer *et);
# 184 "../../../core/./sys/etimer.h"
 int etimer_expired(struct etimer *et);
# 196 "../../../core/./sys/etimer.h"
void etimer_stop(struct etimer *et);
# 213 "../../../core/./sys/etimer.h"
void etimer_request_poll(void);
# 223 "../../../core/./sys/etimer.h"
int etimer_pending(void);
# 234 "../../../core/./sys/etimer.h"
clock_time_t etimer_next_expiration_time(void);




extern struct process etimer_process;
# 59 "../../../core/./sys/ctimer.h" 2

struct ctimer {
  struct ctimer *next;
  struct etimer etimer;
  struct process *p;
  void (*f)(void *);
  void *ptr;
};
# 83 "../../../core/./sys/ctimer.h"
void ctimer_reset(struct ctimer *c);
# 100 "../../../core/./sys/ctimer.h"
void ctimer_restart(struct ctimer *c);
# 114 "../../../core/./sys/ctimer.h"
void ctimer_set(struct ctimer *c, clock_time_t t,
  void (*f)(void *), void *ptr);
# 127 "../../../core/./sys/ctimer.h"
void ctimer_stop(struct ctimer *c);
# 137 "../../../core/./sys/ctimer.h"
int ctimer_expired(struct ctimer *c);







void ctimer_init(void);
# 46 "../../../core/./contiki.h" 2
# 1 "../../../core/./sys/etimer.h" 1
# 47 "../../../core/./contiki.h" 2
# 1 "../../../core/./sys/rtimer.h" 1
# 63 "../../../core/./sys/rtimer.h"
# 1 "../../../cpu/stm32w108/./rtimer-arch.h" 1
# 74 "../../../cpu/stm32w108/./rtimer-arch.h"
rtimer_clock_t rtimer_arch_now(void);


void rtimer_arch_disable_irq(void);
void rtimer_arch_enable_irq(void);
# 64 "../../../core/./sys/rtimer.h" 2
# 72 "../../../core/./sys/rtimer.h"
void rtimer_init(void);

struct rtimer;
typedef void (* rtimer_callback_t)(struct rtimer *t, void *ptr);
# 84 "../../../core/./sys/rtimer.h"
struct rtimer {
  rtimer_clock_t time;
  rtimer_callback_t func;
  void *ptr;
};

enum {
  RTIMER_OK,
  RTIMER_ERR_FULL,
  RTIMER_ERR_TIME,
  RTIMER_ERR_ALREADY_SCHEDULED,
};
# 111 "../../../core/./sys/rtimer.h"
int rtimer_set(struct rtimer *task, rtimer_clock_t time,
        rtimer_clock_t duration, rtimer_callback_t func, void *ptr);
# 121 "../../../core/./sys/rtimer.h"
void rtimer_run_next(void);
# 148 "../../../core/./sys/rtimer.h"
void rtimer_arch_init(void);
void rtimer_arch_schedule(rtimer_clock_t t);
# 48 "../../../core/./contiki.h" 2

# 1 "../../../core/./sys/pt.h" 1
# 50 "../../../core/./contiki.h" 2

# 1 "../../../core/./sys/procinit.h" 1
# 43 "../../../core/./sys/procinit.h"
void procinit_init(void);
# 52 "../../../core/./contiki.h" 2

# 1 "../../../core/./sys/loader.h" 1
# 54 "../../../core/./contiki.h" 2
# 1 "../../../core/./sys/clock.h" 1
# 55 "../../../core/./contiki.h" 2

# 1 "../../../core/./sys/energest.h" 1
# 44 "../../../core/./sys/energest.h"
# 1 "../../../core/./sys/rtimer.h" 1
# 45 "../../../core/./sys/energest.h" 2

typedef struct {

  unsigned long current;
} energest_t;

enum energest_type {
  ENERGEST_TYPE_CPU,
  ENERGEST_TYPE_LPM,
  ENERGEST_TYPE_IRQ,
  ENERGEST_TYPE_LED_GREEN,
  ENERGEST_TYPE_LED_YELLOW,
  ENERGEST_TYPE_LED_RED,
  ENERGEST_TYPE_TRANSMIT,
  ENERGEST_TYPE_LISTEN,

  ENERGEST_TYPE_FLASH_READ,
  ENERGEST_TYPE_FLASH_WRITE,

  ENERGEST_TYPE_SENSORS,

  ENERGEST_TYPE_SERIAL,

  ENERGEST_TYPE_MAX
};

void energest_init(void);
unsigned long energest_type_time(int type);



void energest_type_set(int type, unsigned long value);
void energest_flush(void);
# 57 "../../../core/./contiki.h" 2
# 71 "../../../core/./net/tcpip.h" 2

struct uip_conn;

struct tcpip_uipstate {
  struct process *p;
  void *state;
};







typedef struct tcpip_uipstate uip_udp_appstate_t;
typedef struct tcpip_uipstate uip_tcp_appstate_t;
typedef struct tcpip_uipstate uip_icmp6_appstate_t;
# 1 "../../../core/./net/uip.h" 1
# 89 "../../../core/./net/tcpip.h" 2
void tcpip_uipcall(void);
# 111 "../../../core/./net/tcpip.h"
 void tcp_attach(struct uip_conn *conn,
       void *appstate);
# 129 "../../../core/./net/tcpip.h"
 void tcp_listen(u16_t port);
# 143 "../../../core/./net/tcpip.h"
 void tcp_unlisten(u16_t port);
# 168 "../../../core/./net/tcpip.h"
 struct uip_conn *tcp_connect(uip_ipaddr_t *ripaddr, u16_t port,
      void *appstate);
# 182 "../../../core/./net/tcpip.h"
void tcpip_poll_tcp(struct uip_conn *conn);
# 191 "../../../core/./net/tcpip.h"
struct uip_udp_conn;
# 207 "../../../core/./net/tcpip.h"
void udp_attach(struct uip_udp_conn *conn,
  void *appstate);
# 229 "../../../core/./net/tcpip.h"
 struct uip_udp_conn *udp_new(const uip_ipaddr_t *ripaddr, u16_t port,
      void *appstate);
# 244 "../../../core/./net/tcpip.h"
struct uip_udp_conn *udp_broadcast_new(u16_t port, void *appstate);
# 275 "../../../core/./net/tcpip.h"
 void tcpip_poll_udp(struct uip_udp_conn *conn);
# 321 "../../../core/./net/tcpip.h"
 extern process_event_t tcpip_event;
# 337 "../../../core/./net/tcpip.h"
 void tcpip_input(void);






u8_t tcpip_output(uip_lladdr_t *);
void tcpip_set_outputfunc(u8_t (* f)(uip_lladdr_t *));
# 355 "../../../core/./net/tcpip.h"
void tcpip_ipv6_output(void);





extern unsigned char tcpip_do_forwarding;




extern unsigned char tcpip_is_forwarding;






extern struct process tcpip_process;
# 123 "../../../core/net/uip.h" 2
# 241 "../../../core/net/uip.h"
void uip_init(void);






void uip_setipid(u16_t id);
# 451 "../../../core/net/uip.h"
void uip_reass_over(void);
# 480 "../../../core/net/uip.h"
typedef union {
  uint32_t u32[((256) + 3) / 4];
  uint8_t u8[(256)];
} uip_buf_t;

 extern uip_buf_t uip_aligned_buf;
# 515 "../../../core/net/uip.h"
void uip_listen(u16_t port);
# 529 "../../../core/net/uip.h"
void uip_unlisten(u16_t port);
# 563 "../../../core/net/uip.h"
struct uip_conn *uip_connect(uip_ipaddr_t *ripaddr, u16_t port);
# 603 "../../../core/net/uip.h"
 void uip_send(const void *data, int len);
# 831 "../../../core/net/uip.h"
struct uip_udp_conn *uip_udp_new(const uip_ipaddr_t *ripaddr, u16_t rport);
# 1211 "../../../core/net/uip.h"
 u16_t uip_htons(u16_t val);






 u32_t uip_htonl(u32_t val);
# 1233 "../../../core/net/uip.h"
 extern void *uip_appdata;
# 1268 "../../../core/net/uip.h"
 extern u16_t uip_len;




extern u8_t uip_ext_len;
# 1291 "../../../core/net/uip.h"
struct uip_conn {
  uip_ipaddr_t ripaddr;

  u16_t lport;
  u16_t rport;


  u8_t rcv_nxt[4];

  u8_t snd_nxt[4];

  u16_t len;
  u16_t mss;

  u16_t initialmss;

  u8_t sa;

  u8_t sv;

  u8_t rto;
  u8_t tcpstateflags;
  u8_t timer;
  u8_t nrtx;



  uip_tcp_appstate_t appstate;
};
# 1329 "../../../core/net/uip.h"
 extern struct uip_conn *uip_conn;


 extern struct uip_conn uip_conns[(6)];
# 1343 "../../../core/net/uip.h"
extern u8_t uip_acc32[4];





struct uip_udp_conn {
  uip_ipaddr_t ripaddr;
  u16_t lport;
  u16_t rport;
  u8_t ttl;


  uip_udp_appstate_t appstate;
};




extern struct uip_udp_conn *uip_udp_conn;
extern struct uip_udp_conn uip_udp_conns[(3)];

struct uip_fallback_interface {
  void (*init)(void);
  void (*output)(void);
};
# 1394 "../../../core/net/uip.h"
struct uip_stats {
  struct {
    uip_stats_t recv;

    uip_stats_t sent;

    uip_stats_t forwarded;

    uip_stats_t drop;

    uip_stats_t vhlerr;

    uip_stats_t hblenerr;

    uip_stats_t lblenerr;

    uip_stats_t fragerr;

    uip_stats_t chkerr;

    uip_stats_t protoerr;

  } ip;
  struct {
    uip_stats_t recv;
    uip_stats_t sent;
    uip_stats_t drop;
    uip_stats_t typeerr;

    uip_stats_t chkerr;

  } icmp;

  struct {
    uip_stats_t recv;
    uip_stats_t sent;
    uip_stats_t drop;
    uip_stats_t chkerr;

    uip_stats_t ackerr;

    uip_stats_t rst;
    uip_stats_t rexmit;
    uip_stats_t syndrop;

    uip_stats_t synrst;

  } tcp;


  struct {
    uip_stats_t drop;
    uip_stats_t recv;
    uip_stats_t sent;
    uip_stats_t chkerr;

  } udp;


  struct {
    uip_stats_t drop;
    uip_stats_t recv;
    uip_stats_t sent;
  } nd6;

};
# 1476 "../../../core/net/uip.h"
 extern u8_t uip_flags;
# 1528 "../../../core/net/uip.h"
void uip_process(u8_t flag);
# 1567 "../../../core/net/uip.h"
struct uip_tcpip_hdr {


  u8_t vtc,
    tcflow;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
# 1590 "../../../core/net/uip.h"
  u16_t srcport,
    destport;
  u8_t seqno[4],
    ackno[4],
    tcpoffset,
    flags,
    wnd[2];
  u16_t tcpchksum;
  u8_t urgp[2];
  u8_t optdata[4];
};


struct uip_icmpip_hdr {


  u8_t vtc,
    tcf;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
# 1626 "../../../core/net/uip.h"
  u8_t type, icode;
  u16_t icmpchksum;




};



struct uip_udpip_hdr {


  u8_t vtc,
    tcf;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
# 1659 "../../../core/net/uip.h"
  u16_t srcport,
    destport;
  u16_t udplen;
  u16_t udpchksum;
};







struct uip_ip_hdr {


  u8_t vtc;
  u8_t tcflow;
  u16_t flow;
  u8_t len[2];
  u8_t proto, ttl;
  uip_ip6addr_t srcipaddr, destipaddr;
# 1692 "../../../core/net/uip.h"
};
# 1716 "../../../core/net/uip.h"
typedef struct uip_ext_hdr {
  u8_t next;
  u8_t len;
} uip_ext_hdr;


typedef struct uip_hbho_hdr {
  u8_t next;
  u8_t len;
} uip_hbho_hdr;


typedef struct uip_desto_hdr {
  u8_t next;
  u8_t len;
} uip_desto_hdr;
# 1743 "../../../core/net/uip.h"
typedef struct uip_routing_hdr {
  u8_t next;
  u8_t len;
  u8_t routing_type;
  u8_t seg_left;
} uip_routing_hdr;


typedef struct uip_frag_hdr {
  u8_t next;
  u8_t res;
  u16_t offsetresmore;
  u32_t id;
} uip_frag_hdr;





typedef struct uip_ext_hdr_opt {
  u8_t type;
  u8_t len;
} uip_ext_hdr_opt;


typedef struct uip_ext_hdr_opt_padn {
  u8_t opt_type;
  u8_t opt_len;
} uip_ext_hdr_opt_padn;


struct uip_tcp_hdr {
  u16_t srcport;
  u16_t destport;
  u8_t seqno[4];
  u8_t ackno[4];
  u8_t tcpoffset;
  u8_t flags;
  u8_t wnd[2];
  u16_t tcpchksum;
  u8_t urgp[2];
  u8_t optdata[4];
};


struct uip_icmp_hdr {
  u8_t type, icode;
  u16_t icmpchksum;



};



struct uip_udp_hdr {
  u16_t srcport;
  u16_t destport;
  u16_t udplen;
  u16_t udpchksum;
};
# 1908 "../../../core/net/uip.h"
 extern uip_ipaddr_t uip_hostaddr, uip_netmask, uip_draddr;

 extern const uip_ipaddr_t uip_broadcast_addr;
 extern const uip_ipaddr_t uip_all_zeroes_addr;




 extern uip_lladdr_t uip_lladdr;
# 2136 "../../../core/net/uip.h"
u16_t uip_chksum(u16_t *buf, u16_t len);
# 2147 "../../../core/net/uip.h"
u16_t uip_ipchksum(void);
# 2158 "../../../core/net/uip.h"
u16_t uip_tcpchksum(void);
# 2169 "../../../core/net/uip.h"
u16_t uip_udpchksum(void);






u16_t uip_icmp6chksum(void);
# 147 "sicslow_ethernet.c" 2
# 1 "../../../core/net/uip_arp.h" 1
# 58 "../../../core/net/uip_arp.h"
 extern struct uip_eth_addr uip_ethaddr;




struct uip_eth_hdr {
  struct uip_eth_addr dest;
  struct uip_eth_addr src;
  u16_t type;
};
# 76 "../../../core/net/uip_arp.h"
void uip_arp_init(void);
# 92 "../../../core/net/uip_arp.h"
void uip_arp_arpin(void);
# 104 "../../../core/net/uip_arp.h"
void uip_arp_out(void);



void uip_arp_timer(void);
# 148 "sicslow_ethernet.c" 2
# 1 "../../../core/./net/rime.h" 1
# 49 "../../../core/./net/rime.h"
# 1 "../../../core/./net/rime/announcement.h" 1
# 70 "../../../core/./net/rime/announcement.h"
# 1 "../../../core/./net/rime/rimeaddr.h" 1
# 66 "../../../core/./net/rime/rimeaddr.h"
typedef union {
  unsigned char u8[8];
} rimeaddr_t;
# 80 "../../../core/./net/rime/rimeaddr.h"
void rimeaddr_copy(rimeaddr_t *dest, const rimeaddr_t *from);
# 94 "../../../core/./net/rime/rimeaddr.h"
int rimeaddr_cmp(const rimeaddr_t *addr1, const rimeaddr_t *addr2);
# 104 "../../../core/./net/rime/rimeaddr.h"
void rimeaddr_set_node_addr(rimeaddr_t *addr);
# 115 "../../../core/./net/rime/rimeaddr.h"
extern rimeaddr_t rimeaddr_node_addr;
# 128 "../../../core/./net/rime/rimeaddr.h"
extern const rimeaddr_t rimeaddr_null;
# 71 "../../../core/./net/rime/announcement.h" 2

struct announcement;

typedef void (*announcement_callback_t)(struct announcement *a,
     const rimeaddr_t *from,
     uint16_t id, uint16_t val);







struct announcement {
  struct announcement *next;
  uint16_t id;
  uint16_t value;
  announcement_callback_t callback;
  uint8_t has_value;
};
# 114 "../../../core/./net/rime/announcement.h"
void announcement_register(struct announcement *a,
      uint16_t id,
      announcement_callback_t callback);
# 128 "../../../core/./net/rime/announcement.h"
void announcement_remove(struct announcement *a);
# 141 "../../../core/./net/rime/announcement.h"
void announcement_set_value(struct announcement *a, uint16_t value);
# 153 "../../../core/./net/rime/announcement.h"
void announcement_remove_value(struct announcement *a);
# 168 "../../../core/./net/rime/announcement.h"
void announcement_bump(struct announcement *a);
# 184 "../../../core/./net/rime/announcement.h"
void announcement_listen(int periods);
# 200 "../../../core/./net/rime/announcement.h"
void announcement_init(void);
# 215 "../../../core/./net/rime/announcement.h"
struct announcement *announcement_list(void);
# 228 "../../../core/./net/rime/announcement.h"
void announcement_heard(const rimeaddr_t *from, uint16_t id, uint16_t value);
# 240 "../../../core/./net/rime/announcement.h"
void announcement_register_listen_callback(void (*callback)(int time));

enum {
  ANNOUNCEMENT_NOBUMP,
  ANNOUNCEMENT_BUMP,
};

typedef void (* announcement_observer)(uint16_t id, uint8_t has_value,
                                       uint16_t newvalue, uint16_t oldvalue,
                                       uint8_t bump);
# 265 "../../../core/./net/rime/announcement.h"
void announcement_register_observer_callback(announcement_observer observer);
# 50 "../../../core/./net/rime.h" 2
# 1 "../../../core/./net/rime/collect.h" 1
# 64 "../../../core/./net/rime/collect.h"
# 1 "../../../core/./net/rime/runicast.h" 1
# 82 "../../../core/./net/rime/runicast.h"
# 1 "../../../core/./net/rime/stunicast.h" 1
# 76 "../../../core/./net/rime/stunicast.h"
# 1 "../../../core/./sys/ctimer.h" 1
# 77 "../../../core/./net/rime/stunicast.h" 2
# 1 "../../../core/./net/rime/unicast.h" 1
# 66 "../../../core/./net/rime/unicast.h"
# 1 "../../../core/./net/rime/broadcast.h" 1
# 69 "../../../core/./net/rime/broadcast.h"
# 1 "../../../core/./net/rime/abc.h" 1
# 61 "../../../core/./net/rime/abc.h"
# 1 "../../../core/./net/packetbuf.h" 1
# 86 "../../../core/./net/packetbuf.h"
void packetbuf_clear(void);
# 99 "../../../core/./net/packetbuf.h"
void packetbuf_clear_hdr(void);

void packetbuf_hdr_remove(int bytes);
# 121 "../../../core/./net/packetbuf.h"
void *packetbuf_dataptr(void);
# 133 "../../../core/./net/packetbuf.h"
void *packetbuf_hdrptr(void);
# 146 "../../../core/./net/packetbuf.h"
uint8_t packetbuf_hdrlen(void);
# 165 "../../../core/./net/packetbuf.h"
uint16_t packetbuf_datalen(void);






uint16_t packetbuf_totlen(void);
# 182 "../../../core/./net/packetbuf.h"
void packetbuf_set_datalen(uint16_t len);
# 195 "../../../core/./net/packetbuf.h"
void packetbuf_reference(void *ptr, uint16_t len);
# 207 "../../../core/./net/packetbuf.h"
int packetbuf_is_reference(void);
# 220 "../../../core/./net/packetbuf.h"
void *packetbuf_reference_ptr(void);
# 236 "../../../core/./net/packetbuf.h"
void packetbuf_compact(void);
# 251 "../../../core/./net/packetbuf.h"
int packetbuf_copyfrom(const void *from, uint16_t len);
# 271 "../../../core/./net/packetbuf.h"
int packetbuf_copyto(void *to);
# 287 "../../../core/./net/packetbuf.h"
int packetbuf_copyto_hdr(uint8_t *to);
# 301 "../../../core/./net/packetbuf.h"
int packetbuf_hdralloc(int size);
# 315 "../../../core/./net/packetbuf.h"
int packetbuf_hdrreduce(int size);



typedef uint16_t packetbuf_attr_t;

struct packetbuf_attr {

  packetbuf_attr_t val;
};
struct packetbuf_addr {

  rimeaddr_t addr;
};







enum {
  PACKETBUF_ATTR_NONE,


  PACKETBUF_ATTR_CHANNEL,
  PACKETBUF_ATTR_NETWORK_ID,
  PACKETBUF_ATTR_LINK_QUALITY,
  PACKETBUF_ATTR_RSSI,
  PACKETBUF_ATTR_TIMESTAMP,
  PACKETBUF_ATTR_RADIO_TXPOWER,
  PACKETBUF_ATTR_LISTEN_TIME,
  PACKETBUF_ATTR_TRANSMIT_TIME,
  PACKETBUF_ATTR_MAX_MAC_TRANSMISSIONS,
  PACKETBUF_ATTR_MAC_SEQNO,
  PACKETBUF_ATTR_MAC_ACK,


  PACKETBUF_ATTR_RELIABLE,
  PACKETBUF_ATTR_PACKET_ID,
  PACKETBUF_ATTR_PACKET_TYPE,
  PACKETBUF_ATTR_REXMIT,
  PACKETBUF_ATTR_MAX_REXMIT,
  PACKETBUF_ATTR_NUM_REXMIT,
  PACKETBUF_ATTR_PENDING,


  PACKETBUF_ATTR_HOPS,
  PACKETBUF_ATTR_TTL,
  PACKETBUF_ATTR_EPACKET_ID,
  PACKETBUF_ATTR_EPACKET_TYPE,
  PACKETBUF_ATTR_ERELIABLE,


  PACKETBUF_ADDR_SENDER,
  PACKETBUF_ADDR_RECEIVER,
  PACKETBUF_ADDR_ESENDER,
  PACKETBUF_ADDR_ERECEIVER,

  PACKETBUF_ATTR_MAX
};
# 420 "../../../core/./net/packetbuf.h"
int packetbuf_set_attr(uint8_t type, const packetbuf_attr_t val);
packetbuf_attr_t packetbuf_attr(uint8_t type);
int packetbuf_set_addr(uint8_t type, const rimeaddr_t *addr);
const rimeaddr_t *packetbuf_addr(uint8_t type);


void packetbuf_attr_clear(void);

void packetbuf_attr_copyto(struct packetbuf_attr *attrs,
          struct packetbuf_addr *addrs);
void packetbuf_attr_copyfrom(struct packetbuf_attr *attrs,
     struct packetbuf_addr *addrs);
# 440 "../../../core/./net/packetbuf.h"
struct packetbuf_attrlist {
  uint8_t type;
  uint8_t len;
};
# 62 "../../../core/./net/rime/abc.h" 2
# 1 "../../../core/./net/rime/channel.h" 1
# 44 "../../../core/./net/rime/channel.h"
struct channel;



# 1 "../../../core/./net/rime/chameleon.h" 1
# 44 "../../../core/./net/rime/chameleon.h"
# 1 "../../../core/./net/rime/channel.h" 1
# 45 "../../../core/./net/rime/chameleon.h" 2

struct chameleon_module {
  struct channel *(* input)(void);
  int (* output)(struct channel *);
  int (* hdrsize)(const struct packetbuf_attrlist *);
};

void chameleon_init(void);

int chameleon_hdrsize(const struct packetbuf_attrlist attrlist[]);
struct channel *chameleon_parse(void);
int chameleon_create(struct channel *c);
# 49 "../../../core/./net/rime/channel.h" 2

struct channel {
  struct channel *next;
  uint16_t channelno;
  const struct packetbuf_attrlist *attrlist;
  uint8_t hdrsize;
};

struct channel *channel_lookup(uint16_t channelno);

void channel_set_attributes(uint16_t channelno,
       const struct packetbuf_attrlist attrlist[]);
void channel_open(struct channel *c, uint16_t channelno);
void channel_close(struct channel *c);
void channel_init(void);
# 63 "../../../core/./net/rime/abc.h" 2

struct abc_conn;







struct abc_callbacks {

  void (* recv)(struct abc_conn *ptr);
  void (* sent)(struct abc_conn *ptr, int status, int num_tx);
};

struct abc_conn {
  struct channel channel;
  const struct abc_callbacks *u;
};
# 99 "../../../core/./net/rime/abc.h"
void abc_open(struct abc_conn *c, uint16_t channel,
        const struct abc_callbacks *u);
# 112 "../../../core/./net/rime/abc.h"
void abc_close(struct abc_conn *c);
# 127 "../../../core/./net/rime/abc.h"
int abc_send(struct abc_conn *c);
# 138 "../../../core/./net/rime/abc.h"
void abc_input(struct channel *channel);

void abc_sent(struct channel *channel, int status, int num_tx);
# 70 "../../../core/./net/rime/broadcast.h" 2


struct broadcast_conn;
# 81 "../../../core/./net/rime/broadcast.h"
struct broadcast_callbacks {

  void (* recv)(struct broadcast_conn *ptr, const rimeaddr_t *sender);
  void (* sent)(struct broadcast_conn *ptr, int status, int num_tx);
};

struct broadcast_conn {
  struct abc_conn c;
  const struct broadcast_callbacks *u;
};
# 108 "../../../core/./net/rime/broadcast.h"
void broadcast_open(struct broadcast_conn *c, uint16_t channel,
        const struct broadcast_callbacks *u);
# 121 "../../../core/./net/rime/broadcast.h"
void broadcast_close(struct broadcast_conn *c);
# 136 "../../../core/./net/rime/broadcast.h"
int broadcast_send(struct broadcast_conn *c);
# 67 "../../../core/./net/rime/unicast.h" 2

struct unicast_conn;




struct unicast_callbacks {
  void (* recv)(struct unicast_conn *c, const rimeaddr_t *from);
  void (* sent)(struct unicast_conn *ptr, int status, int num_tx);
};

struct unicast_conn {
  struct broadcast_conn c;
  const struct unicast_callbacks *u;
};

void unicast_open(struct unicast_conn *c, uint16_t channel,
       const struct unicast_callbacks *u);
void unicast_close(struct unicast_conn *c);

int unicast_send(struct unicast_conn *c, const rimeaddr_t *receiver);
# 78 "../../../core/./net/rime/stunicast.h" 2
# 1 "../../../core/./net/queuebuf.h" 1
# 71 "../../../core/./net/queuebuf.h"
struct queuebuf;

void queuebuf_init(void);





struct queuebuf *queuebuf_new_from_packetbuf(void);

void queuebuf_update_attr_from_packetbuf(struct queuebuf *b);

void queuebuf_to_packetbuf(struct queuebuf *b);
void queuebuf_free(struct queuebuf *b);

void *queuebuf_dataptr(struct queuebuf *b);
int queuebuf_datalen(struct queuebuf *b);

rimeaddr_t *queuebuf_addr(struct queuebuf *b, uint8_t type);
packetbuf_attr_t queuebuf_attr(struct queuebuf *b, uint8_t type);

void queuebuf_debug_print(void);
# 79 "../../../core/./net/rime/stunicast.h" 2

struct stunicast_conn;



struct stunicast_callbacks {
  void (* recv)(struct stunicast_conn *c, const rimeaddr_t *from);
  void (* sent)(struct stunicast_conn *c, int status, int num_tx);
};

struct stunicast_conn {
  struct unicast_conn c;
  struct ctimer t;
  struct queuebuf *buf;
  const struct stunicast_callbacks *u;
  rimeaddr_t receiver;
};

void stunicast_open(struct stunicast_conn *c, uint16_t channel,
        const struct stunicast_callbacks *u);
void stunicast_close(struct stunicast_conn *c);

int stunicast_send_stubborn(struct stunicast_conn *c, const rimeaddr_t *receiver,
        clock_time_t rxmittime);
void stunicast_cancel(struct stunicast_conn *c);

int stunicast_send(struct stunicast_conn *c, const rimeaddr_t *receiver);

void stunicast_set_timer(struct stunicast_conn *c, clock_time_t t);

rimeaddr_t *stunicast_receiver(struct stunicast_conn *c);
# 83 "../../../core/./net/rime/runicast.h" 2

struct runicast_conn;







struct runicast_callbacks {
  void (* recv)(struct runicast_conn *c, const rimeaddr_t *from, uint8_t seqno);
  void (* sent)(struct runicast_conn *c, const rimeaddr_t *to, uint8_t retransmissions);
  void (* timedout)(struct runicast_conn *c, const rimeaddr_t *to, uint8_t retransmissions);
};

struct runicast_conn {
  struct stunicast_conn c;
  const struct runicast_callbacks *u;
  uint8_t sndnxt;
  uint8_t is_tx;
  uint8_t rxmit;
  uint8_t max_rxmit;
};

void runicast_open(struct runicast_conn *c, uint16_t channel,
        const struct runicast_callbacks *u);
void runicast_close(struct runicast_conn *c);

int runicast_send(struct runicast_conn *c, const rimeaddr_t *receiver,
    uint8_t max_retransmissions);

uint8_t runicast_is_transmitting(struct runicast_conn *c);
# 65 "../../../core/./net/rime/collect.h" 2
# 1 "../../../core/./net/rime/neighbor-discovery.h" 1
# 66 "../../../core/./net/rime/neighbor-discovery.h"
struct neighbor_discovery_conn;

struct neighbor_discovery_callbacks {
  void (* recv)(struct neighbor_discovery_conn *c,
  const rimeaddr_t *from, uint16_t val);
  void (* sent)(struct neighbor_discovery_conn *c);
};

struct neighbor_discovery_conn {
  struct broadcast_conn c;
  const struct neighbor_discovery_callbacks *u;
  struct ctimer send_timer, interval_timer;
  clock_time_t initial_interval, min_interval, max_interval;
  clock_time_t current_interval;
  uint16_t val;
};

void neighbor_discovery_open(struct neighbor_discovery_conn *c,
        uint16_t channel,
        clock_time_t initial,
        clock_time_t min,
        clock_time_t max,
        const struct neighbor_discovery_callbacks *u);
void neighbor_discovery_close(struct neighbor_discovery_conn *c);
void neighbor_discovery_set_val(struct neighbor_discovery_conn *c, uint16_t val);

void neighbor_discovery_start(struct neighbor_discovery_conn *c, uint16_t val);
# 66 "../../../core/./net/rime/collect.h" 2
# 1 "../../../core/./net/rime/collect-neighbor.h" 1
# 56 "../../../core/./net/rime/collect-neighbor.h"
# 1 "../../../core/./net/rime/collect-link-estimate.h" 1
# 62 "../../../core/./net/rime/collect-link-estimate.h"
struct collect_link_estimate {
  uint32_t etx_accumulator;
  uint8_t num_estimates;
};







void collect_link_estimate_new(struct collect_link_estimate *le);
# 85 "../../../core/./net/rime/collect-link-estimate.h"
void collect_link_estimate_update_tx(struct collect_link_estimate *le,
                                     uint8_t num_tx);
# 98 "../../../core/./net/rime/collect-link-estimate.h"
void collect_link_estimate_update_tx_fail(struct collect_link_estimate *le,
                                          uint8_t num_tx);
# 110 "../../../core/./net/rime/collect-link-estimate.h"
void collect_link_estimate_update_rx(struct collect_link_estimate *le);
# 119 "../../../core/./net/rime/collect-link-estimate.h"
uint16_t collect_link_estimate(struct collect_link_estimate *le);

int collect_link_estimate_num_estimates(struct collect_link_estimate *le);
# 57 "../../../core/./net/rime/collect-neighbor.h" 2
# 1 "../../../core/./lib/list.h" 1
# 136 "../../../core/./lib/list.h"
typedef void ** list_t;

void list_init(list_t list);
void * list_head(list_t list);
void * list_tail(list_t list);
void * list_pop (list_t list);
void list_push(list_t list, void *item);

void * list_chop(list_t list);

void list_add(list_t list, void *item);
void list_remove(list_t list, void *item);

int list_length(list_t list);

void list_copy(list_t dest, list_t src);

void list_insert(list_t list, void *previtem, void *newitem);

void * list_item_next(void *item);
# 58 "../../../core/./net/rime/collect-neighbor.h" 2

struct collect_neighbor_list {
  void *list_list; list_t list;
  struct ctimer periodic;
};

struct collect_neighbor {
  struct collect_neighbor *next;
  rimeaddr_t addr;
  uint16_t rtmetric;
  uint16_t age;
  uint16_t le_age;
  struct collect_link_estimate le;
  struct timer congested_timer;
};

void collect_neighbor_init(void);

list_t collect_neighbor_list(struct collect_neighbor_list *neighbor_list);

void collect_neighbor_list_new(struct collect_neighbor_list *neighbor_list);

int collect_neighbor_list_add(struct collect_neighbor_list *neighbor_list,
                              const rimeaddr_t *addr, uint16_t rtmetric);
void collect_neighbor_list_remove(struct collect_neighbor_list *neighbor_list,
                                  const rimeaddr_t *addr);
struct collect_neighbor *collect_neighbor_list_find(struct collect_neighbor_list *neighbor_list,
                                               const rimeaddr_t *addr);
struct collect_neighbor *collect_neighbor_list_best(struct collect_neighbor_list *neighbor_list);
int collect_neighbor_list_num(struct collect_neighbor_list *neighbor_list);
struct collect_neighbor *collect_neighbor_list_get(struct collect_neighbor_list *neighbor_list, int num);
void collect_neighbor_list_purge(struct collect_neighbor_list *neighbor_list);

void collect_neighbor_update_rtmetric(struct collect_neighbor *n,
                                      uint16_t rtmetric);
void collect_neighbor_tx(struct collect_neighbor *n, uint16_t num_tx);
void collect_neighbor_rx(struct collect_neighbor *n);
void collect_neighbor_tx_fail(struct collect_neighbor *n, uint16_t num_tx);
void collect_neighbor_set_congested(struct collect_neighbor *n);
int collect_neighbor_is_congested(struct collect_neighbor *n);

uint16_t collect_neighbor_link_estimate(struct collect_neighbor *n);
uint16_t collect_neighbor_rtmetric_link_estimate(struct collect_neighbor *n);
uint16_t collect_neighbor_rtmetric(struct collect_neighbor *n);
# 67 "../../../core/./net/rime/collect.h" 2
# 1 "../../../core/./net/packetqueue.h" 1
# 58 "../../../core/./net/packetqueue.h"
# 1 "../../../core/./lib/memb.h" 1
# 97 "../../../core/./lib/memb.h"
struct memb {
  unsigned short size;
  unsigned short num;
  char *count;
  void *mem;
};






void memb_init(struct memb *m);






void *memb_alloc(struct memb *m);
# 130 "../../../core/./lib/memb.h"
char memb_free(struct memb *m, void *ptr);

int memb_inmemb(struct memb *m, void *ptr);
# 59 "../../../core/./net/packetqueue.h" 2
# 71 "../../../core/./net/packetqueue.h"
struct packetqueue {
  list_t *list;
  struct memb *memb;
};
# 87 "../../../core/./net/packetqueue.h"
struct packetqueue_item {
  struct packetqueue_item *next;
  struct queuebuf *buf;
  struct packetqueue *queue;
  struct ctimer lifetimer;
  void *ptr;
};
# 122 "../../../core/./net/packetqueue.h"
void packetqueue_init(struct packetqueue *q);
# 153 "../../../core/./net/packetqueue.h"
int packetqueue_enqueue_packetbuf(struct packetqueue *q, clock_time_t lifetime,
      void *ptr);
# 167 "../../../core/./net/packetqueue.h"
struct packetqueue_item *packetqueue_first(struct packetqueue *q);
# 180 "../../../core/./net/packetqueue.h"
void packetqueue_dequeue(struct packetqueue *q);
# 191 "../../../core/./net/packetqueue.h"
int packetqueue_len(struct packetqueue *q);
# 207 "../../../core/./net/packetqueue.h"
struct queuebuf *packetqueue_queuebuf(struct packetqueue_item *i);






void *packetqueue_ptr(struct packetqueue_item *i);
# 68 "../../../core/./net/rime/collect.h" 2
# 82 "../../../core/./net/rime/collect.h"
struct collect_callbacks {
  void (* recv)(const rimeaddr_t *originator, uint8_t seqno,
  uint8_t hops);
};
# 96 "../../../core/./net/rime/collect.h"
struct collect_conn {
  struct unicast_conn unicast_conn;



  struct announcement announcement;
  struct ctimer transmit_after_scan_timer;

  const struct collect_callbacks *cb;
  struct ctimer retransmission_timer;
  void *send_queue_list_list; list_t send_queue_list;
  struct packetqueue send_queue;
  struct collect_neighbor_list neighbor_list;

  struct ctimer keepalive_timer;
  clock_time_t keepalive_period;

  struct ctimer proactive_probing_timer;

  rimeaddr_t parent, current_parent;
  uint16_t rtmetric;
  uint8_t seqno;
  uint8_t sending, transmissions, max_rexmits;
  uint8_t eseqno;
  uint8_t is_router;

  clock_time_t send_time;
};

enum {
  COLLECT_NO_ROUTER,
  COLLECT_ROUTER,
};

void collect_open(struct collect_conn *c, uint16_t channels,
                  uint8_t is_router,
                  const struct collect_callbacks *callbacks);
void collect_close(struct collect_conn *c);

int collect_send(struct collect_conn *c, int rexmits);

void collect_set_sink(struct collect_conn *c, int should_be_sink);

int collect_depth(struct collect_conn *c);
const rimeaddr_t *collect_parent(struct collect_conn *c);

void collect_set_keepalive(struct collect_conn *c, clock_time_t period);

void collect_print_stats(void);
# 51 "../../../core/./net/rime.h" 2
# 1 "../../../core/./net/rime/ipolite.h" 1
# 102 "../../../core/./net/rime/ipolite.h"
struct ipolite_conn;
# 114 "../../../core/./net/rime/ipolite.h"
struct ipolite_callbacks {



  void (* recv)(struct ipolite_conn *c, const rimeaddr_t *from);




  void (* sent)(struct ipolite_conn *c);





  void (* dropped)(struct ipolite_conn *c);
};





struct ipolite_conn {
  struct broadcast_conn c;
  const struct ipolite_callbacks *cb;
  struct ctimer t;
  struct queuebuf *q;
  uint8_t hdrsize;
  uint8_t maxdups;
  uint8_t dups;
};
# 159 "../../../core/./net/rime/ipolite.h"
void ipolite_open(struct ipolite_conn *c, uint16_t channel, uint8_t maxdups,
    const struct ipolite_callbacks *cb);
# 169 "../../../core/./net/rime/ipolite.h"
void ipolite_close(struct ipolite_conn *c);
# 183 "../../../core/./net/rime/ipolite.h"
int ipolite_send(struct ipolite_conn *c, clock_time_t interval,
    uint8_t hdrsize);
# 193 "../../../core/./net/rime/ipolite.h"
void ipolite_cancel(struct ipolite_conn *c);
# 52 "../../../core/./net/rime.h" 2
# 1 "../../../core/./net/rime/mesh.h" 1
# 66 "../../../core/./net/rime/mesh.h"
# 1 "../../../core/./net/rime/multihop.h" 1
# 77 "../../../core/./net/rime/multihop.h"
struct multihop_conn;
# 86 "../../../core/./net/rime/multihop.h"
struct multihop_callbacks {
  void (* recv)(struct multihop_conn *ptr,
  const rimeaddr_t *sender,
  const rimeaddr_t *prevhop,
  uint8_t hops);
  rimeaddr_t *(* forward)(struct multihop_conn *ptr,
     const rimeaddr_t *originator,
     const rimeaddr_t *dest,
     const rimeaddr_t *prevhop,
     uint8_t hops);
};

struct multihop_conn {
  struct unicast_conn c;
  const struct multihop_callbacks *cb;
};

void multihop_open(struct multihop_conn *c, uint16_t channel,
      const struct multihop_callbacks *u);
void multihop_close(struct multihop_conn *c);
int multihop_send(struct multihop_conn *c, const rimeaddr_t *to);
void multihop_resend(struct multihop_conn *c, const rimeaddr_t *nexthop);
# 67 "../../../core/./net/rime/mesh.h" 2
# 1 "../../../core/./net/rime/route-discovery.h" 1
# 62 "../../../core/./net/rime/route-discovery.h"
# 1 "../../../core/./net/rime/netflood.h" 1
# 81 "../../../core/./net/rime/netflood.h"
struct netflood_conn;






struct netflood_callbacks {
  int (* recv)(struct netflood_conn *c, const rimeaddr_t *from,
        const rimeaddr_t *originator, uint8_t seqno, uint8_t hops);
  void (* sent)(struct netflood_conn *c);
  void (* dropped)(struct netflood_conn *c);
};

struct netflood_conn {
  struct ipolite_conn c;
  const struct netflood_callbacks *u;
  clock_time_t queue_time;
  rimeaddr_t last_originator;
  uint8_t last_originator_seqno;
};

void netflood_open(struct netflood_conn *c, clock_time_t queue_time,
      uint16_t channel, const struct netflood_callbacks *u);
void netflood_close(struct netflood_conn *c);

int netflood_send(struct netflood_conn *c, uint8_t seqno);
# 63 "../../../core/./net/rime/route-discovery.h" 2


struct route_discovery_conn;

struct route_discovery_callbacks {
  void (* new_route)(struct route_discovery_conn *c, const rimeaddr_t *to);
  void (* timedout)(struct route_discovery_conn *c);
};



struct route_discovery_conn {
  struct netflood_conn rreqconn;
  struct unicast_conn rrepconn;
  struct ctimer t;
  rimeaddr_t last_rreq_originator;
  uint16_t last_rreq_id;
  uint16_t rreq_id;
  const struct route_discovery_callbacks *cb;
};

void route_discovery_open(struct route_discovery_conn *c, clock_time_t time,
     uint16_t channels,
     const struct route_discovery_callbacks *callbacks);
int route_discovery_discover(struct route_discovery_conn *c, const rimeaddr_t *dest,
        clock_time_t timeout);

void route_discovery_close(struct route_discovery_conn *c);
# 68 "../../../core/./net/rime/mesh.h" 2

struct mesh_conn;




struct mesh_callbacks {

  void (* recv)(struct mesh_conn *c, const rimeaddr_t *from, uint8_t hops);

  void (* sent)(struct mesh_conn *c);

  void (* timedout)(struct mesh_conn *c);
};

struct mesh_conn {
  struct multihop_conn multihop;
  struct route_discovery_conn route_discovery_conn;
  struct queuebuf *queued_data;
  rimeaddr_t queued_data_dest;
  const struct mesh_callbacks *cb;
};
# 107 "../../../core/./net/rime/mesh.h"
void mesh_open(struct mesh_conn *c, uint16_t channels,
        const struct mesh_callbacks *callbacks);
# 120 "../../../core/./net/rime/mesh.h"
void mesh_close(struct mesh_conn *c);
# 135 "../../../core/./net/rime/mesh.h"
int mesh_send(struct mesh_conn *c, const rimeaddr_t *dest);
# 53 "../../../core/./net/rime.h" 2



# 1 "../../../core/./net/rime/polite-announcement.h" 1
# 63 "../../../core/./net/rime/polite-announcement.h"
void polite_announcement_init(uint16_t channel,
         clock_time_t min,
         clock_time_t max);
# 57 "../../../core/./net/rime.h" 2
# 1 "../../../core/./net/rime/polite.h" 1
# 101 "../../../core/./net/rime/polite.h"
struct polite_conn;
# 113 "../../../core/./net/rime/polite.h"
struct polite_callbacks {



  void (* recv)(struct polite_conn *c);




  void (* sent)(struct polite_conn *c);





  void (* dropped)(struct polite_conn *c);
};





struct polite_conn {
  struct abc_conn c;
  const struct polite_callbacks *cb;
  struct ctimer t;
  struct queuebuf *q;
  uint8_t hdrsize;
};
# 154 "../../../core/./net/rime/polite.h"
void polite_open(struct polite_conn *c, uint16_t channel,
   const struct polite_callbacks *cb);
# 164 "../../../core/./net/rime/polite.h"
void polite_close(struct polite_conn *c);
# 179 "../../../core/./net/rime/polite.h"
int polite_send(struct polite_conn *c, clock_time_t interval, uint8_t hdrsize);
# 188 "../../../core/./net/rime/polite.h"
void polite_cancel(struct polite_conn *c);
# 58 "../../../core/./net/rime.h" 2



# 1 "../../../core/./net/rime/rimestats.h" 1
# 44 "../../../core/./net/rime/rimestats.h"
struct rimestats {
  unsigned long tx, rx;

  unsigned long reliabletx, reliablerx,
    rexmit, acktx, noacktx, ackrx, timedout, badackrx;


  unsigned long toolong, tooshort, badsynch, badcrc;

  unsigned long contentiondrop,
    sendingdrop;

  unsigned long lltx, llrx;
};

extern struct rimestats rimestats;
# 62 "../../../core/./net/rime.h" 2
# 1 "../../../core/./net/rime/rmh.h" 1
# 72 "../../../core/./net/rime/rmh.h"
struct rmh_conn;







struct rmh_callbacks {
  void (* recv)(struct rmh_conn *ptr, rimeaddr_t *sender, uint8_t hops);
  rimeaddr_t *(* forward)(struct rmh_conn *ptr,
     const rimeaddr_t *originator,
     const rimeaddr_t *dest,
     const rimeaddr_t *prevhop,
     uint8_t hops);
};

struct rmh_conn {
  struct runicast_conn c;
  const struct rmh_callbacks *cb;
  uint8_t num_rexmit;
};

void rmh_open(struct rmh_conn *c, uint16_t channel,
       const struct rmh_callbacks *u);
void rmh_close(struct rmh_conn *c);
int rmh_send(struct rmh_conn *c, rimeaddr_t *to, uint8_t num_rexmit,
      uint8_t max_hops);
# 63 "../../../core/./net/rime.h" 2

# 1 "../../../core/./net/rime/route.h" 1
# 57 "../../../core/./net/rime/route.h"
struct route_entry {
  struct route_entry *next;
  rimeaddr_t dest;
  rimeaddr_t nexthop;
  uint8_t seqno;
  uint8_t cost;
  uint8_t time;

  uint8_t decay;
  uint8_t time_last_decay;
};

void route_init(void);
int route_add(const rimeaddr_t *dest, const rimeaddr_t *nexthop,
       uint8_t cost, uint8_t seqno);
struct route_entry *route_lookup(const rimeaddr_t *dest);
void route_refresh(struct route_entry *e);
void route_decay(struct route_entry *e);
void route_remove(struct route_entry *e);
void route_flush_all(void);
void route_set_lifetime(int seconds);

int route_num(void);
struct route_entry *route_get(int num);
# 65 "../../../core/./net/rime.h" 2
# 1 "../../../core/./net/rime/rucb.h" 1
# 46 "../../../core/./net/rime/rucb.h"
struct rucb_conn;

enum {
  RUCB_FLAG_NONE,
  RUCB_FLAG_NEWFILE,
  RUCB_FLAG_LASTCHUNK,
};

struct rucb_callbacks {
  void (* write_chunk)(struct rucb_conn *c, int offset, int flag,
         char *data, int len);
  int (* read_chunk)(struct rucb_conn *c, int offset, char *to,
       int maxsize);
  void (* timedout)(struct rucb_conn *c);
};



struct rucb_conn {
  struct runicast_conn c;
  const struct rucb_callbacks *u;
  rimeaddr_t receiver, sender;
  uint16_t chunk;
  uint8_t last_seqno;
};

void rucb_open(struct rucb_conn *c, uint16_t channel,
       const struct rucb_callbacks *u);
void rucb_close(struct rucb_conn *c);

int rucb_send(struct rucb_conn *c, const rimeaddr_t *receiver);
# 66 "../../../core/./net/rime.h" 2

# 1 "../../../core/./net/rime/timesynch.h" 1
# 71 "../../../core/./net/rime/timesynch.h"
# 1 "../../../core/./net/mac/mac.h" 1
# 45 "../../../core/./net/mac/mac.h"
# 1 "../../../core/./dev/radio.h" 1
# 61 "../../../core/./dev/radio.h"
struct radio_driver {

  int (* init)(void);


  int (* prepare)(const void *payload, unsigned short payload_len);


  int (* transmit)(unsigned short transmit_len);


  int (* send)(const void *payload, unsigned short payload_len);


  int (* read)(void *buf, unsigned short buf_len);



  int (* channel_clear)(void);


  int (* receiving_packet)(void);


  int (* pending_packet)(void);


  int (* on)(void);


  int (* off)(void);
};


enum {
  RADIO_TX_OK,
  RADIO_TX_ERR,
  RADIO_TX_COLLISION,
  RADIO_TX_NOACK,
};
# 46 "../../../core/./net/mac/mac.h" 2


typedef void (* mac_callback_t)(void *ptr, int status, int transmissions);

void mac_call_sent_callback(mac_callback_t sent, void *ptr, int status, int num_tx);




struct mac_driver {
  char *name;


  void (* init)(void);


  void (* send)(mac_callback_t sent_callback, void *ptr);


  void (* input)(void);


  int (* on)(void);


  int (* off)(int keep_radio_on);


  unsigned short (* channel_check_interval)(void);
};


enum {

  MAC_TX_OK,



  MAC_TX_COLLISION,


  MAC_TX_NOACK,


  MAC_TX_DEFERRED,



  MAC_TX_ERR,




  MAC_TX_ERR_FATAL,
};
# 72 "../../../core/./net/rime/timesynch.h" 2
# 81 "../../../core/./net/rime/timesynch.h"
void timesynch_init(void);
# 91 "../../../core/./net/rime/timesynch.h"
rtimer_clock_t timesynch_time(void);
# 104 "../../../core/./net/rime/timesynch.h"
rtimer_clock_t timesynch_time_to_rtimer(rtimer_clock_t synched_time);
# 114 "../../../core/./net/rime/timesynch.h"
rtimer_clock_t timesynch_rtimer_to_time(rtimer_clock_t rtimer_time);
# 125 "../../../core/./net/rime/timesynch.h"
rtimer_clock_t timesynch_offset(void);
# 140 "../../../core/./net/rime/timesynch.h"
int timesynch_authority_level(void);





void timesynch_set_authority_level(int level);
# 68 "../../../core/./net/rime.h" 2
# 1 "../../../core/./net/rime/trickle.h" 1
# 69 "../../../core/./net/rime/trickle.h"
struct trickle_conn;

struct trickle_callbacks {
  void (* recv)(struct trickle_conn *c);
};

struct trickle_conn {
  struct broadcast_conn c;
  const struct trickle_callbacks *cb;
  struct ctimer t, interval_timer, first_transmission_timer;
  struct pt pt;
  struct queuebuf *q;
  clock_time_t interval;
  uint8_t seqno;
  uint8_t interval_scaling;
  uint8_t duplicates;
};

void trickle_open(struct trickle_conn *c, clock_time_t interval,
    uint16_t channel, const struct trickle_callbacks *cb);
void trickle_close(struct trickle_conn *c);

void trickle_send(struct trickle_conn *c);
# 69 "../../../core/./net/rime.h" 2
# 77 "../../../core/./net/rime.h"
int rime_init(void);
# 88 "../../../core/./net/rime.h"
void rime_input(void);

int rime_output(struct channel *c);

extern const struct mac_driver *rime_mac;

struct rime_sniffer {
  struct rime_sniffer *next;
  void (* input_callback)(void);
  void (* output_callback)(int mac_status);
};




void rime_sniffer_add(struct rime_sniffer *s);
void rime_sniffer_remove(struct rime_sniffer *s);

extern const struct network_driver rime_driver;


enum {
  RIME_OK,
  RIME_ERR,
  RIME_ERR_CONTENTION,
  RIME_ERR_NOACK,
};
# 149 "sicslow_ethernet.c" 2
# 1 "../../../core/./net/sicslowpan.h" 1
# 221 "../../../core/./net/sicslowpan.h"
struct sicslowpan_addr_context {
  u8_t used;
  u8_t number;
  u8_t prefix[8];
};
# 308 "../../../core/./net/sicslowpan.h"
struct sicslowpan_nh_compressor {
  int (* is_compressable)(uint8_t next_header);



  int (* compress)(uint8_t *compressed, uint8_t *uncompressed_len);



  int (* uncompress)(uint8_t *compressed, uint8_t *lowpanbuf, uint8_t *uncompressed_len);

};


extern const struct network_driver sicslowpan_driver;

extern const struct mac_driver *sicslowpan_mac;
# 150 "sicslow_ethernet.c" 2
# 1 "sicslow_ethernet.h" 1
# 51 "sicslow_ethernet.h"
typedef enum {
  ll_802154_type,
  ll_8023_type
} lltype_t;


typedef struct {
 uint8_t sicslowpan :1;
 uint8_t sendToRf :1;
 uint8_t translate :1;
 uint8_t raw :1;
} usbstick_mode_t;




extern usbstick_mode_t usbstick_mode;


int8_t mac_translateIcmpLinkLayer(lltype_t target);
int8_t mac_translateIPLinkLayer(lltype_t target);
void mac_LowpanToEthernet(void);
void mac_ethernetToLowpan(uint8_t * ethHeader);
void mac_ethernetSetup(void);
# 151 "sicslow_ethernet.c" 2
# 1 "../../../cpu/stm32w108/hal/micro/micro-common.h" 1
# 24 "../../../cpu/stm32w108/hal/micro/micro-common.h"
  typedef int8u StStatus;





void halInit(void);



void halReboot(void);



void halPowerUp(void);



void halPowerDown(void);
# 52 "../../../cpu/stm32w108/hal/micro/micro-common.h"
void halInternalEnableWatchDog(void);
# 61 "../../../cpu/stm32w108/hal/micro/micro-common.h"
void halInternalDisableWatchDog(int8u magicKey);





boolean halInternalWatchDogEnabled( void );
# 93 "../../../cpu/stm32w108/hal/micro/micro-common.h"
typedef int8u SleepModes;
enum

{
  SLEEPMODE_RUNNING = 0,
  SLEEPMODE_IDLE = 1,
  SLEEPMODE_WAKETIMER = 2,
  SLEEPMODE_MAINTAINTIMER = 3,
  SLEEPMODE_NOTIMER = 4,
};
# 119 "../../../cpu/stm32w108/hal/micro/micro-common.h"
void halCommonDelayMicroseconds(int16u us);
# 135 "../../../cpu/stm32w108/hal/micro/micro-common.h"
StStatus halBootloaderStart(int8u mode, int8u channel, int16u panId);





# 1 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h" 1
# 63 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halInternalResetWatchDog( void );
# 74 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halGpioConfig(int32u io, int32u config);
# 84 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halGpioSet(int32u io, boolean value);





void halInternalCalibrateSlowRc( void );




void halInternalCalibrateFastRc(void);
# 105 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halInternalSetRegTrim(boolean boostMode);
# 114 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
int16u stMeasureVddSlow(void);
# 124 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
int16u stMeasureVddFast(void);






void halCommonCalibratePads(void);







void halCommonCheckXtalBiasTrim(void);
# 148 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halInternalSwitchToXtal(void);






void halInternalSearchForBiasTrim(void);
# 167 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halCommonDelayMilliseconds(int16u ms);
# 186 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halSleepWithOptions(SleepModes sleepMode, int32u gpioWakeBitMask);
# 221 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
StStatus halSleepForQsWithOptions(int32u *duration, int32u gpioWakeBitMask);




void halInternalIdleSleep(void);
# 236 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halInternalSleep(SleepModes sleepMode);
# 265 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
int32u halGetWakeInfo(void);
# 276 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
void halCommonSeedRandom(int32u seed);
# 286 "../../../cpu/stm32w108/hal/micro/cortexm3/micro-common.h"
int16u halCommonGetRandom(void);
# 142 "../../../cpu/stm32w108/hal/micro/micro-common.h" 2
# 152 "sicslow_ethernet.c" 2
# 1 "../../../cpu/stm32w108/simplemac/include/phy-library.h" 1
# 55 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
enum {
  ST_RADIO_POWER_MODE_RX_ON,
  ST_RADIO_POWER_MODE_OFF
};
typedef u8 RadioPowerMode;
# 73 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
typedef struct {
  boolean waitForAck;
  boolean checkCca;
  u8 ccaAttemptMax;
  u8 backoffExponentMin;
  u8 backoffExponentMax;
  boolean appendCrc;
} RadioTransmitConfig;
# 173 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
StStatus ST_RadioInit(RadioPowerMode initialRadioPowerMode);




void ST_RadioWake(void);
# 188 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioSleep(void);
# 220 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
StStatus ST_RadioSetChannel(u8 channel);






u8 ST_RadioGetChannel(void);
# 248 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
StStatus ST_RadioSetChannelAndForceCalibration(u8 channel);
# 261 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
boolean ST_RadioCheckRadio(void);






void ST_RadioCalibrateCurrentChannel(void);
# 302 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
StStatus ST_RadioTransmit(u8* packet);
# 329 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
extern void ST_RadioTransmitCompleteIsrCallback(StStatus status,
                                                  u32 sfdSentTime,
                                                  boolean framePending);







void ST_RadioSetEdCcaThreshold(s8 threshold);







s8 ST_RadioGetEdCcaThreshold(void);







void ST_RadioEnableSfdSentNotification(boolean enable);







boolean ST_RadioSfdSentNotificationEnabled(void);
# 379 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioSfdSentIsrCallback(u32 sfdSentTime);
# 396 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
StStatus ST_RadioSetPower(s8 power);






s8 ST_RadioGetPower(void);
# 434 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
extern void ST_RadioReceiveIsrCallback(u8 *packet,
                                         boolean ackFramePendingSet,
                                         u32 time,
                                         u16 errors,
                                         s8 rssi);
# 448 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioEnableAddressFiltering(boolean enable);






boolean ST_RadioAddressFilteringEnabled(void);
# 469 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioEnableAutoAck(boolean enable);






boolean ST_RadioAutoAckEnabled(void);
# 485 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioSetNodeId(u16 nodeId);







u16 ST_RadioGetNodeId(void);







void ST_RadioSetPanId(u16 panId);







u16 ST_RadioGetPanId(void);
# 520 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
u8* ST_RadioGetEui64(void);
# 533 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
boolean ST_RadioDataPendingLongIdIsrCallback(u8* longId);
# 546 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
boolean ST_RadioDataPendingShortIdIsrCallback(u16 shortId);
# 562 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioSetCoordinator(boolean coordinator);






boolean ST_RadioDeviceIsCoordinator(void);







void ST_RadioEnableOverflowNotification(boolean enable);







boolean ST_RadioOverflowNotificationEnabled(void);






void ST_RadioOverflowIsrCallback(void);
# 606 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioEnableReceiveCrc(boolean enable);







boolean ST_RadioReceiveCrcEnabled(void);
# 636 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
u32 ST_RadioGetMacTimer(void);
# 646 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioEnableMacTimerCompare(boolean enable);
# 655 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
boolean ST_RadioMacTimerCompareEnabled(void);






void ST_RadioSetMacTimerCompare(u32 value);






u32 ST_RadioGetMacTimerCompare(void);





extern void ST_RadioMacTimerCompareIsrCallback(void);
# 693 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_AesSetKey(u8* key);






void ST_AesGetKey(u8* key);
# 711 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_AesEncrypt(u8* block);
# 734 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioStartTransmitTone(void);





void ST_RadioStopTransmitTone(void);
# 751 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioStartTransmitStream(void);





void ST_RadioStopTransmitStream(void);







s8 ST_RadioEnergyDetection(void);
# 774 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioGetRandomNumbers(u16 *rn, u8 count);






boolean ST_RadioChannelIsClear(void);
# 792 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
void ST_RadioEnablePacketTrace(boolean enable);






boolean ST_RadioPacketTraceEnabled(void);
# 819 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
StStatus ST_RadioSetPowerMode(u16 txPowerMode);
# 828 "../../../cpu/stm32w108/simplemac/include/phy-library.h"
u16 ST_RadioGetPowerMode(void);
# 153 "sicslow_ethernet.c" 2


# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 1 3
# 34 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 1 3 4
# 35 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 2 3
# 46 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 1 3
# 69 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 1 3 4
# 149 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 70 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 2 3
# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/types.h" 1 3
# 19 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/machine/types.h" 3
typedef long int __off_t;
typedef int __pid_t;

__extension__ typedef long long int __loff_t;
# 71 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 2 3
# 92 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 3
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;



typedef unsigned short ushort;
typedef unsigned int uint;



typedef unsigned long clock_t;




typedef long time_t;




struct timespec {
  time_t tv_sec;
  long tv_nsec;
};

struct itimerspec {
  struct timespec it_interval;
  struct timespec it_value;
};


typedef long daddr_t;
typedef char * caddr_t;






typedef unsigned short ino_t;
# 162 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 3
typedef _off_t off_t;
typedef __dev_t dev_t;
typedef __uid_t uid_t;
typedef __gid_t gid_t;





typedef int pid_t;



typedef long key_t;

typedef _ssize_t ssize_t;
# 191 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 3
typedef unsigned int mode_t __attribute__ ((__mode__ (__SI__)));




typedef unsigned short nlink_t;
# 218 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 3
typedef long fd_mask;







typedef struct _types_fd_set {
 fd_mask fds_bits[(((64)+(((sizeof (fd_mask) * 8))-1))/((sizeof (fd_mask) * 8)))];
} _types_fd_set;
# 249 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/types.h" 3
typedef unsigned long clockid_t;




typedef unsigned long timer_t;



typedef unsigned long useconds_t;
typedef long suseconds_t;
# 47 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 2 3



typedef __FILE FILE;




typedef _fpos_t fpos_t;





# 1 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/sys/stdio.h" 1 3
# 62 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 2 3
# 208 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3
FILE * tmpfile (void);
char * tmpnam (char *);
int fclose (FILE *);
int fflush (FILE *);
FILE * freopen (const char *, const char *, FILE *);
void setbuf (FILE *, char *);
int setvbuf (FILE *, char *, int, size_t);
int fprintf (FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int fscanf (FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int printf (const char *, ...) __attribute__ ((__format__ (__printf__, 1, 2)))
                                                            ;
int scanf (const char *, ...) __attribute__ ((__format__ (__scanf__, 1, 2)))
                                                           ;
int sscanf (const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int vfprintf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int vprintf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 1, 0)))
                                                            ;
int vsprintf (char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int fgetc (FILE *);
char * fgets (char *, int, FILE *);
int fputc (int, FILE *);
int fputs (const char *, FILE *);
int getc (FILE *);
int getchar (void);
char * gets (char *);
int putc (int, FILE *);
int putchar (int);
int puts (const char *);
int ungetc (int, FILE *);
size_t fread (void *, size_t _size, size_t _n, FILE *);
size_t fwrite (const void * , size_t _size, size_t _n, FILE *);





int fgetpos (FILE *, fpos_t *);
int fsetpos (FILE *, const fpos_t *);


int fseek (FILE *, long, int);
long ftell ( FILE *);
void rewind (FILE *);
void clearerr (FILE *);
int feof (FILE *);
int ferror (FILE *);
void perror (const char *);

FILE * fopen (const char *_name, const char *_type);
int sprintf (char *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int remove (const char *);
int rename (const char *, const char *);







int fseeko (FILE *, off_t, int);
off_t ftello ( FILE *);





int asiprintf (char **, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
char * asniprintf (char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * asnprintf (char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int asprintf (char **, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

int diprintf (int, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

int fcloseall (void);
int fiprintf (FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int fiscanf (FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int iprintf (const char *, ...) __attribute__ ((__format__ (__printf__, 1, 2)))
                                                            ;
int iscanf (const char *, ...) __attribute__ ((__format__ (__scanf__, 1, 2)))
                                                           ;
int siprintf (char *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int siscanf (const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int snprintf (char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int sniprintf (char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * tempnam (const char *, const char *);
int vasiprintf (char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
char * vasniprintf (char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
char * vasnprintf (char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int vasprintf (char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int vdiprintf (int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int vfiprintf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int vfiscanf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int vfscanf (FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int viprintf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 1, 0)))
                                                            ;
int viscanf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 1, 0)))
                                                           ;
int vscanf (const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 1, 0)))
                                                           ;
int vsiprintf (char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int vsiscanf (const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int vsniprintf (char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int vsnprintf (char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int vsscanf (const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
# 351 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3
FILE * fdopen (int, const char *);

int fileno (FILE *);
int getw (FILE *);
int pclose (FILE *);
FILE * popen (const char *, const char *);
int putw (int, FILE *);
void setbuffer (FILE *, char *, int);
int setlinebuf (FILE *);
int getc_unlocked (FILE *);
int getchar_unlocked (void);
void flockfile (FILE *);
int ftrylockfile (FILE *);
void funlockfile (FILE *);
int putc_unlocked (int, FILE *);
int putchar_unlocked (int);
# 376 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3
int dprintf (int, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;

FILE * fmemopen (void *, size_t, const char *);


FILE * open_memstream (char **, size_t *);



int vdprintf (int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;







int _asiprintf_r (struct _reent *, char **, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
char * _asniprintf_r (struct _reent *, char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
char * _asnprintf_r (struct _reent *, char *, size_t *, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int _asprintf_r (struct _reent *, char **, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int _diprintf_r (struct _reent *, int, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int _dprintf_r (struct _reent *, int, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int _fclose_r (struct _reent *, FILE *);
int _fcloseall_r (struct _reent *);
FILE * _fdopen_r (struct _reent *, int, const char *);
int _fflush_r (struct _reent *, FILE *);
int _fgetc_r (struct _reent *, FILE *);
char * _fgets_r (struct _reent *, char *, int, FILE *);




int _fgetpos_r (struct _reent *, FILE *, fpos_t *);
int _fsetpos_r (struct _reent *, FILE *, const fpos_t *);

int _fiprintf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int _fiscanf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
FILE * _fmemopen_r (struct _reent *, void *, size_t, const char *);
FILE * _fopen_r (struct _reent *, const char *, const char *);
FILE * _freopen_r (struct _reent *, const char *, const char *, FILE *);
int _fprintf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int _fpurge_r (struct _reent *, FILE *);
int _fputc_r (struct _reent *, int, FILE *);
int _fputs_r (struct _reent *, const char *, FILE *);
size_t _fread_r (struct _reent *, void *, size_t _size, size_t _n, FILE *);
int _fscanf_r (struct _reent *, FILE *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
int _fseek_r (struct _reent *, FILE *, long, int);
int _fseeko_r (struct _reent *, FILE *, _off_t, int);
long _ftell_r (struct _reent *, FILE *);
_off_t _ftello_r (struct _reent *, FILE *);
void _rewind_r (struct _reent *, FILE *);
size_t _fwrite_r (struct _reent *, const void * , size_t _size, size_t _n, FILE *);
int _getc_r (struct _reent *, FILE *);
int _getc_unlocked_r (struct _reent *, FILE *);
int _getchar_r (struct _reent *);
int _getchar_unlocked_r (struct _reent *);
char * _gets_r (struct _reent *, char *);
int _iprintf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int _iscanf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
FILE * _open_memstream_r (struct _reent *, char **, size_t *);
void _perror_r (struct _reent *, const char *);
int _printf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__printf__, 2, 3)))
                                                            ;
int _putc_r (struct _reent *, int, FILE *);
int _putc_unlocked_r (struct _reent *, int, FILE *);
int _putchar_unlocked_r (struct _reent *, int);
int _putchar_r (struct _reent *, int);
int _puts_r (struct _reent *, const char *);
int _remove_r (struct _reent *, const char *);
int _rename_r (struct _reent *, const char *_old, const char *_new)
                                          ;
int _scanf_r (struct _reent *, const char *, ...) __attribute__ ((__format__ (__scanf__, 2, 3)))
                                                           ;
int _siprintf_r (struct _reent *, char *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int _siscanf_r (struct _reent *, const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
int _sniprintf_r (struct _reent *, char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int _snprintf_r (struct _reent *, char *, size_t, const char *, ...) __attribute__ ((__format__ (__printf__, 4, 5)))
                                                            ;
int _sprintf_r (struct _reent *, char *, const char *, ...) __attribute__ ((__format__ (__printf__, 3, 4)))
                                                            ;
int _sscanf_r (struct _reent *, const char *, const char *, ...) __attribute__ ((__format__ (__scanf__, 3, 4)))
                                                           ;
char * _tempnam_r (struct _reent *, const char *, const char *);
FILE * _tmpfile_r (struct _reent *);
char * _tmpnam_r (struct _reent *, char *);
int _ungetc_r (struct _reent *, int, FILE *);
int _vasiprintf_r (struct _reent *, char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
char * _vasniprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
char * _vasnprintf_r (struct _reent*, char *, size_t *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int _vasprintf_r (struct _reent *, char **, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int _vdiprintf_r (struct _reent *, int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int _vdprintf_r (struct _reent *, int, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int _vfiprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int _vfiscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int _vfprintf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int _vfscanf_r (struct _reent *, FILE *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int _viprintf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int _viscanf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int _vprintf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)))
                                                            ;
int _vscanf_r (struct _reent *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 2, 0)))
                                                           ;
int _vsiprintf_r (struct _reent *, char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int _vsiscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;
int _vsniprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int _vsnprintf_r (struct _reent *, char *, size_t, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 4, 0)))
                                                            ;
int _vsprintf_r (struct _reent *, char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)))
                                                            ;
int _vsscanf_r (struct _reent *, const char *, const char *, __gnuc_va_list) __attribute__ ((__format__ (__scanf__, 3, 0)))
                                                           ;



int fpurge (FILE *);
ssize_t __getdelim (char **, size_t *, int, FILE *);
ssize_t __getline (char **, size_t *, FILE *);
# 553 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3
int __srget_r (struct _reent *, FILE *);
int __swbuf_r (struct _reent *, int, FILE *);
# 573 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3
FILE *funopen (const void * __cookie, int (*__readfn)(void * __cookie, char *__buf, int __n), int (*__writefn)(void * __cookie, const char *__buf, int __n), fpos_t (*__seekfn)(void * __cookie, fpos_t __off, int __whence), int (*__closefn)(void * __cookie))



                                   ;
FILE *_funopen_r (struct _reent *, const void * __cookie, int (*__readfn)(void * __cookie, char *__buf, int __n), int (*__writefn)(void * __cookie, const char *__buf, int __n), fpos_t (*__seekfn)(void * __cookie, fpos_t __off, int __whence), int (*__closefn)(void * __cookie))



                                   ;







typedef ssize_t cookie_read_function_t(void *__cookie, char *__buf, size_t __n);
typedef ssize_t cookie_write_function_t(void *__cookie, const char *__buf,
     size_t __n);




typedef int cookie_seek_function_t(void *__cookie, off_t *__off, int __whence);

typedef int cookie_close_function_t(void *__cookie);
typedef struct
{


  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
FILE *fopencookie (void *__cookie, const char *__mode, cookie_io_functions_t __functions)
                                                         ;
FILE *_fopencookie_r (struct _reent *, void *__cookie, const char *__mode, cookie_io_functions_t __functions)
                                                         ;
# 721 "/home/anhlc/CodeSourcery/Sourcery_G++_Lite/bin/../lib/gcc/arm-none-eabi/4.5.1/../../../../arm-none-eabi/include/stdio.h" 3

# 156 "sicslow_ethernet.c" 2
# 170 "sicslow_ethernet.c"
usbstick_mode_t usbstick_mode;

uint8_t mac_createSicslowpanLongAddr(uint8_t * ethernet, uip_lladdr_t * lowpan);
uint8_t mac_createEthernetAddr(uint8_t * ethernet, uip_lladdr_t * lowpan);
# 190 "sicslow_ethernet.c"
uint8_t prefixCounter;
uint8_t prefixBuffer[32][3];


uint8_t raw_buf[127+ (14) +1];
# 206 "sicslow_ethernet.c"
void mac_ethernetSetup(void)
{
  usbstick_mode.sicslowpan = 1;
  usbstick_mode.sendToRf = 1;
  usbstick_mode.translate = 1;
  usbstick_mode.raw = 1;



  ST_RadioEnableReceiveCrc(1);


   ST_RadioEnableAutoAck(0);
 if (ST_RadioAddressFilteringEnabled() == 0)
 {
  printf("GOOD!!\n");
 }
 else
 {
  printf("BAD!!\n");
 }
   ST_RadioEnableAddressFiltering(0);
 if (ST_RadioAddressFilteringEnabled() == 0)
 {
  printf("GOOD!!\n");
 }
 else
 {
  printf("BAD!!\n");
 }





}






void mac_ethernetToLowpan(uint8_t * ethHeader)
{

  uip_lladdr_t destAddr;
  uip_lladdr_t *destAddrPtr = ((void *)0);

  ;







  if (((struct uip_eth_hdr *) ethHeader)->type != (u16_t)((((u16_t) (0x86dd)) << 8) | (((u16_t) (0x86dd)) >> 8))) {
    ;

    uip_len = 0;
    return;
  }


  if (usbstick_mode.sendToRf == 0) {
    uip_len = 0;
    return;
  }


  if ( (((struct uip_eth_hdr *) ethHeader)->dest.addr[0] == 0x33) &&
       (((struct uip_eth_hdr *) ethHeader)->dest.addr[1] == 0x33) )
  {
    ;
    ;
  } else if ( (((struct uip_eth_hdr *) ethHeader)->dest.addr[0] == 0xFF) &&
            (((struct uip_eth_hdr *) ethHeader)->dest.addr[1] == 0xFF) &&
            (((struct uip_eth_hdr *) ethHeader)->dest.addr[2] == 0xFF) &&
            (((struct uip_eth_hdr *) ethHeader)->dest.addr[3] == 0xFF) &&
            (((struct uip_eth_hdr *) ethHeader)->dest.addr[4] == 0xFF) &&
            (((struct uip_eth_hdr *) ethHeader)->dest.addr[5] == 0xFF) ) {

    ;

    uip_len = 0;
    return;
  } else {
    ;

    if (mac_createSicslowpanLongAddr( &(((struct uip_eth_hdr *) ethHeader)->dest.addr[0]), &destAddr) == 0) {
      ;

      uip_len = 0;
      return;
    }
    ;
    destAddrPtr = &destAddr;
  }


  if(uip_len > (14)) {
    uip_len -= (14);


    if (usbstick_mode.translate) {

      mac_translateIPLinkLayer(ll_802154_type);
      ;
    }

    if (usbstick_mode.sendToRf){
      tcpip_output(destAddrPtr);

    }
  }

  uip_len = 0;

}






void mac_LowpanToEthernet(void)
{



  ((struct uip_eth_hdr *)(uip_aligned_buf.u8))->type = uip_htons(0x86dd);


  if(rimeaddr_cmp(packetbuf_addr(PACKETBUF_ADDR_RECEIVER), &rimeaddr_null)) {


    ((struct uip_eth_hdr *)(uip_aligned_buf.u8))->dest.addr[0] = 0x33;
    ((struct uip_eth_hdr *)(uip_aligned_buf.u8))->dest.addr[1] = 0x33;
    ((struct uip_eth_hdr *)(uip_aligned_buf.u8))->dest.addr[2] = ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->destipaddr.u8[12];
    ((struct uip_eth_hdr *)(uip_aligned_buf.u8))->dest.addr[3] = ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->destipaddr.u8[13];
    ((struct uip_eth_hdr *)(uip_aligned_buf.u8))->dest.addr[4] = ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->destipaddr.u8[14];
    ((struct uip_eth_hdr *)(uip_aligned_buf.u8))->dest.addr[5] = ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->destipaddr.u8[15];
  } else {

 mac_createEthernetAddr((uint8_t *) &(((struct uip_eth_hdr *)(uip_aligned_buf.u8))->dest.addr[0]),
                        (uip_lladdr_t *)packetbuf_addr(PACKETBUF_ADDR_RECEIVER));
  }


  mac_createEthernetAddr((uint8_t *) &(((struct uip_eth_hdr *)(uip_aligned_buf.u8))->src.addr[0]),
                         (uip_lladdr_t *)packetbuf_addr(PACKETBUF_ADDR_SENDER));


  if (usbstick_mode.translate) {

    mac_translateIPLinkLayer(ll_8023_type);
  }

  ;

  uip_len += (14);




}
# 384 "sicslow_ethernet.c"
int8_t mac_translateIPLinkLayer(lltype_t target)
{


  if (((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->proto == 58) {
    ;
    return mac_translateIcmpLinkLayer(target);
  }
  return 0;




}

# 1 "../../../core/./net/uip-icmp6.h" 1
# 101 "../../../core/./net/uip-icmp6.h"
typedef struct uip_icmp6_error{
  u32_t param;
} uip_icmp6_error;
# 113 "../../../core/./net/uip-icmp6.h"
void
uip_icmp6_echo_request_input(void);







void
uip_icmp6_error_output(u8_t type, u8_t code, u32_t param);
# 132 "../../../core/./net/uip-icmp6.h"
void
uip_icmp6_send(uip_ipaddr_t *dest, int type, int code, int payload_len);
# 400 "sicslow_ethernet.c" 2
# 1 "../../../core/./net/uip-nd6.h" 1
# 49 "../../../core/./net/uip-nd6.h"
# 1 "../../../core/./sys/stimer.h" 1
# 82 "../../../core/./sys/stimer.h"
struct stimer {
  unsigned long start;
  unsigned long interval;
};

void stimer_set(struct stimer *t, unsigned long interval);
void stimer_reset(struct stimer *t);
void stimer_restart(struct stimer *t);
int stimer_expired(struct stimer *t);
unsigned long stimer_remaining(struct stimer *t);
unsigned long stimer_elapsed(struct stimer *t);
# 50 "../../../core/./net/uip-nd6.h" 2
# 196 "../../../core/./net/uip-nd6.h"
typedef enum {
  INCOMPLETE = 0,
  REACHABLE = 1,
  STALE = 2,
  DELAY = 3,
  PROBE = 4,
  NO_STATE = 5
} uip_neighbor_state;






struct uip_nd6_neighbor {
  uip_ipaddr_t ipaddr;
  uip_lladdr_t lladdr;
  u8_t isrouter;
  uip_neighbor_state state;
  struct stimer reachable;
  struct stimer last_send;
  u8_t count_send;
  u8_t used;






};



struct uip_nd6_defrouter {
  struct uip_nd6_neighbor *nb;
  struct stimer lifetime;



  u8_t used;
};


struct uip_nd6_prefix {
  uip_ipaddr_t ipaddr;
  u8_t length;



  struct stimer vlifetime;
  u8_t is_infinite;
  u8_t used;
};


extern struct etimer uip_nd6_timer_periodic;
# 271 "../../../core/./net/uip-nd6.h"
typedef struct uip_nd6_ns {
  uint32_t reserved;
  uip_ipaddr_t tgtipaddr;
} uip_nd6_ns;






typedef struct uip_nd6_na {
  uint8_t flagsreserved;
  uint8_t reserved[3];
  uip_ipaddr_t tgtipaddr;
} uip_nd6_na;






typedef struct uip_nd6_rs {
  uint32_t reserved;
} uip_nd6_rs;






typedef struct uip_nd6_ra {
  uint8_t cur_ttl;
  uint8_t flags_reserved;
  uint16_t router_lifetime;
  uint32_t reachable_time;
  uint32_t retrans_timer;
} uip_nd6_ra;






typedef struct uip_nd6_redirect {
  uint32_t reserved;
  uip_ipaddr_t tgtipaddress;
  uip_ipaddr_t destipaddress;
} uip_nd6_redirect;
# 327 "../../../core/./net/uip-nd6.h"
typedef struct uip_nd6_opt_hdr {
  uint8_t type;
  uint8_t len;
} uip_nd6_opt_hdr;


typedef struct uip_nd6_opt_prefix_info {
  uint8_t type;
  uint8_t len;
  uint8_t preflen;
  uint8_t flagsreserved1;
  uint32_t validlt;
  uint32_t preferredlt;
  uint32_t reserved2;
  uip_ipaddr_t prefix;
} uip_nd6_opt_prefix_info ;


typedef struct uip_nd6_opt_mtu {
  uint8_t type;
  uint8_t len;
  uint16_t reserved;
  uint32_t mtu;
} uip_nd6_opt_mtu;


typedef struct uip_nd6_opt_redirected_hdr {
  uint8_t type;
  uint8_t len;
  uint8_t reserved[6];
} uip_nd6_opt_redirected_hdr;
# 367 "../../../core/./net/uip-nd6.h"
void uip_nd6_init(void);




void uip_nd6_periodic(void);







struct uip_nd6_neighbor *uip_nd6_nbrcache_lookup(uip_ipaddr_t *ipaddr);
# 390 "../../../core/./net/uip-nd6.h"
struct uip_nd6_neighbor * uip_nd6_nbrcache_add(uip_ipaddr_t *ipaddr,
                                               uip_lladdr_t *lladdr,
                                               u8_t isrouter,
                                               uip_neighbor_state state);



struct uip_nd6_defrouter * uip_nd6_choose_defrouter(void);






struct uip_nd6_defrouter *
uip_nd6_defrouter_lookup(struct uip_nd6_neighbor *neighbor);





void uip_nd6_defrouter_rm(struct uip_nd6_defrouter *router);







struct uip_nd6_defrouter *
uip_nd6_defrouter_add(struct uip_nd6_neighbor *neighbor, unsigned long interval);






u8_t uip_nd6_is_addr_onlink(uip_ipaddr_t *ipaddr);






struct uip_nd6_prefix *
uip_nd6_prefix_lookup(uip_ipaddr_t *ipaddr);
# 444 "../../../core/./net/uip-nd6.h"
struct uip_nd6_prefix *
uip_nd6_prefix_add(uip_ipaddr_t *ipaddr, u8_t length, unsigned long interval);





void
 uip_nd6_prefix_rm(struct uip_nd6_prefix *prefix);
# 481 "../../../core/./net/uip-nd6.h"
void
uip_nd6_ns_input(void);
# 504 "../../../core/./net/uip-nd6.h"
void
uip_nd6_ns_output(uip_ipaddr_t *src, uip_ipaddr_t *dest, uip_ipaddr_t *tgt);
# 524 "../../../core/./net/uip-nd6.h"
void
uip_nd6_na_input(void);
# 555 "../../../core/./net/uip-nd6.h"
void uip_nd6_rs_output(void);
# 567 "../../../core/./net/uip-nd6.h"
void
uip_nd6_ra_input(void);



void
uip_appserver_addr_get(uip_ipaddr_t *ipaddr);
# 401 "sicslow_ethernet.c" 2

typedef struct {
  uint8_t type;
  uint8_t length;
  uint8_t data[16];
} icmp_opts_t;




void slide(uint8_t * data, uint8_t length, int16_t slide);
# 424 "sicslow_ethernet.c"
int8_t mac_translateIcmpLinkLayer(lltype_t target)
{
  uint16_t icmp_opt_offset = 0;
  int16_t len = ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->len[1] | (((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->len[0] << 8);

  uint16_t iplen;

  uint8_t i;

  int16_t sizechange;

  uint8_t llbuf[16];


  switch(((struct uip_icmp_hdr *)&(uip_aligned_buf.u8)[(14) + 40])->type) {
    case 135:
    case 136:
      icmp_opt_offset = 24;
      break;

    case 133:
      icmp_opt_offset = 8;
      break;

    case 134:
      icmp_opt_offset = 16;
      break;

    case 137:
      icmp_opt_offset = 40;
      break;


    case 1:
    case 2:
    case 3:
    case 4:
    case 128:
    case 129:
      return 0;
      break;

    default:
      return -1;
  }


  len -= icmp_opt_offset;


  if (len < 8) return -2;


  while (len >= 8){


    if (((((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->type) == 1) ||
        ((((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->type) == 2) ) {



      for(i = 0; i < (((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length*8 - 2); i++) {
        llbuf[i] = ((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->data[i];
      }


      if (target == ll_802154_type) {

        sizechange = 8;
        slide(((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->data + 6, len - 6, sizechange);
      } else if (target == ll_8023_type) {






        sizechange = -8;
        slide(((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->data + 14, len - 14, sizechange);
      } else {
        return -3;
      }


      if (target == ll_802154_type) {
        mac_createSicslowpanLongAddr(llbuf, (uip_lladdr_t *)((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->data);
      } else {
        mac_createEthernetAddr(((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->data, (uip_lladdr_t *)llbuf);
      }


      if (target == ll_802154_type) {
        ((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length = 2;
      } else {
        ((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length = 1;
      }


      iplen = ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->len[1] | (((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->len[0]<<8);
      iplen += sizechange;
      len += sizechange;

      ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->len[1] = (uint8_t)iplen;
      ((struct uip_ip_hdr *)&(uip_aligned_buf.u8)[(14)])->len[0] = (uint8_t)(iplen >> 8);

      uip_len += sizechange;


      ((struct uip_icmp_hdr *)&(uip_aligned_buf.u8)[(14) + 40])->icmpchksum = 0;
      ((struct uip_icmp_hdr *)&(uip_aligned_buf.u8)[(14) + 40])->icmpchksum = ~uip_icmp6chksum();


      len -= 8 * ((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length;
      icmp_opt_offset += 8 * ((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length;
    } else {


      len -= 8 * ((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length;


      if (((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length == 0) {
        ;
        len = 0;
      }

      icmp_opt_offset += 8 * ((icmp_opts_t *)&(uip_aligned_buf.u8)[(14) + 40 + icmp_opt_offset])->length;

    }

  }

  return 0;

}







uint8_t mac_createSicslowpanLongAddr(uint8_t * ethernet, uip_lladdr_t * lowpan)
{
  uint8_t index;






  if (memcmp((uint8_t *)&uip_lladdr.addr[2], ethernet, 6) == 0) {
  memcpy((uint8_t *)lowpan, uip_lladdr.addr, 8);


  return 1;
 }


  if (ethernet[0] & (1<<2)) {


    index = ethernet[0] >> 3;


    if (index >= prefixCounter) {
      return 0;
    }


    lowpan->addr[0] = prefixBuffer[index][0];
 lowpan->addr[3] = prefixBuffer[index][1];
 lowpan->addr[4] = prefixBuffer[index][2];



  } else {
    lowpan->addr[0] = ethernet[0];
    lowpan->addr[3] = 0xff;
    lowpan->addr[4] = 0xfe;
  }


    lowpan->addr[1] = ethernet[1];
    lowpan->addr[2] = ethernet[2];
    lowpan->addr[5] = ethernet[3];
    lowpan->addr[6] = ethernet[4];
    lowpan->addr[7] = ethernet[5];
# 620 "sicslow_ethernet.c"
  return 1;
}







uint8_t mac_createEthernetAddr(uint8_t * ethernet, uip_lladdr_t * lowpan)
{
  uint8_t index = 0;
  uint8_t i;







  if (memcmp(uip_lladdr.addr, (uint8_t *)lowpan, 8) == 0) {
  memcpy(ethernet, &uip_lladdr.addr[2], 6);


  return 1;
 }



  if ((lowpan->addr[3] == 0xff) && (lowpan->addr[4] == 0xfe) &&
      ((lowpan->addr[0] & (1<<2)) == 0) &&
      ((lowpan->addr[0] & (1<<0)) == 0) &&
      (lowpan->addr[0] & (1<<1))) {


      ethernet[0] = lowpan->addr[0];
   ethernet[1] = lowpan->addr[1];
   ethernet[2] = lowpan->addr[2];
   ethernet[3] = lowpan->addr[5];
   ethernet[4] = lowpan->addr[6];
   ethernet[5] = lowpan->addr[7];


  } else {


    for (i = 0; i < prefixCounter; i++) {



       if ((lowpan->addr[0] == prefixBuffer[i][0]) &&
           (lowpan->addr[3] == prefixBuffer[i][1]) &&
           (lowpan->addr[4] == prefixBuffer[i][2])) {
   break;
    }

    }

    index = i;


    if (index >= 32) {
      index = 0;
      prefixCounter = 32;
    } else {

      if (index == prefixCounter) {
        prefixCounter++;
      }
    }


    prefixBuffer[index][0] = lowpan->addr[0];
 prefixBuffer[index][1] = lowpan->addr[3];
 prefixBuffer[index][2] = lowpan->addr[4];


    ethernet[1] = lowpan->addr[1];
 ethernet[2] = lowpan->addr[2];
 ethernet[3] = lowpan->addr[5];
 ethernet[4] = lowpan->addr[6];
    ethernet[5] = lowpan->addr[7];


    ethernet[0] = (1<<2) | (1<<1) | (index << 3);
  }
# 715 "sicslow_ethernet.c"
  return 1;
}
# 727 "sicslow_ethernet.c"
void slide(uint8_t * data, uint8_t length, int16_t slide)
{

  if (!length) return;
  if (!slide) return;

  uint8_t i = 0;

  while(length) {
    length--;


    if (slide > 0) {
      *(data + length + slide) = *(data + length);


    } else {
      *(data + slide + i) = *(data + i);
    }

    i++;
  }
}
