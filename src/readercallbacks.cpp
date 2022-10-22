#include "readercallbacks.hpp"
#include "src/models/communication.hpp"
#include "src/models/slot.hpp"
#include "lib/otf2xx/include/otf2xx/otf2.hpp"
#include <QStringListModel>
#include <memory>

ReaderCallbacks::ReaderCallbacks(otf2::reader::reader &rdr) :
    rdr_(rdr),
    slots_(std::make_shared<std::vector<Slot>>()),
    communications_(std::make_shared<std::vector<Communication>>()),
    slotsBuilding(),
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

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::enter &event) {
    auto start = event.timestamp() - this->program_start_;

    Slot::Builder builder{};
    auto region = event.region();
    auto location = loc;
    builder.start(start)->location(location)->region(region);

    std::vector<Slot::Builder> *builders;
    auto buildersIt = this->slotsBuilding.find(location.ref());
    if (buildersIt == this->slotsBuilding.end()) {
        builders = new std::vector<Slot::Builder>();
        this->slotsBuilding.insert({location.ref(), builders});
    } else {
        builders = buildersIt->second;
    }

    builders->push_back(builder);
}

void ReaderCallbacks::event(const otf2::definition::location &location, const otf2::event::leave &event) {
    auto builders = this->slotsBuilding.at(location.ref());

    Slot::Builder &builder = builders->back();

    auto end = event.timestamp() - this->program_start_;
    builder.end(end);

    this->slots_->push_back(builder.build());

    builders->pop_back();
}

std::shared_ptr<std::vector<Slot>> ReaderCallbacks::getSlots() {
    return this->slots_;
}

std::shared_ptr<std::vector<Communication>> ReaderCallbacks::getCommunications() {
    return this->communications_;
}

otf2::chrono::duration ReaderCallbacks::duration() const {
    return this->program_end_ - this->program_start_;
}

void ReaderCallbacks::events_done(const otf2::reader::reader &) {
    std::sort(this->slots_->begin(), this->slots_->end(), [](Slot &rhs, Slot &lhs) {
        return rhs.start < lhs.start;
    });

    for (const auto &item: this->slotsBuilding) {
        delete item.second;
    }
    std::destroy(this->slotsBuilding.begin(), this->slotsBuilding.end());
}
