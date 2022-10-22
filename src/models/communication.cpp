#include <utility>

#include "./communication.hpp"

Communication::Communication(const otf2::chrono::duration &start, const otf2::chrono::duration &anEnd,
                             const otf2::definition::location &sender, const otf2::definition::location &receiver,
                             uint32_t receiverRank) : start(start), end(anEnd), sender(sender), receiver(receiver),
                                                      receiverRank(receiverRank) {}

