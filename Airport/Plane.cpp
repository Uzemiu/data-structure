#include "Plane.h"
#include <iostream>
using namespace std;

Plane::Plane() {
	flt_num = -1;
	clock_start = -1;
	state = null;
}

Plane::Plane(int flt, int time, PlaneStatus status) {
	flt_num = flt;
	clock_start = time;
	state = status;
	cout << "[Plane: " << flt << "]: ready to "
	     << (status == arriving ? "land." : "take off.") << endl;
}

void Plane::refuse() const {
	cout << "[Plane: " << flt_num << "]: "
		<< (state == arriving 
			? "directed to another airport" 
			: "told to try to takeoff again later") << endl;
}

void Plane::land(int time) const {
	int wait = time - clock_start;
	cout << "[Time: " << time << "]: Plane number " << flt_num << " landed after " << wait
		<< " time unit" << (wait == 1 ? "" : "s") << " in the landing queue." << endl;
}

void Plane::fly(int time) const {
	int wait = time - clock_start;
	cout << "[Time: " << time << "]: Plane number " << flt_num << " took off after " << wait
		<< " time unit" << (wait == 1 ? "" : "s") << " in the takeoff queue." << endl;
}

int Plane::started() const {
	return clock_start;
}
