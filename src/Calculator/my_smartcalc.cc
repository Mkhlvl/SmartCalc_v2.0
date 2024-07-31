#include "my_smartcalc.h"

using namespace my;

ControllerSmartCalc::ControllerSmartCalc() : model_(new ModelSmartCalc) {};
ControllerSmartCalc::~ControllerSmartCalc() { delete model_; };

void ControllerSmartCalc::CalculateExpression(const std::string expr,
                                              std::string x) {
  model_->CalculateExpression(expr, x);
}

double ControllerSmartCalc::GetExpressionResult() const {
  return model_->GetExpressionResult();
}

void ControllerSmartCalc::CalculateGraph(const std::string expr,
                                         std::string x_begin,
                                         std::string x_end) {
  model_->CalculateGraph(expr, x_begin, x_end);
}

VectorXY ControllerSmartCalc::GetGraphResult() const {
  return model_->GetGraphResult();
}

ControllerBankCalc::ControllerBankCalc() : model_(new ModelBankCalc) {};
ControllerBankCalc::~ControllerBankCalc() { delete model_; };

void ControllerBankCalc::CalculateAnnuietet(double loan, double term,
                                            double rate) {
  model_->CalculateAnnuietet(loan, term, rate);
}

void ControllerBankCalc::CalculateDifferPayment(double loan, double term,
                                                double rate) {
  model_->CalculateDifferPayment(loan, term, rate);
}

std::vector<double> ControllerBankCalc::GetCreditResult() const {
  return model_->GetCreditResult();
}

std::string Lexema::GetName() { return name_; };
Priority Lexema::GetPriority() { return priority_; };
Type Lexema::GetType() { return type_; };
Associativity Lexema::GetAssociativity() { return associativity_; };
choice_action &Lexema::GetAction() { return action_; };

std::map<std::string, Lexema> ModelSmartCalc::lexema_model_({
    {"cos", Lexema("cos", kFunction, kUnaryFunction, kRight, cosl)},
    {"sin", Lexema("sin", kFunction, kUnaryFunction, kRight, sinl)},
    {"tan", Lexema("tan", kFunction, kUnaryFunction, kRight, tanl)},
    {"acos", Lexema("acos", kFunction, kUnaryFunction, kRight, acosl)},
    {"asin", Lexema("asin", kFunction, kUnaryFunction, kRight, asinl)},
    {"atan", Lexema("atan", kFunction, kUnaryFunction, kRight, atanl)},
    {"sqrt", Lexema("sqrt", kFunction, kUnaryFunction, kRight, sqrtl)},
    {"ln", Lexema("ln", kFunction, kUnaryFunction, kRight, logl)},
    {"log", Lexema("log", kFunction, kUnaryFunction, kRight, log10l)},
    {"mod", Lexema("mod", kMedium, kBinaryOperation, kLeft, fmodl)},
    {"x", Lexema("x", kNone, kNumber, kWithout, nullptr)},
    {"(", Lexema("(", kNone, kBracketOpen, kWithout, nullptr)},
    {")", Lexema(")", kNone, kBracketClose, kWithout, nullptr)},
    {"+", Lexema("+", kLow, kBinaryOperation, kLeft, std::plus<double>())},
    {"-", Lexema("-", kLow, kBinaryOperation, kLeft, std::minus<double>())},
    {"*",
     Lexema("*", kMedium, kBinaryOperation, kLeft, std::multiplies<double>())},
    {"/",
     Lexema("/", kMedium, kBinaryOperation, kLeft, std::divides<double>())},
    {"^", Lexema("^", kHigh, kBinaryOperation, kRight, powl)},
});

bool ModelSmartCalc::kCheckMatrix[kTypes][kTypes] = {
    {0, 1, 0, 0, 0, 1}, {1, 0, 1, 1, 1, 0}, {1, 0, 1, 1, 1, 0},
    {0, 0, 0, 0, 1, 0}, {1, 0, 1, 1, 1, 0}, {0, 1, 0, 0, 0, 1},
};

bool ModelSmartCalc::kFirst[kTypes] = {1, 0, 1, 1, 1, 0};

bool ModelSmartCalc::kLast[kTypes] = {1, 0, 0, 0, 0, 1};

double ModelSmartCalc::ConvertToDouble(std::string expr) {
  return std::stod(expr);
}

std::string ModelSmartCalc::ConvertToLoverCase(std::string expr) {
  transform(expr.begin(), expr.end(), expr.begin(), ::tolower);
  expr.erase(std::remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
  return expr;
}

void ModelSmartCalc::FindExtraSigns(std::string &expr) {
  std::regex rex{"([+-]{3,})"};
  std::smatch match;
  if (std::regex_search(expr, match, rex)) {
    throw std::logic_error("Wrong operations series " + match.str());
  }
}

void ModelSmartCalc::FindOperation(std::string expr) {
  auto it = lexema_model_.find(expr);
  if (it == lexema_model_.end()) {
    throw std::logic_error("Wrong operation " + expr);
  }
  input_.push(it->second);
}

void ModelSmartCalc::ReadWord(std::string::iterator &it) {
  std::string lexema = "";
  while (isalpha(*it)) {
    lexema += (*it);
    ++it;
  }
  FindOperation(lexema);
}

std::string ModelSmartCalc::ReadDigit(std::string::iterator &it) {
  std::string lexema = "";
  while (isdigit(*it)) {
    lexema += (*it);
    ++it;
  }
  return lexema;
}

void ModelSmartCalc::AddNumberToLexema(std::string expr) {
  Lexema number{expr, kNone, kNumber, kWithout, ConvertToDouble(expr)};
  input_.push(number);
}

void ModelSmartCalc::ReadDouble(std::string::iterator &it) {
  std::string lexema = "";
  lexema += ReadDigit(it);
  if (*it == '.') {
    lexema += (*it);
    ++it;
    lexema += ReadDigit(it);
  }
  if (*it == 'e') {
    lexema += (*it);
    ++it;
    if ((*it == '+') || (*it == '-')) {
      lexema += (*it);
      ++it;
      lexema += ReadDigit(it);
    }
  }
  AddNumberToLexema(lexema);
}

void ModelSmartCalc::ReadInput(std::string expr) {
  FindExtraSigns(expr);
  std::string::iterator it = expr.begin();
  std::string simbol;
  while (it != expr.end()) {
    if (isalpha(*it)) {
      ReadWord(it);
    } else if (isdigit(*it)) {
      ReadDouble(it);
    } else {
      simbol = *it;
      FindOperation(simbol);
      ++it;
    }
  }
}

void ModelSmartCalc::SendToOutput() {
  if (!input_.empty()) {
    output_.push(input_.front());
    input_.pop();
  }
}

void ModelSmartCalc::AddMultSigns() {
  SendToOutput();
  while (!input_.empty()) {
    if (((output_.back().GetType() == kNumber) &&
         ((input_.front().GetType() == kBracketOpen) ||
          (input_.front().GetType() == kNumber) ||
          (input_.front().GetType() == kUnaryFunction))) ||
        ((output_.back().GetType() == kBracketClose) &&
         (((input_.front().GetType() == kUnaryFunction)) ||
          (input_.front().GetType() == kNumber))) ||
        ((output_.back().GetType() == kBracketClose) &&
         ((input_.front().GetType() == kBracketOpen)))) {
      output_.push(
          {"*", kMedium, kBinaryOperation, kLeft, std::multiplies<double>()});
    }
    SendToOutput();
  }
}

void ModelSmartCalc::ChangeUnaryToNegate() {
  if (input_.front().GetPriority() == kLow) {
    if (input_.front().GetName() == "-") {
      output_.push({"negate", kUnary, kUnaryOperationPrefix, kRight,
                    std::negate<double>()});

    } else {
      if (!(output_.empty() || output_.back().GetType() == kBracketOpen ||
            output_.back().GetPriority() == kLow)) {
        output_.push(input_.front());
      }
    }
    input_.pop();
  }
}

void ModelSmartCalc::ConvertToUnary() {
  input_ = std::move(output_);
  ChangeUnaryToNegate();
  while (!input_.empty()) {
    SendToOutput();
    if (!input_.empty()) {
      if (!((output_.back().GetType() == kNumber) ||
            (output_.back().GetType() == kBracketClose))) {
        ChangeUnaryToNegate();
      }
    }
  }
}

void ModelSmartCalc::LogicCheck() {
  int count_brackets = 0;
  input_ = std::move(output_);
  if (!kFirst[input_.front().GetType()]) {
    throw std::logic_error("Logic error! " + input_.front().GetName() +
                           " cannot be in the begining!");
  }
  if (!kLast[input_.back().GetType()]) {
    throw std::logic_error("Logic error! " + input_.back().GetName() +
                           " cannot be in the end!");
  }
  while (!input_.empty()) {
    SendToOutput();
    if (output_.back().GetType() == kBracketClose) count_brackets--;
    if (output_.back().GetType() == kBracketOpen) count_brackets++;
    if (count_brackets < 0)
      throw std::logic_error("Logic error! Small problem with brackets");
    if (!input_.empty()) {
      if (!kCheckMatrix[output_.back().GetType()][input_.front().GetType()]) {
        throw std::logic_error("Logic error! " + output_.back().GetName() +
                               " " + input_.front().GetName());
      }
    }
  }
  if (count_brackets)
    throw std::logic_error("Logic error! Small problem with brackets");
}

void ModelSmartCalc::SendToStack() {
  if (!input_.empty()) {
    stack_.push_back(input_.front());
    input_.pop();
  }
}

void ModelSmartCalc::GetFromStack() {
  if (!stack_.empty()) {
    output_.push(stack_.back());
    stack_.pop_back();
  }
}

void ModelSmartCalc::ConvertToOPN() {
  input_ = std::move(output_);
  while (!input_.empty()) {
    switch (input_.front().GetType()) {
      case kNumber:
        SendToOutput();
        break;
      case kUnaryFunction:
      case kUnaryOperationPrefix:
      case kBracketOpen:
        SendToStack();
        break;
      case kBracketClose: {
        while (stack_.back().GetType() != kBracketOpen) {
          GetFromStack();
        }
        stack_.pop_back();
        input_.pop();
        break;
      }
      case kBinaryOperation: {
        if (!stack_.empty()) {
          while (
              (stack_.back().GetType() == kUnaryFunction) ||
              (stack_.back().GetPriority() > input_.front().GetPriority()) ||
              ((stack_.back().GetAssociativity() == kLeft) &&
               (stack_.back().GetPriority() == input_.front().GetPriority()))) {
            GetFromStack();
            if (stack_.empty()) break;
          }
        }
        SendToStack();
        break;
      }
      default:
        break;
    }
  }
  while (!stack_.empty()) {
    GetFromStack();
  }
}

double ModelSmartCalc::GetFromOPN() {
  double value = double_res_.back();
  double_res_.pop_back();
  return value;
}

double ModelSmartCalc::MakeAction(double x_) {
  while (!output_.empty()) {
    std::visit(overload{
                   [&](double function) { double_res_.push_back(function); },
                   [&](unary_action function) {
                     double_res_.push_back(function(GetFromOPN()));
                   },
                   [&](binary_action function) {
                     double rvalue = GetFromOPN();
                     double_res_.push_back(function(GetFromOPN(), rvalue));
                   },
                   [&](auto) { double_res_.push_back(x_); },
               },
               output_.front().GetAction());
    output_.pop();
  }
  return GetFromOPN();
}

void ModelSmartCalc::ClearCalculator() {
  x_ = NAN;
  while (!input_.empty()) {
    input_.pop();
  }
  while (!output_.empty()) {
    output_.pop();
  }
  stack_.clear();
  double_res_.clear();
};

void ModelSmartCalc::MakeOPN(const std::string &expr) {
  ReadInput(ConvertToLoverCase(expr));
  AddMultSigns();
  ConvertToUnary();
  LogicCheck();
  ConvertToOPN();
}

void ModelSmartCalc::CalculateExpression(const std::string expr,
                                         std::string x) {
  ClearCalculator();
  input_string_ = expr;
  if (!x.empty()) {
    x_ = ConvertToDouble(x);
  }
  MakeOPN(input_string_);
  result_ = MakeAction(x_);
}

void ModelSmartCalc::CalculateGraph(const std::string expr, std::string x_begin,
                                    std::string x_end) {
  ClearCalculator();
  std::vector<double> x, y;
  MakeOPN(expr);
  std::queue<Lexema> tmp = output_;
  double x_min = -15.;
  double x_max = 15.;
  if (!x_begin.empty() && !x_end.empty()) {
    x_min = ConvertToDouble(x_begin);
    x_max = ConvertToDouble(x_end);
  }
  double step = (fabs(x_min) + fabs(x_max)) / 250000.;
  for (auto i = x_min; i <= x_max + step; i += step) {
    x.push_back(i);
    y.push_back(MakeAction(i));
    output_ = tmp;
  }
  graph_ = std::make_pair(x, y);
}

void ModelBankCalc::CalculateAnnuietet(double loan, double term, double rate) {
  if (!loan || !term || !rate) {
    throw std::logic_error("Error! Fill in correctly all request detail!");
  }
  double_res_.clear();
  double rate_per_month = rate / 12. / 100.;
  double tmp = pow((1. + rate_per_month), term);
  double kAnn = rate_per_month * tmp / (tmp - 1.);
  double payment_per_month = (round((kAnn * loan) * 100.)) / 100;
  double payment_total = payment_per_month * term;
  double overpayment = payment_total - loan;
  double_res_ = {payment_per_month, overpayment, payment_total};
}

void ModelBankCalc::CalculateDifferPayment(double loan, double term,
                                           double rate) {
  if (!loan || !term || !rate) {
    throw std::logic_error("Error! Fill in correctly all request detail!");
  }
  double_res_.clear();
  double platDolgMes = 0;
  double platProcentMes = 0;
  double sumMes = 0;
  double ostDolga = loan;
  double uplataVsego = 0;
  double uplataProcentVsego = 0;
  double uplataDolgVsego = 0;
  double platMin = 0;
  double platMax = 0;
  platDolgMes = loan / term;
  double_res_.push_back(term);  // 0 element

  for (int i = 1; i <= term; i++) {
    uplataDolgVsego += platDolgMes;
    platProcentMes = ostDolga * rate / 1200;
    uplataProcentVsego += platProcentMes;
    sumMes = platDolgMes + platProcentMes;
    ostDolga -= platDolgMes;
    if (i == 1) {
      platMax = sumMes;
    }
    if (i == term) {
      platMin = sumMes;
    }
    double_res_.push_back(sumMes);
    double_res_.push_back(platDolgMes);
    double_res_.push_back(platProcentMes);
    double_res_.push_back(ostDolga);
    uplataVsego += sumMes;
  }
  double_res_.push_back(uplataVsego);
  double_res_.push_back(uplataDolgVsego);
  double_res_.push_back(uplataProcentVsego);
  double_res_.push_back(ostDolga);
  double_res_.push_back(platMax);
  double_res_.push_back(platMin);
  double_res_.push_back(uplataProcentVsego);
  double_res_.push_back(uplataVsego);
}

double ModelSmartCalc::GetExpressionResult() const { return result_; }

VectorXY ModelSmartCalc::GetGraphResult() const { return graph_; }

std::vector<double> ModelBankCalc::GetCreditResult() const {
  return double_res_;
}
