#include "FFUFRunner.h"
#include "Platform.h"

#include <iostream>
#include <QCoreApplication>
#include <QProcess>
#include <QString>


std::string FFUFRunner::runCommand(std::string const &cmdFlags) {
    const QString ffufPath = QCoreApplication::applicationDirPath() + "/" + QString::fromStdString(getFFUFPath());

    QProcess process;

    process.start(ffufPath, QProcess::splitCommand(QString::fromStdString(cmdFlags)));

    if (!process.waitForStarted()) return "Failed to start ffuf: " + process.errorString().toStdString();

    process.waitForFinished(-1); // blocks UI — OK for first test only

    return process.readAllStandardOutput().toStdString();
}
