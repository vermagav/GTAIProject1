#ifndef VORONOI_H
#define VORONOI_H

//Voronoi.h -v1.0
#include <iostream>
#include <queue>
#include <set>
#include <math.h>
#include "CPoint.h"

using namespace std;

// Notation for working with points and replace first, second with x, y
//for notational convenience
// typedef pair<double, double> CPoint;
// #define x first
// #define y second

// Arc, event, and segment datatypes
class CArc;
class CSegment;

class CEvent 
{
public:
	CEvent(double xx, CPoint pp, CArc *aa)
      : x(xx), p(pp), a(aa), valid(true)
	{}

	double GetX() const
	{
		return x;
	}

	CArc* GetA()	
	{
		return a;
	}

	CPoint GetPoint() const
	{
		return p;
	}

	bool Isvalid() const
	{
		return valid;
	}

	void SetValid(bool val)
	{
		valid = val;
	}

private:
   double x;
   CPoint p;
   CArc *a;
   bool valid;   
};


class CArc
{
public:
	CArc(CPoint pp, CArc *a=0, CArc *b=0)
    : p(pp), prev(a), next(b), e(0), s0(0), s1(0) 
	{}

	CArc* GetPrev()	const
	{
		return prev;
	}

	CArc* GetNext()	const
	{
		return next;
	}

	void SetPrev(CArc* p)
	{
		prev = p;
	}

	void SetNext(CArc* n)
	{
		next = n;
	}

	CSegment* GetS0() const
	{
		return s0;
	}

	CSegment* GetS1() const
	{
		return s1;
	}

	void SetS0(CSegment *s)
	{
		s0 = s;
	}

	void SetS1(CSegment *s)
	{
		s1 = s;
	}

	CPoint GetPoint()
	{
		return p;
	}

	CEvent* GetEvent() const
	{
		return e; 
	}

	void SetEvent(CEvent *eve)
	{
		e = eve;
	}

private:
   CPoint p;
   CArc *prev, *next;
   CEvent *e;
   CSegment *s0, *s1;
 
};

vector<CSegment*> output;  // Array of output segments.

class CSegment 
{
public:
	CSegment(CPoint p): start(p), end(0,0), done(false)
	{
		output.push_back(this);
	}
	   
	// Set the end CPoint and mark as "done."
	void finish(CPoint p)
	{
		if (done) 
			return; 
		end = p; 
		done = true;
	}

	CPoint GetStart() 
	{
		return start;
	}

	CPoint GetEnd() 
	{
		return end;
	}


private:
   CPoint start, end;
   bool done;
};

// "Greater than" comparison, for reverse sorting in priority queue.
struct gt1
{
   bool operator()(CPoint a, CPoint b) 
   {
	   return a.X() == b.X() ? a.Y() > b.Y() : a.X() > b.X();
   }
};

struct gt2
{
   bool operator()(CEvent *a, CEvent *b)
   {
	   return a->GetX() >b->GetX();
   }
};


class Voronoi
{
public:
	void SetPoints();

	vector<CPoint> ComputeVoronoi(priority_queue<CPoint, vector<CPoint>, gt1>);

	// Bounding box coordinates.
	double X0, X1, Y0, Y1;
	//write the constructor__ASK IF RIGHT(Init List)
	Voronoi(): root(NULL), X0(0), X1(0), Y0(0), Y1(0)
	{}

private:
	CArc *root; // First item in the parabolic front linked list.
	priority_queue<CPoint,  vector<CPoint>,  gt1> points; // site events
	priority_queue<CEvent*, vector<CEvent*>, gt2> events; // circle events
	

	void process_point();
	void process_event();
	void front_insert(CPoint  p);

	bool circle(CPoint a, CPoint b, CPoint c, double *x, CPoint *o);
	void check_circle_event(CArc *i, double x0);

	bool intersect(CPoint p, CArc *i, CPoint *result = 0);
	CPoint intersection(CPoint p0, CPoint p1, double l);

	void finish_edges();
	void print_output();
	
};

#endif