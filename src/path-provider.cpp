#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
Path class constructs two arrays: pathAllCoords_X and pathAllCoords_Y
that are representing path that is taken by interpolating lines if path is not curved,
or are calculated from calculating polinomial interpolation for smallest logical vector step
between given crossing points in checkPointCoordinatesX and checkPointCoordinatesY.
This path calculates crossing points from velocity of traveling tag between given crossing
points.
*/

class Path
{
public:
	Path(vector<int> &CoordinatesX, vector<int> &CoordinatesY, bool isClosed, bool isCurved, int&anchors)
	{
		checkPointCoordinatesX = CoordinatesX;
		checkPointCoordinatesY = CoordinatesY;
		isClosed = isClosed;
		isCurved = isCurved;
		anchorsPtr = &anchors;
		closingPathSetter(isClosed, checkPointCoordinatesX, checkPointCoordinatesY);
		calculatePath(isCurved, pathAllCoords_X, pathAllCoords_Y);
		printAllCrossingPoints(pathAllCoords_X, pathAllCoords_Y);
		calculateDistancesForEachAnchor(pathAllCoords_X, pathAllCoords_Y, *anchorsPtr, distancesAnchor_Tag[10]);
	}

	void calculateDistancesForEachAnchor(vector<int> &allCoords_X, vector<int> &allCoords_Y, int&anchorsPtr, vector<int> &distancesAnchor_Tag)
	{
		// todo: calculation of distances will happend here...
	}

private:
	int *anchorsPtr;
	vector<int> checkPointCoordinatesX, checkPointCoordinatesY, pathAllCoords_X, pathAllCoords_Y;
	/*
	distancesAnchor_Tag[10]
	array of vectors to hold distances between maximum 10 anchors and given tag
	*/
	vector<int> distancesAnchor_Tag[10];
	static bool isClosed, isCurved;

	void closingPathSetter(bool closed, vector<int> &checkPointsX, vector<int> &checkPointsY)
	{
		if(closed)
		{
			checkPointsX.push_back(checkPointsX[0]);
			checkPointsY.push_back(checkPointsY[0]);
		}
		else
		{
			int index = checkPointsX.size();
			while(index > 0)
			{
				index--;
				checkPointsX.push_back(checkPointsX[index]);
				checkPointsY.push_back(checkPointsY[index]);
			}
		}
	}

	// this function callculates vector containing path coordinates
	void calculatePath(bool curved, vector<int> &allCoords_X, vector<int> &allCoords_Y)
	{
		int vector_X, vector_Y, step;
		double sectorVector, stepVector_X, stepVector_Y, increment_X, increment_Y;

		if(curved)
		{
			for(int i = 0; i < checkPointCoordinatesX.size() -1; i++)
			{
				/*
				polinomial interpolation method will not work when applied straight away,
				becouse curvature is rarely symetric according to X or Y axis
				and coordinates system needs to be rotated, so better approuch is to
				use quantified vector method, what will be coded soon...
				*/
				cout << "Check point curved X: " << checkPointCoordinatesX[i] << endl;
				cout << "Check point curved Y: " << checkPointCoordinatesY[i] << endl;
			}
		}
		else
		{
			for(int i = 0; i < checkPointCoordinatesX.size() - 1; i++)
			{
				vector_X = checkPointCoordinatesX[i+1] - checkPointCoordinatesX[i];
				vector_Y = checkPointCoordinatesY[i+1] - checkPointCoordinatesY[i];
				sectorVector = sqrt(pow(vector_X, 2) + pow(vector_Y, 2));
				stepVector_X = vector_X / sectorVector;
				stepVector_Y = vector_Y / sectorVector;
				increment_X = 0;
				increment_Y = 0;
				step = 0;
				while(step < sectorVector - 1)
				{
					increment_X += stepVector_X;
					increment_Y += stepVector_Y;
					allCoords_X.push_back(lround(checkPointCoordinatesX[i] + increment_X));
					allCoords_Y.push_back(lround(checkPointCoordinatesY[i] + increment_Y));
					step++;
				}
			}
			cout << "Path has " << pathAllCoords_Y.size() << " points." << endl;
		}
	}

	/*
	todo: remove printAllCrossingPoints() after emulator will be fully finished
	printAllCrossingPoints() is only to check coordinates values durring emitter construction
	*/
	void printAllCrossingPoints(vector<int> &x_es, vector<int> &y_es)
	{
		int counter = 0;
		while(counter < x_es.size())
		{
			cout << "X: " << x_es[counter] << ", Y: " << y_es[counter] << endl;
			counter++;
		}
	}
};
