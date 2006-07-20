/*=========================================================================

  Program:   ParaView
  Module:    vtkSMGenericViewDisplay.cxx

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkSMGenericViewDisplay.h"

#include "vtkObjectFactory.h"

vtkStandardNewMacro(vtkSMGenericViewDisplay);
vtkCxxRevisionMacro(vtkSMGenericViewDisplay, "1.1");

//-----------------------------------------------------------------------------
vtkSMGenericViewDisplay::vtkSMGenericViewDisplay()
{
}

//-----------------------------------------------------------------------------
vtkSMGenericViewDisplay::~vtkSMGenericViewDisplay()
{
}
 
//-----------------------------------------------------------------------------
void vtkSMGenericViewDisplay::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
}

