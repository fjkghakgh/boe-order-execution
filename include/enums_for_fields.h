/*
 * Order Execution
 */
#pragma once
enum class LiquidityIndicator
{
    Added,
    Removed,
    Unknown
};

/*
 * Order Restatement
 */
enum class RestatementReason
{
    Reroute,
    LockedInCross,
    Wash,
    Reload,
    LiquidityUpdated,
    Unknown
};
