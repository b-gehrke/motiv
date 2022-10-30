#include "filetrace.hpp"

FileTrace::FileTrace(std::vector<Slot> &slotss,
                     std::vector<BlockingP2PCommunication> &blockingComm,
                     std::vector<NonBlockingP2PCommunication> &nonBlockingComm,
                     std::vector<CollectiveCommunication> &collectiveComm,
                     otf2::chrono::duration runtime) :
    slots_(slotss),
    blockingComm_(blockingComm),
    nonBlockingComm_(nonBlockingComm),
    collectiveComm_(collectiveComm) {
    runtime_ = runtime;
    startTime_ = otf2::chrono::duration(0);
}

Range<Slot> FileTrace::getSlots() const {
    return Range(slots_);
}

Range<BlockingP2PCommunication> FileTrace::getBlockingP2PCommunications() const {
    return Range(blockingComm_);
}

Range<NonBlockingP2PCommunication> FileTrace::getNonBlockingP2PCommunications() const {
    return Range(nonBlockingComm_);
}

Range<CollectiveCommunication> FileTrace::getCollectiveCommunications() const {
    return Range(collectiveComm_);
}
