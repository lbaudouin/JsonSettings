#include <QCoreApplication>

#include <QSettings>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>

bool readJsonFile(QIODevice &device, QSettings::SettingsMap &map);
bool writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Declare new JSON format
    const QSettings::Format jsonFormat = QSettings::registerFormat("json", readJsonFile, writeJsonFile);

    //Set default format to not specify it each time
    QSettings::setDefaultFormat(jsonFormat);

    //Set output path to default filepath builder
    //QSettings::setPath(jsonFormat, QSettings::UserScope, qApp->applicationDirPath());

    //Get settings using default filepath builder
    //QSettings settings("app", "app");

    //Without default format
    //QSettings settings(jsonFormat, QSettings::UserScope, "app", "app");

    //Using specific file
    QSettings settings("test.json", jsonFormat);

    qDebug() << settings.value("value1","empty").toString();
    qDebug() << settings.value("value2","empty").toString();
    settings.setValue("value1","first value");

    return a.exec();
}


bool readJsonFile(QIODevice &device, QSettings::SettingsMap &map)
{
    QJsonDocument json = QJsonDocument::fromJson( device.readAll() );
    map = json.object().toVariantMap();
    return true;
}

bool writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map)
{
    device.write( QJsonDocument( QJsonObject::fromVariantMap( map ) ).toJson() );
    return true;
}
