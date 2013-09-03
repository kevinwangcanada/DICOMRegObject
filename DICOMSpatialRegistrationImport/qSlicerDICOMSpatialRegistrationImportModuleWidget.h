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

#ifndef __qSlicerDICOMSpatialRegistrationImportModuleWidget_h
#define __qSlicerDICOMSpatialRegistrationImportModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerDICOMSpatialRegistrationImportModuleExport.h"

class qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate;
class vtkMRMLNode;

/// \ingroup SlicerRt_DICOMSpatialRegistrationImport
class Q_SLICER_QTMODULES_DICOMSPATIALREGISTRATIONIMPORT_EXPORT qSlicerDICOMSpatialRegistrationImportModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerDICOMSpatialRegistrationImportModuleWidget(QWidget *parent=0);
  virtual ~qSlicerDICOMSpatialRegistrationImportModuleWidget();

public slots:
  void LoadDICOMSpatialRegistration();

protected:
  QScopedPointer<qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate> d_ptr;
  
  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerDICOMSpatialRegistrationImportModuleWidget);
  Q_DISABLE_COPY(qSlicerDICOMSpatialRegistrationImportModuleWidget);
};

#endif
