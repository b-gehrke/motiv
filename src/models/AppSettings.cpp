#include "AppSettings.hpp"

#define SET_AND_EMIT(key) \
    settings.setValue(#key, key##_); \
    Q_EMIT key##Changed(key##_);

AppSettings::AppSettings() {
    this->recentlyOpenedFiles_ = this->settings.value("recentlyOpenedFiles").toStringList();
}

const QStringList &AppSettings::recentlyOpenedFiles() const {
    return recentlyOpenedFiles_;
}

void AppSettings::recentlyOpenedFilesPush(const QString &newFile) {
    // Make sure most recent files are always at the back.
    recentlyOpenedFiles_.removeAll(newFile);
    recentlyOpenedFiles_.push_back(newFile);
    SET_AND_EMIT(recentlyOpenedFiles)
}

void AppSettings::recentlyOpenedFilesRemove(const QString &filePath) {
    recentlyOpenedFiles_.removeAll(filePath);
    SET_AND_EMIT(recentlyOpenedFiles)
}

void AppSettings::recentlyOpenedFilesClear() {
    this->recentlyOpenedFiles_.clear();
    SET_AND_EMIT(recentlyOpenedFiles)
}
