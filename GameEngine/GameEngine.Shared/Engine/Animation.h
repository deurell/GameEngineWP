/*!
 * \file Animation.h
 *
 * \author deurell
 * \date March 2015
 *
 * Struct to provide simple animation
 */
#pragma once
#include "Engine/Quaternion.h"

struct Animation {
	Quaternion Start;
	Quaternion End;
	Quaternion Current;
	float Elapsed;
	float Duration;
};