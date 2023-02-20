#ifndef MOTIV_INFORMATIONDOCKSLOTSTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKSLOTSTRATEGY_HPP


#include "InformationDockElementBaseStrategy.hpp"
#include "src/models/Slot.hpp"

class InformationDockSlotStrategy : public InformationDockElementBaseStrategy<Slot> {
public:
    void setup(QFormLayout *layout) override;

    void updateView(QFormLayout *layout, Slot *element) override;

private:
    QLabel *nameField = nullptr;
    QLabel *rankField = nullptr;

};


#endif //MOTIV_INFORMATIONDOCKSLOTSTRATEGY_HPP
