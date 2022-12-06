#ifndef MOTIV_READERCALLBACKS_HPP
#define MOTIV_READERCALLBACKS_HPP

#include <otf2xx/otf2.hpp>
#include <cstdint>

#include "src/models/slot.hpp"
#include "src/models/communication/communication.hpp"
#include "src/models/communication/nonblockingsendevent.hpp"
#include "src/models/communication/nonblockingreceiveevent.hpp"
#include "src/models/communication/collectivecommunicationevent.hpp"

template <typename T>
using BuilderSetLocation = std::function<typename T::Builder *(typename T::Builder &,
                                                          otf2::definition::location &)>;

template <typename T>
using BuilderSetTime = std::function<typename T::Builder *(typename T::Builder &,
                                                          otf2::chrono::duration &)>;

template <typename T>
using BuilderSetter = std::function<void (typename T::Builder &)>;

typedef std::variant<NonBlockingSendEvent::Builder,  NonBlockingReceiveEvent::Builder> NonBlockingCommunicationEventBuilder;

class ReaderCallbacks : public otf2::reader::callback {
    using otf2::reader::callback::event;
    using otf2::reader::callback::definition;
private:
    std::shared_ptr<std::vector<Slot>> slots_;
    std::shared_ptr<std::vector<Communication>> communications_;
    std::shared_ptr<std::vector<CollectiveCommunicationEvent>> collectiveCommunications_;

    /**
     * Vectors for building the slot datatypes. Key is the location of the events.
     */
    std::map<otf2::reference<otf2::definition::location>, std::vector<Slot::Builder> *> slotsBuilding;

    /**
     * Vectors for building the blocking communication datatypes. Key is the location id of the sender.
     */
    std::map<uint32_t, std::vector<std::shared_ptr<CommunicationEvent>> *> pendingSends;

    /**
     * Vectors for building the blocking communication datatypes. Key is the location id of the receiver.
     */
    std::map<uint32_t, std::vector<std::shared_ptr<CommunicationEvent>> *> pendingReceives;

    std::map<otf2::reference<otf2::definition::location>, CollectiveCommunicationEvent::Member::Builder> ongoingCollectiveCommunicationMembers;
    CollectiveCommunicationEvent::Builder* ongoingCollectiveCommunication = nullptr;

    /**
     * Vectors for building the non blocking communication datatypes. Key is the request id.
     */
    std::map<uint64_t, NonBlockingCommunicationEventBuilder> uncompletedRequests;

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

    void event(const otf2::definition::location &location, const otf2::event::mpi_send &send) override;
    void event(const otf2::definition::location &location, const otf2::event::mpi_receive &receive) override;

    void event(const otf2::definition::location &location, const otf2::event::mpi_isend_request &request) override;
    void event(const otf2::definition::location &location, const otf2::event::mpi_isend_complete &complete) override;

    void event(const otf2::definition::location &location, const otf2::event::mpi_ireceive_request &request) override;
    void event(const otf2::definition::location &location, const otf2::event::mpi_ireceive_complete &complete) override;

    void event(const otf2::definition::location &location, const otf2::event::mpi_request_test &test) override;
    void event(const otf2::definition::location &location, const otf2::event::mpi_request_cancelled &cancelled) override;

    void event(const otf2::definition::location &location, const otf2::event::mpi_collective_begin &begin) override;
    void event(const otf2::definition::location &location, const otf2::event::mpi_collective_end &anEnd) override;

    void events_done(const otf2::reader::reader &) override;

public:
    /**
     * @brief Returns all read point to point communications
     *
     * The vector will only contain elements read by the reader when calling @link(otf2::reader::reader::read_events)
     *
     * @return All read point to point communications
     */
    std::shared_ptr<std::vector<Communication>> getCommunications();


    /**
     * @brief Returns all read collective communications
     *
     * The vector will only contain elements read by the reader when calling @link(otf2::reader::reader::read_events)
     *
     * @return All read collective communications
     */
    std::shared_ptr<std::vector<CollectiveCommunicationEvent>> getCollectiveCommunications();

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

private:
    template<typename T, typename = std::enable_if_t<std::is_base_of_v<CommunicationEvent, T>>>
    void communicationEvent(std::shared_ptr<T> self, uint32_t matching,
                            std::map<uint32_t, std::vector<std::shared_ptr<CommunicationEvent>> *> &selfPending,
                            std::map<uint32_t, std::vector<std::shared_ptr<CommunicationEvent>> *> &matchingPending);

    [[nodiscard]] otf2::chrono::duration relative(otf2::chrono::time_point) const;
};

#endif //MOTIV_READERCALLBACKS_HPP
