#include <assert.h>

const int bpmUlimit = 150;
const int bpmLlimit = 70;
const int spo2Ulimit = 100;
const int spo2Llimit = 90;
const int respRateUlimit = 95;
const int respRateLlimit = 30;

bool vitalisOk(float value, float upper_limit, float lower_limit) {
	return (value >= lower_limit && value <= upper_limit);
}
bool vitalsAreOk(float bpm, float spo2, float respRate) {
	return (vitalisOk(bpm,bpmUlimit,bpmLlimit) && vitalisOk(spo2, spo2Ulimit,spo2Llimit) && vitalisOk(respRate,respRateUlimit, respRateLlimit ) );
}


int main() {
	assert(vitalsAreOk(80, 95, 40) == true);
	assert(vitalsAreOk(60, 60, 65) == false);
	assert(vitalsAreOk(120, 92, 70) == true);
	assert(vitalsAreOk(95, 98, 85) == true);
}
