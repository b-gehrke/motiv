#ifndef MOTIV_INFORMATIONDOCKCOLLECTIVECOMMUNICATIONSTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKCOLLECTIVECOMMUNICATIONSTRATEGY_HPP


#include "InformationDockElementBaseStrategy.hpp"
#include "src/models/communication/CollectiveCommunicationEvent.hpp"

class InformationDockCollectiveCommunicationStrategy : public InformationDockElementBaseStrategy<CollectiveCommunicationEvent> {
public:
    void setup(QFormLayout *layout) override;

    void updateView(QFormLayout *layout, CollectiveCommunicationEvent *element) override;
private:
    QLabel *communicatorField = nullptr;
    QLabel *operationField = nullptr;
    QLabel *rootField = nullptr;
};


#endif //MOTIV_INFORMATIONDOCKCOLLECTIVECOMMUNICATIONSTRATEGY_HPP
