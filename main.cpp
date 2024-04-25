#include <iostream>
#include <string>
#include <cctype>
#include "main.h"

//----------functions about state pattern----------
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

int MDAEFSM::GetCurrentStateIndex()
{
  for (int i = 0; i < 8; ++i)
  {
    if (LS[i] == s)
    {
      return i;
    }
  }
  return -1;
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
  op->EjectCard();
  op->DisplayMenu();
  op->SetPayType(1);
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

//-------------end-------------

//----------functions about stratgy pattern----------
void StorePrices::storePrices() {}

StorePrices1::StorePrices1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void StorePrices1::storePrices()
{
  // d->price = d->temp_a;
  cf1->setIntData("price", cf1->getIntData("temp_a"));
  int price = cf1->getIntData("price");
  std::cout << "   " << price << " is the gas price" << std::endl;
}

StorePrices2::StorePrices2(ConcreteFactory2 *cf2)
{
  this->cf2 = cf2;
}

void StorePrices2::storePrices()
{
  std::cout << "StorePrices2::StorePrices() called." << std::endl;
  // d->price = d->temp_a;
}

void PayMsg::payMsg() {}

void PayMsg1::payMsg()
{
  std::cout << "   Select payment:" << std::endl;
  std::cout << "   A.Credit (enter 2)" << std::endl;
  std::cout << "   B.Cash (enter 6)" << std::endl;
}

void PayMsg2::payMsg()
{
  std::cout << "display: pay message" << std::endl;
}

void StoreCash::storeCash() {}

StoreCash1::StoreCash1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void StoreCash1::storeCash()
{
  // d->cash = d->temp_cash;
  cf1->setIntData("cash", cf1->getIntData("temp_cash"));
}

void StoreCash2::storeCash()
{
  std::cout << "StoreCash2::StoreCash() called." << std::endl;
}

void DisplayMenu::displayMenu() {}

void DisplayMenu1::displayMenu()
{
  std::cout << "   Menu:" << std::endl;
  std::cout << "   A.StartPump (enter 7)" << std::endl;
  std::cout << "   B.Cancel (enter 4)" << std::endl;
}

void DisplayMenu2::displayMenu()
{
  std::cout << "DisplayMenu2::DisplayMenu() called." << std::endl;
}

void RejectMsg::rejectMsg() {}

void RejectMsg1::rejectMsg()
{
  std::cout << "   The credit card is rejected" << std::endl;
}

void RejectMsg2::rejectMsg()
{
  std::cout << "RejectMsg2::RejectMsg() called." << std::endl;
}

void SetPrice::setPrice() {}

void SetPrice1::setPrice()
{
  std::cout << "SetPrice1::SetPrice() called." << std::endl;
}

void SetPrice2::setPrice()
{
  std::cout << "SetPrice2::SetPrice() called." << std::endl;
}

void SetInitValues::setInitValues() {}

SetInitValues1::SetInitValues1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void SetInitValues1::setInitValues()
{
  // d->total = 0;
  // d->L = 0;
  cf1->setIntData("total", 0);
  cf1->setIntData("L", 0);
  std::cout << "   Pump (enter 8)" << std::endl;
}

void SetInitValues2::setInitValues()
{
  std::cout << "SetInitValues2::SetInitValues() called." << std::endl;
}

void PumpGasUnit::pumpGasUnit() {}

PumpGasUnit1::PumpGasUnit1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void PumpGasUnit1::pumpGasUnit()
{
  // d->L = d->L + 1
  // d->total = d->total + (d->L * d->price)
  cf1->setIntData("L", cf1->getIntData("L") + 1);
  int cal_result = (cf1->getIntData("L") * cf1->getIntData("price"));
  cf1->setIntData("total", cal_result);
}

void PumpGasUnit2::pumpGasUnit()
{
  std::cout << "PumpGasUnit2::PumpGasUnit() called." << std::endl;
}

void GasPumpedMsg::gasPumpedMsg() {}

GasPumpedMsg1::GasPumpedMsg1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void GasPumpedMsg1::gasPumpedMsg()
{
  int L = cf1->getIntData("L");
  int total = cf1->getIntData("total");
  std::cout << "   Added " << L << " L gas" << std::endl;
  std::cout << "   Total is " << total << std::endl;
}

void GasPumpedMsg2::gasPumpedMsg()
{
  std::cout << "GasPumpedMsg2::GasPumpedMsg() called." << std::endl;
}

void PrintReceipt::printReceipt() {}

PrintReceipt1::PrintReceipt1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void PrintReceipt1::printReceipt()
{
  int total = cf1->getIntData("total");
  std::cout << "   Receipt:" << std::endl;
  std::cout << "   Total is " << total << std::endl;
}

void PrintReceipt2::printReceipt()
{
  std::cout << "PrintReceipt2::PrintReceipt() called." << std::endl;
}

void CancelMsg::cancelMsg() {}

void CancelMsg1::cancelMsg()
{
  std::cout << "   Transaction cancelled" << std::endl;
}

void CancelMsg2::cancelMsg()
{
  std::cout << "   Transaction cancelled" << std::endl;
}

void ReturnCash::returnCash() {}

ReturnCash1::ReturnCash1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void ReturnCash1::returnCash()
{
  int w = cf1->getIntData("w");
  if (w == 0)
  {
    int total = cf1->getIntData("total");
    int cash = cf1->getIntData("cash");
    int value = cash - total;
    std::cout << "   Return cash: " << value << std::endl;
  }
}

void ReturnCash2::returnCash()
{
  std::cout << "ReturnCash2::ReturnCash() called." << std::endl;
}

void SetPayType::setPayType(int t) {}

SetPayType1::SetPayType1(ConcreteFactory1 *cf1)
{
  this->cf1 = cf1;
}

void SetPayType1::setPayType(int t)
{
  // d->w = t;
  cf1->setIntData("w", t);
  int w = cf1->getIntData("w");
  // std::cout << w << " = " << t << " is right" << std::endl;
}

void SetPayType2::setPayType(int t)
{
  std::cout << "SetPayType2::SetPayType() called." << std::endl;
}

void EjectCard::ejectCard() {}

void EjectCard1::ejectCard()
{
  std::cout << "   Eject Card" << std::endl;
}

void EjectCard2::ejectCard()
{
  std::cout << "EjectCard2::EjectCard() called." << std::endl;
}

//-------------end-------------

//------functions about Abstract Factory pattern------
AbstractFactory::AbstractFactory() {}

StorePrices *AbstractFactory::StorePrices()
{
  std::cout << "AbstractFactory::StorePrices() called." << std::endl;
  return nullptr;
}

PayMsg *AbstractFactory::PayMsg()
{
  std::cout << "AbstractFactory::PayMsg() called." << std::endl;
  return nullptr;
}

StoreCash *AbstractFactory::StoreCash()
{
  std::cout << "AbstractFactory::StoreCash() called." << std::endl;
  return nullptr;
}

DisplayMenu *AbstractFactory::DisplayMenu()
{
  std::cout << "AbstractFactory::DisplayMenu() called." << std::endl;
  return nullptr;
}

RejectMsg *AbstractFactory::RejectMsg()
{
  std::cout << "AbstractFactory::RejectMsg() called." << std::endl;
  return nullptr;
}

SetPrice *AbstractFactory::SetPrice(int g)
{
  std::cout << "AbstractFactory::SetPrice() called with parameter: " << g << std::endl;
  return nullptr;
}

SetInitValues *AbstractFactory::SetInitValues()
{
  std::cout << "AbstractFactory::SetInitValues() called." << std::endl;
  return nullptr;
}

PumpGasUnit *AbstractFactory::PumpGasUnit()
{
  std::cout << "AbstractFactory::PumpGasUnit() called." << std::endl;
  return nullptr;
}

GasPumpedMsg *AbstractFactory::GasPumpedMsg()
{
  std::cout << "AbstractFactory::GasPumpedMsg() called." << std::endl;
  return nullptr;
}

PrintReceipt *AbstractFactory::PrintReceipt()
{
  std::cout << "AbstractFactory::PrintReceipt() called." << std::endl;
  return nullptr;
}

CancelMsg *AbstractFactory::CancelMsg()
{
  std::cout << "AbstractFactory::CancelMsg() called." << std::endl;
  return nullptr;
}

ReturnCash *AbstractFactory::ReturnCash()
{
  std::cout << "AbstractFactory::ReturnCash() called." << std::endl;
  return nullptr;
}

SetPayType *AbstractFactory::SetPayType(int t)
{
  std::cout << "AbstractFactory::SetPayType() called with parameter: " << t << std::endl;
  return nullptr;
}

EjectCard *AbstractFactory::EjectCard()
{
  std::cout << "AbstractFactory::EjectCard() called." << std::endl;
  return nullptr;
}

ConcreteFactory1::ConcreteFactory1(DataStore1 *d)
{
  this->d = d;
}

int ConcreteFactory1::getIntData(std::string s)
{
  if (s == "price")
  {
    return d->price;
  }
  else if (s == "cash")
  {
    return d->cash;
  }
  else if (s == "L")
  {
    return d->L;
  }
  else if (s == "w")
  {
    return d->w;
  }
  else if (s == "temp_a")
  {
    return d->temp_a;
  }
  else if (s == "temp_cash")
  {
    return d->temp_cash;
  }
  else if (s == "total")
  {
    return d->total;
  }
  else
  {
    return 0;
  }
}

void ConcreteFactory1::setIntData(std::string s, int n)
{
  if (s == "price")
  {
    d->price = n;
  }
  else if (s == "cash")
  {
    d->cash = n;
  }
  else if (s == "L")
  {
    d->L = n;
  }
  else if (s == "w")
  {
    d->w = n;
  }
  else if (s == "temp_a")
  {
    d->temp_a = n;
  }
  else if (s == "temp_cash")
  {
    d->temp_cash = n;
  }
  else if (s == "total")
  {
    d->total = n;
  }
}

StorePrices1 *ConcreteFactory1::StorePrices()
{
  StorePrices1 *storePrices1 = new StorePrices1(this);
  return storePrices1;
}

PayMsg1 *ConcreteFactory1::PayMsg()
{
  PayMsg1 *payMsg1 = new PayMsg1();
  return payMsg1;
}

StoreCash1 *ConcreteFactory1::StoreCash()
{
  // std::cout << "ConcreteFactory1::StoreCash() called." << std::endl;
  StoreCash1 *storeCash1 = new StoreCash1(this);
  return storeCash1;
}

DisplayMenu1 *ConcreteFactory1::DisplayMenu()
{
  // std::cout << "ConcreteFactory1::DisplayMenu() called." << std::endl;
  DisplayMenu1 *displayMenu1 = new DisplayMenu1();
  return displayMenu1;
}

RejectMsg1 *ConcreteFactory1::RejectMsg()
{
  // std::cout << "ConcreteFactory1::RejectMsg() called." << std::endl;
  RejectMsg1 *rejectMsg1 = new RejectMsg1();
  return rejectMsg1;
}

SetPrice1 *ConcreteFactory1::SetPrice(int g)
{
  std::cout << "ConcreteFactory1::SetPrice() called with gas type: " << g << std::endl;
  SetPrice1 *setPrice1 = new SetPrice1();
  return setPrice1;
}

SetInitValues1 *ConcreteFactory1::SetInitValues()
{
  // std::cout << "ConcreteFactory1::SetInitValues() called." << std::endl;
  SetInitValues1 *setInitValues1 = new SetInitValues1(this);
  return setInitValues1;
}

PumpGasUnit1 *ConcreteFactory1::PumpGasUnit()
{
  // std::cout << "ConcreteFactory1::PumpGasUnit() called." << std::endl;
  PumpGasUnit1 *pumpGasUnit1 = new PumpGasUnit1(this);
  return pumpGasUnit1;
}

GasPumpedMsg1 *ConcreteFactory1::GasPumpedMsg()
{
  // std::cout << "ConcreteFactory1::GasPumpedMsg() called." << std::endl;
  GasPumpedMsg1 *gasPumpedMsg1 = new GasPumpedMsg1(this);
  return gasPumpedMsg1;
}

PrintReceipt1 *ConcreteFactory1::PrintReceipt()
{
  // std::cout << "ConcreteFactory1::PrintReceipt() called." << std::endl;
  PrintReceipt1 *printReceipt1 = new PrintReceipt1(this);
  return printReceipt1;
}

CancelMsg1 *ConcreteFactory1::CancelMsg()
{
  // std::cout << "ConcreteFactory1::CancelMsg() called." << std::endl;
  CancelMsg1 *cancelMsg1 = new CancelMsg1();
  return cancelMsg1;
}

ReturnCash1 *ConcreteFactory1::ReturnCash()
{
  // std::cout << "ConcreteFactory1::ReturnCash() called." << std::endl;
  ReturnCash1 *returnCash1 = new ReturnCash1(this);
  return returnCash1;
}

SetPayType1 *ConcreteFactory1::SetPayType(int t)
{
  // std::cout << "ConcreteFactory1::SetPayType() called with payment type: " << t << std::endl;
  SetPayType1 *setPayType1 = new SetPayType1(this);
  return setPayType1;
}

EjectCard1 *ConcreteFactory1::EjectCard()
{
  // std::cout << "ConcreteFactory1::EjectCard() called." << std::endl;
  EjectCard1 *ejectCard1 = new EjectCard1();
  return ejectCard1;
}

ConcreteFactory2::ConcreteFactory2(DataStore2 *d)
{
  this->d = d;
}

StorePrices2 *ConcreteFactory2::StorePrices()
{
  std::cout << "ConcreteFactory2::StorePrices() called." << std::endl;
  StorePrices2 *storePrices2 = new StorePrices2(this);
  return storePrices2;
}

PayMsg2 *ConcreteFactory2::PayMsg()
{
  std::cout << "ConcreteFactory2::PayMsg() called." << std::endl;
  PayMsg2 *payMsg2 = new PayMsg2();
  return payMsg2;
}

StoreCash2 *ConcreteFactory2::StoreCash()
{
  std::cout << "ConcreteFactory2::StoreCash() called." << std::endl;
  StoreCash2 *storeCash2 = new StoreCash2();
  return storeCash2;
}

DisplayMenu2 *ConcreteFactory2::DisplayMenu()
{
  std::cout << "ConcreteFactory2::DisplayMenu() called." << std::endl;
  DisplayMenu2 *displayMenu2 = new DisplayMenu2();
  return displayMenu2;
}

RejectMsg2 *ConcreteFactory2::RejectMsg()
{
  std::cout << "ConcreteFactory2::RejectMsg() called." << std::endl;
  RejectMsg2 *rejectMsg2 = new RejectMsg2();
  return rejectMsg2;
}

SetPrice2 *ConcreteFactory2::SetPrice(int g)
{
  std::cout << "ConcreteFactory2::SetPrice() called with gas type: " << g << std::endl;
  SetPrice2 *setPrice2 = new SetPrice2();
  return setPrice2;
}

SetInitValues2 *ConcreteFactory2::SetInitValues()
{
  std::cout << "ConcreteFactory2::SetInitValues() called." << std::endl;
  SetInitValues2 *setInitValues2 = new SetInitValues2();
  return setInitValues2;
}

PumpGasUnit2 *ConcreteFactory2::PumpGasUnit()
{
  std::cout << "ConcreteFactory2::PumpGasUnit() called." << std::endl;
  PumpGasUnit2 *pumpGasUnit2 = new PumpGasUnit2();
  return pumpGasUnit2;
}

GasPumpedMsg2 *ConcreteFactory2::GasPumpedMsg()
{
  std::cout << "ConcreteFactory2::GasPumpedMsg() called." << std::endl;
  GasPumpedMsg2 *gasPumpedMsg2 = new GasPumpedMsg2();
  return gasPumpedMsg2;
}

PrintReceipt2 *ConcreteFactory2::PrintReceipt()
{
  std::cout << "ConcreteFactory2::PrintReceipt() called." << std::endl;
  PrintReceipt2 *printReceipt2 = new PrintReceipt2();
  return printReceipt2;
}

CancelMsg2 *ConcreteFactory2::CancelMsg()
{
  std::cout << "ConcreteFactory2::CancelMsg() called." << std::endl;
  CancelMsg2 *cancelMsg2 = new CancelMsg2();
  return cancelMsg2;
}

ReturnCash2 *ConcreteFactory2::ReturnCash()
{
  std::cout << "ConcreteFactory2::ReturnCash() called." << std::endl;
  ReturnCash2 *returnCash2 = new ReturnCash2();
  return returnCash2;
}

SetPayType2 *ConcreteFactory2::SetPayType(int t)
{
  std::cout << "ConcreteFactory2::SetPayType() called with payment type: " << t << std::endl;
  SetPayType2 *setPayType2 = new SetPayType2();
  return setPayType2;
}

EjectCard2 *ConcreteFactory2::EjectCard()
{
  std::cout << "ConcreteFactory2::EjectCard() called." << std::endl;
  EjectCard2 *ejectCard2 = new EjectCard2();
  return ejectCard2;
}
//-------------end-------------

OP::OP(AbstractFactory *af)
{
  this->af = af;
}

void OP::StorePrices()
{
  this->storep = af->StorePrices();
  storep->storePrices();
}

void OP::PayMsg()
{
  this->pm = af->PayMsg();
  pm->payMsg();
}

void OP::StoreCash()
{
  // std::cout << "op->StoreCash() called." << std::endl;
  this->sc = af->StoreCash();
  sc->storeCash();
}

void OP::DisplayMenu()
{
  // std::cout << "op->DisplayMenu() called." << std::endl;
  this->dm = af->DisplayMenu();
  dm->displayMenu();
}

void OP::RejectMsg()
{
  // std::cout << "op->RejectMsg() called." << std::endl;
  this->rm = af->RejectMsg();
  rm->rejectMsg();
}

void OP::SetPrice(int g)
{
  std::cout << "op->SetPrice() called with gas type: " << g << std::endl;
  this->setp = af->SetPrice(g);
  setp->setPrice();
}

void OP::SetInitValues()
{
  // std::cout << "op->SetInitValues() called." << std::endl;
  this->sv = af->SetInitValues();
  sv->setInitValues();
}

void OP::PumpGasUnit()
{
  // std::cout << "op->PumpGasUnit() called." << std::endl;
  this->pgu = af->PumpGasUnit();
  pgu->pumpGasUnit();
}

void OP::GasPumpedMsg()
{
  // std::cout << "op->GasPumpedMsg() called." << std::endl;
  this->gpm = af->GasPumpedMsg();
  gpm->gasPumpedMsg();
}

void OP::PrintReceipt()
{
  // std::cout << "op->PrintReceipt() called." << std::endl;
  this->pr = af->PrintReceipt();
  pr->printReceipt();
}

void OP::CancelMsg()
{
  // std::cout << "op->CancelMsg() called." << std::endl;
  this->cm = af->CancelMsg();
  cm->cancelMsg();
}

void OP::ReturnCash()
{
  // std::cout << "op->ReturnCash() called." << std::endl;
  this->rc = af->ReturnCash();
  rc->returnCash();
}

void OP::SetPayType(int t)
{
  // std::cout << "op->SetPayType() called with payment type: " << t << std::endl;
  this->spt = af->SetPayType(t);
  spt->setPayType(t);
}

void OP::EjectCard()
{
  // std::cout << "op->EjectCard() called." << std::endl;
  this->ec = af->EjectCard();
  ec->ejectCard();
}

GP1::GP1(DataStore1 *ds, MDAEFSM *mda, ConcreteFactory1 *cf1)
{
  this->d = ds;
  this->m = mda;
  this->cf1 = cf1;
}

void GP1::Activate(int a)
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 7)
  {
    if (a > 0)
    {
      ((DataStore1 *)d)->temp_a = a;
      m->Activate();
    }
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::Start()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 0)
  {
    m->Start();
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::PayCredit()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 1)
  {
    std::cout << "   Waiting for Approval (enter 5)" << std::endl;
    m->PayType(1);
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::Reject()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 2)
  {
    m->Reject();
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::Cancel()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 3)
  {
    m->Cancel();
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::Approved()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 2)
  {
    std::cout << "   The credit card is approved" << std::endl;
    m->Approved();
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::PayCash(int c)
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 1)
  {
    std::cout << "   Pay with cash: " << c << std::endl;
    if (c > 0)
    {
      ((DataStore1 *)d)->temp_cash = c;
      m->PayType(0);
    }
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::StartPump()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 3)
  {
    std::cout << "   Start pumping gas" << std::endl;
    m->Continue();
    m->StartPump();
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::Pump()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 5)
  {
    std::cout << "   Pumping gas" << std::endl;
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
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

void GP1::StopPump()
{
  int currentStateIndex = m->GetCurrentStateIndex();
  if (currentStateIndex == 5)
  {
    std::cout << "   Stop pumping gas" << std::endl;
    m->StopPump();
    m->Receipt();
  }
  else
  {
    std::cout << "   Error: wrong state" << std::endl;
  }
}

GP2::GP2(DataStore2 *ds, MDAEFSM *mda, ConcreteFactory2 *cf2)
{
  this->d = ds;
  this->m = mda;
  this->cf2 = cf2;
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

int main()
{
  DataStore1 ds1;
  DataStore2 ds2;
  ConcreteFactory1 cf1(&ds1);
  ConcreteFactory2 cf2(&ds2);
  std::string choice;
  int a, b, c;

  std::cout << "Welcome to GasPump System!" << std::endl;
  std::cout << "1. GasPump-1" << std::endl;
  std::cout << "2. GasPump-2" << std::endl;
  std::cout << "Select GasPump: ";
  std::cin >> choice;

  if (choice == "1")
  {
    OP op(&cf1);
    MDAEFSM mda(&op);
    GP1 gp1(&ds1, &mda, &cf1);
    while (choice != "q")
    {
      std::cout << std::endl;
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
        std::cout << std::endl;
        std::cout << "Operation: ";
        switch (std::stoi(choice))
        {
        case 0:
          std::cout << "Activate(a)" << std::endl;
          std::cout << std::endl;
          std::cout << "Enter price of the gas per liter: ";
          std::cin >> a;
          std::cout << std::endl;
          gp1.Activate(a);
          break;
        case 1:
          std::cout << "Start()" << std::endl;
          std::cout << std::endl;
          gp1.Start();
          break;
        case 2:
          std::cout << "PayCredit()" << std::endl;
          std::cout << std::endl;
          gp1.PayCredit();
          break;
        case 3:
          std::cout << "Reject()" << std::endl;
          std::cout << std::endl;
          gp1.Reject();
          break;
        case 4:
          std::cout << "Cancel()" << std::endl;
          std::cout << std::endl;
          gp1.Cancel();
          break;
        case 5:
          std::cout << "Approved()" << std::endl;
          std::cout << std::endl;
          gp1.Approved();
          break;
        case 6:
          std::cout << "PayCash()" << std::endl;
          std::cout << std::endl;
          std::cout << "Enter cash: ";
          std::cin >> c;
          std::cout << std::endl;
          gp1.PayCash(c);
          break;
        case 7:
          std::cout << "StartPump()" << std::endl;
          std::cout << std::endl;
          gp1.StartPump();
          break;
        case 8:
          std::cout << "Pump()" << std::endl;
          std::cout << std::endl;
          gp1.Pump();
          break;
        case 9:
          std::cout << "StopPump()" << std::endl;
          std::cout << std::endl;
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
    OP op(&cf2);
    MDAEFSM mda(&op);
    GP2 gp2(&ds2, &mda, &cf2);
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
          std::cout << "Enter cash: ";
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
