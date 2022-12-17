#include "SelectionDetails.hpp"

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>


SelectionDetails::SelectionDetails(QWidget *parent) : SelectionDetails(parent, QStringList()) {}

SelectionDetails::SelectionDetails(QWidget *, QStringList information) : information(information) {
    auto groupBox = new QGroupBox(tr("Details"), this);

    auto functionNameLabel = new QLabel(this);
    functionNameLabel->setText(tr("Function name: TODO"));
    
    auto startTimeLabel = new QLabel(this);
    startTimeLabel->setText(tr("Start time: TODO"));
    
    auto endTimeLabel = new QLabel(this);
    endTimeLabel->setText(tr("End time: TODO"));
    
    auto layout = new QVBoxLayout(this);
    layout->addWidget(functionNameLabel);
    layout->addWidget(startTimeLabel);
    layout->addWidget(endTimeLabel);

    for(auto info : information) {
        auto label = new QLabel(this);
        label->setText(info); // tr(info)?
        layout->addWidget(label);
    }

    layout->setAlignment(Qt::AlignTop);
    groupBox->setLayout(layout);
}

SelectionDetails::~SelectionDetails() {}