#include <iostream>
#include <string>
#include <cctype>
#include "main.h"

MDAEFSM::MDAEFSM(OP *op) : s0(this, op), s1(this, op), s2(this, op), s3(this, op), s4(this, op), s5(this, op), s6(this, op), start(this, op)
{
  LS[0] = &s0;
  LS[1] = &s1;
  LS[2] = &s2;
  LS[3] = &s3;
  LS[4] = &s4;
  LS[5] = &s5;
  LS[6] = &s6;
  LS[7] = &start;
  s = LS[7];
}

void MDAEFSM::Activate()
{
  s->Activate();
}

void MDAEFSM::Start()
{
  s->Start();
}

void MDAEFSM::PayType(int t)
{
  s->PayType(t);
}

void MDAEFSM::Reject()
{
  s->Reject();
}

void MDAEFSM::Cancel()
{
  s->Cancel();
}

void MDAEFSM::Approved()
{
  s->Approved();
}

void MDAEFSM::StartPump()
{
  s->StartPump();
}

void MDAEFSM::Pump()
{
  s->Pump();
}

void MDAEFSM::StopPump()
{
  s->StopPump();
}

void MDAEFSM::SelectGas(int g)
{
  s->SelectGas(g);
}

void MDAEFSM::Receipt()
{
  s->Receipt();
}

void MDAEFSM::NoReceipt()
{
  s->NoReceipt();
}

void MDAEFSM::Continue()
{
  s->Continue();
}

void MDAEFSM::ChangeState(int x)
{
  std::cout << "Change State to S" << x << std::endl;
  s = LS[x];
}

State::State(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
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

Start::Start(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void Start::Activate()
{
  op->StorePrices();
  p->ChangeState(0);
}

S0::S0(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void S0::Start()
{
  op->PayMsg();
  p->ChangeState(1);
}

S1::S1(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void S1::PayType(int t)
{
  if (t == 1)
  {
    p->ChangeState(2);
  }
  else
  {
    op->StoreCash();
    op->DisplayMenu();
    op->SetPayType(t);
    p->ChangeState(3);
  }
}

S2::S2(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void S2::Reject()
{
  op->RejectMsg();
  op->EjectCard();
  p->ChangeState(0);
}

void S2::Approved()
{
  op->DisplayMenu();
  op->SetPayType(1);
  op->EjectCard();
  p->ChangeState(3);
}

S3::S3(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void S3::Cancel()
{
  op->CancelMsg();
  p->ChangeState(0);
}

void S3::Continue()
{
  p->ChangeState(4);
}

void S3::SelectGas(int g)
{
  op->SetPrice(g);
}

S4::S4(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void S4::StartPump()
{
  op->SetInitValues();
  p->ChangeState(5);
}

S5::S5(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void S5::Pump()
{
  op->PumpGasUnit();
  op->GasPumpedMsg();
}

void S5::StopPump()
{
  p->ChangeState(6);
}

S6::S6(MDAEFSM *mda, OP *op)
{
  this->p = mda;
  this->op = op;
}

void S6::NoReceipt()
{
  op->ReturnCash();
  p->ChangeState(0);
}

void S6::Receipt()
{
  op->PrintReceipt();
  op->ReturnCash();
  p->ChangeState(0);
}

GP1::GP1(DataStore1 *ds, MDAEFSM *mda, AbstractFactory *af)
{
  this->d = ds;
  this->m = mda;
  this->af = af;
}

void GP1::Activate(int a)
{
  std::cout << "Activate GasPump price with parameter: " << a << std::endl;
  if (a > 0)
  {
    ((DataStore1 *)d)->temp_a = a;
    m->Activate();
  }
}

void GP1::Start()
{
  std::cout << "Start GasPump" << std::endl;
  m->Start();
}

void GP1::PayCredit()
{
  std::cout << "Pay with credit" << std::endl;
  m->PayType(1);
}

void GP1::Reject()
{
  std::cout << "Transaction rejected" << std::endl;
  m->Reject();
}

void GP1::Cancel()
{
  std::cout << "Transaction cancelled" << std::endl;
  m->Cancel();
}

void GP1::Approved()
{
  std::cout << "Transaction approved" << std::endl;
  m->Approved();
}

void GP1::PayCash(int c)
{
  std::cout << "Pay with cash: " << c << std::endl;
  if (c > 0)
  {
    ((DataStore1 *)d)->temp_cash = c;
    m->PayType(0);
  }
}

void GP1::StartPump()
{
  std::cout << "Start pumping gas" << std::endl;
  m->Continue();
  m->StartPump();
}

void GP1::Pump()
{
  std::cout << "Pumping gas" << std::endl;
  if (((DataStore1 *)d)->w == 1)
  {
    m->Pump();
  }
  else if (((DataStore1 *)d)->cash < ((DataStore1 *)d)->price * (((DataStore1 *)d)->L + 1))
  {
    m->StopPump();
    m->Receipt();
  }
  else
  {
    m->Pump();
  }
}

void GP1::StopPump()
{
  std::cout << "Stop pumping gas" << std::endl;
  m->StopPump();
  m->Receipt();
}

GP2::GP2(DataStore2 *ds)
{
  this->d = ds;
}

void GP2::Activate(float a, float b, float c)
{
  std::cout << "Activate GasPump with Regular/Premium/Diesel: " << a << b << c << std::endl;
  if (a > 0 && b > 0 && c > 0)
  {
    ((DataStore2 *)d)->temp_a = a;
    ((DataStore2 *)d)->temp_b = b;
    ((DataStore2 *)d)->temp_c = c;
    m->Activate();
  }
}

void GP2::Start()
{
  std::cout << "Start GasPump" << std::endl;
  m->Start();
}

void GP2::PayCash(int c)
{
  std::cout << "Pay with cash: " << c << std::endl;
  if (c > 0)
  {
    ((DataStore2 *)d)->temp_cash = c;
    m->PayType(0);
  }
}

void GP2::Cancel()
{
  std::cout << "Transaction cancelled" << std::endl;
  m->Cancel();
}

void GP2::Premium()
{
  std::cout << "Premium gas selected" << std::endl;
  m->SelectGas(3);
  m->Continue();
}

void GP2::Regular()
{
  std::cout << "Regular gas selected" << std::endl;
  m->SelectGas(1);
  m->Continue();
}

void GP2::Diesel()
{
  std::cout << "Diesel gas selected" << std::endl;
  m->SelectGas(2);
  m->Continue();
}

void GP2::StartPump()
{
  std::cout << "Start pumping gas" << std::endl;
  m->StartPump();
}

void GP2::PumpGallon()
{
  std::cout << "One gallon of gas is disposed" << std::endl;
  if (((DataStore2 *)d)->cash < ((DataStore2 *)d)->price * (((DataStore2 *)d)->G + 1))
  {
    m->StopPump();
  }
  else
  {
    m->Pump();
  }
}

void GP2::Stop()
{
  std::cout << "Stop pumping gas" << std::endl;
  m->StopPump();
}

void GP2::Receipt()
{
  std::cout << "Receipt is requested" << std::endl;
  m->Receipt();
}

void GP2::NoReceipt()
{
  std::cout << "No receipt" << std::endl;
  m->NoReceipt();
}

OP::OP() {}

void OP::StorePrices()
{
  std::cout << "op->StorePrices() called." << std::endl;
  StorePrices();
}

void OP::PayMsg()
{
  std::cout << "op->PayMsg() called." << std::endl;
}

void OP::StoreCash()
{
  std::cout << "op->StoreCash() called." << std::endl;
}

void OP::DisplayMenu()
{
  std::cout << "op->DisplayMenu() called." << std::endl;
}

void OP::RejectMsg()
{
  std::cout << "op->RejectMsg() called." << std::endl;
}

void OP::SetPrice(int g)
{
  std::cout << "op->SetPrice() called with gas type: " << g << std::endl;
}

void OP::SetInitValues()
{
  std::cout << "op->SetInitValues() called." << std::endl;
}

void OP::PumpGasUnit()
{
  std::cout << "op->PumpGasUnit() called." << std::endl;
}

void OP::GasPumpedMsg()
{
  std::cout << "op->GasPumpedMsg() called." << std::endl;
}

void OP::PrintReceipt()
{
  std::cout << "op->PrintReceipt() called." << std::endl;
}

void OP::CancelMsg()
{
  std::cout << "op->CancelMsg() called." << std::endl;
}

void OP::ReturnCash()
{
  std::cout << "op->ReturnCash() called." << std::endl;
}

void OP::SetPayType(int t)
{
  std::cout << "op->SetPayType() called with payment type: " << t << std::endl;
}

void OP::EjectCard()
{
  std::cout << "op->EjectCard() called." << std::endl;
}

AbstractFactory::AbstractFactory()
{
  // Constructor implementation
}

void AbstractFactory::StorePrices()
{
  std::cout << "AbstractFactory::StorePrices() called." << std::endl;
  // Implementation of StorePrices
}

void AbstractFactory::PayMsg()
{
  std::cout << "AbstractFactory::PayMsg() called." << std::endl;
  // Implementation of PayMsg
}

void AbstractFactory::StoreCash()
{
  std::cout << "AbstractFactory::StoreCash() called." << std::endl;
  // Implementation of StoreCash
}

void AbstractFactory::DisplayMenu()
{
  std::cout << "AbstractFactory::DisplayMenu() called." << std::endl;
  // Implementation of DisplayMenu
}

void AbstractFactory::RejectMsg()
{
  std::cout << "AbstractFactory::RejectMsg() called." << std::endl;
  // Implementation of RejectMsg
}

void AbstractFactory::SetPrice(int g)
{
  std::cout << "AbstractFactory::SetPrice() called with gas type: " << g << std::endl;
  // Implementation of SetPrice
}

void AbstractFactory::SetInitValues()
{
  std::cout << "AbstractFactory::SetInitValues() called." << std::endl;
  // Implementation of SetInitValues
}

void AbstractFactory::PumpGasUnit()
{
  std::cout << "AbstractFactory::PumpGasUnit() called." << std::endl;
  // Implementation of PumpGasUnit
}

void AbstractFactory::GasPumpedMsg()
{
  std::cout << "AbstractFactory::GasPumpedMsg() called." << std::endl;
  // Implementation of GasPumpedMsg
}

void AbstractFactory::PrintReceipt()
{
  std::cout << "AbstractFactory::PrintReceipt() called." << std::endl;
  // Implementation of PrintReceipt
}

void AbstractFactory::CancelMsg()
{
  std::cout << "AbstractFactory::CancelMsg() called." << std::endl;
  // Implementation of CancelMsg
}

void AbstractFactory::ReturnCash()
{
  std::cout << "AbstractFactory::ReturnCash() called." << std::endl;
  // Implementation of ReturnCash
}

void AbstractFactory::SetPayType(int t)
{
  std::cout << "AbstractFactory::SetPayType() called with payment type: " << t << std::endl;
  // Implementation of SetPayType
}

void AbstractFactory::EjectCard()
{
  std::cout << "AbstractFactory::EjectCard() called." << std::endl;
  // Implementation of EjectCard
}

void StorePrices1::StorePrices()
{
  std::cout << "StorePrices1::StorePrices() called." << std::endl;
  // d->price = d->temp_a;
}

ConcreteFactory1::ConcreteFactory1() {}

void ConcreteFactory1::StorePrices()
{
  std::cout << "ConcreteFactory1::StorePrices() called." << std::endl;
  StorePrices1 *c;
  c->StorePrices();
}

void ConcreteFactory1::PayMsg()
{
  std::cout << "ConcreteFactory1::PayMsg() called." << std::endl;
  // Implementation of PayMsg for ConcreteFactory1
}

void ConcreteFactory1::StoreCash()
{
  std::cout << "ConcreteFactory1::StoreCash() called." << std::endl;
  // Implementation of StoreCash for ConcreteFactory1
}

void ConcreteFactory1::DisplayMenu()
{
  std::cout << "ConcreteFactory1::DisplayMenu() called." << std::endl;
  // Implementation of DisplayMenu for ConcreteFactory1
}

void ConcreteFactory1::RejectMsg()
{
  std::cout << "ConcreteFactory1::RejectMsg() called." << std::endl;
  // Implementation of RejectMsg for ConcreteFactory1
}

void ConcreteFactory1::SetPrice(int g)
{
  std::cout << "ConcreteFactory1::SetPrice() called with gas type: " << g << std::endl;
  // Implementation of SetPrice for ConcreteFactory1
}

void ConcreteFactory1::SetInitValues()
{
  std::cout << "ConcreteFactory1::SetInitValues() called." << std::endl;
  // Implementation of SetInitValues for ConcreteFactory1
}

void ConcreteFactory1::PumpGasUnit()
{
  std::cout << "ConcreteFactory1::PumpGasUnit() called." << std::endl;
  // Implementation of PumpGasUnit for ConcreteFactory1
}

void ConcreteFactory1::GasPumpedMsg()
{
  std::cout << "ConcreteFactory1::GasPumpedMsg() called." << std::endl;
  // Implementation of GasPumpedMsg for ConcreteFactory1
}

void ConcreteFactory1::PrintReceipt()
{
  std::cout << "ConcreteFactory1::PrintReceipt() called." << std::endl;
  // Implementation of PrintReceipt for ConcreteFactory1
}

void ConcreteFactory1::CancelMsg()
{
  std::cout << "ConcreteFactory1::CancelMsg() called." << std::endl;
  // Implementation of CancelMsg for ConcreteFactory1
}

void ConcreteFactory1::ReturnCash()
{
  std::cout << "ConcreteFactory1::ReturnCash() called." << std::endl;
  // Implementation of ReturnCash for ConcreteFactory1
}

void ConcreteFactory1::SetPayType(int t)
{
  std::cout << "ConcreteFactory1::SetPayType() called with payment type: " << t << std::endl;
  // Implementation of SetPayType for ConcreteFactory1
}

void ConcreteFactory1::EjectCard()
{
  std::cout << "ConcreteFactory1::EjectCard() called." << std::endl;
  // Implementation of EjectCard for ConcreteFactory1
}

ConcreteFactory2::ConcreteFactory2()
{
  // Constructor implementation
}

void ConcreteFactory2::StorePrices()
{
  std::cout << "ConcreteFactory2::StorePrices() called." << std::endl;
  // Implementation of StorePrices for ConcreteFactory2
}

void ConcreteFactory2::PayMsg()
{
  std::cout << "ConcreteFactory2::PayMsg() called." << std::endl;
  // Implementation of PayMsg for ConcreteFactory2
}

void ConcreteFactory2::StoreCash()
{
  std::cout << "ConcreteFactory2::StoreCash() called." << std::endl;
  // Implementation of StoreCash for ConcreteFactory2
}

void ConcreteFactory2::DisplayMenu()
{
  std::cout << "ConcreteFactory2::DisplayMenu() called." << std::endl;
  // Implementation of DisplayMenu for ConcreteFactory2
}

void ConcreteFactory2::RejectMsg()
{
  std::cout << "ConcreteFactory2::RejectMsg() called." << std::endl;
  // Implementation of RejectMsg for ConcreteFactory2
}

void ConcreteFactory2::SetPrice(int g)
{
  std::cout << "ConcreteFactory2::SetPrice() called with gas type: " << g << std::endl;
  // Implementation of SetPrice for ConcreteFactory2
}

void ConcreteFactory2::SetInitValues()
{
  std::cout << "ConcreteFactory2::SetInitValues() called." << std::endl;
  // Implementation of SetInitValues for ConcreteFactory2
}

void ConcreteFactory2::PumpGasUnit()
{
  std::cout << "ConcreteFactory2::PumpGasUnit() called." << std::endl;
  // Implementation of PumpGasUnit for ConcreteFactory2
}

void ConcreteFactory2::GasPumpedMsg()
{
  std::cout << "ConcreteFactory2::GasPumpedMsg() called." << std::endl;
  // Implementation of GasPumpedMsg for ConcreteFactory2
}

void ConcreteFactory2::PrintReceipt()
{
  std::cout << "ConcreteFactory2::PrintReceipt() called." << std::endl;
  // Implementation of PrintReceipt for ConcreteFactory2
}

void ConcreteFactory2::CancelMsg()
{
  std::cout << "ConcreteFactory2::CancelMsg() called." << std::endl;
  // Implementation of CancelMsg for ConcreteFactory2
}

void ConcreteFactory2::ReturnCash()
{
  std::cout << "ConcreteFactory2::ReturnCash() called." << std::endl;
  // Implementation of ReturnCash for ConcreteFactory2
}

void ConcreteFactory2::SetPayType(int t)
{
  std::cout << "ConcreteFactory2::SetPayType() called with payment type: " << t << std::endl;
  // Implementation of SetPayType for ConcreteFactory2
}

void ConcreteFactory2::EjectCard()
{
  std::cout << "ConcreteFactory2::EjectCard() called." << std::endl;
  // Implementation of EjectCard for ConcreteFactory2
}

int main()
{
  DataStore1 ds1;
  DataStore2 ds2;
  OP op;
  MDAEFSM mda(&op);
  AbstractFactory af;
  // ConcreteFactory1 cf1;
  // ConcreteFactory2 cf2;
  std::string choice;
  int a, b, c;

  std::cout << "Welcome to GasPump System!" << std::endl;
  std::cout << "1. GasPump-1" << std::endl;
  std::cout << "2. GasPump-2" << std::endl;
  std::cout << "Select GasPump: ";
  std::cin >> choice;
  std::cout << std::endl;

  if (choice == "1")
  {
    GP1 gp1(&ds1, &mda, &af);
    while (choice != "q")
    {
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
      if (choice == "q")
      {
        break;
      }

      if (std::stoi(choice) >= 0 && std::stoi(choice) <= 9)
      {
        std::cout << " ***** Operation:";
        switch (std::stoi(choice))
        {
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
      }
      else if (choice != "q")
      {
        std::cout << "Invalid choice" << std::endl;
      }
    }
  }
  else if (choice == "2")
  {
    GP2 gp2(&ds2);
    while (choice != "q")
    {
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
      if (choice == "q")
      {
        break;
      }

      if (std::stoi(choice) >= 0 && std::stoi(choice) <= 11)
      {
        std::cout << "Operation: ";
        switch (std::stoi(choice))
        {
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
      }
      else if (choice != "q")
      {
        std::cout << "Invalid choice" << std::endl;
      }
    }
  }
  else
  {
    std::cout << "Invalid choice. Exiting..." << std::endl;
  }
  return 0;
}
