#ifndef MOTIV_SETTINGSVIEW_HPP
#define MOTIV_SETTINGSVIEW_HPP

#include <QListView>

class SettingsView : public QListView{
    Q_OBJECT

public:
    explicit SettingsView(QWidget *parent = nullptr);
};


#endif //MOTIV_SETTINGSVIEW_HPP
