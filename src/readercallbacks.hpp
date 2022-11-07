#ifndef MOTIV_READERCALLBACKS_HPP
#define MOTIV_READERCALLBACKS_HPP

#include <otf2xx/otf2.hpp>
#include <cstdint>

#include "src/models/slot.hpp"
#include "src/models/communication.hpp"
#include "src/models/blockingp2pcommunication.hpp"
#include "src/models/nonblockingp2pcommunication.hpp"
#include "src/models/collectivecommunication.hpp"

template <typename T>
using BuilderSetLocation = std::function<typename T::Builder *(typename T::Builder &,
                                                          otf2::definition::location &)>;

template <typename T>
using BuilderSetTime = std::function<typename T::Builder *(typename T::Builder &,
                                                          otf2::chrono::duration &)>;

template <typename T>
using BuilderSetter = std::function<void (typename T::Builder &)>;

class ReaderCallbacks : public otf2::reader::callback {
    using otf2::reader::callback::event;
    using otf2::reader::callback::definition;
private:
    std::shared_ptr<std::vector<Slot>> slots_;
    std::shared_ptr<std::vector<BlockingP2PCommunication>> blockingComm_;
    std::shared_ptr<std::vector<NonBlockingP2PCommunication>> nonBlockingComm_;
    std::shared_ptr<std::vector<CollectiveCommunication>> collectiveComm_;

    /**
     * Vectors for building the slot datatypes. Key is the location of the events.
     */
    std::map<otf2::reference<otf2::definition::location>, std::vector<Slot::Builder> *> slotsBuilding;


    /**
     * Vectors holding builders for communications for which the send request is issued but receive is pending.
     */
    std::map<uint32_t, std::vector<BlockingP2PCommunication::Builder> *> pendingSends;

    /**
     * Vectors holding builders for communications for which the receive request is issued but send is pending.
     */
    std::map<uint32_t, std::vector<BlockingP2PCommunication::Builder> *> pendingReceives;

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
     * @brief Returns all read communications
     *
     * The vector will only contain elements read by the reader when calling @link(otf2::reader::reader::read_events)
     *
     * @return All read communications
     */
    std::shared_ptr<std::vector<Communication>> getCommunications();

    std::shared_ptr<std::vector<BlockingP2PCommunication>> getBlockingComm();
    std::shared_ptr<std::vector<NonBlockingP2PCommunication>> getNonBlockingComm();
    std::shared_ptr<std::vector<CollectiveCommunication>> getCollectiveComm();

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
    template <typename T>
    void communicationEvent(otf2::definition::location location, uint32_t matching, otf2::chrono::time_point timestamp,
                            std::map<uint32_t, std::vector<typename T::Builder> *> &selfPending,
                            std::map<uint32_t, std::vector<typename T::Builder> *> &matchingPending,
                            BuilderSetLocation<T> &setLocation, BuilderSetTime<T> &setTime);

    template <typename T>
    void communicationEvent(otf2::definition::location location, uint32_t matching,
                            otf2::chrono::time_point timestamp,
                            std::map<uint32_t, std::vector<typename T::Builder> *> &selfPending,
                            std::map<uint32_t, std::vector<typename T::Builder> *> &matchingPending,
                            BuilderSetLocation<T> &setLocation,
                            BuilderSetTime<T> &setTime,
                            BuilderSetter<T> &additionalBuilderSetter);
};

#endif //MOTIV_READERCALLBACKS_HPP
