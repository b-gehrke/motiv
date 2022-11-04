#ifndef MOTIV_SELECTIONDETAILS_HPP
#define MOTIV_SELECTIONDETAILS_HPP

#include <QStringList>
#include <QWidget>

namespace view {

class SelectionDetails : public QWidget {
    Q_OBJECT

public:
    SelectionDetails(QWidget *parent);
    SelectionDetails(QWidget *parent, QStringList information);
    ~SelectionDetails();

private:
    QStringList information;
};

} // namespace view

#endif // MOTIV_SELECTIONDETAILS_HPP