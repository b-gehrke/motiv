#include "TimeUnit.hpp"

TimeUnit::TimeUnit(TimeUnit::Unit unit) : unit(unit) {}

QString TimeUnit::str() const {
    switch (this->unit) {
        case NanoSecond:
            return "ns";
        case MicroSecond:
            return "μs";
        case MilliSecond:
            return "ms";
        case Second:
            return "s";
        case Minute:
            return "m";
        case Hour:
            return "h";
        default:
            throw std::invalid_argument("Unknown TimeUnit");
    }
}

TimeUnit::TimeUnit(QString unit) {
    std::__1::map<QString, Unit> lut = {
            {"ns", NanoSecond},
            {"μs", MicroSecond},
            {"ms", MilliSecond},
            {"s", Second},
            {"m", Minute},
            {"h", Hour},
    };

    auto it = lut.find(unit);
    if (it == lut.end()) {
        throw std::invalid_argument("Unknown TimeUnit");
    }

    this->unit = it->second;
}

double TimeUnit::multiplier() const {
    switch (this->unit) {
        case TimeUnit::NanoSecond:
            return 1;
        case TimeUnit::MicroSecond:
            return 1e3;
        case TimeUnit::MilliSecond:
            return 1e6;
        case TimeUnit::Second:
            return 1e9;
        case TimeUnit::Minute:
            return 60e9;
        case TimeUnit::Hour:
            return 60 * 60e9;
        default:
            // This should be caught by the constructors
            __builtin_unreachable();
    }
}