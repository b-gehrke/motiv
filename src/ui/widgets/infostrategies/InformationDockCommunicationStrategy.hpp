#ifndef MOTIV_INFORMATIONDOCKCOMMUNICATIONSTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKCOMMUNICATIONSTRATEGY_HPP


#include "InformationDockElementBaseStrategy.hpp"
#include "src/models/communication/Communication.hpp"

class InformationDockCommunicationStrategy : public InformationDockElementBaseStrategy<Communication> {
public:
    void setup(QFormLayout *layout) override;

    void updateView(QFormLayout *layout, Communication *element) override;

    std::string title() override;

private:
    QLabel* communicatorField = nullptr;
    QLabel *startKindField = nullptr;
    QLabel *endKindField = nullptr;
    QLabel *rankFromField = nullptr;
    QLabel *rankToField = nullptr;
};


#endif //MOTIV_INFORMATIONDOCKCOMMUNICATIONSTRATEGY_HPP
