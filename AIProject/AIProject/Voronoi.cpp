#include <conio.h>
#include "voronoi.h"

void Voronoi::SetPoints()
{
	// Read points from input.
	point p;

	while (cin >> p.x >> p.y) 
	{
		points.push(p);

		// Keep track of bounding box size.
		if (p.x < X0) X0 = p.x;
		if (p.y < Y0) Y0 = p.y;
		if (p.x > X1) X1 = p.x;
		if (p.y > Y1) Y1 = p.y;
   }

   // Add margins to the bounding box.
   double dx = (X1-X0+1)/5.0;
   double dy = (Y1-Y0+1)/5.0;
   X0 -= dx;
   X1 += dx;
   Y0 -= dy;
   Y1 += dy;
}

vector<CSegment*> Voronoi::ComputeVornoi()
{
	//set the priority Queue ofPoints and Bounding Points
	SetPoints();
	
   // Process the queues; select the top element with smaller x coordinate.
   while (!points.empty())
	   if (!events.empty() && events.top()->GetX() <= points.top().x)
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

   return output;
}

void Voronoi::process_point()
{
   // Get the next point from the queue.
   point p = points.top();
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

void Voronoi::front_insert(point p)
{
   if (!root)
   {
      root = new CArc(p);
      return;
   }

   // Find the current arc(s) at height p.y (if there are any).
   for (CArc *i = root; i; i = i->GetNext()) 
   {
      point z, zz;
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
         check_circle_event(i, p.x);
		 check_circle_event(i->GetPrev(), p.x);
         check_circle_event(i->GetNext(), p.x);

         return;
      }
   }

   // Special case: If p never intersects an arc, append it to the list.
   CArc *i;

   // Find the last node.
   for (i = root; i->GetNext(); i = i->GetNext()) ; 

   i->SetNext(new CArc(p,i));
   
   // Insert segment between p and i
   point start;
   start.x = X0;
   start.y = (i->GetNext()->GetPoint().y + i->GetPoint().y) / 2;
    
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
   point o;

   if (circle(i->GetPrev()->GetPoint(), i->GetPoint(), i->GetNext()->GetPoint(), &x, &o) && x > x0)
   {
      // Create new event.
	   i->SetEvent(new CEvent(x, o, i));
	   events.push(i->GetEvent());
   }
}


// Find the rightmost point on the circle through a,b,c.
bool Voronoi::circle(point a, point b, point c, double *x, point *o)
{
   // Check that bc is a "right turn" from ab.
   if ((b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y) > 0)
      return false;

   // Algorithm from O'Rourke 2ed p. 189.
   double A = b.x - a.x,  B = b.y - a.y,
          C = c.x - a.x,  D = c.y - a.y,
          E = A * (a.x + b.x) + B * (a.y + b.y),
          F = C * (a.x + c.x) + D * (a.y + c.y),
          G = 2 * (A * (c.y - b.y) - B * (c.x - b.x));

   if (G == 0) return false;  // Points are co-linear.

   // Point o is the center of the circle.
   o->x = (D*E-B*F)/G;
   o->y = (A*F-C*E)/G;

   // o.x plus radius equals max x coordinate.
   *x = o->x + sqrt( pow(a.x - o->x, 2) + pow(a.y - o->y, 2) );
   return true;
}

// Will a new parabola at point p intersect with arc i?
bool Voronoi::intersect(point p, CArc *i, point *res)
{
	if (i->GetPoint().x == p.x)
		return false;

   double a,b;
	
   // Get the intersection of i->prev, i.
   if (i->GetPrev()) 
	   a = intersection(i->GetPrev()->GetPoint(), i->GetPoint(), p.x).y;
   
   // Get the intersection of i->next, i.
   if (i->GetNext()) 
	   b = intersection(i->GetPoint(), i->GetNext()->GetPoint(), p.x).y;

   if ((!i->GetPrev() || a <= p.y) && (!i->GetNext() || p.y <= b))
   {
      res->y = p.y;

      // Plug it back into the parabola equation.
	  res->x = (i->GetPoint().x * i->GetPoint().x + (i->GetPoint().y-res->y) * (i->GetPoint().y-res->y) - p.x * p.x)
		  / (2 * i->GetPoint().x - 2 * p.x);

      return true;
   }
   return false;
}

// Where do two parabolas intersect?
point Voronoi::intersection(point p0, point p1, double l)
{
   point res, p = p0;

   if (p0.x == p1.x)
      res.y = (p0.y + p1.y) / 2;
   else if (p1.x == l)
      res.y = p1.y;
   else if (p0.x == l) {
      res.y = p0.y;
      p = p1;
   } else {
      // Use the quadratic formula.
      double z0 = 2*(p0.x - l);
      double z1 = 2*(p1.x - l);

      double a = 1/z0 - 1/z1;
      double b = -2*(p0.y/z0 - p1.y/z1);
      double c = (p0.y*p0.y + p0.x*p0.x - l*l)/z0
               - (p1.y*p1.y + p1.x*p1.x - l*l)/z1;

      res.y = ( -b - sqrt(b*b - 4*a*c) ) / (2*a);
   }
   // Plug back into one of the parabola equations.
   res.x = (p.x*p.x + (p.y-res.y)*(p.y-res.y) - l*l)/(2*p.x-2*l);
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
	   point p0 = (*i)->GetStart();
	   point p1 = (*i)->GetEnd();
      cout << p0.x << " " << p0.y << " " << p1.x << " " << p1.y << endl;
   }
}
