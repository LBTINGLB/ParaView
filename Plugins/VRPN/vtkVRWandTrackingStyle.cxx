#include "vtkVRWandTrackingStyle.h"

#include "pqActiveObjects.h"
#include "pqDataRepresentation.h"
#include "pqView.h"
#include "vtkCamera.h"
#include "vtkMath.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkSMDoubleVectorProperty.h"
#include "vtkSMPropertyHelper.h"
#include "vtkSMRenderViewProxy.h"
#include "vtkSMRepresentationProxy.h"
#include "vtkVRQueue.h"

vtkVRWandTrackingStyle::vtkVRWandTrackingStyle(QObject* parentObject) :
  Superclass(parentObject)
{

}

vtkVRWandTrackingStyle::~vtkVRWandTrackingStyle()
{

}

// ----------------------------------------------------------------------------
// This handler currently only get the
bool vtkVRWandTrackingStyle::handleEvent(const vtkVREventData& data)
{
  std::cout<< "Event Name = " << data.name << std::endl;
  switch( data.eventType )
    {
  case BUTTON_EVENT:
    this->HandleButton( data );
    break;
  case ANALOG_EVENT:
    this->HandleAnalog( data );
    break;
  case TRACKER_EVENT:
    this->HandleTracker( data );
    break;
    }
  return false;
}

// ----------------------------------------------------------------------------
void vtkVRWandTrackingStyle::HandleTracker( const vtkVREventData& data )
{
  if ( data.data.tracker.sensor == 0 // Head from Kinect
       || data.data.tracker.sensor == 13 ) // Hand from Kinect
    {
    std::cout  << "(Tracker" << "\n"
               << "  :from  " << data.connId <<"\n"
               << "  :time  " << data.timeStamp << "\n"
               << "  :id    " << data.data.tracker.sensor << "\n"
               << "  :pos   '( "
               << data.data.tracker.pos[0] << " "
               << data.data.tracker.pos[1] << " "
               << data.data.tracker.pos[2] << " )"<< "\n"
               << "  :quat  '( "
               << data.data.tracker.quat[0] << " "
               << data.data.tracker.quat[1] << " "
               << data.data.tracker.quat[2] << " "
               << data.data.tracker.quat[3] << " ))" << "\n" ;
    }
  if ( data.data.tracker.sensor ==0 ) // Handle head tracking
    {
    this->SetHeadPoseProperty( data );
    }
}

// ----------------------------------------------------------------------------
void vtkVRWandTrackingStyle::HandleButton( const vtkVREventData& data )
{
  std::cout << "(Button" << "\n"
            << "  :from  " << data.connId <<"\n"
            << "  :time  " << data.timeStamp << "\n"
            << "  :id    " << data.data.button.button << "\n"
            << "  :state " << data.data.button.state << " )" << "\n";
}

// ----------------------------------------------------------------------------
void vtkVRWandTrackingStyle::HandleAnalog( const vtkVREventData& data )
{
  std::cout << "(Analog" << "\n"
            << "  :from  " << data.connId <<"\n"
            << "  :time  " << data.timeStamp << "\n"
            << "  :channel '(" ;
  for ( int i =0 ; i<data.data.analog.num_channel; i++ )
    {
    std::cout << data.data.analog.channel[i] ;
    }
  std::cout  << " ))" << "\n" ;
}

// ----------------------------------------------------------------------------
bool vtkVRWandTrackingStyle::GetHeadPoseProxyNProperty( vtkSMRenderViewProxy** outProxy,
                                                   vtkSMDoubleVectorProperty** outProp)
{
  *outProxy =0;
  *outProp = 0;
  vtkSMRenderViewProxy *proxy =0;
  vtkSMDoubleVectorProperty *prop =0;

  pqView *view = 0;
  view = pqActiveObjects::instance().activeView();
  if ( view )
    {
    proxy = vtkSMRenderViewProxy::SafeDownCast( view->getViewProxy() );
    if ( proxy )
      {
      prop = vtkSMDoubleVectorProperty::SafeDownCast(proxy->GetProperty( "HeadPose" ) );
      if ( prop )
        {
        *outProxy = proxy;
        *outProp =  prop;
        return true;
        }
      }
    }
  return false;
}

bool vtkVRWandTrackingStyle::SetHeadPoseProperty(const vtkVREventData &data)
{
  vtkSMRenderViewProxy *proxy =0;
  vtkSMDoubleVectorProperty *prop =0;
  if ( this->GetHeadPoseProxyNProperty( &proxy, &prop ) )
    {
    double rotMat[3][3];
    vtkMath::QuaternionToMatrix3x3( data.data.tracker.quat, rotMat );

    prop->SetElement( 0,  rotMat[0][0] );
    prop->SetElement( 1,  rotMat[0][1] );
    prop->SetElement( 2,  rotMat[0][2] );
    prop->SetElement( 3,  data.data.tracker.pos [0]*-1  );

    prop->SetElement( 4,  rotMat[1][0] );
    prop->SetElement( 5,  -rotMat[1][1] );
    prop->SetElement( 6,  rotMat[1][2] );
    prop->SetElement( 7,  data.data.tracker.pos [1]*1  );

    prop->SetElement( 8,  rotMat[2][0] );
    prop->SetElement( 9,  rotMat[2][1] );
    prop->SetElement( 10, rotMat[2][2] );
    prop->SetElement( 11, data.data.tracker.pos [2]*1  );

    prop->SetElement( 12, 0.0 );
    prop->SetElement( 13, 0.0 );
    prop->SetElement( 14, 0.0 );
    prop->SetElement( 15, 1.0 );

    return true;
    }
  return false;
}

bool vtkVRWandTrackingStyle::UpdateNRenderWithHeadPose()
{
  vtkSMRenderViewProxy *proxy =0;
  vtkSMDoubleVectorProperty *prop =0;
  if ( GetHeadPoseProxyNProperty( &proxy, &prop ) )
    {
    proxy->UpdateVTKObjects();
    proxy->StillRender();
    return true;
    }
  return false;
}

bool vtkVRWandTrackingStyle::update()
{
    // Update the when all the events are handled
    this->UpdateNRenderWithHeadPose();
    return false;
}
