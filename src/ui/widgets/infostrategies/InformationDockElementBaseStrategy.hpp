#ifndef MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP
#define MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP

#include "InformationDockElementStrategy.hpp"
#include "src/ui/widgets/TimeUnitLabel.hpp"

template<class T> requires std::is_base_of_v<TimedElement, T>
class InformationDockElementBaseStrategy : public InformationDockElementStrategy {
public:
    static QString tr(const char *s, const char *c = nullptr, int n = -1) {
        return QObject::tr(s, c, n);
    }

public:
    virtual T *applicable(TimedElement *t) { return dynamic_cast<T *>(t); }

    void setup(QFormLayout *layout) override;

    virtual void updateView(QFormLayout *layout, T *element);

    bool update(QFormLayout *layout, TimedElement *element) override;

    std::string title() override;

protected:
    TimeUnitLabel *startField = nullptr;
    TimeUnitLabel *endField = nullptr;
    TimeUnitLabel *runtimeField = nullptr;
};


#endif //MOTIV_INFORMATIONDOCKELEMENTBASESTRATEGY_HPP
