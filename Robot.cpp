#include "Robot.h"
#include <stdexcept>

Robot::Robot(char* ip, int port) {

	_pc = new PlayerClient(ip, port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);

	//For fixing Player's reading BUG
	for (int i = 0; i < 15; i++)
		Read();
}

double Robot::getXPosition() {
	return _pp->GetXPos();
}

double Robot::getYPosition() {
	return _pp->GetYPos();
}

double Robot::getYawPosition() {
	return _pp->GetYaw();
}

bool Robot::canTurnRight()
{
	return canTurnInDirection(START_RIGHT_RAYS_RANGE_ANGLE, END_RIGHT_RAYS_RANGE_ANGLE);
}

bool Robot::canTurnLeft()
{
	return canTurnInDirection(START_LEFT_RAYS_RANGE_ANGLE, END_LEFT_RAYS_RANGE_ANGLE);
}

bool Robot::canTurnInDirection(double startRangeAngle, double endRangeAngle)
{
	int rangeStartIndex = angleToIndex(startRangeAngle);
	int rangeEndIndex = angleToIndex(endRangeAngle);

	for (int i = rangeStartIndex; i < rangeEndIndex; i++)
	{
		if (getDistanceFromObstacle(i) <= 0.5)
		{
			return false;
		}
	}

	return true;
}

bool Robot::canMoveForward()
{
	//todo this
	return true;
}



// This function summarize the "rays range" distances from obstacles
double Robot::getRaysRangeSum(double rangeStartAngle,double rangeEndAngle)
{
	double sum = 0;

	int rangeStartIndex = angleToIndex(rangeStartAngle);
	int rangeEndIndex = angleToIndex(rangeEndAngle);

	for (int i = rangeStartIndex; i <= rangeEndIndex; i++)
	{
		sum += getDistanceFromObstacle(i);
	}

	return sum;
}

double Robot::getRangeLaser(unsigned index) {
	if (index < 0 || index > LASER_SLEASER_ARRAY_SIZE) {
		return -1;
	}
	return _lp->GetRange(index);;
}

double Robot::getRangeLaser(double angle) {
	return getRangeLaser(angleToIndex(angle));
}

double Robot::indexToAngle(int index) {
	double angular_resolution = LASER_FOV_DEGREE
			/ (double) LASER_SLEASER_ARRAY_SIZE;
	double min_angle = LASER_FOV_DEGREE / 2;

	double angle = index * angular_resolution - min_angle;
	return angle;
}

unsigned Robot::angleToIndex(double angle) {
	double min_angle = LASER_FOV_DEGREE / 2;

	int index = ((double) LASER_SLEASER_ARRAY_SIZE / LASER_FOV_DEGREE)
			* (angle + min_angle);
	if (index >= LASER_SLEASER_ARRAY_SIZE) {
		throw new out_of_range("index larger than possible.");
	}

	return index;
}

double Robot::getDistanceFromObstacle(int index) {
	return (*_lp)[index];
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
