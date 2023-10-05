#ifndef EXPEDIA_USER_MGR_H_
#define EXPEDIA_USER_MGR_H_

#include <map>
using namespace std;

#include "expedia_payment_card.h"
#include "expedia_user.h"
#include "expedia_utils.h"


class UsersManager {
protected:
	User* current_user = nullptr;
	map<string, User*> username_userObject_map;

	void FreeLoadedData() {
		for (auto pair : username_userObject_map) {
			delete pair.second;
		}
		username_userObject_map.clear();
		current_user = nullptr;
	}

public:

	UsersManager() {
	}

	~UsersManager() {
		cout << "Destructor: UsersManager\n";
		FreeLoadedData();
	}

	UsersManager(const UsersManager&) = delete; // No sense for such a class (manager of objects) to be copyable!
	void operator=(const UsersManager&) = delete;

	void LoadDatabase() {
		cout << "UsersManager: LoadDatabase\n";

		FreeLoadedData();

		// Some "Dummy Data" for simplicity
		Admin* admin_user = new Admin();
		admin_user->SetUserName("mohamed");
		admin_user->SetPassword("123");
		admin_user->SetEmail("mohamed@gmail.com");
		admin_user->SetName("mohamed Mostafa Mahmoud");
		username_userObject_map[admin_user->GetUserName()] = admin_user;

		Customer* customerUser = new Customer();
		customerUser->SetUserName("mostafa");
		customerUser->SetPassword("456");
		customerUser->SetEmail("mostafa@gmail.com");
		customerUser->SetName("Mostafa Mahmoud Elsayed");

		DebitCard* debitCard = new DebitCard();
		debitCard->SetOwnerName(customerUser->GetName());
		debitCard->SetCardNumber("11-22-33-44");
		debitCard->SetExpiryDate("11/20");
		debitCard->SetSecurityCode(111);
		debitCard->SetBillingAddress("111 hello st, BC, Canada");
		customerUser->AddPaymentCard(*debitCard);

		CreditCard* creditCard = new CreditCard();
		creditCard->SetOwnerName(customerUser->GetName());
		creditCard->SetCardNumber("22-11-03-44");
		creditCard->SetExpiryDate("11/25");
		creditCard->SetSecurityCode(1117);
		customerUser->AddPaymentCard(*creditCard);
		username_userObject_map[customerUser->GetUserName()] = customerUser;

	}

	void AccessSystem() {
		int choice = ShowReadMenu( { "Login", "Customer Sign Up" });
		if (choice == 1)
			DoLogin();
		else
			DoSignUp();
	}

	void DoLogin() {
		LoadDatabase();

		while (true) {
			string user_name, pass;
			cout << "Enter user user_name & password: ";
			cin >> user_name >> pass;

			if (!username_userObject_map.count(user_name)) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			User* user_exist = username_userObject_map.find(user_name)->second;

			if (pass != user_exist->GetPassword()) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			current_user = user_exist;
			break;
		}
	}

	void DoSignUp() {
		string user_name;
		while (true) {
			cout << "Enter user name. (No spaces): ";
			cin >> user_name;

			if (username_userObject_map.count(user_name))
				cout << "Already used. Try again\n";
			else
				break;
		}
		current_user = new Customer();
		current_user->Read(user_name);
		username_userObject_map[current_user->GetUserName()] = current_user;
	}

	User* GetCurrentUser() const {
		// For simplicity, I don't return it as const, which is not good
		// One ok way: return as const, and user support clone + copy constructor. Then caller can make his own copy
		return current_user;
	}
};



#endif /* EXPEDIA_USER_MGR_H_ */

