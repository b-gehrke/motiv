#include "InformationDockCollectiveCommunicationStrategy.hpp"
#include "src/utils.hpp"


void InformationDockCollectiveCommunicationStrategy::setup(QFormLayout *layout) {
    communicatorField = new QLabel;
    operationField = new QLabel;
    rootField = new QLabel;

    layout->addRow(tr("Communicator:"), communicatorField);
    layout->addRow(tr("Operation:"), operationField);
    layout->addRow(tr("Root:"), rootField);

    InformationDockElementBaseStrategy::setup(layout);
}

void InformationDockCollectiveCommunicationStrategy::updateView(QFormLayout *layout, CollectiveCommunicationEvent *element) {
    auto communicator = std::get<otf2::definition::comm>(*element->getCommunicator());

    auto collectiveRoot = static_cast<otf2::collective_root_type>(element->getRoot());

    QString rootName = "Unknown";
    switch(collectiveRoot) {
        case otf2::common::collective_root_type::none:
            rootName = "None";
            break;
        case otf2::common::collective_root_type::self:
            rootName = "Self";
            break;
        case otf2::common::collective_root_type::this_group:
            rootName = "This Group";
            break;
        default:
            if(holds_alternative<otf2::definition::comm_group>(communicator.group())) {
                auto group = get<otf2::definition::comm_group>(communicator.group());
                auto root = group[element->getRoot()];

                rootName = QString::fromStdString(root.name().str());
            }
            break;
    }

    auto operationName = QString::fromStdString(collectiveCommunicationOperationName(element->getOperation()));
    auto communicatorName = QString::fromStdString(communicator.name().str());

    rootField->setText(rootName);
    operationField->setText(operationName);
    communicatorField->setText(communicatorName);

    InformationDockElementBaseStrategy::updateView(layout, element);
}

std::string InformationDockCollectiveCommunicationStrategy::title() {
    return tr("Collective communication").toStdString();
}
