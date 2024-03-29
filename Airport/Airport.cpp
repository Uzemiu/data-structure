﻿#include <iostream>
#include "Random.h"
#include "Runway.h"

using namespace std;

void initialize(int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate) {
	cout << "Initializing..." << endl;
	cout << "Up to what number of planes can be waiting to land "
		 << "or take off at any time?" << flush;
	cin >> queue_limit;
	cout << "How many units of time will the simulation run?" << flush;
	cin >> end_time;
	bool acceptable = false;
	do{
		cout << "Expected number of arrivals per unit time?" << flush;
		cin >> arrival_rate;
		cout << "Expected number of departures per unit time?" << flush;
		cin >> departure_rate;
		if (arrival_rate < 0.0 || departure_rate < 0.0){
			cerr << "Negative rate!" << endl;
		} else {
			acceptable = true;
		}
		if (acceptable && arrival_rate + departure_rate > 1.0) {
			cerr << "Safety Wawrning:" << endl;
		}
	} while (!acceptable);
	
}

void test_airport() {
	int end_time;
	int queue_limit;
	int flight_number = 0;
	double arrival_rate, departure_rate;
	initialize(end_time, queue_limit, arrival_rate, departure_rate);
	Random variable;
	Runway small_airport(queue_limit);
	for (int current_time = 0; current_time < end_time; current_time++) {
		// landing
		int number_arrivals = variable.poisson(arrival_rate);
		for (int i = 0; i < number_arrivals; i++) {
			Plane current_plane(flight_number++, current_time, arriving);
			if (!small_airport.can_land(current_plane)) {
				current_plane.refuse();
			}
		}
		// departing
		int number_departures = variable.poisson(departure_rate);
		for (int i = 0; i < number_departures; i++) {
			Plane current_plane(flight_number++, current_time, departing);
			if (!small_airport.can_depart(current_plane)) {
				current_plane.refuse();
			}
		}

		Plane moving_plane;
		switch (small_airport.activity(current_time, moving_plane)) {
		case land:
			moving_plane.land(current_time);
			break;
		case takeoff:
			moving_plane.fly(current_time);
			break;
		case idle:
			small_airport.run_idle(current_time);
			break;
		}
	}
	small_airport.shutdown(end_time);
}

int main(){
	test_airport();
	system("pause");
}
