#include "traceselection.hpp"

#include <QLabel>
#include <QPushButton>
#include <QSizePolicy>
#include <QVBoxLayout>

using namespace view;

TraceSelection::TraceSelection(QWidget *parent) {
    auto vBoxLayout = new QVBoxLayout(this);
    setLayout(vBoxLayout);

    auto openButton = new QPushButton(tr("&Open Trace"), this);
    // TODO for some reason, the compiler claims the constructor is private?
    // openButton->setSizePolicy(QSizePolicy::Policy::Fixed));
    // TODO cant find slot
    connect(openButton, SIGNAL(clicked()), this, SLOT(openTrace()));

    // auto recentLabel = new QLabel(this);
    // recentLabel->setText(tr("Recently opened traces:"));

    layout()->addWidget(openButton);
    // layout()->addWidget(recentLabel);

    // if(!recent.isEmpty()) {
    //     for(auto name : this->recent) {
    //         auto entryLabel = new QLabel(this);
    //         entryLabel->setText(name);
    //         layout()->addWidget(entryLabel);
    //     }
    // }
}

TraceSelection::~TraceSelection(){}