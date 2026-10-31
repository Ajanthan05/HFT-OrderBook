#pragma once

#include <cstdint>

// #include "core/types.hpp"

namespace hftob {
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



}  // namespace itch
}  // namespace hftob
