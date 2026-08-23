#ifndef FLAGS_MAKROS_H
#define FLAGS_MAKROS_H

/* masks */
#define S_FLAG_MASK  ((byte_t)(1u << 7u))
#define Z_FLAG_MASK  ((byte_t)(1u << 6u))
#define AC_FLAG_MASK ((byte_t)(1u << 4u))
#define P_FLAG_MASK  ((byte_t)(1u << 2u))
#define C_FLAG_MASK  ((byte_t)(1u << 0u))

/* read flags -> always 0 or 1 */
#define R_S_FLAG(x)  (((x) & S_FLAG_MASK)  != 0u)
#define R_Z_FLAG(x)  (((x) & Z_FLAG_MASK)  != 0u)
#define R_AC_FLAG(x) (((x) & AC_FLAG_MASK) != 0u)
#define R_P_FLAG(x)  (((x) & P_FLAG_MASK)  != 0u)
#define R_C_FLAG(x)  (((x) & C_FLAG_MASK)  != 0u)

/* set flags */
#define S_S_FLAG(x)  ((x) |= S_FLAG_MASK)
#define S_Z_FLAG(x)  ((x) |= Z_FLAG_MASK)
#define S_AC_FLAG(x) ((x) |= AC_FLAG_MASK)
#define S_P_FLAG(x)  ((x) |= P_FLAG_MASK)
#define S_C_FLAG(x)  ((x) |= C_FLAG_MASK)

/* clear flags */
#define DEL_S_FLAG(x)  ((x) &= (byte_t)~S_FLAG_MASK)
#define DEL_Z_FLAG(x)  ((x) &= (byte_t)~Z_FLAG_MASK)
#define DEL_AC_FLAG(x) ((x) &= (byte_t)~AC_FLAG_MASK)
#define DEL_P_FLAG(x)  ((x) &= (byte_t)~P_FLAG_MASK)
#define DEL_C_FLAG(x)  ((x) &= (byte_t)~C_FLAG_MASK)

/* flip flags */
#define F_S_FLAG(x)  ((x) ^= S_FLAG_MASK)
#define F_Z_FLAG(x)  ((x) ^= Z_FLAG_MASK)
#define F_AC_FLAG(x) ((x) ^= AC_FLAG_MASK)
#define F_P_FLAG(x)  ((x) ^= P_FLAG_MASK)
#define F_C_FLAG(x)  ((x) ^= C_FLAG_MASK)

#endif