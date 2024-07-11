#include <bits/stdc++.h>
#include <Windows.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
using namespace std;

double engine_1, engine_2;
int e1_s, e2_s;//80-> 80%  -20-> -20%
double fuel;
int airspeed, changespeed;
int alt,airalt, calt;
double updown;//10-> +10ï¿½ï¿½ -20-> -20ï¿½ï¿½
double leftright;//10-> L10  -20-> R20 
int airportlength =4000,airportway = -1,groundspeed;
int gear = 1;//1-> gear down  2-> gear up
double needspeed;
int hdg = 0, airporthdg = 0;

int AP1,AP2;

int now_s = 1;
void color(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
int getRand(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}
void init()
{
	printf("Welcome!\nThis version is 1.0.0\n\n");
	printf("Updates:\n");
	printf("¡¤add airport\n");
	printf("¡¤add Autopilot 1\n");
	
	system("pause");
	system("cls");
}
void control()
{
	if(KEY_DOWN('W'))
	{
		updown -= 2;	
	}
	if(KEY_DOWN('S'))
	{
		updown += 2;	
	}
	if(KEY_DOWN('A'))
	{
		leftright -= 1;	
	}
	if(KEY_DOWN('D'))
	{
		leftright += 1;	
	}
	if(KEY_DOWN('G'))
	{
		if(gear == 1)
		{
			gear = 0;
		}
		else
		{
			gear = 1;
		}
	}
	if(KEY_DOWN('1'))
	{
		if(AP1 == 1)
		{
			AP1 = 0;
		}
		else
		{
			AP1 = 1;
		}
	}
	if(KEY_DOWN(' '))
	{
		cout << "Breaks!\n";
		if(airalt <= 8)
		{
			engine_1 = 0;
			engine_2 = 0;
			airspeed -= 1;
		}
		if(airspeed < 0)
		{
			airspeed = 0;
		}
	}
	if(KEY_DOWN('E'))
	{
		if(engine_1 <= 90.0)
		{
			engine_1 += getRand(5, 6);
		}
		if(engine_2 <= 90.0)
		{
			engine_2 += getRand(5, 6);
		}
	}
	if(KEY_DOWN('Q'))
	{
		if(engine_1 >= 10.0)
		{
			engine_1 -= getRand(5, 6);
		}
		if(engine_2 >= 10.0)
		{
			engine_2 -= getRand(5, 6);
		}
	}
	
	if(AP1 == 1 && airalt >= 4 && !KEY_DOWN('A') && !KEY_DOWN('D'))
	{
		if(airportway >= -8000)
		{
			int dg1,dg2;
			dg1 = airporthdg - hdg;
			if(dg1 < 0)
			{
				dg1 += 360; 
			}
			dg2 = hdg - airporthdg;
			if(dg2 < 0)
			{
				dg2 += 360;
			}
			
			if(dg1 <= dg2)
			{
				if(dg1 >= 200)
				{
					if(leftright <= 7)
					{
						leftright++;
					}
					else if(leftright > 8)
					{
						leftright--;
					}
				}
				else if(dg1 >= 80)
				{
					if(leftright <= 5)
					{
						leftright++;
					}
					else if(leftright > 6)
					{
						leftright--;
					}
				}
				else if(dg1 >= 10)
				{
					if(leftright <= 3)
					{
						leftright++;
					}
					else if(leftright > 4)
					{
						leftright--;
					}
				}
				else
				{
					if(leftright <= 0)
					{
						leftright++;
					}
					else if(leftright > 1)
					{
						leftright--;
					}
					
					if(hdg == airporthdg)
					{
						leftright = 0;
					}
				}
			}
			else
			{
				if(dg2 >= 200)
				{
					if(leftright >= -7)
					{
						leftright--;
					}
					else if(leftright < -8)
					{
						leftright++;
					}
				}
				else if(dg2 >= 80)
				{
					if(leftright >= -5)
					{
						leftright--;
					}
					else if(leftright < -6)
					{
						leftright++;
					}
				}
				else if(dg2 >= 10)
				{
					if(leftright >= -3)
					{
						leftright--;
					}
					else if(leftright < -4)
					{
						leftright++;
					}
				}
				else
				{
					if(leftright >= 0)
					{
						leftright--;
					}
					else if(leftright < -1)
					{
						leftright++;
					}
					
					if(hdg == airporthdg)
					{
						leftright = 0;
					}
				}
			}
		}
	}
	else
	{
		if(AP1 == 1)
		{
			AP1 = 0;
			cout << "Autopilot 1 disabled!\n";
		}
	}
}
void change()
{
	airalt = alt - calt;
	groundspeed = airspeed - abs(updown * 0.8) - abs(leftright) * 2;
	airportway -= groundspeed;
	
	hdg += leftright * airspeed * 0.006;
	if(hdg < 0)
	{
		hdg += 360;
	}
	if(hdg > 360)
	{
		hdg -= 360;
	}
	
	if(airportlength <= 0)
	{
		airportlength = getRand(7000, 12000);
		airportway = getRand(20000, 48000);
		airporthdg = getRand(0, 360);
	}
	if(airportway <= 0)
	{
		airportlength -= groundspeed;
	}
	

	changespeed += (engine_1 + engine_2) * 0.646;
	changespeed -= abs(leftright) * 2;
	double l;
	double lsl;
	if(gear == 1)
	{
		lsl = 0.01;
	}
	else
	{
		lsl = 0;
	}
	 
	if(airalt <= 1)
	{
		if(airspeed <= 1)
		{
			l = 1;
		}
		else
		{
			l = 0.7;
		}
	}
	else
	{
		l = 0.75 - lsl;
	}
	needspeed = 100 + updown * 2.5;
	changespeed *= l;
	changespeed -= updown * 0.01 * airspeed;
	
	airspeed = changespeed;
	cout << "\n Airport[*way " << airportway << " *len " << airportlength << "  *hdg " << airporthdg << "] gspeed " << groundspeed << " vspeed " << updown * (airspeed * 0.01) << " AP1_" << AP1 << " AP2_" << AP2 << endl << endl;
	
	alt += updown * (airspeed * 0.01);
	if(airalt < 0)
	{
		alt = calt;
		if(gear == 0 || updown < -4 || updown > 12)
		{
			system("cls");
			printf("You Crash!");
			Sleep(5000);
			exit(0);
		}
	}
	else if(airalt <= 0 && gear == 0)
	{
		system("cls");
		printf("You Crash!");
		Sleep(5000);
		exit(0);
	}
	else if(airalt <= 1 && airportway > 0 || airalt <= 1 && airportlength < 0 || airalt <= 1 && abs(hdg - airporthdg) > 6)
	{
		system("cls");
		printf("Not a airport!");
		Sleep(5000);
		exit(0);
	}
}
void warn()
{
	if(airalt >= 1)
	{
		if(airspeed < (needspeed + 15))
		{
			cout << "!Alpha Stall Portect!\n";
			updown -= 2;
			if((engine_1 + engine_2) < 120 && !KEY_DOWN('Q'))
				{
					engine_1 += 5;
					engine_2 += 5;
				}
			if(airspeed < needspeed)
			{
				cout << "!!Stall!!\n";
				alt -= (needspeed - airspeed) * 2;
				if((engine_1 + engine_2) < 160)
				{
					cout << "TO/GA FLOOR\n";
					engine_1 = 80;
					engine_2 = 80;
				}
			}
		}
	}
	if(airalt <= 200 && gear == 0 && updown < 0)
	{
		cout << "!Dont sink!\n";
		if(updown <= -12 && !KEY_DOWN('W'))
		{
			updown += 2;
		}
		if(airalt <= 80 && updown <= -2)
		{
			cout << "!!!Terrian!!!\n";
			updown += 2;
			if(updown <= -10)
			{
				updown += 2;
			}
		}
		if(airalt <= 120 && abs(hdg - airporthdg) <= 6 && updown <= 0 && gear == 0)
		{
			cout << "Too low, gear";
			gear = 1;
		}
	}
	if(airspeed >= 240)
	{
		cout << "!Overspeed!\n";
		if((engine_1 + engine_2) > 20 && !KEY_DOWN('E'))
		{
			engine_1 -= 5;
			engine_2 -= 5;
		}
	}
	if(airalt + (airspeed * 0.12) > airportway / 20 && airalt >= 6 && airportway > -3000 && updown <= 10)
	{
		cout << "Sink now\n";
		if(updown >= -2 && !KEY_DOWN('S'))
		{
			updown -= 2;
		}
		if(airalt <= 16 && updown <= -4)
		{
			updown += 2;
		}
	}
	
	cout << endl;
}
int main()
{
	init();
	Sleep(1000);
	
	alt = getRand(0, 300);
	calt = alt - airalt;
	airportlength = getRand(7000, 12000);
	
	while(now_s)
	{
		control();
		change();
		printf("  ALT       AirALT     Speed     HDG\n");

		printf(" %d        %d         %d        %d\n\n", alt, airalt, airspeed,hdg);
		printf(" UpDown      LeftRight\n");
		printf("  %d             %d\n\n", int(updown), int(leftright));
		printf("  E1            E2\n");
		printf("  %d            %d\n\n", int(engine_1), int(engine_2));
		printf(" Gear %d\n", gear);
		warn();
		Sleep(500);
	}
	
	
	return 0;
}
