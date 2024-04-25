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
  int total;
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
};

class PayMsg1 : public PayMsg
{
public:
  void PayMsg();
};

class PayMsg2 : public PayMsg
{
public:
  void PayMsg();
};

class StoreCash
{
public:
};

class StoreCash1 : public StoreCash
{
public:
  void StoreCash();
};

class StoreCash2 : public StoreCash
{
public:
  void StoreCash();
};

class DisplayMenu
{
public:
};

class DisplayMenu1 : public DisplayMenu
{
public:
  void DisplayMenu();
};

class DisplayMenu2 : public DisplayMenu
{
public:
  void DisplayMenu();
};

class RejectMsg
{
public:
};

class RejectMsg1 : public RejectMsg
{
public:
  void RejectMsg();
};

class RejectMsg2 : public RejectMsg
{
public:
  void RejectMsg();
};

class SetPrice
{
public:
};

class SetPrice1 : public SetPrice
{
public:
  void SetPrice();
};

class SetPrice2 : public SetPrice
{
public:
  void SetPrice();
};

class SetInitValues
{
public:
};

class SetInitValues1 : public SetInitValues
{
public:
  void SetInitValues();
};

class SetInitValues2 : public SetInitValues
{
public:
  void SetInitValues();
};

class PumpGasUnit
{
public:
};

class PumpGasUnit1 : public PumpGasUnit
{
public:
  void PumpGasUnit();
};

class PumpGasUnit2 : public PumpGasUnit
{
public:
  void PumpGasUnit();
};

class GasPumpedMsg
{
public:
};

class GasPumpedMsg1 : public GasPumpedMsg
{
public:
  void GasPumpedMsg();
};

class GasPumpedMsg2 : public GasPumpedMsg
{
public:
  void GasPumpedMsg();
};

class PrintReceipt
{
public:
};

class PrintReceipt1 : public PrintReceipt
{
public:
  void PrintReceipt();
};

class PrintReceipt2 : public PrintReceipt
{
public:
  void PrintReceipt();
};

class CancelMsg
{
public:
};

class CancelMsg1 : public CancelMsg
{
public:
  void CancelMsg();
};

class CancelMsg2 : public CancelMsg
{
public:
  void CancelMsg();
};

class ReturnCash
{
public:
};

class ReturnCash1 : public ReturnCash
{
public:
  void ReturnCash();
};

class ReturnCash2 : public ReturnCash
{
public:
  void ReturnCash();
};

class SetPayType
{
public:
};

class SetPayType1 : public SetPayType
{
public:
  void SetPayType();
};

class SetPayType2 : public SetPayType
{
public:
  void SetPayType();
};

class EjectCard
{
public:
};

class EjectCard1 : public EjectCard
{
public:
  void EjectCard();
};

class EjectCard2 : public EjectCard
{
public:
  void EjectCard();
};

//-------------end-------------

//------class about Abstract Factory pattern------
class AbstractFactory
{
public:
  AbstractFactory();
  virtual StorePrices *StorePrices();
  virtual void PayMsg();
  virtual void StoreCash();
  virtual void DisplayMenu();
  virtual void RejectMsg();
  virtual void SetPrice(int g);
  virtual void SetInitValues();
  virtual void PumpGasUnit();
  virtual void GasPumpedMsg();
  virtual void PrintReceipt();
  virtual void CancelMsg();
  virtual void ReturnCash();
  virtual void SetPayType(int t);
  virtual void EjectCard();
};

class ConcreteFactory1 : public AbstractFactory
{
public:
  DataStore1 *d;
  ConcreteFactory1(DataStore1 *d);
  int getIntData(std::string s);
  void setIntData(std::string s, int n);
  StorePrices1 *StorePrices() override;
  void PayMsg() override;
  void StoreCash() override;
  void DisplayMenu() override;
  void RejectMsg() override;
  void SetPrice(int g) override;
  void SetInitValues() override;
  void PumpGasUnit() override;
  void GasPumpedMsg() override;
  void PrintReceipt() override;
  void CancelMsg() override;
  void ReturnCash() override;
  void SetPayType(int t) override;
  void EjectCard() override;
};

class ConcreteFactory2 : public AbstractFactory
{
public:
  DataStore2 *d;
  ConcreteFactory2(DataStore2 *d);
  StorePrices2 *StorePrices() override;
  void PayMsg() override;
  void StoreCash() override;
  void DisplayMenu() override;
  void RejectMsg() override;
  void SetPrice(int g) override;
  void SetInitValues() override;
  void PumpGasUnit() override;
  void GasPumpedMsg() override;
  void PrintReceipt() override;
  void CancelMsg() override;
  void ReturnCash() override;
  void SetPayType(int t) override;
  void EjectCard() override;
};

//-------------end-------------

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
  PumpGasUnit *psu;
  GasPumpedMsg *gpu;
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
