#ifndef _LGY_MD5_H
#define _LGY_MD5_H

#include <cstdint>

/* MD5 Class. */
class PasMD5
{
public:
    PasMD5() { MD5Init(); }

    virtual ~PasMD5() = default;

	void MD5Update (const unsigned char * input, unsigned int inputLen);

	void MD5Final (unsigned char digest[16]);

	void TwiceMD5(unsigned char * input, unsigned int inputLen, unsigned char digest2[16]);

private:
	void MD5Init ();

    static void MD5Transform (uint32_t state[4], const unsigned char block[64]);

    static void MD5_memcpy (unsigned char * output, const unsigned char * input, unsigned int len);

    static void Encode (unsigned char * output, const uint32_t * input, unsigned int len);

    static void Decode (uint32_t * output, const unsigned char * input, unsigned int len);

    static void MD5_memset (unsigned char * output, int value, unsigned int len);

private:
	uint32_t state[4];			    /* state (ABCD) */
	uint32_t count[2];				/* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];       /* input buffer */
	unsigned char PADDING[64];		/* What? */
};

#endif
