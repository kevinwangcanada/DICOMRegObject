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

// SlicerQt includes
#include "qSlicerDICOMSpatialRegistrationImportModuleWidget.h"
#include "ui_qSlicerDICOMSpatialRegistrationImportModule.h"
#include "vtkSlicerDICOMSpatialRegistrationImportModuleLogic.h"

//-----------------------------------------------------------------------------
/// \ingroup SlicerRt_DICOMSpatialRegistrationImport
class qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate: public Ui_qSlicerDICOMSpatialRegistrationImportModule
{
public:
  qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate();
};

//-----------------------------------------------------------------------------
// qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate::qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerDICOMSpatialRegistrationImportModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerDICOMSpatialRegistrationImportModuleWidget::qSlicerDICOMSpatialRegistrationImportModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerDICOMSpatialRegistrationImportModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerDICOMSpatialRegistrationImportModuleWidget::~qSlicerDICOMSpatialRegistrationImportModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerDICOMSpatialRegistrationImportModuleWidget::setup()
{
  Q_D(qSlicerDICOMSpatialRegistrationImportModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();

  QObject::connect( this->d_ptr->pushButton_LoadDICOMSpatialRegistration, SIGNAL(pressed()), this, SLOT(LoadDICOMSpatialRegistration()) );
}

//-----------------------------------------------------------------------------
void qSlicerDICOMSpatialRegistrationImportModuleWidget::LoadDICOMSpatialRegistration()
{
}
