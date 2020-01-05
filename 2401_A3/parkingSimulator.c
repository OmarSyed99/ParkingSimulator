#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
  int hour;
  int minute;
} Time;


typedef struct{
  char *plateNumber;
  char permit;
  Time enteringTime;
  int lotParkedln;
} Car;



typedef struct{
  int lotNumber;
  double hourlyRate;
  double maxCharge;
  int capacity;
  int currentCarCount;
  double revenue;
} ParkingLot;


void setHours(Time *t, double h);
void difference(Time t1, Time t2, Time *diff);
void initializeCar(Car *c, char *plate, char hasPermit);
void initializeLot(ParkingLot *p, int num, int cap, double rate, double max);
void printLotInfo(ParkingLot p);
void carEnters(ParkingLot *p, Car *c, int hour, int minute);
void carLeaves(ParkingLot *p, Car *c, int hour, int minute);

int main() {

 Car car1, car2, car3, car4, car5, car6, car7, car8, car9;
 ParkingLot p1, p2;
 // Set up 9 cars
 initializeCar(&car1, "ABC 123", 0);
 initializeCar(&car2, "ABC 124", 0);
 initializeCar(&car3, "ABD 314", 0);
 initializeCar(&car4, "ADE 901", 0);
 initializeCar(&car5, "AFR 304", 0);
 initializeCar(&car6, "AGD 888", 0);
 initializeCar(&car7, "AAA 111", 0);
 initializeCar(&car8, "ABB 001", 0);
 initializeCar(&car9, "XYZ 678", 1);
 // Set up two parking lots
 initializeLot(&p1, 1, 4, 5.5, 20.0);
 initializeLot(&p2, 2, 6, 3.0, 12.0);
 printLotInfo(p1);
 printLotInfo(p2);
 printf("\n");
 // Simulate cars entering the lots
 carEnters(&p1, &car1, 7, 15);
 carEnters(&p1, &car2, 7, 25);
 carEnters(&p2, &car3, 8, 0);
 carEnters(&p2, &car4, 8, 10);
 carEnters(&p1, &car5, 8, 15);
 carEnters(&p1, &car6, 8, 20);
 carEnters(&p1, &car7, 8, 30);
 carEnters(&p2, &car7, 8, 32);
 carEnters(&p2, &car8, 8, 50);
 carEnters(&p2, &car9, 8, 55);
 printf("\n");
 printLotInfo(p1);
 printLotInfo(p2);
 printf("\n");
 // Simulate cars leaving the lots
 carLeaves(&p2, &car4, 9, 0);
 carLeaves(&p1, &car2, 9, 5);
 carLeaves(&p1, &car6, 10, 0);
 carLeaves(&p1, &car1, 10, 30);
 carLeaves(&p2, &car8, 13, 0);
 carLeaves(&p2, &car9, 15, 15);
 carEnters(&p1, &car8, 17, 10);
 carLeaves(&p1, &car5, 17, 50);
 carLeaves(&p2, &car7, 18, 0);
 carLeaves(&p2, &car3, 18, 15);
 carLeaves(&p1, &car8, 20, 55);
 printf("\n");
 printLotInfo(p1);
 printLotInfo(p2);
 printf("\n");
 // Display the total revenue
 printf("Total revenue of Lot 1 is $%4.2f\n", p1.revenue);
 printf("Total revenue of Lot 2 is $%4.2f\n", p2.revenue);


 return 0;

}
//-------------------------------------------------------------------------------------
// Sets the hours and minutes amount for the given time t based
// on the specified hours h. (e.g., 1.25 hours would be 1 hour
// and 15 minutes)
void setHours(Time *t, double h) {
  double p = t->minute;
  p = ((p/60) * 100)/100;
  h = t->hour + p;
}
// Takes two Time objects (not pointers) and computes the difference
// in time from t1 to t2 and then stores that difference in the diff
// Time (which must be a pointer)
void difference(Time t1, Time t2, Time *diff) {
  double time1 = t1.hour + (((float)t1.minute/60) * 100)/100;
  //setHours(&t1, &time1);
  double time2 = t2.hour + (((float)t2.minute/60) * 100)/100;
  //setHours(&t2,time2);
  double deltaHr = floor(fabs(time2-time1));
  double deltaMin = fabs(deltaHr - fabs(time2-time1));

  diff->hour = deltaHr;
  diff->minute = deltaMin * 60;
 //printf("time1: %f  time2: %f  deltaHr: %f  deltaMin: %f  diffHr: %d  diffMinL %d\n", time1, time2, deltaHr, deltaMin, diff->hour, diff->minute);
  //diff->hour = abs(t1.hour - t2.hour);
//  diff->minute = abs(t1.minute - t2.minute);

}
// Initialize the car pointed to by c to have the given plate and
// hasPermit status. The car should have it’s lotParkedIn set to
// 0 and enteringTime to be -1 hours and -1 minutes.
void initializeCar(Car *c, char *plate, char hasPermit) {
  c->plateNumber = plate;
  c->permit = hasPermit;
  c->lotParkedln = 0;
  c->enteringTime.hour = -1;
  c->enteringTime.minute = -1;
}
// Initialize the lot pointed to by p to have the given number,
// capacity, hourly rate and max charge values. The currentCarCount
// and revenue should be at 0.
void initializeLot(ParkingLot *p, int num, int cap, double rate, double max) {
  p->lotNumber = num;
  p->capacity = cap;
  p->hourlyRate = rate;
  p->maxCharge = max;
  p->currentCarCount = 0;
  p->revenue = 0;
}


// Print out the parking lot parameters so that is displays as
// follows:
// Parking Lot #2 - rate = $3.00, capacity  6, current cars 5
void printLotInfo(ParkingLot p) {
  printf("Parking Lot #%d - rate = $%0.2f, capacity %d, current cars %d\n", p.lotNumber, p.hourlyRate, p.capacity, p.currentCarCount );

}

void carEnters(ParkingLot *p, Car *c, int hour, int minute){
  c->enteringTime.hour = hour;
  c->enteringTime.minute = minute;

  if(p->currentCarCount>=p->capacity){
    printf("Car %s arrives at Lot %d at %d:%d, but the lot is full.\n",c->plateNumber, p->lotNumber, c->enteringTime.hour, c->enteringTime.minute);
    printf("Car %s cannot get in.\n",c->plateNumber);
  }else{
    p->currentCarCount++;
    printf("Car %s enters Lot %d at %d:%d.\n",c->plateNumber, p->lotNumber, c->enteringTime.hour, c->enteringTime.minute);
    c->lotParkedln = p->lotNumber;

  }
}



void carLeaves(ParkingLot *p, Car *c, int hour, int minute){
  Time deltaT;
  Time leaving;
  double cost;
  double times;
  leaving.hour = hour;
  leaving.minute = minute;
  difference(leaving,c->enteringTime, &deltaT);
  times = ceil(deltaT.hour + ((float)deltaT.minute/100));

  cost = times * p->hourlyRate;
  if(cost >= p->maxCharge){
    cost = p->maxCharge;
  }

  if(c->permit == 1){
    cost = 0;
    printf("Car %s leaves Lot %d at %d:%2d .\n",c->plateNumber, p->lotNumber, hour, minute);
  }else{
    printf("Car %s leaves Lot %d at %d:%2d paid $%0.2f.\n",c->plateNumber, p->lotNumber, hour, minute, cost);
  }

  p->currentCarCount--;
  p->revenue +=  cost;

}
