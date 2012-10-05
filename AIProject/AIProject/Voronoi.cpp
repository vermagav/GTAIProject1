#include <conio.h>
#include "voronoi.h"

void Voronoi::SetPoints()
{
	// Read points from input.
	CPoint p;

	// while (cin >> p.X() >> p.Y()) 
	//{
		points.push(p);

		// Keep track of bounding box size.
		if (p.X() < X0) X0 = p.X();
		if (p.Y() < Y0) Y0 = p.Y();
		if (p.X() > X1) X1 = p.X();
		if (p.Y() > Y1) Y1 = p.Y();
   //}

   // Add margins to the bounding box.
   double dx = (X1-X0+1)/5.0;
   double dy = (Y1-Y0+1)/5.0;
   X0 -= dx;
   X1 += dx;
   Y0 -= dy;
   Y1 += dy;
}

vector<CPoint> Voronoi::ComputeVoronoi(priority_queue<CPoint, vector<CPoint>, gt1> abcdTODO) // TODO
{
	vector<CPoint> ret;
	//set the priority Queue ofPoints and Bounding Points
	SetPoints();
	
   // Process the queues; select the top element with smaller x coordinate.
   while (!points.empty())
	   if (!events.empty() && events.top()->GetX() <= points.top().X())
         process_event();
      else
         process_point();
    
   // After all points are processed, do the remaining circle events.
   while (!events.empty())
      process_event();

   // Clean up dangling edges.
   finish_edges();

   // Output the voronoi diagram.
   print_output();

    // Each output segment in four-column format.
   vector<CSegment*>::iterator i;
   for (i = output.begin(); i != output.end(); i++)
	{
	   CPoint p0 = (*i)->GetStart();
	   CPoint p1 = (*i)->GetEnd();
	   ret.push_back(p0);
	   ret.push_back(p1);
    }

   return ret;
}

void Voronoi::process_point()
{
   // Get the next CPoint from the queue.
   CPoint p = points.top();
   points.pop();

   // Add a new arc to the parabolic front.
   front_insert(p);
}

void Voronoi::process_event()
{
   // Get the next event from the queue.
   CEvent *e = events.top();
   events.pop();

   if (e->Isvalid())
   {
      // Start a new edge.
	  CSegment *s = new CSegment(e->GetPoint());

	  // Remove the associated arc from the front.
	  CArc *a = e->GetA();

	  if (a->GetPrev()) 
	  {
		  //a->prev->next = a->next;
		  a->GetPrev()->SetNext(a->GetNext());
		
		  //a->prev->s1 = s;
		  a->GetPrev()->SetS1(s);
	  }
        
      if (a->GetNext())
	  {
		 //a->next->prev = a->prev;
         a->GetNext()->SetPrev(a->GetPrev());
		
		 //a->next->s0 = s;
         a->GetNext()->SetS0(s);   
	  }
        
      // Finish the edges before and after a.
	  //if (a->s0) a->s0->finish(e->p);
      //if (a->s1) a->s1->finish(e->p);
	
	  if (a->GetS0())
		  a->GetS0()->finish(e->GetPoint());
	  if (a->GetS1())
		  a->GetS1()->finish(e->GetPoint());

      // Recheck circle events on either side of p:
      if (a->GetPrev())
		  check_circle_event(a->GetPrev(), e->GetX());

      if (a->GetNext()) 
		  check_circle_event(a->GetNext(), e->GetX());
   }
   
   delete e;
}

void Voronoi::front_insert(CPoint p)
{
   if (!root)
   {
      root = new CArc(p);
      return;
   }

   // Find the current arc(s) at height p.y (if there are any).
   for (CArc *i = root; i; i = i->GetNext()) 
   {
      CPoint z, zz;
      if (intersect(p,i,&z))
	  {
		  // New parabola intersects arc i.  If necessary, duplicate i.
          if (i->GetNext() && !intersect(p, i->GetNext(), &zz))
		  {
			  //i->next->prev = new arc(i->p,i,i->next);
              // i->next = i->next->prev;
			  i->GetNext()->SetPrev(new CArc(i->GetPoint(), i, i->GetNext()));
			  i->SetNext(i->GetNext()->GetPrev());
          }
		  else
			  i->SetNext(new CArc(i->GetPoint(), i));
         
		  i->GetNext()->SetS1(i->GetS1());

         // Add p between i and i->GetNext().
         i->GetNext()->SetPrev(new CArc(p, i, i->GetNext()));
         i->SetNext(i->GetNext()->GetPrev());

         i = i->GetNext(); // Now i points to the new arc.

         // Add new half-edges connected to i's endpoints.
		 //i->prev->s1 = i->s0 = new seg(z);
         //i->next->s0 = i->s1 = new seg(z);
         
		 i->SetS0(new CSegment(z));
		 i->GetPrev()->SetS1(i->GetS0());

		 i->SetS1(new CSegment(z));
		 i->GetNext()->SetS0(i-> GetS1());

         // Check for new circle events around the new arc:
         check_circle_event(i, p.X());
		 check_circle_event(i->GetPrev(), p.X());
         check_circle_event(i->GetNext(), p.X());

         return;
      }
   }

   // Special case: If p never intersects an arc, append it to the list.
   CArc *i;

   // Find the last node.
   for (i = root; i->GetNext(); i = i->GetNext()) ; 

   i->SetNext(new CArc(p,i));
   
   // Insert segment between p and i
   CPoint start;
   start.X( X0 );
   start.Y( (i->GetNext()->GetPoint().Y() + i->GetPoint().Y()) / 2 );
    
   i->GetNext()->SetS0(new CSegment(start));
   i->SetS1(i->GetNext()->GetS0());

}

// Look for a new circle event for arc i.
void Voronoi::check_circle_event(CArc *i, double x0)
{
   // Invalidate any old event.
	if (i->GetEvent() && i->GetEvent()->GetX() != x0)
		i->GetEvent()->SetValid(false);
	
	i->SetEvent(NULL);

	if (!i->GetPrev() || !i->GetNext())
      return;

   double x;
   CPoint o;

   if (circle(i->GetPrev()->GetPoint(), i->GetPoint(), i->GetNext()->GetPoint(), &x, &o) && x > x0)
   {
      // Create new event.
	   i->SetEvent(new CEvent(x, o, i));
	   events.push(i->GetEvent());
   }
}


// Find the rightmost CPoint on the circle through a,b,c.
bool Voronoi::circle(CPoint a, CPoint b, CPoint c, double *x, CPoint *o)
{
   // Check that bc is a "right turn" from ab.
   if ((b.X()-a.X())*(c.Y()-a.Y()) - (c.X()-a.X())*(b.Y()-a.Y()) > 0)
      return false;

   // Algorithm from O'Rourke 2ed p. 189.
   double A = b.X() - a.X(),  B = b.Y() - a.Y(),
          C = c.X() - a.X(),  D = c.Y() - a.Y(),
          E = A * (a.X() + b.X()) + B * (a.Y() + b.Y()),
          F = C * (a.X() + c.X()) + D * (a.Y() + c.Y()),
          G = 2 * (A * (c.Y() - b.Y()) - B * (c.X() - b.X()));

   if (G == 0) return false;  // Points are co-linear.

   // Point o is the center of the circle.
   o->X( (D*E-B*F)/G );
   o->Y( (A*F-C*E)/G );

   // o.x plus radius equals max x coordinate.
   *x = o->X() + sqrt( pow(a.X() - o->X(), 2) + pow(a.Y() - o->Y(), 2) );
   return true;
}

// Will a new parabola at CPoint p intersect with arc i?
bool Voronoi::intersect(CPoint p, CArc *i, CPoint *res)
{
	if (i->GetPoint().X() == p.X())
		return false;

   double a,b;
	
   // Get the intersection of i->prev, i.
   if (i->GetPrev()) 
	   a = intersection(i->GetPrev()->GetPoint(), i->GetPoint(), p.X()).Y();
   
   // Get the intersection of i->next, i.
   if (i->GetNext()) 
	   b = intersection(i->GetPoint(), i->GetNext()->GetPoint(), p.X()).Y();

   if ((!i->GetPrev() || a <= p.Y()) && (!i->GetNext() || p.Y() <= b))
   {
      res->Y( p.Y() );

      // Plug it back into the parabola equation.
	  res->X( (i->GetPoint().X() * i->GetPoint().X() + (i->GetPoint().Y()-res->Y()) * (i->GetPoint().Y()-res->Y()) - p.X() * p.X()) / (2 * i->GetPoint().X() - 2 * p.X()) );

      return true;
   }
   return false;
}

// Where do two parabolas intersect?
CPoint Voronoi::intersection(CPoint p0, CPoint p1, double l)
{
   CPoint res, p = p0;

   if (p0.X() == p1.X())
      res.Y( (p0.Y() + p1.Y()) / 2 );
   else if (p1.X() == l)
      res.Y( p1.Y() );
   else if (p0.X() == l) {
      res.Y( p0.Y() );
      p = p1;
   } else {
      // Use the quadratic formula.
      double z0 = 2*(p0.X() - l);
      double z1 = 2*(p1.X() - l);

      double a = 1/z0 - 1/z1;
      double b = -2*(p0.Y()/z0 - p1.Y()/z1);
      double c = (p0.Y()*p0.Y() + p0.X()*p0.X() - l*l)/z0 - (p1.Y()*p1.Y() + p1.X()*p1.X() - l*l)/z1;

      res.Y( ( -b - sqrt(b*b - 4*a*c) ) / (2*a) );
   }
   // Plug back into one of the parabola equations.
   res.X( (p.X()*p.X() + (p.Y()-res.Y())*(p.Y()-res.Y()) - l*l)/(2*p.X()-2*l) );
   return res;
}



void Voronoi::finish_edges()
{
   // Advance the sweep line so no parabolas can cross the bounding box.
   double l = X1 + (X1-X0) + (Y1-Y0);

   // Extend each remaining segment to the new parabola intersections.
   for (CArc *i = root; i->GetNext(); i = i->GetNext())
	   if (i->GetS1())
		   i->GetS1()->finish(intersection(i->GetPoint(), i->GetNext()->GetPoint(), l*2));
}

void Voronoi::print_output()
{
   // Bounding box coordinates.
   cout << X0 << " "<< X1 << " " << Y0 << " " << Y1 << endl;

   // Each output segment in four-column format.
   vector<CSegment*>::iterator i;
   for (i = output.begin(); i != output.end(); i++) {
	   CPoint p0 = (*i)->GetStart();
	   CPoint p1 = (*i)->GetEnd();
      cout << p0.X() << " " << p0.Y() << " " << p1.X() << " " << p1.Y() << endl;
   }
}