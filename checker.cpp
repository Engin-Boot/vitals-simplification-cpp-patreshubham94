#include <assert.h>

const int bpmUlimit = 150;
const int bpmLlimit = 70;
const int spo2Ulimit = 100;
const int spo2Llimit = 90;
const int respRateUlimit = 95;
const int respRateLlimit = 30;

bool vitalsOk(float value, float upper_limit, float lower_limit) {
	return (value >= lower_limit && value <= upper_limit);
}

int main() {
	assert(vitalsOk(80, respRateUlimit, respRateLlimit) == true);
	assert(vitalsOk(60, spo2Ulimit, spo2Llimit) == false);
	assert(vitalsOk(120, bpmUlimit, bpmLlimit) == true);
	assert(vitalsOk(95, spo2Ulimit, spo2Llimit) == true);
}
