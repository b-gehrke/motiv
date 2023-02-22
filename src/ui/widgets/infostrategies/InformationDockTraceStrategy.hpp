#ifndef MOTIV_INFORMATIONDOCKTRACESTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKTRACESTRATEGY_HPP


#include "InformationDockElementBaseStrategy.hpp"
#include "src/models/Trace.hpp"

class InformationDockTraceStrategy : public InformationDockElementBaseStrategy<Trace> {
public:
    std::string title() override;
};


#endif //MOTIV_INFORMATIONDOCKTRACESTRATEGY_HPP
