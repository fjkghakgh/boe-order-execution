#ifndef NEW_OP_FIELD
#error You need to define NEW_OP_FIELD
#else

NEW_OP_FIELD(symbol, 2, 1, 8)
NEW_OP_FIELD(last_mkt, 7, 8, 4)
NEW_OP_FIELD(fee_code, 8, 1, 2)
#undef NEW_OP_FIELD

#endif
