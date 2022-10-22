#ifndef MOTIV_READERCALLBACKS_HPP
#define MOTIV_READERCALLBACKS_HPP

#include <otf2xx/otf2.hpp>

#include "src/models/slot.hpp"
#include "src/models/communication.hpp"

class ReaderCallbacks : public otf2::reader::callback {
private:
    std::shared_ptr<std::vector<Slot>> slots_;
    std::shared_ptr<std::vector<Communication>> communications_;

    std::map<otf2::reference<otf2::definition::location>, std::vector<Slot::Builder> *> slotsBuilding;

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
    /**
     * @brief Returns all read communications
     *
     * The vector will only contain elements read by the reader when calling @link(otf2::reader::reader::read_events)
     *
     * @return All read communications
     */
    std::shared_ptr<std::vector<Communication>> getCommunications();
    /**
     * @brief Returns all read slots
     *
     * The vector will only contain elements read by the reader when calling @link(otf2::reader::reader::read_events)
     *
     * @return All read slots
     */
    std::shared_ptr<std::vector<Slot>> getSlots();
    /**
     * Duration of the trace
     * @return Duration of the trace
     */
    [[nodiscard]] otf2::chrono::duration duration() const;
};

#endif //MOTIV_READERCALLBACKS_HPP
