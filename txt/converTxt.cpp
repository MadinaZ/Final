#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <typeinfo>
using namespace std;

#include <cstring>
#include <ctime>



struct Hotels
{
	char name[30];
	char city[20];
	int star;
	double rate;
	char type1[10];
	char type2[10];
	char type3[10];
	char type4[10];
	char type5[10];
	char type6[10];
	char type7[10];
	double baseprice[7];
	int cap[7];
	int num_rooms[7];

	Hotels();
};

Hotels::Hotels()
:name("")
,city("")
,star(0)
,rate(0)
,type1("")
,type2("")
,type3("")
,type4("")
,type5("")
,type6("")
,type7("")
{}




int main()
{
	srand(time(0));
	ifstream fin;
	fin.open("Hotel.txt");

	ofstream outHotel("newHotel.dat", ios::out | ios::binary);
	ifstream inHotel("newHotel.dat", ios::in | ios::binary);
	ofstream outxtHote;
	ofstream copyHotel;

	outxtHote.open("newHotel.txt");
	copyHotel.open("copydatHotel.txt");

	if(!fin)
	{
		cerr << "fin error";
		exit(EXIT_FAILURE);
	}
	if(!outHotel)
	{
		cerr << "outHotel error";
		exit(EXIT_FAILURE);
	}
	if(!outxtHote)
	{
		cerr << "outxtHote error";
		exit(EXIT_FAILURE);
	}
	if(!copyHotel)
	{
		cerr << "copyHotel error";
		exit(EXIT_FAILURE);
	}



  char *token;
  char buf[1000];
  const char* const tab = "\t";
  int line_counter = 0;
  Hotels hotel;

  while(line_counter < 10)//fin.good())
  {
  	string line;
  	getline(fin, line);
    strcpy(buf, line.c_str());

    if(buf[0] == 0)	continue;

    const string name (token = strtok(buf, tab));
    const string star((token = strtok(0, tab)) ? token : "");
    const string location((token = strtok(0, tab)) ? token : "");
    const string price((token = strtok(0, tab)) ? token : "");
    const string rate((token = strtok(0, tab)) ? token : "");



    int n = 1;//  rand()%2 + 1; // for case 1 or 2 random room info
    string type[7]; // room types
    double baseprices[7];
    int cap[7], num_rooms[7]; // cap = num of people can stay in a room.
    													// num_rooms = num of rooms for each room type
    			// index matches corresponding with room types.


    // hotel price = baseprice * RevPAR

    switch(n)
    {
    	case 1:  type[0] = "typeA"; type[1] = "typeB"; type[2] = "typeC"; type[3] = "typeD";
    					 type[4] = "typeE"; type[5] = "typeF"; type[6] = "typeG";
    					for(int i = 0; i < 7; i++)
    					{
    						baseprices[i] = rand()%200000 / 100.00 + 20;
    						cap[i] = rand()%5 + 1;
    						num_rooms[i] = rand()%200;
    					}
    					break;
    	case 2: type[0] = "King Suite"; type[1] = "King Room"; type[2] = "Queen Suite"; type[3] = "Queen Room";
    					type[4] = "Luxury"; type[5] = "Premium";
    					double k = rand()%1000/100.00 + 1;
    					baseprices[0] = 200*k; baseprices[1] = 150*k; baseprices[2] = 100*k; baseprices[3] = 50*k;
    					baseprices[4] = 30*k; baseprices[5] = 20*k;
    					cap[0] = 6; cap[1] = 4; cap[2] = 4; cap[3] = 2; cap[4] = 2; cap[5] = 2;
    					for(int i = 0; i < 6; i++)
    						num_rooms[i] = rand()%100;
    					break;
    }


    outxtHote.setf(ios::left);
    outxtHote << fixed;

    int n_max = (n == 1 ? 7:6);
    outxtHote << setw(30) << name << setw(20) << location << setw(5) << star << setw(5) << rate;

    if(line_counter == 0)
    	outxtHote << setw(13) << "Roomtype" << setw(9) << "baseprice" << setw(4) << "cap" << setw(5) << "num_rooms" << endl;
    else
    {
    	for(int i = 0; i < n_max; i++)
    	{
    		outxtHote << setw(13) << type[i] << setw(9) << setprecision(2) << baseprices[i] << setw(4) << cap[i] << setw(5) << num_rooms[i];
    	}
    }
    outxtHote << endl;

    ++line_counter;


    // for binary
    strcpy(hotel.name, name.c_str());
    strcpy(hotel.city, location.c_str());
    hotel.star = atoi(star.c_str());
    hotel.rate = atof(rate.c_str());
    strcpy(hotel.type1,type[0].c_str());
    strcpy(hotel.type2,type[1].c_str());
    strcpy(hotel.type3,type[2].c_str());
    strcpy(hotel.type4,type[3].c_str());
    strcpy(hotel.type5,type[4].c_str());
    strcpy(hotel.type6,type[5].c_str());
    strcpy(hotel.type7,type[6].c_str());

    for(int i = 0; i < 7; i++)
    {
    	if(n == 2 && i == 6)
    	{
      	//hotel.type7[0] = '';
      	hotel.baseprice[i] = 0;
      	hotel.cap[i] = 0;
      	hotel.num_rooms[i] = 0;
      	break;
    	}
    	hotel.baseprice[i] = baseprices[i];
    	hotel.cap[i] = cap[i];
    	hotel.num_rooms[i] = num_rooms[i];
    }

    outHotel.seekp((line_counter - 1) * sizeof(Hotels));
    outHotel.write(reinterpret_cast<const char*> (&hotel), sizeof(Hotels));

  }



	int counter =0;
	Hotels hotels;
	inHotel.read(reinterpret_cast <char*>(&hotels), sizeof(Hotels));

	cout << hotels.name;

	while(!inHotel.eof() && inHotel)
	{
		cout << hotels.star << endl;

		inHotel.read(reinterpret_cast<char*>(&hotels), sizeof(Hotels));
		counter++;

	}
	cout<< counter;



	outHotel.close();
	outxtHote.close();
	copyHotel.close();
  return 0;
}


