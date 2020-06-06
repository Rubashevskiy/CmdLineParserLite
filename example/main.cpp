/**
 * @author Yuriy Rubashevskiy (r9182230628@gmail.com)
 * @brief Пример  парсинга командной строки в объектном режиме
 * @version 0.1
 * @date 2020-06-05
 * 
 * @copyright Copyright (c) 2020 Free   Software   Foundation,  Inc.
 *     License  GPLv3+:  GNU  GPL  version  3  or  later <http://gnu.org/licenses/gpl.html>.
 *     This is free software: you are free to change and redistribute it.  
 *     There is NO WARRANTY, to the  extent  permitted by law.
 */

#include <iostream>

// Клас для работы с параметрами командной строки
#include "../src/CmdLineParserLite/cmdlineparserlite.hpp"

void result(CMDPARS::Param *p) {
  // Для наглядности вытаскиваем имена(в рабочем режиме(объектном) врядли пригодиться)
  std::string listName{};
  for (std::string n : p->name) listName += "'" + n + "' ";

  switch (p->type) {
    case CMDPARS::Arg::No: { // // Параметр без значений
      if (p->set) std::cout << "Param (not value): " << listName << " is set" << std::endl;
      else std::cout << "Param (not value): " << listName << " is not set" << std::endl;
      break;
    }
    case CMDPARS::Arg::Required: { // Значение параметра должен быть не пустое
      if (p->set)
        std::cout << "Param (Required value): "
                  << listName << " is set. Value: "
                  << p->value
                  << std::endl;
      else
        std::cout << "Param (Required value): " << listName << "is not set" << std::endl;
      break;
    }
    case CMDPARS::Arg::Optional: { // Параметр опциональный
      if (p->set) {
        std::string value = (p->value.empty()) ? ("NULL") : (p->value);
        std::cout << "Param (Optional value): "
                  << listName << " is set. Value: "
                  << value
                  << std::endl;
      }
      else {
        std::cout << "Param (Optional value): " << listName << "is not set" << std::endl;
      }
    }
  }
}

int main(int argc, char **argv) {
    // Класс для парсинга командной строки
  CMDPARS::CmdLineParserLite cmd(argc, argv);
  // Проверяем что не переданна строка без параметров
  if (cmd.isNull()) {
    std::cerr << "Param is null" << std::endl;
    exit(1);
  }
  // Параметр "команда" с обязтельным аргументом
  CMDPARS::Param select({"SELECT"}, CMDPARS::Arg::Required);
  // Параметр "команда" с обязтельным аргументом
  CMDPARS::Param update({"UPDATE"}, CMDPARS::Arg::Required);
  // Параметр "команда" с обязтельным аргументом
  CMDPARS::Param incert({"INCERT"}, CMDPARS::Arg::Required);
  // Параметр "команда" с обязтельным аргументом
  CMDPARS::Param del(   {"DELETE"}, CMDPARS::Arg::Required);
  // Параметр "ключ" без аргумента
  CMDPARS::Param help({"-h", "--help"}, CMDPARS::Arg::No);
  // Опциональный параметр
  CMDPARS::Param test({"-t","--test"}, CMDPARS::Arg::Optional);

  // Добавляем  в парсер
  cmd.addParam(&select);
  cmd.addParam(&update);
  cmd.addParam(&incert);
  cmd.addParam(&del);
  cmd.addParam(&help);
  cmd.addParam(&test);
  // Запускаем парсинг коммандной строки
  if (!cmd.parse()) {
    // Произошла ошибка
    std::cerr << cmd.lastErr() << std::endl;
    exit(1);
  }
  // Проверяем параметры (для упрощение через функцию result)
  result(&select);
  result(&update);
  result(&incert);
  result(&del);
  result(&help);
  result(&test);
  return 0;
}
