/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// Qt includes
#include <QDebug> 
#include <QtPlugin>

// Slicer includes
#include <qSlicerCoreApplication.h>
#include <qSlicerModuleManager.h>
#include <vtkSlicerVolumesLogic.h>

// ExtensionTemplate Logic includes
#include <vtkSlicerDICOMSpatialRegistrationImportModuleLogic.h>

// ExtensionTemplate includes
#include "qSlicerDICOMSpatialRegistrationImportModule.h"
#include "qSlicerDICOMSpatialRegistrationImportModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerDICOMSpatialRegistrationImportModule, qSlicerDICOMSpatialRegistrationImportModule);

//-----------------------------------------------------------------------------
/// \ingroup SlicerRt_DICOMSpatialRegistrationImport
class qSlicerDICOMSpatialRegistrationImportModulePrivate
{
public:
  qSlicerDICOMSpatialRegistrationImportModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerDICOMSpatialRegistrationImportModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerDICOMSpatialRegistrationImportModulePrivate::qSlicerDICOMSpatialRegistrationImportModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerDICOMSpatialRegistrationImportModule methods

//-----------------------------------------------------------------------------
qSlicerDICOMSpatialRegistrationImportModule::qSlicerDICOMSpatialRegistrationImportModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerDICOMSpatialRegistrationImportModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerDICOMSpatialRegistrationImportModule::~qSlicerDICOMSpatialRegistrationImportModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerDICOMSpatialRegistrationImportModule::helpText()const
{
  QString help = 
    "The DICOMSpatialRegistrationImport module enables importing and loading DICOM Spatial Registration files into the Slicer DICOM database and the Slicer scene. "
    "For more information see <a href=\"%1/Documentation/%2.%3/Modules/DICOMSpatialRegistrationImport\">%1/Documentation/%2.%3/Modules/Models</a><br>";
  return help.arg(this->slicerWikiUrl()).arg(Slicer_VERSION_MAJOR).arg(Slicer_VERSION_MINOR);
}

//-----------------------------------------------------------------------------
QString qSlicerDICOMSpatialRegistrationImportModule::acknowledgementText()const
{
  return "This work is part of SparKit project, funded by Cancer Care Ontario (CCO)'s ACRU program and Ontario Consortium for Adaptive Interventions in Radiation Oncology (OCAIRO).";
}

//-----------------------------------------------------------------------------
QStringList qSlicerDICOMSpatialRegistrationImportModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors << QString("Kevin Wang (UHN, Toronto)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerDICOMSpatialRegistrationImportModule::icon()const
{
  return QIcon(":/Icons/DICOMSpatialRegistrationImport.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerDICOMSpatialRegistrationImportModule::categories()const
{
  return QStringList() << "Radiotherapy";
}

//-----------------------------------------------------------------------------
QStringList qSlicerDICOMSpatialRegistrationImportModule::dependencies()const
{
  return QStringList() << "";
}

//-----------------------------------------------------------------------------
void qSlicerDICOMSpatialRegistrationImportModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerDICOMSpatialRegistrationImportModule::createWidgetRepresentation()
{
  return new qSlicerDICOMSpatialRegistrationImportModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerDICOMSpatialRegistrationImportModule::createLogic()
{
  return vtkSlicerDICOMSpatialRegistrationImportModuleLogic::New();
}
