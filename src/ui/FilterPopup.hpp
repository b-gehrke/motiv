#ifndef MOTIV_FILTERPOPUP_HPP
#define MOTIV_FILTERPOPUP_HPP


#include <QDialog>
#include <QGroupBox>
#include <QCheckBox>
#include "src/models/Filter.hpp"

class FilterPopup : public QDialog {
Q_OBJECT

public: // constructors
    /**
     * Creates a new instance of this modal popup.
     * @param filter The current filter object
     * @param parent See QDialog::QDialog(QWidget*, Qt::WindowFlags)
     * @param f See QDialog::QDialog(QWidget*, Qt::WindowFlags)
     */
    explicit FilterPopup(const Filter &filter, QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags());

public: // methods

public Q_SLOTS:
    /**
     * Applies the changes made in the UI to @c filter_
     */
    void updateFilter();

public: Q_SIGNALS:
    /**
     * Signals the filter was changes
     */
    void filterChanged(Filter);

private: // fields
    Filter filter_;

private: // widgets
    QCheckBox *mpiSlotKindCheckBox = nullptr;
    QCheckBox *openMpSlotKindCheckBox = nullptr;
    QCheckBox *plainSlotKindCheckBox = nullptr;
};


#endif //MOTIV_FILTERPOPUP_HPP
