#include "RecentFilesDialog.hpp"

#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QSettings>
#include <QListView>
#include <QStringListModel>
#include <QLabel>

#include "src/models/AppSettings.hpp"
#include "Otf2FileDialog.hpp"

RecentFilesDialog::RecentFilesDialog(QString *dest) : dest(dest) {
    auto layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    auto pushButton = new QPushButton;
    pushButton->setText(tr("&Open"));
    layout->addWidget(pushButton);

    auto fileDialog = new Otf2FileDialog(this);

    QObject::connect(pushButton, &QPushButton::clicked, fileDialog, &Otf2FileDialog::exec);
    QObject::connect(fileDialog, &QFileDialog::fileSelected,  [this](const QString &selectedFile){
        if (selectedFile.isEmpty()) {
            this->reject();
        } else {
            AppSettings::getInstance().recentlyOpenedFilesPush(selectedFile);
            *this->dest = selectedFile;
            this->accept();
        }
    });

    auto label = new QLabel(QObject::tr("Recently opened files:"));
    layout->addWidget(label);

    auto recentlyOpenedFiles = AppSettings::getInstance().recentlyOpenedFiles();

    if(recentlyOpenedFiles.isEmpty()) {
        auto listEmptyLabel = new QLabel(QObject::tr("No recent files"));
        listEmptyLabel->setStyleSheet("QLabel { color : gray; }");
        layout->addWidget(listEmptyLabel);
    } else {
        auto listView = new QListView;
        listView->setEditTriggers(QListView::NoEditTriggers);
        layout->addWidget(listView);

        auto stringListModel = new QStringListModel;
        stringListModel->setStringList(recentlyOpenedFiles);
        listView->setModel(stringListModel);

        connect(listView, &QAbstractItemView::doubleClicked, [this](const QModelIndex &idx){
           *this->dest = idx.data().toString();
           this->accept();
        });

//        auto clearButton = new QPushButton(tr("&Clear"));
//        layout->addWidget(clearButton);
//        connect(clearButton, &QPushButton::clicked, [] {
//            AppSettings::getInstance().recentlyOpenedFilesClear();
//        });
    }
}
