#ifndef MAIN_H
#define MAIN_H

#include <iostream>

class MDAEFSM;
class OP;
class ConcreteFactory1;
class ConcreteFactory2;

class DataStore
{
public:
};

class DataStore1 : public DataStore
{
public:
  int temp_a = 0;
  int price = 0;
  int L = 0;
  int total = 0;
  int temp_cash = 0;
  int w = 0;
  int cash = 0;
};

class DataStore2 : public DataStore
{
public:
  float temp_a;
  float temp_b;
  float temp_c;
  int temp_cash;
  float Dprice;
  float Rprice;
  float Pprice;
  int cash;
  float total;
  int G;
  float price;
};

//----------class about state pattern----------
class State
{
public:
  MDAEFSM *p;
  OP *op;
  State(MDAEFSM *mda, OP *op);
  State() : p(nullptr){};
  virtual void Activate();
  virtual void Start();
  virtual void PayType(int t);
  virtual void Reject();
  virtual void Cancel();
  virtual void Approved();
  virtual void StartPump();
  virtual void Pump();
  virtual void StopPump();
  virtual void SelectGas(int g);
  virtual void Receipt();
  virtual void NoReceipt();
  virtual void Continue();
};

class Start : public State
{
public:
  Start(MDAEFSM *mda, OP *op);
  void Activate() override;
};

class S0 : public State
{
public:
  S0(MDAEFSM *mda, OP *op);
  void Start() override;
};

class S1 : public State
{
public:
  S1(MDAEFSM *mda, OP *op);
  void PayType(int t) override;
};

class S2 : public State
{
public:
  S2(MDAEFSM *mda, OP *op);
  void Reject() override;
  void Approved() override;
};

class S3 : public State
{
public:
  S3(MDAEFSM *mda, OP *op);
  void Cancel() override;
  void Continue() override;
  void SelectGas(int g) override;
};

class S4 : public State
{
public:
  S4(MDAEFSM *mda, OP *op);
  void StartPump() override;
};

class S5 : public State
{
public:
  S5(MDAEFSM *mda, OP *op);
  void Pump() override;
  void StopPump() override;
};

class S6 : public State
{
public:
  S6(MDAEFSM *mda, OP *op);
  void NoReceipt() override;
  void Receipt() override;
};

class MDAEFSM
{
public:
  State *s;
  State *LS[8];
  Start start;
  S0 s0;
  S1 s1;
  S2 s2;
  S3 s3;
  S4 s4;
  S5 s5;
  S6 s6;
  MDAEFSM(OP *op);
  int GetCurrentStateIndex();
  void Activate();
  void Start();
  void PayType(int t);
  void Reject();
  void Cancel();
  void Approved();
  void StartPump();
  void Pump();
  void StopPump();
  void SelectGas(int g);
  void Receipt();
  void NoReceipt();
  void Continue();
  void ChangeState(int x);
};

//-------------end-------------

//----------class about stratgy pattern----------
class StorePrices
{
public:
  virtual void storePrices();
};

class StorePrices1 : public StorePrices
{
public:
  ConcreteFactory1 *cf1;
  StorePrices1(ConcreteFactory1 *cf1);
  void storePrices();
};

class StorePrices2 : public StorePrices
{
public:
  ConcreteFactory2 *cf2;
  StorePrices2(ConcreteFactory2 *cf2);
  void storePrices();
};

class PayMsg
{
public:
  virtual void payMsg();
};

class PayMsg1 : public PayMsg
{
public:
  void payMsg();
};

class PayMsg2 : public PayMsg
{
public:
  void payMsg();
};

class StoreCash
{
public:
  virtual void storeCash();
};

class StoreCash1 : public StoreCash
{
public:
  ConcreteFactory1 *cf1;
  StoreCash1(ConcreteFactory1 *cf1);
  void storeCash();
};

class StoreCash2 : public StoreCash
{
public:
  ConcreteFactory2 *cf2;
  StoreCash2(ConcreteFactory2 *cf2);
  void storeCash();
};

class DisplayMenu
{
public:
  virtual void displayMenu();
};

class DisplayMenu1 : public DisplayMenu
{
public:
  void displayMenu();
};

class DisplayMenu2 : public DisplayMenu
{
public:
  void displayMenu();
};

class RejectMsg
{
public:
  virtual void rejectMsg();
};

class RejectMsg1 : public RejectMsg
{
public:
  void rejectMsg();
};

class RejectMsg2 : public RejectMsg
{
public:
  void rejectMsg();
};

class SetPrice
{
public:
  virtual void setPrice(int g);
};

class SetPrice1 : public SetPrice
{
public:
  void setPrice(int g);
};

class SetPrice2 : public SetPrice
{
public:
  ConcreteFactory2 *cf2;
  SetPrice2(ConcreteFactory2 *cf2);
  void setPrice(int g);
};

class SetInitValues
{
public:
  virtual void setInitValues();
};

class SetInitValues1 : public SetInitValues
{
public:
  ConcreteFactory1 *cf1;
  SetInitValues1(ConcreteFactory1 *cf1);
  void setInitValues();
};

class SetInitValues2 : public SetInitValues
{
public:
  ConcreteFactory2 *cf2;
  SetInitValues2(ConcreteFactory2 *cf2);
  void setInitValues();
};

class PumpGasUnit
{
public:
  virtual void pumpGasUnit();
};

class PumpGasUnit1 : public PumpGasUnit
{
public:
  ConcreteFactory1 *cf1;
  PumpGasUnit1(ConcreteFactory1 *cf1);
  void pumpGasUnit();
};

class PumpGasUnit2 : public PumpGasUnit
{
public:
  ConcreteFactory2 *cf2;
  PumpGasUnit2(ConcreteFactory2 *cf2);
  void pumpGasUnit();
};

class GasPumpedMsg
{
public:
  virtual void gasPumpedMsg();
};

class GasPumpedMsg1 : public GasPumpedMsg
{
public:
  ConcreteFactory1 *cf1;
  GasPumpedMsg1(ConcreteFactory1 *cf1);
  void gasPumpedMsg();
};

class GasPumpedMsg2 : public GasPumpedMsg
{
public:
  ConcreteFactory2 *cf2;
  GasPumpedMsg2(ConcreteFactory2 *cf2);
  void gasPumpedMsg();
};

class PrintReceipt
{
public:
  virtual void printReceipt();
};

class PrintReceipt1 : public PrintReceipt
{
public:
  ConcreteFactory1 *cf1;
  PrintReceipt1(ConcreteFactory1 *cf1);
  void printReceipt();
};

class PrintReceipt2 : public PrintReceipt
{
public:
  ConcreteFactory2 *cf2;
  PrintReceipt2(ConcreteFactory2 *cf2);
  void printReceipt();
};

class CancelMsg
{
public:
  virtual void cancelMsg();
};

class CancelMsg1 : public CancelMsg
{
public:
  void cancelMsg();
};

class CancelMsg2 : public CancelMsg
{
public:
  void cancelMsg();
};

class ReturnCash
{
public:
  virtual void returnCash();
};

class ReturnCash1 : public ReturnCash
{
public:
  ConcreteFactory1 *cf1;
  ReturnCash1(ConcreteFactory1 *cf1);
  void returnCash();
};

class ReturnCash2 : public ReturnCash
{
public:
  ConcreteFactory2 *cf2;
  ReturnCash2(ConcreteFactory2 *cf2);
  void returnCash();
};

class SetPayType
{
public:
  virtual void setPayType(int t);
};

class SetPayType1 : public SetPayType
{
public:
  ConcreteFactory1 *cf1;
  SetPayType1(ConcreteFactory1 *cf1);
  void setPayType(int t);
};

class SetPayType2 : public SetPayType
{
public:
  void setPayType(int t);
};

class EjectCard
{
public:
  virtual void ejectCard();
};

class EjectCard1 : public EjectCard
{
public:
  void ejectCard();
};

class EjectCard2 : public EjectCard
{
public:
  void ejectCard();
};

//-------------end-------------

//------class about Abstract Factory pattern------
class AbstractFactory
{
public:
  AbstractFactory();
  virtual StorePrices *StorePrices();
  virtual PayMsg *PayMsg();
  virtual StoreCash *StoreCash();
  virtual DisplayMenu *DisplayMenu();
  virtual RejectMsg *RejectMsg();
  virtual SetPrice *SetPrice(int g);
  virtual SetInitValues *SetInitValues();
  virtual PumpGasUnit *PumpGasUnit();
  virtual GasPumpedMsg *GasPumpedMsg();
  virtual PrintReceipt *PrintReceipt();
  virtual CancelMsg *CancelMsg();
  virtual ReturnCash *ReturnCash();
  virtual SetPayType *SetPayType(int t);
  virtual EjectCard *EjectCard();
};

class ConcreteFactory1 : public AbstractFactory
{
public:
  DataStore1 *d;
  ConcreteFactory1(DataStore1 *d);
  int getIntData(std::string s);
  void setIntData(std::string s, int n);
  StorePrices1 *StorePrices() override;
  PayMsg1 *PayMsg() override;
  StoreCash1 *StoreCash() override;
  DisplayMenu1 *DisplayMenu() override;
  RejectMsg1 *RejectMsg() override;
  SetPrice1 *SetPrice(int g) override;
  SetInitValues1 *SetInitValues() override;
  PumpGasUnit1 *PumpGasUnit() override;
  GasPumpedMsg1 *GasPumpedMsg() override;
  PrintReceipt1 *PrintReceipt() override;
  CancelMsg1 *CancelMsg() override;
  ReturnCash1 *ReturnCash() override;
  SetPayType1 *SetPayType(int t) override;
  EjectCard1 *EjectCard() override;
};

class ConcreteFactory2 : public AbstractFactory
{
public:
  DataStore2 *d;
  ConcreteFactory2(DataStore2 *d);
  float getIntData(std::string s);
  void setIntData(std::string s, float n);
  StorePrices2 *StorePrices() override;
  PayMsg2 *PayMsg() override;
  StoreCash2 *StoreCash() override;
  DisplayMenu2 *DisplayMenu() override;
  RejectMsg2 *RejectMsg() override;
  SetPrice2 *SetPrice(int g) override;
  SetInitValues2 *SetInitValues() override;
  PumpGasUnit2 *PumpGasUnit() override;
  GasPumpedMsg2 *GasPumpedMsg() override;
  PrintReceipt2 *PrintReceipt() override;
  CancelMsg2 *CancelMsg() override;
  ReturnCash2 *ReturnCash() override;
  SetPayType2 *SetPayType(int t) override;
  EjectCard2 *EjectCard() override;
};

//-------------end-------------

class OP
{
public:
  StorePrices *storep;
  PayMsg *pm;
  StoreCash *sc;
  DisplayMenu *dm;
  RejectMsg *rm;
  SetPrice *setp;
  SetInitValues *sv;
  PumpGasUnit *pgu;
  GasPumpedMsg *gpm;
  PrintReceipt *pr;
  CancelMsg *cm;
  ReturnCash *rc;
  SetPayType *spt;
  EjectCard *ec;
  AbstractFactory *af;
  OP(AbstractFactory *af);
  void StorePrices();
  void PayMsg();
  void StoreCash();
  void DisplayMenu();
  void RejectMsg();
  void SetPrice(int g);
  void SetInitValues();
  void PumpGasUnit();
  void GasPumpedMsg();
  void PrintReceipt();
  void CancelMsg();
  void ReturnCash();
  void SetPayType(int t);
  void EjectCard();
};

class GP1
{
  MDAEFSM *m;
  DataStore *d;
  ConcreteFactory1 *cf1;

public:
  GP1(DataStore1 *ds, MDAEFSM *mda, ConcreteFactory1 *cf1);
  void Activate(int a);
  void Start();
  void PayCredit();
  void Reject();
  void Cancel();
  void Approved();
  void PayCash(int c);
  void StartPump();
  void Pump();
  void StopPump();
};

class GP2
{
  MDAEFSM *m;
  DataStore *d;
  ConcreteFactory2 *cf2;

public:
  GP2(DataStore2 *ds, MDAEFSM *mda, ConcreteFactory2 *cf2);
  void Activate(float a, float b, float c);
  void Start();
  void PayCash(int c);
  void Cancel();
  void Premium();
  void Regular();
  void Diesel();
  void StartPump();
  void PumpGallon();
  void Stop();
  void Receipt();
  void NoReceipt();
};

#endif /* MAIN_H */
