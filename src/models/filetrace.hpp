//
// Created by bjoern on 21.10.22.
//

#ifndef MOTIV_FILETRACE_HPP
#define MOTIV_FILETRACE_HPP

#include "subtrace.hpp"

class FileTrace : public SubTrace {
private:
    std::vector<Slot>& slotsVec_;
    std::vector<Communication> &communicationsVec_;
public:
    FileTrace(std::vector<Slot>& slotss, std::vector<Communication> &communications, otf2::chrono::duration runtime);

    [[nodiscard]] Range<Slot> getSlots() const override;

    [[nodiscard]] Range<Communication> getCommunications() const override;
};

#endif //MOTIV_FILETRACE_HPP
