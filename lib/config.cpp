#include "config.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Decleration {
	string name;
	string value;
};

#include <tr1/regex>
#include <regex.h>
#include "log.h"

vector<Decleration> readLines(string fileName) {
	vector<Decleration> lines;
	ifstream fileStream(fileName.c_str());
	if (!fileStream) {
		cout << "WAT";
		return lines;
	}
	string line;
	while (getline(fileStream, line)) {
		Decleration lineDec;
		int colon = line.find(':');
		lineDec.name = line.substr(0, colon);
		lineDec.value = line.substr(colon + 2, line.length() - colon - 3);
		lines.push_back(lineDec);
	}
	return lines;
}

void parseGoal(Config* config, string value) {
	int space = value.find(' ');
	unsigned x = atoi(value.substr(0, space).c_str());
	unsigned y = atoi(value.substr(space+1).c_str());
	config->goal[0] = x;
	config->goal[1] = y;
}

void parseStartLocation(Config* config, string value) {
	int firstSpace = value.find(' ');
	int secondSpace = value.substr(firstSpace+1).find(' ') + firstSpace + 1;
	unsigned x = atoi(value.substr(0, firstSpace).c_str());
	unsigned y = atoi(value.substr(firstSpace+1, secondSpace).c_str());
	unsigned yaw = atoi(value.substr(secondSpace+1).c_str());
	config->startLocation[0] = x;
	config->startLocation[1] = y;
	config->startLocation[2] = yaw;
}

void parseRobotSize(Config* config, string value) {
	int space = value.find(' ');
	unsigned width = atoi(value.substr(0, space).c_str());
	unsigned height = atoi(value.substr(space+1).c_str());
	config->robotSize[0] = width;
	config->robotSize[1] = height;
}

void Config::parse(string fileName) {
	vector<Decleration> decs = readLines(fileName);

	// OMFG its ugly
	for (Decleration dec : decs) {
		if (!dec.name.compare("goal")) {
			parseGoal(this, dec.value);
		} else if (!dec.name.compare("map")) {
			this->mapLocation = dec.value;
		} else if (!dec.name.compare("startLocation")) {
			parseStartLocation(this, dec.value);
		} else if (!dec.name.compare("robotSize")) {
			parseRobotSize(this, dec.value);
		} else if (!dec.name.compare("MapResolutionCM")) {
			this->mapResolutionCm = atof(dec.value.c_str());
		} else if (!dec.name.compare("GridResolutionCM")) {
			this->gridResolutionCm = atof(dec.value.c_str());
		}
	}
}

ostream& operator<<(ostream& os, const Config& config) {
	os << "map location: "   << config.mapLocation << endl
	   << "start location: " << config.startLocation[0] << " "
							 << config.startLocation[1] << " "
							 << config.startLocation[2] << endl
	   << "goal: " 	     	 << config.goal[0] << " " << config.goal[1] << endl
	   << "robot size: "     << config.robotSize[0] << " " << config.robotSize[1] << endl
	   << "map res: "        << config.mapResolutionCm << endl
	   << "grid res: "       << config.gridResolutionCm << endl;
	return os;
}

Config::Config(string fileName) {
	this->mapLocation = string("");
	this->startLocation = new int[3];
	this->goal = new int[2];
	this->robotSize = new int[2];
	this->mapResolutionCm = 1.0;
	this->gridResolutionCm = 1.0;
	this->parse(fileName);
}

Config::~Config() {
	delete[] this->goal;
	delete[] this->startLocation;
	delete[] this->robotSize;
}
