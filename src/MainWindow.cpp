#include "MainWindow.h"

#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QDir>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSizePolicy>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

#include "FFUFCommand.h"
#include "FFUFRunner.h"

QDir MainWindow::findWordlistsDir() const
{
    const QStringList candidates = {
        QCoreApplication::applicationDirPath() + QStringLiteral("/wordlists"),
        QStringLiteral("wordlists"),
    };

    for (const QString& path : candidates) {
        QDir dir(path);
        if (dir.exists() && !dir.entryList({QStringLiteral("*.txt")}, QDir::Files).isEmpty())
            return dir;
    }

    return QDir(candidates.first());
}

void MainWindow::onStartScan() {
    FFUFCommand cmdModel;

    cmdModel.url = urlEdit->text().toStdString();
    cmdModel.threads = static_cast<unsigned short>(threadsSpin->value());
    cmdModel.wordlistPath = wordlistCombo->currentData().toString().toStdString();
    cmdModel.redirects = followRedirectsCheck->isChecked();
    cmdModel.autoCal = autoCalibrateCheck->isChecked();
    cmdModel.recursion = recursionCheck->isChecked();
    cmdModel.recursionDepth = static_cast<unsigned short>(recursionDepthSpin->value());
    cmdModel.ignoreBody = ignoreBodyCheck->isChecked();
    cmdModel.http2 = http2Check->isChecked();
    cmdModel.ignoreWordlistComments = ignoreCommentsCheck->isChecked();
    cmdModel.extensions = extensionsEdit->text().toStdString();
    cmdModel.filterOutStatuses = filterStatusEdit->text().toStdString();
    cmdModel.matchStatuses = matchStatusEdit->text().toStdString();
    cmdModel.timeout = static_cast<unsigned short>(timeoutSpin->value());

    std::string cmdFlags = cmdModel.buildCommandFlags();

    FFUFRunner cmdRunner;

    std::string ffufResponse = cmdRunner.runCommand(cmdFlags);

    std::cout << ffufResponse << std::endl;

    //show res in table
    resultsTable->setRowCount(0); // clear previous scan
    const QString output = QString::fromStdString(ffufResponse);
    const QStringList lines = output.split('\n', Qt::SkipEmptyParts);
    for (const QString& line : lines) {
        const QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8());
        if (!doc.isObject())
            continue;
        const QJsonObject obj = doc.object();
        const int row = resultsTable->rowCount();
        resultsTable->insertRow(row);
        resultsTable->setItem(row, 0, new QTableWidgetItem(obj.value("url").toString()));
        resultsTable->setItem(row, 1, new QTableWidgetItem(QString::number(obj.value("status").toInt())));
        resultsTable->setItem(row, 2, new QTableWidgetItem(QString::number(obj.value("length").toInt())));
        resultsTable->setItem(row, 3, new QTableWidgetItem(QString::number(obj.value("words").toInt())));
        resultsTable->setItem(row, 4, new QTableWidgetItem(QString::number(obj.value("lines").toInt())));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("RouteHunter");
    resize(1000, 700);

    auto* central = new QWidget(this);
    setCentralWidget(central);

    auto* mainLayout = new QVBoxLayout(central);

    //form
    auto* form = new QFormLayout();
    form->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    form->setLabelAlignment(Qt::AlignLeft);
    form->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    urlEdit = new QLineEdit();
    urlEdit->setPlaceholderText("https://example.com/FUZZ");
    urlEdit->setMinimumWidth(500);
    urlEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    wordlistCombo = new QComboBox();
    wordlistCombo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    const QDir wordlistsDir = findWordlistsDir();
    const QStringList wordlists = wordlistsDir.entryList(
        {QStringLiteral("*.txt")}, QDir::Files, QDir::Name);
    for (const QString& name : wordlists)
        wordlistCombo->addItem(name, wordlistsDir.absoluteFilePath(name));

    if (wordlistCombo->count() == 0)
        wordlistCombo->addItem(QStringLiteral("(no wordlists found)"));
    else if (const int commonIndex = wordlistCombo->findText(QStringLiteral("common.txt"));
             commonIndex >= 0)
        wordlistCombo->setCurrentIndex(commonIndex);

    threadsSpin = new QSpinBox();
    threadsSpin->setRange(1, 500);
    threadsSpin->setValue(40);
    threadsSpin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    form->addRow("Target URL:", urlEdit);
    form->addRow("Wordlist:", wordlistCombo);
    form->addRow("Threads:", threadsSpin);

    mainLayout->addLayout(form);

    //options
    auto* optionsGroup = new QGroupBox(QStringLiteral("Options"));
    auto* optionsLayout = new QVBoxLayout(optionsGroup);

    auto* checksLayout = new QGridLayout();
    followRedirectsCheck = new QCheckBox(QStringLiteral("Follow redirects (-r)"));
    autoCalibrateCheck = new QCheckBox(QStringLiteral("Auto-calibrate (-ac)"));
    recursionCheck = new QCheckBox(QStringLiteral("Recursion (-recursion)"));
    ignoreBodyCheck = new QCheckBox(QStringLiteral("Ignore body (-ignore-body)"));
    http2Check = new QCheckBox(QStringLiteral("HTTP/2 (-http2)"));
    ignoreCommentsCheck = new QCheckBox(QStringLiteral("Ignore wordlist comments (-ic)"));

    checksLayout->addWidget(followRedirectsCheck, 0, 0);
    checksLayout->addWidget(autoCalibrateCheck, 0, 1);
    checksLayout->addWidget(recursionCheck, 0, 2);
    checksLayout->addWidget(ignoreBodyCheck, 1, 0);
    checksLayout->addWidget(http2Check, 1, 1);
    checksLayout->addWidget(ignoreCommentsCheck, 1, 2);
    optionsLayout->addLayout(checksLayout);

    auto* optionsForm = new QFormLayout();
    optionsForm->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    optionsForm->setLabelAlignment(Qt::AlignLeft);
    optionsForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    extensionsEdit = new QLineEdit();
    extensionsEdit->setPlaceholderText(QStringLiteral("php,html,txt (leave empty to find all)"));
    extensionsEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    filterStatusEdit = new QLineEdit();
    filterStatusEdit->setPlaceholderText(QStringLiteral("403,404 (leave empty to not filter)"));
    filterStatusEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    matchStatusEdit = new QLineEdit();
    matchStatusEdit->setPlaceholderText(QStringLiteral("200-299,301,302,307,401,403 (leave empty for defaults)"));
    matchStatusEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    recursionDepthSpin = new QSpinBox();
    recursionDepthSpin->setRange(0, 50);
    recursionDepthSpin->setValue(0);
    recursionDepthSpin->setEnabled(false);
    recursionDepthSpin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    timeoutSpin = new QSpinBox();
    timeoutSpin->setRange(1, 300);
    timeoutSpin->setValue(10);
    timeoutSpin->setSuffix(QStringLiteral(" s"));
    timeoutSpin->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    optionsForm->addRow(QStringLiteral("Extensions (-e):"), extensionsEdit);
    optionsForm->addRow(QStringLiteral("Filter out status (-fc):"), filterStatusEdit);
    optionsForm->addRow(QStringLiteral("Match status (-mc):"), matchStatusEdit);
    optionsForm->addRow(QStringLiteral("Recursion depth:"), recursionDepthSpin);
    optionsForm->addRow(QStringLiteral("Timeout:"), timeoutSpin);
    optionsLayout->addLayout(optionsForm);

    connect(recursionCheck, &QCheckBox::toggled, recursionDepthSpin, &QWidget::setEnabled);

    mainLayout->addWidget(optionsGroup);

    //buttons
    auto* buttonLayout = new QHBoxLayout();

    startButton = new QPushButton(QStringLiteral("Start Scan"));

    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartScan);

    stopButton = new QPushButton(QStringLiteral("Stop"));

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    //results table
    resultsTable = new QTableWidget();

    resultsTable->setColumnCount(5);
    resultsTable->setHorizontalHeaderLabels({
        QStringLiteral("URL"),
        QStringLiteral("Status"),
        QStringLiteral("Size"),
        QStringLiteral("Words"),
        QStringLiteral("Lines")
    });

    resultsTable->horizontalHeader()->setStretchLastSection(true);
    resultsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(resultsTable);
}
