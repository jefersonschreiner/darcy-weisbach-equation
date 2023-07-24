#include <iostream>
#include <math.h>
using namespace std;

//Global Constant
#define G2 19.62 /*Gravity x2 */
#define G 9.81 /*Gravity*/
#define Pi 3.14 /*Pi*/

//Global Variables
float f;/*Friction Factor (TEMPORARY)*/
float v = 0.000001; /*Kinematic Viscosity (TEMPORARY)*/
float q = 0.0; /*Flow Rate*/

//Function Type 01/02/03 
float Contas(float hp, int Type) {

	//General Functions Variables
	float d;
	float kr;
	float area = 0.0;
	float ures = 0.0;
	float length = 0.0;
	float aux1;
	float aux2;

	//General Function Input
	cout << "Enter the Length(in meters - m): ";
	cin >> length;

	cout << "Enter the Relative Roughness (in millimeters - mm): ";
	cin >> kr;
	kr /= 1000;

	cout << "Enter the Friction Factor: "; /*Temporary*/
	cin >> f;

	//Calculation Type 01
	if (Type == 1) {

		//Variables Type 01
		float hl = 0.0; /*Localized Load Loss*/
		float ecoef; /*Sum of Localized Loss Coefficients*/

		//Input Type 01
		cout << "Enter the flow rate(in liters per second - l/s): ";
		cin >> q;
		q /= 1000;

		cout << "Enter the diameter(in centimeters - cm): ";
		cin >> d;
		d /= 100;

		//Area Calculation (Round Pipe)
		area = (pow(d, 2) * Pi) / 4;

		//Velocity Calculation
		ures = q / area;

		//System Loss Calculation
		aux1 = (pow(ures, 2) / G2);
		aux2 = (length / d);
		hp = f * aux1 * aux2;

		//Localizated Loss Calculation
		int tlocal = 0;
		cout << "Calculate Localized Loss? (1-yes): ";
		cin >> tlocal;

		if (tlocal == 1) {
			cout << "Sum of Localized Loss Coefficient: ";
			cin >> ecoef;

			hl = ecoef * aux1;
			return (hp += hl);
		}

		else return hp;
	}

	//Calculation Type 02
	else if (Type == 2) {

		//Variables Type 02
		float kd;
		float ref12 = 0;

		//Input Type 02
		cout << "Enter the diameter (in centimeters - cm): ";
		cin >> d;

		//Conversions
		kd = kr / d; /*Temporary*/
		d /= 100;

		//Area Calculation (Round Pipe)
		area = (pow(d, 2) * Pi) / 4;

		//Estimate Ref1/2 (TEMPORARY)
		aux1 = (pow(d, 1.5) / v); 
		aux2 = ((G2 * hp) / length);
		ref12 = aux1 * (pow(aux2, 0.5));

		//Velocity Calculation
		aux1 = hp * d * G2;
		aux2 = aux1 / (f * length);
		ures = sqrt(aux2);

		//Flow Rate Calculation
		return  ures * area;
	}

	//Calculation Type 03
	else if (Type == 3) {

		//Variables Type 03
		float auxFelevado = pow(f, 0.2);

		//Input Type 03
		cout << "Enter the flow rate(in liters per second - l/s): ";
		cin >> q;
		q /= 1000;

		//Diameter Calculation
		aux1 = pow(q, 2) * 8 * length;
		aux2 = pow(Pi, 2) * G * hp;
		return (aux1 / aux2) * auxFelevado;
	}

}

//Pump Power Function
float bomba(float hp) {

	//Function Variables
	float pb; /*Pump Power*/
	float ef; /*Pump Efficiency*/
	float auxb1;
	float auxb2;

	//Input Pump Efficiency
	cout << "What is the efficiency of the pump?: ";
	cin >> ef;
	ef /= 100;

	//Pump Power Calculation
	auxb1 = 9810 * q * hp;
	auxb2 = 736 * ef;
	pb = auxb1 / auxb2;

	return pb;
}

//Main Function
int main(){

//Program Variables
	int tipo = 0;
	int tconta; /*Calculate Type*/
	int tbomba; /*Pump Condition*/
	float hpt = 0, ret1 = 0;
	float qres = 0;
	float dres = 0;

//Program Input
	cout << "Input the type problem " << " ";
	cin >> tconta;

//Input Type 01
	if (tconta == 1) {
		ret1 = Contas(hpt, tconta);
		cout << "Total System Load Loss: " << ret1 << endl;
	}

//Input Type 02
	else if (tconta == 2) {
		cout << "Enter System Loss: "; 
		cin >> hpt;

		ret1 = Contas(hpt, tconta);

		cout << "Flow rate of system in m3/s: " << ret1 << endl;
		cout << "Flow rate of system in L/s: " << ret1 * 1000 << endl;
	}

//Input Type 03
	else if (tconta == 3) {
		cout << "Enter System Loss: "; 
		cin >> hpt;

		ret1 = Contas(hpt, tconta);

		cout << "Diameter of the system in cm " << ret1 * 100 << endl;
		cout << "Diameter of the system in m: " << ret1 << endl;
	}

//Error Input
	else {
		cout << "Error Input" << endl;
		return 0;
	}

//Pump Input
	cout << "Calculate the pump (1-yes): ";
	cin >> tbomba;

	if (tbomba != 1) {
		cout << "End of Program" << endl;
		return 0;
	}

	ret1 = bomba(ret1);
	cout << "Pump Power (HP) " << ret1 << endl;
	
	return 0;
}