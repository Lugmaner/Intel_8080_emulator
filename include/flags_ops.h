#ifndef FLAGS_OPS_H
#define FLAGS_OPS_H

//  read flags
#define R_S_FLAG(x) (x & (1u << 7u))
#define R_Z_FLAG(x) (x & (1u << 6u))
#define R_AC_FLAG(x) (x & (1u << 4u))
#define R_P_FLAG(x) (x & (1u << 2u))
#define R_C_FLAG(x) (x & 1u)

//  set flags
#define S_S_FLAG(x) (x |= (1u << 7u))
#define S_Z_FLAG(x) (x |= (1u << 6u))
#define S_AC_FLAG(x) (x |= (1u << 4u))
#define S_P_FLAG(x) (x |= (1u << 2u))
#define S_C_FLAG(x) (x |= 1u)

//  delete flags
#define DEL_S_FLAG(x) (x &= ~(1u << 7u))
#define DEL_Z_FLAG(x) (x &= ~(1u << 6u))
#define DEL_AC_FLAG(x) (x &= ~(1u << 4u))
#define DEL_P_FLAG(x) (x &= ~(1u << 2u))
#define DEL_C_FLAG(x) (x &= ~1u)

#endif