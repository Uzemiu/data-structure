#pragma once
enum PlaneStatus {null, arriving, departing};

class Plane {
public:
	Plane();
	Plane(int flt, int time, PlaneStatus status);
	void refuse() const;
	void land(int time) const;
	void fly(int time) const;
	int started() const;
private:
	int flt_num;
	int clock_start;
	PlaneStatus state;
};

