#if !defined(LOC_FIELD) || !defined(LOC_VAR_FIELD)
#error You need to define FIELD and VAR_FIELD macro
#else

LOC_VAR_FIELD(symbol, 8)
LOC_FIELD(leaves_qty, binary4, unsigned)
LOC_VAR_FIELD(last_mkt, 4)
LOC_VAR_FIELD(fee_code, 2)
LOC_FIELD(secondary_order_id, binary8, std::string)
LOC_VAR_FIELD(cl_ord_id, 20)
LOC_FIELD(exec_id, binary8, std::string)
LOC_FIELD(filled_volume, binary4, unsigned)
LOC_FIELD(price, price_t, double)
LOC_FIELD(active_volume, binary4, unsigned)
LOC_FIELD(liquidity_indicator, liquidity_indicator_t, LiquidityIndicator)
LOC_FIELD(reason, reason_t, RestatementReason)

#undef LOC_FIELD
#undef LOC_VAR_FIELD

#endif
