#ifndef MAIN_H
#define MAIN_H

#include <iostream>

class MDAEFSM;
class OP;

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

class AbstractFactory
{
public:
  AbstractFactory();
  virtual void StorePrices();
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

class StorePrices
{
public:
};

class StorePrices1
{
public:
  void StorePrices();
};

class StorePrices2
{
public:
  void StorePrices();
};

class ConcreteFactory1 : public AbstractFactory
{
public:
  // DataStore1 *d;
  ConcreteFactory1();
  void StorePrices() override;
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
  // DataStore2 *d;
  ConcreteFactory2();
  void StorePrices() override;
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

class OP
{
public:
  OP();
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

class DataStore
{
public:
};

class DataStore1 : public DataStore
{
public:
  int temp_a;
  int price;
  int L;
  int total;
  int temp_cash;
  int w;
  int cash;
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

class GP1
{
  MDAEFSM *m;
  DataStore *d;
  AbstractFactory *af;

public:
  GP1(DataStore1 *ds, MDAEFSM *mda, AbstractFactory *af);
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

public:
  GP2(DataStore2 *ds);
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
