#include "collectivecommunication.hpp"

CollectiveCommunication::CollectiveCommunication(const otf2::chrono::duration &startTime,
                                                 const otf2::chrono::duration &endTime,
                                                 const types::communicator &communicator, const uint32_t root,
                                                 const std::vector<Participation> &participants) : startTime(startTime),
                                                                                                   endTime(endTime),
                                                                                                   communicator(
                                                                                                       communicator),
                                                                                                   root(root),
                                                                                                   participants(
                                                                                                       participants) {}
