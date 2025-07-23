#ifndef _WIN_USER_SETTINGS_H_
#define _WIN_USER_SETTINGS_H_

/* Verify this is Windows */
#ifndef _WIN32
#error This user_settings.h header is only designed for Windows
#endif

#define USE_WOLFSSL_IO
#define HAVE_AESGCM
#define WOLFSSL_TLS13
#define HAVE_HKDF
#define HAVE_FFDHE_4096
#define WC_RSA_PSS
#define WOLFSSL_DTLS
#define WOLFSSL_DTLS13
#define WOLFSSL_SEND_HRR_COOKIE
#define WOLFSSL_DTLS_CID

// Windows Phone support stuff
#if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
	// wolfSSL flags
	#define NO_GETENV
	#define CUSTOM_RAND_GENERATE  wpGenRandom // To be compiled and linked in the application.
	// Polyfills
	#define WaitForMultipleObjects(a,b,c,d) WaitForMultipleObjectsEx(a,b,c,d,0)
	#define WaitForSingleObject(a,b) WaitForSingleObjectEx(a,b,0)
	#define CreateEventA(Attrib, ManReset, InitialState, Name) CreateEventExA(Attrib, Name, InitialState << 1 | ManReset, EVENT_ALL_ACCESS)
	extern int __stdcall inet_pton(int Family, const char* pszAddrString, void* pAddrBuf); // Available.
	#define InetPton inet_pton
	#define _beginthreadex CreateThread
	#define _beginthread(addr, stack, arg) CreateThread(NULL, stack, addr, arg, 0, NULL)
	#define FindFirstFileA(name, out) FindFirstFileExA(name, FindExInfoStandard, out, FindExSearchNameMatch, NULL, 0)
	#define InitializeCriticalSection(out) InitializeCriticalSectionEx(out, 0, CRITICAL_SECTION_NO_DEBUG_INFO)
#endif

/* Configurations */
#if defined(HAVE_FIPS)
    /* FIPS */
    #define OPENSSL_EXTRA
    #define HAVE_THREAD_LS
    #define WOLFSSL_KEY_GEN
    #define HAVE_HASHDRBG
    #define WOLFSSL_SHA384
    #define WOLFSSL_SHA512
    #define NO_PSK
    #define NO_RC4
    #define NO_DSA
    #define NO_MD4

    #define GCM_NONCE_MID_SZ 12
#else
    /* Enables blinding mode, to prevent timing attacks */
    #define WC_RSA_BLINDING
    #define NO_MULTIBYTE_PRINT

    #define HAVE_CRL
#if WINAPI_FAMILY != WINAPI_FAMILY_PHONE_APP
    #define HAVE_CRL_MONITOR // Uses 3 missing functions.
#endif

    #if defined(WOLFSSL_LIB)
        /* The lib */
        #define OPENSSL_EXTRA
        #define OPENSSL_ALL
        #define WOLFSSL_RIPEMD
        #define NO_PSK
        #define HAVE_EXTENDED_MASTER
        #define WOLFSSL_SNIFFER
        #define HAVE_SECURE_RENEGOTIATION

        #define HAVE_AESGCM
        #define WOLFSSL_AESGCM_STREAM
        #define WOLFSSL_SHA384
        #define WOLFSSL_SHA512

        #define HAVE_SUPPORTED_CURVES
        #define HAVE_TLS_EXTENSIONS

        #define HAVE_ECC
        #define ECC_SHAMIR
        #define ECC_TIMING_RESISTANT

        #define WOLFSSL_SP_X86_64
        #define SP_INT_BITS  4096

        /* Optional Performance Speedups */
        #if 0
            /* AESNI on x64 */
            #ifdef _WIN64
                #define HAVE_INTEL_RDSEED
                #define WOLFSSL_AESNI
                #define HAVE_INTEL_AVX1
                #if 0
                    #define HAVE_INTEL_AVX2
                #endif

                #define USE_INTEL_CHACHA_SPEEDUP
                #define USE_INTEL_POLY1305_SPEEDUP
            #endif

            /* Single Precision Support for RSA/DH 1024/2048/3072 and
             * ECC P-256/P-384 */
            #define WOLFSSL_SP
            #define WOLFSSL_HAVE_SP_ECC
            #define WOLFSSL_HAVE_SP_DH
            #define WOLFSSL_HAVE_SP_RSA

            #ifdef _WIN64
                /* Old versions of MASM compiler do not recognize newer
                 * instructions. */
                #if 0
                    #define NO_AVX2_SUPPORT
                    #define NO_MOVBE_SUPPORT
                #endif
                #define WOLFSSL_SP_ASM
                #define WOLFSSL_SP_X86_64_ASM
            #endif
        #endif
    #else
        /* The servers and clients */
        #define OPENSSL_EXTRA
        #define NO_PSK
    #endif
#endif /* HAVE_FIPS */

#endif /* _WIN_USER_SETTINGS_H_ */
