#if !defined(NEW_FIELD) || !defined(OP_FIELD_OFFSET)
#error You need to define NEW_FIELD macro & OP_FIELD_OFFSET
#else

OP_FIELD_OFFSET(48)

NEW_FIELD(cl_ord_id, 18)
NEW_FIELD(reason, 46)

#undef NEW_FIELD
#undef OP_FIELD_OFFSET

#endif
