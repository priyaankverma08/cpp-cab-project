// C++ Fun
#include <bits/stdc++.h>
using namespace std;

// Latitude of customer who needs a cab.
#define lat1d 12.9611159

// Longitude of customer who needs a cab.
#define lon1d 77.6362214

#define pi 3.14159265358979323846
#define earth_radius 6371.0

ifstream customer_list ("customers.json");
ofstream out ("answer.json");

//Converting degree to radian.
double degtorad(double deg)
{
	return ( deg * pi / 180);
}


// using Great Circle Distance Formula.
double distanceEarth(double lat2d, double lon2d)
{
	double lat1, lon1, lat2, lon2,
		delta_lon, central_ang;

	lat1 = degtorad(lat1d);
	lon1 = degtorad(lon1d);
	lat2 = degtorad(lat2d);
	lon2 = degtorad(lon2d);

	delta_lon = lon2 - lon1;

	// great circle distance formula.
	central_ang = acos ( sin(lat1) *
				sin(lat2) + cos(lat1) *
				cos(lat2) * cos(delta_lon) );

	return (earth_radius * central_ang);
}

// Structure which contains data and
// functions for accessing and processing
// data from the given customers.json file.
struct json
{
	/* i and j are used to access various
	elements of the char arrays. x is used
	to measure the size of the element of
	latitude_as_string array. y is used to
	measure the size of the element of
	longitude_as_string array. m is used
	to measure the size of the element
	of id_as_string array. n is used to
	measure the size of the element of
	name array. f keeps count of " " "
	symbol. fi keeps count of " : " symbol.
	*/
	long long int length, i, j, x, y, m,
				n, f, fi, id[100000];

	char latitude_as_string[1000],
		longitude_as_string[1000],
		id_as_string[1000], name[1000];

	double lat2d, lon2d;

	// To get each line of customers.json
	
	string line;

	
	void distance_calculator()
	{
		if (distanceEarth(lat2d, lon2d) <= 50.0000)
		{
			// Converting id to int format.
			id[i] = atoll(id_as_string);
			i++;
			out << "{\"user_id\": " << id[i - 1] <<
				", \"name\": " << name << "}" << endl;
		}
	}


	void json_parser()
	{
		if (customer_list.is_open())
		{

			while (getline(customer_list, line))
			{

				f = 0; x = 0; y = 0; fi = 0; m = 0, n = 0;
				length = line.size();

				for (j = 0; j < length; j++)
				{

					if (line[j] == '"')
						f++;

					else if (line[j] == ':')
						fi++;

					// To get latitude of the location.
					if (f == 3)
					{
						j++;

						while (line[j] != '"')
						{
							latitude_as_string[x] = line[j];
							x++; j++;
						}

						j--; latitude_as_string[x] = '\0';
					}

					// To get longitude of the location.
					else if (f == 13)
					{
						j++;

						while (line[j] != '"')
						{
							longitude_as_string[y] = line[j];
							y++; j++;
						}

						j--; longitude_as_string[y] = '\0';
					}

					
					if (fi == 2)
					{
						j += 2;

						while (line[j] != ',')
						{
							id_as_string[m] = line[j];
							m++; j++;
						}

						j--; id_as_string[m] = '\0';
						fi++;
					}

					
					else if (fi == 4)
					{
						j += 2;

						while (line[j] != ',')
						{
							name[n] = line[j];
							n++; j++;
						}

						j--; name[n] = '\0';
						fi++; f += 2;
					}
				}

				
				lat2d = atof(latitude_as_string);
				lon2d = atof(longitude_as_string);
				distance_calculator();
			}
		}

		
		customer_list.close();

		out.close();
	}
};

int main()
{
	// Creating object of the structure json
	json obj;

	// To read customers.json file.
	obj.json_parser();
	return 0;
}