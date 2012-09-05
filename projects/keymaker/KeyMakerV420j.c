/*
 * $Revision: 1.1.2.26 $
 * $Date: 2010/03/30 15:04:50 $
 */

/*
  KeyMaker.c, version 4.20j (02Feb2010)

  Stand-alone key generator source code for the Armadillo Software Protection
  System, by The Silicon Realms Toolworks. Copyright 1999-2008 by Digital River
  and The Silicon Realms Toolworks; all rights reserved.

  Please do not distribute this file! If someone else needs it, please have
  them contact us at support@siliconrealms.com for the latest version.

  To the user: This code will generate keys for *any* Armadillo-protected
  program, including Armadillo itself, given the keytext (referred to as the
  "encryption template" in the Armadillo documentation) for the associated
  security certificate. It should be completely self-contained and should
  compile as-is with no errors or warnings. All you'll need to do is uncomment
  the appropriate #defines, found directly below this comment block, and start
  compiling it. For usage information, see the comment block just above the
  main function that you're using (either STDMAIN or SWREG).

  All of this code assumes that a "long int" is 32 bits, and a "short int" is
  16 bits. It HAS been tested on both little-endian (Intel) and big-endian
  (Motorola) systems, and works the same on both. See the section-header
  comment blocks for specific implementation info, if required. The function
  CookText will need to be changed if it is ever used on a system where the
  numeric representation of the letters are not in alphabetical order (almost
  never, on modern systems).

  NOTE: To produce the exact same keys on different systems, for testing, you
  have to make the functions GetRandomSeed() and GetToday() return the same
  values! We've created a #define called FOR_TESTING that sets both of these to
  a known value, GetRandomSeed() to 1000, and GetToday() to 1791 (US
  Thanksgiving day, 2003); if required, just add a "#define FOR_TESTING" line.

  ---

  NOTE: If you are using the command line to call this key generator, the level
  number you provide should be one higher than what the comments below show.
  (i.e. ShortV3 Level 10 keys are normalized internally to level 29 but using
  the command line should pass a 30.

  ---


  #defines:

	STDMAIN: Uncomment this one to include a standard main() function (found at
	  the bottom of the file). This is the only one that most people need.

	CALLED_FROM_JAVA: Uncomment this line to handle "escaped" double-quotes,
	  such as those apparently added by the Java Runtime.exec() method.

	SWREG: This is an alternate form of the main() function, intended for use
	  with SWREG. The SIGNATURE_LEVEL and ENCRYPTION_TEMPLATE portions are
	  designed to work with it.

	USECLOCKTICKS: If you need to create guaranteed-unique signed keys faster
	  than once per second, you can try uncommenting this #define. It uses the
	  clock() function, which is defined as part of the ANSI standard, but
	  which may not return a unique value if it's not supported on your
	  platform. If it isn't supported, then you'll need to customize the
	  GetRandomSeed() function further down -- see the comments just above that
	  function for more information.

	ASP Notes: Refer to files: ASPReadme.txt, KeyMaker.asp, TestKeyMaker.asp

	Partial revision history:

		4.00 (01Feb2004): Added ShortV3 Level 10 support, for Armadillo 3.61
		and later.

		4.00a (10Feb2004): Added FOR_TESTING defines, in GetRandomSeed() and
		GetToday().

		4.01 (12Feb2004): Added "nameless" ShortV3 key support, for Armadillo
		3.70 and later.

		4.02 (19Feb2004): Fixed RetrieveKeyInfo function for ShortV3 Level 10
		keys.

		4.02a (11Mar2004): Fixed minor ShortV3 Level 10 bugs in RetrieveKeyInfo
		function.

		4.10 (13Jun2004): Added a second random number generator, which uses a
		128-bit seed instead of a 32-bit one, to block brute-force attacks on
		the RNG.

		4.11 (14Jun2004): Updated the second random number generator. It's now
		more secure, if somewhat slower.

		4.12 (26Aug2004): Corrected some minor problems with compilers that
		assume unsigned characters. Thanks to BMT Micro for letting us know
		about that, and pointing out the places that require the fix.

		4.20 (16Mar2005): Added the keys-with-strings option, via the function
		CreateShortV3KeyWithString, for Armadillo 4.10 and later. Note that
		keys that include strings are NOT compatible with programs protected
		with earlier versions of Armadillo, and will not be recognized by them.

		4.20a (04Apr2005): Added the /str option to STDMAIN, by request, so
		that this file can create keys-with-strings using STDMAIN.

		4.20c (16May2005): Fixed a minor bug in RetrieveKeyInfo, mostly for
		keys containing strings.

		4.20d (18Jul2005): Added #define for GNU CC compilers to handle their
		lack of a stricmp function.

		4.20e (18Nov2005): Added a comment about level number required when using
		command line activation of this.

		4.20f (14Feb2006): Added ASP Notes section. (see Case 5315).

		4.20g (20Apr2006): Added code to correctly handle uninstall codes for nameless keys. (see Case 9528).

		4.20h (17Oct2006): Added #pragma lines so that Visual C++ 8.0/Visual Studio 2005 does not give bogus
		security deprecation complaints for standard C functions. They can be removed if you are not using
		Visual C++ and the pragmas are causing problems on your compiler.

		4.20i (31Jan2008): Commented RetrieveKeyInfo better to insure that it is known the level must be
		1 based and not zero based like the create functions.

		4.20j (02Feb2010): Fixed the mult function to work properly on 64 bit machines.
		Original solution by Zhuo Mei
*/

/*#define STDMAIN*/
/*#define CALLED_FROM_JAVA*/

/*#define SWREG*/
/*#define ENCRYPTION_TEMPLATE ""*/
/*#define SIGNATURE_LEVEL 0*/
/*#define USECLOCKTICKS*/

/* The following #pragma lines are here so that Visual C++ 8.0/Visual Studio 2005 does not give bogus security
   deprecation complaints for standard C functions. */
#pragma warning(disable:4996)
#pragma warning(disable:4244)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*
	For compiling on a 64 bit machine, you may have to redefine longs to ints:
*/
/*#undef long*/
/*#define long int*/

/*
	For compiling on Linux with GNU CC, uncomment the following line
*/
/*#define stricmp strcasecmp*/

const int primeoffsetcount=9, primeoffsets[]={ 15, 15, 21, 81, 3103, 3643, 2191, 9691, 2887 };

/*#define TEST*/

/*
	Set BITS_PER_DIGIT to 16 if your system can handle it, for efficiency.
*/

#define BITS_PER_DIGIT 8

/*
	In the typedefs below, DIGIT must be at least eight bits long (I don't know
	of any computer where this wouldn't be true), and WORKING_DIGIT must be at
	least twice the size of DIGIT. Modify them as needed.
*/

#if BITS_PER_DIGIT==8
	typedef unsigned char DIGIT; /* This must be a minimum of 8 bits long! */
	typedef unsigned short WORKING_DIGIT; /* This must be at least twice the size of DIGIT! */
	#define DIGIT_HIBIT 0x80
	#define	WORKING_DIGIT_HIBIT 0x8000
	#define DIGIT_MASK 0xFF
	#define OVERFLOW_DIGIT 0x100
#elif BITS_PER_DIGIT==16
	typedef unsigned short DIGIT;
	typedef unsigned long WORKING_DIGIT;
	#define DIGIT_HIBIT 0x8000
	#define	WORKING_DIGIT_HIBIT 0x80000000
	#define DIGIT_MASK 0xFFFF
	#define OVERFLOW_DIGIT 0x10000L
#else
	#error Invalid BITS_PER_DIGIT, must be 8 or 16.
#endif
#define HWIDXOR 0

/*
#if sizeof(long int)!=4 || sizeof(short int)!=2
	#error This code requires 32-bit long int and 16-bit short int to operate correctly.
#endif
*/

struct BigIntBase {
	int length, alloc, negative;
	DIGIT *digits;
};

typedef struct BigIntBase* BigInt;

/* Basic housekeeping functions */
BigInt BigInt_Create();
void BigInt_Destroy(BigInt n);
void BigInt_Copy(BigInt target, BigInt source);
void BigInt_Set(BigInt n, signed long init);
void BigInt_SetU(BigInt n, unsigned long init);
signed long BigInt_Get(BigInt n);
unsigned long BigInt_GetU(BigInt n);
int BigInt_Compare(BigInt a, BigInt b);
BigInt BigInt_Zero();
BigInt BigInt_One();

/* Mathematical operator functions */
void BigInt_Add(BigInt a, BigInt b, BigInt answer);
void BigInt_Subtract(BigInt a, BigInt b, BigInt answer);
void BigInt_Multiply(BigInt a, BigInt b, BigInt answer);
int  BigInt_Divide(BigInt a, BigInt b, BigInt answer, BigInt remainder);
void BigInt_Power(BigInt n, BigInt exp, BigInt answer);

/* Logical operator functions */
void BigInt_And(BigInt a, BigInt b, BigInt answer);
void BigInt_Or(BigInt a, BigInt b, BigInt answer);
void BigInt_Xor(BigInt a, BigInt b, BigInt answer);
void BigInt_Shift(BigInt n, int places, BigInt answer); /* Negative 'places' shifts right */
void BigInt_Invert(BigInt n);

/* Specialized functions */
void BigInt_Modulus(BigInt n, BigInt mod, BigInt answer);
void BigInt_PowerModulus(BigInt n, BigInt exp, BigInt modulus, BigInt answer);
void BigInt_GCD(BigInt n, BigInt m, BigInt answer);
int  BigInt_ModularInverse(BigInt n, BigInt m, BigInt answer);
int  BigInt_IsEven(BigInt n);
int  BigInt_IsOdd(BigInt n);
int  BigInt_IsZero(BigInt n);
int  BigInt_IsOne(BigInt n);
void BigInt_FromString(const char *string, BigInt target);

/*
	------------
	CRC Function
	------------

	Note that this function does not release its allocated memory (table32). The
	code assumes that the operating system releases all of a program's allocated
	memory when the program exits. If your system does not, you must explicitly
	add a function to release it, and call it before your program exits.
*/

typedef unsigned long CRC32;
const CRC32 NewCRC32=0xFFFFFFFF;

static unsigned long reflect(unsigned long source, int b) {
	unsigned long sourcemask=0x01, targetmask=(0x01 << (b-1)), target=0;
	while (targetmask) {
		if (source & sourcemask) target|=targetmask;
		sourcemask<<=1;
		targetmask>>=1;
	};
	return target;
};

static CRC32 *table32=0;

/* 'calc' is the macro for the actual CRC calculations. */
#define calc(crc, table, c) { crc=table[alphamask&(*c^crc)]^(crc>>8); }

CRC32 crc32(const char *s, unsigned long length, CRC32 crc) {
	const int BITS=32;
	const int alphabits=8;						/* Number of bits in a character */
	const int alphabet=(1L<<alphabits);			/* Number of symbols in table */
	const int alphamask=(alphabet-1);			/* Mask for these bits */
	const CRC32 poly32=0x04C11DB7;				/* CRC32 standard */
	const CRC32 topbit=(CRC32)(1L<<(BITS-1));
	const char *c, *e;
	int x, b;
	CRC32 r;

	if (!table32) {
		table32=(CRC32*)malloc(alphabet*sizeof(CRC32));
		for (x=0; x<alphabet; ++x) {
			r=reflect(x, alphabits) << (BITS-alphabits);
			for (b=0; b<alphabits; ++b) if (r&topbit) r=(r<<1)^poly32; else r<<=1;
			table32[x]=(CRC32)(reflect(r, BITS));
		};
	};

	for (c=s, e=s+length; c<e; ++c) calc(crc, table32, c);
	return crc;
};

/*
	--------
	MD5 code
	--------

	An implementation of the RSA MD5 algorithm, a cryptographically secure
	hashing algorithm that produces a 128-bit hash value from input of an
	arbitrary length. Used for the ShortV3 key system.
*/

#define RotateLeft(x,n) (((x) << n) | ((x) >> (32-n)))
#define FF(A,B,C,D,X,S,T) (RotateLeft(((B & C)|(~B & D))+A+X+T, S)+B)
#define GG(A,B,C,D,X,S,T) (RotateLeft(((B & D)|(C & ~D))+A+X+T, S)+B)
#define HH(A,B,C,D,X,S,T) (RotateLeft((B^C^D)+A+X+T, S)+B)
#define II(A,B,C,D,X,S,T) (RotateLeft((C^ (B | ~D))+A+X+T, S)+B)

static void TransformBlock(unsigned long *i, const unsigned char *in) {
	const int s1[]={ 7, 12, 17, 22 };
	const int s2[]={ 5, 9, 14, 20 };
	const int s3[]={ 4, 11, 16, 23 };
	const int s4[]={ 6, 10, 15, 21 };

	unsigned long a=i[0], b=i[1], c=i[2], d=i[3], X[16], *dp=X;
	const unsigned char *p=in, *in_end=p+64;

	/* Transfer it to the unsigned long array, in reverse-byte format */
	while (p<in_end) {
		*dp++=((unsigned long)(*(p+0)))|((unsigned long)(*(p+1))<<8)|((unsigned long)(*(p+2))<<16)|((unsigned long)(*(p+3))<<24);
		p+=4;
	};

	/* Round 1 */
	a=FF(a, b, c, d, X[ 0], s1[0], 0xd76aa478);
	d=FF(d, a, b, c, X[ 1], s1[1], 0xe8c7b756);
	c=FF(c, d, a, b, X[ 2], s1[2], 0x242070db);
	b=FF(b, c, d, a, X[ 3], s1[3], 0xc1bdceee);
	a=FF(a, b, c, d, X[ 4], s1[0], 0xf57c0faf);
	d=FF(d, a, b, c, X[ 5], s1[1], 0x4787c62a);
	c=FF(c, d, a, b, X[ 6], s1[2], 0xa8304613);
	b=FF(b, c, d, a, X[ 7], s1[3], 0xfd469501);
	a=FF(a, b, c, d, X[ 8], s1[0], 0x698098d8);
	d=FF(d, a, b, c, X[ 9], s1[1], 0x8b44f7af);
	c=FF(c, d, a, b, X[10], s1[2], 0xffff5bb1);
	b=FF(b, c, d, a, X[11], s1[3], 0x895cd7be);
	a=FF(a, b, c, d, X[12], s1[0], 0x6b901122);
	d=FF(d, a, b, c, X[13], s1[1], 0xfd987193);
	c=FF(c, d, a, b, X[14], s1[2], 0xa679438e);
	b=FF(b, c, d, a, X[15], s1[3], 0x49b40821);

	/* Round 2 */
	a=GG(a, b, c, d, X[ 1], s2[0], 0xf61e2562);
	d=GG(d, a, b, c, X[ 6], s2[1], 0xc040b340);
	c=GG(c, d, a, b, X[11], s2[2], 0x265e5a51);
	b=GG(b, c, d, a, X[ 0], s2[3], 0xe9b6c7aa);
	a=GG(a, b, c, d, X[ 5], s2[0], 0xd62f105d);
	d=GG(d, a, b, c, X[10], s2[1], 0x02441453);
	c=GG(c, d, a, b, X[15], s2[2], 0xd8a1e681);
	b=GG(b, c, d, a, X[ 4], s2[3], 0xe7d3fbc8);
	a=GG(a, b, c, d, X[ 9], s2[0], 0x21e1cde6);
	d=GG(d, a, b, c, X[14], s2[1], 0xc33707d6);
	c=GG(c, d, a, b, X[ 3], s2[2], 0xf4d50d87);
	b=GG(b, c, d, a, X[ 8], s2[3], 0x455a14ed);
	a=GG(a, b, c, d, X[13], s2[0], 0xa9e3e905);
	d=GG(d, a, b, c, X[ 2], s2[1], 0xfcefa3f8);
	c=GG(c, d, a, b, X[ 7], s2[2], 0x676f02d9);
	b=GG(b, c, d, a, X[12], s2[3], 0x8d2a4c8a);

	/* Round 3 */
	a=HH(a, b, c, d, X[ 5], s3[0], 0xfffa3942);
	d=HH(d, a, b, c, X[ 8], s3[1], 0x8771f681);
	c=HH(c, d, a, b, X[11], s3[2], 0x6d9d6122);
	b=HH(b, c, d, a, X[14], s3[3], 0xfde5380c);
	a=HH(a, b, c, d, X[ 1], s3[0], 0xa4beea44);
	d=HH(d, a, b, c, X[ 4], s3[1], 0x4bdecfa9);
	c=HH(c, d, a, b, X[ 7], s3[2], 0xf6bb4b60);
	b=HH(b, c, d, a, X[10], s3[3], 0xbebfbc70);
	a=HH(a, b, c, d, X[13], s3[0], 0x289b7ec6);
	d=HH(d, a, b, c, X[ 0], s3[1], 0xeaa127fa);
	c=HH(c, d, a, b, X[ 3], s3[2], 0xd4ef3085);
	b=HH(b, c, d, a, X[ 6], s3[3], 0x04881d05);
	a=HH(a, b, c, d, X[ 9], s3[0], 0xd9d4d039);
	d=HH(d, a, b, c, X[12], s3[1], 0xe6db99e5);
	c=HH(c, d, a, b, X[15], s3[2], 0x1fa27cf8);
	b=HH(b, c, d, a, X[ 2], s3[3], 0xc4ac5665);

	/* Round 4 */
	a=II(a, b, c, d, X[ 0], s4[0], 0xf4292244);
	d=II(d, a, b, c, X[ 7], s4[1], 0x432aff97);
	c=II(c, d, a, b, X[14], s4[2], 0xab9423a7);
	b=II(b, c, d, a, X[ 5], s4[3], 0xfc93a039);
	a=II(a, b, c, d, X[12], s4[0], 0x655b59c3);
	d=II(d, a, b, c, X[ 3], s4[1], 0x8f0ccc92);
	c=II(c, d, a, b, X[10], s4[2], 0xffeff47d);
	b=II(b, c, d, a, X[ 1], s4[3], 0x85845dd1);
	a=II(a, b, c, d, X[ 8], s4[0], 0x6fa87e4f);
	d=II(d, a, b, c, X[15], s4[1], 0xfe2ce6e0);
	c=II(c, d, a, b, X[ 6], s4[2], 0xa3014314);
	b=II(b, c, d, a, X[13], s4[3], 0x4e0811a1);
	a=II(a, b, c, d, X[ 4], s4[0], 0xf7537e82);
	d=II(d, a, b, c, X[11], s4[1], 0xbd3af235);
	c=II(c, d, a, b, X[ 2], s4[2], 0x2ad7d2bb);
	b=II(b, c, d, a, X[ 9], s4[3], 0xeb86d391);

	/* Add the transformed values to the current checksum */
	i[0]+=a;
	i[1]+=b;
	i[2]+=c;
	i[3]+=d;
};

static void md5(unsigned long *i, const void *bytes, unsigned long length) {
	const unsigned char *p=(const unsigned char *)bytes;
	unsigned long bytesremaining=length, d;
	unsigned char buffer[128], *b;

	/* Initialize the MD5 values */
	i[0]=0x67452301;
	i[1]=0xefcdab89;
	i[2]=0x98badcfe;
	i[3]=0x10325476;

	/* Do the transform on the initial data, up to the last block */
	while (bytesremaining>64) {
		TransformBlock(i, p);
		bytesremaining-=64;
		p+=64;
	};

	/* Pad the block according to the MD5 spec */
	memset(buffer, 0, 128);
	memcpy(buffer, p, bytesremaining);
	buffer[bytesremaining++]=0x80;

	/*
	** Add the 64-bit size to the end of the first block if there's room,
	** otherwise the second. This function is designed to handle a maximum
	** byte length of 4GB, which should be plenty for our purposes.
	*/
	if (bytesremaining<=56) {
		/* There's room. Only need one added group. */
		/*
		Can't use these two lines, because they don't work on big-endian
		*(unsigned long*)(buffer+56)=(length<<3);
		*(unsigned long*)(buffer+60)=(length>>29);
		*/

		b=buffer+56;
		d=length<<3;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		d=length>>29;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;

		TransformBlock(i, buffer);
	} else {
		/* Not enough room, we'll have to spill over to a second block. */
		/*
		Can't use these two lines, because they don't work on big-endian
		*(unsigned long*)(buffer+120)=(length<<3);
		*(unsigned long*)(buffer+124)=(length>>29);
		*/

		b=buffer+120;
		d=length<<3;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		d=length>>29;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;
		*b++=(unsigned char)(d&0xFF); d>>=8;

		TransformBlock(i, buffer);
		TransformBlock(i, buffer+64);
	};

	/*
	** And we're done. Normally we would have to do some extra work to spit out
	** the MD5 information, low-byte first in A,B,C,D order (step 5 of the
	** description), but I only need it for binary uses, so the four unsigned
	** longs are enough.
	*/
};

/*
	-----------------------
	Miscellaneous Functions
	-----------------------
*/

void CookText(char *target, const char *source) {
	/* Not using toupper() because certain high-ASCII (non-English) characters
	are processed differently after certain DLLs are loaded... it's better
	to have reliability in this function. */
	const char *s=source;
	char *t=target;
	while (*s) {
		if (*s==' ' || *s=='\t' || *s=='\r' || *s=='\n') ++s;
		else if (*s>='a' && *s<='z') *t++=((*s++)-'a'+'A');
		else *t++=*s++;
	};
	*t=0;
};

/*
static void CookText(char *target, const char *source) {
	const char *s=source;
	char *t=target;
	while (*s) {
		if (*s==' ') ++s;
		else *t++=toupper(*s++);
	};
	*t=0;
};
*/

/* Armadillo does NOT use time-zone stuff. The NoTimeZoneStuff() call is
designed to clear out the time-zone and daylight-savings-time differences. It's
not strictly necessary, since Armadillo allows for a variation of a day, and
may not be portable (thus the #ifdefs). */
#ifdef _WIN32
	void NoTimeZoneStuff() {
		static int firstrun=1;
		if (firstrun) {
			_timezone=0;
			putenv("TZ=GMT0");
			firstrun=0;
		};
	};
#else
	#define NoTimeZoneStuff()
#endif

static unsigned short GetToday() {
	#ifdef FOR_TESTING
		/* This line for debugging only -- 1791 is US Thanksgiving day, 2003. */
		return 1791;
	#else
		const unsigned long secondsperday=(24*60*60);
		const int dateoffset=10592; /* Difference (in days) between 01Jan70 and 01Jan99 */
		unsigned long days;

		NoTimeZoneStuff();

		days=(time(NULL)/secondsperday);
		return (unsigned short)(days-dateoffset);
	#endif
};

static void InterpretDate(unsigned short keymade, unsigned short *year, unsigned short *month, unsigned short *day) {
	const unsigned long secondsperday=(24*60*60);
	const int dateoffset=10592; /* Difference (in days) between 01Jan70 and 01Jan99 */
	time_t xtime;
	struct tm *tm;

	NoTimeZoneStuff();
	xtime=(keymade+dateoffset)*secondsperday+(secondsperday/2);
	tm=gmtime(&xtime);
	if (tm) {
		if (year) *year=tm->tm_year+1900;
		if (month) *month=tm->tm_mon+1;
		if (day) *day=tm->tm_mday;
	};
};

unsigned long hextoint(const char *string) {
	unsigned long r=0;
	const char *c=string;
	while (*c) {
		if (*c>='0' && *c<='9') r=(r*16)+(*c-'0');
		else if (*c>='a' && *c<='f') r=(r*16)+(*c-'a')+10;
		else if (*c>='A' && *c<='F') r=(r*16)+(*c-'A')+10;
		++c;
	};
	return r;
};



/*
	-------------
	GetRandomSeed
	-------------

	The GetRandomSeed function is designed to seed the random number generator.
	For compatibility with various standard C libraries, we can only make a
	unique seed once every second. If you need to create signed keys faster
	than that, and ensure that they are unique, then you'll have to customize
	this function to either use something that increments more quickly, or that
	stores the result somewhere to ensure that it never returns the same value
	twice. We've included a preprocessor definition, USECLOCKTICKS, that
	attempts to do this using the clock() function, but it may not work on all
	platforms.
*/

static unsigned long GetRandomSeed() {
	#ifdef FOR_TESTING
		return 1000;
	#else
		#ifdef USECLOCKTICKS
			return time(0)+clock();
		#else
			return time(0);
		#endif
	#endif
};



/*
	-------------------------------
	Pseudo-Random Number Generators
	-------------------------------
*/

#define m 100000000L
#define m1 10000L
#define b 31415821L

static unsigned long a;

/*
Original
static unsigned long mult(long p, long q) {
	unsigned long p1=p/m1, p0=p%m1, q1=q/m1, q0=q%m1;
	return (((p0*q1+p1*q0) % m1) * m1+p0*q0) % m;
};

Works in 64 environment
static unsigned long mult(long p, long q) {
	unsigned long p1=p/m1, p0=p%m1, q1=q/m1, q0=q%m1;
	unsigned long t = p0*q1;
	unsigned long t1 = p1*q0;
	unsigned long t2 = p0*q0;
	unsigned long r = (t + t1) % m1;
	r = r * m1;
	r = (r + t2)%m;
	return r;
};
*/
static unsigned long mult(long p, long q) {
	unsigned long p1=p/m1, p0=p%m1, q1=q/m1, q0=q%m1;
	unsigned long t1=p0*q1, t2=p1*q0, t3=p0*q0;
	unsigned long r=(t1+t2)%m1; r*=m1; r+=t3; r%=m;
	return r;
};

static void InitRandomGenerator(unsigned long seed) {
	a=seed;
};

static unsigned long NextRandomRange(long range) {
	a=(mult(a, b)+1) % m;
	return (((a/m1)*range)/m1);
};

static unsigned long NextRandomNumber() {
	long n1=NextRandomRange(256);
	long n2=NextRandomRange(256);
	long n3=NextRandomRange(256);
	long n4=NextRandomRange(256);
	return (n1<<24)|(n2<<16)|(n3<<8)|n4;
};

/* Improved version, for ECC keys */

static unsigned long aa[4];

static void InitRandomGenerator128(unsigned long *seed) {
	memcpy(aa, seed, sizeof(unsigned long)*4);
};

static void NextRandomNumber128(unsigned long *i) {
	/* Take the existing four double-words and print some form of them to a
	string. Then do the same with a new seed value. Then create the MD5
	signature of that string -- that's the new 128-bit number. */
	unsigned long ii[5];
	char string[256], *c;
	int x, y;

	memcpy(ii, aa, sizeof(unsigned long)*4);
	ii[4]=GetRandomSeed();

	c=string;
	for (x=0; x<5; ++x) for (y=0; y<8; ++y) { *c++=(char)('A' + (ii[x] & 0x0F)); ii[x]>>=4; };
	md5(aa, string, c-string);
	memcpy(i, aa, sizeof(unsigned long)*4);
};

#undef b
#undef m1
#undef m


/*
	---------------
	Encryption Code
	---------------

	The decryption code is also included here, although it isn't needed for
	creating keys.
*/

typedef struct CipherKeyStruct {
	unsigned long S[4][256];
	unsigned long P[18];
} CipherKey;

const int MAXKEYBYTES=56; /* 448-bit maximum key; additional bits ignored. */
const int N=16;

static unsigned long F(CipherKey *bc, unsigned long x) {
	return ((bc->S[0][(x>>24)&0xFF] + bc->S[1][(x>>16)&0xFF])
		^ bc->S[2][(x>>8)&0xFF]) + bc->S[3][x&0xFF];
};

static void encipher(CipherKey *c, unsigned long *xl, unsigned long *xr) {
	unsigned long Xl=*xl, Xr=*xr, temp;
	short i;

	for (i=0; i<N; ++i) { Xl=Xl^c->P[i]; Xr=F(c, Xl)^Xr; temp=Xl; Xl=Xr; Xr=temp; };
	temp=Xl; Xl=Xr; Xr=temp;
	Xr=Xr^c->P[N]; Xl=Xl^c->P[N+1];
	*xl=Xl; *xr=Xr;
};

static void decipher(CipherKey *c, unsigned long *xl, unsigned long *xr) {
	unsigned long Xl=*xl, Xr=*xr, temp;
	short i;

	for (i=N+1; i>1; --i) { Xl=Xl^c->P[i]; Xr=F(c, Xl)^Xr; temp=Xl; Xl=Xr; Xr=temp; };
	temp=Xl; Xl=Xr; Xr=temp;
	Xr=Xr^c->P[1]; Xl=Xl^c->P[0];
	*xl=Xl; *xr=Xr;
};

static void initialize(CipherKey *c, const char *keybytes, int keylength, unsigned long seed) {
	int i, j, k;

	const unsigned long ps[18]={
		0x243f6a88, 0x85a308d3, 0x13198a2e, 0x03707344, 0xa4093822, 0x299f31d0,
		0x082efa98, 0xec4e6c89, 0x452821e6, 0x38d01377, 0xbe5466cf, 0x34e90c6c,
		0xc0ac29b7, 0xc97c50dd, 0x3f84d5b5, 0xb5470917, 0x9216d5d9, 0x8979fb1b,
	};
	unsigned long datal=0, datar=0;

	/* Initialize P array */
	for(i=0; i<18; ++i) c->P[i]=ps[i];

	/* Initialize S-boxes with pseudo-random number generator */
	InitRandomGenerator(seed);
	for (i=0; i<4; ++i) for (j=0; j<256; ++j) c->S[i][j]=NextRandomNumber();

	for (i=0, j=0; i<N+2; ++i) {
		unsigned long data=0;
		for (k=0; k<4; ++k) { data=(data<<8)|keybytes[j]; if (++j>=keylength) j=0; };
		c->P[i]^=data;
	};

	#ifdef DEBUG
		printf("PData:\n");
		for (i=0; i<N+2; i+=2) {
			encipher(c, &datal, &datar);
			c->P[i]=datal;
			c->P[i+1]=datar;

			printf("    datal=%08X, datar=%08X\n", datal, datar);
		};

		printf("\nSData:\n");
		for (i=0; i<4; ++i) for (j=0; j<256; j+=2) {
			encipher(c, &datal, &datar);
			c->S[i][j]=datal;
			c->S[i][j+1]=datar;

			printf("    datal=%08X, datar=%08X\n", datal, datar);
		};
	#else
		for (i=0; i<N+2; i+=2) { encipher(c, &datal, &datar); c->P[i]=datal; c->P[i+1]=datar; };
		for (i=0; i<4; ++i) for (j=0; j<256; j+=2) { encipher(c, &datal, &datar); c->S[i][j]=datal; c->S[i][j+1]=datar; };
	#endif
};

static CipherKey *CreateCipherKey(const char *keybytes, int length) {
	CipherKey *newkey=(CipherKey*)malloc(sizeof(CipherKey));
	initialize(newkey, keybytes, length, 0x31415921);
	return newkey;
};

static void ReleaseCipherKey(CipherKey *key) {
	free(key);
};

static void Encipher(CipherKey *key, char *buffer, int length) {
	unsigned long *p, *e;
	length&=(~0x07); /* Round down to the next-lower multiple of 8 bytes */
	for (p=(unsigned long *)buffer, e=p+(length/4); p<e; p+=2) encipher(key, p, p+1);
};

static void Decipher(CipherKey *key, char *buffer, int length) {
	unsigned long *p, *e;
	length&=(~0x07); /* Round down to the next-lower multiple of 8 bytes */
	for (p=(unsigned long *)buffer, e=p+(length/4); p<e; p+=2) decipher(key, p, p+1);
};

/*
	---------
	CreateKey
	---------

	This is the only function that needs to be externally visible for unsigned
	keys. The "regname" parameter is the name of the person to make the key for;
	it's used as the encryption key for the other information.

	The "keytext" parameter is the "encryption template" for the appropriate
	security certificate -- see the Armadillo documentation for details.

	The "otherinfo" parameter can specify the number of days and/or uses this
	key permits, or the expiration date of the key (in days since 01Jan1999),
	or the version number to expire on, or the number of copies to allow. The
	meaning depends on the certificate. In most cases, the certificate itself
	will specify values for these parameters, and you can leave this at zero.
	If the certificate specifies values for these parameters, the "otherinfo"
	is ignored.

	hardwareID is used only for hardware-locked certificates, and can be set to
	zero for anything else.

	The only cautions for this function... it expects both "regname" and
	"keytext" to be less than 256 bytes, in the calls to CookText(). You may
	wish to confirm that before calling CreateKey().

	To confirm it: CreateKey("Chad Nelson", "Testing", 14, 0) should return a
	key of F806-3E6F-0A27-D091 on 20Jan1999.
*/

const char *CreateKey(const char *regname, const char *keytext, unsigned short otherinfo, unsigned long hardwareID) {
	static char returntext[25];
	CipherKey *cipherkey;
	unsigned long k[2];
	char cooked[512];

	if (*regname==0) return "NoNameError";

	CookText(cooked, keytext);
	k[0]=((unsigned long)crc32(cooked, strlen(cooked), NewCRC32))^hardwareID^HWIDXOR;
	k[1]=(GetToday()<<16)|otherinfo;

	/* Encrypt the key information */
	CookText(cooked, regname);
	cipherkey=CreateCipherKey(cooked, strlen(cooked));
	Encipher(cipherkey, (char*)k, 2*sizeof(unsigned long));
	ReleaseCipherKey(cipherkey);

	/* Format and return it! */
	sprintf(returntext, "%04X-%04X-%04X-%04X", k[0]>>16, k[0]&0xFFFF, k[1]>>16, k[1]&0xFFFF);
	return returntext;
};

/*
	--------------------
	The BigInt functions
	--------------------
*/

/* private */
void BigInt_Realloc(BigInt n, int newcount, int copydata) {
	if (newcount<0) newcount=0;
	if (newcount < n->alloc) {
		if (copydata) {
			if (newcount > n->length) memset(n->digits+n->length, 0, (newcount-n->length)*sizeof(DIGIT));
			n->length=newcount;
		} else {
			n->length=newcount;
			memset(n->digits, 0, n->length*sizeof(DIGIT));
		};
	} else if (copydata) {
		DIGIT *olddigits=n->digits;
		n->digits=(DIGIT*)malloc(newcount*sizeof(DIGIT));
		memcpy(n->digits, olddigits, n->length*sizeof(DIGIT));
		memset(n->digits+n->length, 0, (newcount-n->length)*sizeof(DIGIT));
		n->length=n->alloc=newcount;
		free(olddigits);
	} else {
		free(n->digits);
		n->length=n->alloc=newcount;
		n->digits=(DIGIT*)malloc(newcount*sizeof(DIGIT));
		memset(n->digits, 0, n->length*sizeof(DIGIT));
	};
};

/* private */
void BigInt_FindMSD(BigInt n) {
	DIGIT *d=n->digits+n->length-1;
	while (d>n->digits && *d==0) --d;
	n->length=(d-n->digits)+1;
	/*
	if (n->length==0) {
		if (n->alloc<1) BigInt_Realloc(n, 1, 0);
		n->length=1;
	};
	*/
	if (n->length==0 || (n->length==1 && n->digits[0]==0)) n->negative=0;
};

/* private */
int BigInt_Compare_SignOptional(BigInt b1, BigInt b2, int ignoresign) {
	int z1=0, z2=0, answer=0, x;

	if (!ignoresign) {
		/* Are b1 and/or b2 zero? */
		if (b1->length==0 || (b1->length==1 && b1->digits[0]==0)) z1=1;
		if (b2->length==0 || (b2->length==1 && b2->digits[0]==0)) z2=1;

		if (z1 && z2) return 0;
		if (z1) return b2->negative ? 1 : -1;
		if (z2) return b1->negative ? -1 : 1;

		if (b1->negative!=b2->negative) return (b1->negative ? -1 : 1);
	};

	if (b1->length!=b2->length) {
		answer=((b1->length < b2->length) ? -1 : 1);
	} else {
		for (x=b1->length-1; !answer && x>=0; --x) answer=b1->digits[x]-b2->digits[x];
	};

	if (!ignoresign && b1->negative) return -answer;
	return answer;
};

/* private */
#ifdef DEBUG
void BigInt_Dump(BigInt n, const char *title) {
	int x;
	if (title && *title) printf("%s\n", title);
	printf("Dump: length=%d, negative=%s\n", n->length, n->negative ? "true" : "false");
	#if BITS_PER_DIGIT==8
		for (x=0; x<n->length; x+=2) printf("    Digit %d: %02X%02X\n", x, x+1<n->length ? n->digits[x+1] : 0, n->digits[x]);
	#else
		for (x=0; x<n->length; ++x) printf("    Digit %d: %04X\n", x, n->digits[x]);
	#endif
};
#endif

int  BigInt_IsEven(BigInt n) {
	if (n->length<1) return 1;
	return !(n->digits[0] & 0x01);
};

int  BigInt_IsOdd(BigInt n) {
	if (n->length<1) return 0;
	return (n->digits[0] & 0x01);
};

int  BigInt_IsZero(BigInt n) {
	return (n->length==0 || (n->length==1 && n->digits[0]==0));
};

int  BigInt_IsOne(BigInt n) {
	return (n->length==1 && n->digits[0]==1);
};

BigInt BigInt_Create() {
	struct BigIntBase *b=(struct BigIntBase *)malloc(sizeof(struct BigIntBase));
	b->length=b->alloc=0;
	b->negative=0;
	b->digits=0;
	return b;
};

void BigInt_Destroy(BigInt n) {
	if (n->digits) free(n->digits);
	free(n);
};

void BigInt_Copy(BigInt target, BigInt source) {
	BigInt_Realloc(target, source->length, 0);
	target->negative=source->negative;
	memcpy(target->digits, source->digits, source->length*sizeof(DIGIT));
};

void BigInt_Set(BigInt n, signed long init) {
	int neg=0;
	if (init<0) { neg=1; init=-init; };
	BigInt_SetU(n, init);
	n->negative=neg;
};

void BigInt_SetU(BigInt n, unsigned long init) {
	int index;

	BigInt_Realloc(n, sizeof(unsigned long)/sizeof(DIGIT), 0);
	for (index=0; init; ++index) {
		n->digits[index]=(DIGIT)(init&DIGIT_MASK);
		init=init>>BITS_PER_DIGIT;
	};
	BigInt_FindMSD(n);
};

signed long BigInt_Get(BigInt n) {
	signed long value=BigInt_GetU(n);
	if (value<0) value=-value;
	if (n->negative) value=-value;
	return value;
};

unsigned long BigInt_GetU(BigInt n) {
	unsigned long value=0;
	int x;

	for (x=(sizeof(unsigned long)/sizeof(DIGIT))-1; x>=0; --x) {
		value<<=BITS_PER_DIGIT;
		if (x<n->length) value|=n->digits[x];
	};

	return value;
};

BigInt BigInt_Zero() {
	static BigInt zero=0;
	if (!zero) zero=BigInt_Create();
	return zero;
};

BigInt BigInt_One() {
	static BigInt one=0;
	if (!one) {
		one=BigInt_Create();
		BigInt_Set(one, 1);
	};
	return one;
};

int BigInt_Compare(BigInt a, BigInt b) {
	return BigInt_Compare_SignOptional(a, b, 0);
};

void BigInt_Add(BigInt a, BigInt b, BigInt answer) {
	DIGIT *ad, *bd, *ansd;
	int level=0, x, carry;
	WORKING_DIGIT n;
	BigInt savedb;

	/* Check for zeros */
	if (a->length==0 || (a->length==1 && a->digits[0]==0)) {
		BigInt_Copy(answer, b);
		return;
	} else if (b->length==0 || (b->length==1 && b->digits[0]==0)) {
		BigInt_Copy(answer, a);
		return;
	};

	/* Handle mismatched signs, step 1 */
	if (a->negative!=b->negative) {
		savedb=BigInt_Create();
		BigInt_Copy(savedb, b);

		/* Bug fix. If 'a' and 'b' aren't the same length, we need to expand
		the shorter one to the same size as the longer one before we invert it.
		This was the original source of the invert problem. */
		if (b->length<a->length) BigInt_Realloc(b, a->length, 1);
		else if (a->length<b->length) BigInt_Realloc(a, b->length, 1);

		level=b->length;
		BigInt_Invert(b);
	};

	/* Make the numbers both the same size */
	if (a->length!=b->length) {
		if (a->length > b->length) BigInt_Realloc(b, a->length, 1);
		else BigInt_Realloc(a, b->length, 1);
	};

	/* Allocate one more digit for the answer */
	BigInt_Realloc(answer, a->length+1, 0);
	answer->negative=a->negative;

	carry=0;
	ad=a->digits;
	bd=b->digits;
	ansd=answer->digits;
	for (x=0; x<a->length; ++x) {
		n=(WORKING_DIGIT)(*ad++)+(WORKING_DIGIT)(*bd++)+carry;

		if (n>=OVERFLOW_DIGIT) {
			carry=1;
			*ansd++=(DIGIT)(n-OVERFLOW_DIGIT);
		} else {
			carry=0;
			*ansd++=(DIGIT)(n);
		};
	};
	*ansd=carry;

	/* Find the most significant digits, for efficiency */
	BigInt_FindMSD(answer);
	BigInt_FindMSD(b);
	BigInt_FindMSD(a);

	if (level!=0) {
		/* Handle mismatched signs, step 2 */
		BigInt_Copy(b, savedb);
		BigInt_Destroy(savedb);

		if (answer->length > level) {
			--answer->digits[level];
			BigInt_FindMSD(answer);
		} else {
			BigInt_Realloc(answer, level, 1);
			BigInt_Invert(answer);

			#ifdef DEBUG1
			BigInt_Dump(answer, "inverted, step 2");
			#endif
		};
	};
};

void BigInt_Subtract(BigInt a, BigInt b, BigInt answer) {
	b->negative=!b->negative;
	BigInt_Add(a, b, answer);
	b->negative=!b->negative;
};

void BigInt_Multiply(BigInt a, BigInt b, BigInt answer) {
	int carry, digit1, digit2, digita;
	DIGIT *ad, *ae, *bd, *be, *ansd;
	WORKING_DIGIT t, addt;

	/* If the numbers are the same, use square instead -- more efficient */
	/*x*/

	/* Allocate the appropriate number of digits */
	BigInt_Realloc(answer, a->length+b->length+1, 0);

	/* Multiply the digits, starting at the least-significant one */
	for (ad=a->digits, ae=ad+a->length, digit1=0; ad<ae; ++ad, ++digit1) {
		for (bd=b->digits, be=bd+b->length, digit2=0; bd<be; ++bd, ++digit2) {
			/* Multiply the digits and add the result to the answer */
			carry=0;
			digita=digit1+digit2;
			ansd=answer->digits+digita;

			t=(*ad)*(*bd);
			addt=(*ansd)+(t & DIGIT_MASK);
			if (addt >= OVERFLOW_DIGIT) carry=1;
			(*ansd++)=(DIGIT)(addt);

			addt=(*ansd)+((t>>BITS_PER_DIGIT)&DIGIT_MASK)+carry;
			if (addt >= OVERFLOW_DIGIT) carry=1; else carry=0;
			(*ansd++)=(DIGIT)(addt);

			while (carry) {
				addt=(*ansd)+1;
				(*ansd++)=(DIGIT)addt;
				if (addt < OVERFLOW_DIGIT) break;
			};
		};
	};

	answer->negative=(a->negative ^ b->negative);
	BigInt_FindMSD(answer);
};

int BigInt_Divide(BigInt a, BigInt b, BigInt answer, BigInt remainder) {
	int compare, i, signa, signb;
	WORKING_DIGIT high, low, t;
	BigInt temp1, temp2;

	temp1=BigInt_Create();
	temp2=BigInt_Create();

	signa=a->negative; a->negative=0;
	signb=b->negative; b->negative=0;

	/* Check for divide-by-zero, it's not allowed */
	if (b->length==1 && b->digits[0]==0) return 0;

	/* Compare a and b, to see if we can take a shortcut */
	compare=BigInt_Compare_SignOptional(a, b, 1);
	if (compare<0) {
		BigInt_Set(answer, 0);
		BigInt_Copy(remainder, a);
		return 1;
	} else if (compare==0) {
		BigInt_Set(answer, 1);
		BigInt_Set(remainder, 0);
		return 1;
	};

	BigInt_Realloc(answer, a->length, 0);
	BigInt_Set(remainder, 0);
	for (i=1; i<=a->length; ++i) {
		/* remainder=(remainder<<BITS_PER_DIGIT)+a->digits[a->length-i]; */
		BigInt_Copy(temp1, remainder);
		BigInt_Shift(temp1, BITS_PER_DIGIT, remainder);
		remainder->digits[0]=a->digits[a->length-i];

		if (BigInt_Compare_SignOptional(remainder, b, 1)>=0) {
			high=OVERFLOW_DIGIT;
			low=0;
			while (low<high) {
				t=((high-low)/2)+low;

				/* if ((b*t)>remainder) high=t; else low=t+1; */
				BigInt_Set(temp2, t);
				BigInt_Multiply(b, temp2, temp1);
				if (BigInt_Compare(temp1, remainder)>0) high=t; else low=t+1;
			};
			t=low-1;
			answer->digits[a->length-i]=(DIGIT)(t);

			/* remainder=remainder-(b*t) */
			BigInt_Set(temp2, t);
			BigInt_Multiply(b, temp2, temp1);
			BigInt_Subtract(remainder, temp1, temp2);
			BigInt_Copy(remainder, temp2);
		} else answer->digits[a->length-i]=0;
	};

	a->negative=signa;
	b->negative=signb;
	answer->negative=(a->negative ^ b->negative);
	BigInt_FindMSD(answer);
	BigInt_Destroy(temp2);
	BigInt_Destroy(temp1);
	return 1;
};

void BigInt_PowerModulus(BigInt n, BigInt exp, BigInt modulus, BigInt answer) {
	DIGIT *eptr, *eend, emask;
	BigInt p, temp, r;

	/* If n is negative and the exponent is odd, the answer will be negative. */
	int neg=(n->negative && (exp->digits[0]&0x01));

	p=BigInt_Create();
	temp=BigInt_Create();
	if (modulus) r=BigInt_Create();

	BigInt_Copy(p, n);
	p->negative=0;

	BigInt_Set(answer, 1);

	/* Continue this loop while the exponent is not zero */
	eptr=exp->digits;
	eend=eptr+exp->length;
	emask=0x01;
	while (eptr<eend) {
		/* If e is odd, multiply the answer by p */
		if ((*eptr) & emask) {
			BigInt_Copy(temp, answer);
			BigInt_Multiply(temp, p, answer);

			if (modulus) {
				BigInt_Modulus(answer, modulus, r);
				BigInt_Copy(answer, r);
			};
		};

		/* Now square p (mod modulus, if supplied) */
		BigInt_Multiply(p, p, temp);
		if (modulus) BigInt_Modulus(temp, modulus, p);
		else BigInt_Copy(p, temp);

		/* Shift e right by one bit */
		emask<<=1;
		if (emask==0) {
			++eptr;
			emask=0x01;
		};
	};
	answer->negative=neg;

	if (modulus) BigInt_Destroy(r);
	BigInt_Destroy(temp);
	BigInt_Destroy(p);
};

void BigInt_Power(BigInt n, BigInt exp, BigInt answer) {
	BigInt_PowerModulus(n, exp, 0, answer);
};

void BigInt_And(BigInt a, BigInt b, BigInt answer) {
	DIGIT *ansd, *anse, *z;

	if (BigInt_IsZero(a) || BigInt_IsZero(b)) {
		BigInt_Copy(answer, BigInt_Zero());
		BigInt_FindMSD(answer);
		return;
	} else if (a->length >= b->length) {
		BigInt_Copy(answer, a);
		z=b->digits;
	} else {
		BigInt_Copy(answer, b);
		z=a->digits;
	};

	ansd=answer->digits;
	anse=ansd+answer->length;
	while (ansd<anse) (*ansd++)&=(*z++);
	BigInt_FindMSD(answer);
};

void BigInt_Or(BigInt a, BigInt b, BigInt answer) {
	DIGIT *ansd, *anse, *z;

	if (a->length >= b->length) {
		BigInt_Copy(answer, a);
		z=b->digits;
	} else {
		BigInt_Copy(answer, b);
		z=a->digits;
	};

	ansd=answer->digits;
	anse=ansd+answer->length;
	while (ansd<anse) (*ansd++)|=(*z++);
	BigInt_FindMSD(answer);
};

void BigInt_Xor(BigInt a, BigInt b, BigInt answer) {
	DIGIT *ansd, *anse, *z;

	if (a->length >= b->length) {
		BigInt_Copy(answer, a);
		z=b->digits;
	} else {
		BigInt_Copy(answer, b);
		z=a->digits;
	};

	ansd=answer->digits;
	anse=ansd+answer->length;
	while (ansd<anse) (*ansd++)^=(*z++);
	BigInt_FindMSD(answer);
};

void BigInt_Shift(BigInt n, int places, BigInt answer) {
	/* Negative 'places' shifts right */
	int bytes, bits, neg=0, x;

	if (places<0) { neg=1; places=-places; };
	bytes=places/BITS_PER_DIGIT;
	bits=places%BITS_PER_DIGIT;
	answer->negative=n->negative;
	if (bytes) {
		/* Bytes only */
		if (neg) {
			/* Right-shift */
			BigInt_Realloc(answer, n->length-bytes, 0);
			for (x=0; x<n->length-bytes; ++x) answer->digits[x]=n->digits[x+bytes];
		} else {
			/* Left-shift */
			BigInt_Realloc(answer, n->length+bytes+1, 0);
			for (x=0; x<n->length; ++x) answer->digits[x+bytes]=n->digits[x];
		};
	} else BigInt_Copy(answer, n);

	if (bits) {
		if (neg) {
			/* Right-shift */
			for (x=0; x<answer->length; ++x) {
				answer->digits[x]>>=bits;
				if (x+1<answer->length) answer->digits[x]|=answer->digits[x+1]<<(BITS_PER_DIGIT-bits);
			};
		} else {
			/* Left-shift */
			BigInt_Realloc(answer, answer->length+1, 1);
			for (x=answer->length-1; x>=0; --x) {
				answer->digits[x]<<=bits;
				if (x-1>=0) answer->digits[x]|=answer->digits[x-1]>>(BITS_PER_DIGIT-bits);
			};
		};
	};

	BigInt_FindMSD(answer);
};

void BigInt_Invert(BigInt n) {
	WORKING_DIGIT w;
	DIGIT *d, *e;

	d=n->digits;
	e=d+n->length;
	n->negative=!n->negative;
	while (d<e) {
		*d=(DIGIT)(OVERFLOW_DIGIT-1-(*d));
		++d;
	};

	d=n->digits;
	while (d<e) {
		w=(*d)+1;
		(*d++)=(DIGIT)(w);
		if (w<OVERFLOW_DIGIT) break;
	};

	BigInt_FindMSD(n);
};

void BigInt_Modulus(BigInt n, BigInt mod, BigInt answer) {
	BigInt q=BigInt_Create();
	BigInt temp=BigInt_Create();

	if (n->negative) {
		BigInt_Divide(n, mod, q, temp);
		BigInt_Subtract(mod, temp, answer);
	} else if (BigInt_Compare(n, mod)>=0) {
		BigInt_Divide(n, mod, q, answer);
	} else BigInt_Copy(answer, n);

	BigInt_Destroy(temp);
	BigInt_Destroy(q);
};

void BigInt_GCD(BigInt _n, BigInt _m, BigInt answer) {
	BigInt n, m, u1, u2, u3, t1, t2, t3, temp, uninit;
	DIGIT *p, *e, mask;
	int k, t;

	n=BigInt_Create();
	m=BigInt_Create();
	u1=BigInt_Create();
	u2=BigInt_Create();
	u3=BigInt_Create();
	t1=BigInt_Create();
	t2=BigInt_Create();
	t3=BigInt_Create();
	temp=BigInt_Create();

	BigInt_Copy(n, _n);
	BigInt_Copy(m, _m);
	n->negative=m->negative=0;

	/* Factor out any common twos. */
	p=n->digits;
	e=p+n->length;
	t=0;
	while (p<e) {
		mask=0x01;
		while (mask) { if ((*p) & mask) break; mask<<=1; ++t; };
		if (mask) break;
		++p;
	};
	k=t;

	p=m->digits;
	e=p+m->length;
	t=0;
	while (p<e) {
		mask=0x01;
		while (mask) { if ((*p) & mask) break; mask<<=1; ++t; };
		if (mask) break;
		++p;
	};
	if (t<k) k=t;

	if (k) {
		BigInt_Shift(n, -k, temp);
		BigInt_Copy(n, temp);
		BigInt_Shift(m, -k, temp);
		BigInt_Copy(m, temp);
	};

	BigInt_Set(u1, 1);
	BigInt_Set(u2, 0);
	BigInt_Copy(u3, n);
	BigInt_Copy(t1, m);
	BigInt_Subtract(n, BigInt_One(), t2);
	BigInt_Copy(t3, m);
	do {
		do {
			if (!(u3->digits[0] & 0x01)) {
				if ((u1->digits[0] & 0x01) || (u2->digits[0] & 0x01)) {
					BigInt_Add(u1, m, temp); BigInt_Copy(u1, temp);
					BigInt_Add(u2, n, temp); BigInt_Copy(u2, temp);
				};

				BigInt_Shift(u1, -1, temp); BigInt_Copy(u1, temp);
				BigInt_Shift(u2, -1, temp); BigInt_Copy(u2, temp);
				BigInt_Shift(u3, -1, temp); BigInt_Copy(u3, temp);
			};

			if (!(t3->digits[0] & 0x01) || BigInt_Compare(u3, t3)<0) {
				/* Swap the u's with the t's */
				uninit=u1; u1=t1; t1=uninit;
				uninit=u2; u2=t2; t2=uninit;
				uninit=u3; u3=t3; t3=uninit;
			};
		} while (!(u3->digits[0] & 0x01));

		while (BigInt_Compare(u1, t1)<0 || BigInt_Compare(u2, t2)<0) {
			BigInt_Add(u1, m, temp); BigInt_Copy(u1, temp);
			BigInt_Add(u2, n, temp); BigInt_Copy(u2, temp);
		};

		BigInt_Subtract(u1, t1, temp); BigInt_Copy(u1, temp);
		BigInt_Subtract(u2, t2, temp); BigInt_Copy(u2, temp);
		BigInt_Subtract(u3, t3, temp); BigInt_Copy(u3, temp);
	} while (t3->length>1 || t3->digits[0]>0);

	while (BigInt_Compare(u1, m)>=0 && BigInt_Compare(u2, n)>=0) {
		BigInt_Subtract(u1, m, temp); BigInt_Copy(u1, temp);
		BigInt_Subtract(u2, n, temp); BigInt_Copy(u2, temp);
	};

	if (u3->length>1 || u3->digits[0]!=0) {
		BigInt_Shift(u3, k, answer);
	} else {
		BigInt_Shift(BigInt_One(), k, answer);
	};

	BigInt_Destroy(temp);
	BigInt_Destroy(t3);
	BigInt_Destroy(t2);
	BigInt_Destroy(t1);
	BigInt_Destroy(u3);
	BigInt_Destroy(u2);
	BigInt_Destroy(u1);
	BigInt_Destroy(m);
	BigInt_Destroy(n);
};

int BigInt_ModularInverse(BigInt n, BigInt m, BigInt answer) {
	/* Calculates the modular inverse of n mod m, or (n^(-1)) mod m, defined as
	b, where n*b corresponds to 1 (mod m), using the binary extended GCD
	algorithm. */
	BigInt u1, u2, u3, t1, t2, t3, temp, uninit;
	int t;

	if (m->negative) return 0;
	if (n->negative) {
		temp=BigInt_Create();
		n->negative=0;
		t=BigInt_ModularInverse(n, m, temp);
		n->negative=1;
		BigInt_Add(temp, m, answer);
		BigInt_Destroy(temp);
		return t;
	};

	/* If they're both even, then GCD(n,m)!=1, and no inverse is possible. */
	if (BigInt_IsEven(n) && BigInt_IsEven(m)) return 0;

	u1=BigInt_Create();
	u2=BigInt_Create();
	u3=BigInt_Create();
	t1=BigInt_Create();
	t2=BigInt_Create();
	t3=BigInt_Create();
	temp=BigInt_Create();

	BigInt_Set(u1, 1);
	BigInt_Set(u2, 0);
	BigInt_Copy(u3, n);
	BigInt_Copy(t1, m);
	BigInt_Subtract(n, BigInt_One(), t2);
	BigInt_Copy(t3, m);
	do {
		do {
			if (BigInt_IsEven(u3)) {
				if (BigInt_IsOdd(u1) || BigInt_IsOdd(u2)) {
					BigInt_Add(u1, m, temp); BigInt_Copy(u1, temp);
					BigInt_Add(u2, n, temp); BigInt_Copy(u2, temp);
				};

				BigInt_Shift(u1, -1, temp); BigInt_Copy(u1, temp);
				BigInt_Shift(u2, -1, temp); BigInt_Copy(u2, temp);
				BigInt_Shift(u3, -1, temp); BigInt_Copy(u3, temp);
			};

			if (BigInt_IsEven(t3) || BigInt_Compare(u3, t3)<0) {
				/* Swap the u's with the t's */
				uninit=u1; u1=t1; t1=uninit;
				uninit=u2; u2=t2; t2=uninit;
				uninit=u3; u3=t3; t3=uninit;
			};
		} while (BigInt_IsEven(u3));

		while (BigInt_Compare(u1, t1)<0 || BigInt_Compare(u2, t2)<0) {
			BigInt_Add(u1, m, temp); BigInt_Copy(u1, temp);
			BigInt_Add(u2, n, temp); BigInt_Copy(u2, temp);
		};

		BigInt_Copy(temp, u1); BigInt_Subtract(temp, t1, u1);
		BigInt_Copy(temp, u2); BigInt_Subtract(temp, t2, u2);
		BigInt_Copy(temp, u3); BigInt_Subtract(temp, t3, u3);
	} while (BigInt_Compare(t3, BigInt_Zero())>0);

	while (BigInt_Compare(u1, m)>=0 && BigInt_Compare(u2, n)>=0) {
		BigInt_Subtract(u1, m, temp); BigInt_Copy(u1, temp);
		BigInt_Subtract(u2, n, temp); BigInt_Copy(u2, temp);
	};

	t=1;
	if (!BigInt_IsOne(u3)) t=0;
	if (t) BigInt_Copy(answer, u1);

	BigInt_Destroy(temp);
	BigInt_Destroy(t3);
	BigInt_Destroy(t2);
	BigInt_Destroy(t1);
	BigInt_Destroy(u3);
	BigInt_Destroy(u2);
	BigInt_Destroy(u1);

	return t;
};

void BigInt_FromString(const char *string, BigInt target) {
	const char *c=string;
	BigInt t, t2, base;
	int neg=0;

	t=BigInt_Create();
	t2=BigInt_Create();
	base=BigInt_Create();

	BigInt_SetU(base, 10);
	BigInt_Set(target, 0);

	if (*c=='-') { neg=1; ++c; };
	while (*c) {
		if (*c>='0' && *c<='9') {
			BigInt_Set(t, *c-'0');
			BigInt_Multiply(target, base, t2);
			BigInt_Add(t2, t, target);
		} else break;
		++c;
	};

	if (neg) target->negative=1;

	BigInt_Destroy(base);
	BigInt_Destroy(t2);
	BigInt_Destroy(t);
};

/*
	Elliptic-Curve Cryptography code follows. This is the standard Digital
	Signature Algorithm (DSA) modified to use the elliptic-curve discrete
	logarithm problem, rather than the standard one; it provides much stronger
	security for the same number of bits.

	We're using a 113-bit type-2 Koblitz curve ("an elliptic curve whose
	defining equation has coefficients in the binary field F(2)"). This has
	roughly the same strength as 56-bit symmetric encryption, and more than
	512-bit RSA. Solving the Certicom ECC2K-108 challenge (which used a
	slightly weaker curve of the same form) required the equivalent of 500
	years on a single 450MHz machine.

	Note that it is theoretically possible that the very form of Koblitz curves
	may someday allow an attacker to break this scheme much more easily than at
	present. If this ever happens, we'll need to make a new key system before
	someone attacks this one.

	There is already a way to make attacks on it about ten to fifteen times
	easier than it was originally thought, reducing the security by roughly
	four bits; this attack was well-known before the ECC2K-108 challenge was
	solved, and was used in it. This system still provides more than enough
	security against a single attacker, or even a moderately-sized group of
	attackers -- if it takes more than a few weeks of computer time for a
	fifty-person group to crack a key (far larger than any cracking group we
	know of at present), then it's more than strong enough to keep software
	secure against them. This setup should, barring new mathematical
	discoveries, provide enough security to last us until 2010 or 2012 at
	least.
*/

/* The curve parameters we're using. */
#define ECC_NUMBITS	113
#define ECC_TYPE2
#define ECC_PRIMEORDER "5192296858534827627896703833467507"

#ifdef ECC_TYPE2
	#define ECC_FIELDPRIME ((ECC_NUMBITS<<1)+1)
#else
	#define ECC_FIELDPRIME (ECC_NUMBITS+1)
#endif

typedef	short int ECC_INDEX;
typedef unsigned long ECC_ELEMENT;

#define ECC_ELEMENTBITS	(sizeof(ECC_ELEMENT)*8)

#define	ECC_NUMWORD		(ECC_NUMBITS/ECC_ELEMENTBITS)
#define ECC_UPRSHIFT	(ECC_NUMBITS%ECC_ELEMENTBITS)
#define ECC_MAXLONG		(ECC_NUMWORD+1)

#define ECC_MAXBITS		(ECC_MAXLONG*ECC_ELEMENTBITS)
#define ECC_MAXSHIFT	(ECC_ELEMENTBITS-1)
#define ECC_MSB			(1L<<ECC_MAXSHIFT)

#define ECC_UPRBIT		(1L<<(ECC_UPRSHIFT-1))
#define ECC_UPRMASK		(~(-1L<<ECC_UPRSHIFT))
#define ECC_SUMLOOP(i)	for (i=0; i<ECC_MAXLONG; i++)

/* Structures used for ECC functions. */

typedef struct {
	/* The 'e' array must be large enough to accept a 128-bit MD5 signature. */
	ECC_ELEMENT e[ECC_MAXLONG];
} ECC_FIELD;

typedef struct {
	ECC_FIELD x;
	ECC_FIELD y;
} ECC_POINT;

typedef struct {
	ECC_INDEX form; /* 'form' is just a fast way to check if a2==0 */
	ECC_FIELD a2; /* if form is zero, then: y^2 + xy = x^3 + a_6 */
	ECC_FIELD a6; /* otherwise: y^2 + xy = x^3 + a_2*x^2 + a_6 ("twist" curve) */
} ECC_CURVE;

/* These structures described in IEEE P1363 Nov. 1997. */

typedef struct {
	ECC_CURVE crv;
	ECC_POINT pnt;
	ECC_FIELD pnt_order;
	ECC_FIELD cofactor;
} EC_PARAMETER;

typedef struct {
	ECC_FIELD prvt_key;
	ECC_POINT pblc_key;
} EC_KEYPAIR;

typedef struct  {
	ECC_FIELD c;
	ECC_FIELD d;
} SIGNATURE;

static ECC_INDEX ecc_table[2][ECC_FIELDPRIME];
static ECC_INDEX ecc_log2m;

void BigIntToField(BigInt _source, ECC_FIELD *target) {
	BigInt t_me, source;
	int i;

	t_me=BigInt_Create();
	source=BigInt_Create();

	BigInt_Copy(source, _source);
	ECC_SUMLOOP(i) target->e[i]=0;

	i=ECC_MAXLONG-1;
	while (!BigInt_IsZero(source)) {
		target->e[i--]=BigInt_GetU(source);
		BigInt_Shift(source, -32, t_me);
		BigInt_Copy(source, t_me);
	};

	BigInt_Destroy(source);
	BigInt_Destroy(t_me);
};

void FieldToBigInt(ECC_FIELD *source, BigInt target) {
	BigInt t_me, t2_me;
	int i;

	t_me=BigInt_Create();
	t2_me=BigInt_Create();

	BigInt_Set(target, 0);

	for (i=0; i<ECC_MAXLONG; ++i) if (source->e[i]!=0) break;
	for (; i<ECC_MAXLONG; ++i) {
		BigInt_SetU(t_me, source->e[i]);
		BigInt_Shift(target, 32, t2_me);
		BigInt_Add(t2_me, t_me, target);
	};

	BigInt_Destroy(t2_me);
	BigInt_Destroy(t_me);
};

void ECC_RotateLeft(ECC_FIELD *a) {
	ECC_INDEX i;
	ECC_ELEMENT bit,temp;

	bit = (a->e[0] & ECC_UPRBIT) ? 1L : 0L;
	for (i=ECC_NUMWORD; i>=0; i--) {
		temp = (a->e[i] & ECC_MSB) ? 1L : 0L;
		a->e[i] = (a->e[i] << 1) | bit;
		bit = temp;
	};
	a->e[0] &= ECC_UPRMASK;
};

void ECC_RotateRight(ECC_FIELD *a) {
	ECC_INDEX i;
	ECC_ELEMENT bit,temp;

	bit = (a->e[ECC_NUMWORD] & 1) ? ECC_UPRBIT : 0L;
	ECC_SUMLOOP(i) {
		temp = (a->e[i] >> 1)  | bit;
		bit = (a->e[i] & 1) ? ECC_MSB : 0L;
		a->e[i] = temp;
	};
	a->e[0] &= ECC_UPRMASK;
};

void Field_Clear(ECC_FIELD *a) {
	ECC_INDEX i;
	ECC_SUMLOOP(i) a->e[i] = 0;
};

void Field_Copy(ECC_FIELD *a, ECC_FIELD *b) {
	ECC_INDEX i;
	ECC_SUMLOOP(i) b->e[i] = a->e[i];
};

void Field_Set(ECC_FIELD *place) {
	ECC_INDEX i;
	ECC_SUMLOOP(i) place->e[i] = (unsigned long)(-1L);
	place->e[0] &= ECC_UPRMASK;
};

void ECC_Multiply(ECC_FIELD *a, ECC_FIELD *b, ECC_FIELD *c) {
	ECC_INDEX i, j;
	ECC_INDEX zero_index, one_index;
	ECC_FIELD	amatrix[ECC_NUMBITS], copyb;

	Field_Clear(c);
	Field_Copy(b, &copyb);
	Field_Copy(a, &amatrix[0]);
	for (i = 1; i < ECC_NUMBITS; i++) {
		Field_Copy(&amatrix[i-1], &amatrix[i]);
		ECC_RotateRight(&amatrix[i]);
	};

	zero_index = ecc_table[0][0];
	ECC_SUMLOOP (i) c->e[i] = copyb.e[i] & amatrix[zero_index].e[i];

	for (j = 1; j<ECC_NUMBITS; j++) {
		ECC_RotateRight(&copyb);
		zero_index = ecc_table[0][j];
		one_index = ecc_table[1][j];
		ECC_SUMLOOP (i) c->e[i] ^= copyb.e[i] & (amatrix[zero_index].e[i] ^ amatrix[one_index].e[i]);
	};
};

void ECC_Inverse(ECC_FIELD *a, ECC_FIELD *result) {
	ECC_FIELD	shift, temp;
	ECC_INDEX m, s, r, rsft;

	s = ecc_log2m - 1;
	Field_Copy(a, result);
	m = ECC_NUMBITS - 1;

	while (s >= 0) {
		r = m >> s;
		Field_Copy(result, &shift);
		for (rsft = 0; rsft < (r>>1); rsft++) ECC_RotateLeft(&shift);
		ECC_Multiply(result, &shift, &temp);
		if (r&1) {
			ECC_RotateLeft(&temp);
			ECC_Multiply(&temp, a, result);
		} else Field_Copy(&temp, result);
		--s;
	};
	ECC_RotateLeft(result);
};

void ECC_RandomFieldOriginal(ECC_FIELD *value) {
	ECC_INDEX i;
	ECC_SUMLOOP(i) value->e[i]=NextRandomNumber();
	value->e[0]&=ECC_UPRMASK;
};

void ECC_RandomFieldImproved(ECC_FIELD *value) {
	NextRandomNumber128(value->e);
	value->e[0]&=ECC_UPRMASK;
};

void ECC_PointCopy(ECC_POINT *p1, ECC_POINT *p2) {
	Field_Copy(&p1->x, &p2->x);
	Field_Copy(&p1->y, &p2->y);
};

void ECC_PointAdd(ECC_POINT *p1, ECC_POINT *p2, ECC_POINT *p3, ECC_CURVE *curv) {
	ECC_INDEX i;
	ECC_FIELD x1, y1, theta, onex, theta2;

	Field_Clear(&x1);
	Field_Clear(&y1);
	ECC_SUMLOOP(i) {
		x1.e[i] = p1->x.e[i] ^ p2->x.e[i];
		y1.e[i] = p1->y.e[i] ^ p2->y.e[i];
	};
	ECC_Inverse(&x1, &onex);
	ECC_Multiply(&onex, &y1, &theta);
	Field_Copy(&theta, &theta2);
	ECC_RotateLeft(&theta2);

	if (curv->form) {
		ECC_SUMLOOP (i) p3->x.e[i] = theta.e[i] ^ theta2.e[i] ^ p1->x.e[i] ^ p2->x.e[i] ^ curv->a2.e[i];
	} else {
		ECC_SUMLOOP (i) p3->x.e[i] = theta.e[i] ^ theta2.e[i] ^ p1->x.e[i] ^ p2->x.e[i];
	};

	ECC_SUMLOOP (i) x1.e[i] = p1->x.e[i] ^ p3->x.e[i];
	ECC_Multiply(&x1, &theta, &theta2);
	ECC_SUMLOOP (i) p3->y.e[i] = theta2.e[i] ^ p3->x.e[i] ^ p1->y.e[i];
};

void ECC_PointSubtract(ECC_POINT *p1, ECC_POINT *p2, ECC_POINT *p3, ECC_CURVE *curv) {
	ECC_POINT negp;
	ECC_INDEX i;

	Field_Copy(&p2->x, &negp.x);
	Field_Clear(&negp.y);
	ECC_SUMLOOP(i) negp.y.e[i] = p2->x.e[i] ^ p2->y.e[i];
	ECC_PointAdd(p1, &negp, p3, curv);
};

void ECC_PointDouble(ECC_POINT *p1, ECC_POINT *p3, ECC_CURVE *curv) {
	ECC_FIELD x1, y1, theta, theta2, t1;
	ECC_INDEX i;

	ECC_Inverse(&p1->x, &x1);
	ECC_Multiply(&x1, &p1->y, &y1);
	ECC_SUMLOOP (i) theta.e[i] = p1->x.e[i] ^ y1.e[i];

	Field_Copy(&theta, &theta2);
	ECC_RotateLeft(&theta2);
	if(curv->form) {
		ECC_SUMLOOP (i) p3->x.e[i] = theta.e[i] ^ theta2.e[i] ^ curv->a2.e[i];
	} else {
		ECC_SUMLOOP (i) p3->x.e[i] = theta.e[i] ^ theta2.e[i];
	};

	Field_Set(&y1);
	ECC_SUMLOOP (i) y1.e[i] ^= theta.e[i];
	ECC_Multiply(&y1, &p3->x, &t1);
	Field_Copy(&p1->x, &x1);
	ECC_RotateLeft(&x1);
	ECC_SUMLOOP (i) p3->y.e[i] = x1.e[i] ^ t1.e[i];
};

void ECC_PointMultiply(ECC_FIELD *k, ECC_POINT *p, ECC_POINT *r, ECC_CURVE *curv) {
	signed char blncd[ECC_NUMBITS+1];
	ECC_INDEX bit_count, i;
	ECC_ELEMENT notzero;
	ECC_FIELD number;
	ECC_POINT temp;

	/* make sure input multiplier k is not zero. Return point at infinity if it
	is. */
	Field_Copy(k, &number);
	notzero = 0;
	ECC_SUMLOOP (i) notzero |= number.e[i];
	if (!notzero) {
		Field_Clear(&r->x);
		Field_Clear(&r->y);
		return;
	};

	bit_count = 0;
	while (notzero) {
		if (number.e[ECC_NUMWORD] & 1) {
			blncd[bit_count] = (signed char)(2 - (number.e[ECC_NUMWORD] & 3));
			if (blncd[bit_count] < 0) {
				for (i=ECC_NUMWORD; i>=0; i--) {
					number.e[i]++;
					if (number.e[i]) break;
				};
			};
		} else blncd[bit_count] = 0;

		number.e[ECC_NUMWORD] &= ~0 << 1;
		ECC_RotateRight(&number);
		bit_count++;
		notzero = 0;
		ECC_SUMLOOP (i) notzero |= number.e[i];
	};

	--bit_count;
	ECC_PointCopy(p,r);
	while (bit_count > 0) {
		ECC_PointDouble(r, &temp, curv);
		bit_count--;
		switch (blncd[bit_count]) {
			case 1: ECC_PointAdd(p, &temp, r, curv); break;
			case -1: ECC_PointSubtract(&temp, p, r, curv); break;
			case 0: ECC_PointCopy(&temp, r); break;
		};
	};
};

void ECC_KeyGenerationPrimitive(EC_PARAMETER *Base, EC_KEYPAIR *Key, BigInt init) {
	BigInt key_num=BigInt_Create();
	BigInt point_order=BigInt_Create();
	BigInt quotient=BigInt_Create();
	BigInt remainder=BigInt_Create();
	ECC_FIELD rand_key;

	if (init) {
		BigInt_Copy(key_num, init);
	} else {
		ECC_RandomFieldImproved(&rand_key);
		FieldToBigInt(&rand_key, key_num);
	};

	/* ensure the value is less than point order */
	FieldToBigInt(&Base->pnt_order, point_order);
	BigInt_Divide(key_num, point_order, quotient, remainder);
	BigIntToField(remainder, &Key->prvt_key);

	BigInt_Destroy(remainder);
	BigInt_Destroy(quotient);
	BigInt_Destroy(point_order);
	BigInt_Destroy(key_num);

	ECC_PointMultiply(&Key->prvt_key, &Base->pnt, &Key->pblc_key, &Base->crv);
};

void BigInt_Hash(char *Message, unsigned long length, BigInt hash_value) {
	unsigned long hash[4];	/* MD5 hash of message */
	BigInt t=BigInt_Create();
	BigInt t2=BigInt_Create();
	BigInt t3=BigInt_Create();
	ECC_INDEX i;

	/* create hash and convert to a BigInt */
	md5(hash, Message, length);
	BigInt_SetU(t, 0);
	for (i=0; i<4; ++i) {
		BigInt_SetU(t3, hash[i]);
		BigInt_Shift(t, 32, t2);
		BigInt_Add(t2, t3, t);
	};
	BigInt_Copy(hash_value, t);

	BigInt_Destroy(t3);
	BigInt_Destroy(t2);
	BigInt_Destroy(t);
};

void ECC_MakeSignature(char *Message, unsigned long length, EC_PARAMETER *public_curve, ECC_FIELD *secret_key, SIGNATURE *signature) {
	EC_KEYPAIR random_key;
	BigInt hash_value=BigInt_Create();
	BigInt x_value=BigInt_Create();
	BigInt k_value=BigInt_Create();
	BigInt sig_value=BigInt_Create();
	BigInt c_value=BigInt_Create();
	BigInt temp=BigInt_Create();
	BigInt temp2=BigInt_Create();
	BigInt quotient=BigInt_Create();
	BigInt key_value=BigInt_Create();
	BigInt point_order=BigInt_Create();
	BigInt u_value=BigInt_Create();

	/* compute hash of input message  */
	BigInt_Hash(Message, length, hash_value);

	/* create random value and generate random point on public curve  */
	ECC_KeyGenerationPrimitive(public_curve, &random_key, 0);

	/* convert x component of random point to an integer modulo the order of
	the base point. This is first part of signature. */
	FieldToBigInt(&public_curve->pnt_order, point_order);
	FieldToBigInt(&random_key.pblc_key.x, x_value);
	BigInt_Divide(x_value, point_order, quotient, c_value);
	BigIntToField(c_value, &signature->c);

	/* multiply that by signers private key and add to message digest modulo
	the order of the base point. hash value + private key * c value */
	FieldToBigInt(secret_key, key_value);
	BigInt_Multiply(key_value, c_value, temp);
	BigInt_Add(temp, hash_value, temp2);
	BigInt_Divide(temp2, point_order, quotient, k_value);

	/* final step is to multiply by inverse of random key value modulo order of
	base point. */
	FieldToBigInt(&random_key.prvt_key, temp);
	BigInt_ModularInverse(temp, point_order, u_value);
	BigInt_Multiply(u_value, k_value, temp);
	BigInt_Divide(temp, point_order, quotient, sig_value);
	BigIntToField(sig_value, &signature->d);

	BigInt_Destroy(hash_value);
	BigInt_Destroy(x_value);
	BigInt_Destroy(k_value);
	BigInt_Destroy(sig_value);
	BigInt_Destroy(c_value);
	BigInt_Destroy(temp);
	BigInt_Destroy(temp2);
	BigInt_Destroy(quotient);
	BigInt_Destroy(key_value);
	BigInt_Destroy(point_order);
	BigInt_Destroy(u_value);
};

/* These functions are part of the initialization stuff */

void ECC_InitializeTable() {
	/* If you need to reduce the CPU load, you can replace this function with a
	pre-computed table. For the 113-bit type-2 values we're using, it will
	calculate a 225-value 2D table. */
	ECC_ELEMENT ebit, bitsave, bitmask;
	ECC_INDEX k, n, i, twoexp, log2[ECC_FIELDPRIME];

	#ifdef ECC_TYPE2
		ECC_INDEX logof[4], j;

		twoexp = 1;
		for (i=0; i<ECC_NUMBITS; i++) {
			log2[twoexp] = i;
			twoexp = (short)((twoexp << 1) % ECC_FIELDPRIME);
		};

		if (twoexp == 1) {
			twoexp = 2*ECC_NUMBITS;
			for (i=0; i<ECC_NUMBITS; i++) {
				log2[twoexp] = i;
				twoexp = (short)((twoexp << 1) % ECC_FIELDPRIME);
			};
		} else {
			for (i=ECC_NUMBITS; i<ECC_FIELDPRIME-1; i++) {
				log2[twoexp] = i;
				twoexp = (short)((twoexp << 1) % ECC_FIELDPRIME);
			};
		};

		/* first element in vector 1 always = 1 */
		ecc_table[0][0] = 1;
		ecc_table[1][0] = -1;

		n = (ECC_FIELDPRIME - 1)/2;

		twoexp = 1;
		for (i=1; i<n; i++) {
			twoexp = (short)((twoexp<<1) % ECC_FIELDPRIME);
			logof[0] = log2[ECC_FIELDPRIME + 1 - twoexp];
			logof[1] = log2[ECC_FIELDPRIME - 1 - twoexp];
			logof[2] = log2[twoexp - 1];
			logof[3] = log2[twoexp + 1];
			k = 0;
			j = 0;
			while (k<2) {
				if (logof[j] < n) {
					ecc_table[k][i] = logof[j];
					++k;
				};
				++j;
			};
		};
	#else
		ECC_INDEX logof, index;

		for (i=0; i<ECC_FIELDPRIME; i++) log2[i] = -1;

		twoexp = 1;
		for (i=0; i<ECC_FIELDPRIME; i++) {
			log2[twoexp] = i;
			twoexp = (short)((twoexp << 1) % ECC_FIELDPRIME);
		};

		n = (ECC_FIELDPRIME - 1)/2;

		ecc_table[0][0] = n;
		for (i=1; i<ECC_FIELDPRIME; i++)
		ecc_table[0][i] = (ecc_table[0][i-1] + 1) % ECC_NUMBITS;

		ecc_table[1][0]= -1; /* never used */
		ecc_table[1][1] = n;
		ecc_table[1][n] = 1;

		for (i=2; i<=n; i++) {
			index = log2[i];
			logof = log2[ECC_FIELDPRIME - i + 1];
			ecc_table[1][index] = logof;
			ecc_table[1][logof] = index;
		};
		ecc_table[1][log2[n+1]] = log2[n+1];
	#endif

	ecc_log2m=0;
	bitsave=(ECC_ELEMENT)(ECC_NUMBITS - 1);
	k=ECC_ELEMENTBITS/2;
	bitmask=-1L<<k;
	while (k) {
		ebit=bitsave & bitmask;
		if (ebit) {
			ecc_log2m+=k;
			bitsave=ebit;
		};
		k/=2;
		bitmask^=(bitmask >> k);
	};
};

void ECC_FOFX(ECC_FIELD *x, ECC_CURVE *curv, ECC_FIELD *f) {
	ECC_FIELD x2, x3;
	ECC_INDEX i;

	Field_Copy(x, &x2);
	ECC_RotateLeft(&x2);
	ECC_Multiply(x, &x2, &x3);
	if (curv->form) ECC_Multiply(&x2, &curv->a2, f);
	else Field_Clear(f);
	ECC_SUMLOOP(i) f->e[i] ^= (x3.e[i] ^ curv->a6.e[i]);
};

int ECC_Quadratic(ECC_FIELD *a, ECC_FIELD *b, ECC_FIELD *y) {
	ECC_INDEX i, l, bits;
	ECC_FIELD x, k, a2;
	ECC_ELEMENT r, t, mask;

	r = 0;
	ECC_SUMLOOP(i) r |= a->e[i];
	if (!r) {
		Field_Copy(b, &y[0]);
		ECC_RotateRight(&y[0]);
		Field_Copy(&y[0], &y[1]);
		return 0;
	};

	ECC_Inverse(a, &a2);
	ECC_RotateLeft(&a2);

	ECC_Multiply(b, &a2, &k);
	ECC_RotateRight(&k);
	r = 0;

	ECC_SUMLOOP(i) r ^= k.e[i];

	mask = (unsigned long)(-1L);
	for (bits = ECC_ELEMENTBITS/2; bits > 0; bits >>= 1) {
		mask >>= bits;
		r = ((r & mask) ^ (r >> bits));
	};

	if (r) {
		Field_Clear(&y[0]);
		Field_Clear(&y[1]);
		return 1;
	};

	Field_Clear(&x);
	mask = 1;
	for (bits=0; bits < ECC_NUMBITS ; bits++) {
		i = ECC_NUMWORD - bits/ECC_ELEMENTBITS;
		l = ECC_NUMWORD - (bits + 1)/ECC_ELEMENTBITS;

		r = k.e[i] & mask;
		t = x.e[i] & mask;
		r ^= t;

		if (l == i) {
			r <<= 1;
			x.e[l] |= r;
			mask <<= 1;
		} else {
			mask = 1;
			if (r) x.e[l] = 1;
		};
	};

	r = k.e[0] & ECC_UPRBIT;
	t = x.e[0] & ECC_UPRBIT;
	if (r^t) {
		Field_Clear(&y[0]);
		Field_Clear(&y[1]);
		return 2; /* Should be mathematically impossible. */
	};

	ECC_Multiply(a, &x, &y[0]);

	Field_Clear (&y[1]);
	ECC_SUMLOOP(i) y[1].e[i] = y[0].e[i] ^ a->e[i];

	return 0;
};

void ECC_Embed(ECC_FIELD *data, ECC_CURVE *curv, ECC_INDEX incrmt, ECC_INDEX root, ECC_POINT *pnt) {
	ECC_FIELD f, y[2];
	ECC_INDEX inc=incrmt;

	if ((inc < 0) || (inc > ECC_NUMWORD)) inc=0;
	Field_Copy(data, &pnt->x);
	ECC_FOFX(&pnt->x, curv, &f);
	while (ECC_Quadratic( &pnt->x, &f, y)) {
		pnt->x.e[inc]++;
		ECC_FOFX( &pnt->x, curv, &f);
	};
	Field_Copy(&y[root&1], &pnt->y);
};

void ECC_RandomPoint(ECC_POINT *point, ECC_CURVE *curve) {
	ECC_FIELD	rf;
	ECC_RandomFieldOriginal(&rf);
	ECC_Embed(&rf, curve, ECC_NUMWORD, (ECC_INDEX)(rf.e[ECC_NUMWORD]&1), point);
};

void ECC_Initialize(EC_PARAMETER *Base, EC_KEYPAIR *Signer, unsigned long basepointinit, const char *_rndinitstring) {
	BigInt secretkeyhash=BigInt_Create();
	BigInt prime_order=BigInt_Create();
	char rndinitstring[1024];
	unsigned long i[4];
	ECC_POINT temp;

	/* Compute the ECC tables. */
	ECC_InitializeTable();

	/* Compute the curve order from Koblitz data. SEGC's "Recommended Elliptic
	Curve Domain Parameters" document has more information on this, but we're
	not using their recommendations because they only provide polynomial curves
	over F(2^m), not "optimal normal basis" curves over the same field (which
	is what we're using). The ECC_PRIMEORDER number came from Michael Rosing's
	example code. */
	BigInt_FromString(ECC_PRIMEORDER, prime_order);
	BigIntToField(prime_order, &Base->pnt_order);
	Field_Clear(&Base->cofactor);
	Base->cofactor.e[ECC_NUMWORD]=2;

	/* Create Koblitz curve of ECC_NUMBITS order. This curve is part of the
	public key, and can be safely shared between users. */
	Base->crv.form=1;
	Field_Set(&Base->crv.a2);
	Field_Set(&Base->crv.a6);
	/*print_curve("Koblitz 113", &Base->crv);*/

	/* Create the base point, with a known order and no cofactor. This point is
	part of the public key, and can be safely shared between many users if
	necessary (but for added security, I'm setting it up so it can also be
	different for everyone). */
	InitRandomGenerator(basepointinit);
	ECC_RandomPoint(&temp, &Base->crv);
	ECC_PointDouble(&temp, &Base->pnt, &Base->crv);
	/*print_point("Random point", &temp);*/
	/*print_point(" Base point ",&Base->pnt);*/

	/* Create the secret key from the encryption template. The secret key
	must be less than order -- this is dealt with by BigInt_Hash. Also note
	that BigInt_Hash only creates a 128-bit secret key; that's okay for our
	purposes, but if you use a field size larger than 128 bits, you'll need to
	extend the hash to the same number of bits or greater, for security. */
	strcpy(rndinitstring, _rndinitstring);
	strcat(rndinitstring, "PVTKEY");
	BigInt_Hash(rndinitstring, strlen(rndinitstring), secretkeyhash);
	ECC_KeyGenerationPrimitive(Base, Signer, secretkeyhash);
	/*print_field("Signer's secret key", &Signer->prvt_key);*/
	/*print_point("Signers public key", &Signer->pblc_key);*/

	/* Reinitialize the random number generators to a new random value, based
	on both the encryption template and the system clock. This ensures that it
	can't be guessed from the time and date unless the attacker also knows the
	encryption template already, which means he could generate all the keys he
	wants without bothering to guess anything. */
	sprintf(rndinitstring, "%sECCRND%u", _rndinitstring, GetRandomSeed());
	md5(i, rndinitstring, strlen(rndinitstring));
	InitRandomGenerator(i[0]^i[1]^i[2]^i[3]);
	InitRandomGenerator128(i);

	BigInt_Destroy(secretkeyhash);
	BigInt_Destroy(prime_order);
};

/*
	The following code creates the Signed Keys.
*/

#define KS_V1 -1
#define KS_V2 0
#define KS_V3 1
#define KS_SHORTV3 2

static unsigned char *AddByte(unsigned char *c, unsigned char n) {
	*c++=n;
	return c;
};

static unsigned char *AddShort(unsigned char *c, unsigned short n) {
	*c++=(unsigned char)(n>>8);
	*c++=(unsigned char)(n&0xFF);
	return c;
};

static unsigned char *AddLong(unsigned char *c, unsigned long n) {
	*c++=(unsigned char)(n>>24);
	*c++=(unsigned char)(n>>16);
	*c++=(unsigned char)(n>>8);
	*c++=(unsigned char)(n&0xFF);
	return c;
};

static void mystrrev(char *str) {
	/*
	** strrev() apparently isn't part of the standard C library, or at least
	** isn't supported on all platforms, because I've had reports that it
	** isn't available on some. So I wrote this function to replace it.
	*/

	char tmp, *s1, *s2;
	s1=str;
	s2=strchr(str, 0)-1;
	while (s1<s2) {
		tmp=*s1; *s1=*s2; *s2=tmp;
		++s1; --s2;
	};
};

static CRC32 GetKeyCRC(char *keytext, int period) {
	char cooked[512], temp[512], *s, *t;
	int x, y, len;

	CookText(cooked, keytext);
	if (period==1) {
		/* Just reverse the string. strrev() is apparently not supported on
		some CGI systems, so I've written my own version here. */
		strcpy(temp, cooked);
		t=cooked;
		s=strchr(temp, 0)-1;
		while (s>=temp) *t++=*s--;
		*t=0;
	} else if (period>1) {
		/* Start at the beginning and split the keytext into groups of 'period'
		letters. Reverse each group. */
		strcpy(temp, cooked);
		t=cooked;
		len=strlen(cooked);
		for (x=0; x<(len/period); ++x) {
			s=temp+(x*period);
			for (y=period-1; y>=0; --y) *t++=*(s+y);
		};

		/* Now reverse the last group, if there are any characters that haven't
		been handled yet. */
		if ((len%period)!=0) {
			s=temp+len-1;
			for (y=0; y<len%period; ++y) *t++=*(s-y);
		};

		*t=0;

		#ifdef TEST
			/*printf("String '%s', period %d, is '%s'\n", temp, period, cooked);*/
		#endif
	};
	return crc32(cooked, strlen(cooked), NewCRC32);
};

void GetKeyMD5(unsigned long *i, const char *keytext, int period) {
	char cooked[512];
	int len, x, y;

	CookText(cooked, keytext);
	if (period==1) {
		mystrrev(cooked);
	} else if (period>1) {
		/*
		** Start at the beginning and split the keytext into groups of 'period'
		** letters. Reverse each group.
		*/
		char temp[512], *s, *t;

		strcpy(temp, cooked);
		t=cooked;
		len=strlen(cooked);
		for (x=0; x<(len/period); ++x) {
			s=temp+(x*period);
			for (y=period-1; y>=0; --y) *t++=*(s+y);
		};

		/*
		** Now reverse the last group, if there are any characters that haven't
		** been handled yet.
		*/
		if ((len%period)!=0) {
			s=temp+len-1;
			for (y=0; y<len%period; ++y) *t++=*(s-y);
		};

		*t=0;
	};

	md5(i, cooked, strlen(cooked));
};

static void GenerateKeyNumberFromString(char *string, BigInt p, BigInt *keynumber, int keysystem, int v3level) {
	unsigned long i[4], current[4]={0,0,0,0};
	BigInt n, n2, n3, exp;
	int x, y;

	n=BigInt_Create();

	if (keysystem==KS_SHORTV3) {
		/* The ShortV3 key system uses shorter numbers than the standard v3
		system, but longer ones than the v2 system. ShortV3 numbers are also
		generated using MD5 instead of CRC32. */
		for (x=0; x<4; ++x) {
			GetKeyMD5(i, string, x+2);
			for (y=0; y<4; ++y) current[y]^=i[y];
		};

		n2=BigInt_Create();
		n3=BigInt_Create();

		for (x=0; x<4; ++x) {
			BigInt_Shift(n, 32, n2);
			BigInt_SetU(n3, current[x]);
			BigInt_Add(n2, n3, n);
		};

		BigInt_Modulus(n, p, *keynumber);

		BigInt_Destroy(n3);
		BigInt_Destroy(n2);
	} else if (keysystem==KS_V3) {
		/* v2 keys are based on 32 bit numbers; v3 keys use much larger ones,
		32 additional bits per level. */
		n2=BigInt_Create();
		n3=BigInt_Create();
		exp=BigInt_Create();

		BigInt_SetU(n, GetKeyCRC(string, 1));
		BigInt_Copy(exp, n);
		for (x=0; x<v3level; ++x) {
			BigInt_Shift(n, 32, n2);
			BigInt_SetU(n3, GetKeyCRC(string, x+2));
			BigInt_Add(n2, n3, n);
		};
		BigInt_PowerModulus(n, exp, p, *keynumber);

		BigInt_Destroy(exp);
		BigInt_Destroy(n3);
		BigInt_Destroy(n2);
	} else {
		/* V2 keys */
		BigInt_SetU(n, GetKeyCRC(string, 1));
		BigInt_PowerModulus(n, n, p, *keynumber);
	};

	BigInt_Destroy(n);
};

/*
static void CheckModularInverse(BigInt a, BigInt b, BigInt p1) {
	BigInt temp, temp2, temp3;

	temp=BigInt_Create();
	temp2=BigInt_Create();
	temp3=BigInt_Create();

	BigInt_Multiply(a, b, temp);
	BigInt_Divide(temp, p1, temp2, temp3);
	if (BigInt_Get(temp3)!=1) printf("ERROR IN MODULARINVERSE!\n");
	else printf("ModularInverse is good!\n");

	BigInt_Destroy(temp3);
	BigInt_Destroy(temp2);
	BigInt_Destroy(temp);
};

static void CheckMultiply(BigInt a, BigInt b, BigInt ans) {
	BigInt temp=BigInt_Create();
	BigInt temp2=BigInt_Create();

	BigInt_Divide(ans, b, temp, temp2);

	if (BigInt_Compare(temp2, BigInt_Zero())) printf("ERROR IN MULTIPLY!\n");

	if (BigInt_Compare(a, temp)!=0) printf("ERROR IN MULTIPLY!\n");
	else printf("Multiply okay.\n");

	BigInt_Destroy(temp2);
	BigInt_Destroy(temp);
};

void CheckDivide(BigInt m1, BigInt m2, BigInt q, BigInt r) {
	BigInt temp=BigInt_Create();
	BigInt temp2=BigInt_Create();

	BigInt_Multiply(q, m2, temp);
	BigInt_Add(temp, r, temp2);
	if (BigInt_Compare(temp2, m1)) {
		printf("Divide error!\n");
		printf("temp2 "); BigInt_Dump(temp2);
		printf("m1 "); BigInt_Dump(m1);
		printf("m2 "); BigInt_Dump(m2);
		printf("q "); BigInt_Dump(q);
		printf("r "); BigInt_Dump(r);

		BigInt_Subtract(temp2, m1, temp);
		printf("Difference "); BigInt_Dump(temp);

	} else printf("Divide okay.\n");

	BigInt_Destroy(temp2);
	BigInt_Destroy(temp);
};
*/

/*
void GCDTest() {
	BigInt k, p, p1, pvt, temp, temp2, banswer;
	unsigned long ksource=0x3C66499A+1;
	char pvtkeystring[]="Testing";
	int level=1, size=5;

	k=BigInt_Create();
	p=BigInt_Create();
	p1=BigInt_Create();
	pvt=BigInt_Create();
	temp=BigInt_Create();
	temp2=BigInt_Create();
	banswer=BigInt_Create();

	// Make p1
	BigInt_Set(temp, 1);
	BigInt_Shift(temp, size*8, p);
	BigInt_Set(temp, primeoffsets[level]);
	BigInt_Add(p, temp, temp2);
	BigInt_Copy(p, temp2);
	BigInt_Subtract(p, BigInt_One(), p1);

	BigInt_Dump(p1);

	// Make pvt
	GenerateKeyNumberFromString(pvtkeystring, p, &pvt, KS_V2, 0);

	BigInt_Dump(pvt);

	// Make k
	BigInt_Set(temp, ksource);
	BigInt_PowerModulus(pvt, temp, p, k);

	BigInt_Dump(k);

	// Do the test!
	BigInt_GCD(k, p1, temp);
	if (BigInt_Compare(temp, BigInt_One())==0) printf("GCD is 1?\n");
	BigInt_Dump(temp);


	//BigInt_Set(bn, 10);
	//BigInt_Set(bm, 5);
	//BigInt_GCD(bn, bm, banswer);
	//BigInt_Dump(banswer);
};
*/

static int MakeEccSignature(unsigned char *keybytes, int *keylength, char *pvtkeystring, char *name_to_make_key_for, int level) {
	EC_PARAMETER Base;
	EC_KEYPAIR Signer;
	SIGNATURE signature;
	char tmp[512], tmp2[512], encryption_template[512];
	unsigned long i[4], x, basepointinit;
	unsigned char *c;
	BigInt stemp=BigInt_Create();
	BigInt stemp2=BigInt_Create();
	BigInt stemp3=BigInt_Create();
	BigInt stemp4=BigInt_Create();

	/* Level 29 (ShortV3 Level 10) is the only level that uses this format. */
	if (level!=29) return 0;

	/* The base-point can be shared between everyone, but for added security,
	I'd rather it weren't. Make a different one depending on the encryption
	template (which is the private key string). */
	CookText(encryption_template, pvtkeystring);
	md5(i, encryption_template, strlen(encryption_template));
	basepointinit=i[0];

	/* Initialize the ECC system with the base-point and cooked encryption
	template. */
	ECC_Initialize(&Base, &Signer, basepointinit, encryption_template);

	/* Create the message to be signed. That will be the current contents of
	'keybytes' plus the name we're making the key for, not including the
	terminating null. */
	CookText(tmp, name_to_make_key_for);
	memcpy(tmp2, keybytes, *keylength);
	memcpy(tmp2+(*keylength), tmp, strlen(tmp));

	/* Create the signature. */
	BigInt_Set(stemp, 1);
	BigInt_Shift(stemp, 112, stemp4);
	while (1) {
		ECC_MakeSignature(tmp2, *keylength+strlen(tmp), &Base, &Signer.prvt_key, &signature);

		/* The signature is now in two FIELDs. Convert them to a single
		BigNumber and write it into the key. I'm reserving 112 bits for each,
		the exact amount that should be needed... we should probably allow for
		113, to be on the safe side, but 112 comes out to an even 28 bytes of
		signature. To ensure that everything fits, we'll check the signature
		parts after we create them, and try again with a different random point
		if either of them are too big. */
		FieldToBigInt(&signature.c, stemp3);
		if (BigInt_Compare(stemp3, stemp4)>0) continue;
		BigInt_Shift(stemp3, 112, stemp2);
		FieldToBigInt(&signature.d, stemp3);
		if (BigInt_Compare(stemp3, stemp4)>0) continue;
		BigInt_Add(stemp3, stemp2, stemp);
		break;
	};

	c=keybytes+(*keylength);
	BigInt_Set(stemp3, 0xFF);
	for (x=0; x<28; ++x) {
		BigInt_And(stemp, stemp3, stemp2);
		c=AddByte(c, (unsigned char)BigInt_GetU(stemp2));
		BigInt_Shift(stemp, -8, stemp2);
		BigInt_Copy(stemp, stemp2);
	};
	*keylength=(c-keybytes);

	BigInt_Destroy(stemp4);
	BigInt_Destroy(stemp3);
	BigInt_Destroy(stemp2);
	BigInt_Destroy(stemp);
	return 1;
};

unsigned long ksource=0;
static int MakeSignature(unsigned char *keybytes, int *keylength, char *pvtkeystring, char *name_encryptkey, int level) {
	BigInt message, p, p1, pub, pvt, y, temp, temp2, temp3, a, b, k, c1, c2;
	char tmp[512], tmp2[512];
	int size, x, keysystem;
	unsigned long i[4];
	unsigned char *c;
	CRC32 crc;

	/* What kind of key is it? */
	if (level==29) {
		/* If the signature level is 29, it's ShortV3 Level 10. That level is
		different from other signed keys; it uses ECC-DSA for the signature,
		rather than standard Elgamal. */
		return MakeEccSignature(keybytes, keylength, pvtkeystring, name_encryptkey, level);
	} else if (level>=20) {
		keysystem=KS_SHORTV3;
		level=level-20;
		/* Standard ShortV3 keys can have signature levels 1 through 9 (or
		rather, 0..8) */
		if (level>8) return 0;
	} else if (level>=10) {
		keysystem=KS_V3;
		level=level-10;
		/* V3 keys can now have signature levels 1 through 9 (or rather, 0..8) */
		if (level>8) return 0;
	} else {
		/* V2 keys can only have signature levels 1 through 4 (or rather, 0..3) */
		keysystem=KS_V2;
		if (level<0 || level>3) return 0;
	};
	size=level+4;

	message=BigInt_Create();
	p=BigInt_Create();
	p1=BigInt_Create();
	pub=BigInt_Create();
	pvt=BigInt_Create();
	y=BigInt_Create();
	temp=BigInt_Create();
	temp2=BigInt_Create();
	temp3=BigInt_Create();
	a=BigInt_Create();
	b=BigInt_Create();
	k=BigInt_Create();
	c1=BigInt_Create();
	c2=BigInt_Create();

	/*
	** First we make the "message" that we're going to use. This is much larger
	** for v3 keys than it was previously. ShortV3 keys sign the MD5 of the
	** message instead of the message itself -- more efficient that way.
	*/
	CookText(tmp, name_encryptkey);
	if (keysystem==KS_SHORTV3) {
		memcpy(tmp2, keybytes, *keylength);
		memcpy(tmp2+(*keylength), tmp, strlen(tmp));
		md5(i, tmp2, (*keylength)+strlen(tmp));
		for (x=0; x<4; ++x) {
			BigInt_Shift(message, 32, temp2);
			BigInt_SetU(temp3, i[x]);
			BigInt_Add(temp2, temp3, message);
		};
	} else if (keysystem==KS_V3) {
		BigInt_SetU(message, crc32((char *)keybytes, *keylength, NewCRC32));
		for (x=0; x<level+1; ++x) {
			BigInt_Shift(message, 32, temp2);
			BigInt_SetU(temp3, GetKeyCRC(tmp, x));
			BigInt_Add(temp2, temp3, message);
		};
	} else {
		crc=crc32(tmp, strlen(tmp), NewCRC32);
		crc=crc32((char *)keybytes, *keylength, crc);
		BigInt_SetU(message, crc);
	};

	/* Now we grab a large prime number. Armadillo uses several precalculated
	primes, based on the level (size). */
	BigInt_Set(temp, 1);
	BigInt_Shift(temp, size*8, p);
	BigInt_Set(temp, primeoffsets[level]);
	BigInt_Add(p, temp, temp2);
	BigInt_Copy(p, temp2);
	BigInt_Subtract(p, BigInt_One(), p1);
	/*BigNumber(2).Power((level+4)*8)+primeoffsets[level];*/

	/* Generate the public and private keys, and the 'y' value */
	sprintf(tmp, "%u Level Public Key", level);
	GenerateKeyNumberFromString(tmp, p, &pub, keysystem, ((keysystem==KS_V3 || keysystem==KS_SHORTV3) ? level+1 : 0));
	GenerateKeyNumberFromString(pvtkeystring, p, &pvt, keysystem, ((keysystem==KS_V3 || keysystem==KS_SHORTV3) ? level+1 : 0));
	BigInt_PowerModulus(pub, pvt, p, y);

	/* Get random value for k -- must remain secret! Prepare to repeat if necessary. */
	if (!ksource) ksource=GetRandomSeed()^GetKeyCRC(pvtkeystring, 1);

	while (1) {
		/* In previous versions of this file, we just set 'temp' to a 32-bit
		value based on the time, but that made it possible to brute-force the
		reversed private key number if someone knew the exact time that a key
		was made. 'temp' is now set to a random 48-bit number, and the result
		cannot be traced back to the private key number at all. This little
		section replaces these two lines:
			BigInt_Set(temp, ++ksource);
			BigInt_PowerModulus(pvt, temp, p, k);
		*/
		sprintf(tmp, "%u%s", ++ksource, pvtkeystring);
		BigInt_Set(temp, 0);
		for (x=0; x<5; ++x) {
			BigInt_Shift(temp, 4, temp2);
			BigInt_SetU(temp3, GetKeyCRC(tmp, x+2));
			BigInt_Add(temp2, temp3, temp);
		};
		BigInt_Modulus(temp, p, k); /* Make sure it's less than 'p' */

		/* If k and p1 have a common factor, it won't work. Check for it. */
		while (1) {
			BigInt_GCD(k, p1, temp);
			if (BigInt_Compare(temp, BigInt_One())==0) break;

			BigInt_Add(k, BigInt_One(), temp);
			BigInt_Copy(k, temp);
			if (BigInt_Compare(k, p)>=0) BigInt_Set(k, 3);
		};

		/* Make signature, 'a' and 'b' parts. */
		BigInt_PowerModulus(pub, k, p, a);
		BigInt_Multiply(pvt, a, temp);
		BigInt_Subtract(message, temp, temp2); /*temp2=(message-(pvt*a))*/
		BigInt_ModularInverse(k, p1, b); /*b=ModularInverse(k, p-1)*/

		/* Check it! We shouldn't have to, but there used to be a rare bug in
		the BigInt_ModularInverse function... about one out of every 224 times,
		it would return an inverse that wasn't right. Should be fixed now, so
		this code shouldn't be necessary, but it doesn't impact the speed very
		much, so we've left it in here as a "belt and suspenders" fix. */
		BigInt_Multiply(k, b, temp);
		BigInt_Modulus(temp, p1, temp3);
		if (!BigInt_Compare(temp3, BigInt_One())==0) {
			#ifdef DEBUG
			printf("ModularInverse returned the wrong answer!\n");
			BigInt_Dump(k, "k");
			BigInt_Dump(p1, "p1");
			#endif
			continue;
		};

		BigInt_Multiply(b, temp2, temp); /*temp=b*temp2*/
		BigInt_Modulus(temp, p1, b); /*b=temp%(p-1)*/
		/*b=((message-(pvt*a))*BigNumber::ModularInverse(k, p-1)).Mod(p-1);*/

		/* Check the size of the parts. */
		BigInt_Set(temp, 256);
		BigInt_Shift(BigInt_One(), size*8, temp2);
		if (BigInt_Compare(a, temp)>=0 && BigInt_Compare(a, temp2)<0 && BigInt_Compare(b, temp)>=0 && BigInt_Compare(b, temp2)<0) {
			/* Check the signature, to ensure it's okay. Not needed, it's just
			here for debugging purposes. */
			/*
			BigInt_PowerModulus(y, a, p, c1);
			BigInt_PowerModulus(a, b, p, temp);
			BigInt_Multiply(temp, c1, temp2);
			BigInt_Modulus(temp2, p, c1);
			BigInt_PowerModulus(pub, message, p, c2);
			if (BigInt_Compare(c1, c2)==0) {
				printf("Signature good!\n");
				break;
			} else printf("Signature error!\n");
 			*/
			break;
		};
	};

	/* Write the signature into the key */
	c=keybytes+(*keylength);
	BigInt_Set(temp2, 0xFF);
	for (x=0; x<size; ++x) {
		BigInt_And(a, temp2, temp);
		c=AddByte(c, (unsigned char)BigInt_GetU(temp));
		BigInt_Shift(a, -8, temp);
		BigInt_Copy(a, temp);

		BigInt_And(b, temp2, temp);
		c=AddByte(c, (unsigned char)BigInt_GetU(temp));
		BigInt_Shift(b, -8, temp);
		BigInt_Copy(b, temp);
	};
	*keylength=(c-keybytes);

	BigInt_Destroy(c2);
	BigInt_Destroy(c1);
	BigInt_Destroy(k);
	BigInt_Destroy(b);
	BigInt_Destroy(a);
	BigInt_Destroy(temp3);
	BigInt_Destroy(temp2);
	BigInt_Destroy(temp);
	BigInt_Destroy(y);
	BigInt_Destroy(pvt);
	BigInt_Destroy(pub);
	BigInt_Destroy(p1);
	BigInt_Destroy(p);
	BigInt_Destroy(message);

	return 1;
};

static void EncryptSignedKey(unsigned char *keybytes, int keylength, char *encryptkey) {
	char tmp[512];
	int x;

	CookText(tmp, encryptkey);
	InitRandomGenerator(crc32(tmp, strlen(tmp), NewCRC32)); /*RandomGenerator r(crc32(tmp, strlen(tmp), NewCRC32));*/
	for (x=0; x<keylength; ++x) keybytes[x]^=NextRandomRange(256);
};

const char *CreateSignedKey(int level, char *encryption_template, char *_name_to_make_key_for, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5, char *keystring) {
	static char retval[512]="";
	char name_to_make_key_for[512], temp[512], *cc, *cc2, *shortv3digits="0123456789ABCDEFGHJKMNPQRTUVWXYZ";
	int otherinfocount, x, nn, dcount, keylength=0, nameless=0;
	unsigned long symmetrickey, i[4];
	unsigned char *c, keybytes[512];
	BigInt n, t1, t2;

	/* Make a copy of the name -- might not be safe to change the original. */
	if (_name_to_make_key_for) strcpy(name_to_make_key_for, _name_to_make_key_for);
	else strcpy(name_to_make_key_for, "");

	/* If the signature level is less than zero, he wants to make a v1
	(unsigned) key. Route the call to that function instead, and ignore the
	parameters that aren't used in that type. */
	if (level<0) return CreateKey(name_to_make_key_for, encryption_template, otherinfo1, hardwareID);

	CookText(temp, encryption_template);
	if (level>=20) {
		/* ShortV3 format */
		GetKeyMD5(i, temp, 0);
		symmetrickey=i[0]^i[1]^hardwareID;

		/* Is this a "nameless" key? If so, make up a name for it. */
		if (*name_to_make_key_for==0) {
			nameless=1;
			nn=strlen(shortv3digits);
			cc=name_to_make_key_for;
			*cc++='2';
			for (x=0; x<5; ++x) *cc++=shortv3digits[NextRandomRange(nn)];
			*cc++=0;
		};
	} else {
		/* V2 or conventional V3 format */
		symmetrickey=crc32(temp, strlen(temp), NewCRC32)^hardwareID;

		if (*name_to_make_key_for==0) {
			/* Can't make nameless keys for any other format. */
			return "NoNameError";
		};
	};
	symmetrickey^=HWIDXOR;

	/* How many otherinfo values are we going to use? */
	if (otherinfo5) otherinfocount=5;
	else if (otherinfo4) otherinfocount=4;
	else if (otherinfo3) otherinfocount=3;
	else if (otherinfo2) otherinfocount=2;
	else if (otherinfo1) otherinfocount=1;
	else otherinfocount=0;

	/* Put the unsigned key together */
	c=keybytes;
	if (otherinfocount>=5) c=AddShort(c, otherinfo5);
	if (otherinfocount>=4) c=AddShort(c, otherinfo4);
	if (otherinfocount>=3) c=AddShort(c, otherinfo3);
	if (otherinfocount>=2) c=AddShort(c, otherinfo2);
	if (otherinfocount>=1) c=AddShort(c, otherinfo1);
	c=AddShort(c, GetToday());
	c=AddLong(c, symmetrickey);
	if (keystring && *keystring) {
		char *cc=strchr(keystring, 0)-1;
		while (cc>=keystring) c=AddByte(c, *cc--);
		c=AddByte(c, (unsigned char)(strlen(keystring)));
	};

	keylength=c-keybytes;

	/* Encrypt the key */
	EncryptSignedKey(keybytes, keylength, name_to_make_key_for);

	/* Now add the signature of this key. */
	if (MakeSignature(keybytes, &keylength, encryption_template, name_to_make_key_for, level)) {
		/* Make it into a string */
		strcpy(retval, "");
		if (level>=20) {
			/* ShortV3 format */
			n=BigInt_Create();
			t1=BigInt_Create();
			t2=BigInt_Create();

			/* When I created the ShortV3 keysystem, I didn't take into account
			that some keys would have zero-bytes at the beginning, so I had to
			change Armadillo later to deal with that case, which made it slower
			to recognize keys than it should have been. For the new level 10
			ShortV3 keys, I've learned my lesson: I'm setting the first bit on
			the key, which we'll strip off when we interpret it. */
			if (level==29) BigInt_Set(n, 1);

			for (x=0; x<keylength; ++x) {
				BigInt_Shift(n, 8, t1);
				BigInt_SetU(t2, keybytes[x]);
				BigInt_Add(t1, t2, n);
			};

			cc=retval;
			dcount=6;
			while (BigInt_Compare(n, BigInt_Zero())!=0) {
				BigInt_SetU(t2, 32);
				BigInt_Modulus(n, t2, t1);
				nn=BigInt_Get(t1);

				BigInt_Shift(n, -5, t2);
				BigInt_Copy(n, t2);

				if (level==29) {
					/* For the new ShortV3 Level 10 keys, I'm just going to
					insist that all of them start with the digit '1'. That way,
					when we're taking them apart, we'll always know which level
					to use for it immediately, we don't have to try different
					combinations of levels and extra-info like we did with the
					earlier ones. */
					*cc++=shortv3digits[nn];
					if (--dcount==0) { dcount=6; *cc++='-'; };
				} else {
					/*
					** Ensure that the first digit is outside the range of 0..9
					** and A..F. To do this, we'll either add 16 to the first
					** digit (if it's less than 16), or add an extra digit.
					*/
					if (BigInt_Compare(n, BigInt_Zero())==0) {
						if (nn<16) {
							*cc++=shortv3digits[nn+16];
							--dcount;
						} else {
							*cc++=shortv3digits[nn];
							if (--dcount==0) { dcount=6; *cc++='-'; };
							*cc++=shortv3digits[16];
							--dcount;
						};
					} else {
						*cc++=shortv3digits[nn];
						if (--dcount==0) { dcount=6; *cc++='-'; };
					};
				};
			};
			if (level==29) { if (dcount==0) { dcount=6; *cc++='-'; }; *cc++='1'; --dcount; };
			if (keystring && *keystring) { if (dcount==0) { dcount=6; *cc++='-'; }; *cc++='3'; --dcount; };
			if (nameless) {
				if (dcount==0) { dcount=6; *cc++='-'; };
				cc2=name_to_make_key_for+strlen(name_to_make_key_for)-1;
				while (cc2>=name_to_make_key_for) {
					*cc++=*cc2--;
					if (--dcount==0) { dcount=6; *cc++='-'; };
				};
			};

			while (dcount-->0) *cc++='0';
			*cc=0;
			mystrrev(retval);

			BigInt_Destroy(t2);
			BigInt_Destroy(t1);
			BigInt_Destroy(n);
		} else {
			/* V2 or conventional V3 format */
			for (x=0; x<keylength; x+=2) {
				if (x>0) strcat(retval, "-");
				sprintf(strchr(retval, 0), "%02X%02X", (unsigned char)keybytes[x], (unsigned char)keybytes[x+1]);
			};
		};
	} else strcpy(retval, "SigLevelError");

	return retval;
};

const char *CreateV2Key(int level, char *encryption_template, char *name_to_make_key_for, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5) {
	return CreateSignedKey(level, encryption_template, name_to_make_key_for, hardwareID, otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5, 0);
};

const char *CreateV3Key(int level, char *encryption_template, char *name_to_make_key_for, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5) {
	return CreateSignedKey(level+10, encryption_template, name_to_make_key_for, hardwareID, otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5, 0);
};

const char *CreateShortV3Key(int level, char *encryption_template, char *name_to_make_key_for, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5) {
	return CreateSignedKey(level+20, encryption_template, name_to_make_key_for, hardwareID, otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5, 0);
};

const char *CreateShortV3KeyWithString(int level, char *encryption_template, char *name_to_make_key_for, unsigned long hardwareID, unsigned short otherinfo1, unsigned short otherinfo2, unsigned short otherinfo3, unsigned short otherinfo4, unsigned short otherinfo5, char *keystring) {
	if (keystring && strlen(keystring)>64) return "KeyStringTooLong";
	return CreateSignedKey(level+20, encryption_template, name_to_make_key_for, hardwareID, otherinfo1, otherinfo2, otherinfo3, otherinfo4, otherinfo5, keystring);
};

/*
	-----------------------------------------------
	Key information functions, to take a key apart.
	-----------------------------------------------
*/

struct KeyInformation {
	unsigned short createdyear, createdmonth, createdday;
	unsigned short otherinfo[5];
};

static int hexdigit(char c) {
	if (c>='0' && c<='9') return (c-'0');
	else if (c>='a' && c<='f') return (c-'a'+10);
	else if (c>='A' && c<='F') return (c-'A'+10);
	return -1;
};

static const char *GetTwoHexDigits(const char *c, unsigned char *value) {
	int digit1=-1, digit2=-1;
	while (digit1<0) { if (*c==0) return 0; digit1=hexdigit(*c++); };
	while (digit2<0) { if (*c==0) return 0; digit2=hexdigit(*c++); };
	*value=(unsigned char)((digit1<<4)|digit2);
	return c;
};

void CheckNameless(char *name, char *origkey) {
	char leaders=0;
	char namex[32]="";
	char newkey[512]="";
	char newkey2[512]="";
	int ii, ik, di;					// loop indexes
	int divide, keylen, keylen2;
	int leadingzeros=0;
	char *dashesin;
	char *ptrsrc;
	char *ptrdest;
	// Remove leading zeroes.
	keylen = strlen(origkey);
	ptrsrc = origkey;		// pointer to the original nameless key.
	ptrdest= newkey;		// pointer to the array to hold the new stripped key.
	while (*ptrsrc == '0') {
		ptrsrc++;				// skip over the leading zero.
		leaders++;				// increment counter
	};
	// Remove dashes to be able to extract the embedded name.
	for (ik=0; ik<keylen; ik++) {
		if (*ptrsrc == '-') *ptrsrc++;	// skip over the dash
		else *ptrdest++=*ptrsrc++;	// copy the key, character at a time.
	};
	*ptrdest=0;

	for (ii=0; ii<6; ii++) {
		namex[ii]=newkey[ii];	// The name is 6 characters.
	};
	strcpy(name, namex);		// This makes sure the name is correct
	leadingzeros=6-(strlen(newkey)%6);	// The modulus says how many 'extra' characters there are, 0..5.
										// The six-minus part changes it to how many to add.
	if (leadingzeros==6) leadingzeros=0; // Don't add any if it was the right length to begin with.
	if (leadingzeros!=0) memset(origkey, '0', leadingzeros); // Create the right number of leading zeros.
	memset(origkey+leadingzeros, 0, 1);	// Null terminate.
	strcat(origkey+leadingzeros, &newkey[6]); // Add the remainder of the key.

	// Replace the dashes, needed for the crc32 call at the end...
	dashesin=origkey;
	keylen2=strlen(origkey);
	divide=keylen2/6;

	for(di=0; di<divide; di++) {
		strncat(newkey2, dashesin, 6);
		if (di>=(divide-1)) { // Do not place one at the end
		} else {
			strncat(newkey2, "-", 1);	// replace the dashes every 6 characters.
		};
		dashesin+=6;
	};
	strcpy(origkey, newkey2);	// copy the extracted named portion of the key.
	return;
};


/* PLEASE NOTE: The level parameter in RetrieveKeyInfo is expected to be 1 based!
For example: it expects 0 for unsigned, 1 to 4 for v2, 11 to 19 for v3 and 21 to
30 for ShortV3
*/
char RetrieveKeyInfo(int level, const char *encrypt_template, const char *name, unsigned long hardwareID, const char *origkey, const char *uninstallkey, struct KeyInformation *keyinfo) {
	unsigned short keydatecreated=0, keyotherinfo[5]={0,0,0,0,0};
	unsigned long templateID, keytemplateID=0, i[4];
	struct CipherKeyStruct *cipherkey;
	char cooked[512]="";
	int x, v2=0, v3=0, shortv3=0;
	char newkeyx[512]="";
	char newname[32]="";

	if (level>=20) {
		shortv3=1;
		level=level-20;
		/* ShortV3 keys can have signature levels 1 through 10 now */
		if (level<1 || level>10) return 0;

		/* Is this a "nameless" key? If so, make up a name for it. */
		if ((name==0) || (name[0]==0)) {
			strcpy(newkeyx, origkey);
			CheckNameless(newname, newkeyx);
			origkey=(const char *)newkeyx;
			name=(const char *)newname;
		};
	} else if (level>=10) {
		v3=1;
		level=level-10;
		/* V3 keys can now have signature levels 1 through 9 */
		if (level<1 || level>9) return 0;
	} else if (level!=0) {
		/* V2 keys can only have signature levels 1 through 4 */
		if (level<1 || level>4) return 0;
	};

	/* Figure out what the encryption template's number is. */
	CookText(cooked, encrypt_template);
	if (shortv3) {
		/* ShortV3 format */
		GetKeyMD5(i, cooked, 0);
		templateID=i[0]^i[1]^hardwareID;
	} else {
		/* V2 or conventional V3 format */
		templateID=((unsigned long)crc32(cooked, strlen(cooked), NewCRC32))^hardwareID;
	};

	/* Take the key apart. */
	if (level==0) {
		unsigned long k[2];
		const char *c=origkey;
		int digits=0;
		signed char cc;
		while (digits<8 && *c) {
			cc=hexdigit(*c++);
			if (cc>=0) { ++digits; k[0]=(k[0]<<4)|cc; };
		};

		while (digits<16 && *c) {
			cc=hexdigit(*c++);
			if (cc>=0) { ++digits; k[1]=(k[1]<<4)|cc; };
		};

		CookText(cooked, name);
		cipherkey=CreateCipherKey(cooked, strlen(cooked));
		Decipher(cipherkey, (char*)k, 2*sizeof(unsigned long));
		ReleaseCipherKey(cipherkey);

		keytemplateID=k[0];
		keydatecreated=(unsigned short)(k[1]>>16);
		keyotherinfo[0]=(unsigned short)(k[1]&0xFFFF);
	} else {
		char keybytes[512], signature[512], *kb=keybytes, *k1, *k2, hasstring=0;
		int keylength, siglength;

		if (shortv3) {
			const char *udigits="0123456789ABCDEFGHJKMNPQRTUVWXYZ",
				*ldigits="0123456789abcdefghjkmnpqrtuvwxyz";
			const char *c=origkey, *p;
			unsigned short a=0, bits=0;
			unsigned char value=0, firstdigit=1;
			BigInt n, n2, n3;

			n=BigInt_Create();
			n2=BigInt_Create();
			n3=BigInt_Create();

			if (origkey==0 || *origkey==0) return 0;
			while (*c) {
				p=strchr(udigits, *c);
				if (p) value=p-udigits;
				else {
					p=strchr(ldigits, *c);
					if (p) value=p-ldigits;
					else if (*c=='i' || *c=='I' || *c=='l' || *c=='L') value=1;
					else if (*c=='o' || *c=='O') value=0;
					else if (*c=='s' || *c=='S') value=5;
					else value=32;
				};
				++c;

				if (value<32) {
					if (firstdigit) {
						if (value==3) {
							/* A three as the first digit means the key contains
							a string too. Note it and ignore it, and leave the
							firstdigit item set. */
							hasstring=1;
							value=0;
						} else if (level==10) {
							/* All level 10 keys start with the digit 1. It
							doesn't convey any information other than the fact
							that they're level 10 keys; discard it. */
							if (value!=0) { value=0; firstdigit=0; };
						} else {
							if (value!=0 && value>=16) { value-=16; firstdigit=0; };
						};
					};
					BigInt_Shift(n, 5, n2);
					BigInt_SetU(n3, value);
					BigInt_Add(n2, n3, n);
				};
			};

			/* Spit out the bytes, in reverse order. */
			BigInt_Set(n3, 0xFF);
			if (level==10) {
				while (BigInt_Compare(n, BigInt_One())>0) {
					BigInt_And(n, n3, n2);
					*kb++=(unsigned char)BigInt_GetU(n2);
					BigInt_Shift(n, -8, n2);
					BigInt_Copy(n, n2);
				};
			} else {
				while (BigInt_Compare(n, BigInt_Zero())!=0) {
					BigInt_And(n, n3, n2);
					*kb++=(unsigned char)BigInt_GetU(n2);
					BigInt_Shift(n, -8, n2);
					BigInt_Copy(n, n2);
				};
			};

			/*if ((kb-keybytes)%2) *kb++=0;*/

			/* Reverse digits in keybytes */
			k1=keybytes;
			k2=kb-1;
			while (k1<k2) { char t=*k1; *k1=*k2; *k2=t; --k2; ++k1; };

			BigInt_Destroy(n3);
			BigInt_Destroy(n2);
			BigInt_Destroy(n);
		} else {
			const char *c=origkey;
			unsigned char value;
			while (c && *c) {
				c=GetTwoHexDigits(c, &value);
				if (c) *kb++=(char)value;
			};
		};
		keylength=kb-keybytes;

		/* Strip off signature here. For ShortV3 Level 10 keys, the signature
		will be the last 28 bytes, always. For earlier keys, it will be the
		last 6+(level*2) bytes. */
		if (level==10 && shortv3==1) siglength=28;
		else siglength=6+(level*2);
		memcpy(signature, keybytes+(keylength-siglength), siglength);
		keylength-=siglength;

		/* Check the signature, return false if not valid */
		/*x*/

		/* Decrypt the rest of the key */
		CookText(cooked, name);
		InitRandomGenerator(crc32(cooked, strlen(cooked), NewCRC32));
		for (x=0; x<keylength; ++x) keybytes[x]^=NextRandomRange(256);

		/* Strip off any string in the key */
		if (hasstring) keylength-=(*(keybytes+keylength-1)+1);

		/* Make sure it has an even number of bytes, add one (with a zero
		value) to the beginning if it doesn't. */
		if (keylength%2 != 0) {
			memmove(keybytes+1, keybytes, keylength);
			keybytes[0]=0;
			keylength++;
		};

		/* Assign bytes to their proper locations. */
		kb=keybytes;
		if (keylength>14) for (x=0; x<2; ++x) keyotherinfo[4]=(keyotherinfo[4]<<8)|(unsigned char)(*kb++);
		if (keylength>12) for (x=0; x<2; ++x) keyotherinfo[3]=(keyotherinfo[3]<<8)|(unsigned char)(*kb++);
		if (keylength>10) for (x=0; x<2; ++x) keyotherinfo[2]=(keyotherinfo[2]<<8)|(unsigned char)(*kb++);
		if (keylength>8) for (x=0; x<2; ++x) keyotherinfo[1]=(keyotherinfo[1]<<8)|(unsigned char)(*kb++);
		if (keylength>6) for (x=0; x<2; ++x) keyotherinfo[0]=(keyotherinfo[0]<<8)|(unsigned char)(*kb++);
		for (x=0; x<2; ++x) keydatecreated=(keydatecreated<<8)|(unsigned char)(*kb++);
		for (x=0; x<4; ++x) keytemplateID=(keytemplateID<<8)|(unsigned char)(*kb++);
	};

	/* Is the key good? If not, return false. */
	if (keytemplateID!=templateID) return 0;

	/* If an uninstall code is supplied, is that good? Again, if not, return false. */
	if (uninstallkey) {
		unsigned long ucrc=0;
		const char *c=uninstallkey;
		signed char cc;
		for (x=0; x<8 && *c;) {
			cc=hexdigit(*c++);
			if (cc>=0) { ucrc=(ucrc<<4)|cc; ++x; };
		};

		CookText(cooked, name);
		strcat(cooked, origkey);
		if (crc32(cooked, strlen(cooked), NewCRC32)!=ucrc) return 0;
	};

	/* Fill in the KeyInformation stuff, if supplied. */
	if (keyinfo) {
		InterpretDate(keydatecreated, &keyinfo->createdyear, &keyinfo->createdmonth, &keyinfo->createdday);
		for (x=0; x<5; ++x) keyinfo->otherinfo[x]=keyotherinfo[x];
	};

	return 1;
};

/*
	----------------------------------
	Test functions, to check the math.
	----------------------------------
*/

#ifdef TEST

	const int ADDCOUNT=6;
	const long addnumbers[][3]={
		{ 352, 48, 400, },
		{ -352, 48, -304, },
		{ 352, -48, 304, },
		{ -48, 352, 304, },
		{ -352, -48, -400, },
		{ 1000, -984, 16, },
	};

	int TestAddition() {
		BigInt a, b, answer;
		signed long i;
		int x;

		a=BigInt_Create();
		b=BigInt_Create();
		answer=BigInt_Create();

		for (x=0; x<ADDCOUNT; ++x) {
			BigInt_Set(a, addnumbers[x][0]);
			BigInt_Set(b, addnumbers[x][1]);
			BigInt_Add(a, b, answer);
			i=BigInt_Get(answer);
			if (i!=addnumbers[x][2]) {
				printf("Add test failed! %d + %d = %d, but answered %d\n", addnumbers[x][0],
					addnumbers[x][1], addnumbers[x][2], i);
				return 0;
			};
		};

		BigInt_Destroy(answer);
		BigInt_Destroy(b);
		BigInt_Destroy(a);

		printf("Passed addition tests!\n");
		return 1;
	};

	const int SUBCOUNT=9;
	const long subnumbers[][3]={
		{ 352, 48, 304, },
		{ -352, 48, -400, },
		{ 352, -48, 400, },
		{ -48, 352, -400, },
		{ -352, -48, -304, },
		{ 1000, 984, 16, },
		{ 984, 1000, -16, },
		{ 100000, 984, 99016, },
		{ 5, 0, 5, },
	};

	int TestSubtraction() {
		BigInt a, b, answer;
		signed long i;
		int x;

		a=BigInt_Create();
		b=BigInt_Create();
		answer=BigInt_Create();

		for (x=0; x<SUBCOUNT; ++x) {
			BigInt_Set(a, subnumbers[x][0]);
			BigInt_Set(b, subnumbers[x][1]);
			BigInt_Subtract(a, b, answer);
			i=BigInt_Get(answer);
			if (i!=subnumbers[x][2]) {
				printf("Subtraction test failed! %d - %d = %d, but answered %d\n", subnumbers[x][0],
					subnumbers[x][1], subnumbers[x][2], i);
				return 0;
			};
		};

		BigInt_Destroy(answer);
		BigInt_Destroy(b);
		BigInt_Destroy(a);

		printf("Passed subtraction tests!\n");
		return 1;
	};

	const int MULTCOUNT=5;
	const long multnumbers[][3]={
		{ 352, 48, 16896, },
		{ -352, 48, -16896, },
		{ 352, -48, -16896, },
		{ -48, 352, -16896, },
		{ -352, -48, 16896, },
	};

	int TestMultiplication() {
		BigInt a, b, answer;
		signed long i;
		int x;

		a=BigInt_Create();
		b=BigInt_Create();
		answer=BigInt_Create();

		for (x=0; x<MULTCOUNT; ++x) {
			BigInt_Set(a, multnumbers[x][0]);
			BigInt_Set(b, multnumbers[x][1]);
			BigInt_Multiply(a, b, answer);
			i=BigInt_Get(answer);
			if (i!=multnumbers[x][2]) {
				printf("Multiply test failed! %d * %d = %d, but answered %d\n",
					multnumbers[x][0], multnumbers[x][1], multnumbers[x][2], i);
				return 0;
			};
		};

		BigInt_Destroy(answer);
		BigInt_Destroy(b);
		BigInt_Destroy(a);

		printf("Passed multiplication tests!\n");
		return 1;
	};

	const int DIVCOUNT=4;
	const long divnumbers[][4]={
		{ 1000, 123, 8, 16, },
		{ -1000, 123, -8, 16, },
		{ 1000, -123, -8, 16, },
		{ -1000, -123, 8, 16, },
	};

	int TestDivision() {
		BigInt a, b, answer, remainder;
		signed long i, r;
		int x;

		a=BigInt_Create();
		b=BigInt_Create();
		answer=BigInt_Create();
		remainder=BigInt_Create();

		for (x=0; x<DIVCOUNT; ++x) {
			BigInt_Set(a, divnumbers[x][0]);
			BigInt_Set(b, divnumbers[x][1]);
			BigInt_Divide(a, b, answer, remainder);
			i=BigInt_Get(answer);
			r=BigInt_Get(remainder);
			if (i!=divnumbers[x][2] || r!=divnumbers[x][3]) {
				printf("Division test failed! %d / %d = %d r %d, but answered %d r %d\n",
					divnumbers[x][0], divnumbers[x][1], divnumbers[x][2], divnumbers[x][3], i, r);
				return 0;
			};
		};

		BigInt_Destroy(remainder);
		BigInt_Destroy(answer);
		BigInt_Destroy(b);
		BigInt_Destroy(a);

		printf("Passed division tests!\n");
		return 1;
	};

	const int POWERCOUNT=4;
	const long powernumbers[][3]={
		{ 2, 2, 4, },
		{ 2, 5, 32, },
		{ 2, 6, 64, },
		{ 3, 5, 243, },
	};

	int TestPowers() {
		BigInt a, b, answer;
		signed long i;
		int x;

		a=BigInt_Create();
		b=BigInt_Create();
		answer=BigInt_Create();

		for (x=0; x<POWERCOUNT; ++x) {
			BigInt_Set(a, powernumbers[x][0]);
			BigInt_Set(b, powernumbers[x][1]);
			BigInt_Power(a, b, answer);
			i=BigInt_Get(answer);
			if (i!=powernumbers[x][2]) {
				printf("Power test failed! %d * %d = %d, but answered %d\n",
					powernumbers[x][0], powernumbers[x][1], powernumbers[x][2], i);
				return 0;
			};
		};

		BigInt_Destroy(answer);
		BigInt_Destroy(b);
		BigInt_Destroy(a);

		printf("Passed power tests!\n");
		return 1;
	};

	const int SHIFTCOUNT=4;
	const long shiftnumbers[][3]={
		{ 0x1234, 5, 0x24680, },
		{ 0x1234, -5, 0x91, },
		{ 0x1234, 10, 0x48D000, },
		{ 0x1234, -10, 0x04, },
	};

	int TestShift() {
		BigInt a, answer;
		signed long i;
		int x;

		a=BigInt_Create();
		answer=BigInt_Create();

		for (x=0; x<SHIFTCOUNT; ++x) {
			BigInt_Set(a, shiftnumbers[x][0]);
			BigInt_Shift(a, shiftnumbers[x][1], answer);
			i=BigInt_Get(answer);
			if (i!=shiftnumbers[x][2]) {
				printf("Shift test failed! %d shift %d = %d, but answered %d\n",
					shiftnumbers[x][0], shiftnumbers[x][1], shiftnumbers[x][2], i);
				return 0;
			};
		};

		BigInt_Destroy(answer);
		BigInt_Destroy(a);

		printf("Passed shift tests!\n");
		return 1;
	};

	const int GCDCOUNT=2;
	const long gcdnumbers[][3]={
		{ 10, 5, 5, },
		{ 100, 75, 25, },
	};

	int TestGCD() {
		BigInt a, b, answer;
		signed long i;
		int x;

		a=BigInt_Create();
		b=BigInt_Create();
		answer=BigInt_Create();

		for (x=0; x<GCDCOUNT; ++x) {
			BigInt_Set(a, gcdnumbers[x][0]);
			BigInt_Set(b, gcdnumbers[x][1]);
			BigInt_GCD(a, b, answer);
			i=BigInt_Get(answer);
			if (i!=gcdnumbers[x][2]) {
				printf("GCD test failed! GCD(%d, %d) = %d, but answered %d\n",
					gcdnumbers[x][0], gcdnumbers[x][1], gcdnumbers[x][2], i);
				return 0;
			};
		};

		BigInt_Destroy(answer);
		BigInt_Destroy(b);
		BigInt_Destroy(a);

		printf("Passed GCD tests!\n");
		return 1;
	};

	int TestKeyCRC() {
		char *teststring="elemenopuss"; // 11 characters
		if (GetKeyCRC(teststring, 2)!=0x95880AEB) return 0; // 'lemeneposus'
		if (GetKeyCRC(teststring, 3)!=0x99CA4256) return 0; // 'elenemuposs'
		if (GetKeyCRC(teststring, 4)!=0xDA53CEA9) return 0; // 'meleponessu'
		if (GetKeyCRC(teststring, 5)!=0xF29D21E2) return 0; // 'emelesupons'
		printf("Passed KeyCRC tests!\n");
		return 1;
	};

	void BigIntToString(BigInt n, char *target) {
		char *t=target;
		BigInt temp=BigInt_Create();
		BigInt temp2=BigInt_Create();
		BigInt base=BigInt_Create();
		BigInt_SetU(base, 10);

		while (BigInt_Compare(n, BigInt_Zero())>0) {
			BigInt_Divide(n, base, temp, temp2);
			*t++='0'+(unsigned char)(BigInt_GetU(temp2));
			BigInt_Copy(n, temp);
		};
		*t=0;
		mystrrev(target);

		BigInt_Destroy(base);
		BigInt_Destroy(temp2);
		BigInt_Destroy(temp);
	};

	void MakeP(BigInt p, int level) {
		BigInt temp, temp2;
		temp=BigInt_Create();
		temp2=BigInt_Create();

		BigInt_Set(temp, 1);
		BigInt_Shift(temp, (level+4)*8, p);
		BigInt_Set(temp, primeoffsets[level]);
		BigInt_Add(p, temp, temp2);
		BigInt_Copy(p, temp2);

		BigInt_Destroy(temp2);
		BigInt_Destroy(temp);
	};

	int TestKeyNumber() {
		char *teststring="elemenopuss", temp[512];
		BigInt p, keynumber;
		int x;

		p=BigInt_Create();
		keynumber=BigInt_Create();

		for (x=0; x<8; ++x) {
			MakeP(p, x);
			GenerateKeyNumberFromString(teststring, p, &keynumber, (x==0 ? KS_V2 : KS_V3), x);
			BigIntToString(keynumber, temp);
			printf("Level %u: %s\n", x, temp);
		};

		BigInt_Destroy(keynumber);
		BigInt_Destroy(p);
		return 0;
	};

	void main() {
		//char keybytes[512], pvtkey[]="pvtkey";
		//int keylength=0, x;

		if (!TestKeyNumber()) return;
		if (!TestKeyCRC()) return;
		if (!TestAddition()) return;
		if (!TestSubtraction()) return;
		if (!TestMultiplication()) return;
		if (!TestDivision()) return;
		if (!TestPowers()) return;
		if (!TestShift()) return;
		if (!TestGCD()) return;
	};

#endif

#ifdef CALLED_FROM_JAVA

	int HasBackslashQuoteBegin(char *string) {
		return (string[0]=='\\' && string[1]=='\"');
	};

	int HasBackslashQuoteEnd(char *string) {
		char *e=strchr(string, 0);
		if (e-2>=string) return (*(e-2)=='\\' && *(e-1)=='\"');
		return 0;
	};

	int StripBackslashQuoteBegin(char *string) {
		memmove(string, string+2, strlen(string+2)+1);
		return 0;
	};

	int StripBackslashQuoteEnd(char *string) {
		char *e=strchr(string, 0);
		if (e-2>=string) *(e-2)=0;
		return 0;
	};

#endif


/*
	--------
	MakeDate
	--------

	Most implimentations can ignore this function. It creates an Armadillo-
	formatted date, for use in the "otherinfo" parameter of CreateKey for
	expire-by-date keys. The year should be the four-digit year, the month
	should be 1 to 12, and the day should be 1 to 31. It returns 0xFFFF on
	error (bad date or date before 01Jan99).
*/

/*
unsigned short MakeDate(unsigned int year, unsigned int month, unsigned int day) {
	const unsigned long secondsperday=(24*60*60);
	const int dateoffset=10592;

	struct tm tm;
	tm.tm_year=year-1900;
	tm.tm_mon=month-1;
	tm.tm_mday=day;
	tm.tm_hour=0;
	tm.tm_min=0;
	tm.tm_sec=0;
	unsigned long seconds=mktime(&tm);
	if (seconds==(unsigned long)(-1)) return (unsigned short)(-1);

	long days=(seconds/secondsperday);
	if (days<dateoffset) return (unsigned short)(-1);

	return (unsigned short)(days-dateoffset);
};
*/

/*
	-------------------------
	The SWREG "main" function
	-------------------------

	SWREG passes variables in the environment, and expects the return value to be
	printed as "<softshop>keycode</softshop>" to stdout. The signature level and
	encryption template are compiled into the program as hardcoded values.

	Limitations:

		Otherinfo and hardwareID values are not supported -- there's nowhere to
		safely put them.

		Always uses the billing user's first and last name. No option to use the
		shipping customer's name or the company name.

		Unsigned keys are considered "level 0" for this function.
*/

#ifdef SWREG

char x2c(char *what) {
	register char digit;

	digit = (what[0] >= 'A' ? ((what[0] & 0xdf) - 'A')+10 : (what[0] - '0'));
	digit *= 16;
	digit += (what[1] >= 'A' ? ((what[1] & 0xdf) - 'A')+10 : (what[1] - '0'));
	return(digit);
}

void unescape_url(char *url) {
	register int x,y;

	for(x=0,y=0;url[y];++x,++y) {
		if((url[x] = url[y]) == '%') {
			url[x] = x2c(&url[y+1]);
			y+=2;
		};
	};
	url[x] = '\0';
};

int my_strnicmp(const char *str1, const char *str2, int len) {
	const char *c1=str1, *c2=str2, *e1=c1+len;

	while (c1<e1) {
		if (toupper(*c1)!=toupper(*c2)) return toupper(*c1)-toupper(*c2);
		if (*c1==0) return 0;
		++c1;
		++c2;
	};

	return 0;
};

char *cgi_getenv(const char *varname, char *varstring, int len) {
	/* Search the QUERY_STRING environment variable to find the requested
	"real" variable. */
	const char *vars=getenv("QUERY_STRING");
	int namelen=strlen(varname), vlen;
	const char *v, *e;

	if (vars) {
		v=vars;
		while (*v) {
			e=strchr(v, '&');
			if (!e) e=strchr(v, 0);
			if (!my_strnicmp(v, varname, namelen) && *(v+namelen)=='=') {
				v+=namelen+1;
				vlen=e-v;
				if (vlen>len-1) vlen=len-1;
				memcpy(varstring, v, vlen);
				*(varstring+vlen)=0;
				unescape_url(varstring);
				return varstring;
			};

			if (e) v=e+1;
			else break;
		};
	};

	return 0;
};

static void cgi_printheader() {
	/*printf("Content-type: text/html\n\n") ;*/
	printf("<html>\n") ;
	printf("<head><title>Armadillo Results</title></head>\n") ;
	printf("<body>\n") ;
};

static void cgi_printfooter() {
	printf("</body>\n") ;
	printf("</html>\n") ;
};

int main() {
	char username[512]="", privatekey[512]="", keytext[512]="", temp[512], *c;
	unsigned short otherinfo[5]={0,0,0,0,0};
	unsigned long hardwareID=0;
	int y=0, level=-1;

	strcpy(privatekey, ENCRYPTION_TEMPLATE);
	level=SIGNATURE_LEVEL-1;

	/* Collect the username */
	c=cgi_getenv("initals", temp, 255); /* Deliberately misspelled; this is the user's first name */
	if (c) strcat(username, c);
	c=cgi_getenv("name", temp, 255); /* The user's last name */
	if (c) {
		if (strlen(username)) strcat(username, " ");
		strcat(username, c);
	};
	if (!strlen(username) || !strlen(privatekey)) {
		cgi_printheader();
		printf("<softshop>Error: No username, or blank encryption template!</softshop>");
		cgi_printfooter();
		return 1;
	};

	/* Now create the key and write it out. */
	if (level<0) strcpy(keytext, CreateKey(username, privatekey, otherinfo[0], hardwareID));
	else strcpy(keytext, CreateV2Key(level, privatekey, username, hardwareID, otherinfo[0], otherinfo[1], otherinfo[2], otherinfo[3], otherinfo[4]));

	/* Print the CGI response header and key (with thanks to Jose Neto). */
	cgi_printheader();
	printf("<softshop>%s</softshop>", keytext);
	cgi_printfooter();
	return 0;
};

#endif

/*
	----------------------------
	The standard "main" function
	----------------------------

	For version 1 ("unsigned") keys, the parameters are:

		User's name;
		Encryption template;
		Otherinfo;
		Hardware ID

		Example: KeyMaker.exe "Chad Nelson" "pvtkey" 10 0

	For version 2 ("signed") keys, the parameters have changed. They are:

		The signature level, preceded by a '-' or '/'; (MUST be first in line!)
		User's name;
		Encryption template;
		Hardware ID, or zero if not hardware locked;
		Up to five 'otherinfo' numbers

		Example: KeyMaker.exe /2 "Chad Nelson" "pvtkey" 0 10

	Version 3 signed keys use the same parameters as the version 2 ones. The
	only difference is that you must add ten to the signature level; for
	example, a v3 signature level 2 key is considered signature level 12
	instead (for purposes of this key generator), and would be specified like
	this:

		Example: KeyMaker.exe /12 "Chad Nelson" "pvtkey" 0 10

	We've also provided a CreateV3Key function, identical to CreateV2Key, to
	handle this for you if you're not using the standard main() function.

	(For ShortV3 keys, add 20 to the signature level, otherwise it's identical
	to v2 and v3 keys.)

	To add a string to the key, use a ShortV3 key and the /str option, like
	this:

		Example: KeyMaker.exe /12 /str "String!" "Chad Nelson" "pvtkey" 0 10

	Note that the string must be in quotation marks if it contains any spaces.
*/

#ifdef STDMAIN
int main(int argc, char *argv[]) {
	char username[512]="", privatekey[512]="", keystring[512]="", parsedargs[10][512];
	unsigned short otherinfo[5]={0,0,0,0,0};
	unsigned long hardwareID=0;
	int x, y, level=-1;

	#ifdef CALLED_FROM_JAVA
		int started=0;

		for (x=1, y=1; x<argc; ++x) {
			if (started) {
				if (HasBackslashQuoteEnd(argv[x])) {
					StripBackslashQuoteEnd(argv[x]);
					strcat(parsedargs[y++], argv[x]);
					started=0;
				} else {
					strcat(parsedargs[y], argv[x]);
					strcat(parsedargs[y], " ");
				};
			} else {
				if (HasBackslashQuoteBegin(argv[x])) {
					StripBackslashQuoteBegin(argv[x]);
					if (HasBackslashQuoteEnd(argv[x])) {
						StripBackslashQuoteEnd(argv[x]);
						strcpy(parsedargs[y++], argv[x]);
					} else {
						strcpy(parsedargs[y], argv[x]);
						strcat(parsedargs[y], " ");
						started=1;
					};
				} else strcpy(parsedargs[y++], argv[x]);
			};
		};
	#else
		for (x=1; x<argc; ++x) strcpy(parsedargs[x], argv[x]);
	#endif

	for (x=1, y=0; x<argc; ++x) {
		if (x<3 && (parsedargs[x][0]=='/' || parsedargs[x][0]=='-')) {
			if (!stricmp(parsedargs[x]+1, "str")) {
				strcpy(keystring, parsedargs[++x]);
				keystring[64]=0; /* Must be 64 characters or less. */
			} else if (parsedargs[x][1]>='0' && parsedargs[x][1]<='9') level=atoi(parsedargs[x]+1)-1;
		} else {
			if (y==0) strcpy(username, parsedargs[x]);
			else if (y==1) strcpy(privatekey, parsedargs[x]);
			else if (y==2) {
				if (level<0) otherinfo[0]=atoi(parsedargs[x]);
				else hardwareID=hextoint(parsedargs[x]);
			} else if (y==3) {
				if (level<0) hardwareID=hextoint(parsedargs[x]);
				else otherinfo[0]=atoi(parsedargs[x]);
			} else if (y==4) otherinfo[1]=atoi(parsedargs[x]);
			else if (y==5) otherinfo[2]=atoi(parsedargs[x]);
			else if (y==6) otherinfo[3]=atoi(parsedargs[x]);
			else if (y==7) otherinfo[4]=atoi(parsedargs[x]);
			++y;
		};
	};

	if (!strlen(privatekey)) return 1;

	if (level<0) {
		printf("%s\n", CreateKey(username, privatekey, otherinfo[0], hardwareID));
	} else {
		printf("%s\n", CreateSignedKey(level, privatekey, username, hardwareID, otherinfo[0], otherinfo[1], otherinfo[2], otherinfo[3], otherinfo[4], keystring));
	};

	return 0;
};
#endif
