#pragma once

#include <cstdint>

namespace hftob {

// ITCH (NASDAQ's market data protocol) represents prices using an unsigned 4-byte integer (uint32_t) with 4 implied decimal places.
// We keep them as a signed 64-bit integer of those ticks and only convert to a double for display.
// i.e. the integer is the price in units of 1/10000 of a dollar.
using Price    = std::int64_t;

/// One price tick == $0.0001.
constexpr Price kPriceScale = 10000;

constexpr double to_SGD(Price ticks) {
    return static_cast<double>(ticks) / static_cast<double>(kPriceScale);
}

enum class Side : char { Buy = 'B', Sell = 'S', None = '\0' };

namespace itch {

enum class MsgType : char {
    Unknown                = '\0',
    SystemEvent            = 'S',
    StockDirectory         = 'R',
    AddOrder               = 'A',
    AddOrderMpid           = 'F',
    OrderExecuted          = 'E',
    OrderExecutedWithPrice = 'C',
    OrderCancel            = 'X',
    OrderDelete            = 'D',
    OrderReplace           = 'U',
    Trade                  = 'P',
    CrossTrade             = 'Q',
};

struct Message {
    MsgType       type           = MsgType::Unknown;
    std::uint16_t stock_locate   = 0;   // per-day instrument index (header)
    std::uint64_t timestamp      = 0;   // nanoseconds since midnight
    std::uint64_t order_ref      = 0;   // Add/Exec/Cancel/Delete; Replace=original
    std::uint64_t new_order_ref  = 0;   // OrderReplace only
    std::uint64_t match_number   = 0;   // Exec/Trade
    Side          side           = Side::None;  // AddOrder / Trade
    std::uint32_t shares         = 0;   // add | executed | cancelled | replace shares
    Price         price          = 0;   // add | replace | exec-with-price
    char          stock[8]       = {};  // Add/Trade/StockDirectory (space-padded)
    char          event_code     = 0;   // SystemEvent
};

}  // namespace itch
}  // namespace hftob
