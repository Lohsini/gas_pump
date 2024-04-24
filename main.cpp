#include <iostream>
#include <string>
#include <cctype>
#include "main.h"

void MDAEFSM::Activate() {
    s->Activate();
}

void MDAEFSM::Start() {
    s->Start();
}

void MDAEFSM::PayType(int t) {
    s->PayType(t);
}

void MDAEFSM::Reject() {
    s->Reject();
}

void MDAEFSM::Cancel() {
    s->Cancel();
}

void MDAEFSM::Approved() {
    s->Approved();
}

void MDAEFSM::StartPump() {
    s->StartPump();
}

void MDAEFSM::Pump() {
    s->Pump();
}

void MDAEFSM::StopPump() {
    s->StopPump();
}

void MDAEFSM::SelectGas(int g) {
    s->SelectGas(g);
}

void MDAEFSM::Receipt() {
    s->Receipt();
}

void MDAEFSM::NoReceipt() {
    s->NoReceipt();
}

void MDAEFSM::Continue() {
    s->Continue();
}

void MDAEFSM::ChangeState(int x) {
    s = LS[x];
}

void State::Activate() {}

void State::Start() {}

void State::PayType(int t) {}

void State::Reject() {}

void State::Cancel() {}

void State::Approved() {}

void State::StartPump() {}

void State::Pump() {}

void State::StopPump() {}

void State::SelectGas(int g) {}

void State::Receipt() {}

void State::NoReceipt() {}

void State::Continue() {}

void Start::Activate() {}

void S0::Start() {}

void S1::PayType(int t) {}

void S2::Reject() {}

void S2::Approved() {}

void S3::Cancel() {}

void S3::Continue() {}

void S3::SelectGas(int g) {}

void S4::StartPump() {}

void S5::Pump() {}

void S5::StopPump() {}

void S6::NoReceipt() {}

void S6::Receipt() {}

GP1::GP1(DataStore1 *ds) {
    this->d = ds;
}

void GP1::Activate(int a) {
    std::cout << "Activate GasPump price with parameter: " << a << std::endl;
}

void GP1::Start() {
    std::cout << "Start GasPump" << std::endl;
}

void GP1::PayCredit() {
    std::cout << "Pay with credit" << std::endl;
}

void GP1::Reject() {
    std::cout << "Transaction rejected" << std::endl;
}

void GP1::Cancel() {
    std::cout << "Transaction cancelled" << std::endl;
}

void GP1::Approved() {
    std::cout << "Transaction approved" << std::endl;
}

void GP1::PayCash(int c) {
    std::cout << "Pay with cash: " << c << std::endl;
}

void GP1::StartPump() {
    std::cout << "Start pumping gas" << std::endl;
}

void GP1::Pump() {
    std::cout << "Pumping gas" << std::endl;
}

void GP1::StopPump() {
    std::cout << "Stop pumping gas" << std::endl;
}

GP2::GP2(DataStore2 *ds) {
    this->d = ds;
}

void GP2::Activate(float a, float b, float c) {
    std::cout << "Activate GasPump with Regular/Premium/Diesel: " << a << b << c << std::endl;
}

void GP2::Start() {
    std::cout << "Start GasPump" << std::endl;
}

void GP2::PayCash(int c) {
    std::cout << "Pay with cash: " << c << std::endl;
}

void GP2::Cancel() {
    std::cout << "Transaction cancelled" << std::endl;
}

void GP2::Premium() {
    std::cout << "Premium gas selected" << std::endl;
}

void GP2::Regular() {
    std::cout << "Regular gas selected" << std::endl;
}

void GP2::Diesel() {
    std::cout << "Diesel gas selected" << std::endl;
}

void GP2::StartPump() {
    std::cout << "Start pumping gas" << std::endl;
}

void GP2::PumpGallon() {
    std::cout << "One gallon of gas is disposed" << std::endl;
}

void GP2::Stop() {
    std::cout << "Stop pumping gas" << std::endl;
}

void GP2::Receipt() {
    std::cout << "Receipt is requested" << std::endl;
}

void GP2::NoReceipt() {
    std::cout << "No receipt" << std::endl;
}

int main() {
  DataStore1 ds1;
  DataStore2 ds2;
  std::string choice;
  int a, b, c;

  std::cout << "Welcome to GasPump System!" << std::endl;
  std::cout << "1. GasPump-1" << std::endl;
  std::cout << "2. GasPump-2" << std::endl;
  std::cout << "Select GasPump: ";
  std::cin >> choice;
  std::cout << std::endl;

  if (choice == "1") {
    GP1 gp1(&ds1);
    while (choice != "q") {
      std::cout << " ----- GasPump-1 MENU of Operations ----- " << std::endl;
      std::cout << "0. Activate(int)" << std::endl;
      std::cout << "1. Start()" << std::endl;
      std::cout << "2. PayCredit" << std::endl;
      std::cout << "3. Reject()" << std::endl;
      std::cout << "4. Cancel()" << std::endl;
      std::cout << "5. Approved()" << std::endl;
      std::cout << "6. PayCash(int)" << std::endl;
      std::cout << "7. StartPump()" << std::endl;
      std::cout << "8. Pump()" << std::endl;
      std::cout << "9. StopPump()" << std::endl;
      std::cout << "q. Quit the program" << std::endl;
      std::cout << "Select Operation: ";
      std::cin >> choice;
      if (choice == "q"){
        break;
      }
      
      if (std::stoi(choice) >= 0 && std::stoi(choice) <= 9) {
        std::cout << " ***** Operation:";
        switch (std::stoi(choice)) {
          case 0:
            std::cout << "Activate(int a)" << std::endl;
            std::cout << "Enter value of the parameter a: ";
            std::cin >> a;
            gp1.Activate(a);
            break;
          case 1:
            std::cout << "Start()" << std::endl;
            gp1.Start();
            break;
          case 2:
            std::cout << "PayCredit()" << std::endl;
            gp1.PayCredit();
            break;
          case 3:
            std::cout << "Reject()" << std::endl;
            gp1.Reject();
            break;
          case 4:
            std::cout << "Cancel()" << std::endl;
            gp1.Cancel();
            break;
          case 5:
            std::cout << "Approved()" << std::endl;
            gp1.Approved();
            break;
          case 6:
            std::cout << "PayCash(int c)" << std::endl;
            std::cout << "Enter value of the parameter c: ";
            std::cin >> c;
            gp1.PayCash(c);
            break;
          case 7:
            std::cout << "StartPump()" << std::endl;
            gp1.StartPump();
            break;
          case 8:
            std::cout << "Pump()" << std::endl;
            gp1.Pump();
            break;
          case 9:
            std::cout << "StopPump()" << std::endl;
            gp1.StopPump();
            break;
        }
      } else if (choice != "q") {
          std::cout << "Invalid choice" << std::endl;
      }
    }
  } else if (choice == "2") {
    GP2 gp2(&ds2);
    while (choice != "q") {
      std::cout << "----- GasPump-2 MENU of Operations -----" << std::endl;
      std::cout << "0. Activate(float, float, float)" << std::endl;
      std::cout << "1. Start()" << std::endl;
      std::cout << "2. PayCash(int)" << std::endl;
      std::cout << "3. Cancel()" << std::endl;
      std::cout << "4. Premium()" << std::endl;
      std::cout << "5. Regular()" << std::endl;
      std::cout << "6. Diesel()" << std::endl;
      std::cout << "7. StartPump()" << std::endl;
      std::cout << "8. PumpGallon()" << std::endl;
      std::cout << "9. Stop()" << std::endl;
      std::cout << "10. Receipt()" << std::endl;
      std::cout << "11. NoReceipt()" << std::endl;
      std::cout << "q. Quit the program" << std::endl;
      std::cout << "Select Operation: ";
      std::cin >> choice;
      if (choice == "q"){
        break;
      }
      
      if (std::stoi(choice) >= 0 && std::stoi(choice) <= 11) {
        std::cout << "Operation: ";
        switch (std::stoi(choice)) {
          case 0:
            std::cout << "Activate(float, float, float)" << std::endl;
            std::cout << "Enter value of parameters with Regular/Premium/Diesel: ";
            std::cin >> a >> b >> c;
            gp2.Activate(a, b, c);
            break;
          case 1:
            std::cout << "Start()" << std::endl;
            gp2.Start();
            break;
          case 2:
            std::cout << "PayCash(int)" << std::endl;
            std::cout << "Enter value of the parameter cash: ";
            std::cin >> c;
            gp2.PayCash(c);
            break;
          case 3:
            std::cout << "Cancel()" << std::endl;
            gp2.Cancel();
            break;
          case 4:
            std::cout << "Premium()" << std::endl;
            gp2.Premium();
            break;
          case 5:
            std::cout << "Regular()" << std::endl;
            gp2.Regular();
            break;
          case 6:
            std::cout << "Diesel" << std::endl;
            gp2.Diesel();
            break;
          case 7:
            std::cout << "StartPump()" << std::endl;
            gp2.StartPump();
            break;
          case 8:
            std::cout << "PumpGallon()" << std::endl;
            gp2.PumpGallon();
            break;
          case 9:
            std::cout << "Stop()" << std::endl;
            gp2.Stop();
            break;
          case 10:
            std::cout << "Receipt()" << std::endl;
            gp2.Receipt();
            break;
          case 11:
            std::cout << "NoReceipt()" << std::endl;
            gp2.NoReceipt();
            break;
        }
      } else if (choice != "q") {
          std::cout << "Invalid choice" << std::endl;
      }
    }
  } else {
    std::cout << "Invalid choice. Exiting..." << std::endl;
  }
  return 0;
}
