#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <vector>

using namespace std;

const int SIZE = 62;

// function prototypes
vector<int> bounds(int, int);
void menu(unsigned, string&);
void mainCrack(const string&, string, char*, bool&, int, thread*, vector<int>);
bool check1(const string &, string &, char*);
bool check2(const string &, string &, char*);
bool check3(const string &, string &, char*);
bool check4(const string &, string &, char*);
bool check5(const string &, string &, char*);
bool check6(const string &, string &, char*);
bool check7(const string &, string &, char*);
void check6thread(const string &, string, char*, bool &, int, int);
void check7thread(const string, string, char*, bool &, int, int);
void check8thread(const string, string, char*, bool &, int, int);


int main(int argc, char** argv){

	unsigned numThreads = thread::hardware_concurrency();
	int parts = numThreads;
	char arr[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ0123456789";
	string password;
	string crack = "";
	bool found = false;
	vector<int>bnd = bounds(parts, SIZE);
	thread *t = new thread[parts - 1];
	time_t start, finish, result;
	float minutes;

	menu(numThreads, password);

	time(&start);

	mainCrack(password, crack, arr, ref(found), parts, t, bnd);

	time(&finish);

	result = finish - start;

	if (result >= 60) {

		minutes = static_cast<int>(result) / 60.0;
		cout << "Cracked in " << minutes << " minutes!!!" << endl;

	}

	else cout << "Cracked in " << result << " seconds!!!\n" << endl;

	//delete [] t;  // if you really want it :)

	system("PAUSE");

	return 0;
}

vector<int> bounds(int parts, int size){

	vector<int>bnd;
	int delta = size / parts;
	int reminder = size % parts;
	int N1 = 0, N2 = 0;
	bnd.push_back(N1);
	for (int i = 0; i < parts; ++i) {
		N2 = N1 + delta;
		if (i == parts - 1)
			N2 += reminder;
		bnd.push_back(N2);
		N1 = N2;
	}
	return bnd;
}


void menu(unsigned numThreads, string& password){


	float five = 24.0,
		six = 24.0,
		seven = 24.8,
		eight = 64.0,
		nine = 10.4,
		ten = 673.6,
		eleven = 41832.0,
		twelve = 2593616.0;

	switch (numThreads){

	case 2:
		five /= 2.0;
		six /= 2.0;
		seven /= 2.0;
		eight /= 2.0;
		nine /= 2.0;
		ten /= 2.0;
		eleven /= 2.0;
		twelve /= 2.0;
		break;

	case 4:
		five /= 4.0;
		six /= 4.0;
		seven /= 4.0;
		eight /= 4.0;
		nine /= 4.0;
		ten /= 4.0;
		eleven /= 4.0;
		twelve /= 4.0;
		break;

	case 8:
		five /= 8.0;
		six /= 8.0;
		seven /= 8.0;
		eight /= 8.0;
		nine /= 8.0;
		ten /= 8.0;
		eleven /= 8.0;
		twelve /= 8.0;
		break;

	case 12:
		five /= 12.0;
		six /= 12.0;
		seven /= 12.0;
		eight /= 12.0;
		nine /= 12.0;
		ten /= 12.0;
		eleven /= 12.0;
		twelve /= 12.0;
		break;

	case 16:
		five /= 16.0;
		six /= 16.0;
		seven /= 16.0;
		eight /= 16.0;
		nine /= 16.0;
		ten /= 16.0;
		eleven /= 16.0;
		twelve /= 16.0;
		break;

	default:
		break;
	}

	cout << "Password Crack Simulator\n";
	cout << "Created by:  Matt Danner\n\n";
	cout << "This progam will take a given password and \nattempt a brute force method of finding the password.\n\n";
	cout << "************PASSWORD CRACKING TRIVIA!!*************\n\n";
	cout << "Your computer has " << numThreads << " virtual cpu cores.\n\n";
	cout << "Approximate length of time to find passwords:\n\n";
	cout << "1, 2, 3, or 4 Letters: near-instant\n";
	cout << "5 Letters: " << five << " seconds\n";
	cout << "6 Letters: " << six << " minutes\n";
	cout << "7 Letters: " << seven << " hours\n";
	cout << "8 Letters: " << eight << " days\n";
	cout << "9 Letters: " << nine << " years\n";
	cout << "10 Letters: " << ten << " years\n";
	cout << "11 Letters: " << eleven << " years\n";
	cout << "12 Letters: " << twelve << " years.\n\n";
	cout << "**************************************************\n\n";

	do{
		cout << "Enter a password to crack: ";
		cin >> password;
		cout << endl;

		if (password.length() > 8) cout << "Seriously?!  You are not running this program for several years.  \nTry another password\n\n";

	} while (password.length() > 8);

}

void mainCrack(const string &password, string crack, char* arr, bool &found, int parts, thread* t, vector<int> bnd){


	while (!found){

		crack += '0';

		cout << "working " << crack.length() << " digits..." << endl;

		switch (crack.length()){

		case 1:
			found = check1(password, crack, arr);
			break;
		case 2:
			found = check2(password, crack, arr);
			break;
		case 3:
			found = check3(password, crack, arr);
			break;
		case 4:
			found = check4(password, crack, arr);
			break;
		case 5:
			found = check5(password, crack, arr);
			break;
		case 6:
			cout << "Could take up to 3 minutes!!!\n";
			for (int i = 0; i < parts - 1; i++){
				t[i] = thread(check6thread, password, crack, arr, ref(found), bnd[i], bnd[i + 1]);
			}
			check6thread(password, crack, arr, ref(found), bnd[parts - 1], bnd[parts]);

			for (int i = 0; i < parts - 1; i++){
				t[i].join();
			}

			// for testing non-threaded procedure
			//found = check6(password, crack, arr);
			break;
		case 7:
			cout << "Could take up to 3 hours!!!\n";
			for (int i = 0; i < parts - 1; i++){
				t[i] = thread(check7thread, password, crack, arr, ref(found), bnd[i], bnd[i + 1]);
			}
			check7thread(password, crack, arr, ref(found), bnd[parts - 1], bnd[parts]);

			for (int i = 0; i < parts - 1; i++){
				t[i].join();
			}

			// for testing non-threaded procedure
			//found = check7(password, crack, arr);
			break;
		case 8:
			cout << "Could take up to 8 days!!!\n";
			for (int i = 0; i < parts - 1; i++){
				t[i] = thread(check8thread, password, crack, arr, ref(found), bnd[i], bnd[i + 1]);
			}
			check8thread(password, crack, arr, ref(found), bnd[parts - 1], bnd[parts]);

			for (int i = 0; i < parts - 1; i++){
				t[i].join();
			}
			break;
		case 9:
			break;
		case 10:
			break;
		default:
			found = false;
			break;
		}
	}
}

bool check1(const string &password, string &crack, char *arr){

	for (int i = 0; i < SIZE; i++){

		crack[0] = arr[i];

		if (crack == password) {
			cout << "password is: " << crack << endl;

			return true;
		}
	}

	return false;
}

bool check2(const string &password, string &crack, char *arr){

	for (int i = 0; i < SIZE; i++){

		crack[0] = arr[i];

		for (int j = 0; j < SIZE; j++){

			crack[1] = arr[j];
			if (crack == password) {
				cout << "password is: " << crack << endl;

				return true;
			}
		}

	}

	return false;
}

bool check3(const string &password, string &crack, char *arr){

	for (int a = 0; a < SIZE; a++){

		crack[0] = arr[a];

		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];
				if (crack == password) {
					cout << "password is: " << crack << endl;

					return true;
				}
			}
		}
	}

	return false;
}

bool check4(const string &password, string &crack, char *arr){

	for (int a = 0; a < SIZE; a++){

		crack[0] = arr[a];

		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];

				for (int d = 0; d < SIZE; d++){

					crack[3] = arr[d];
					if (crack == password) {
						cout << "password is: " << crack << endl;

						return true;
					}
				}
			}
		}
	}

	return false;
}

bool check5(const string &password, string &crack, char *arr){

	for (int a = 0; a < SIZE; a++){

		crack[0] = arr[a];

		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];

				for (int d = 0; d < SIZE; d++){

					crack[3] = arr[d];

					for (int e = 0; e < SIZE; e++){

						crack[4] = arr[e];
						if (crack == password) {
							cout << "password is: " << crack << endl;

							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool check6(const string &password, string &crack, char *arr){

	for (int a = 0; a < SIZE; a++){

		crack[0] = arr[a];

		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];

				for (int d = 0; d < SIZE; d++){

					crack[3] = arr[d];

					for (int e = 0; e < SIZE; e++){

						crack[4] = arr[e];

						for (int f = 0; f < SIZE; f++){

							crack[5] = arr[f];
							if (crack == password) {
								cout << "password is: " << crack << endl;

								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool check7(const string &password, string &crack, char *arr){

	for (int a = 0; a < SIZE; a++){

		crack[0] = arr[a];
		
		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];
			//cout << crack << endl; // testing

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];
				//cout << crack << endl; // testing


				for (int d = 0; d < SIZE; d++){

					crack[3] = arr[d];

					for (int e = 0; e < SIZE; e++){

						crack[4] = arr[e];

						for (int f = 0; f < SIZE; f++){

							crack[5] = arr[f];

							for (int g = 0; g < SIZE; g++){

								crack[6] = arr[g];
								//cout << crack << endl; // testing

								if (crack == password) { 
									cout << "password is: " << crack << endl;

									return true; 
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}


void check6thread(const string &password, string crack, char *arr, bool &found, int start, int end){

	for (int a = start; a < end; a++){

		crack[0] = arr[a];

		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];

				for (int d = 0; d < SIZE; d++){

					crack[3] = arr[d];

					for (int e = 0; e < SIZE; e++){

						crack[4] = arr[e];

						for (int f = 0; f < SIZE; f++){

							crack[5] = arr[f];
							if (crack == password) {
								found = true;
								cout << "password is: " << crack << endl;
								return;
							}

							if (found) return;
						}
					}
				}
			}
		}
	}
}

void check7thread(const string password, string crack, char *arr, bool &found, int start, int end){

	for (int a = start; a < end; a++){

		crack[0] = arr[a];
		//cout << crack << " ";  // testing

		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];

				for (int d = 0; d < SIZE; d++){

					crack[3] = arr[d];

					for (int e = 0; e < SIZE; e++){

						crack[4] = arr[e];

						for (int f = 0; f < SIZE; f++){

							crack[5] = arr[f];

							for (int g = 0; g < SIZE; g++){

								crack[6] = arr[g];
								if (crack == password) {
									found = true;
									cout << "password is: " << crack << endl;
									return;
								}

								if (found) return;
							}
						}
					}
				}
			}
		}
	}
}

void check8thread(const string password, string crack, char *arr, bool &found, int start, int end){

	for (int a = start; a < end; a++){

		crack[0] = arr[a];
		//cout << crack << " ";  // testing

		for (int b = 0; b < SIZE; b++){

			crack[1] = arr[b];

			for (int c = 0; c < SIZE; c++){

				crack[2] = arr[c];

				for (int d = 0; d < SIZE; d++){

					crack[3] = arr[d];

					for (int e = 0; e < SIZE; e++){

						crack[4] = arr[e];

						for (int f = 0; f < SIZE; f++){

							crack[5] = arr[f];

							for (int g = 0; g < SIZE; g++){

								crack[6] = arr[g];

								for (int h = 0; h < SIZE; h++){
									crack[7] = arr[h];
									if (crack == password) {
										found = true;
										cout << "password is: " << crack << endl;
										return;
									}

									if (found) return;
								}
							}
						}
					}
				}
			}
		}
	}
}



