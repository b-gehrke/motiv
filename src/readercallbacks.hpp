//
// Created by bjoern on 20.10.22.
//

#ifndef MOTIV_READERCALLBACKS_HPP
#define MOTIV_READERCALLBACKS_HPP

#include <otf2xx/otf2.hpp>

#include "src/models/slot.hpp"
#include "src/models/communication.hpp"

class ReaderCallbacks : public otf2::reader::callback {
//    using otf2::reader::callback::event;
//    using otf2::reader::callback::definition;
private:
    std::vector<Slot> slots_;
    std::vector<Communication> communications_;

    std::map<otf2::reference<otf2::definition::location>, std::vector<Slot> *> slots_building_;
//    std::vector<Slot> slots_building_;

    otf2::chrono::time_point program_start_;
    otf2::chrono::time_point program_end_;

    otf2::reader::reader &rdr_;
public:
    explicit ReaderCallbacks(otf2::reader::reader &rdr);

    void definition(const otf2::definition::location &loc) override;
    void event(const otf2::definition::location &location, const otf2::event::program_begin &event) override;
    void event(const otf2::definition::location &location, const otf2::event::program_end &event) override;
    void event(const otf2::definition::location &location, const otf2::event::enter &event) override;
    void event(const otf2::definition::location &location, const otf2::event::leave &event) override;
    void events_done(const otf2::reader::reader &) override;

public:
    std::vector<Communication> &getCommunications();
    std::vector<Slot> &getSlots();
    otf2::chrono::duration duration() const;
};

#endif //MOTIV_READERCALLBACKS_HPP
