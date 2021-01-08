#include <iostream>
#include <thread>
#include <mutex>
#include <windows.h>


using namespace std;

mutex mtx;
int MAX_VISITORS = 5;
int haircut_time = 3000;
int number_of_visitors = 5;
bool sleep = false;



void barber_actions() {
	while (true) {
		mtx.lock();
		if (number_of_visitors > 0) {
		
			number_of_visitors = number_of_visitors - 1;

			sleep = false;
			cout << "Парикмахер стрижёт посетителя" << endl << "Посетителей в очереди:" << number_of_visitors << endl;
			Sleep(1000);
			cout << "Парикмахер подстриг на 10 из 10)" << endl;
		}
		else {
			
			sleep = true;
			cout << "ZZZ" << endl;
			
		}
		mtx.unlock();
		this_thread::sleep_for(chrono::milliseconds(1000));

	}
}

void visitor_actions() {

	if (number_of_visitors == 0) {

		if (sleep == true) {
			sleep = false;
			cout << "Парикмахер встал" << endl;
			number_of_visitors++;
		}
	}
	else {
		if (number_of_visitors == MAX_VISITORS) {
			cout << "Пришёл посетитель, но мест не оказалось. Пока-пока <3" << endl;
		}
		else {
			number_of_visitors += 1;
			cout << "Пришёл новый посетитель" << endl;
		}

	}
}

void flow_visitors() {
	while (true) {
		Sleep(rand()%5 * 1000);
		visitor_actions();
	}
}



int main() {
	setlocale(LC_ALL, "Russian");
	mutex mtx;
	thread th1(barber_actions);
	thread th2(flow_visitors);
	th1.join();
	th2.join();
}