#ifndef MOTIV_LICENSE_HPP
#define MOTIV_LICENSE_HPP

#include <QStringList>
#include <QWidget>

namespace view {

class License : public QWidget {
    Q_OBJECT

public:
    License(QWidget *parent = nullptr);
    ~License();
};

} // namespace view

#endif // MOTIV_LICENSE_HPP