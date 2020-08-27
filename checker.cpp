#include <assert.h>

const int bpmlimit[] = { 70,150 };
const int spo2limit = 90;
const int respRatelimit[] = { 30, 95 };

bool isbpmok(float bpm) {
	return (bpm > bpmlimit[0] && bpm < bpmlimit[1]);
}

bool isSpo2ok(bool spo2) {
	return (spo2 < spo2limit);
}

bool isResprateok(float respRate) {
	return ((respRate > respRatelimit[0]) && (respRate < respRatelimit[1]));
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
	return (isbpmok(bpm) && isSpo2ok(spo2) && isResprateok(respRate));

}

int main() {
	assert(vitalsAreOk(80, 95, 60) == true);
	assert(vitalsAreOk(60, 90, 40) == false);
}
