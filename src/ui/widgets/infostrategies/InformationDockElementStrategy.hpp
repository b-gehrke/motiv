#ifndef MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP

#include "src/models/TimedElement.hpp"

#include <QFormLayout>

class InformationDockElementStrategy {
public:
    virtual void setup(QFormLayout* layout) { };
    virtual bool update(QFormLayout* layout, TimedElement* t) { return false; };

    virtual std::string title() { return ""; }
};

#endif //MOTIV_INFORMATIONDOCKELEMENTSTRATEGY_HPP