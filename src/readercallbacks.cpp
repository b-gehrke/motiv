#include "readercallbacks.hpp"
#include "src/models/communication.hpp"
#include "src/models/slot.hpp"
#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include <QStringListModel>

ReaderCallbacks::ReaderCallbacks(otf2::reader::reader &rdr) : rdr_(rdr), slots_(), communications_(), slots_building_(),
                                                              program_start_() {

}

void ReaderCallbacks::definition(const otf2::definition::location &loc) {
    rdr_.register_location(loc);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::program_begin &event) {
    this->program_start_ = event.timestamp();
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::program_end &event) {
    this->program_end_ = event.timestamp();
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::enter &event) {
    auto start = event.timestamp() - this->program_start_;

    Slot slot(start,  location, event.region());

    std::vector<Slot> *locationStack;
    auto locationStackIt = this->slots_building_.find(location.ref());
    if (locationStackIt == this->slots_building_.end()) {
        locationStack = new std::vector<Slot>();
        this->slots_building_.insert({location.ref(), locationStack});
    } else {
        locationStack = locationStackIt->second;
    }

    locationStack->push_back(slot);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::leave &event) {
    auto locationStack = this->slots_building_.at(location.ref());

    Slot &slot = locationStack->back();
    locationStack->pop_back();


    slot.end = event.timestamp() - this->program_start_;

    this->slots_.push_back(slot);
}

std::vector<Slot> &ReaderCallbacks::getSlots() {
    return this->slots_;
}

std::vector<Communication> &ReaderCallbacks::getCommunications() {
    return this->communications_;
}

otf2::chrono::duration ReaderCallbacks::duration() const {
    return this->program_end_ - this->program_start_;
}

void ReaderCallbacks::events_done(const otf2::reader::reader &) {
    std::sort(this->slots_.begin(), this->slots_.end(), [](Slot &rhs, Slot &lhs) {
        return rhs.start < lhs.start;
    });

    for (const auto &item: this->slots_building_) {
        delete item.second;
    }
    std::destroy(this->slots_building_.begin(), this->slots_building_.end());
}
