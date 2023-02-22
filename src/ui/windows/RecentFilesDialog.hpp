#ifndef MOTIV_RECENTFILESDIALOG_HPP
#define MOTIV_RECENTFILESDIALOG_HPP


#include <QDialog>

class RecentFilesDialog : public QDialog {
public:
    RecentFilesDialog(QString *dest);

private:
    QString *dest;
};


#endif //MOTIV_RECENTFILESDIALOG_HPP
