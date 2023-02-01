#include "Otf2FileDialog.hpp"

#include "src/models/AppSettings.hpp"

Otf2FileDialog::Otf2FileDialog(QWidget *parent) : QFileDialog(parent) {
    this->setFileMode(QFileDialog::ExistingFile);
    this->setNameFilter("*.otf2");
    auto recentlyOpenedFiles = AppSettings::getInstance().recentlyOpenedFiles();
    if (recentlyOpenedFiles.isEmpty()) {
        this->setDirectory(QDir::home());
    } else {
        this->setDirectory(recentlyOpenedFiles.last());
    }
}
