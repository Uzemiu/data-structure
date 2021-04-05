#pragma once

#include "Plane.h"
#include <queue>

using namespace std;

enum RunwayActivity {idle, land, takeoff};
class Runway {
public:
	Runway(int limit);
	bool can_land(const Plane& current);
	bool can_depart(const Plane& current);
	RunwayActivity activity(int time, Plane& moving);
	void shutdown(int time) const;
	void run_idle(int time) const;
private:
	queue<Plane> landing;
	queue<Plane> takeoff;
	int queue_limit;
	int num_land_requests;
	int num_takeoff_requests;
	int num_landings;
	int num_takeoffs;
	int num_land_accepted;
	int num_takeoff_accepted;
	int num_land_refused;
	int num_takeoff_refused;
	int land_wait;
	int takeoff_wait;
	int idle_time;
};

