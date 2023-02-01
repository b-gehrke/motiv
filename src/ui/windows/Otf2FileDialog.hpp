#ifndef MOTIV_OTF2FILEDIALOG_HPP
#define MOTIV_OTF2FILEDIALOG_HPP


#include <QFileDialog>

class Otf2FileDialog : public QFileDialog {
    Q_OBJECT
public:
    explicit Otf2FileDialog(QWidget *parent = nullptr);
};


#endif //MOTIV_OTF2FILEDIALOG_HPP
