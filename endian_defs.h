/// Endian transformation
/**
 * @file endian_defs.h
 * @author Takeshi Enomoto
 *
 * Macros obtained from /usr/include/arch/_OSByteOrder.h
 */
#define SwapConstInt16(x) \
      ((uint16_t)((((uint16_t)(x) & 0xff00) >> 8) | \
                        (((uint16_t)(x) & 0x00ff) << 8)))
#define SwapConstInt32(x) \
      ((uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) | \
                        (((uint32_t)(x) & 0x00ff0000) >>  8) | \
                        (((uint32_t)(x) & 0x0000ff00) <<  8) | \
                        (((uint32_t)(x) & 0x000000ff) << 24)))

#define SwapConstInt64(x) \
      ((uint64_t)((((uint64_t)(x) & 0xff00000000000000ULL) >> 56) | \
                        (((uint64_t)(x) & 0x00ff000000000000ULL) >> 40) | \
                        (((uint64_t)(x) & 0x0000ff0000000000ULL) >> 24) | \
                        (((uint64_t)(x) & 0x000000ff00000000ULL) >>  8) | \
                        (((uint64_t)(x) & 0x00000000ff000000ULL) <<  8) | \
                        (((uint64_t)(x) & 0x0000000000ff0000ULL) << 24) | \
                        (((uint64_t)(x) & 0x000000000000ff00ULL) << 40) | \
                        (((uint64_t)(x) & 0x00000000000000ffULL) << 56)))

#define eno_endian_swap_int16(x) SwapConstInt16(x)
#define eno_endian_swap_int32(x) SwapConstInt32(x)
#define eno_endian_swap_int64(x) SwapConstInt64(x)
