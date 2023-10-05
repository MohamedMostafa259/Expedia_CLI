#include<iostream>
#include<vector>
using namespace std;

#include"expedia_customer.h"
#include"expedia_user_mgr.h"
#include"expedia_customer_view.h"

class ExpediaFrontend {
private:
	UsersManager* users_manager;
	ExpediaBackend* expedia_manager;
	CustomerManager* customer_manager = nullptr;

	void LoadDatabase() {
		users_manager->LoadDatabase();
	}

public:
	ExpediaFrontend(const ExpediaFrontend&) = delete;
	void operator=(const ExpediaFrontend&) = delete;

	ExpediaFrontend() : users_manager(new UsersManager()), expedia_manager(new ExpediaBackend()){
	}

	~ExpediaFrontend() {
		cout << "Destructor: ExpediaFrontend\n";

		if (users_manager != nullptr) {
			delete users_manager;
			users_manager = nullptr;
		}
	}

	void Run() {
		LoadDatabase();

		while (true) {
			users_manager->AccessSystem();	// login/signup

			if(users_manager->GetCurrentUser()->GetType() == UserType::CustomerUser) {
				customer_manager = new CustomerManager(users_manager->GetCurrentUser(), *expedia_manager);
				CustomerView view(*customer_manager);
				view.Display();
			} else
				assert(false);
		}
	}
};


int main() {
	ExpediaFrontend site;
	site.Run();

	User* user = new Customer();
	dynamic_cast<Customer*>(user);

	return 0;
}

