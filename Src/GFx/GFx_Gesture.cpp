#include "GFxConfig.h"
#ifdef GFX_GESTURE_RECOGNIZE

#include "GFx/GFx_Gesture.h"
#include "GFx/GFx_Input.h"
#include "GFx/GFx_PlayerImpl.h"
//#include <iostream>

namespace Scaleform { namespace GFx {


//////////////////////////////////////////////////////////////////////////
// Gesture-related utils

float Slope(float deltaX, float deltaY)
{
	return deltaY/deltaX;
}

float angleBetweenLines(float line1x, float line1y, float line1x2, float line1y2, float line2x, float line2y, float line2x2, float line2y2) 
{
	float a = line1x2 - line1x;
	float b = line1y2 - line1y;
	float c = line2x2 - line2x;
	float d = line2y2 - line2y;

	float atanA = atan2(a, b) ;
	float atanB = atan2(c, d);

	float angle = (atanA - atanB)*(180/3.14159265359f);

	// TODO: fix range mismatch

	return angle;
}

float AngleBetweenSlopes(float m1, float m2)
{
	return atan(abs( (m1 - m2)/(1 + m1*m2) ));
}


float Angle(float x1, float y1, float x2, float y2)
{
	float deltaY = y2 - y1;
	float deltaX = x2 - x1;

	float angleInDegrees = atan2(deltaY, deltaX) * 180 / 3.14159265359f;
	return angleInDegrees;
	}

float Dot(PointF v1, PointF v2)
{
	return (v1.x*v2.x + v1.y*v2.y);
}

float signedAngle(PointF v1, PointF v2)
{
	float perpDot = v1.x * v2.y - v1.y * v2.x;
	
	return (float)atan2(perpDot, Dot(v1, v2)) * 180 / 3.14159265359f;
}

float Distance(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrtf(dx * dx + dy * dy);
}

//////////////////////////////////////////////////////////////////////////
// Gesture-related class declarations

TouchPoint::TouchPoint(UInt32 id, float x, float y):id(id),x(x),y(y){}

void GestureRecognizer::setup()
{
	oldTime = Timer::GetTicksMs();
	DPI = 60;
	minSwipeDist = DPI;
	selected=0;

	supportedGestures[0] = new GestureRotate();
	supportedGestures[0]->parent = this;

	supportedGestures[1] = new GesturePan();
	supportedGestures[1]->parent = this;

	supportedGestures[2] = new GestureZoom();
	supportedGestures[2]->parent = this;

	supportedGestures[3] = new GesturePressAndTap();
	supportedGestures[3]->parent = this;

	supportedGestures[4] = new GestureSwipe();
	supportedGestures[4]->parent = this;

	supportedGestures[5] = new GestureTwoFingerTap();
	supportedGestures[5]->parent = this;

	numSupportedGestures = 6;

}

void GestureRecognizer::SetMovie(Ptr<Scaleform::GFx::Movie> moviePtr)
{
	pMovie = moviePtr;
}

TouchPoint *GestureRecognizer::getTouchPointById(UInt32 id)
{
	for(UPInt a=0;a<touchPointArr.GetSize();a++)
	{
		if(touchPointArr[a]->id==id)
			return touchPointArr[a];
	}
	
	return NULL;
}

void GestureRecognizer::ProcessDown(UInt32 id, const Point<int>& screenPt, const PointF& moviePt)
{
	TouchPoint *tp = new TouchPoint(id, screenPt.x, screenPt.y);
	
	touchPointArr.PushBack(tp);

	update();
}

void GestureRecognizer::ProcessUp(UInt32 id, const Point<int>& screenPt, const PointF& moviePt)
{
	for(UPInt a=0;a<touchPointArr.GetSize();a++)
	{
		if(touchPointArr[a]->id==id)
		{
			touchPointArr[a]->x=screenPt.x;
			touchPointArr[a]->y=screenPt.y;
			touchPointArr.RemoveAt(a);
		}
	}

	update();
}

void GestureRecognizer::ProcessMove(UInt32 id, const Point<int>& screenPt, const PointF& moviePt)
{
	TouchPoint* tp = getTouchPointById(id); 
	if(tp==NULL)
		return;

	tp->x = screenPt.x;
	tp->y = screenPt.y;

	update();
}


void GestureRecognizer::update()
{
	// calculating deltaTime
	UINT32 newTime = Timer::GetTicksMs(); 
	deltaSeconds = (float)(newTime - oldTime)/1000.0f;
	oldTime = newTime;

	// calculating centroid of current points
	if(touchPointArr.GetSize()>0)
	{
		float sumX=0;
		float sumY=0;

		for(UPInt a=0;a<touchPointArr.GetSize();a++ )
		{
			sumX+=touchPointArr[a]->x;
			sumY+=touchPointArr[a]->y;
		}

		NewCentroidX = sumX / (float)touchPointArr.GetSize();
		NewCentroidY = sumY / (float)touchPointArr.GetSize();
	}

	// calculating distance of centroid change
	deltaInches = Distance(OldCentroidX, OldCentroidY, NewCentroidX, NewCentroidY) / DPI;

	//
	for(int a=0; a<numSupportedGestures; a++)
	{
		if(selected==0 || selected==supportedGestures[a])
		{
			supportedGestures[a]->update();
		}
		else
		{
			supportedGestures[a]->currentPhase=Gesture::Phase_None;
			supportedGestures[a]->timeCounter=0;
			supportedGestures[a]->started=false;
			supportedGestures[a]->recognized=false;
		}
	}

	//
	OldCentroidX=NewCentroidX;
	OldCentroidY=NewCentroidY;
}

// Gesture
Gesture::Gesture()
{
	currentPhase = Phase_None;
	started=false;
}

GestureRotate::GestureRotate(){}
GesturePan::GesturePan(){ }
GestureZoom::GestureZoom(){}
GestureSwipe::GestureSwipe(){ }
GesturePressAndTap::GesturePressAndTap(){}
GestureTwoFingerTap::GestureTwoFingerTap(){}

void Gesture::update(){}

// AS3 usage
//	event.currentTarget.x += event.offsetX;
//	event.currentTarget.y += event.offsetY;
void GesturePan::update()
{
	Array<TouchPoint*> touchPoints = parent->touchPointArr;

	float dist;

	int count=0;
	float coordsX[2];
	float coordsY[2];

	if(touchPoints.GetSize()==2)
	{
		for(int a=0;a<2;a++ )
		{
			coordsX[count] = touchPoints[a]->x;
			coordsY[count] = touchPoints[a]->y;
			count++;
		}

		dist = Distance(coordsX[0], coordsY[0], coordsX[1], coordsY[1]);
	}

	switch(currentPhase)
	{
	case Phase_None:

		if(touchPoints.GetSize()==2)
		{
			if(!started)
			{
				timeCounter = 0;
				startDist = Distance(coordsX[0], coordsY[0], coordsX[1], coordsY[1]);

				totalCentroidOffsetX=0;
				totalCentroidOffsetY=0;

				startCentroidX=parent->NewCentroidX;
				startCentroidY=parent->NewCentroidY;

				currentPhase=Phase_Update;

				started=true;
				recognized=false;
			}
		}

		break;
	case Phase_Update:

		if(touchPoints.GetSize()!=2)
		{
			if(recognized)
			{
				recognized=false;

				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_End, GestureEvent::GestureBit_Pan, PointF(parent->OldCentroidX, parent->OldCentroidY), PointF(0, 0), 1, 1, 0);
				GestureEvent evt(GFx::Event::GestureEnd, GestureEvent::GestureBit_Pan, parent->OldCentroidX, parent->OldCentroidY, 0, 0, 1, 1, 0);
				parent->pMovie->HandleEvent(evt);

				currentPhase=Phase_None;
				parent->selected=0;
			}
			else
			{
				started=false;
				currentPhase=Phase_None;
			}
		}
		else if(!(parent->NewCentroidX==parent->OldCentroidX && parent->NewCentroidY==parent->OldCentroidY))
		{
			timeCounter+=parent->deltaSeconds;
			totalCentroidOffsetX+=(parent->NewCentroidX-parent->OldCentroidX);
			totalCentroidOffsetY+=(parent->NewCentroidY-parent->OldCentroidY);

			if(recognized)
			{
				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_Update, GestureEvent::GestureBit_Pan, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF((parent->NewCentroidX-parent->OldCentroidX), (parent->NewCentroidY-parent->OldCentroidY)), 1,1,0);
				GestureEvent evt(GFx::Event::Gesture, GestureEvent::GestureBit_Pan, parent->NewCentroidX, parent->NewCentroidY, (parent->NewCentroidX-parent->OldCentroidX), (parent->NewCentroidY-parent->OldCentroidY), 1, 1, 0);
				parent->pMovie->HandleEvent(evt);
			}		
			else if(Distance(parent->NewCentroidX, parent->NewCentroidY, startCentroidX, startCentroidY)>20) // threshold
			{
				//std::cout<<"distance "<< Distance(parent->NewCentroidX, parent->NewCentroidY, startCentroidX, startCentroidY)<<"\n";

				recognized=true;
				parent->selected=this;
				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_Begin, GestureEvent::GestureBit_Pan, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0, 0), 1, 1, 0);
				GestureEvent evt(GFx::Event::GestureBegin, GestureEvent::GestureBit_Pan, parent->NewCentroidX, parent->NewCentroidY, 0, 0, 1, 1, 0);
				parent->pMovie->HandleEvent(evt);
			}
		}

		break;
	}
}

// AS3 usage
// event.target.rotation += event.rotation;
void GestureRotate::update()
{
	Array<TouchPoint*> touchPoints = parent->touchPointArr;

	int count;
	float coordsX[2];
	float coordsY[2];
	float dist;

	count=0;
	if(touchPoints.GetSize()==2)
	{
		for(int a=0;a<2;a++ )
		{
			coordsX[count] = touchPoints[a]->x;
			coordsY[count] = touchPoints[a]->y;
			count++;
		}

		dist = Distance(coordsX[0], coordsY[0], coordsX[1], coordsY[1]);
	}

	switch(currentPhase)
	{
	case Phase_None:
		if(touchPoints.GetSize()==2)
		{
			if(!started)
			{
				timeCounter = 0;
				currentPhase=Phase_Update;
				totalAngle=0;
				started=true;
				recognized=false;
			}

		}
		break;
	case Phase_Update:
		if(touchPoints.GetSize()!=2)
		{
			started=false;
			if(recognized)
			{
				currentPhase=Phase_None;

				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_End, GestureEvent::GestureBit_Rotate, PointF(parent->OldCentroidX, parent->OldCentroidY), PointF(0,0), 1,1,0);
				GestureEvent evt(GFx::Event::GestureEnd, GestureEvent::GestureBit_Rotate, parent->OldCentroidX, parent->OldCentroidY, 0, 0, 1, 1, 0);
				parent->pMovie->HandleEvent(evt);

				recognized=false;
				parent->selected=0;
			}
		}
		else if(!(coordsX[1]==lastCoordsX[1] && coordsX[0]==lastCoordsX[0] && coordsY[1]==lastCoordsY[1] && coordsY[0]==lastCoordsY[0]))
		{
			timeCounter+=parent->deltaSeconds;
			float deltaAngle = signedAngle(PointF(coordsX[1] - coordsX[0], coordsY[1] - coordsY[0]) , PointF(lastCoordsX[1] - lastCoordsX[0], lastCoordsY[1] - lastCoordsY[0]));

			totalAngle+=deltaAngle;


			if(recognized)
			{
				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_Update, GestureEvent::GestureBit_Rotate, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0,0), 1, 1, deltaAngle);
				GestureEvent evt(GFx::Event::Gesture, GestureEvent::GestureBit_Rotate, parent->NewCentroidX, parent->NewCentroidY, 0, 0, 1, 1, deltaAngle);
				parent->pMovie->HandleEvent(evt);
			}
			else if(abs(totalAngle)>15) // threshold
			{
				recognized=true;
				parent->selected=this;
				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_Begin, GestureEvent::GestureBit_Rotate, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0,0), 1,1,0);
				GestureEvent evt(GFx::Event::GestureBegin, GestureEvent::GestureBit_Rotate, parent->NewCentroidX, parent->NewCentroidY, 0, 0, 1, 1, 0);
				parent->pMovie->HandleEvent(evt);
			}
			
		}

		break;
	}

	if(touchPoints.GetSize()==2)
	{
		count=0;
		for(int a=0;a<2;a++ )
		{
			lastCoordsX[count] = touchPoints[a]->x;
			lastCoordsY[count] = touchPoints[a]->y;
			count++;
		}
	}
}

// AS3 usage
// event.offsetX = 1 | -1;
// event.offsetY = 1 | -1;
void GestureSwipe::update()
{
	Array<TouchPoint*> touchPoints = parent->touchPointArr;

	switch(currentPhase)
	{
	case Phase_None:

		if(touchPoints.GetSize()==1 && !started)
		{
			this->startPosX = parent->NewCentroidX;
			this->startPosY = parent->NewCentroidY;
			currentPhase = Phase_Update;
			timeCounter = 0;
			started=true;
		}

		if(touchPoints.GetSize()==0)
		{
			started=false;
		}

		break;
	case Phase_Update:
		if(touchPoints.GetSize()==1)
		{
			timeCounter+=parent->deltaSeconds;

			if(timeCounter<.5)
			{
				PointF posChange = PointF(parent->NewCentroidX - startPosX, parent->NewCentroidY - startPosY);
				if(Distance(0,0,posChange.x,posChange.y)>parent->minSwipeDist)
				{
					float HorizontalAngle;
					
					HorizontalAngle = signedAngle(posChange, PointF(1,0));
					if(abs(HorizontalAngle)<15 && posChange.x>0)
					{
						//std::cout<<"SWIPE RIGHT!"<<"\n";
						//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_All, GestureEvent::GestureBit_Swipe, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(1,0), 1,1,0);
						GestureEvent evt(GFx::Event::GestureSimple, GestureEvent::GestureBit_Swipe, parent->NewCentroidX, parent->NewCentroidY, 1, 0, 1, 1, 0);
						parent->pMovie->HandleEvent(evt);
						currentPhase = Phase_None;
					}

					HorizontalAngle = signedAngle(posChange, PointF(-1,0));
					if(abs(HorizontalAngle)<15 && posChange.x<0)
					{
						//std::cout<<"SWIPE LEFT!"<<"\n";
						//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_All, GestureEvent::GestureBit_Swipe, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(-1,0), 1,1,0);
						GestureEvent evt(GFx::Event::GestureSimple, GestureEvent::GestureBit_Swipe, parent->NewCentroidX, parent->NewCentroidY, -1, 0, 1, 1, 0);
						parent->pMovie->HandleEvent(evt);
						currentPhase = Phase_None;
					}

					///

					float VerticalAngle;

					VerticalAngle = signedAngle(posChange, PointF(0,1));
					if(abs(VerticalAngle)<15 && posChange.y>0)
					{
						//std::cout<<"SWIPE DOWN!"<<"\n";
						//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_All, GestureEvent::GestureBit_Swipe, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0,1), 1,1,0);
						GestureEvent evt(GFx::Event::GestureSimple, GestureEvent::GestureBit_Swipe, parent->NewCentroidX, parent->NewCentroidY, 0, 1, 1, 1, 0);
						parent->pMovie->HandleEvent(evt);
						currentPhase = Phase_None;
					}

					VerticalAngle = signedAngle(posChange, PointF(0,-1));
					if(abs(VerticalAngle)<15 && posChange.y<0)
					{
						//std::cout<<"SWIPE UP!"<<"\n";
						//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_All, GestureEvent::GestureBit_Swipe, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0,-1), 1,1,0);
						GestureEvent evt(GFx::Event::GestureSimple, GestureEvent::GestureBit_Swipe, parent->NewCentroidX, parent->NewCentroidY, 0, -1, 1, 1, 0);
						parent->pMovie->HandleEvent(evt);
						currentPhase = Phase_None;
					}

				}
			}
		}
		else
		{
			currentPhase = Phase_None;
		}
		break;
	}
}

//instance_name_here.scaleX *= event.scaleX;
//instance_name_here.scaleY *= event.scaleY;
void GestureZoom::update()
{
	Array<TouchPoint*> touchPoints = parent->touchPointArr;

	float dist=0;

	int count=0;
	float coordsX[2];
	float coordsY[2];

	if(touchPoints.GetSize()==2)
	{
		for(int a=0;a<2;a++ )
		{
			coordsX[count] = touchPoints[a]->x;
			coordsY[count] = touchPoints[a]->y;
			count++;
		}

		dist = Distance(coordsX[0], coordsY[0], coordsX[1], coordsY[1]);
	}

	float distX = abs(coordsX[0] - coordsX[1]);
	float distY = abs(coordsY[0] - coordsY[1]);

	switch(currentPhase)
	{
	case Phase_None:
		if(touchPoints.GetSize()==2)
		{
			if(!started)
			{
				timeCounter = 0;
				startDist = dist;

				started=true;
				recognized=false;

				currentPhase=Phase_Update;

				lastDist = dist;
				startDist = dist;

				startDistX = distX;
				startDistY = distY;
			}
		}

		break;
	case Phase_Update:

		if(touchPoints.GetSize()!=2)
		{
			started=false;
			if(recognized)
			{
				// send end phase gesture event
				currentPhase=Phase_None;
				started=false;
				recognized=false;
				parent->selected=0;

				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_End, GestureEvent::GestureBit_Zoom, PointF(parent->OldCentroidX, parent->OldCentroidY), PointF(0,0), 1,1,0);
				GestureEvent evt(GFx::Event::GestureEnd, GestureEvent::GestureBit_Zoom, parent->OldCentroidX, parent->OldCentroidY, 0, 0, 1, 1, 0);
				parent->pMovie->HandleEvent(evt);
			}
		}
		else if(!(distX==lastDistX && distY==lastDistY))
		{
			timeCounter+=parent->deltaSeconds;

			if(recognized)
			{
				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_Update, GestureEvent::GestureBit_Zoom, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0,0), distX/lastDistX, distY/lastDistY,0);
				GestureEvent evt(GFx::Event::Gesture, GestureEvent::GestureBit_Zoom, parent->NewCentroidX, parent->NewCentroidY, 0, 0, distX/lastDistX, distY/lastDistY, 0);
				parent->pMovie->HandleEvent(evt);
			}
			else
			{
				if(abs(dist - startDist)>40) // threshold
				{
					//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_Begin, GestureEvent::GestureBit_Zoom, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0,0), 1,1,0);
					GestureEvent evt(GFx::Event::GestureBegin, GestureEvent::GestureBit_Zoom, parent->NewCentroidX, parent->NewCentroidY, 0, 0, 1, 1, 0);
					parent->pMovie->HandleEvent(evt);

					recognized=true;
					parent->selected=this;

				}
			}
		}

		break;
	}

	lastDist = dist;
	lastDistX = distX;
	lastDistY = distY;
}

//event.tapLocalX;
//event.tapLocalY;
//event.tapStageX;
//event.tapStageY;
void GesturePressAndTap::update()
{
	Array<TouchPoint*> touchPoints = parent->touchPointArr;

	switch(currentPhase)
	{
	case Phase_None:
		if(touchPoints.GetSize()==1)
		{
			currentPhase = Phase_Update;
			timeCounter = 0;
			started = false;
			tapping = false;
		}
		break;
	case Phase_Update:

		timeCounter+=parent->deltaSeconds;

		if(touchPoints.GetSize()==2 && timeCounter>.15 && !tapping)
		{
			//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_All, GestureEvent::GestureBit_PressAndTap, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0, 0), 1, 1, 0);
			GestureEvent evt(GFx::Event::GestureSimple, GestureEvent::GestureBit_PressAndTap, parent->NewCentroidX, parent->NewCentroidY, 0, 0, 1, 1, 0);
			parent->pMovie->HandleEvent(evt);

			started = true;
			tapping = true;
		}

		if(touchPoints.GetSize()==1 && started)
		{
			started=false;
			tapping = false;
		}

		if(touchPoints.GetSize()==0 || touchPoints.GetSize()>2)
		{
			currentPhase = Phase_None;
		}

		break;
	}
}

// null
void GestureTwoFingerTap::update()
{
	Array<TouchPoint*> touchPoints = parent->touchPointArr;

	int count=0;

	float dist;
	float coordsX[2];
	float coordsY[2];

	if(touchPoints.GetSize()==2)
	{
		for(int a=0;a<2;a++)
		{
			coordsX[count] = touchPoints[a]->x;
			coordsY[count] = touchPoints[a]->y;
			count++;
		}

		dist = Distance(coordsX[0], coordsY[0], coordsX[1], coordsY[1]);
	}

	switch(currentPhase)
	{
	case Phase_None:

		if(touchPoints.GetSize()==2 && dist<4*parent->DPI)
		{
			currentPhase = Phase_Update;
			started=true;
			timeCounter=0;
		}

		break;
	case Phase_Update:
		
		timeCounter += parent->deltaSeconds;
		if(touchPoints.GetSize()==0)
		{
			if(timeCounter<.25)
			{
				//parent->pMovie->InputEventsQueue.AddGestureEvent(InputEventsQueueEntry::Phase_All, GestureEvent::GestureBit_TwoFingerTap, PointF(parent->NewCentroidX, parent->NewCentroidY), PointF(0, 0), 1, 1, 0);
				GestureEvent evt(GFx::Event::GestureSimple, GestureEvent::GestureBit_TwoFingerTap, parent->NewCentroidX, parent->NewCentroidY, 0, 0, 1, 1, 0);
				parent->pMovie->HandleEvent(evt);
			}

			started=false;
			currentPhase=Phase_None;
		}

		break;
	}

}

}} // namespace Scaleform::GFx

#endif // GFX_GESTURE_RECOGNIZE