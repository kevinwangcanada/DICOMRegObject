cmake_minimum_required(VERSION 2.8.9)

#-----------------------------------------------------------------------------
project(DICOMRegObject)

#-----------------------------------------------------------------------------
set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/MRgRT")
set(EXTENSION_CATEGORY "MRgRT")
set(EXTENSION_CONTRIBUTORS "Kevin Wang (PMH)")
set(EXTENSION_DESCRIPTION "This is a development module for loading Dicom registration object")
set(EXTENSION_ICONURL "http://viewvc.slicer.org/viewvc.cgi/Slicer4/trunk/Extensions/Testing/DICOMRegObject/DICOMRegObject.png?revision=21746&view=co")
set(EXTENSION_SCREENSHOTURLS "http://wiki.slicer.org/slicerWiki/images/4/42/Slicer-r19441-DICOMRegObject-screenshot.png")

#-----------------------------------------------------------------------------
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
add_subdirectory(DICOMSpatialRegistrationImport)

#-----------------------------------------------------------------------------
INCLUDE(${Slicer_EXTENSION_CPACK})
