#ifndef MOTIV_APPSETTINGS_HPP
#define MOTIV_APPSETTINGS_HPP


#include <QSettings>

/**
 * Singleton holding persistent information
 */
class AppSettings : QObject {
Q_OBJECT
private:
    AppSettings();

public:
    /**
     * @return instance of AppSettings
     */
    static AppSettings &getInstance() {
        static AppSettings instance;
        return instance;
    }

    // Do not implement copy and copy assignment constructor.
    AppSettings(AppSettings const &) = delete;
    void operator=(AppSettings const &) = delete;

    [[nodiscard]] const QStringList &recentlyOpenedFiles() const;
    void recentlyOpenedFilesPush(const QString &newFile);
    void recentlyOpenedFilesRemove(const QString &filePath);
    void recentlyOpenedFilesClear();

public: Q_SIGNALS:
    void recentlyOpenedFilesChanged(QStringList);

private:
    QSettings settings;
    QString leastRecentDirectory_;
    QStringList recentlyOpenedFiles_;
};


#endif //MOTIV_APPSETTINGS_HPP
