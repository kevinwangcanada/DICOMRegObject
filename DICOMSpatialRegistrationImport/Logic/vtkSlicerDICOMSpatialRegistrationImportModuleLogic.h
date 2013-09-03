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

// .NAME vtkSlicerDICOMSpatialRegistrationImportModuleLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerDICOMSpatialRegistrationImportLogic_h
#define __vtkSlicerDICOMSpatialRegistrationImportLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"

//BTX
// STD includes
#include <vector>
//ETX

#include "vtkSlicerDICOMSpatialRegistrationImportModuleLogicExport.h"

class vtkDICOMImportInfo;
class vtkMatrix4x4;
class vtkSlicerDICOMSpatialRegistrationReader;

/// \ingroup SlicerRt_DICOMSpatialRegistrationImportLogic
class VTK_SLICER_DICOMSPATIALREGISTRATIONIMPORT_MODULE_LOGIC_EXPORT vtkSlicerDICOMSpatialRegistrationImportModuleLogic :
  public vtkSlicerModuleLogic
{
public:
  static vtkSlicerDICOMSpatialRegistrationImportModuleLogic *New();
  vtkTypeMacro(vtkSlicerDICOMSpatialRegistrationImportModuleLogic, vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);

  /// Examine a list of file lists and determine what objects can be loaded from them
  void Examine(vtkDICOMImportInfo *importInfo);

  /// Load DICOM RT series from file name
  /// /return True if loading successful
  bool LoadDICOMSpatialRegistration(vtkDICOMImportInfo *loadInfo);

protected:
  vtkSlicerDICOMSpatialRegistrationImportModuleLogic();
  virtual ~vtkSlicerDICOMSpatialRegistrationImportModuleLogic();

  /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();

  /// Load RT Structure Set and related objects into the MRML scene
  /// \return Success flag
  bool LoadSpatialRegistration(vtkSlicerDICOMSpatialRegistrationReader* regReader, vtkDICOMImportInfo* loadInfo);

  /// Load RT Structure Set and related objects into the MRML scene
  /// \return Success flag
  bool LoadSpatialFiducials(vtkSlicerDICOMSpatialRegistrationReader* regReader, vtkDICOMImportInfo* loadInfo);

  /// Load RT Structure Set and related objects into the MRML scene
  /// \return Success flag
  bool LoadDeformableSpatialRegistration(vtkSlicerDICOMSpatialRegistrationReader* regReader, vtkDICOMImportInfo* loadInfo);

  /// Add an ROI contour to the scene
  //vtkMRMLTransformNode* AddTransformNode(vtkMatrix4x4* registrationMatrix);

private:
  vtkSlicerDICOMSpatialRegistrationImportModuleLogic(const vtkSlicerDICOMSpatialRegistrationImportModuleLogic&); // Not implemented
  void operator=(const vtkSlicerDICOMSpatialRegistrationImportModuleLogic&);              // Not implemented
};

#endif
