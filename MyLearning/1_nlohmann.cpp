#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

using json = nlohmann::json;

void Print_NDJSON() {
    std::string input = R"({"type":"tick","symbol":"SGDSL","bid":259.78})";

    try {
        json msg = json::parse(input);

        const std::string type = msg.at("type").get<std::string>();

        const std::string symbol = msg.at("symbol").get<std::string>();

        const double bid = msg.at("bid").get<double>();

        std::cout << "Type: " << type << '\n';
        std::cout << "Symbol: " << symbol << '\n';
        std::cout << "Bid: " << bid << '\n';
    }
    catch (const json::exception& e) {
        std::cerr << "JSON Error:" << e.what() << "\n";
    }
}

void Make_NDJSON() {
    json tick = {
        {"v", 1},
        {"type", "tick"},
        {"symbol", "SGDSL"},
        {"bid", 259.78},
        {"ask", 259.80}
    };

    std::string ndjson = tick.dump() + "\n";
    // dump() generates JSON. Adding \n makes it an NDJSON record.

    std::cout << ndjson << "\n";
}

int main() {
    json message;

    message["type"] = "tick";
    message["symbol"] = "EURUSD";
    message["bid"] = 1.0850;
    message["ask"] = 1.0852;

    std::cout << message.dump() << '\n';

    Print_NDJSON();
    Make_NDJSON();
    return 0;
}