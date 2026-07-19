#ifndef ROUTEHUNTER_MAINWINDOW_H
#define ROUTEHUNTER_MAINWINDOW_H

#pragma once

#include <QCheckBox>
#include <QComboBox>
#include <QDir>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>

class MainWindow : public QMainWindow {

Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QDir findWordlistsDir() const;
    void onStartScan();

    QLineEdit* urlEdit;
    QComboBox* wordlistCombo;
    QSpinBox* threadsSpin;

    QCheckBox* followRedirectsCheck;
    QCheckBox* autoCalibrateCheck;
    QCheckBox* recursionCheck;
    QCheckBox* ignoreBodyCheck;
    QCheckBox* http2Check;
    QCheckBox* ignoreCommentsCheck;

    QLineEdit* extensionsEdit;
    QLineEdit* filterStatusEdit;
    QLineEdit* matchStatusEdit;
    QSpinBox* recursionDepthSpin;
    QSpinBox* timeoutSpin;

    QPushButton* startButton;
    QPushButton* stopButton;
    QTableWidget* resultsTable;
};

#endif //ROUTEHUNTER_MAINWINDOW_H
