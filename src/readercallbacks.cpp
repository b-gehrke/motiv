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
    std::sort(this->communications_->begin(), this->communications_->end(), [](Communication &rhs, Communication &lhs) {
        return rhs.start < lhs.start;
    });

    for (const auto &item: this->slotsBuilding) {
        delete item.second;
    }
    for (const auto &item: this->pendingSends) {
        delete item.second;
    }
    for (const auto &item: this->pendingReceives) {
        delete item.second;
    }
    std::destroy(this->slotsBuilding.begin(), this->slotsBuilding.end());
    std::destroy(this->pendingSends.begin(), this->pendingSends.end());
    std::destroy(this->pendingReceives.begin(), this->pendingReceives.end());
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_send &send) {
    auto location = loc;
    auto source = location.ref().get();
    auto destination = send.receiver();

    // Check for a pending matching receive call
    if (this->pendingReceives.contains(destination)){
        auto builderStack =  this->pendingReceives[destination];
        auto builder = builderStack->back();


        auto start = send.timestamp() - this->program_start_;
        builder.sender(location)->start(start);
        auto communication = builder.build();

        this->communications_->push_back(communication);

        builderStack->pop_back();
        if(builderStack->empty()){
            delete builderStack;
            this->pendingReceives.erase(destination);
        }
    } else {
        std::vector<Communication::Builder>* builderStack;
        if(this->pendingSends.contains(source)) {
            builderStack = this->pendingSends[source];
        } else {
            builderStack = new std::vector<Communication::Builder>();
            pendingSends[source] = builderStack;
        }

        Communication::Builder builder;

        auto start = send.timestamp() - this->program_start_;
        builder.start(start)->sender(location);

        builderStack->push_back(builder);
    }
}

void ReaderCallbacks::event(const otf2::definition::location &loc, const otf2::event::mpi_receive &receive) {
    auto location = loc;
    auto source = receive.sender();
    auto destination = loc.ref().get();

    // Check for a pending matching send call
    if (this->pendingSends.contains(source)){
        auto builderStack =  this->pendingSends[source];
        auto builder = builderStack->back();

        auto end = receive.timestamp() - this->program_start_;
        builder.receiver(location)->end(end);
        auto communication = builder.build();

        this->communications_->push_back(communication);

        builderStack->pop_back();
        if(builderStack->empty()){
            delete builderStack;
            this->pendingSends.erase(source);
        }
    } else {
        std::vector<Communication::Builder>* builderStack;
        if(this->pendingReceives.contains(destination)) {
            builderStack = this->pendingReceives[destination];
        } else {
            builderStack = new std::vector<Communication::Builder>();
            pendingReceives[destination] = builderStack;
        }

        Communication::Builder builder;

        auto end = receive.timestamp() - this->program_start_;
        builder.end(end)->receiver(location);

        builderStack->push_back(builder);
    }
}
