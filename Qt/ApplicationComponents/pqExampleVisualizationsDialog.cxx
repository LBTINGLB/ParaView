#include "pqExampleVisualizationsDialog.h"
#include "ui_pqExampleVisualizationsDialog.h"

#include "pqActiveObjects.h"
#include "pqApplicationCore.h"
#include "pqCoreUtilities.h"
#include "pqEventDispatcher.h"
#include "pqFixPathsInStateFilesBehavior.h"
#include "vtkPVConfig.h"

#include <QFile>
#include <QMessageBox>

//-----------------------------------------------------------------------------
pqExampleVisualizationsDialog::pqExampleVisualizationsDialog(QWidget* parentObject)
  : Superclass(parentObject)
  , ui(new Ui::pqExampleVisualizationsDialog)
{
  ui->setupUi(this);

  QObject::connect(
    this->ui->CanExampleButton, SIGNAL(clicked(bool)), this, SLOT(onButtonPressed()));
  QObject::connect(
    this->ui->DiskOutRefExampleButton, SIGNAL(clicked(bool)), this, SLOT(onButtonPressed()));
  QObject::connect(
    this->ui->WaveletExampleButton, SIGNAL(clicked(bool)), this, SLOT(onButtonPressed()));
}

//-----------------------------------------------------------------------------
pqExampleVisualizationsDialog::~pqExampleVisualizationsDialog()
{
  delete ui;
}

//-----------------------------------------------------------------------------
void pqExampleVisualizationsDialog::onButtonPressed()
{
#if defined(_WIN32) || defined(__APPLE__)
  QString dataPath = QCoreApplication::applicationDirPath() + "/../data";
#else
  QString appdir = QCoreApplication::applicationDirPath();
  QString dataPath = QFileInfo(appdir).fileName() == "bin"
    ?
    /* w/o shared forwarding */ appdir + "/../share/paraview-" PARAVIEW_VERSION "/data"
    :
    /* w/ shared forwarding  */ appdir + "/../../share/paraview-" PARAVIEW_VERSION "/data";
#endif
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  if (button)
  {
    const char* stateFile = NULL;
    bool needsData = false;
    if (button == this->ui->CanExampleButton)
    {
      stateFile = ":/pqApplicationComponents/ExampleVisualizations/CanExample.pvsm";
      needsData = true;
    }
    else if (button == this->ui->DiskOutRefExampleButton)
    {
      stateFile = ":/pqApplicationComponents/ExampleVisualizations/DiskOutRefExample.pvsm";
      needsData = true;
    }
    else if (button == this->ui->WaveletExampleButton)
    {
      stateFile = ":/pqApplicationComponents/ExampleVisualizations/WaveletExample.pvsm";
      needsData = false;
    }
    else
    {
      qCritical("No example file for button");
      return;
    }
    if (needsData)
    {
      QFileInfo fdataPath(dataPath);
      if (!fdataPath.isDir())
      {
        QString msg =
          QString("Your installation doesn't have datasets to load the example visualizations."
                  "You can manually download the datasets from paraview.org and then "
                  "place them under the following path to examples to work.\n\n'%1'")
            .arg(fdataPath.absoluteFilePath());
        // dump to cout for easy copy/paste.
        cout << msg.toUtf8().data() << endl;
        QMessageBox::warning(this, "Missing data", msg, QMessageBox::Ok);
        return;
      }
      dataPath = fdataPath.absoluteFilePath();
    }

    this->hide();
    Q_ASSERT(stateFile != NULL);

    bool prev = pqFixPathsInStateFilesBehavior::blockDialog(true);
    QFile qfile(stateFile);
    if (qfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QMessageBox box(this);
      box.setText("Loading example visualization, please wait ...");
      box.setStandardButtons(QMessageBox::NoButton);
      box.show();

      // without this, the message box doesn't paint properly.
      pqEventDispatcher::processEventsAndWait(100);

      QString xmldata(qfile.readAll());
      xmldata.replace("$PARAVIEW_EXAMPLES_DATA", dataPath);
      pqApplicationCore::instance()->loadStateFromString(
        xmldata.toUtf8().data(), pqActiveObjects::instance().activeServer());
    }
    else
    {
      qCritical("Failed to open resource");
    }
    pqFixPathsInStateFilesBehavior::blockDialog(prev);
  }
}
