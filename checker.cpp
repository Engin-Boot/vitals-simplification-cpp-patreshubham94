#include <assert.h>
#include<iostream>
#include<vector>

using namespace std;

const int bpmUlimit = 150;
const int bpmLlimit = 70;
const int spo2Ulimit = 100;
const int spo2Llimit = 90;
const int respRateUlimit = 95;
const int respRateLlimit = 30;

class Alert {
public :
	virtual void alert(string message) = 0;
};

class AlertWithSMS : public Alert {
public: 
	void alert(string message) override {
		cout << "Send message : "<< message ;
	}
};

class AlertWithSound : public Alert {
public:
	void alert(string message) override {
		cout << "Send alarm : " << message ;
	}
};

class AlertSystem {
	Alert *alertType; //pointer to base class, access with & operator
public:
	void setAlert(Alert *type) {
		alertType = type;
	}

	void SpecificVitalAlert(string message) {
		alertType->alert(message);
	}
};

AlertSystem alrt;

struct vitals {
	string vital_name;
	float Lwr_limit;
	float Upr_limit;
};

//with this we can add new vitals in the list
vector<vitals> vitalList;

void AddVitals(string vitalName, float Lwr_limit, float Upr_limit){
	vitalList.push_back({ vitalName,Lwr_limit,Upr_limit });
}

int findVitalinList(string vitalName) {
	int pos = 0;

	while (vitalList[pos].vital_name != vitalName){
		pos++;
	
	    if(pos >= vitalList.size()){
	        cout << "Invalid vital is entered/Vital is not present" << endl;
	        exit(0);
	    }
	}

	return pos;
}

bool vitalsAreOk(string vitalName, float value) {
	int pos = findVitalinList(vitalName);

	
     if (value < vitalList[pos].Lwr_limit) {
		alrt.SpecificVitalAlert(vitalName);
		cout << " is LOW." << endl;
		return false;
	}

	else if (value > vitalList[pos].Upr_limit) {
		alrt.SpecificVitalAlert(vitalName);
		cout << " is HIGH." << endl;
		return false;
	}

	else {
		cout << "All vitals are Normal" << endl;
		return true;
	}

}

int main() {
	
	AlertWithSMS sms;
	AlertWithSound sound;

	AddVitals("SPO2", spo2Llimit, spo2Ulimit);
	AddVitals("RespRate", respRateLlimit, respRateUlimit);
	AddVitals("BPM", bpmLlimit, bpmUlimit);

	alrt.setAlert(&sound);
    assert(vitalsAreOk("SPO2", 111) == false);
	assert(vitalsAreOk("SPO2", 92) == true);
	assert(vitalsAreOk("SPO2", 99) == true);

	assert(vitalsAreOk("BPM", 60) == false);
	assert(vitalsAreOk("BPM", 167) == false);
	assert(vitalsAreOk("BPM", 87) == true);

	alrt.setAlert(&sms);

	assert(vitalsAreOk("RespRate", 45) == true);
	assert(vitalsAreOk("RespRate", 105) == false);
	assert(vitalsAreOk("RespRate", 68) == true);

	assert(vitalsAreOk("Suger", 68) == true); // Handelling Unknown vital
}
