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

// DICOMSpatialRegistrationImport includes
#include "vtkSlicerDICOMSpatialRegistrationImportModuleLogic.h"
#include "vtkSlicerDICOMSpatialRegistrationReader.h"
#include "vtkDICOMImportInfo.h"

// Slicer Logic includes
#include "vtkSlicerVolumesLogic.h"


// DCMTK includes
#include <dcmtk/dcmdata/dcfilefo.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcdatset.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/ofstd/ofcond.h>
#include <dcmtk/ofstd/ofstring.h>
#include <dcmtk/ofstd/ofstd.h>        /* for class OFStandard */

// MRML includes
#include <vtkMRMLLinearTransformNode.h>

// VTK includes
#include <vtkSmartPointer.h>
#include <vtkStringArray.h>
#include <vtkMatrix4x4.h>

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerDICOMSpatialRegistrationImportModuleLogic);

//----------------------------------------------------------------------------
vtkSlicerDICOMSpatialRegistrationImportModuleLogic::vtkSlicerDICOMSpatialRegistrationImportModuleLogic()
{
}

//----------------------------------------------------------------------------
vtkSlicerDICOMSpatialRegistrationImportModuleLogic::~vtkSlicerDICOMSpatialRegistrationImportModuleLogic()
{
}

//----------------------------------------------------------------------------
void vtkSlicerDICOMSpatialRegistrationImportModuleLogic::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

//-----------------------------------------------------------------------------
void vtkSlicerDICOMSpatialRegistrationImportModuleLogic::RegisterNodes()
{
}

//---------------------------------------------------------------------------
void vtkSlicerDICOMSpatialRegistrationImportModuleLogic::Examine(vtkDICOMImportInfo *importInfo)
{
  importInfo->RemoveAllLoadables();

  for (int fileListIndex=0; fileListIndex<importInfo->GetNumberOfFileLists(); fileListIndex++)
  {
    vtkStringArray *fileList=importInfo->GetFileList(fileListIndex);
    for (int fileIndex=0; fileIndex<fileList->GetNumberOfValues(); fileIndex++)
    {
      DcmFileFormat fileformat;

      vtkStdString fileName=fileList->GetValue(fileIndex);
      OFCondition result;
      result = fileformat.loadFile(fileName.c_str(), EXS_Unknown);
      if (!result.good())
      {
        continue; // failed to parse this file, skip it
      }
      DcmDataset *dataset = fileformat.getDataset();
      // check SOP Class UID for one of the supported RT objects
      OFString sopClass;
      if (!dataset->findAndGetOFString(DCM_SOPClassUID, sopClass).good() || sopClass.empty())
      {
        continue; // failed to parse this file, skip it
      }    
      
      // DICOM parsing is successful, now check if the object is loadable 
      std::string name;
      std::string tooltip;
      std::string warning;
      bool selected=true;
      double confidence=0.9; // almost sure, it's not 1.0 to allow user modules to override this importer

      OFString seriesNumber;
      dataset->findAndGetOFString(DCM_SeriesNumber, seriesNumber);
      if (!seriesNumber.empty())
      {
        name+=std::string(seriesNumber.c_str())+": ";
      }

      if (sopClass == UID_SpatialRegistrationStorage)
      {
        name+="SpatialReg";
        OFString instanceNumber;
        dataset->findAndGetOFString(DCM_InstanceNumber, instanceNumber);
        OFString seriesDescription;
        dataset->findAndGetOFString(DCM_SeriesDescription, seriesDescription);
        if (!seriesDescription.empty())
        {
          name+=std::string(": ")+seriesDescription.c_str(); 
        }
        if (!instanceNumber.empty())
        {
          name+=std::string(" [")+instanceNumber.c_str()+"]"; 
        }
      }
      else if (sopClass == UID_SpatialFiducialsStorage)
      {
        name+="SpatialFid";
        OFString instanceNumber;
        dataset->findAndGetOFString(DCM_InstanceNumber, instanceNumber);
        OFString seriesDescription;
        dataset->findAndGetOFString(DCM_SeriesDescription, seriesDescription);
        if (!seriesDescription.empty())
        {
          name+=std::string(": ")+seriesDescription.c_str(); 
        }
        if (!instanceNumber.empty())
        {
          name+=std::string(" [")+instanceNumber.c_str()+"]"; 
        }
      }
      else if (sopClass == UID_DeformableSpatialRegistrationStorage)
      {
        name+="DeformableReg";
        OFString instanceNumber;
        dataset->findAndGetOFString(DCM_InstanceNumber, instanceNumber);
        OFString seriesDescription;
        dataset->findAndGetOFString(DCM_SeriesDescription, seriesDescription);
        if (!seriesDescription.empty())
        {
          name+=std::string(": ")+seriesDescription.c_str(); 
        }
        if (!instanceNumber.empty())
        {
          name+=std::string(" [")+instanceNumber.c_str()+"]"; 
        }
      }
      else
      {
        continue; // not an Registration Object
      }

      // The object is stored in a single file
      vtkSmartPointer<vtkStringArray> loadableFileList=vtkSmartPointer<vtkStringArray>::New();
      loadableFileList->InsertNextValue(fileName);
     
      importInfo->InsertNextLoadable(loadableFileList, name.c_str(), tooltip.c_str(), warning.c_str(), selected, confidence);
    }
  }
}

//---------------------------------------------------------------------------
bool vtkSlicerDICOMSpatialRegistrationImportModuleLogic::LoadDICOMSpatialRegistration(vtkDICOMImportInfo *loadInfo)
{
  bool loadSuccessful = false;
  if (!loadInfo || !loadInfo->GetLoadableFiles(0) || loadInfo->GetLoadableFiles(0)->GetNumberOfValues() < 1)
  {
    vtkErrorMacro("LoadDICOMSpatialRegistration: Unable to load DICOM REG data due to invalid loadable information.");
    return loadSuccessful;
  }

  vtkStdString firstFileNameStr = loadInfo->GetLoadableFiles(0)->GetValue(0);
  const char* seriesName = loadInfo->GetLoadableName(0);
  std::cout << "Loading series '" << seriesName << "' from file '" << firstFileNameStr << "'" << std::endl;

  vtkSmartPointer<vtkSlicerDICOMSpatialRegistrationReader> spatialRegistrationReader = vtkSmartPointer<vtkSlicerDICOMSpatialRegistrationReader>::New();
  spatialRegistrationReader->SetFileName(firstFileNameStr.c_str());
  spatialRegistrationReader->Update();

  // spatial registration
  if (spatialRegistrationReader->GetLoadSpatialRegistrationSuccessful())
  {
    loadSuccessful = this->LoadSpatialRegistration(spatialRegistrationReader, loadInfo);
  }

  // spatial fiducials
  if (spatialRegistrationReader->GetLoadSpatialFiducialsSuccessful())
  {
    loadSuccessful = this->LoadSpatialFiducials(spatialRegistrationReader, loadInfo);
  }

  // deformable spatial registration
  if (spatialRegistrationReader->GetLoadDeformableSpatialRegistrationSuccessful())
  {
    loadSuccessful = this->LoadDeformableSpatialRegistration(spatialRegistrationReader, loadInfo);
  }

  return loadSuccessful;
}

//---------------------------------------------------------------------------
bool vtkSlicerDICOMSpatialRegistrationImportModuleLogic::LoadSpatialRegistration(vtkSlicerDICOMSpatialRegistrationReader* regReader, vtkDICOMImportInfo *loadInfo)
{
  vtkStdString firstFileNameStr = loadInfo->GetLoadableFiles(0)->GetValue(0);
  const char* seriesName = loadInfo->GetLoadableName(0);

  vtkMatrix4x4* regMatrix = NULL;
  regMatrix = regReader->GetRegistrationMatrix();

  // change to RAS system from DICOM LPS system
  vtkSmartPointer<vtkMatrix4x4> invMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
  invMatrix->Identity();
  invMatrix->SetElement(0,0,-1);
  invMatrix->SetElement(1,1,-1);
  vtkSmartPointer<vtkMatrix4x4> forMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
  forMatrix->Identity();
  forMatrix->SetElement(0,0,-1);
  forMatrix->SetElement(1,1,-1);
  vtkMatrix4x4::Multiply4x4(invMatrix, regMatrix, regMatrix);
  vtkMatrix4x4::Multiply4x4(regMatrix, forMatrix, regMatrix);

  // Add transform node
  vtkSmartPointer<vtkMRMLLinearTransformNode> spatialTransformNode = vtkSmartPointer<vtkMRMLLinearTransformNode>::New();
  spatialTransformNode->SetScene(this->GetMRMLScene());
  spatialTransformNode->SetDisableModifiedEvent(1);
  std::string spatialTransformNodeName;
  spatialTransformNodeName = std::string(seriesName);
  // spatialTransformNodeName = this->GetMRMLScene()->GenerateUniqueName(spatialTransformNodeName);
  // spatialTransformNode->SetName(spatialTransformNodeName.c_str());
  spatialTransformNode->HideFromEditorsOff();
  spatialTransformNode->SetAndObserveMatrixTransformToParent(regMatrix);
  spatialTransformNode->SetDisableModifiedEvent(0);

  this->GetMRMLScene()->AddNode(spatialTransformNode);

  return true;
}

// TODO: not implemented yet...
//---------------------------------------------------------------------------
bool vtkSlicerDICOMSpatialRegistrationImportModuleLogic::LoadSpatialFiducials(vtkSlicerDICOMSpatialRegistrationReader* regReader, vtkDICOMImportInfo *loadInfo)
{
  return false;
}

// TODO: not implemented yet...
//---------------------------------------------------------------------------
bool vtkSlicerDICOMSpatialRegistrationImportModuleLogic::LoadDeformableSpatialRegistration(vtkSlicerDICOMSpatialRegistrationReader* regReader, vtkDICOMImportInfo *loadInfo)
{
  return true;
}
