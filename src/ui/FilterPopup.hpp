#ifndef MOTIV_FILTERPOPUP_HPP
#define MOTIV_FILTERPOPUP_HPP


#include <QDialog>
#include <QGroupBox>
#include <QCheckBox>
#include "src/models/Filter.hpp"

class FilterPopup : public QDialog {
Q_OBJECT

public: // constructors
    explicit FilterPopup(const Filter &filter, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags());

public: // methods

public Q_SLOTS:
    void updateFilter();

public: Q_SIGNALS:
    void filterChanged(Filter);

private:
    Filter filter_;

private: // widgets
    QCheckBox *mpiSlotKindCheckBox = nullptr;
    QCheckBox *openMpSlotKindCheckBox = nullptr;
    QCheckBox *plainSlotKindCheckBox = nullptr;
};


#endif //MOTIV_FILTERPOPUP_HPP
