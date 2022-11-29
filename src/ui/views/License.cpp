#include "License.hpp"

#include <QFile>
#include <QLabel>
#include <QVBoxLayout>

using namespace view;

License::License(QWidget *parent) {
    QFile licenseText(":/COPYING");

    // TODO display
}

License::~License() {}