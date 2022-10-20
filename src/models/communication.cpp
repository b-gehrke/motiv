#include <utility>

#include "./communication.hpp"

Communication::Communication(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                             std::string from, std::string to) : start(start),
                                                                 end(anEnd),
                                                                 from(std::move(from)),
                                                                 to(std::move(to)) {}
