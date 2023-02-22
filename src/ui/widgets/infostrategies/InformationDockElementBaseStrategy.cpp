#include "InformationDockElementBaseStrategy.hpp"
#include "src/models/Slot.hpp"
#include "src/models/Trace.hpp"

template<class T> requires std::is_base_of_v<TimedElement, T>
void InformationDockElementBaseStrategy<T>::setup(QFormLayout *layout)  {
    startField = new TimeUnitLabel(0);
    endField = new TimeUnitLabel(0);
    runtimeField = new TimeUnitLabel(0);


    layout->addRow(tr("Start:"), startField);
    layout->addRow(tr("End:"), endField);
    layout->addRow(tr("Runtime:"), runtimeField);
}

template<class T> requires std::is_base_of_v<TimedElement, T>
void InformationDockElementBaseStrategy<T>::updateView(QFormLayout *, T *element) {
    if (!element) return;

    auto start = static_cast<double>(element->getStartTime().count());
    auto end = static_cast<double>(element->getEndTime().count());
    auto runtime = static_cast<double>(element->getDuration().count());

    startField->setTime(start);
    endField->setTime(end);
    runtimeField->setTime(runtime);
}

template<class T>
requires std::is_base_of_v<TimedElement, T>bool
InformationDockElementBaseStrategy<T>::update(QFormLayout *layout, TimedElement *element) {
    T *t = applicable(element);
    if (t) {
        updateView(layout, t);
    }

    return t;
}

template<class T>
requires std::is_base_of_v<TimedElement, T>std::string InformationDockElementBaseStrategy<T>::title() {
    return typeid(T).name();
}

template class InformationDockElementBaseStrategy<Slot>;
template class InformationDockElementBaseStrategy<Trace>;
template class InformationDockElementBaseStrategy<Communication>;
template class InformationDockElementBaseStrategy<CollectiveCommunicationEvent>;
