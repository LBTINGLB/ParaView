/*=========================================================================

  Program:   ParaView
  Module:    vtkPVIceTRenderModule.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkPVIceTRenderModule - Handles MPI and Client Server
// .SECTION Description
// This module hanldes both the cases of ParaView running Client-Server
// and ParaView running as a set MPI processes.

#ifndef __vtkPVIceTRenderModule_h
#define __vtkPVIceTRenderModule_h

#include "vtkPVMultiDisplayRenderModule.h"

class vtkCompositeRenderManager;

class VTK_EXPORT vtkPVIceTRenderModule : public vtkPVMultiDisplayRenderModule
{
public:
  static vtkPVIceTRenderModule* New();
  vtkTypeRevisionMacro(vtkPVIceTRenderModule,vtkPVMultiDisplayRenderModule);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the application right after construction.
  virtual void SetPVApplication(vtkPVApplication *pvApp);

  void StillRender();
  void InteractiveRender();

protected:
  vtkPVIceTRenderModule();
  ~vtkPVIceTRenderModule();

  // This is the IceT manager that is ignorent of the client.
  // It runs on all processes of the server.
  vtkSetStringMacro(DisplayManagerTclName);
  char *DisplayManagerTclName;

  vtkPVIceTRenderModule(const vtkPVIceTRenderModule&); // Not implemented
  void operator=(const vtkPVIceTRenderModule&); // Not implemented
};


#endif
