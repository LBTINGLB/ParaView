/*=========================================================================

Copyright (c) 1998-2003 Kitware Inc. 469 Clifton Corporate Parkway,
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
// .NAME vtkKWLabeledLoadSaveButton - a load/save button with a label
// .SECTION Description
// The vtkKWLabeledLoadSaveButton class creates a load/save button with a label
// in front of it

#ifndef __vtkKWLabeledLoadSaveButton_h
#define __vtkKWLabeledLoadSaveButton_h

#include "vtkKWLabeledWidget.h"

class vtkKWLoadSaveButton;

class VTK_EXPORT vtkKWLabeledLoadSaveButton : public vtkKWLabeledWidget
{
public:
  static vtkKWLabeledLoadSaveButton* New();
  vtkTypeRevisionMacro(vtkKWLabeledLoadSaveButton, vtkKWLabeledWidget);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Create the widget
  virtual void Create(vtkKWApplication *app, const char *args = 0);

  // Description:
  // Convenience method to set the button label.
  void SetLoadSaveButtonLabel(const char *);
  
  // Description:
  // Convenience method to get the button load/save filename.
  char* GetLoadSaveButtonFileName();
  
  // Description:
  // Get the internal object
  vtkGetObjectMacro(LoadSaveButton, vtkKWLoadSaveButton);
  
  // Description:
  // Set the string that enables balloon help for this widget.
  // Override to pass down to children.
  virtual void SetBalloonHelpString(const char *str);
  virtual void SetBalloonHelpJustification(int j);

  // Description:
  // Pack the label last
  virtual void SetPackLabelLast(int);
  vtkGetMacro(PackLabelLast, int);
  vtkBooleanMacro(PackLabelLast, int);

  // Description:
  // Update the "enable" state of the object and its internal parts.
  // Depending on different Ivars (this->Enabled, the application's 
  // Limited Edition Mode, etc.), the "enable" state of the object is updated
  // and propagated to its internal parts/subwidgets. This will, for example,
  // enable/disable parts of the widget UI, enable/disable the visibility
  // of 3D widgets, etc.
  virtual void UpdateEnableState();

protected:
  vtkKWLabeledLoadSaveButton();
  ~vtkKWLabeledLoadSaveButton();

  int PackLabelLast;

  vtkKWLoadSaveButton *LoadSaveButton;

  // Pack or repack the widget

  virtual void Pack();

private:
  vtkKWLabeledLoadSaveButton(const vtkKWLabeledLoadSaveButton&); // Not implemented
  void operator=(const vtkKWLabeledLoadSaveButton&); // Not implemented
};

#endif

