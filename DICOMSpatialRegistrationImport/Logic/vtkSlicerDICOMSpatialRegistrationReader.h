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

// .NAME vtkSlicerDICOMSpatialRegistrationReader - 
// .SECTION Description
// This class manages the Reader associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerDICOMSpatialRegistrationReader_h
#define __vtkSlicerDICOMSpatialRegistrationReader_h

// VTK includes
#include "vtkObject.h"

// STD includes
#include <vector>

#include "vtkSlicerDICOMSpatialRegistrationImportModuleLogicExport.h"

class DcmDataset;
class OFString;
class vtkMatrix4x4;

// Due to some reason the Python wrapping of this class fails, therefore
// put everything between BTX/ETX to exclude from wrapping.
// TODO #210: investigate why the wrapping fails
//BTX

/// \ingroup SlicerRt_DICOMSpatialRegistrationImport
class VTK_SLICER_DICOMSPATIALREGISTRATIONIMPORT_MODULE_LOGIC_EXPORT vtkSlicerDICOMSpatialRegistrationReader : public vtkObject
{
public:
  static const std::string DICOMSPATIALREGISTRATIONREADER_DICOM_DATABASE_FILENAME;
  static const std::string DICOMSPATIALREGISTRATIONREADER_DICOM_CONNECTION_NAME;

public:
  static vtkSlicerDICOMSpatialRegistrationReader *New();
  vtkTypeMacro(vtkSlicerDICOMSpatialRegistrationReader, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);

  /// Do reading
  void Update();

public:
  /// Get model of a certain ROI by internal index
  /// \param internalIndex Internal index of ROI to get
  vtkMatrix4x4* GetRegistrationMatrix();

  /// Set input file name
  vtkSetStringMacro(FileName);

  /// Get patient name
  vtkGetStringMacro(PatientName);
  /// Get patient ID
  vtkGetStringMacro(PatientId);
  /// Get patient sex
  vtkGetStringMacro(PatientSex);
  /// Get patient birth date
  vtkGetStringMacro(PatientBirthDate);
  /// Get study instance UID
  vtkGetStringMacro(StudyInstanceUid);
  /// Get study description
  vtkGetStringMacro(StudyDescription);
  /// Get study date
  vtkGetStringMacro(StudyDate);
  /// Get study time
  vtkGetStringMacro(StudyTime);
  /// Get series instance UID
  vtkGetStringMacro(SeriesInstanceUid);
  /// Get series description
  vtkGetStringMacro(SeriesDescription);
  /// Get series modality
  vtkGetStringMacro(SeriesModality);

  /// Get DICOM database file name
  vtkGetStringMacro(DatabaseFile);

  /// Get load dose successful flag
  vtkGetMacro(LoadSpatialRegistrationSuccessful, bool);

  /// Get load dose successful flag
  vtkGetMacro(LoadSpatialFiducialsSuccessful, bool);

  /// Get load dose successful flag
  vtkGetMacro(LoadDeformableSpatialRegistrationSuccessful, bool);

protected:
  /// Load Spatial Registration
  void LoadSpatialRegistration(DcmDataset*);
  /// Load Spatial Registration
  void LoadSpatialFiducials(DcmDataset*);
  /// Load Spatial Registration
  void LoadDeformableSpatialRegistration(DcmDataset*);

protected:
  /// Set patient name
  vtkSetStringMacro(PatientName);
  /// Set patient ID
  vtkSetStringMacro(PatientId);
  /// Set patient sex
  vtkSetStringMacro(PatientSex);
  /// Set patient birth date
  vtkSetStringMacro(PatientBirthDate);
  /// Set study instance UID
  vtkSetStringMacro(StudyInstanceUid);
  /// Set study description
  vtkSetStringMacro(StudyDescription); 
  /// Set study date
  vtkSetStringMacro(StudyDate);
  /// Set study time
  vtkSetStringMacro(StudyTime);
  /// Set series instance UID
  vtkSetStringMacro(SeriesInstanceUid);
  /// Set series description
  vtkSetStringMacro(SeriesDescription); 
  /// Set series modality
  vtkSetStringMacro(SeriesModality);

  /// Set DICOM database file name
  vtkSetStringMacro(DatabaseFile);

protected:
  /// Input file name
  char* FileName;

  /// Patient name
  char* PatientName;

  /// Patient ID
  char* PatientId;

  /// Patient sex
  char* PatientSex;

  /// Patient birth date
  char* PatientBirthDate;

  /// Study instance UID
  char* StudyInstanceUid;

  /// Study description
  char* StudyDescription;

  /// Study date
  char* StudyDate;

  /// Study time
  char* StudyTime;

  /// Series instance UID
  char* SeriesInstanceUid;

  /// Series description
  char* SeriesDescription;

  /// Series modality
  char* SeriesModality;

  /// DICOM database file name
  char* DatabaseFile;

  /// 
  vtkMatrix4x4* RegistrationMatrix;

  /// Flag indicating if RT Dose has been successfully read from the input dataset
  bool LoadSpatialRegistrationSuccessful;

  /// Flag indicating if RT Dose has been successfully read from the input dataset
  bool LoadSpatialFiducialsSuccessful;

  /// Flag indicating if RT Dose has been successfully read from the input dataset
  bool LoadDeformableSpatialRegistrationSuccessful;

protected:
  vtkSlicerDICOMSpatialRegistrationReader();
  virtual ~vtkSlicerDICOMSpatialRegistrationReader();

private:
  vtkSlicerDICOMSpatialRegistrationReader(const vtkSlicerDICOMSpatialRegistrationReader&); // Not implemented
  void operator=(const vtkSlicerDICOMSpatialRegistrationReader&);         // Not implemented
};
//ETX

#endif
