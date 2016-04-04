/* ibrcommon/config.h.  Generated from config.h.in by configure.  */
/* ibrcommon/config.h.in.  Generated from configure.ac by autoheader.  */

/* Compiling for Android! */
/* #undef ANDROID */

/* Define to 1 if you have the `alarm' function. */
#define HAVE_ALARM 1

/* Define to 1 if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define to 1 if you have the `bzero' function. */
#define HAVE_BZERO 1

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <features.h> header file. */
#define HAVE_FEATURES_H 1

/* Define to 1 if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `inet_ntoa' function. */
#define HAVE_INET_NTOA 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* "netlink library is available" */
/* #undef HAVE_LIBNL */

/* "netlink library is available" */
/* #undef HAVE_LIBNL2 */

/* "netlink library 3.0 is available" */
#define HAVE_LIBNL3 1

/* "netlink genl library 3.0 is available" */
#define HAVE_LIBNL3_GENL 1

/* "netlink route library 3.0 is available" */
#define HAVE_LIBNL3_ROUTE 1

/* Define to 1 if you have the `nl-genl' library (-lnl-genl). */
/* #undef HAVE_LIBNL_GENL */

/* Define to 1 if you have the `nl-genl-3' library (-lnl-genl-3). */
/* #undef HAVE_LIBNL_GENL_3 */

/* Define to 1 if you have the `nl-route' library (-lnl-route). */
/* #undef HAVE_LIBNL_ROUTE */

/* Define to 1 if you have the `nl-route-3' library (-lnl-route-3). */
/* #undef HAVE_LIBNL_ROUTE_3 */

/* Define to 1 if you have the `pthread' library (-lpthread). */
#define HAVE_LIBPTHREAD 1

/* Define to 1 if you have the `rt' library (-lrt). */
#define HAVE_LIBRT 1

/* "xml library is available" */
/* #undef HAVE_LIBXML */

/* "enable lowpan support" */
/* #undef HAVE_LOWPAN_SUPPORT */

/* Define to 1 if you have the <mach/mach_time.h> header file. */
/* #undef HAVE_MACH_MACH_TIME_H */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define to 1 if you have the `mkdir' function. */
#define HAVE_MKDIR 1

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* "openssl library is available" */
/* #undef HAVE_OPENSSL */

/* Define to 1 if you have the `pow' function. */
#define HAVE_POW 1

/* "pthread clocking" */
#define HAVE_PTHREAD_CONDATTR_SETCLOCK 1

/* "pthread delay" */
/* #undef HAVE_PTHREAD_DELAY */

/* "pthread delay np" */
/* #undef HAVE_PTHREAD_DELAY_NP */

/* "pthread concurrency" */
#define HAVE_PTHREAD_SETCONCURRENCY 1

/* "pthread scheduling" */
#define HAVE_PTHREAD_SETSCHEDPRIO 1

/* "pthread yield" */
#define HAVE_PTHREAD_YIELD 1

/* Define to 1 if you have the `rmdir' function. */
#define HAVE_RMDIR 1

/* Define to 1 if you have the <semaphore.h> header file. */
#define HAVE_SEMAPHORE_H 1

/* Define to 1 if you have the `socket' function. */
#define HAVE_SOCKET 1

/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the <sys/semaphore.h> header file. */
/* #undef HAVE_SYS_SEMAPHORE_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if the system has the type `_Bool'. */
/* #undef HAVE__BOOL */

/* "lowpan extension is available" */
/* #undef IBRCOMMON_SUPPORT_LOWPAN */

/* "ssl extension is available" */
/* #undef IBRCOMMON_SUPPORT_SSL */

/* "xml extension is available" */
/* #undef IBRCOMMON_SUPPORT_XML */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "ibrcommon"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "morgenro@ibr.cs.tu-bs.de"

/* Define to the full name of this package. */
#define PACKAGE_NAME "ibrcommon"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "ibrcommon 1.0.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "ibrcommon"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.0.1"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Version number of package */
#define VERSION "1.0.1"

/* Compiling for Win32! */
/* #undef WIN32 */

/* Minimum platform is Windows 7 */
/* #undef WINVER */

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */

/* Minimum platform is Windows 7 */
/* #undef _WIN32_WINNT */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef int64_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */
