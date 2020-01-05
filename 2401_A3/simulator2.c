#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

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
char* randomPlate();
Car* randomCar();
double timeToDec(Time *t);


int main() {
  srand(time(NULL));
  Car* vehicle;
  ParkingLot* lots;
  Time setTime;
  setTime.hour = 6;
  setTime.minute = 00;
  int carSize = 50;
  int lotSize = 5;

  vehicle = malloc(carSize * sizeof(Car));
  lots = malloc(lotSize * sizeof(ParkingLot));


  initializeLot(&lots[0], 1, 5, 4, 12);
  initializeLot(&lots[1], 2, 10, 5, 14);
  initializeLot(&lots[2], 3, 15, 6, 16);
  initializeLot(&lots[3], 4, 20, 7, 18);
  initializeLot(&lots[4], 5, 25, 8, 20);

//generate random car
  for(int i=0; i<50; i++){
    Car *newCar = randomCar();

    vehicle[i] = *newCar;

    printf("Car %s with permit %d\n", vehicle[i].plateNumber,vehicle[i].permit);
    //free(vehicle[i].plateNumber);
    free(newCar);
    //free(plate);
  }
  printf("\n");

//print lot infor
  for(int i=0; i<5; i++){
    printLotInfo(lots[i]);
  }
  printf("\n");

//car enter
  for(int i=0; i<carSize; i++){
    carEnters(&lots[rand()%5], &vehicle[i], setTime.hour, setTime.minute);
    float temp = timeToDec(&setTime) + (0.0834);
    setHours(&setTime,temp);
  }
  printf("\n");

//print lot info
  for(int i=0; i<lotSize; i++){
    printLotInfo(lots[i]);
  }
  printf("\n");

  //set leaving time to 11:00
  setTime.hour = 11;
  setTime.minute = 00;
  for(int i=0; i<carSize; i++){
    if(vehicle[i].lotParkedln != 0){
      for(int j=0; j<lotSize; j++){
        if(vehicle[i].lotParkedln == lots[j].lotNumber){
          carLeaves(&lots[j], &vehicle[i], setTime.hour, setTime.minute);
          float temp = timeToDec(&setTime) + (0.0834);
          setHours(&setTime,temp);
        }
      }
    }
  }
  printf("\n");

//print each parking lots revenue
  for(int i =0; i<lotSize; i++){
    printf("Total revenue of Lot %d is $%4.2f\n",lots[i].lotNumber, lots[i].revenue);
  }


//free all the plate number refrence spots
  for(int i =0; i<50; i++){
    free(vehicle[i].plateNumber);
  }

free(vehicle);
free(lots);

 return 0;

}
//-------------------------------------------------------------------------------------
// Sets the hours and minutes amount for the given time t based
// on the specified hours h. (e.g., 1.25 hours would be 1 hour
// and 15 minutes)
void setHours(Time *t, double h) {
  double hr = floor(h);
  double min = h - hr;
  t->hour = hr;
  t->minute = ((float)min)*60;
  //printf("-----------------------------------------------%d:%d\n",t->hour, t->minute );
}

double timeToDec(Time *t){
  float convMin = (((float)t->minute/60)*100)/100;
  float decTime = t->hour + convMin;
  return decTime;
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
    printf("Car %s arrives at Lot %d at %d:%02d, but the lot is full.\n",c->plateNumber, p->lotNumber, c->enteringTime.hour, c->enteringTime.minute);
    printf("Car %s cannot get in.\n",c->plateNumber);
  }else{
    p->currentCarCount++;
    printf("Car %s enters Lot %d at %d:%02d.\n",c->plateNumber, p->lotNumber, c->enteringTime.hour, c->enteringTime.minute);
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
  printf("Car %s leaves Lot %d at %d:%02d.\n",c->plateNumber, p->lotNumber, hour, minute);
}else{
  printf("Car %s leaves Lot %d at %d:%02d paid $%0.2f.\n",c->plateNumber, p->lotNumber, hour, minute, cost);
}

  //printf("Car %s leaves Lot %d at %d:%2d paid $%0.2f. diffT%d:%d   times %0.2f\n",c->plateNumber, p->lotNumber, hour, minute, cost, deltaT.hour, deltaT.minute, times);
  p->currentCarCount--;
  p->revenue +=  cost;

}

char* randomPlate(){



  char a[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char b[10] ="0123456789";
  char* e;
  int size = 7;
  int counter = 0;
  e = malloc(size * sizeof(char));

  for(int i =0; i< 7;i++){
    if(counter<=2){
      e[i] = a[rand()%26];
    }else if(counter == 3){
      e[i] = ' ';
    }else{
      e[i] = b[rand()%10];
    }
    counter++;
  }

  return e;
}

Car* randomCar(){
  //srand(time(NULL));
  int randPermit = rand()%2;
  Car* car;
  car = malloc(sizeof(Car));

  initializeCar(car, randomPlate(), randPermit);
  return car;
}
