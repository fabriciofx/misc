/**
 * FIXME: this version has some problems with ASan Address
 */
u64
chars_length(const char *chars)
{
    const char *chr = chars;
    const u64 misalign = N_BYTES_NOT_ALIGNED64(chr);
    for (u64 length = 0; length < misalign; length++, chr++) {
        if (*chr == CHARS_END) {
            return length;
        }
    }
    for (const u64 *block = AS_U64(chr); ;block++) {
        if (U64_HAS_ZERO8(*block)) {
            for (const char *chr_blk = AS_CONST_CHARS(block); ; chr_blk++) {
                if (*chr_blk == CHARS_END) {
                    return chr_blk - chars;
                }
            }
        }
    }
}

i64
chars_compare(const char *chars1, const char *chars2)
{
    const u64 *block1;
    const u64 *block2;
    i64 misalign = N_BYTES_NOT_ALIGNED64(chars1);
    while (misalign-- > 0) {
        if (*chars1 != *chars2 || (*chars1 & *chars2) == CHARS_END) {
            return *chars1 - *chars2;
        }
        chars1++;
        chars2++;
    }
    block1 = AS_U64(chars1);
    block2 = AS_U64(chars2);
    while (TRUE) {
        if (*block1 != *block2) {
            chars1 = AS_CONST_CHARS(block1);
            chars2 = AS_CONST_CHARS(block2);
            while (TRUE) {
                if (*chars1 != *chars2 || (*chars1 & *chars2) == CHARS_END) {
                    return *chars1 - *chars2;
                }
                chars1++;
                chars2++;
            }
        }
        block1++;
        block2++;
    }
}
