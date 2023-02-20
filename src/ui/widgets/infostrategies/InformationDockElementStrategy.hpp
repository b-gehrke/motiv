#ifndef MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP

#include "src/models/TimedElement.hpp"

#include <QFormLayout>

class InformationDockElementStrategy {
public:
    virtual void setup(QFormLayout* layout) { };
    virtual bool update(QFormLayout* layout, TimedElement* t) { return false; };
};

#endif //MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP
