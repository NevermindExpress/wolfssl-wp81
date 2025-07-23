///
/// This file contains a C export of WinRT cryptographic random number generator function.
/// This function is referenced on wolfSSL and is compiled with application.
///
/// DO NOT INTEGRATE THIS SOURCE FILE TO WOLFSSL!!! 
/// This file is meant to be compiled with the APPLICATION as a supplemental.
///

#include <collection.h>
#include <ppltasks.h>

using namespace Windows::Security::Cryptography;
using namespace Windows::Storage::Streams;

extern "C" uint32_t wpGenRandom() {
	return CryptographicBuffer::GenerateRandomNumber();
}