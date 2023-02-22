#if !defined(OP_FIELD_FOR_MESSAGE)
#error You need to define OP_FIELDS_FOR_MESSAGE macro
#else

OP_FIELD_FOR_MESSAGE(OrderExecution, 2, 1)
OP_FIELD_FOR_MESSAGE(OrderRestatement, 5, 2)
OP_FIELD_FOR_MESSAGE(OrderRestatement, 6, 1)
OP_FIELD_FOR_MESSAGE(OrderExecution, 7, 8)
OP_FIELD_FOR_MESSAGE(OrderExecution, 8, 1)

#undef FIELDS_COUNT
#undef OP_FIELD_FOR_MESSAGE

#endif
