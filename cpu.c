#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <cpuid.h>

int main()
{
	int i;
	uint32_t eax, ebx, ecx, edx;
	uint64_t xcr0;

	asm volatile(
		"xorq %%rcx, %%rcx\n\t"
		"xgetbv\n\t"
		: "=a"(eax), "=d"(edx)
		:
		:
	);

	printf("XCR0: EAX = %08" PRIx32 "; EDX = %08" PRIx32 "\n", eax, edx);
	xcr0 = ((uint64_t)edx << 32) | eax;

	if (!__get_cpuid_count(0x0D, 0, &eax, &ebx, &ecx, &edx))
		return 0;

	printf("0Dh(0): EAX = %08" PRIx32 "; EDX = %08" PRIx32 "\n", eax, edx);
	printf("0Dh(0): ECX = %" PRId32 "; EBX = %" PRId32 "\n", ecx, ebx);

	for (i = 2; i < 64; ++i)
	{
		if (!(xcr0 & ((uint64_t)1 << i)))
			continue;

		__cpuid_count(0x0D, i, eax, ebx, ecx, edx);
		printf("0Dh(%d): EAX = %" PRId32 "; EBX = %" PRId32 "; ECX = %"
				PRIx32 "\n", i, eax, ebx, ecx);
	}
}
