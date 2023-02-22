#if !defined(NEW_FIELD) || !defined(OP_FIELD_OFFSET)
#error You need to define NEW_FIELD macro & OP_FIELD_OFFSET
#else

OP_FIELD_OFFSET(69)

NEW_FIELD(cl_ord_id, 18)
NEW_FIELD(exec_id, 38)
NEW_FIELD(filled_volume, 46)
NEW_FIELD(price, 50)
NEW_FIELD(active_volume, 58)
NEW_FIELD(liquidity_indicator, 62)

#undef NEW_FIELD
#undef OP_FIELD_OFFSET

#endif
