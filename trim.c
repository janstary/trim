/* Read a stream of unsigned 32bit integers from standard input,
 * and zero the given number of lowest bits of each. */

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int
tail(uint32_t sample)
{
	int i;
	for (i = 0; i < 32; i++)
		if (sample & (1 << i))
			break;
	return i;
}

uint32_t
ru32le(unsigned char *b)
{
	return (b[0] << 0) | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
}

uint32_t
ru32be(unsigned char *b)
{
	return (b[3] << 0) | (b[2] << 8) | (b[1] << 16) | (b[0] << 24);
}

int
main(int argc, char** argv)
{
	int b = 0;
	int t = 0;
	int T = 32;
	uint8_t buf[4];
	int32_t sample, z;

	b = (argc == 1) ? 0 : strtonum(argv[1], 0, 32, NULL);
	z = (0xffffffff >> (32 - b));

	while (read(0, &buf, 4) == 4) {
		sample = ru32le(buf);
		if (b) {
			sample &= ~z;
		} else {
			if ((t = tail(sample)) < T)
				T = t;
		}
		write(1, &sample, 4);
	}

	if ((b == 0) && T) {
		fprintf(stderr, "%d lower bits unused\n", T);
	}

	return 0;
}
