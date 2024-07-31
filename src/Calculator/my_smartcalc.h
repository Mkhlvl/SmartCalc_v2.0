#ifndef MY_SMARTCALC_H_
#define MY_SMARTCALC_H_

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <variant>
#include <vector>
namespace my {
template <class... Ts>
struct overload : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overload(Ts...) -> overload<Ts...>;

using unary_action = std::function<double(double)>;
using binary_action = std::function<double(double, double)>;
using choice_action =
    std::variant<double, unary_action, binary_action, std::nullptr_t>;
using VectorXY = std::pair<std::vector<double>, std::vector<double>>;

enum Priority {
  kNone,
  kLow,
  kMedium,
  kHigh,
  kUnary,
  kFunction,
};
enum Associativity {
  kWithout,
  kLeft,
  kRight,
};
enum Type {
  kNumber,
  kBinaryOperation,
  kUnaryOperationPrefix,
  kUnaryFunction,
  kBracketOpen,
  kBracketClose,
  kTypes,
};

class Lexema {
 public:
  Lexema() = default;
  Lexema(const std::string &name, Priority priority, Type type,
         Associativity associatyvity, choice_action action) {
    this->name_ = name;
    this->priority_ = priority;
    this->type_ = type;
    this->associativity_ = associatyvity;
    this->action_ = action;
  };
  std::string GetName();
  Priority GetPriority();
  Type GetType();
  Associativity GetAssociativity();
  choice_action &GetAction();

 private:
  std::string name_;
  Priority priority_;
  Type type_;
  Associativity associativity_;
  choice_action action_;
};

class ModelSmartCalc {
 public:
  ModelSmartCalc() {};
  ~ModelSmartCalc() = default;
  void CalculateExpression(const std::string input_string, std::string x);
  void CalculateGraph(const std::string expr, std::string x_begin,
                      std::string x_end);
  double GetExpressionResult() const;
  VectorXY GetGraphResult() const;

 private:
  std::string input_string_;
  double x_;
  double result_;
  VectorXY graph_;
  std::queue<Lexema> input_{};
  std::queue<Lexema> output_{};
  std::vector<Lexema> stack_{};
  std::vector<double> double_res_{};

  double ConvertToDouble(std::string expr);
  std::string ConvertToLoverCase(std::string expr);
  void FindExtraSigns(std::string &expr);
  void FindOperation(std::string expr);
  void ReadWord(std::string::iterator &it);
  std::string ReadDigit(std::string::iterator &it);
  void AddNumberToLexema(std::string expr);
  void ReadDouble(std::string::iterator &it);
  void ReadInput(std::string expr);
  void SendToOutput();
  void AddMultSigns();
  void ChangeUnaryToNegate();
  void ConvertToUnary();
  void LogicCheck();
  void SendToStack();
  void GetFromStack();
  double GetFromOPN();
  void ConvertToOPN();
  void MakeOPN(const std::string &input_string);
  double MakeAction(double x_);
  void ClearCalculator();

  static std::map<std::string, Lexema> lexema_model_;
  static bool kCheckMatrix[kTypes][kTypes];
  static bool kFirst[kTypes];
  static bool kLast[kTypes];
};

class ModelBankCalc {
 public:
  ModelBankCalc() {};
  ~ModelBankCalc() = default;
  void CalculateAnnuietet(double loan, double term, double rate);
  void CalculateDifferPayment(double loan, double term, double rate);
  std::vector<double> GetCreditResult() const;

 private:
  std::string input_string_;
  double x_;
  double result_;
  VectorXY graph_;
  std::vector<double> double_res_{};
};

class ControllerSmartCalc {
 public:
  ControllerSmartCalc();
  ~ControllerSmartCalc();
  void CalculateExpression(const std::string str, std::string x);
  double GetExpressionResult() const;
  void CalculateGraph(const std::string expr, std::string x_begin,
                      std::string x_end);
  VectorXY GetGraphResult() const;

 private:
  ModelSmartCalc *model_;
};

class ControllerBankCalc {
 public:
  ControllerBankCalc();
  ~ControllerBankCalc();
  void CalculateAnnuietet(double loan, double term, double rate);
  void CalculateDifferPayment(double loan, double term, double rate);
  std::vector<double> GetCreditResult() const;

 private:
  ModelBankCalc *model_;
};
}  // namespace my

#endif  // MY_SMARTCALC_H_
